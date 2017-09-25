#include "../includes/calibrate_functions_phase2_a.h"

double res_phase = 0;
int cal_on = TRUE;
int aux_counter = 0;

int auto_calibration(
					rt_args * args,
					calibration_args * cs,
					double * ret_values,
					double rafaga_viva_pts,
					double * ecm_result,
					message * msg,
					double * g_virtual_to_real,
					double * g_real_to_virtual,
                    double * lectura_a,
                    double * lectura_b,
                    double * lectura_t,
                    int size_lectura,
                    int cont_send,
                    double * syn_aux_params,
                    double ini_k1,
                    double ini_k2
					){

	if(args->calibration==1 || args->calibration==2 || args->calibration==3){
		
        //Electrica en fase - ecm
		int ret_ecm = calc_ecm(args->vars[0] * cs->scale_virtual_to_real + cs->offset_virtual_to_real, ret_values[0], rafaga_viva_pts, ecm_result);
        msg->ecm = *ecm_result;

        if(cal_on && ret_ecm==1){
        	int is_syn;
            if (args->calibration == 1){
                //Porcentaje
                is_syn = is_syn_by_percentage(*ecm_result);
            }else if (args->calibration == 2){
                //Pendiente
                is_syn = is_syn_by_slope(*ecm_result);
            }else if (args->calibration == 3){
                //Var
                is_syn = is_syn_by_variance(*ecm_result);
            }

            if (is_syn==TRUE){
                printf("CALIBRATION END: g=%f\n", g_virtual_to_real[0]);
                cal_on=FALSE;
            }else if(is_syn==FALSE && cal_on==TRUE){
                //printf("%f\n", g_virtual_to_real[0]);
                change_g(&g_virtual_to_real[0]);
                change_g(&g_real_to_virtual[0]);
            }
        }

	}else if (args->calibration==4){

        /***** REVISAR *******/
        //Electrica y var
        if(aux_counter<size_lectura){
            /*Guardamos info*/
            lectura_b[aux_counter]=args->vars[0] * cs->scale_virtual_to_real + cs->offset_virtual_to_real;
            lectura_a[aux_counter]=ret_values[0];
            lectura_t[aux_counter]=msg->t_absol;
            msg->ecm = res_phase;
            aux_counter++;
        }else{
            /*Ejecuta metrica*/
            int is_syn = calc_phase (lectura_b, lectura_a, lectura_t, size_lectura, cs->max_real_relativo, cs->min_real, &res_phase, args->anti);
            msg->ecm = res_phase;

            printf("var = %f\n", msg->ecm);
            if(cal_on){
                if (is_syn==TRUE){
                    printf("CALIBRATION END: g=%f\n", g_virtual_to_real[0]);
                    cal_on=FALSE;
                }else if (is_syn==FALSE){
                    change_g(&g_virtual_to_real[0]);
                    change_g(&g_real_to_virtual[0]);
                } 
            }
            aux_counter=0;
        }

    }else if(args->calibration==6){
        aux_counter++;
        if(aux_counter == 10000*3){
            args->params[R_HR]+=0.0006;
            printf("%f\n", args->params[R_HR]);
            aux_counter=0;
        }
        int ret_ecm = calc_ecm(args->vars[0] * cs->scale_virtual_to_real + cs->offset_virtual_to_real, ret_values[0], rafaga_viva_pts, ecm_result);
        msg->ecm = *ecm_result;
        msg->extra = args->params[R_HR];
        
    }else if(args->calibration==7){
        if (cal_on==TRUE){
            double paso_fast = 0.2;//0.2; //0.3
            double max_fast = 1.8;//1.8; //2.7
            double paso_slow = 0.01;
            double max_slow = 0.11;

            //Mapa de conductancia 
            aux_counter++;
            if (aux_counter>=10000*10){ //Cada 10s hay cambio
                aux_counter=0;
                g_virtual_to_real[G_SLOW] += paso_slow;
                if (g_virtual_to_real[G_SLOW]>max_slow){
                    g_virtual_to_real[G_SLOW] = 0;
                    g_real_to_virtual[G_FAST] += paso_fast;
                    if(g_real_to_virtual[G_FAST]>=max_fast){
                        printf("FIN\n");
                        printf("Apuntar: %d\n", cont_send);
                        g_virtual_to_real[G_SLOW] = 0;
                        g_real_to_virtual[G_FAST] = 0;
                        cal_on=FALSE;
                    }
                }
            }
        }

    }else if(args->calibration==8){
                if (cal_on==TRUE){
                    /*Los ini se cambian en rt thread*/
                    double paso_k1 = 0.3;
                    double paso_k2 = 0.02;
                    double max_k1 = 1.6;
                    double max_k2 = 0.1;

                    //Mapa de k 
                    aux_counter++;
                    if (aux_counter>=10000*10){ //Cada 10s hay cambio
                        aux_counter=0;
                        syn_aux_params[SC_MS_K1]+=paso_k1;
                        if(syn_aux_params[SC_MS_K1]>=max_k1){
                            syn_aux_params[SC_MS_K1]=ini_k1;
                            syn_aux_params[SC_MS_K2]+=paso_k2;
                            if( syn_aux_params[SC_MS_K2]>=max_k2){
                                printf("FIN\n");
                                printf("Apuntar: %d\n", cont_send);
                                syn_aux_params[SC_MS_K1]=0;
                                syn_aux_params[SC_MS_K2]=0;
                                cal_on=FALSE;
                            }
                        }
                    }
                }
                msg->ecm=syn_aux_params[SC_MS_K1];
                msg->extra=syn_aux_params[SC_MS_K2];

            }

}