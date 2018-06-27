#include "../includes/xml_clamp_parser.h"

/*CLAMP PARSER DEFINITIONS */

#define CLAMP "clamp"
#define MODEL "model"
#define SYNAPSE "synapse"
#define FREQ "freq"
#define TIMES "times"
#define BEFORE "before"
#define DURATION "duration"
#define AFTER "after"
#define ANTI "anti"
#define IMP "imp"
#define CALIB "calib"
#define INPUT_CHANNELS "input_channels"
#define OUTPUT_CHANNELS "output_channels"
#define INPUT_FACTOR "input_factor"
#define OUTPUT_FACTOR "output_factor"
#define FIRING "sec_per_burst"
#define AUTOCAL_VAL_1 "autocal_val_1"
#define DRIFT "drift"

#define VARS "vars"
#define PARAMS "params"

#define X_VAR "x"
#define Y_VAR "y"
#define Z_VAR "z"

#define STEP_V_TO_R "step_v_to_r"
#define STEP_R_TO_V "step_r_to_v"

#define VALUE "val"
#define TYPE "type"

/*CLAMP PARSER FUNCTIONS */
static int parse_clamp_model_iz (xmlDocPtr doc, xmlNodePtr cur, clamp_args * args);
static int parse_clamp_model_hr (xmlDocPtr doc, xmlNodePtr cur, clamp_args * args);
static int parse_clamp_model_rlk (xmlDocPtr doc, xmlNodePtr cur, clamp_args * args);
static int parse_clamp_model (xmlDocPtr doc, xmlNodePtr cur, clamp_args * args);
static int parse_clamp_synapse (xmlDocPtr doc, xmlNodePtr cur, clamp_args * args);
static int parse_clamp_syn_elec (xmlDocPtr doc, xmlNodePtr cur, clamp_args * args);
static int parse_clamp_syn_golowasch (xmlDocPtr doc, xmlNodePtr cur, clamp_args * args);
static int parse_clamp_freq (xmlDocPtr doc, xmlNodePtr cur, clamp_args * args);
static int parse_clamp_time (xmlDocPtr doc, xmlNodePtr cur, clamp_args * args);
static int parse_clamp_drift (xmlDocPtr doc, xmlNodePtr cur, clamp_args * args);
static int parse_clamp_sec_per_burst (xmlDocPtr doc, xmlNodePtr cur, clamp_args * args);
static int parse_clamp_important (xmlDocPtr doc, xmlNodePtr cur, clamp_args * args);
static int parse_clamp_calibration (xmlDocPtr doc, xmlNodePtr cur, clamp_args * args);
static int parse_clamp_input_channels (xmlDocPtr doc, xmlNodePtr cur, clamp_args * args);
static int parse_clamp_output_channels (xmlDocPtr doc, xmlNodePtr cur, clamp_args * args);
static int parse_clamp_input_factor (xmlDocPtr doc, xmlNodePtr cur, clamp_args * args);
static int parse_clamp_output_factor (xmlDocPtr doc, xmlNodePtr cur, clamp_args * args);


/* CLAMP PARSER */

