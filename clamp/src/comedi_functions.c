#include "../includes/comedi_functions.h"

comedi_t * open_device_comedi (char * dev_name) {
	comedi_t * device;

	device = comedi_open(dev_name);
	if(device == NULL)
	{
		comedi_perror(dev_name);
		return NULL;
	}

	return device;
}

int close_device_comedi (comedi_t * device) {
	if (comedi_close(device) == -1) {
		comedi_perror("Error with comedi_close");
		return -1;
	}

	return 0;
}


int create_session_comedi (comedi_t * device, int aref, Comedi_session ** session_ptr) {
	Comedi_session * session;
	*session_ptr = (Comedi_session *) malloc (sizeof(Comedi_session));
	session = *session_ptr;
	
	session->device = device;
	session->range = 0; //get_range_comedi(device, subdev, chan, unit, min, max);
	session->aref = aref;


	session->in_subdev = comedi_find_subdevice_by_type(device, COMEDI_SUBD_AI, 0);
	if (session->in_subdev == -1) {
		comedi_perror("Error finding input subdevice");

		free(session);
		return ERR;
	}

	session->out_subdev = comedi_find_subdevice_by_type(device, COMEDI_SUBD_AO, 0);
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

comedi_range * get_range_info_comedi (Comedi_session * session, int direction, int chan) {
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

lsampl_t get_maxdata_comedi (Comedi_session * session, int direction, int chan) {
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

int read_comedi (Comedi_session * session, int n_channels, int * channels, double * ret) {
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


int write_comedi (Comedi_session * session, int n_channels, int * channels, double * values) {
	int i;
	double aux;
	comedi_range * range_info;
	lsampl_t maxdata;

    for (i = 0; i < n_channels; ++i) {
    	range_info = get_range_info_comedi(session, COMEDI_OUTPUT, channels[i]);
    	maxdata = get_maxdata_comedi(session, COMEDI_OUTPUT, channels[i]);

        if (DEBUG == 1) syslog(LOG_INFO, "WRITE_DAQ: Writing value[%d] %f", i, values[i]);

    	if (write_single_data_comedi (session, range_info, maxdata, channels[i], values[i]) != 1) {
    		printf("Error writing from channel %d at iter %d\n", channels[i], i);
    		return -1;
    	}

        if (DEBUG == 1) syslog(LOG_INFO, "WRITE_DAQ: Wrote value[%d] %f", i, values[i]);
    }

    if (DEBUG == 1) syslog(LOG_INFO, "WRITE_DAQ: Ending");
    
    return 0;
}


int read_single_data_comedi (Comedi_session * session, comedi_range * range_info, lsampl_t maxdata, int chan, double * ret) {
	lsampl_t data;
	double physical_value;
	int retval;

	retval = comedi_data_read(session->device, session->in_subdev, chan, session->range, session->aref, &data);
	if(retval < 0)
	{
		comedi_perror("read");
		return -1;
	}

	comedi_set_global_oor_behavior(COMEDI_OOR_NAN);
	physical_value = comedi_to_phys(data, range_info, maxdata);
	
	if(isnan(physical_value)) {
		return -1;
	} else {
		*ret = physical_value;
	}

	return 0;
}


int write_single_data_comedi (Comedi_session * session, comedi_range * range_info, lsampl_t maxdata, int chan, double data) {
	lsampl_t comedi_value;

	comedi_value = comedi_from_phys(data, range_info, maxdata);
	if (comedi_value < 0 || comedi_value > maxdata) {
		comedi_perror("write");
		return -1;
	}

	return comedi_data_write(session->device, session->out_subdev, chan, session->range, session->aref, comedi_value);
}
