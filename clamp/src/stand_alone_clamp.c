//#include "../includes/xml_clamp_parser.h"
#include "../includes/clamp.h"



struct option main_opts[] = {
	{"xml", required_argument, NULL, 'x'},
	{"help", no_argument, NULL, 'h'},
	{0},
};

void do_print_usage ()
{
	printf("usage:\tclamp-cli_preempt [OPTS]\n");
	printf("\tOPTS:\t -x, --xml: XML file with the experiment parameters\n");
	printf("\t\t -h, --help: print this help\n");
}



int main (int argc, char * argv[]) {
	clamp_args args;
	int ret = 0;


	while ((ret = getopt_long(argc, argv, "x:h", main_opts, NULL)) >= 0) {
		switch (ret) {
		case 'x':
			printf("%s\n", optarg);
			ret = xml_clamp_parser(optarg, &args);
			/*if (ret != OK) {
				printf("CLAMP: Error reading XML file %s.\n", optarg);
				return -1;
			}*/

			break;
		case 'h':
		default:
			do_print_usage();
			return 0;
		}
	}


	clamp(&args);

	return 1;
}