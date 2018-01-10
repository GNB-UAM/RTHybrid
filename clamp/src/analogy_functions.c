#include "../includes/device_functions.h"
#include <rtdm/analogy.h>

struct _Daq_session {
    a4l_desc_t * device;
	int idx_subd_in;
	int idx_subd_out;     
};

int debug = 0;

int daq_open_device (void ** device) {
	int err = 0;
	a4l_desc_t * dsc;

	*device = (a4l_desc_t *) malloc (sizeof(a4l_desc_t));
	dsc = *device;
	dsc->sbdata = NULL;


	err = a4l_open(dsc, "analogy0");
	if ( err < 0) {
        fprintf(stderr, "Analogy: a4l_open %s failed (err=%d)\n", "analogy0", err);
        return ERR;
    }

    dsc->sbdata = malloc(dsc->sbsize);

    if (dsc->sbdata == NULL) {
		fprintf(stderr, "Analogy: info buffer allocation failedn");
		return ERR;
	}

    err = a4l_fill_desc(dsc);
    if (err < 0) {
        fprintf(stderr, "Analogy:  a4l_fill_desc failed (err=%d)\n", err);
        free(dsc->sbdata);
        return ERR;
    }

    return OK;
}



int daq_create_session (void  ** device, Daq_session ** session_ptr) {
	Daq_session * session;
	*session_ptr = (Daq_session *) malloc (sizeof(Daq_session));
	session = *session_ptr;
	a4l_sbinfo_t *sbinfo;
	int err = 0;

	session->device = (a4l_desc_t*) *device;


	session->idx_subd_in  = session->device->idx_read_subd;
	session->idx_subd_out  = 1;//session->device->idx_write_subd;

	if (session->idx_subd_in == -1) {
		fprintf(stderr, "Analogy: no analog input subdevice available\n");
		return ERR;
	}

	if (session->idx_subd_out == -1) {
		fprintf(stderr, "Analogy: no analog output subdevice available\n");
		return ERR;
	}

	if (debug != 0) printf("Analogy: selected input subdevice index = %d\n", session->idx_subd_in);
	if (debug != 0) printf("Analogy: selected output subdevice index = %d\n", session->idx_subd_out);

	/* We must check that the subdevice is really an AI one
	   (in case, the subdevice index was set with the option -s) */
	err = a4l_get_subdinfo(session->device, session->idx_subd_in, &sbinfo);
	if (err < 0) {
		fprintf(stderr,
			"insn_read: get_sbinfo(%d) failed (err = %d)\n",
			session->idx_subd_in, err);
		return ERR;
	}

	if ((sbinfo->flags & A4L_SUBD_TYPES) != A4L_SUBD_AI) {
		fprintf(stderr,
			"insn_read: wrong subdevice selected "
			"(not an analog input)\n");
		return ERR;
	}


	/* We must check that the subdevice is really an AO one
	   (in case, the subdevice index was set with the option -s) */
	err = a4l_get_subdinfo(session->device, session->idx_subd_out, &sbinfo);
	if (err < 0) {
		fprintf(stderr,
			"insn_write: get_sbinfo(%d) failed (err = %d)\n",
			session->idx_subd_out, err);
		return ERR;
	}

	if ((sbinfo->flags & A4L_SUBD_TYPES) != A4L_SUBD_AO) {
		fprintf(stderr,
			"insn_write: wrong subdevice selected "
			"(not an analog output)\n");
		return ERR;
	}

	return OK;
}


int daq_close_device (void ** device) {
	a4l_desc_t * dsc = *device;
	if (dsc->sbdata != NULL) free(dsc->sbdata);
	a4l_close(dsc);

    return 1;
}


