#include "../includes/rt_thread_functions.h"
#include "../includes/writer_thread_functions.h"


/* Global variables */
double * params = NULL;
double * vars = NULL;
void * msqid = NULL;
pthread_t writer, rt;

void clamp_cli_cleanup () {

	if (pthread_kill(writer, SIGUSR2) != 0) perror("Error sending SIGUSR2 at main");
	if (pthread_kill(rt, SIGUSR1) != 0) perror("Error sending SIGUSR1 at main");

	/*pthread_join(writer, NULL);
    pthread_join(rt, NULL);
    
    if (msqid != NULL) {
    	if (close_queue(&msqid) != OK) printf("Error closing queue.\n");
    }
    

    free_pointers(2, &vars, &params);*/

    return 1;
}


struct option main_opts[] = {
	{"frequency", required_argument, NULL, 'f'},
	{"time", required_argument, NULL, 't'},
	{"model", required_argument, NULL, 'm'},
	{"synapse", required_argument, NULL, 's'},
	{"calibration", required_argument, NULL, 'c'},
	{"antiphase", required_argument, NULL, 'a'},
	{"Important", required_argument, NULL, 'I'},
	{"input_channels", required_argument, NULL, 'i'},
	{"output_channels", required_argument, NULL, 'o'},
	{"help", no_argument, NULL, 'h'},
	{0},
};

void do_print_usage ()
{
	printf("usage:\tmain [OPTS]\n");
	printf("\tOPTS:\t -f, --frequency: sample frequency (in KHz)\n");
	printf("\t\t -t, --time: simulation time (in s)\n");
	printf("\t\t -m, --model: neural model (0 = Izhikevich, 1 = Hindmarsh-Rose, 2 = Rulkov Map)\n");
	printf("\t\t -s, --synapse: synapse type (0 = electrical, 1 = gradual)\n");
	printf("\t\t -a, --antiphase: turn on antiphase\n");
	printf("\t\t -c, --calibration: automatic calibration process\n\t\t\t - Don't use with antiphase\n\t\t\t - Synapse will be ignored\n \t\t\t - Codes in Readme or github\n");
	printf("\t\t -I, --Important: mark experiment in summary.txt\n");
	printf("\t\t -i, --input_channels: input channels, separated by commas (ej: 0,2,3,7)\n");
	printf("\t\t -o, --output_channels: output channels, separated by commas (ej: 0,2,3,7)\n");
	printf("\t\t -h, --help: print this help\n");
}

void parse_channels (char * str, int ** channels, int * n_chan) {
	int n_chan_aux = 0;
	int chan_aux[32];
	char * token = NULL;
	int i;

	token = strtok(str, ",");
	

	while (token != NULL) {
		chan_aux[n_chan_aux] = atoi(token);
		n_chan_aux++;

		token = strtok(NULL, ",");
	}

	*channels = (int *) malloc (sizeof(int) * n_chan_aux);
	*n_chan = n_chan_aux;

	for (i = 0; i < n_chan_aux; i++) {
		(*channels)[i] = chan_aux[i];
	}

	return;
}


