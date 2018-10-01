#include "sm_xml_electrical.h"

/**
 * @file sm_xml_electrical.c
 * @brief Source file with the Electrical synapse model XML parser functions.
 */ 

int parse_sm_electrical (xmlDocPtr doc, xmlNodePtr cur, void ** syn_args) {
	int ret = OK;
	int antiphase = 0;

	if ((!doc) || (!cur) || (!syn_args)) return ERR;

	(*syn_args) = (syn_elec_args *) malloc (sizeof(syn_elec_args));

    syn_elec_args * args_elec = (syn_elec_args *) (*syn_args);


    while (cur != NULL) {
		if (xmlStrcmp(cur->name, (const xmlChar *) "g") == 0) ret = parse_double(doc, cur, &(args_elec->g[ELEC_G]), (const xmlChar*) VALUE);
		if (xmlStrcmp(cur->name, (const xmlChar *) "antiphase") == 0) ret = parse_int(doc, cur, &antiphase, (const xmlChar*) VALUE);

		if (antiphase) {
	        args_elec->anti = -1;
	    } else {
	        args_elec->anti = 1;
	    }

		if (ret != OK) return ret;

		cur = cur->next;
	}

	return OK;

}