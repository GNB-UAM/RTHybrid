#include "../includes/clamp.h"

/* Global variables */
void * msqid_rt = NULL, * msqid_nrt = NULL;
pthread_t writer, rt;
rt_args r_args;

void clamp_cleanup () {

    syslog(LOG_INFO, "CLAMP: Ctrl+C");

    if (kill_writer_thread(writer, SIGUSR2) != 0)  syslog(LOG_INFO, "Error sending SIGUSR2 at main");
    if (kill_rt_thread(rt, SIGUSR1) != 0)  syslog(LOG_INFO, "Error sending SIGUSR1 at main");
}

void parse_channels (char * str, int ** channels, unsigned int * n_chan) {
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

int clamp (clamp_args * args) {
	pthread_attr_t attr_rt, attr_wr;

	time_t t;
	struct tm tm;
	char * path = NULL;
	char * hour = NULL;
	char filename[50];
    char * filename_data = NULL;
    char * filename_events = NULL;


	writer_args w_args;


	sigset_t set;

	r_args.n_in_chan = 0;
	r_args.n_out_chan = 0;
	r_args.in_channels = NULL;
	r_args.out_channels = NULL;
    r_args.input_factor = args->input_factor;
    r_args.output_factor = args->output_factor;

	/*Delete queue*/
	//system("rm -rf /dev/mqueue/rt_queue* > /dev/null 2>&1");

	/*Parse channels*/
    if (args->input_channels != NULL) parse_channels(args->input_channels, &(r_args.in_channels), &(r_args.n_in_chan));
    if (args->output_channels != NULL) parse_channels(args->output_channels, &(r_args.out_channels), &(r_args.n_out_chan));


    /*Calchange*/
    if (args->mode_auto_cal == 7){
        r_args.step_v_to_r = args->step_v_to_r;
        r_args.step_r_to_v = args->step_r_to_v;
    }

    init_neuron_model(&(r_args.nm), args->model, args->vars, args->params);
    init_synapse_model(&(r_args.sm_model_to_live), args->synapse, args->syn_args_model_to_live);
    init_synapse_model(&(r_args.sm_live_to_model), args->synapse, args->syn_args_live_to_model);


    /*
     * Create and open recording files
     */

    t = time(NULL);
	tm = *localtime(&t);

    asprintf(&path, "data/%dy_%dm_%dd", tm.tm_year + 1900, tm.tm_mon + 1, tm.tm_mday);


	struct stat st = {0};

    if (stat("data", &st) == -1) {
        mkdir("data", 0777);
    }

    if (stat(path, &st) == -1) {
		mkdir(path, 0777);
	}

	asprintf(&hour, "/%dh_%dm_%ds", tm.tm_hour, tm.tm_min, tm.tm_sec);
	asprintf(&filename_data, "%s%s_data.txt", path, hour);
    sprintf(filename, "%s%s", path, hour);

    if (init_file_selector() == ERR) {
        syslog(LOG_INFO, "Error starting file selector.");
        return ERR;
    }

    if (add_file(filename_data, &(r_args.data_file_id)) == ERR) {
        syslog(LOG_INFO, "Error opening data file.");
        return ERR;
    }

    if (add_file("data/log.txt", &(r_args.events_file_id)) == ERR) {
        syslog(LOG_INFO, "Error opening data file.");
        return ERR;
    }

    printf(" - File: %s\n", filename_data);

    free_pointers(4, &path, &hour, &filename_data, &filename_events);

    /* End of opening recording files */


    /*
     * Set threads
     */

    pthread_attr_init(&attr_rt);
    pthread_attr_init(&attr_wr);
    pthread_attr_setdetachstate(&attr_rt, PTHREAD_CREATE_JOINABLE);
    pthread_attr_setdetachstate(&attr_wr, PTHREAD_CREATE_JOINABLE);


    sigemptyset(&set);
    sigaddset(&set, SIGINT);
    if (pthread_sigmask(SIG_BLOCK, &set, NULL) != 0) syslog(LOG_INFO, "Error blocking SIGINT at main.\n");

    if (open_queue(&msqid_rt, &msqid_nrt) != OK) {
        syslog(LOG_INFO, "Error opening rt queue.");
    	return ERR;
    }

    syslog(LOG_INFO, "CLAMP: Queue opened");

    r_args.msqid = msqid_rt;
    r_args.time_var = args->time_var;
    r_args.before = args->before;
    r_args.after = args->after;
    r_args.observation = args->observation;
    r_args.period =  (1 / args->freq) * NSEC_PER_SEC;
    r_args.freq = args->freq;
    r_args.filename = filename;
    r_args.calibration = args->mode_auto_cal;
    r_args.sec_per_burst = args->sec_per_burst;
    r_args.check_drift = args->check_drift;
    r_args.auto_cal_val_1 = args->auto_cal_val_1;

    w_args.path = path;
    w_args.filename = filename;
    w_args.msqid = msqid_nrt;
    w_args.type_syn = args->synapse;
    w_args.model = args->model;
    w_args.freq = args->freq;
    w_args.time_var = args->time_var;
    w_args.important = args->imp;
    w_args.calibration = args->mode_auto_cal;
    w_args.sm_model_to_live = r_args.sm_model_to_live;
    w_args.sm_model_to_live = r_args.sm_model_to_live;


    create_writer_thread(&(writer), (void *) &w_args);
    create_rt_thread(&(rt), (void *) &r_args);

    syslog(LOG_INFO, "CLAMP: Threads created");

    if (pthread_sigmask(SIG_UNBLOCK, &set, NULL) != 0) syslog(LOG_INFO, "Error unblocking SIGINT at main.\n");
    if (signal(SIGINT, clamp_cleanup) == SIG_ERR) syslog(LOG_INFO, "Error catching SIGINT at main.\n");

    syslog(LOG_INFO, "CLAMP: Signals set");

    join_writer_thread(writer, NULL);
    join_rt_thread(rt, NULL);

    syslog(LOG_INFO, "CLAMP: Threads joined");

    /* End setting threads*/
    

    /*
     * Free and close the resources before the end
     */

    if (msqid_nrt != NULL || msqid_rt != NULL) {
        if (close_queue(&msqid_rt, &msqid_nrt) != OK) syslog(LOG_INFO, "Error closing queue.\n");
    }

    syslog(LOG_INFO, "CLAMP: Queue closed");

    free_neuron_model (&(r_args.nm));
    free_synapse_model (&(r_args.sm_model_to_live));
    free_synapse_model (&(r_args.sm_live_to_model));
    free_pointers(4 , &(args->input_channels), &(args->output_channels), /*&(args->vars), &(args->params),*/ &(args->syn_args_live_to_model), &(args->syn_args_model_to_live));
    /* vars y params no se liberan al acabar porque si se vuelve a ejecutar el experimento sin cambiar de modelo pues petaria */

    syslog(LOG_INFO, "CLAMP: Pointers freed");


    if (destroy_file_selector() == ERR) {
        syslog(LOG_INFO, "Error destroying file selector.");
        return ERR; 
    }

    syslog(LOG_INFO, "CLAMP: File selector destroyed");


    syslog(LOG_INFO, PRINT_YELLOW "CLAMP: clamp finished." PRINT_RESET "\n");
    return OK;
}
