#include "sm_xml_golowasch_et_al_1999.h"

/**
 * @file sm_xml_golowasch_et_al_1999.c
 * @brief Source file with the Golowasch et al. synapse model XML parser functions.
 */ 

/**
 * @brief Imports the parameters of the Golowasch et al. 1999 synapse model from an XML file.
 * @param[in] doc XML pointer to the document
 * @param[in] cur Cursor to navigate the XML file.
 * @param[in/out] syn_args Pointer to the synapse arguments structure
 * @return #OK if it works, #ERR if there is an error
 */

int parse_sm_golowasch_et_al_1999 (xmlDocPtr doc, xmlNodePtr cur, void ** syn_args) {
	int ret = OK;

	if ((!doc) || (!cur) || (!syn_args)) return ERR;

    (*syn_args) = (syn_gl_args *) malloc (sizeof(syn_gl_args));
    syn_gl_args * args_gl = (syn_gl_args *) (*syn_args);


    while (cur != NULL) {
    	if (xmlStrcmp(cur->name, (const xmlChar *) "g_slow") == 0) ret = parse_double(doc, cur, &(args_gl->g[GL_G_SLOW]), (const xmlChar*) VALUE);
    	if (xmlStrcmp(cur->name, (const xmlChar *) "vth_slow") == 0) ret = parse_double(doc, cur, &(args_gl->v_slow), (const xmlChar*) VALUE);
    	if (xmlStrcmp(cur->name, (const xmlChar *) "s_slow") == 0) ret = parse_double(doc, cur, &(args_gl->s_slow), (const xmlChar*) VALUE);
    	if (xmlStrcmp(cur->name, (const xmlChar *) "k1_slow") == 0) ret = parse_double(doc, cur, &(args_gl->k1), (const xmlChar*) VALUE);
		if (xmlStrcmp(cur->name, (const xmlChar *) "k2_slow") == 0) ret = parse_double(doc, cur, &(args_gl->k2), (const xmlChar*) VALUE);

		if (xmlStrcmp(cur->name, (const xmlChar *) "g_fast") == 0) ret = parse_double(doc, cur, &(args_gl->g[GL_G_FAST]), (const xmlChar*) VALUE);
		if (xmlStrcmp(cur->name, (const xmlChar *) "vth_fast") == 0) ret = parse_double(doc, cur, &(args_gl->v_fast), (const xmlChar*) VALUE);
		if (xmlStrcmp(cur->name, (const xmlChar *) "s_fast") == 0) ret = parse_double(doc, cur, &(args_gl->s_fast), (const xmlChar*) VALUE);
		
		if (ret != OK) return ret;
		cur = cur->next;
	}

	return OK;
}