int daq_read (Daq_session * session, int n_channels, int * channels, double * ret) {
	int i, err = 0;
	a4l_sbinfo_t * sbinfo;
	a4l_chinfo_t * chinfo;
	a4l_rnginfo_t * rnginfo;
	unsigned char buf[sizeof(double)];


	for (i = 0; i < n_channels; ++i) {
		err = a4l_get_rnginfo(session->device, session->idx_subd_in, channels[i], 1, &rnginfo);
		if (err < 0) {
			fprintf(stderr, "Analogy read: failed to recover range descriptor (err=%d)\n", err);
			return ERR;
		}

		if (debug != 0) {
			printf("Analogy read: range descriptor retrieved\n");
			printf("\t min = %ld\n", rnginfo->min);
			printf("\t max = %ld\n", rnginfo->max);
		}

		/* Retrieve the subdevice data size */
		err = a4l_get_chinfo(session->device, session->idx_subd_in, channels[i], &chinfo);
		if (err < 0) {
			fprintf(stderr, "Analogy read: info for channel %d on subdevice %d not available (err=%d)\n", channels[i], session->idx_subd_in, err);
			return ERR;
		}

		if (read_single_data_analogy(session, channels[i], buf) != OK) {
			fprintf(stderr, "Analogy read: error reading from channel %d at iter %d\n", channels[i], i);
			return ERR;
		}

		err = a4l_rawtod(chinfo, rnginfo, &ret[i], buf, 1);
		if (err < 0) {
			fprintf(stderr, "Analogy read: a4l_rawtod failed (err=%d)\n", err);
			return ERR;
		}
	}

	return OK;
}


int read_single_data_analogy (Daq_session * session, int idx_chan, unsigned char * buf) {
	int err = 0;


	err = a4l_sync_read(session->device, session->idx_subd_in, CHAN(idx_chan), 0, buf, sizeof(double));

	if (err < 0) {
		fprintf(stderr, "Analogy read: a4l_sync_read failed (err=%d)\n", err);
		return ERR;
	}

	return OK;
}




int daq_write (Daq_session * session, int n_channels, int * channels, double * values) {
	int i, err = 0, raw_val = 0;
	a4l_sbinfo_t * sbinfo;
	a4l_chinfo_t * chinfo;
	a4l_rnginfo_t * rnginfo;
	unsigned char buf[sizeof(double)];


	for (i = 0; i < n_channels; ++i) {
		err = a4l_get_rnginfo(session->device, session->idx_subd_out, channels[i], 1, &rnginfo);
		if (err < 0) {
			fprintf(stderr, "Analogy write: failed to recover range descriptor (err=%d)\n", err);
			return ERR;
		}

		if (debug != 0) {
			printf("Analogy write: range descriptor retrieved\n");
			printf("\t min = %ld\n", rnginfo->min);
			printf("\t max = %ld\n", rnginfo->max);
		}

		/* Retrieve the subdevice data size */
		err = a4l_get_chinfo(session->device, session->idx_subd_out, channels[i], &chinfo);
		if (err < 0) {
			fprintf(stderr, "Analogy write: info for channel %d on subdevice %d not available (err=%d)\n", channels[i], session->idx_subd_out, err);
			return ERR;
		}

		if (a4l_dtoraw(chinfo, rnginfo, &raw_val, &values[i], 1) < 0) {
			fprintf(stderr, "Analogy write: data conversion failed (err=%d)\n", err);
			return ERR;
		}

		if (write_single_data_analogy(session, channels[i], raw_val) != OK) {
			fprintf(stderr, "Analogy write: error writing to channel %d at iter %d\n", channels[i], i);
			return ERR;
		}
	}

	return OK;
}


int write_single_data_analogy (Daq_session * session, int idx_chan, int value) {
	int err = 0;


	err = a4l_sync_write(session->device, session->idx_subd_out, CHAN(idx_chan), 0, &value, sizeof(double));

	if (err < 0) {
		fprintf(stderr, "Analogy write: a4l_sync_write failed (err=%d)\n", err);
		return ERR;
	}

	return OK;
}
