#include "../includes/calibrate_functions_phase2.h"

/**********************************************
*
*		SCORE OF THE CALIBRATION
*
**********************************************/

//Futuro: no variables globales 
//        conseguir "orientacion a objetos" por medio de una struct que se pasa siempre

/*
* Args:
*         v_a and v_b must be in the same scale
*
* Return: 
*         -1 ERR
*          0 OK, no ecm result yet
*          1 OK, ecm result ready
*/

int count_a_calc_ecm = 0; 
double ecm_calc_ecm =0;

int calc_ecm (double v_a, double v_b, int life_burst_points, double *ecm_result){
	int num_burst = 3;
	double diff = 0;

	if(count_a_calc_ecm < life_burst_points*num_burst){
		count_a_calc_ecm++;
		diff = (v_a-v_b);
		ecm_calc_ecm += diff * diff;
		return 0;
	}else{
		ecm_calc_ecm = ecm_calc_ecm / count_a_calc_ecm;
		count_a_calc_ecm=0;
		//ecm_calc_ecm = ecm_calc_ecm / life_burst_points * num_burst;
		*ecm_result = ecm_calc_ecm;
		ecm_calc_ecm = 0;
		return 1;
	}
}

/*
*/
double old_res_calc_phase = -1;

int calc_phase (double * v_a, double * v_b, double * t, int size, double th_up, double th_on, double * result, int antifase){

	double limit = 3; //ns

	if (antifase==1){
		limit=50;
	}else{
		limit=3;
	}

	int up_a=FALSE, up_b=FALSE;
	int size_res = 50;
	double res_a[50] = {0};
	double res_b[50] = {0};
	double res[50] = {0};
	int count_a=0, count_b=0, i=0;
	if(v_a[0]>th_up)
		up_a=TRUE;
	if(v_b[0]>th_up)
		up_b=TRUE;

	//FILE * ff;
	//ff = fopen("cosa", "w");

	for(i=0; i<size; i++){
		//A
		//fprintf(ff, "%d %f %f", i, v_a[i], v_b[i]);
		if (up_a==FALSE && v_a[i]>th_up){
			up_a=TRUE;
			//Apuntamos tiempo de disparo
			res_a[count_a]=t[i];
			count_a++;
			//fprintf(ff, " 1");
		}else if (up_a==TRUE && v_a[i]<th_on){
			up_a=FALSE;
			//fprintf(ff, " 0");
		}else {
			//fprintf(ff, " 0");
		}

		//B
		if (up_b==FALSE && v_b[i]>th_up){
			up_b=TRUE;
			//Apuntamos tiempo de disparo
			res_b[count_b]=t[i];
			count_b++;
			//fprintf(ff, " 1\n");
		}else if (up_b==TRUE && v_b[i]<th_on){
			up_b=FALSE;
			//fprintf(ff, " 0\n");
		}else{
			//fprintf(ff, " 0\n");
		}
	}
	//fclose(ff);

	//res a y b incluyen los tiempos de disparo
	/*double a = fabs(res_a[0] - res_b[0]);
	double b = fabs(res_a[1] - res_b[0]);
	double c = fabs(res_a[0] - res_b[1]);
	int salto_a=0;
	
	if (b<a && b<c){
		salto_a=1;
	}else if(c<a && c<b){
		salto_b=1;
	}*/
	int salto_b=0;
	if(res_a[1]-res_b[0]<0){
		//estan al reves
		salto_b=1;
	}

	int count=0;
	for(i=0; i<size_res; i++){
		if (res_a[i]==0  || res_b[i]==0){
			break;
		}
		res[i] = fabs(res_a[i] - res_b[i+salto_b]);
		count++;
	}

	//Calculamos varianza
	double media = 0;
	for(i=0; i<count; i++){
		media+=res[i];
	}
	media = media / count;

	double var=0, tmp=0;

	for(i=0; i<count; i++){
		tmp = res[i] - media;
		var += tmp*tmp;
	}

	if ( old_res_calc_phase !=-1){
		if ( old_res_calc_phase<200 && fabs(old_res_calc_phase-var)>100){
			//Se empezo a medir cortando una rafaga
			return ERR;
		}
	}

	var = var / count;

	*result = var;

	old_res_calc_phase = var;

	/***SINCRO***/
	if (var<limit){
		return TRUE;
	}else{
		return FALSE;
	}
}

