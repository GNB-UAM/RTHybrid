#include "sm_xml_destexhe_et_al_1994.h"

/**
 * @file sm_xml_destexhe_et_al_1994.c
 * @brief Source file with the Destexhe_et_al_1994 synapse model XML parser functions.
 */ 

/**
 * @brief Imports the parameters of the Destexhe_et_al_1994 synapse model from an XML file.
 * @param[in] doc XML pointer to the document
 * @param[in] cur Cursor to navigate the XML file.
 * @param[in/out] syn_args Pointer to the synapse arguments structure
 * @return #OK if it works, #ERR if there is an error
 */

int parse_sm_destexhe_et_al_1994 (xmlDocPtr doc, xmlNodePtr cur, void ** syn_args) {
	int ret = OK;
	double pulse_duration, freq, e_syn_per, alpha, beta;

	if ((!doc) || (!cur) || (!syn_args)) return ERR;

	(*syn_args) = (sm_destexhe_et_al_1994_args *) malloc (sizeof(sm_destexhe_et_al_1994_args));

    sm_destexhe_et_al_1994_args * aux_args = (sm_destexhe_et_al_1994_args *) (*syn_args);


    while (cur != NULL) {
		if (xmlStrcmp(cur->name, (const xmlChar *) "g") == 0) ret = parse_double(doc, cur, &(aux_args->g[SM_DESTEXHE_ET_AL_1994_G]), (const xmlChar*) VALUE);
		if (xmlStrcmp(cur->name, (const xmlChar *) "e_syn") == 0) ret = parse_double(doc, cur, &(e_syn_per), (const xmlChar*) VALUE);

		if (xmlStrcmp(cur->name, (const xmlChar *) "alpha") == 0) ret = parse_double(doc, cur, &(alpha), (const xmlChar*) VALUE);
		if (xmlStrcmp(cur->name, (const xmlChar *) "beta") == 0) ret = parse_double(doc, cur, &(beta), (const xmlChar*) VALUE);

		if (xmlStrcmp(cur->name, (const xmlChar *) "tmax") == 0) ret = parse_double(doc, cur, &(aux_args->tmax), (const xmlChar*) VALUE);
		if (xmlStrcmp(cur->name, (const xmlChar *) "pulse_duration") == 0) ret = parse_double(doc, cur, &(pulse_duration), (const xmlChar*) VALUE);
		if (xmlStrcmp(cur->name, (const xmlChar *) "freq") == 0) ret = parse_double(doc, cur, &(freq), (const xmlChar*) VALUE);


		if (ret != OK) return ret;

		cur = cur->next;
	}

	aux_args->pulse_duration = pulse_duration * freq;
	aux_args->e_syn_per = e_syn_per / 100.0;
	aux_args->alpha = (alpha / 1000.0) * freq;
	aux_args->beta = (beta / 1000.0) * freq;

	return OK;

}
