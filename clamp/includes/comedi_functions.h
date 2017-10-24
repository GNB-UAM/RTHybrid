#include <stdio.h>
#include <stdlib.h>
#include <comedilib.h>
#include <ctype.h>
#include <math.h>
#include "types_clamp.h"

typedef struct {
	comedi_t * device;
	int in_subdev;		/*input subdevice */
	int out_subdev;		/*output subdevice */
	int range;			
	int aref;		
} Comedi_session;


comedi_t * open_device_comedi (char * dev_name);

int close_device_comedi (comedi_t * device);

int create_session_comedi (comedi_t * device, int aref, Comedi_session ** session_ptr);

//int get_range_comedi (comedi_t * device, int subdev, int chan, double min, double max, int unit);

comedi_range * get_range_info_comedi (Comedi_session * session, int direction, int chan);

lsampl_t get_maxdata_comedi (Comedi_session * session, int direction, int chan);

int read_comedi (Comedi_session * session, int n_channels, int * channels, double * ret);

int write_comedi (Comedi_session * session, int n_channels, int * channels, double * values);

int read_single_data_comedi (Comedi_session * session, comedi_range * range_info, lsampl_t maxdata, int chan, double * ret);

int write_single_data_comedi (Comedi_session * session, comedi_range * range_info, lsampl_t maxdata, int chan, double data);