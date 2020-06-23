#include "../includes/xml_clamp_parser.h"

/*CLAMP PARSER DEFINITIONS */

#define CLAMP "clamp"
#define NEURON "neuron"
#define SYNAPSE_MTOL "synapse_mtol"
#define SYNAPSE_LTOM "synapse_ltom"
#define FREQ "freq"
#define TIMES "times"
#define BEFORE "before"
#define DURATION "duration"
#define AFTER "after"
#define OBSERVATION "observation"
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


/*CLAMP PARSER FUNCTIONS */
static int parse_clamp_nm (xmlDocPtr doc, xmlNodePtr cur, clamp_args * args);
static int parse_clamp_synapse_ltom (xmlDocPtr doc, xmlNodePtr cur, clamp_args * args);
static int parse_clamp_synapse_mtol (xmlDocPtr doc, xmlNodePtr cur, clamp_args * args);
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
        if (xmlStrcmp(cur->name, (const xmlChar*) NEURON) == 0) {
            ret = parse_clamp_nm(doc, cur, args);
            if (ret == ERR) fprintf(stderr, "Error when parsing neuron model\n");
        }
        else if (xmlStrcmp(cur->name, (const xmlChar*) SYNAPSE_MTOL) == 0) {
        	ret = parse_clamp_synapse_mtol(doc, cur, args);
            if (ret == ERR) fprintf(stderr, "Error when parsing model to living synapse model\n");
        }
        else if (xmlStrcmp(cur->name, (const xmlChar*) SYNAPSE_LTOM) == 0) {
        	ret = parse_clamp_synapse_ltom(doc, cur, args);
            if (ret == ERR) fprintf(stderr, "Error when parsing living to model synapse model\n");
        }
        else if (xmlStrcmp(cur->name, (const xmlChar*) FREQ) == 0) {
        	ret = parse_clamp_freq(doc, cur, args);
            if (ret == ERR) fprintf(stderr, "Error when parsing the frequency\n");
        }
        else if (xmlStrcmp(cur->name, (const xmlChar*) TIMES) == 0) {
            ret = parse_clamp_time(doc, cur, args);
            if (ret == ERR) fprintf(stderr, "Error when parsing times\n");
        }
        else if (xmlStrcmp(cur->name, (const xmlChar*) DRIFT) == 0) {
            ret = parse_clamp_drift(doc, cur, args);
            if (ret == ERR) fprintf(stderr, "Error when parsing drift compensation\n");
        }
        else if (xmlStrcmp(cur->name, (const xmlChar*) IMP) == 0) {
            ret = parse_clamp_important(doc, cur, args);
            if (ret == ERR) fprintf(stderr, "Error when parsing important\n");
        }
        else if (xmlStrcmp(cur->name, (const xmlChar*) CALIB) == 0) {
            ret = parse_clamp_calibration(doc, cur, args);
            if (ret == ERR) fprintf(stderr, "Error when parsing calibration\n");
        }
        else if (xmlStrcmp(cur->name, (const xmlChar*) INPUT_CHANNELS) == 0) {
            ret = parse_clamp_input_channels(doc, cur, args);
            if (ret == ERR) fprintf(stderr, "Error when parsing input channels\n");
        }
        else if (xmlStrcmp(cur->name, (const xmlChar*) OUTPUT_CHANNELS) == 0) {
            ret = parse_clamp_output_channels(doc, cur, args);
            if (ret == ERR) fprintf(stderr, "Error when parsing output channels\n");
        }
        else if (xmlStrcmp(cur->name, (const xmlChar*) INPUT_FACTOR) == 0) {
            ret = parse_clamp_input_factor(doc, cur, args);
            if (ret == ERR) fprintf(stderr, "Error when parsing input factor\n");
        }
        else if (xmlStrcmp(cur->name, (const xmlChar*) OUTPUT_FACTOR) == 0) {
            ret = parse_clamp_output_factor(doc, cur, args);
            if (ret == ERR) fprintf(stderr, "Error when parsing output factor\n");
        }
        else if (xmlStrcmp(cur->name, (const xmlChar*) FIRING) == 0) {
            ret = parse_clamp_sec_per_burst(doc, cur, args);
            if (ret == ERR) fprintf(stderr, "Error when parsing firing rate\n");
        }

        if (ret == ERR) break;

        cur = cur->next;
    }


    xmlFreeDoc(doc);
    return ret;

}



