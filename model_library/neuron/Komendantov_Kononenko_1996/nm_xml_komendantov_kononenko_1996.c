#include "nm_xml_komendantov_kononenko_1996.h"

/**
 * @file nm_xml_komendantov_kononenko_1996.c
 * @brief Source file with the Komendantov_Kononenko_1996 neuron model functions.
 */

/**
 * @brief Imports the parameters of the Komendantov_Kononenko_1996 neuron model from an XML file.
 * @param[in] doc XML pointer to the document
 * @param[in] cur Cursor to navigate the XML file.
 * @param[in/out] args Pointer to the main arguments structure
 * @return #OK if it works, #ERR if there is an error
 */

int parse_nm_komendantov_kononenko_1996 (xmlDocPtr doc, xmlNodePtr cur, clamp_args * args) {
	xmlNodePtr child =  NULL;
	int ret = OK;

	if ((!doc) || (!cur) || (!args)) return ERR;

	args->vars = (double*) malloc (sizeof(double) * 8);
	args->params = (double *) malloc (sizeof(double) * 20);

	while (cur != NULL) {
		if (xmlStrcmp(cur->name, (const xmlChar *) "vars") == 0) {
			child = cur->xmlChildrenNode;

			while (child != NULL) {

				if (xmlStrcmp(child->name, (const xmlChar *) "V") == 0) ret = parse_double(doc, child, &args->vars[NM_KOMENDANTOV_KONONENKO_1996_V], (const xmlChar*) VALUE);

				if (ret != OK) return ret;

				child = child->next;
			}
		}
		else if (xmlStrcmp(cur->name, (const xmlChar *) "params") == 0) {
			child = cur->xmlChildrenNode;

			while (child != NULL) {

				if (xmlStrcmp(child->name, (const xmlChar *) "i") == 0) ret = parse_double(doc, child, &args->params[NM_KOMENDANTOV_KONONENKO_1996_I], (const xmlChar*) VALUE);
				if (xmlStrcmp(child->name, (const xmlChar *) "Cm") == 0) ret = parse_double(doc, child, &args->params[NM_KOMENDANTOV_KONONENKO_1996_CM], (const xmlChar*) VALUE);
				if (xmlStrcmp(child->name, (const xmlChar *) "g_na_v") == 0) ret = parse_double(doc, child, &args->params[NM_KOMENDANTOV_KONONENKO_1996_G_NA_V], (const xmlChar*) VALUE);
				if (xmlStrcmp(child->name, (const xmlChar *) "V_na") == 0) ret = parse_double(doc, child, &args->params[NM_KOMENDANTOV_KONONENKO_1996_V_NA], (const xmlChar*) VALUE);
				if (xmlStrcmp(child->name, (const xmlChar *) "g_k") == 0) ret = parse_double(doc, child, &args->params[NM_KOMENDANTOV_KONONENKO_1996_G_K], (const xmlChar*) VALUE);
				if (xmlStrcmp(child->name, (const xmlChar *) "V_k") == 0) ret = parse_double(doc, child, &args->params[NM_KOMENDANTOV_KONONENKO_1996_V_K], (const xmlChar*) VALUE);
				if (xmlStrcmp(child->name, (const xmlChar *) "g_na") == 0) ret = parse_double(doc, child, &args->params[NM_KOMENDANTOV_KONONENKO_1996_G_NA], (const xmlChar*) VALUE);
				if (xmlStrcmp(child->name, (const xmlChar *) "g_b") == 0) ret = parse_double(doc, child, &args->params[NM_KOMENDANTOV_KONONENKO_1996_G_B], (const xmlChar*) VALUE);
				if (xmlStrcmp(child->name, (const xmlChar *) "V_b") == 0) ret = parse_double(doc, child, &args->params[NM_KOMENDANTOV_KONONENKO_1996_V_B], (const xmlChar*) VALUE);
				if (xmlStrcmp(child->name, (const xmlChar *) "g_na_ttx") == 0) ret = parse_double(doc, child, &args->params[NM_KOMENDANTOV_KONONENKO_1996_G_NA_TTX], (const xmlChar*) VALUE);
				if (xmlStrcmp(child->name, (const xmlChar *) "g_k_tea") == 0) ret = parse_double(doc, child, &args->params[NM_KOMENDANTOV_KONONENKO_1996_G_K_TEA], (const xmlChar*) VALUE);
				if (xmlStrcmp(child->name, (const xmlChar *) "g_ca") == 0) ret = parse_double(doc, child, &args->params[NM_KOMENDANTOV_KONONENKO_1996_G_CA], (const xmlChar*) VALUE);
				if (xmlStrcmp(child->name, (const xmlChar *) "V_ca") == 0) ret = parse_double(doc, child, &args->params[NM_KOMENDANTOV_KONONENKO_1996_V_CA], (const xmlChar*) VALUE);
				if (xmlStrcmp(child->name, (const xmlChar *) "g_ca_ca") == 0) ret = parse_double(doc, child, &args->params[NM_KOMENDANTOV_KONONENKO_1996_G_CA_CA], (const xmlChar*) VALUE);
				if (xmlStrcmp(child->name, (const xmlChar *) "k_beta") == 0) ret = parse_double(doc, child, &args->params[NM_KOMENDANTOV_KONONENKO_1996_K_BETA], (const xmlChar*) VALUE);
				if (xmlStrcmp(child->name, (const xmlChar *) "beta") == 0) ret = parse_double(doc, child, &args->params[NM_KOMENDANTOV_KONONENKO_1996_BETA], (const xmlChar*) VALUE);
				if (xmlStrcmp(child->name, (const xmlChar *) "rho") == 0) ret = parse_double(doc, child, &args->params[NM_KOMENDANTOV_KONONENKO_1996_RHO], (const xmlChar*) VALUE);
				if (xmlStrcmp(child->name, (const xmlChar *) "k_s") == 0) ret = parse_double(doc, child, &args->params[NM_KOMENDANTOV_KONONENKO_1996_K_S], (const xmlChar*) VALUE);
				if (xmlStrcmp(child->name, (const xmlChar *) "method") == 0) ret = parse_double(doc, child, &args->params[NM_KOMENDANTOV_KONONENKO_1996_DT], (const xmlChar*) VALUE);

				if (ret != OK) return ret;

				child = child->next;
			}
		}

	cur = cur->next;
	}

	return OK;
}