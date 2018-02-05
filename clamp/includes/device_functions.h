#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <math.h>
#include "types_clamp.h"


typedef struct _Daq_session Daq_session;

int daq_open_device (void ** device);

int daq_create_session (void  ** device, Daq_session ** session_ptr);

int daq_close_device (void ** device);

int daq_read (Daq_session * session, int n_channels, int * channels, double * ret);

int daq_write (Daq_session * session, int n_channels, int * channels, double * values);

int daq_digital_write (Daq_session * session, int n_channels, int * channels, unsigned int * bits);