int xml_clamp_parser (char * file, clamp_args * args) {
	int ret = OK;

	xmlDocPtr doc;
    xmlNodePtr cur;
     
    if(!file) {
        return ERR;
    }
 
    if((doc = xmlParseFile(file)) == NULL) {
        fprintf(stderr,"File %s is not an XML file.\n", file);
        return ERR;
    }
    cur = xmlDocGetRootElement(doc);
    if (cur == NULL) {
        fprintf(stderr, "Empty file\n");
        xmlFreeDoc(doc);
        return ERR;
    }
 
    if (xmlStrcmp(cur->name, (const xmlChar*) CLAMP) != 0) {
        fprintf(stderr,"<%s> expected, not <%s>\n", CLAMP, cur->name);
        xmlFreeDoc(doc);
        return ERR;
    }


    args->input_channels = NULL;
    args->output_channels = NULL;

    cur = cur->xmlChildrenNode;

    while(cur != NULL) {
        if (xmlStrcmp(cur->name, (const xmlChar*) MODEL) == 0) {
            ret = parse_clamp_model(doc, cur, args);
        }
        else if (xmlStrcmp(cur->name, (const xmlChar*) SYNAPSE) == 0) {
        	ret = parse_clamp_synapse(doc, cur, args);
        }
        else if (xmlStrcmp(cur->name, (const xmlChar*) FREQ) == 0) {
        	ret = parse_clamp_freq(doc, cur, args);
        }
        else if (xmlStrcmp(cur->name, (const xmlChar*) TIMES) == 0) {
            ret = parse_clamp_time(doc, cur, args);
        }
        else if (xmlStrcmp(cur->name, (const xmlChar*) DRIFT) == 0) {
            ret = parse_clamp_drift(doc, cur, args);
        }
        else if (xmlStrcmp(cur->name, (const xmlChar*) IMP) == 0) {
            ret = parse_clamp_important(doc, cur, args);
        }
        else if (xmlStrcmp(cur->name, (const xmlChar*) CALIB) == 0) {
            ret = parse_clamp_calibration(doc, cur, args);
        }
        else if (xmlStrcmp(cur->name, (const xmlChar*) INPUT_CHANNELS) == 0) {
            ret = parse_clamp_input_channels(doc, cur, args);
        }
        else if (xmlStrcmp(cur->name, (const xmlChar*) OUTPUT_CHANNELS) == 0) {
            ret = parse_clamp_output_channels(doc, cur, args);
        }
        else if (xmlStrcmp(cur->name, (const xmlChar*) INPUT_FACTOR) == 0) {
            ret = parse_clamp_input_factor(doc, cur, args);
        }
        else if (xmlStrcmp(cur->name, (const xmlChar*) OUTPUT_FACTOR) == 0) {
            ret = parse_clamp_output_factor(doc, cur, args);
        }
        else if (xmlStrcmp(cur->name, (const xmlChar*) FIRING) == 0) {
            ret = parse_clamp_sec_per_burst(doc, cur, args);
        }

        if (ret == ERR) break;

        cur = cur->next;
    }


    xmlFreeDoc(doc);
    return ret;

}



static int parse_clamp_model_iz (xmlDocPtr doc, xmlNodePtr cur, clamp_args * args) {
	xmlNodePtr child =  NULL;
	int ret = OK;

	if ((!doc) || (!cur) || (!args)) return ERR;

	args->vars = (double*) malloc (sizeof(double) * 2);
    args->params = (double *) malloc (sizeof(double) * 6);

	while (cur != NULL) {
		if (xmlStrcmp(cur->name, (const xmlChar *) VARS) == 0) {
			child = cur->xmlChildrenNode;

			while (child != NULL) {
				if (xmlStrcmp(child->name, (const xmlChar *) X_VAR) == 0) ret = parse_double(doc, child, &args->vars[VAR_X], (const xmlChar*) VALUE);
				if (xmlStrcmp(child->name, (const xmlChar *) Y_VAR) == 0) ret = parse_double(doc, child, &args->vars[VAR_Y], (const xmlChar*) VALUE);

				if (ret != OK) return ret;

				child = child->next;
			}
		}
		else if (xmlStrcmp(cur->name, (const xmlChar *) PARAMS) == 0) {
			child = cur->xmlChildrenNode;

			while (child != NULL) {
				if (xmlStrcmp(child->name, (const xmlChar *) "a") == 0) ret = parse_double(doc, child, &args->params[IZ_A], (const xmlChar*) VALUE);
				if (xmlStrcmp(child->name, (const xmlChar *) "b") == 0) ret = parse_double(doc, child, &args->params[IZ_B], (const xmlChar*) VALUE);
				if (xmlStrcmp(child->name, (const xmlChar *) "c") == 0) ret = parse_double(doc, child, &args->params[IZ_C], (const xmlChar*) VALUE);
				if (xmlStrcmp(child->name, (const xmlChar *) "d") == 0) ret = parse_double(doc, child, &args->params[IZ_D], (const xmlChar*) VALUE);
				if (xmlStrcmp(child->name, (const xmlChar *) "i") == 0) ret = parse_double(doc, child, &args->params[IZ_I], (const xmlChar*) VALUE);
				args->params[IZ_DT] = 0.001;

				if (ret != OK) return ret;

				child = child->next;
			}
		}

	cur = cur->next;
	}

	return OK;
}


