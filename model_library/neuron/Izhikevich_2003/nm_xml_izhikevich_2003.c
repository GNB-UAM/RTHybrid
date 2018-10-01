#include "nm_xml_izhikevich_2003.h"

/**
 * @file nm_xml_izhikevich_2003.c
 * @brief Source file with the Izhikevich neuron model XML parser functions.
 */ 

int parse_nm_izhikevich_2003 (xmlDocPtr doc, xmlNodePtr cur, clamp_args * args) {
	xmlNodePtr child =  NULL;
	int ret = OK;

	if ((!doc) || (!cur) || (!args)) return ERR;

	args->vars = (double*) malloc (sizeof(double) * 2);
    args->params = (double *) malloc (sizeof(double) * 6);

	while (cur != NULL) {
		if (xmlStrcmp(cur->name, (const xmlChar *) "vars") == 0) {
			child = cur->xmlChildrenNode;

			while (child != NULL) {
                if (xmlStrcmp(child->name, (const xmlChar *) "v") == 0) ret = parse_double(doc, child, &args->vars[IZ_V], (const xmlChar*) VALUE);
                if (xmlStrcmp(child->name, (const xmlChar *) "u") == 0) ret = parse_double(doc, child, &args->vars[IZ_U], (const xmlChar*) VALUE);

				if (ret != OK) return ret;

				child = child->next;
			}
		}
		else if (xmlStrcmp(cur->name, (const xmlChar *) "params") == 0) {
			child = cur->xmlChildrenNode;

			while (child != NULL) {
				if (xmlStrcmp(child->name, (const xmlChar *) "a") == 0) ret = parse_double(doc, child, &args->params[IZ_A], (const xmlChar*) VALUE);
				if (xmlStrcmp(child->name, (const xmlChar *) "b") == 0) ret = parse_double(doc, child, &args->params[IZ_B], (const xmlChar*) VALUE);
				if (xmlStrcmp(child->name, (const xmlChar *) "c") == 0) ret = parse_double(doc, child, &args->params[IZ_C], (const xmlChar*) VALUE);
				if (xmlStrcmp(child->name, (const xmlChar *) "d") == 0) ret = parse_double(doc, child, &args->params[IZ_D], (const xmlChar*) VALUE);
				if (xmlStrcmp(child->name, (const xmlChar *) "i") == 0) ret = parse_double(doc, child, &args->params[IZ_I], (const xmlChar*) VALUE);

                if (xmlStrcmp(child->name, (const xmlChar *) "method") == 0) ret = parse_double(doc, child, &args->params[IZ_DT], (const xmlChar*) VALUE);

				if (ret != OK) return ret;

				child = child->next;
			}
		}

	cur = cur->next;
	}

	return OK;
}