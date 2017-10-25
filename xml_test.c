#include "clamp/includes/xml_clamp_parser.h"

int main () {
	clamp_args args;
	char file[] = "xml/clamp_args_2.xml";

	xml_clamp_parser(file, &args);


	printf("Model = %d\n", args.model);

	switch (args.model) {
		case IZHIKEVICH:
			printf("A = %f\n", args.params[A_IZ]);
			printf("B = %f\n", args.params[B_IZ]);
			printf("C = %f\n", args.params[C_IZ]);
			printf("D = %f\n", args.params[D_IZ]);
			printf("I = %f\n", args.params[I_IZ]);
			printf("X = %f\n", args.vars[X]);
			printf("Y = %f\n", args.vars[Y]);

			break;
		case HR:
			printf("R = %f\n", args.params[R_HR]);
			printf("S = %f\n", args.params[S_HR]);
			printf("I = %f\n", args.params[I_HR]);
			printf("X = %f\n", args.vars[X]);
			printf("Y = %f\n", args.vars[Y]);
			printf("Z = %f\n", args.vars[Z]);

			break;
		case RLK:
			printf("ALPHA = %f\n", args.params[ALPHA_RLK]);
			printf("MU = %f\n", args.params[MU_RLK]);
			printf("SIGMA = %f\n", args.params[SIGMA_RLK]);
			printf("I = %f\n", args.params[I_RLK]);
			printf("X = %f\n", args.vars[X]);
			printf("Y = %f\n", args.vars[Y]);

			break;
		default:
			break;
	}
	

	printf("\nSynapse = %d\n", args.synapse);

	switch (args.synapse) {
		case ELECTRIC:
			printf("G_V_R = %f\n", args.g_virtual_to_real[0]);
			printf("G_R_V = %f\n", args.g_real_to_virtual[0]);

			break;
		case CHEMICAL:
			printf("G_V_R_S = %f\n", args.g_virtual_to_real[G_SLOW]);
			printf("G_V_R_F = %f\n", args.g_virtual_to_real[G_FAST]);
			printf("G_R_V_S = %f\n", args.g_real_to_virtual[G_SLOW]);
			printf("G_R_V_F = %f\n", args.g_real_to_virtual[G_FAST]);

			break;
		default:
			break;
	}


	switch (args.mode_auto_cal) {
		case 1:
			printf("Electric conductance MSE.\n");
			break;
		case 7:
			printf("Gradual Map.  Step V to R: %f   Step R to V: %f\n", args.step_v_to_r, args.step_r_to_v);
			break;
		default:
			break;
	}



	printf("\nTIMES: Before %d  Duration %d  After %d\n", args.before, args.time_var, args.after);
	printf("Freq %.0f   Antiphase %d   Important %d   Calibration %d\n", args.freq, args.anti, args.imp, args.mode_auto_cal);

	printf("\nINPUT: %s  OUTPUT: %s\n", args.input, args.output);


	free(args.vars);
	free(args.params);
	free(args.g_real_to_virtual);
	free(args.g_virtual_to_real);
	free(args.input);
	free(args.output);

	return 1;
}