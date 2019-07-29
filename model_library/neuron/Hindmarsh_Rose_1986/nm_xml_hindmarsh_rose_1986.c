#include "nm_xml_hindmarsh_rose_1986.h"

/**
 * @file nm_xml_hindmarsh_rose_1986.c
 * @brief Source file with the Hindmarsh_Rose_1986 neuron model functions.
 */

/**
 * @brief Imports the parameters of the Hindmarsh_Rose_1986 neuron model from an XML file.
 * @param[in] doc XML pointer to the document
 * @param[in] cur Cursor to navigate the XML file.
 * @param[in/out] args Pointer to the main arguments structure
 * @return #OK if it works, #ERR if there is an error
 */

int parse_nm_hindmarsh_rose_1986 (xmlDocPtr doc, xmlNodePtr cur, clamp_args * args) {
	xmlNodePtr child =  NULL;
	int ret = OK;

	if ((!doc) || (!cur) || (!args)) return ERR;

	args->vars = (double*) malloc (sizeof(double) * 3);
	args->params = (double *) malloc (sizeof(double) * 10);

	while (cur != NULL) {
		if (xmlStrcmp(cur->name, (const xmlChar *) "vars") == 0) {
			child = cur->xmlChildrenNode;

			while (child != NULL) {

                if (xmlStrcmp(child->name, (const xmlChar *) "x") == 0) ret = parse_double(doc, child, &args->vars[NM_HINDMARSH_ROSE_1986_V], (const xmlChar*) VALUE);
				if (xmlStrcmp(child->name, (const xmlChar *) "y") == 0) ret = parse_double(doc, child, &args->vars[NM_HINDMARSH_ROSE_1986_Y], (const xmlChar*) VALUE);
				if (xmlStrcmp(child->name, (const xmlChar *) "z") == 0) ret = parse_double(doc, child, &args->vars[NM_HINDMARSH_ROSE_1986_Z], (const xmlChar*) VALUE);
				if (ret != OK) return ret;

				child = child->next;
			}
		}
		else if (xmlStrcmp(cur->name, (const xmlChar *) "params") == 0) {
			child = cur->xmlChildrenNode;

			while (child != NULL) {

				if (xmlStrcmp(child->name, (const xmlChar *) "b") == 0) ret = parse_double(doc, child, &args->params[NM_HINDMARSH_ROSE_1986_B], (const xmlChar*) VALUE);
				if (xmlStrcmp(child->name, (const xmlChar *) "a") == 0) ret = parse_double(doc, child, &args->params[NM_HINDMARSH_ROSE_1986_A], (const xmlChar*) VALUE);
                if (xmlStrcmp(child->name, (const xmlChar *) "i") == 0) ret = parse_double(doc, child, &args->params[NM_HINDMARSH_ROSE_1986_I], (const xmlChar*) VALUE);
				if (xmlStrcmp(child->name, (const xmlChar *) "c") == 0) ret = parse_double(doc, child, &args->params[NM_HINDMARSH_ROSE_1986_C], (const xmlChar*) VALUE);
				if (xmlStrcmp(child->name, (const xmlChar *) "d") == 0) ret = parse_double(doc, child, &args->params[NM_HINDMARSH_ROSE_1986_D], (const xmlChar*) VALUE);
				if (xmlStrcmp(child->name, (const xmlChar *) "r") == 0) ret = parse_double(doc, child, &args->params[NM_HINDMARSH_ROSE_1986_R], (const xmlChar*) VALUE);
				if (xmlStrcmp(child->name, (const xmlChar *) "s") == 0) ret = parse_double(doc, child, &args->params[NM_HINDMARSH_ROSE_1986_S], (const xmlChar*) VALUE);
				if (xmlStrcmp(child->name, (const xmlChar *) "xr") == 0) ret = parse_double(doc, child, &args->params[NM_HINDMARSH_ROSE_1986_XR], (const xmlChar*) VALUE);
				if (xmlStrcmp(child->name, (const xmlChar *) "method") == 0) ret = parse_double(doc, child, &args->params[NM_HINDMARSH_ROSE_1986_DT], (const xmlChar*) VALUE);

				if (ret != OK) return ret;

				child = child->next;
			}
		}

	cur = cur->next;
	}

	return OK;
}