int main (int argc, char * argv[]) {
	key_t key_q;
	pthread_attr_t attr_rt, attr_wr;
	int err;
	FILE * f;

	time_t t;
	struct tm tm;
	char path [19];
	char path_b [19];
	char hour [13];
	char filename [23];


	writer_args w_args;
	rt_args r_args;

	double rafaga_modelo_pts_hr;
	double rafaga_modelo_pts_iz;
    double pts_por_s;
    double t_rafaga_viva_s;
    double rafaga_viva_pts;

    int model = 0;
	int synapse = 0;
	double freq = 10000.0;
	int time_var = 0;
	int ret = 0;
	int mode_auto_cal = 0;
	int c_a = FALSE;

	sigset_t set;

	r_args.n_in_chan = 0;
	r_args.n_out_chan = 0;
	r_args.in_channels = NULL;
	r_args.out_channels = NULL;
	r_args.anti=-1;
	w_args.anti=-1;
	w_args.important=0;


    while ((ret = getopt_long(argc, argv, "I:f:t:m:s:i:o:c:a:h", main_opts, NULL)) >= 0) {
		switch (ret) {
		case 'I':
			w_args.important = atoi(optarg);
			break;
		case 'f':
			freq = atof(optarg) * 1000;
			break;
		case 't':
			time_var = atoi(optarg);
			break;
		case 'm':
			model = atoi(optarg);
			break;
		case 's':
			synapse = atoi(optarg);
			break;
		case 'i':
			parse_channels(optarg, &(r_args.in_channels), &(r_args.n_in_chan));
			break;
		case 'o':
			parse_channels(optarg, &(r_args.out_channels), &(r_args.n_out_chan));
			break;
		case 'a':
			if (atoi(optarg) == 1) {
				r_args.anti=1;
				w_args.anti=1;
			}
			
			if(!c_a){
				c_a=TRUE;
			}else{
				printf("DON'T USE -a AND -c AT THE SAME TIME\n");
			}
			break;
		case 'c':
			mode_auto_cal = atoi(optarg);

			if (mode_auto_cal == 1){
				//Electrica en fase - ecm y %
				synapse=0;
				r_args.anti=-1;
				w_args.anti=-1;
			}else if(mode_auto_cal == 2){
				//Electrica en fase - ecm y slope
				synapse=0;
				r_args.anti=-1;
				w_args.anti=-1;
			}else if(mode_auto_cal == 3){
				//Electrica en fase - ecm y var
				synapse=0;
				r_args.anti=-1;
				w_args.anti=-1;
			}else if(mode_auto_cal == 4){
				//Electrica en fase - fase y var
				synapse=0;
				r_args.anti=-1;
				w_args.anti=-1;
			}else if(mode_auto_cal == 5){
				//Electrica en anti - fase y var
				synapse=0;
				r_args.anti=1;
				w_args.anti=1;
				mode_auto_cal = 4;
			}else if(mode_auto_cal == 6){
				//variar mu de hr
				model=1;
				r_args.anti=-1;
				w_args.anti=-1;
			}else if(mode_auto_cal == 7 || mode_auto_cal == 8){
				model=2;
				r_args.anti=-1;
				w_args.anti=-1;
			}

			if(!c_a){
				c_a=TRUE;
			}else{
				printf("DON'T USE -a AND -c AT THE SAME TIME\n");
			}
			break;
		case 'h':
		default:
			do_print_usage();
			return 0;
		}
	}

	r_args.calibration = mode_auto_cal;
	w_args.calibration = mode_auto_cal;

	switch (model){
		case IZHIKEVICH:
			vars = (double*) malloc (sizeof(double) * 2);
			params = (double*) malloc (sizeof(double) * 5);

			r_args.rafaga_modelo_pts = 59324.0;
			r_args.dt = 0.001;

			params[I_IZ] = 10.0;
			params[A_IZ] = 0.02;
			params[B_IZ] = 0.2;
			params[C_IZ] = -50.0;
			params[D_IZ] = 2.0;

			r_args.params = params;
			r_args.vars = vars;

			r_args.dim = 2;
			r_args.s_points = 0;
			
			r_args.func = &izhikevich;
			r_args.ini = &ini_iz;

			break;
		case HR:
			vars = (double*) malloc (sizeof(double) * 3);
			params = (double*) malloc (sizeof(double) * 3);

			r_args.rafaga_modelo_pts = 260166.0;
			r_args.dt = 0.001;

			params[I_HR] = 3.0;
			params[R_HR] = 0.0021;
			if(mode_auto_cal==6)
				params[R_HR] = 0.0011;
			params[S_HR] = 4.0;

			r_args.params = params;
			r_args.vars = vars;

			r_args.dim = 3;
			r_args.s_points = 0;

			r_args.func = &hindmarsh_rose;
			r_args.ini = &ini_hr;

			break;
		case RLK:
			vars = (double*) malloc (sizeof(double) * 2);
			params = (double*) malloc (sizeof(double) * 8);

			r_args.rafaga_modelo_pts = freq;
			r_args.dt = 0.003;

			params[I_RLK] = 1.0;
			params[ALPHA_RLK] = 6.0;
			params[SIGMA_RLK] = 0.1;
			params[MU_RLK] = 0.001;
			params[OLD_RLK] = 0.0;
			params[PTS_RLK] = freq;
			params[J_RLK] = ((params[PTS_RLK] - 400) / 400) + 1;
			params[INTER_RLK] = 0.0;

			r_args.params = params;
			r_args.vars = vars;

			r_args.dim = 2;
			r_args.s_points = 1;
			
			r_args.func = &rulkov_map;
			r_args.ini = &ini_rlk;

			break;
		default:
			return -1;
	}


	switch (synapse) {
		case ELECTRIC:
			r_args.syn = &elec_syn;

			break;
		case CHEMICAL:
			r_args.syn = &chem_syn;

			break;
		default:
			return -1;
	}

	/*Messages queue*/
    /*key_q = ftok ("/bin/ls", 28);
    if (key_q == (key_t) -1) {
        perror("Error obtaining message queue key.");
        exit(EXIT_FAILURE);
    }

    msqid = msgget (key_q, 0600 | IPC_CREAT);
    if (msqid == -1) {
        perror("Error obtaining message queue ID.");
        return(0);
    }*/

    t = time(NULL);
	tm = *localtime(&t);
	sprintf(path, "data/%dy_%dm_%dd", tm.tm_year + 1900, tm.tm_mon + 1, tm.tm_mday);
	sprintf(path_b, "data/%dy_%dm_%dd", tm.tm_year + 1900, tm.tm_mon + 1, tm.tm_mday);

	filename[0] = '\0';
	strcat(filename, path);


	struct stat st = {0};

	if (stat(path, &st) == -1) {
		mkdir(path, 0777);
	}

	sprintf(hour, "/%dh_%dm_%ds", tm.tm_hour, tm.tm_min, tm.tm_sec);
	strcat(filename, hour);  

	printf(" - File:\n%s%s\n", filename, "_1.txt");


    pthread_attr_init(&attr_rt);
    pthread_attr_init(&attr_wr);
    pthread_attr_setdetachstate(&attr_rt, PTHREAD_CREATE_JOINABLE);
    pthread_attr_setdetachstate(&attr_wr, PTHREAD_CREATE_JOINABLE);

    sigemptyset(&set);
    sigaddset(&set, SIGINT);
    if (pthread_sigmask(SIG_BLOCK, &set, NULL) != 0) printf("Error blocking SIGINT at main.\n");

    if (open_queue(&msqid) != OK) {
    	printf("Error opening queue.\n");
    	return ERR;
    }

    r_args.msqid = msqid;
    r_args.points = time_var * freq;
    r_args.period = 1 / freq * NSEC_PER_SEC;
    r_args.type_syn = synapse;
    r_args.freq = freq;
    r_args.filename = filename;
    r_args.model = model;

    w_args.path = path;
    w_args.filename = filename;
    w_args.points = r_args.points;
    w_args.s_points = r_args.s_points;
    w_args.msqid = msqid;
    w_args.type_syn = synapse;
    w_args.model = model;
    w_args.freq = freq;
    w_args.time_var = time_var;

    err = pthread_create(&(writer), &attr_wr, &writer_thread, (void *) &w_args);
    if (err != 0)
        printf("Can't create thread :[%s]", strerror(err));

    err = pthread_create(&(rt), &attr_rt, &rt_thread, (void *) &r_args);
    if (err != 0)
        printf("Can't create thread :[%s]", strerror(err));

    if (pthread_sigmask(SIG_UNBLOCK, &set, NULL) != 0) printf("Error unblocking SIGINT at main.\n");
    if (signal(SIGINT, clamp_cli_cleanup) == SIG_ERR) printf("Error catching SIGINT at main.\n");


    pthread_join(writer, NULL);
    pthread_join(rt, NULL);
    

    if (msqid != NULL) {
    	if (close_queue(&msqid) != OK) printf("Error closing queue.\n");
    }

    free(vars);
    free(params);

    printf(PRINT_YELLOW "\nclamp_cli finished." PRINT_RESET "\n");
	return 1;
}