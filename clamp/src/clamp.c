#include "clamp/includes/clamp.h"


/* Global variables */
void * msqid = NULL;
pthread_t writer, rt;

void clamp_cleanup () {

	if (pthread_kill(writer, SIGUSR2) != 0) perror("Error sending SIGUSR2 at main");
	if (pthread_kill(rt, SIGUSR1) != 0) perror("Error sending SIGUSR1 at main");
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



int clamp (double freq, int time_var, int model, int synapse, int mode_auto_cal, int anti, int imp, char * input, char * output, double * vars, double * params, double * g_virtual_to_real, double * g_real_to_virtual, double step_v_to_r, double step_r_to_v) {
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

    /*int model = 0;
	int synapse = 0;
	double freq = 10000.0;
	int time_var = 0;*/
    int ret = 0;
	//int mode_auto_cal = 0;
	int c_a = FALSE;

	sigset_t set;

	r_args.n_in_chan = 0;
	r_args.n_out_chan = 0;
	r_args.in_channels = NULL;
	r_args.out_channels = NULL;
    r_args.g_real_to_virtual = g_real_to_virtual;
    r_args.g_virtual_to_real = g_virtual_to_real;
	r_args.anti=-1;
	w_args.anti=-1;
	w_args.important = imp;

	parse_channels(input, &(r_args.in_channels), &(r_args.n_in_chan));

	parse_channels(output, &(r_args.out_channels), &(r_args.n_out_chan));

	if (anti == 1) {
		r_args.anti=1;
		w_args.anti=1;
	}


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
    }else if(mode_auto_cal == 7){
		model=2;
		r_args.anti=-1;
		w_args.anti=-1;
        r_args.step_v_to_r=step_v_to_r;
        r_args.step_r_to_v=step_r_to_v;
    }else if(mode_auto_cal == 8){
        model=2;
        r_args.anti=-1;
        w_args.anti=-1;
    }

	if(!c_a){
		c_a=TRUE;
	}else{
		printf("DON'T USE -a AND -c AT THE SAME TIME\n");
	}


	r_args.calibration = mode_auto_cal;
	w_args.calibration = mode_auto_cal;

	switch (model){
        case IZHIKEVICH:
			r_args.rafaga_modelo_pts = 59324.0;
			r_args.dt = 0.001;

			r_args.params = params;
			r_args.vars = vars;

			r_args.dim = 2;
			r_args.s_points = 0;
			
			r_args.func = &izhikevich;
			r_args.ini = &ini_iz;

			break;
		case HR:
			r_args.rafaga_modelo_pts = 260166.0;
			r_args.dt = 0.001;

            /*if(mode_auto_cal==6)
                params[R_HR] = 0.0011;*/

			r_args.params = params;
			r_args.vars = vars;

			r_args.dim = 3;
			r_args.s_points = 0;

			r_args.func = &hindmarsh_rose;
			r_args.ini = &ini_hr;

			break;
		case RLK:
			r_args.rafaga_modelo_pts = freq;
			r_args.dt = 0.003;

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


    t = time(NULL);
	tm = *localtime(&t);
	sprintf(path, "data/%dy_%dm_%dd", tm.tm_year + 1900, tm.tm_mon + 1, tm.tm_mday);
	sprintf(path_b, "data/%dy_%dm_%dd", tm.tm_year + 1900, tm.tm_mon + 1, tm.tm_mday);

	filename[0] = '\0';
	strcat(filename, path);


	struct stat st = {0};

    if (stat("data", &st) == -1) {
        mkdir("data", 0777);
    }

    if (stat(path, &st) == -1) {
		mkdir(path, 0777);
	}

	sprintf(hour, "/%dh_%dm_%ds", tm.tm_hour, tm.tm_min, tm.tm_sec);
	strcat(filename, hour);  

    syslog(LOG_INFO, " - File: %s%s", filename, "_1.txt");


    pthread_attr_init(&attr_rt);
    pthread_attr_init(&attr_wr);
    pthread_attr_setdetachstate(&attr_rt, PTHREAD_CREATE_JOINABLE);
    pthread_attr_setdetachstate(&attr_wr, PTHREAD_CREATE_JOINABLE);

    sigemptyset(&set);
    sigaddset(&set, SIGINT);
    if (pthread_sigmask(SIG_BLOCK, &set, NULL) != 0) syslog(LOG_INFO, "Error blocking SIGINT at main.\n");

    if (open_queue(&msqid) != OK) {
        syslog(LOG_INFO, "Error opening queue.");
    	return ERR;
    }

    syslog(LOG_INFO, "CLAMP: Queue opened");

    r_args.msqid = msqid;
    r_args.points = time_var * freq;
    r_args.period =  (1 / freq) * NSEC_PER_SEC;
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
        syslog(LOG_INFO, "Can't create thread :[%s]", strerror(err));

    err = pthread_create(&(rt), &attr_rt, &rt_thread, (void *) &r_args);
    if (err != 0)
        syslog(LOG_INFO, "Can't create thread :[%s]", strerror(err));

    syslog(LOG_INFO, "CLAMP: Threads created");

    if (pthread_sigmask(SIG_UNBLOCK, &set, NULL) != 0) syslog(LOG_INFO, "Error unblocking SIGINT at main.\n");
    if (signal(SIGINT, clamp_cleanup) == SIG_ERR) syslog(LOG_INFO, "Error catching SIGINT at main.\n");

    syslog(LOG_INFO, "CLAMP: Signals set");


    pthread_join(writer, NULL);
    pthread_join(rt, NULL);
    

    if (msqid != NULL) {
        if (close_queue(&msqid) != OK) syslog(LOG_INFO, "Error closing queue.\n");
    }

    /*free(vars);
    free(params);*/

    syslog(LOG_INFO, PRINT_YELLOW "CLAMP: clamp_cli finished." PRINT_RESET "\n");
	return 1;
}
