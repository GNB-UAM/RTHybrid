#include "../includes/calibrate_functions_phase1.h"

int ini_recibido (double *min_rel_real, double *min_abs_real, double *max_abs_real, double *max_rel_real, double *period_signal, Daq_session * session, int chan, int period, int freq, char* filename, double input_factor, int observation_time){

    /*VARIABLES TO DETERMINATE RANGES*/
    int i=0;
    double retval=0.0;
    struct timespec ts_target, ts_start;
    double max_abs = -DBL_MAX;
    double min_abs =  DBL_MAX;
    double percentage_min = 0.10;
    double percentage_max = 0.90;
    double range;

    /*DAQ Config*/
    int n_channels = 1;
    int in_channels [1];
    double ret_values [1];
    in_channels[0] = chan;

    /*RT config*/
    clock_gettime(CLOCK_MONOTONIC, &ts_target);
    ts_assign (&ts_start,  ts_target);
    ts_add_time(&ts_target, 0, period);

    /*DECLARACIONES DE ARRAYS Y SUS TAMAÑOS*/
    int size_signal = freq*observation_time;
    double * signal = (double*) malloc(sizeof(double) * size_signal);

    /*
    double * convolution = (double*) malloc(sizeof(double) * size_signal);
    int size_media = size_signal / 10;
    double * media = (double*) malloc(sizeof(double) * size_signal);
    */

    for (i=0; i<size_signal; i++){

        /*SLEEP & READ DATA*/
        clock_nanosleep(CLOCK_MONOTONIC, TIMER_ABSTIME, &ts_target, NULL);
        if (daq_read(session, n_channels, in_channels, ret_values) != 0) {
            return -1;
        }
        retval = (ret_values[0] * 1000.0) / input_factor;
        signal[i] = retval;
        
        /*DETECT MAX/MIN*/
        if(retval>max_abs){
            max_abs=retval;
        }else if(retval<min_abs){
            min_abs=retval;
        }
        
        /*NEXT PERIOD*/
        ts_add_time(&ts_target, 0, period); 
    }
    
    /*RETURN*/
    range = max_abs - min_abs;
    *min_abs_real = min_abs;
    *max_abs_real = max_abs;
    *min_rel_real = percentage_min * range + min_abs;
    *max_rel_real = percentage_max * range + min_abs;

    /*SIGNAL PERIOD*/

    /*Functions to reduce noise*/
    //signal_convolution (signal, size_signal, convolution, size_signal);
    //signal_average     (signal, size_signal, media,       size_media);

    *period_signal = signal_period (observation_time, signal, size_signal, *max_rel_real, *min_rel_real);

    /*Save signal to file*/
    //array_to_file (signal,      size_signal, filename, "lectura_ini");
    //array_to_file (convolution, size_signal, filename, "lectura_ini_filtro");

    return OK;
}

/***
Fixed convolution
***/
int signal_convolution (double * signal, int size_l, double * result, int size_r){
    if(size_l!=size_r)
        return ERR;
    int i;
    for (i=0; i<size_l; i++){
      if(i>3){
        result[i]= 0.2*signal[i]  + 0.2*signal[i-1] + 0.2*signal[i-2] + 0.2*signal[i-3] + 0.2*signal[i-4];
      }else{
        result[i]=signal[i];
      }
    }
    return OK;
}

/***
Downsample signal using average value method
***/
int signal_average(double * signal, int size_l, double * result, int size_r){
    if (size_r>=size_l)
        return ERR;
    int saltar = size_l / size_r;
    int i, j;
    for (i=0, j=0; i<size_l; i++, j++){
        int counter = i+saltar;
        double sum = 0.0;
        for(; i<counter; i++){
            sum += signal[i];
        }
        sum = sum / saltar;
        result[j] = sum;

    }
    return OK;
}

/***
Get period using two thresholds
***/
double signal_period(int seg_observacion, double * signal, int size, double th_up, double th_on){
    int up=FALSE;
    if (signal[0]>th_up)
        up=TRUE;

    double changes=0;
    int i=0;
    for (i=0; i<size; i++){
        if(up==FALSE && signal[i]>th_up){
            //Cambio de tendencia
            changes++;
            up=TRUE;
        }else if(up==TRUE && signal[i]<th_on){
            up=FALSE;
        }
    }
    double period = 1.0 / (changes/seg_observacion);
    return period;
}

/***
Save an array into a file
***/
void array_to_file(double * array, int size, char * filename_date, char * tittle){
    FILE * f;
    char filename[100];
    sprintf(filename, "%s_%s.txt", filename_date, tittle);
    f = fopen(filename, "w");
    int i;

    for(i=0; i<size; i++){
        fprintf(f, "%f\n", array[i]);
    }

    fflush(f);
    fclose(f);
    sleep(1);
    return;
}
