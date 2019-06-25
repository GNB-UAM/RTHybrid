#include "nm_xml_bluetooth.h"

/**
 * @file nm_xml_bluetooth.c
 * @brief Source file with the Bluetooth neuron model functions.
 */

/**
 * @brief Imports the parameters of the Bluetooth neuron model from an XML file.
 * @param[in] doc XML pointer to the document
 * @param[in] cur Cursor to navigate the XML file.
 * @param[in/out] args Pointer to the main arguments structure
 * @return #OK if it works, #ERR if there is an error
 */

int parse_nm_bluetooth (xmlDocPtr doc, xmlNodePtr cur, clamp_args * args) {
	xmlNodePtr child =  NULL;
	int ret = OK;

	if ((!doc) || (!cur) || (!args)) return ERR;

	args->vars = (double*) malloc (sizeof(double) * NM_BLUETOOTH_N_VARS);
	args->params = (double *) malloc (sizeof(double) * NM_BLUETOOTH_N_PARAMS);

	while (cur != NULL) {
		if (xmlStrcmp(cur->name, (const xmlChar *) "vars") == 0) {
			child = cur->xmlChildrenNode;

			while (child != NULL) {

				if (xmlStrcmp(child->name, (const xmlChar *) "n1") == 0) ret = parse_double(doc, child, &args->vars[NM_BLUETOOTH_N1], (const xmlChar*) VALUE);
				if (xmlStrcmp(child->name, (const xmlChar *) "n2") == 0) ret = parse_double(doc, child, &args->vars[NM_BLUETOOTH_N2], (const xmlChar*) VALUE);
				if (ret != OK) return ret;

				child = child->next;
			}
		}
		else if (xmlStrcmp(cur->name, (const xmlChar *) "params") == 0) {
			child = cur->xmlChildrenNode;

			while (child != NULL) {

				if (xmlStrcmp(child->name, (const xmlChar *) "method") == 0) ret = parse_double(doc, child, &args->params[NM_BLUETOOTH_DT], (const xmlChar*) VALUE);

				if (ret != OK) return ret;

				child = child->next;
			}
		}

	cur = cur->next;
	}

	return OK;
}