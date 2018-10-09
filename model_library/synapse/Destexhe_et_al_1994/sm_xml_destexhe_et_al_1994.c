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

	if ((!doc) || (!cur) || (!syn_args)) return ERR;

	(*syn_args) = (destexhe_et_al_1994_args *) malloc (sizeof(destexhe_et_al_1994_args));

    destexhe_et_al_1994_args * aux_args = (destexhe_et_al_1994_args *) (*syn_args);


    while (cur != NULL) {
		//if (xmlStrcmp(cur->name, (const xmlChar *) "g") == 0) ret = parse_double(doc, cur, &(aux_args->g[DESTEXHE_ET_AL_1994_G]), (const xmlChar*) VALUE);

		//TODO

		if (ret != OK) return ret;

		cur = cur->next;
	}

	return OK;

}
