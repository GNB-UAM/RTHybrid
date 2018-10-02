#include "nm_xml_wang_1993.h"

/**
 * @file nm_xml_wang_1993.c
 * @brief Source file with the Wang neuron model functions.
 */

/**
 * @brief Imports the parameters of the Wang_1993 neuron model from an XML file.
 * @param[in] doc XML pointer to the document
 * @param[in] cur Cursor to navigate the XML file.
 * @param[in/out] args Pointer to the main arguments structure
 * @return #OK if it works, #ERR if there is an error
 */

int parse_nm_wang_1993 (xmlDocPtr doc, xmlNodePtr cur, clamp_args * args) {
    xmlNodePtr child =  NULL;
    int ret = OK;

    if ((!doc) || (!cur) || (!args)) return ERR;

    args->vars = (double*) malloc (sizeof(double) * 6);
    args->params = (double *) malloc (sizeof(double) * 15);

    while (cur != NULL) {
        if (xmlStrcmp(cur->name, (const xmlChar *) "vars") == 0) {
            child = cur->xmlChildrenNode;

            while (child != NULL) {
                if (xmlStrcmp(child->name, (const xmlChar *) "v") == 0) ret = parse_double(doc, child, &args->vars[WANG_V], (const xmlChar*) VALUE);

                if (ret != OK) return ret;

                child = child->next;
            }
        }
        else if (xmlStrcmp(cur->name, (const xmlChar *) "params") == 0) {
            child = cur->xmlChildrenNode;

            while (child != NULL) {
                if (xmlStrcmp(child->name, (const xmlChar *) "g_na") == 0) ret = parse_double(doc, child, &args->params[WANG_G_NA], (const xmlChar*) VALUE);
                if (xmlStrcmp(child->name, (const xmlChar *) "v_na") == 0) ret = parse_double(doc, child, &args->params[WANG_V_NA], (const xmlChar*) VALUE);
                if (xmlStrcmp(child->name, (const xmlChar *) "g_nap") == 0) ret = parse_double(doc, child, &args->params[WANG_G_NAP], (const xmlChar*) VALUE);

                if (xmlStrcmp(child->name, (const xmlChar *) "g_k") == 0) ret = parse_double(doc, child, &args->params[WANG_G_K], (const xmlChar*) VALUE);
                if (xmlStrcmp(child->name, (const xmlChar *) "v_k") == 0) ret = parse_double(doc, child, &args->params[WANG_V_K], (const xmlChar*) VALUE);
                if (xmlStrcmp(child->name, (const xmlChar *) "g_ks") == 0) ret = parse_double(doc, child, &args->params[WANG_G_KS], (const xmlChar*) VALUE);

                if (xmlStrcmp(child->name, (const xmlChar *) "g_l") == 0) ret = parse_double(doc, child, &args->params[WANG_G_L], (const xmlChar*) VALUE);
                if (xmlStrcmp(child->name, (const xmlChar *) "v_l") == 0) ret = parse_double(doc, child, &args->params[WANG_V_L], (const xmlChar*) VALUE);

                if (xmlStrcmp(child->name, (const xmlChar *) "cm") == 0) ret = parse_double(doc, child, &args->params[WANG_CM], (const xmlChar*) VALUE);
                if (xmlStrcmp(child->name, (const xmlChar *) "sigma") == 0) ret = parse_double(doc, child, &args->params[WANG_SIGMA], (const xmlChar*) VALUE);
                if (xmlStrcmp(child->name, (const xmlChar *) "rho") == 0) ret = parse_double(doc, child, &args->params[WANG_RHO], (const xmlChar*) VALUE);
                if (xmlStrcmp(child->name, (const xmlChar *) "phi") == 0) ret = parse_double(doc, child, &args->params[WANG_PHI], (const xmlChar*) VALUE);
                if (xmlStrcmp(child->name, (const xmlChar *) "taum") == 0) ret = parse_double(doc, child, &args->params[WANG_TAUM], (const xmlChar*) VALUE);
                if (xmlStrcmp(child->name, (const xmlChar *) "i") == 0) ret = parse_double(doc, child, &args->params[WANG_I], (const xmlChar*) VALUE);

                if (xmlStrcmp(child->name, (const xmlChar *) "method") == 0) ret = parse_double(doc, child, &args->params[WANG_DT], (const xmlChar*) VALUE);

                if (ret != OK) return ret;

                child = child->next;
            }
        }

    cur = cur->next;
    }

    return OK;
}
