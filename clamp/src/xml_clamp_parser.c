#include "../includes/xml_clamp_parser.h"

/*CLAMP PARSER DEFINITIONS */

#define CLAMP "clamp"
#define MODEL "model"
#define SYNAPSE "synapse"
#define FREQ "freq"
#define TIME_VAR "time_war"
#define ANTI "anti"
#define IMP "imp"
#define CALIB "calib"
#define INPUT "input"
#define OUTPUT "output"

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

#define VALUE "val"
#define TYPE "type"





/*CLAMP PARSER FUNCTIONS */
static int parse_clamp_model_iz (xmlDocPtr doc, xmlNodePtr cur, clamp_args * args);
static int parse_clamp_model_hr (xmlDocPtr doc, xmlNodePtr cur, clamp_args * args);
static int parse_clamp_model_rlk (xmlDocPtr doc, xmlNodePtr cur, clamp_args * args);
static int parse_clamp_model (xmlDocPtr doc, xmlNodePtr cur, clamp_args * args);
static int parse_clamp_synapse (xmlDocPtr doc, xmlNodePtr cur, clamp_args * args);
static int parse_clamp_freq (xmlDocPtr doc, xmlNodePtr cur, clamp_args * args);
static int parse_clamp_time (xmlDocPtr doc, xmlNodePtr cur, clamp_args * args);
static int parse_clamp_antiphase (xmlDocPtr doc, xmlNodePtr cur, clamp_args * args);
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
        else if (xmlStrcmp(cur->name, (const xmlChar*) TIME_VAR) == 0) {
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
				if (xmlStrcmp(child->name, (const xmlChar *) SIGMA) == 0) ret = parse_double(doc, child, &args->params[MU_RLK], (const xmlChar*) VALUE);
				if (xmlStrcmp(child->name, (const xmlChar *) MU) == 0) ret = parse_double(doc, child, &args->params[SIGMA_RLK], (const xmlChar*) VALUE);
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

static int parse_clamp_synapse (xmlDocPtr doc, xmlNodePtr cur, clamp_args * args) {
	int ret = ERR;

	return OK;
}

static int parse_clamp_freq (xmlDocPtr doc, xmlNodePtr cur, clamp_args * args) {
	int ret = ERR;

	return OK;
}

static int parse_clamp_time (xmlDocPtr doc, xmlNodePtr cur, clamp_args * args) {
	int ret = ERR;

	return OK;
}

static int parse_clamp_antiphase (xmlDocPtr doc, xmlNodePtr cur, clamp_args * args) {
	int ret = ERR;

	return OK;
}

static int parse_clamp_important (xmlDocPtr doc, xmlNodePtr cur, clamp_args * args) {
	int ret = ERR;

	return OK;
}

static int parse_clamp_calibration (xmlDocPtr doc, xmlNodePtr cur, clamp_args * args) {
	int ret = ERR;

	return OK;
}

static int parse_clamp_input (xmlDocPtr doc, xmlNodePtr cur, clamp_args * args) {
	int ret = ERR;

	return OK;
}

static int parse_clamp_output (xmlDocPtr doc, xmlNodePtr cur, clamp_args * args) {
	int ret = ERR;

	return OK;
}