static int parse_clamp_model_hr (xmlDocPtr doc, xmlNodePtr cur, clamp_args * args) {
	xmlNodePtr child =  NULL;
	int ret = OK;

	if ((!doc) || (!cur) || (!args)) return ERR;

	args->vars = (double*) malloc (sizeof(double) * 3);
    args->params = (double *) malloc (sizeof(double) * 4);

	while (cur != NULL) {
		if (xmlStrcmp(cur->name, (const xmlChar *) VARS) == 0) {
			child = cur->xmlChildrenNode;

			while (child != NULL) {
				if (xmlStrcmp(child->name, (const xmlChar *) X_VAR) == 0) ret = parse_double(doc, child, &args->vars[VAR_X], (const xmlChar*) VALUE);
				if (xmlStrcmp(child->name, (const xmlChar *) Y_VAR) == 0) ret = parse_double(doc, child, &args->vars[VAR_Y], (const xmlChar*) VALUE);
				if (xmlStrcmp(child->name, (const xmlChar *) Z_VAR) == 0) ret = parse_double(doc, child, &args->vars[VAR_Z], (const xmlChar*) VALUE);

				if (ret != OK) return ret;

				child = child->next;
			}
		}
		else if (xmlStrcmp(cur->name, (const xmlChar *) PARAMS) == 0) {
			child = cur->xmlChildrenNode;

			while (child != NULL) {
				if (xmlStrcmp(child->name, (const xmlChar *) "r") == 0) ret = parse_double(doc, child, &args->params[HR_R], (const xmlChar*) VALUE);
				if (xmlStrcmp(child->name, (const xmlChar *) "s") == 0) ret = parse_double(doc, child, &args->params[HR_S], (const xmlChar*) VALUE);
				if (xmlStrcmp(child->name, (const xmlChar *) "i") == 0) ret = parse_double(doc, child, &args->params[HR_I], (const xmlChar*) VALUE);
				args->params[HR_DT] = 0.001;

				if (ret != OK) return ret;

				child = child->next;
			}
		}

	cur = cur->next;
	}

	return OK;
}


static int parse_clamp_model_rlk (xmlDocPtr doc, xmlNodePtr cur, clamp_args * args) {
	xmlNodePtr child =  NULL;
	int ret = OK;

	if ((!doc) || (!cur) || (!args)) return ERR;

	args->vars = (double*) malloc (sizeof(double) * 2);
    args->params = (double *) malloc (sizeof(double) * 8);

	while (cur != NULL) {
		if (xmlStrcmp(cur->name, (const xmlChar *) VARS) == 0) {
			child = cur->xmlChildrenNode;

			while (child != NULL) {
				if (xmlStrcmp(child->name, (const xmlChar *) X_VAR) == 0) ret = parse_double(doc, child, &args->vars[VAR_X], (const xmlChar*) VALUE);
				if (xmlStrcmp(child->name, (const xmlChar *) Y_VAR) == 0) ret = parse_double(doc, child, &args->vars[VAR_Y], (const xmlChar*) VALUE);

				if (ret != OK) return ret;

				child = child->next;
			}
		}
		else if (xmlStrcmp(cur->name, (const xmlChar *) PARAMS) == 0) {
			child = cur->xmlChildrenNode;

			while (child != NULL) {
				if (xmlStrcmp(child->name, (const xmlChar *) "alpha") == 0) ret = parse_double(doc, child, &args->params[RLK_ALPHA], (const xmlChar*) VALUE);
				if (xmlStrcmp(child->name, (const xmlChar *) "mu") == 0) ret = parse_double(doc, child, &args->params[RLK_MU], (const xmlChar*) VALUE);
				if (xmlStrcmp(child->name, (const xmlChar *) "sigma") == 0) ret = parse_double(doc, child, &args->params[RLK_SIGMA], (const xmlChar*) VALUE);
				if (xmlStrcmp(child->name, (const xmlChar *) "i") == 0) ret = parse_double(doc, child, &args->params[RLK_I], (const xmlChar*) VALUE);

				if (ret != OK) return ret;

				child = child->next;
			}
		}

	cur = cur->next;
	}

	return OK;
}


