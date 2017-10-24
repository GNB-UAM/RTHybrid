#include "clamp/includes/xml_clamp_parser.h"

int main () {
	clamp_args args;
	char file[] = "clamp_args.xml";

	xml_clamp_parser(file, &args);


	printf("Model = %d\n", args.model);
	printf("A = %f\n", args.params[A_IZ]);
	printf("B = %f\n", args.params[B_IZ]);
	printf("C = %f\n", args.params[C_IZ]);
	printf("D = %f\n", args.params[D_IZ]);
	printf("I = %f\n", args.params[I_IZ]);
	printf("X = %f\n", args.vars[X]);
	printf("Y = %f\n", args.vars[Y]);

	free(args.vars);
	free(args.params);

	return 1;
}