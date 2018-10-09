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
		//if (xmlStrcmp(cur->name, (const xmlChar *) "g") == 0) ret = parse_double(doc, cur, &(aux_args->g[GREENBERG_MANOR_2005_G]), (const xmlChar*) VALUE);

		//TODO

		if (ret != OK) return ret;

		cur = cur->next;
	}

	return OK;

}