static int parse_clamp_model_gh (xmlDocPtr doc, xmlNodePtr cur, clamp_args * args) {
	xmlNodePtr child =  NULL;
	int ret = OK;

	if ((!doc) || (!cur) || (!args)) return ERR;

	args->vars = (double*) malloc (sizeof(double) * 3);
    args->params = (double *) malloc (sizeof(double) * 18);

	while (cur != NULL) {
		if (xmlStrcmp(cur->name, (const xmlChar *) VARS) == 0) {
			child = cur->xmlChildrenNode;

			while (child != NULL) {
				if (xmlStrcmp(child->name, (const xmlChar *) X_VAR) == 0) ret = parse_double(doc, child, &args->vars[VAR_X], (const xmlChar*) VALUE);

				if (ret != OK) return ret;

				child = child->next;
			}
		}
		else if (xmlStrcmp(cur->name, (const xmlChar *) PARAMS) == 0) {
			child = cur->xmlChildrenNode;

			while (child != NULL) {
				if (xmlStrcmp(child->name, (const xmlChar *) "gca") == 0) ret = parse_double(doc, child, &args->params[GH_G_CA], (const xmlChar*) VALUE);
				if (xmlStrcmp(child->name, (const xmlChar *) "eca") == 0) ret = parse_double(doc, child, &args->params[GH_E_CA], (const xmlChar*) VALUE);
				if (xmlStrcmp(child->name, (const xmlChar *) "vthca") == 0) ret = parse_double(doc, child, &args->params[GH_VTH_CA], (const xmlChar*) VALUE);
				if (xmlStrcmp(child->name, (const xmlChar *) "kca") == 0) ret = parse_double(doc, child, &args->params[GH_K_CA], (const xmlChar*) VALUE);

				if (xmlStrcmp(child->name, (const xmlChar *) "gk") == 0) ret = parse_double(doc, child, &args->params[GH_G_K], (const xmlChar*) VALUE);
				if (xmlStrcmp(child->name, (const xmlChar *) "ek") == 0) ret = parse_double(doc, child, &args->params[GH_E_K], (const xmlChar*) VALUE);
				if (xmlStrcmp(child->name, (const xmlChar *) "vthk") == 0) ret = parse_double(doc, child, &args->params[GH_VTH_K], (const xmlChar*) VALUE);
				if (xmlStrcmp(child->name, (const xmlChar *) "kk") == 0) ret = parse_double(doc, child, &args->params[GH_K_K], (const xmlChar*) VALUE);

				if (xmlStrcmp(child->name, (const xmlChar *) "gks") == 0) ret = parse_double(doc, child, &args->params[GH_G_KS], (const xmlChar*) VALUE);
				if (xmlStrcmp(child->name, (const xmlChar *) "vthks") == 0) ret = parse_double(doc, child, &args->params[GH_VTH_KS], (const xmlChar*) VALUE);
				if (xmlStrcmp(child->name, (const xmlChar *) "kks") == 0) ret = parse_double(doc, child, &args->params[GH_K_KS], (const xmlChar*) VALUE);

				if (xmlStrcmp(child->name, (const xmlChar *) "gl") == 0) ret = parse_double(doc, child, &args->params[GH_G_L], (const xmlChar*) VALUE);
				if (xmlStrcmp(child->name, (const xmlChar *) "el") == 0) ret = parse_double(doc, child, &args->params[GH_E_L], (const xmlChar*) VALUE);

				if (xmlStrcmp(child->name, (const xmlChar *) "c") == 0) ret = parse_double(doc, child, &args->params[GH_CM], (const xmlChar*) VALUE);
				if (xmlStrcmp(child->name, (const xmlChar *) "epsilon") == 0) ret = parse_double(doc, child, &args->params[GH_EPSILON], (const xmlChar*) VALUE);
				if (xmlStrcmp(child->name, (const xmlChar *) "delta") == 0) ret = parse_double(doc, child, &args->params[GH_DELTA], (const xmlChar*) VALUE);
				if (xmlStrcmp(child->name, (const xmlChar *) "i") == 0) ret = parse_double(doc, child, &args->params[GH_I], (const xmlChar*) VALUE);

				if (ret != OK) return ret;

				child = child->next;
			}
		}

	cur = cur->next;
	}

	return OK;
}



