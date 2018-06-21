#include "../includes/calibrate_functions_phase1.h"

int ini_recibido (double *min_rel_real, double *min_abs_real, double *max_abs_real, double *max_rel_real, double *period_signal, Daq_session * session, int chan, int period, int freq, char* filename, double input_factor){
    
    /*TIEMPO OBSERVACION*/
    int segs_observo = 10; 

    /*VARIABLES CALCULO DE RANGOS*/
    int i=0;
    double retval=0.0, valor_old=0.0, resta=0.0, pendiente_max=-999999;
    struct timespec ts_target, ts_iter, ts_result, ts_start;
    double maxi=-999999;
    double mini=999999;
    double miniB=999999;

    /*DAQ*/
    int n_channels = 1;
    int in_channels [1];
    double ret_values [1];
    in_channels[0] = chan;

    /*RT*/
    clock_gettime(CLOCK_MONOTONIC, &ts_target);
    ts_assign (&ts_start,  ts_target);
    ts_add_time(&ts_target, 0, period);

    /*DECLARACIONES DE ARRAYS Y SUS TAMAÑOS*/
    int size_lectura = freq*segs_observo;
    double * lectura = (double*) malloc(sizeof(double) * size_lectura);
    double * convolution = (double*) malloc(sizeof(double) * size_lectura);
    int size_media = size_lectura / 10;
    double * media = (double*) malloc(sizeof(double) * size_lectura);


    for (i=0; i<freq*(segs_observo); i++){

    	/*LECTURA DE DATOS*/
        clock_nanosleep(CLOCK_MONOTONIC, TIMER_ABSTIME, &ts_target, NULL);
        if (daq_read(session, n_channels, in_channels, ret_values) != 0) {
            return -1;
        }
        retval = (ret_values[0] * 1000.0) / input_factor;
        lectura[i] = retval;
        
        /*COMPROBAR DATOS*/
        if(retval>maxi){
            maxi=retval;
        }else if(retval<mini){
            mini=retval;
        }
        
        if(i>2){
            resta=retval-valor_old;
            if(resta>pendiente_max){
                pendiente_max=resta;
                miniB=valor_old;
            }
        }
        
        if(i%10==0)
            valor_old=retval;

        ts_add_time(&ts_target, 0, period); 
    }


    /*RETURN*/
    *min_abs_real = mini;
    *max_abs_real = maxi;

    double porcentaje_mini = 0.10;
    double porcentaje_maxi = 0.10;

    //printf("min_abs_real= %f\n", min_abs_real_aux);
    //printf("MAX_ABS= %f\n", max_abs_real_aux);

    if(mini>0){
        *min_rel_real = mini + mini*porcentaje_mini;
    }else{
        *min_rel_real = mini - mini*porcentaje_mini;
    }

    if(maxi>0){
        *max_rel_real = maxi - maxi*porcentaje_maxi;
    }else{
        *max_rel_real = maxi + maxi*porcentaje_maxi;
    }

    //printf("MIN_RE= %f\n", *min);
    //printf("MAX_RE= %f\n", *max_rel_real);

    /*GUARDAR DATOS LEIDOS*/

    /*PERIODO DE LA SEÑAL*/
    signal_convolution (lectura, size_lectura, convolution, size_lectura);
    signal_average (lectura, size_lectura, media, size_media);
    *period_signal = signal_period_2 (segs_observo, lectura, size_lectura, *max_rel_real, *min_rel_real);
    //printf("Perido signal = %f\n", *period_signal);
    //array_to_file(lectura, size_lectura, filename, "lectura_ini");
    //array_to_file(convolution, size_lectura, filename, "lectura_ini_filtro");

    //printf("PERIODO= %f\n", *period_signal);

    return OK;
}

int signal_convolution (double * lectura, int size_l, double * result, int size_r){
	if(size_l!=size_r)
		return ERR;
	int i;
	for (i=0; i<size_l; i++){
	  if(i>3){
        result[i]= 0.2*lectura[i]  + 0.2*lectura[i-1] + 0.2*lectura[i-2] + 0.2*lectura[i-3] + 0.2*lectura[i-4];
      }else{
        result[i]=lectura[i];
      }
	}
	return OK;
}

int signal_average(double * lectura, int size_l, double * result, int size_r){
	if (size_r>=size_l)
		return ERR;
	int saltar = size_l / size_r;
	int i, j;
	for (i=0, j=0; i<size_l; i++, j++){
		int counter = i+saltar;
		double sum = 0.0;
		for(; i<counter; i++){
			sum += lectura[i];
		}
		sum = sum / saltar;
		result[j] = sum;

	}
	return OK;
}

double signal_period_1(int seg_observacion, double * signal, int size, double th_up, double th_on){
    printf("up = %f // on = %f\n", th_up, th_on);
	int up=FALSE;
	if (signal[0]>th_on)
		up=TRUE;

	int changes=0, i=0;
	for (i=0; i<size; i++){
		if(up==TRUE && signal[i]<th_on){
			//Cambio de tendencia
			changes++;
			up=FALSE;
		}else if(up==FALSE && signal[i]>th_on){
			up=TRUE;
		}
	}
	double period = 1.0 / (changes/seg_observacion);
	return period;
}

double signal_period_2(int seg_observacion, double * signal, int size, double th_up, double th_on){
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
    //printf("CHANGES = %f\n", changes);
    double period = 1.0 / (changes/seg_observacion);
    return period;
}

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