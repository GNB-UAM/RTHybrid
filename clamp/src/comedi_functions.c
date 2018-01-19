#include "../includes/device_functions.h"
#include <comedilib.h>

#define READ_FROM_FILE 0

struct _Daq_session{
	comedi_t * device;
	int in_subdev;		/*input subdevice */
	int out_subdev;		/*output subdevice */
	int range;			
	int aref;		
};


/* Read from file variables */
FILE * f;

comedi_range * get_range_info_comedi (Daq_session * session, int direction, int chan);
lsampl_t get_maxdata_comedi (Daq_session * session, int direction, int chan);
int read_single_data_comedi (Daq_session * session, comedi_range * range_info, lsampl_t maxdata, int chan, double * ret);
int write_single_data_comedi (Daq_session * session, comedi_range * range_info, lsampl_t maxdata, int chan, double data);

int daq_open_device (void ** device) {
	comedi_t * dsc;

	/**device = (comedi_t *) malloc (sizeof(comedi_t));
	dsc = *device;*/

	if (READ_FROM_FILE == 1) f = fopen("data/2017y_11m_28d/19h_34m_1s_1.txt", "r");

	dsc = comedi_open("/dev/comedi0");
	if(dsc == NULL)
	{
		comedi_perror("/dev/comedi0");
		return ERR;
	}

	*device = dsc;

	return OK;
}

int daq_close_device (void ** device) {
	comedi_t * dsc = *device;

	if (READ_FROM_FILE == 1) fclose(f);

	if (comedi_close(dsc) == -1) {
		comedi_perror("Error with comedi_close");
		return ERR;
	}

	return OK;
}


int daq_create_session (void  ** device, Daq_session ** session_ptr) {
	Daq_session * session;
	*session_ptr = (Daq_session *) malloc (sizeof(Daq_session));
	session = *session_ptr;
	
	session->device = (comedi_t *) *device;
	session->range = 0; //get_range_comedi(device, subdev, chan, unit, min, max);
	session->aref = AREF_GROUND;


	session->in_subdev = comedi_find_subdevice_by_type(session->device, COMEDI_SUBD_AI, 0);
	if (session->in_subdev == -1) {
		comedi_perror("Error finding input subdevice");

		free(session);
		return ERR;
	}

	session->out_subdev = comedi_find_subdevice_by_type(session->device, COMEDI_SUBD_AO, 0);
	if (session->out_subdev == -1) {
		comedi_perror("Error finding output subdevice");

		free(session);
		return ERR;
	}

	return OK;
}

/*int get_range_comedi (comedi_t * device, int subdev, int chan, double min, double max, int unit) {
	int range = comedi_find_range (device, subdev, chan, unit, min, max);

	if (range == -1) {
		comedi_perror("Error with comedi_find_range");
		return -1;
	}

	return range;
}*/

comedi_range * get_range_info_comedi (Daq_session * session, int direction, int chan) {
	comedi_range * range_info;
	int subdev;

	if (direction == COMEDI_INPUT) {
		subdev = session->in_subdev;
	} else if (direction == COMEDI_OUTPUT) {
		subdev = session->out_subdev;
	} else {
		return NULL;
	}

	range_info = comedi_get_range(session->device, subdev, chan, session->range);

	return range_info;
}

lsampl_t get_maxdata_comedi (Daq_session * session, int direction, int chan) {
	lsampl_t maxdata;
	int subdev;

	if (direction == COMEDI_INPUT) {
		subdev = session->in_subdev;
	} else if (direction == COMEDI_OUTPUT) {
		subdev = session->out_subdev;
	} else {
		return 0;
	}

	maxdata = comedi_get_maxdata(session->device, subdev, chan);
	return maxdata;
}


int read_single_data_comedi (Daq_session * session, comedi_range * range_info, lsampl_t maxdata, int chan, double * ret) {
	lsampl_t data;
	double physical_value;
	int retval;

	if (READ_FROM_FILE == 0) {
		retval = comedi_data_read(session->device, session->in_subdev, chan, session->range, session->aref, &data);
		if(retval < 0)
		{
			comedi_perror("read");
			return -1;
		}

		comedi_set_global_oor_behavior(COMEDI_OOR_NUMBER);
		physical_value = comedi_to_phys(data, range_info, maxdata);
		
		if(isnan(physical_value)) {
			return -1;
		} else {
			*ret = physical_value;
		}
	} else if (READ_FROM_FILE == 1) {
		char buf[999];
		fgets(buf, sizeof(char) * 200, f);
		//printf("%s\n", buf);
		char * elemento;
		elemento = strtok(buf, " ");
		//printf("%p %p\n", elemento, buf);
		int i;
		for (i=0; i<8; i++){
			elemento = strtok(NULL, " ");
			//printf("%p\n", elemento);
			fflush(NULL);
		}
		*ret = atof(elemento);
		//printf("\n%f\n", *ret);

		while (elemento != NULL) {
			elemento = strtok(NULL, " ");
		}
	}
	


	

	return 0;
}


int write_single_data_comedi (Daq_session * session, comedi_range * range_info, lsampl_t maxdata, int chan, double data) {
	lsampl_t comedi_value;

	comedi_value = comedi_from_phys(data, range_info, maxdata);
	if (comedi_value < 0 || comedi_value > maxdata) {
		comedi_perror("write");
		return -1;
	}

	return comedi_data_write(session->device, session->out_subdev, chan, session->range, session->aref, comedi_value);
}

int daq_read (Daq_session * session, int n_channels, int * channels, double * ret) {
	int i;
	double aux;
	comedi_range * range_info;
	lsampl_t maxdata;

    for (i = 0; i < n_channels; ++i) {
    	range_info = get_range_info_comedi(session, COMEDI_INPUT, channels[i]);
    	maxdata = get_maxdata_comedi(session, COMEDI_INPUT, channels[i]);

    	if (read_single_data_comedi (session, range_info, maxdata, channels[i], &aux) == 0) {
    		ret[i] = aux;
    	} else {
    		printf("Error reading from channel %d at iter %d\n", channels[i], i);
    		return -1;
    	}
    }
    
    return 0;
}


int daq_write (Daq_session * session, int n_channels, int * channels, double * values) {
	int i;
	double aux;
	comedi_range * range_info;
	lsampl_t maxdata;

    for (i = 0; i < n_channels; ++i) {
    	range_info = get_range_info_comedi(session, COMEDI_OUTPUT, channels[i]);
    	maxdata = get_maxdata_comedi(session, COMEDI_OUTPUT, channels[i]);

        //if (DEBUG == 1) syslog(LOG_INFO, "WRITE_DAQ: Writing value[%d] %f", i, values[i]);

    	if (write_single_data_comedi (session, range_info, maxdata, channels[i], values[i]) != 1) {
    		printf("Error writing from channel %d at iter %d\n", channels[i], i);
    		return -1;
    	}

        //if (DEBUG == 1) syslog(LOG_INFO, "WRITE_DAQ: Wrote value[%d] %f", i, values[i]);
    }

    //if (DEBUG == 1) syslog(LOG_INFO, "WRITE_DAQ: Ending");
    
    return 0;
}