static int parse_clamp_model (xmlDocPtr doc, xmlNodePtr cur, clamp_args * args) {
	int ret = ERR;

	if ((!doc) || (!cur) || (!args)) return ERR;

	if (parse_int(doc, cur, &args->model, (const xmlChar*) TYPE) != OK) return ERR;


	switch(args->model) {
		case IZ:
			ret = parse_clamp_model_iz(doc, cur->xmlChildrenNode, args);
			break;
		case HR:
			ret = parse_clamp_model_hr(doc, cur->xmlChildrenNode, args);
			break;
		case RLK:
			ret = parse_clamp_model_rlk(doc, cur->xmlChildrenNode, args);
			break;
		case GH:
			ret = parse_clamp_model_gh(doc, cur->xmlChildrenNode, args);
			break;
		default:
			return ERR;
	}

	return ret;
}


static int parse_clamp_syn_elec (xmlDocPtr doc, xmlNodePtr cur, clamp_args * args) {
	xmlNodePtr child =  NULL;
	int ret = OK;
	int antiphase = 0;

	if ((!doc) || (!cur) || (!args)) return ERR;

	args->syn_args_live_to_model = (syn_elec_args *) malloc (sizeof(syn_elec_args));
    args->syn_args_model_to_live = (syn_elec_args *) malloc (sizeof(syn_elec_args));

    syn_elec_args * args_live_to_model_elec = (syn_elec_args *) args->syn_args_live_to_model;
    syn_elec_args * args_model_to_live_elec = (syn_elec_args *) args->syn_args_model_to_live;


    while (cur != NULL) {
		if (xmlStrcmp(cur->name, (const xmlChar *) "g_virtual_to_real") == 0) ret = parse_double(doc, cur, &(args_model_to_live_elec->g[ELEC_G]), (const xmlChar*) VALUE);
		if (xmlStrcmp(cur->name, (const xmlChar *) "g_real_to_virtual") == 0) ret = parse_double(doc, cur, &(args_live_to_model_elec->g[ELEC_G]), (const xmlChar*) VALUE);
		if (xmlStrcmp(cur->name, (const xmlChar *) "antiphase") == 0) ret = parse_int(doc, cur, &antiphase, (const xmlChar*) VALUE);

		if (antiphase) {
	        args_model_to_live_elec->anti = -1;
	        args_live_to_model_elec->anti = -1;
	    } else {
	        args_model_to_live_elec->anti = 1;
	        args_live_to_model_elec->anti = 1;
	    }

		if (ret != OK) return ret;


		cur = cur->next;
	}

	return OK;

}


