#include "nm_xml_ghigliazza_holmes_2004.h"

/**
 * @file nm_xml_ghigliazza_holmes_2004.c
 * @brief Source file with the Ghigliazza_Holmes_2004 neuron model functions.
 */

/**
 * @brief Imports the parameters of the Ghigliazza_Holmes_2004 neuron model from an XML file.
 * @param[in] doc XML pointer to the document
 * @param[in] cur Cursor to navigate the XML file.
 * @param[in/out] args Pointer to the main arguments structure
 * @return #OK if it works, #ERR if there is an error
 */

int parse_nm_ghigliazza_holmes_2004 (xmlDocPtr doc, xmlNodePtr cur, clamp_args * args) {
	xmlNodePtr child =  NULL;
	int ret = OK;

	if ((!doc) || (!cur) || (!args)) return ERR;

	args->vars = (double*) malloc (sizeof(double) * 3);
	args->params = (double *) malloc (sizeof(double) * 19);

	while (cur != NULL) {
		if (xmlStrcmp(cur->name, (const xmlChar *) "vars") == 0) {
			child = cur->xmlChildrenNode;

			while (child != NULL) {

                if (xmlStrcmp(child->name, (const xmlChar *) "v") == 0) ret = parse_double(doc, child, &args->vars[NM_GHIGLIAZZA_HOLMES_2004_V], (const xmlChar*) VALUE);
				if (ret != OK) return ret;

				child = child->next;
			}
		}
		else if (xmlStrcmp(cur->name, (const xmlChar *) "params") == 0) {
			child = cur->xmlChildrenNode;

			while (child != NULL) {

                if (xmlStrcmp(child->name, (const xmlChar *) "i") == 0) ret = parse_double(doc, child, &args->params[NM_GHIGLIAZZA_HOLMES_2004_I], (const xmlChar*) VALUE);
				if (xmlStrcmp(child->name, (const xmlChar *) "Cm") == 0) ret = parse_double(doc, child, &args->params[NM_GHIGLIAZZA_HOLMES_2004_CM], (const xmlChar*) VALUE);
				if (xmlStrcmp(child->name, (const xmlChar *) "epsilon") == 0) ret = parse_double(doc, child, &args->params[NM_GHIGLIAZZA_HOLMES_2004_EPSILON], (const xmlChar*) VALUE);
				if (xmlStrcmp(child->name, (const xmlChar *) "delta") == 0) ret = parse_double(doc, child, &args->params[NM_GHIGLIAZZA_HOLMES_2004_DELTA], (const xmlChar*) VALUE);
				if (xmlStrcmp(child->name, (const xmlChar *) "gca") == 0) ret = parse_double(doc, child, &args->params[NM_GHIGLIAZZA_HOLMES_2004_GCA], (const xmlChar*) VALUE);
				if (xmlStrcmp(child->name, (const xmlChar *) "eca") == 0) ret = parse_double(doc, child, &args->params[NM_GHIGLIAZZA_HOLMES_2004_ECA], (const xmlChar*) VALUE);
				if (xmlStrcmp(child->name, (const xmlChar *) "gk") == 0) ret = parse_double(doc, child, &args->params[NM_GHIGLIAZZA_HOLMES_2004_GK], (const xmlChar*) VALUE);
				if (xmlStrcmp(child->name, (const xmlChar *) "ek") == 0) ret = parse_double(doc, child, &args->params[NM_GHIGLIAZZA_HOLMES_2004_EK], (const xmlChar*) VALUE);
				if (xmlStrcmp(child->name, (const xmlChar *) "gks") == 0) ret = parse_double(doc, child, &args->params[NM_GHIGLIAZZA_HOLMES_2004_GKS], (const xmlChar*) VALUE);
				if (xmlStrcmp(child->name, (const xmlChar *) "gl") == 0) ret = parse_double(doc, child, &args->params[NM_GHIGLIAZZA_HOLMES_2004_GL], (const xmlChar*) VALUE);
				if (xmlStrcmp(child->name, (const xmlChar *) "el") == 0) ret = parse_double(doc, child, &args->params[NM_GHIGLIAZZA_HOLMES_2004_EL], (const xmlChar*) VALUE);
				if (xmlStrcmp(child->name, (const xmlChar *) "kk") == 0) ret = parse_double(doc, child, &args->params[NM_GHIGLIAZZA_HOLMES_2004_KK], (const xmlChar*) VALUE);
				if (xmlStrcmp(child->name, (const xmlChar *) "vthk") == 0) ret = parse_double(doc, child, &args->params[NM_GHIGLIAZZA_HOLMES_2004_VTHK], (const xmlChar*) VALUE);
				if (xmlStrcmp(child->name, (const xmlChar *) "kks") == 0) ret = parse_double(doc, child, &args->params[NM_GHIGLIAZZA_HOLMES_2004_KKS], (const xmlChar*) VALUE);
				if (xmlStrcmp(child->name, (const xmlChar *) "vthks") == 0) ret = parse_double(doc, child, &args->params[NM_GHIGLIAZZA_HOLMES_2004_VTHKS], (const xmlChar*) VALUE);
				if (xmlStrcmp(child->name, (const xmlChar *) "kca") == 0) ret = parse_double(doc, child, &args->params[NM_GHIGLIAZZA_HOLMES_2004_KCA], (const xmlChar*) VALUE);
				if (xmlStrcmp(child->name, (const xmlChar *) "vthca") == 0) ret = parse_double(doc, child, &args->params[NM_GHIGLIAZZA_HOLMES_2004_VTHCA], (const xmlChar*) VALUE);
				if (xmlStrcmp(child->name, (const xmlChar *) "method") == 0) ret = parse_double(doc, child, &args->params[NM_GHIGLIAZZA_HOLMES_2004_DT], (const xmlChar*) VALUE);

				if (ret != OK) return ret;

				child = child->next;
			}
		}

	cur = cur->next;
	}

	return OK;
}