/**********************************************
*
*			SYNCHRONIZATION
*
**********************************************/

double first_val_is_syn_by_percentage = -1;
int count_is_syn_by_percentage = 0; 

void set_is_syn_by_percentage(double val_sin, double percentage){
	printf("ECM_inicial = %f\n", val_sin);
	first_val_is_syn_by_percentage = val_sin;
    printf("ECM_objetivo = %f\n", val_sin*percentage/100);
	count_is_syn_by_percentage = 0;
}

int is_syn_by_percentage(double val_sin, double percentage){
	printf("%f\n", val_sin);
	int times_correct = 2;
	
	/*FIRST TIME*/
	if (first_val_is_syn_by_percentage == -1){
		return ERR;
	}
    /*PERCENTAGE REACHED*/
	else if( (first_val_is_syn_by_percentage*percentage/100) > val_sin){
		/*ENOUGH CONSECUTIVE TIMES*/
		if(count_is_syn_by_percentage<times_correct){
			count_is_syn_by_percentage++;
			return FALSE;
		}else{
			return TRUE;
		}
	/*NO YET*/
	}else{
		count_is_syn_by_percentage = 0;
		return FALSE;
	}
}

/*
*/

double last_val_sin_is_syn_by_slope_1 = -1;
double last_val_sin_is_syn_by_slope_2 = -1;

int is_syn_by_slope(double val_sin){
	printf("HOLA\n");
	double tolerance = 2.5;

	/*FIRST TIME*/
	if (last_val_sin_is_syn_by_slope_1 == -1){
		last_val_sin_is_syn_by_slope_1 = val_sin;
		return ERR;
	} else if(last_val_sin_is_syn_by_slope_2 == -1){
		last_val_sin_is_syn_by_slope_2 = val_sin;
		return ERR;
	}
	/*SLOPE*/
	double slope_1 = last_val_sin_is_syn_by_slope_2 - last_val_sin_is_syn_by_slope_1;
	double slope_2 = val_sin - last_val_sin_is_syn_by_slope_2;
	last_val_sin_is_syn_by_slope_2 = last_val_sin_is_syn_by_slope_1;
	last_val_sin_is_syn_by_slope_1 = val_sin;

	/*SLOPE IS THE SAME??*/
	double diff = fabs(slope_2-slope_1);
	//printf("d = %f\n", diff);
	if (diff<=tolerance){
		return TRUE;
	}else{
		return FALSE;
	}
}

/*
*/

double vals_is_syn_by_variance[4] = {-1};
int num_variances_is_syn_by_variance = 4;
int count_is_syn_by_variance = 0;

int is_syn_by_variance(double val_sin){
	double tolerance = 4;

	vals_is_syn_by_variance[count_is_syn_by_variance % num_variances_is_syn_by_variance] = val_sin;
	count_is_syn_by_variance++;

	int i;
	double media=0;
	for (i=0; i<num_variances_is_syn_by_variance; i++){
		if (vals_is_syn_by_variance[i] == -1){
			return FALSE;
		}
		media += vals_is_syn_by_variance[i];
	}
	media = media / num_variances_is_syn_by_variance;

    double res = 0;
    double tmp;
	for (i=0; i<num_variances_is_syn_by_variance; i++){
		tmp = vals_is_syn_by_variance[i] - media;
		res += tmp * tmp;
	}
	res = res / num_variances_is_syn_by_variance;
	printf("var = %f\n", res);

	if (res<=tolerance){
		return TRUE;
	}else{
		return FALSE;
	}
}

/**********************************************
*
*			CHANGE PARAMETERS
*
**********************************************/

void change_g (double *g){
	*g+=0.05;
	return;
}



