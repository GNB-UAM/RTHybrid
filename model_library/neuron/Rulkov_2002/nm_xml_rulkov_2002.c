#include "nm_xml_rulkov_2002.h"

/**
 * @file nm_xml_rulkov_2002.c
 * @brief Source file with the Rulkov neuron model functions.
 */

/**
 * @brief Imports the parameters of the Rulkov_2002 neuron model from an XML file.
 * @param[in] doc XML pointer to the document
 * @param[in] cur Cursor to navigate the XML file.
 * @param[in/out] args Pointer to the main arguments structure
 * @return #OK if it works, #ERR if there is an error
 */

int parse_nm_rulkov_2002 (xmlDocPtr doc, xmlNodePtr cur, clamp_args * args) {
	xmlNodePtr child =  NULL;
	int ret = OK;

	if ((!doc) || (!cur) || (!args)) return ERR;

	args->vars = (double*) malloc (sizeof(double) * 2);
    args->params = (double *) malloc (sizeof(double) * 8);

	while (cur != NULL) {
		if (xmlStrcmp(cur->name, (const xmlChar *) "vars") == 0) {
			child = cur->xmlChildrenNode;

			while (child != NULL) {
                if (xmlStrcmp(child->name, (const xmlChar *) "x") == 0) ret = parse_double(doc, child, &args->vars[RLK_X], (const xmlChar*) VALUE);
                if (xmlStrcmp(child->name, (const xmlChar *) "y") == 0) ret = parse_double(doc, child, &args->vars[RLK_Y], (const xmlChar*) VALUE);

				if (ret != OK) return ret;

				child = child->next;
			}
		}
		else if (xmlStrcmp(cur->name, (const xmlChar *) "params") == 0) {
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