static int parse_clamp_nm (xmlDocPtr doc, xmlNodePtr cur, clamp_args * args) {
	int ret = ERR;

	if ((!doc) || (!cur) || (!args)) return ERR;

	if (parse_int(doc, cur, &args->model, (const xmlChar*) TYPE) != OK) return ERR;


	switch(args->model) {
        case NM_EMPTY:
            ret = OK;
            break;
        case NM_IZHIKEVICH_2003:
            ret = parse_nm_izhikevich_2003(doc, cur->xmlChildrenNode, args);
			break;
        case NM_HINDMARSH_ROSE_1986:
            ret = parse_nm_hindmarsh_rose_1986(doc, cur->xmlChildrenNode, args);
			break;
        case NM_RULKOV_2002:
            ret = parse_nm_rulkov_2002(doc, cur->xmlChildrenNode, args);
			break;
        case NM_GHIGLIAZZA_HOLMES_2004:
            ret = parse_nm_ghigliazza_holmes_2004(doc, cur->xmlChildrenNode, args);
			break;
        case NM_WANG_1993:
            ret = parse_nm_wang_1993(doc, cur->xmlChildrenNode, args);
            break;
        case NM_KOMENDANTOV_KONONENKO_1996:
            ret = parse_nm_komendantov_kononenko_1996(doc, cur->xmlChildrenNode, args);
            break;
        case NM_NOWOTNY_ET_AL_2008:
            ret = parse_nm_nowotny_et_al_2008(doc, cur->xmlChildrenNode, args);
            break;
	default:
	    return ERR;
	}

	return ret;
}


static int parse_clamp_synapse_mtol (xmlDocPtr doc, xmlNodePtr cur, clamp_args * args) {
	int ret = ERR;

	if ((!doc) || (!cur) || (!args)) return ERR;

    if (parse_int(doc, cur, &args->synapse_mtol, (const xmlChar*) TYPE) != OK) return ERR;


    switch(args->synapse_mtol) {
        case SM_EMPTY:
            ret = OK;
            break;
        case SM_ELECTRICAL:
			ret = parse_sm_electrical(doc, cur->xmlChildrenNode, &(args->syn_args_model_to_live));
			break;
        case SM_GOLOWASCH_ET_AL_1999:
			ret = parse_sm_golowasch_et_al_1999(doc, cur->xmlChildrenNode, &(args->syn_args_model_to_live));
			break;
        case SM_DESTEXHE_ET_AL_1994:
            ret = parse_sm_destexhe_et_al_1994(doc, cur->xmlChildrenNode, &(args->syn_args_model_to_live));
            break;
        case SM_GREENBERG_MANOR_2005:
            ret = parse_sm_golowasch_et_al_1999(doc, cur->xmlChildrenNode, &(args->syn_args_model_to_live));
            break;
		default:
			return ERR;
	}

	return ret;
}

static int parse_clamp_synapse_ltom (xmlDocPtr doc, xmlNodePtr cur, clamp_args * args) {
	int ret = ERR;

	if ((!doc) || (!cur) || (!args)) return ERR;

    if (parse_int(doc, cur, &args->synapse_ltom, (const xmlChar*) TYPE) != OK) return ERR;


    switch(args->synapse_ltom) {
        case SM_EMPTY:
            ret = OK;
            break;
        case SM_ELECTRICAL:
			ret = parse_sm_electrical(doc, cur->xmlChildrenNode, &(args->syn_args_live_to_model));
			break;
        case SM_GOLOWASCH_ET_AL_1999:
			ret = parse_sm_golowasch_et_al_1999(doc, cur->xmlChildrenNode, &(args->syn_args_live_to_model));
			break;
        case SM_DESTEXHE_ET_AL_1994:
            ret = parse_sm_destexhe_et_al_1994(doc, cur->xmlChildrenNode, &(args->syn_args_live_to_model));
            break;
        case SM_GREENBERG_MANOR_2005:
            ret = parse_sm_greenberg_manor_2005(doc, cur->xmlChildrenNode, &(args->syn_args_live_to_model));
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
        if (xmlStrcmp(child->name, (const xmlChar *) OBSERVATION) == 0) ret = parse_int(doc, child, &args->observation, (const xmlChar*) VALUE);

		if (ret != OK) return ret;

		child = child->next;
	}

	return ret;
}


static int parse_clamp_sec_per_burst (xmlDocPtr doc, xmlNodePtr cur, clamp_args * args) {
	int ret = ERR;

	if ((!doc) || (!cur) || (!args)) return ERR;

	ret = parse_double(doc, cur, &args->sec_per_burst, (const xmlChar*) VALUE);

    if (ret == -2) args->sec_per_burst = -1;

	return ret;
}


static int parse_clamp_drift (xmlDocPtr doc, xmlNodePtr cur, clamp_args * args) {
	int ret = ERR;

	if ((!doc) || (!cur) || (!args)) return ERR;

	ret = parse_int(doc, cur, &args->check_drift, (const xmlChar*) VALUE);
    if (ret == -2) args->check_drift = 1;

	return ret;
}


static int parse_clamp_important (xmlDocPtr doc, xmlNodePtr cur, clamp_args * args) {
	int ret = ERR;

	if ((!doc) || (!cur) || (!args)) return ERR;

	ret = parse_int(doc, cur, &args->imp, (const xmlChar*) VALUE);
    if (ret == -2) args->imp = 0;

	return ret;
}

static int parse_clamp_calibration (xmlDocPtr doc, xmlNodePtr cur, clamp_args * args) {
	int ret = OK;
	xmlNodePtr child;

	if ((!doc) || (!cur) || (!args)) return ERR;

	ret = parse_int(doc, cur, &args->mode_auto_cal, (const xmlChar*) TYPE);

	child = cur->xmlChildrenNode;

	/*switch(args->mode_auto_cal) {
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
	}*/

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

