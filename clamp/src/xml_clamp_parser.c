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
#define INPUT "input"
#define OUTPUT "output"
#define FIRING "firing_rate"
#define AUTOCAL_VAL_1 "autocal_val_1"

#define VARS "vars"
#define X_VAR "x"
#define Y_VAR "y"
#define Z_VAR "z"
#define PARAMS "params"
#define A "a"
#define B "b"
#define C "c"
#define D "d"
#define R "r"
#define S "s"
#define ALPHA "alpha"
#define SIGMA "sigma"
#define MU "mu"
#define I "i"

#define G_VIRTUAL_TO_REAL "g_virtual_to_real"
#define G_VIRTUAL_TO_REAL_SLOW "g_virtual_to_real_slow"
#define G_VIRTUAL_TO_REAL_FAST "g_virtual_to_real_fast"
#define G_REAL_TO_VIRTUAL "g_real_to_virtual"
#define G_REAL_TO_VIRTUAL_SLOW "g_real_to_virtual_slow"
#define G_REAL_TO_VIRTUAL_FAST "g_real_to_virtual_fast"
#define SYN_GRADUAL_K1 "syn_gradual_k1"
#define SYN_GRADUAL_K2 "syn_gradual_k2"
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
static int parse_clamp_syn_chem (xmlDocPtr doc, xmlNodePtr cur, clamp_args * args);
static int parse_clamp_freq (xmlDocPtr doc, xmlNodePtr cur, clamp_args * args);
static int parse_clamp_time (xmlDocPtr doc, xmlNodePtr cur, clamp_args * args);
static int parse_clamp_antiphase (xmlDocPtr doc, xmlNodePtr cur, clamp_args * args);
static int parse_clamp_firing_rate (xmlDocPtr doc, xmlNodePtr cur, clamp_args * args);
static int parse_clamp_important (xmlDocPtr doc, xmlNodePtr cur, clamp_args * args);
static int parse_clamp_calibration (xmlDocPtr doc, xmlNodePtr cur, clamp_args * args);
static int parse_clamp_input (xmlDocPtr doc, xmlNodePtr cur, clamp_args * args);
static int parse_clamp_output (xmlDocPtr doc, xmlNodePtr cur, clamp_args * args);


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


    args->input = NULL;
    args->output = NULL;

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
        else if (xmlStrcmp(cur->name, (const xmlChar*) ANTI) == 0) {
            ret = parse_clamp_antiphase(doc, cur, args);
        }
        else if (xmlStrcmp(cur->name, (const xmlChar*) IMP) == 0) {
            ret = parse_clamp_important(doc, cur, args);
        }
        else if (xmlStrcmp(cur->name, (const xmlChar*) CALIB) == 0) {
            ret = parse_clamp_calibration(doc, cur, args);
        }
        else if (xmlStrcmp(cur->name, (const xmlChar*) INPUT) == 0) {
            ret = parse_clamp_input(doc, cur, args);
        }
        else if (xmlStrcmp(cur->name, (const xmlChar*) OUTPUT) == 0) {
            ret = parse_clamp_output(doc, cur, args);
        }
        else if (xmlStrcmp(cur->name, (const xmlChar*) FIRING) == 0) {
            ret = parse_clamp_firing_rate(doc, cur, args);
        }

        if (ret != OK) break;

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
    args->params = (double *) malloc (sizeof(double) * 5);

	while (cur != NULL) {
		if (xmlStrcmp(cur->name, (const xmlChar *) VARS) == 0) {
			child = cur->xmlChildrenNode;

			while (child != NULL) {
				if (xmlStrcmp(child->name, (const xmlChar *) X_VAR) == 0) ret = parse_double(doc, child, &args->vars[X], (const xmlChar*) VALUE);
				if (xmlStrcmp(child->name, (const xmlChar *) Y_VAR) == 0) ret = parse_double(doc, child, &args->vars[Y], (const xmlChar*) VALUE);

				if (ret != OK) return ret;

				child = child->next;
			}
		}
		else if (xmlStrcmp(cur->name, (const xmlChar *) PARAMS) == 0) {
			child = cur->xmlChildrenNode;

			while (child != NULL) {
				if (xmlStrcmp(child->name, (const xmlChar *) A) == 0) ret = parse_double(doc, child, &args->params[A_IZ], (const xmlChar*) VALUE);
				if (xmlStrcmp(child->name, (const xmlChar *) B) == 0) ret = parse_double(doc, child, &args->params[B_IZ], (const xmlChar*) VALUE);
				if (xmlStrcmp(child->name, (const xmlChar *) C) == 0) ret = parse_double(doc, child, &args->params[C_IZ], (const xmlChar*) VALUE);
				if (xmlStrcmp(child->name, (const xmlChar *) D) == 0) ret = parse_double(doc, child, &args->params[D_IZ], (const xmlChar*) VALUE);
				if (xmlStrcmp(child->name, (const xmlChar *) I) == 0) ret = parse_double(doc, child, &args->params[I_IZ], (const xmlChar*) VALUE);

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
    args->params = (double *) malloc (sizeof(double) * 3);

	while (cur != NULL) {
		if (xmlStrcmp(cur->name, (const xmlChar *) VARS) == 0) {
			child = cur->xmlChildrenNode;

			while (child != NULL) {
				if (xmlStrcmp(child->name, (const xmlChar *) X_VAR) == 0) ret = parse_double(doc, child, &args->vars[X], (const xmlChar*) VALUE);
				if (xmlStrcmp(child->name, (const xmlChar *) Y_VAR) == 0) ret = parse_double(doc, child, &args->vars[Y], (const xmlChar*) VALUE);
				if (xmlStrcmp(child->name, (const xmlChar *) Z_VAR) == 0) ret = parse_double(doc, child, &args->vars[Z], (const xmlChar*) VALUE);

				if (ret != OK) return ret;

				child = child->next;
			}
		}
		else if (xmlStrcmp(cur->name, (const xmlChar *) PARAMS) == 0) {
			child = cur->xmlChildrenNode;

			while (child != NULL) {
				if (xmlStrcmp(child->name, (const xmlChar *) R) == 0) ret = parse_double(doc, child, &args->params[R_HR], (const xmlChar*) VALUE);
				if (xmlStrcmp(child->name, (const xmlChar *) S) == 0) ret = parse_double(doc, child, &args->params[S_HR], (const xmlChar*) VALUE);
				if (xmlStrcmp(child->name, (const xmlChar *) I) == 0) ret = parse_double(doc, child, &args->params[I_HR], (const xmlChar*) VALUE);

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
				if (xmlStrcmp(child->name, (const xmlChar *) X_VAR) == 0) ret = parse_double(doc, child, &args->vars[X], (const xmlChar*) VALUE);
				if (xmlStrcmp(child->name, (const xmlChar *) Y_VAR) == 0) ret = parse_double(doc, child, &args->vars[Y], (const xmlChar*) VALUE);

				if (ret != OK) return ret;

				child = child->next;
			}
		}
		else if (xmlStrcmp(cur->name, (const xmlChar *) PARAMS) == 0) {
			child = cur->xmlChildrenNode;

			while (child != NULL) {
				if (xmlStrcmp(child->name, (const xmlChar *) ALPHA) == 0) ret = parse_double(doc, child, &args->params[ALPHA_RLK], (const xmlChar*) VALUE);
				if (xmlStrcmp(child->name, (const xmlChar *) MU) == 0) ret = parse_double(doc, child, &args->params[MU_RLK], (const xmlChar*) VALUE);
				if (xmlStrcmp(child->name, (const xmlChar *) SIGMA) == 0) ret = parse_double(doc, child, &args->params[SIGMA_RLK], (const xmlChar*) VALUE);
				if (xmlStrcmp(child->name, (const xmlChar *) I) == 0) ret = parse_double(doc, child, &args->params[I_RLK], (const xmlChar*) VALUE);

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
		case IZHIKEVICH:
			ret = parse_clamp_model_iz(doc, cur->xmlChildrenNode, args);
			break;
		case HR:
			ret = parse_clamp_model_hr(doc, cur->xmlChildrenNode, args);
			break;
		case RLK:
			ret = parse_clamp_model_rlk(doc, cur->xmlChildrenNode, args);
			break;
		default:
			return ERR;
	}

	return ret;
}


static int parse_clamp_syn_elec (xmlDocPtr doc, xmlNodePtr cur, clamp_args * args) {
	xmlNodePtr child =  NULL;
	int ret = OK;

	if ((!doc) || (!cur) || (!args)) return ERR;

	args->g_virtual_to_real = (double *) malloc (sizeof(double) * 1);
    args->g_real_to_virtual = (double *) malloc (sizeof(double) * 1);


    while (cur != NULL) {
		if (xmlStrcmp(cur->name, (const xmlChar *) G_VIRTUAL_TO_REAL) == 0) ret = parse_double(doc, cur, &args->g_virtual_to_real[0], (const xmlChar*) VALUE);
		if (xmlStrcmp(cur->name, (const xmlChar *) G_REAL_TO_VIRTUAL) == 0) ret = parse_double(doc, cur, &args->g_real_to_virtual[0], (const xmlChar*) VALUE);

		if (ret != OK) return ret;


		cur = cur->next;
	}

	return OK;

}


static int parse_clamp_syn_chem (xmlDocPtr doc, xmlNodePtr cur, clamp_args * args) {
	xmlNodePtr child =  NULL;
	int ret = OK;

	if ((!doc) || (!cur) || (!args)) return ERR;

	args->g_virtual_to_real = (double *) malloc (sizeof(double) * 2);
    args->g_real_to_virtual = (double *) malloc (sizeof(double) * 2);


    while (cur != NULL) {
		if (xmlStrcmp(cur->name, (const xmlChar *) G_VIRTUAL_TO_REAL_SLOW) == 0) ret = parse_double(doc, cur, &args->g_virtual_to_real[G_SLOW], (const xmlChar*) VALUE);
		if (xmlStrcmp(cur->name, (const xmlChar *) G_VIRTUAL_TO_REAL_FAST) == 0) ret = parse_double(doc, cur, &args->g_virtual_to_real[G_FAST], (const xmlChar*) VALUE);
		if (xmlStrcmp(cur->name, (const xmlChar *) G_REAL_TO_VIRTUAL_SLOW) == 0) ret = parse_double(doc, cur, &args->g_real_to_virtual[G_SLOW], (const xmlChar*) VALUE);
		if (xmlStrcmp(cur->name, (const xmlChar *) G_REAL_TO_VIRTUAL_FAST) == 0) ret = parse_double(doc, cur, &args->g_real_to_virtual[G_FAST], (const xmlChar*) VALUE);

		if (xmlStrcmp(cur->name, (const xmlChar *) SYN_GRADUAL_K1) == 0) ret = parse_double(doc, cur, &args->syn_gradual_k1, (const xmlChar*) VALUE);
		if (xmlStrcmp(cur->name, (const xmlChar *) SYN_GRADUAL_K2) == 0) ret = parse_double(doc, cur, &args->syn_gradual_k2, (const xmlChar*) VALUE);

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
		case CHEMICAL:
			ret = parse_clamp_syn_chem(doc, cur->xmlChildrenNode, args);
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
	args->freq *= 1000;

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

static int parse_clamp_antiphase (xmlDocPtr doc, xmlNodePtr cur, clamp_args * args) {
	int ret = ERR;

	if ((!doc) || (!cur) || (!args)) return ERR;

	ret = parse_int(doc, cur, &args->anti, (const xmlChar*) VALUE);

	return ret;
}


static int parse_clamp_firing_rate (xmlDocPtr doc, xmlNodePtr cur, clamp_args * args) {
	int ret = ERR;

	if ((!doc) || (!cur) || (!args)) return ERR;

	ret = parse_double(doc, cur, &args->firing_rate, (const xmlChar*) VALUE);

	return ret;
}

static int parse_clamp_important (xmlDocPtr doc, xmlNodePtr cur, clamp_args * args) {
	int ret = ERR;

	if ((!doc) || (!cur) || (!args)) return ERR;

	ret = parse_int(doc, cur, &args->imp, (const xmlChar*) VALUE);

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

static int parse_clamp_input (xmlDocPtr doc, xmlNodePtr cur, clamp_args * args) {
	int ret = ERR;

	if ((!doc) || (!cur) || (!args)) return ERR;

	ret = parse_string(doc, cur, &args->input, (const xmlChar*) VALUE);

	return ret;
}

static int parse_clamp_output (xmlDocPtr doc, xmlNodePtr cur, clamp_args * args) {
	int ret = ERR;

	if ((!doc) || (!cur) || (!args)) return ERR;

	ret = parse_string(doc, cur, &args->output, (const xmlChar*) VALUE);

	return ret;
}