static int parse_clamp_syn_golowasch (xmlDocPtr doc, xmlNodePtr cur, clamp_args * args) {
	xmlNodePtr child =  NULL;
	int ret = OK;

	if ((!doc) || (!cur) || (!args)) return ERR;

    args->syn_args_live_to_model = (syn_gl_args *) malloc (sizeof(syn_gl_args));
    args->syn_args_model_to_live = (syn_gl_args *) malloc (sizeof(syn_gl_args));

    syn_gl_args * args_live_to_model_gl = (syn_gl_args *) args->syn_args_live_to_model;
    syn_gl_args * args_model_to_live_gl = (syn_gl_args *) args->syn_args_model_to_live;


    while (cur != NULL) {
    	if (xmlStrcmp(cur->name, (const xmlChar *) "g_real_to_virtual_slow") == 0) ret = parse_double(doc, cur, &(args_live_to_model_gl->g[GL_G_SLOW]), (const xmlChar*) VALUE);
		if (xmlStrcmp(cur->name, (const xmlChar *) "g_real_to_virtual_fast") == 0) ret = parse_double(doc, cur, &(args_live_to_model_gl->g[GL_G_FAST]), (const xmlChar*) VALUE);
		if (xmlStrcmp(cur->name, (const xmlChar *) "k1_real_to_virtual") == 0) ret = parse_double(doc, cur, &(args_live_to_model_gl->k1), (const xmlChar*) VALUE);
		if (xmlStrcmp(cur->name, (const xmlChar *) "k2_real_to_virtual") == 0) ret = parse_double(doc, cur, &(args_live_to_model_gl->k2), (const xmlChar*) VALUE);
		if (xmlStrcmp(cur->name, (const xmlChar *) "vfast_real_to_virtual") == 0) ret = parse_double(doc, cur, &(args_live_to_model_gl->v_fast), (const xmlChar*) VALUE);
		if (xmlStrcmp(cur->name, (const xmlChar *) "vslow_real_to_virtual") == 0) ret = parse_double(doc, cur, &(args_live_to_model_gl->v_slow), (const xmlChar*) VALUE);

    	if (xmlStrcmp(cur->name, (const xmlChar *) "g_virtual_to_real_slow") == 0) ret = parse_double(doc, cur, &(args_model_to_live_gl->g[GL_G_SLOW]), (const xmlChar*) VALUE);
		if (xmlStrcmp(cur->name, (const xmlChar *) "g_virtual_to_real_fast") == 0) ret = parse_double(doc, cur, &(args_model_to_live_gl->g[GL_G_FAST]), (const xmlChar*) VALUE);
		if (xmlStrcmp(cur->name, (const xmlChar *) "k1_virtual_to_real") == 0) ret = parse_double(doc, cur, &(args_model_to_live_gl->k1), (const xmlChar*) VALUE);
		if (xmlStrcmp(cur->name, (const xmlChar *) "k2_virtual_to_real") == 0) ret = parse_double(doc, cur, &(args_model_to_live_gl->k2), (const xmlChar*) VALUE);
		if (xmlStrcmp(cur->name, (const xmlChar *) "vfast_virtual_to_real") == 0) ret = parse_double(doc, cur, &(args_model_to_live_gl->v_fast), (const xmlChar*) VALUE);
		if (xmlStrcmp(cur->name, (const xmlChar *) "vslow_virtual_to_real") == 0) ret = parse_double(doc, cur, &(args_model_to_live_gl->v_slow), (const xmlChar*) VALUE);

		if (ret != OK) return ret;
		cur = cur->next;
	}

	return OK;
}

static int parse_clamp_synapse (xmlDocPtr doc, xmlNodePtr cur, clamp_args * args) {
	int ret = ERR;

	if ((!doc) || (!cur) || (!args)) return ERR;

	if (parse_int(doc, cur, &args->synapse, (const xmlChar*) TYPE) != OK) return ERR;


	switch(args->synapse) {
		case ELECTRIC:
			ret = parse_clamp_syn_elec(doc, cur->xmlChildrenNode, args);
			break;
		case GOLOWASCH:
			ret = parse_clamp_syn_golowasch(doc, cur->xmlChildrenNode, args);
			break;
		default:
			return ERR;
	}

	return ret;
}

static int parse_clamp_freq (xmlDocPtr doc, xmlNodePtr cur, clamp_args * args) {
	int ret = ERR;

	if ((!doc) || (!cur) || (!args)) return ERR;

	ret = parse_double(doc, cur, &args->freq, (const xmlChar*) VALUE);
	//if (ret == OK) args->freq *= 1000;

	return ret;
}

static int parse_clamp_time (xmlDocPtr doc, xmlNodePtr cur, clamp_args * args) {
	int ret = OK;
	xmlNodePtr child;

	if ((!doc) || (!cur) || (!args)) return ERR;

	child = cur->xmlChildrenNode;

	while (child != NULL) {
		if (xmlStrcmp(child->name, (const xmlChar *) BEFORE) == 0) ret = parse_int(doc, child, &args->before, (const xmlChar*) VALUE);
		if (xmlStrcmp(child->name, (const xmlChar *) DURATION) == 0) ret = parse_int(doc, child, &args->time_var, (const xmlChar*) VALUE);
		if (xmlStrcmp(child->name, (const xmlChar *) AFTER) == 0) ret = parse_int(doc, child, &args->after, (const xmlChar*) VALUE);

		if (ret != OK) return ret;

		child = child->next;
	}

	return ret;
}


