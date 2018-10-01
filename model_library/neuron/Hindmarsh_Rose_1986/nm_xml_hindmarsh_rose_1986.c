#include "nm_xml_hindmarsh_rose_1986.h"

/**
 * @file nm_xml_hindmarsh_rose_1986.c
 * @brief Source file with the Hindmarsh and Rose neuron model functions.
 */ 

int parse_nm_hindmarsh_rose_1986 (xmlDocPtr doc, xmlNodePtr cur, clamp_args * args) {
	xmlNodePtr child =  NULL;
	int ret = OK;

	if ((!doc) || (!cur) || (!args)) return ERR;

	args->vars = (double*) malloc (sizeof(double) * 3);
    args->params = (double *) malloc (sizeof(double) * 4);

	while (cur != NULL) {
		if (xmlStrcmp(cur->name, (const xmlChar *) "vars") == 0) {
			child = cur->xmlChildrenNode;

			while (child != NULL) {
                if (xmlStrcmp(child->name, (const xmlChar *) "x") == 0) ret = parse_double(doc, child, &args->vars[HR_X], (const xmlChar*) VALUE);
                if (xmlStrcmp(child->name, (const xmlChar *) "y") == 0) ret = parse_double(doc, child, &args->vars[HR_Y], (const xmlChar*) VALUE);
                if (xmlStrcmp(child->name, (const xmlChar *) "z") == 0) ret = parse_double(doc, child, &args->vars[HR_Z], (const xmlChar*) VALUE);

				if (ret != OK) return ret;

				child = child->next;
			}
		}
		else if (xmlStrcmp(cur->name, (const xmlChar *) "params") == 0) {
			child = cur->xmlChildrenNode;

			while (child != NULL) {
				if (xmlStrcmp(child->name, (const xmlChar *) "r") == 0) ret = parse_double(doc, child, &args->params[HR_R], (const xmlChar*) VALUE);
				if (xmlStrcmp(child->name, (const xmlChar *) "s") == 0) ret = parse_double(doc, child, &args->params[HR_S], (const xmlChar*) VALUE);
				if (xmlStrcmp(child->name, (const xmlChar *) "i") == 0) ret = parse_double(doc, child, &args->params[HR_I], (const xmlChar*) VALUE);
                if (xmlStrcmp(child->name, (const xmlChar *) "method") == 0) ret = parse_double(doc, child, &args->params[HR_DT], (const xmlChar*) VALUE);

				if (ret != OK) return ret;

				child = child->next;
			}
		}

	cur = cur->next;
	}

	return OK;
}