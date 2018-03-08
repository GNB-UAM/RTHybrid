#include "clamp/includes/xml_clamp_parser.h"

int main () {
	clamp_args args;
	char file[] = "xml/clamp_args_1.xml";

	xml_clamp_parser(file, &args);


	printf("Model = %d\n", args.model);

	switch (args.model) {
		case IZ:
			printf("A = %f\n", args.params[IZ_A]);
			printf("B = %f\n", args.params[IZ_B]);
			printf("C = %f\n", args.params[IZ_C]);
			printf("D = %f\n", args.params[IZ_D]);
			printf("I = %f\n", args.params[IZ_I]);
			printf("X = %f\n", args.vars[X]);
			printf("Y = %f\n", args.vars[Y]);

			break;
		case HR:
			printf("R = %f\n", args.params[HR_R]);
			printf("S = %f\n", args.params[HR_S]);
			printf("I = %f\n", args.params[HR_I]);
			printf("X = %f\n", args.vars[X]);
			printf("Y = %f\n", args.vars[Y]);
			printf("Z = %f\n", args.vars[Z]);

			break;
		case RLK:
			printf("ALPHA = %f\n", args.params[RLK_ALPHA]);
			printf("MU = %f\n", args.params[RLK_MU]);
			printf("SIGMA = %f\n", args.params[RLK_SIGMA]);
			printf("I = %f\n", args.params[RLK_I]);
			printf("X = %f\n", args.vars[X]);
			printf("Y = %f\n", args.vars[Y]);

			break;
		default:
			break;
	}
	

	printf("\nSynapse = %d\n", args.synapse);

	switch (args.synapse) {
		case ELECTRIC:
		{
			printf("G_V_R = %f\n", args.g_virtual_to_real[0]);
			printf("G_R_V = %f\n", args.g_real_to_virtual[0]);

			break;
		}
		case GOLOWASCH:
		{
		    syn_gl_args * args_live_to_model_gl = (syn_gl_args *) args.syn_args_live_to_model;
            syn_gl_args * args_model_to_live_gl = (syn_gl_args *) args.syn_args_model_to_live;

			printf("G_to_model_S = %f\n", args_live_to_model_gl->g[GL_G_SLOW]);
			printf("G_to_model_F = %f\n", args_live_to_model_gl->g[GL_G_FAST]);

			printf("G_to_living_S = %f\n", args_model_to_live_gl->g[GL_G_SLOW]);
			printf("G_to_living_F = %f\n", args_model_to_live_gl->g[GL_G_FAST]);

			break;
		}
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
	printf("Freq %.0f   Important %d   Calibration %d\n", args.freq, args.imp, args.mode_auto_cal);

	printf("\nINPUT: %s  OUTPUT: %s\n", args.input, args.output);


	free(args.vars);
	free(args.params);
	/*free(args.g_real_to_virtual);
	free(args.g_virtual_to_real);*/
	free(args.input);
	free(args.output);

	return 1;
}