static int parse_clamp_sec_per_burst (xmlDocPtr doc, xmlNodePtr cur, clamp_args * args) {
	int ret = ERR;

	if ((!doc) || (!cur) || (!args)) return ERR;

	ret = parse_double(doc, cur, &args->sec_per_burst, (const xmlChar*) VALUE);
	if (ret == 0) args->sec_per_burst = -1;

	return ret;
}


static int parse_clamp_drift (xmlDocPtr doc, xmlNodePtr cur, clamp_args * args) {
	int ret = ERR;

	if ((!doc) || (!cur) || (!args)) return ERR;

	ret = parse_int(doc, cur, &args->check_drift, (const xmlChar*) VALUE);
	if (ret == 0) args->check_drift = 1;

	return ret;
}


static int parse_clamp_important (xmlDocPtr doc, xmlNodePtr cur, clamp_args * args) {
	int ret = ERR;

	if ((!doc) || (!cur) || (!args)) return ERR;

	ret = parse_int(doc, cur, &args->imp, (const xmlChar*) VALUE);
	if (ret == 0) args->imp = 0;

	return ret;
}

static int parse_clamp_calibration (xmlDocPtr doc, xmlNodePtr cur, clamp_args * args) {
	int ret = OK;
	xmlNodePtr child;

	if ((!doc) || (!cur) || (!args)) return ERR;

	ret = parse_int(doc, cur, &args->mode_auto_cal, (const xmlChar*) TYPE);

	child = cur->xmlChildrenNode;

	switch(args->mode_auto_cal) {
		case 1:
            while (child != NULL) {
                if (xmlStrcmp(child->name, (const xmlChar*) AUTOCAL_VAL_1) == 0) ret = parse_double(doc, child, &args->auto_cal_val_1, (const xmlChar*) VALUE);

                if (ret != OK) return ret;
                child = child->next;
            }
			break;
		case 7:
			while (child != NULL) {
				if (xmlStrcmp(child->name, (const xmlChar*) SYNAPSE) == 0) ret = parse_clamp_synapse(doc, child, args);
				if (xmlStrcmp(child->name, (const xmlChar*) STEP_V_TO_R) == 0) ret = parse_double(doc, child, &args->step_v_to_r, (const xmlChar*) VALUE);
				if (xmlStrcmp(child->name, (const xmlChar*) STEP_R_TO_V) == 0) ret = parse_double(doc, child, &args->step_r_to_v, (const xmlChar*) VALUE);

				if (ret != OK) return ret;
				child = child->next;
			}

			break;
		default:
			break;
	}

	return ret;
}

static int parse_clamp_input_channels (xmlDocPtr doc, xmlNodePtr cur, clamp_args * args) {
	int ret = ERR;

	if ((!doc) || (!cur) || (!args)) return ERR;

	ret = parse_string(doc, cur, &args->input_channels, (const xmlChar*) VALUE);

	return ret;
}

static int parse_clamp_output_channels (xmlDocPtr doc, xmlNodePtr cur, clamp_args * args) {
	int ret = ERR;

	if ((!doc) || (!cur) || (!args)) return ERR;

	ret = parse_string(doc, cur, &args->output_channels, (const xmlChar*) VALUE);

	return ret;
}


static int parse_clamp_input_factor (xmlDocPtr doc, xmlNodePtr cur, clamp_args * args) {
	int ret = ERR;

	if ((!doc) || (!cur) || (!args)) return ERR;

	ret = parse_double(doc, cur, &args->input_factor, (const xmlChar*) VALUE);

	return ret;
}

static int parse_clamp_output_factor (xmlDocPtr doc, xmlNodePtr cur, clamp_args * args) {
	int ret = ERR;

	if ((!doc) || (!cur) || (!args)) return ERR;

	ret = parse_double(doc, cur, &args->output_factor, (const xmlChar*) VALUE);

	return ret;
}

