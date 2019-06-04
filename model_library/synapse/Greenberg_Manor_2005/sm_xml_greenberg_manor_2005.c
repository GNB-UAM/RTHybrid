#include "sm_xml_greenberg_manor_2005.h"

/**
 * @file sm_xml_greenberg_manor_2005.c
 * @brief Source file with the Greenberg_Manor_2005 synapse model XML parser functions.
 */ 

/**
 * @brief Imports the parameters of the Greenberg_Manor_2005 synapse model from an XML file.
 * @param[in] doc XML pointer to the document
 * @param[in] cur Cursor to navigate the XML file.
 * @param[in/out] syn_args Pointer to the synapse arguments structure
 * @return #OK if it works, #ERR if there is an error
 */

int parse_sm_greenberg_manor_2005 (xmlDocPtr doc, xmlNodePtr cur, void ** syn_args) {
	int ret = OK;

	if ((!doc) || (!cur) || (!syn_args)) return ERR;

	(*syn_args) = (sm_greenberg_manor_2005_args *) malloc (sizeof(sm_greenberg_manor_2005_args));

    sm_greenberg_manor_2005_args * aux_args = (sm_greenberg_manor_2005_args *) (*syn_args);

    while (cur != NULL) {
		if (xmlStrcmp(cur->name, (const xmlChar *) "g") == 0) ret = parse_double(doc, cur, &(aux_args->g[SM_GREENBERG_MANOR_2005_G]), (const xmlChar*) VALUE);
		if (xmlStrcmp(cur->name, (const xmlChar *) "e_syn") == 0) ret = parse_double(doc, cur, &(aux_args->e_syn_per), (const xmlChar*) VALUE);

		if (xmlStrcmp(cur->name, (const xmlChar *) "p") == 0) ret = parse_double(doc, cur, &(aux_args->p), (const xmlChar*) VALUE);
		if (xmlStrcmp(cur->name, (const xmlChar *) "k_m") == 0) ret = parse_double(doc, cur, &(aux_args->k_m), (const xmlChar*) VALUE);
		if (xmlStrcmp(cur->name, (const xmlChar *) "v12_m") == 0) ret = parse_double(doc, cur, &(aux_args->v12_m), (const xmlChar*) VALUE);
		if (xmlStrcmp(cur->name, (const xmlChar *) "tau_hi_m") == 0) ret = parse_double(doc, cur, &(aux_args->tau_hi_m), (const xmlChar*) VALUE);
		if (xmlStrcmp(cur->name, (const xmlChar *) "tau_lo_m") == 0) ret = parse_double(doc, cur, &(aux_args->tau_lo_m), (const xmlChar*) VALUE);

		if (xmlStrcmp(cur->name, (const xmlChar *) "q") == 0) ret = parse_double(doc, cur, &(aux_args->q), (const xmlChar*) VALUE);
		if (xmlStrcmp(cur->name, (const xmlChar *) "k_h") == 0) ret = parse_double(doc, cur, &(aux_args->k_h), (const xmlChar*) VALUE);
		if (xmlStrcmp(cur->name, (const xmlChar *) "v12_h") == 0) ret = parse_double(doc, cur, &(aux_args->v12_h), (const xmlChar*) VALUE);
		if (xmlStrcmp(cur->name, (const xmlChar *) "tau_hi_h") == 0) ret = parse_double(doc, cur, &(aux_args->tau_hi_h), (const xmlChar*) VALUE);
		if (xmlStrcmp(cur->name, (const xmlChar *) "tau_lo_h") == 0) ret = parse_double(doc, cur, &(aux_args->tau_lo_h), (const xmlChar*) VALUE);

		if (ret != OK) return ret;

		cur = cur->next;
	}

	return OK;

}
