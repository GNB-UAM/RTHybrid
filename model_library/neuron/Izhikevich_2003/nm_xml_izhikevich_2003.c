#include "nm_xml_izhikevich_2003.h"

/**
 * @file nm_xml_izhikevich_2003.c
 * @brief Source file with the Izhikevich_2003 neuron model functions.
 */

/**
 * @brief Imports the parameters of the Izhikevich_2003 neuron model from an XML file.
 * @param[in] doc XML pointer to the document
 * @param[in] cur Cursor to navigate the XML file.
 * @param[in/out] args Pointer to the main arguments structure
 * @return #OK if it works, #ERR if there is an error
 */

int parse_nm_izhikevich_2003 (xmlDocPtr doc, xmlNodePtr cur, clamp_args * args) {
	xmlNodePtr child =  NULL;
	int ret = OK;

	if ((!doc) || (!cur) || (!args)) return ERR;

	args->vars = (double*) malloc (sizeof(double) * 2);
	args->params = (double *) malloc (sizeof(double) * 7);

	while (cur != NULL) {
		if (xmlStrcmp(cur->name, (const xmlChar *) "vars") == 0) {
			child = cur->xmlChildrenNode;

			while (child != NULL) {

				if (xmlStrcmp(child->name, (const xmlChar *) "v") == 0) ret = parse_double(doc, child, &args->vars[NM_IZHIKEVICH_2003_V], (const xmlChar*) VALUE);
				if (xmlStrcmp(child->name, (const xmlChar *) "u") == 0) ret = parse_double(doc, child, &args->vars[NM_IZHIKEVICH_2003_U], (const xmlChar*) VALUE);
				if (ret != OK) return ret;

				child = child->next;
			}
		}
		else if (xmlStrcmp(cur->name, (const xmlChar *) "params") == 0) {
			child = cur->xmlChildrenNode;

			while (child != NULL) {

                if (xmlStrcmp(child->name, (const xmlChar *) "i") == 0) ret = parse_double(doc, child, &args->params[NM_IZHIKEVICH_2003_I], (const xmlChar*) VALUE);
				if (xmlStrcmp(child->name, (const xmlChar *) "a") == 0) ret = parse_double(doc, child, &args->params[NM_IZHIKEVICH_2003_A], (const xmlChar*) VALUE);
				if (xmlStrcmp(child->name, (const xmlChar *) "b") == 0) ret = parse_double(doc, child, &args->params[NM_IZHIKEVICH_2003_B], (const xmlChar*) VALUE);
				if (xmlStrcmp(child->name, (const xmlChar *) "d") == 0) ret = parse_double(doc, child, &args->params[NM_IZHIKEVICH_2003_D], (const xmlChar*) VALUE);
				if (xmlStrcmp(child->name, (const xmlChar *) "c") == 0) ret = parse_double(doc, child, &args->params[NM_IZHIKEVICH_2003_C], (const xmlChar*) VALUE);
				if (xmlStrcmp(child->name, (const xmlChar *) "method") == 0) ret = parse_double(doc, child, &args->params[NM_IZHIKEVICH_2003_DT], (const xmlChar*) VALUE);

				if (ret != OK) return ret;

				child = child->next;
			}
		}

	cur = cur->next;
	}

	return OK;
}
