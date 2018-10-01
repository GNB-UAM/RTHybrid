#include "nm_xml_ghigliazza_holmes_2004.h"

/**
 * @file nm_xml_ghigliazza_holmes_2004.c
 * @brief Source file with the Ghigliazza and Holmes model functions.
 */ 

int parse_nm_ghigliazza_holmes_2004 (xmlDocPtr doc, xmlNodePtr cur, clamp_args * args) {
    xmlNodePtr child =  NULL;
    int ret = OK;

    if ((!doc) || (!cur) || (!args)) return ERR;

    args->vars = (double*) malloc (sizeof(double) * 3);
    args->params = (double *) malloc (sizeof(double) * 18);

    while (cur != NULL) {
        if (xmlStrcmp(cur->name, (const xmlChar *) "vars") == 0) {
            child = cur->xmlChildrenNode;

            while (child != NULL) {
                if (xmlStrcmp(child->name, (const xmlChar *) "v") == 0) ret = parse_double(doc, child, &args->vars[GH_V], (const xmlChar*) VALUE);

                if (ret != OK) return ret;

                child = child->next;
            }
        }
        else if (xmlStrcmp(cur->name, (const xmlChar *) "params") == 0) {
            child = cur->xmlChildrenNode;

            while (child != NULL) {
                if (xmlStrcmp(child->name, (const xmlChar *) "gca") == 0) ret = parse_double(doc, child, &args->params[GH_G_CA], (const xmlChar*) VALUE);
                if (xmlStrcmp(child->name, (const xmlChar *) "eca") == 0) ret = parse_double(doc, child, &args->params[GH_E_CA], (const xmlChar*) VALUE);
                if (xmlStrcmp(child->name, (const xmlChar *) "vthca") == 0) ret = parse_double(doc, child, &args->params[GH_VTH_CA], (const xmlChar*) VALUE);
                if (xmlStrcmp(child->name, (const xmlChar *) "kca") == 0) ret = parse_double(doc, child, &args->params[GH_K_CA], (const xmlChar*) VALUE);

                if (xmlStrcmp(child->name, (const xmlChar *) "gk") == 0) ret = parse_double(doc, child, &args->params[GH_G_K], (const xmlChar*) VALUE);
                if (xmlStrcmp(child->name, (const xmlChar *) "ek") == 0) ret = parse_double(doc, child, &args->params[GH_E_K], (const xmlChar*) VALUE);
                if (xmlStrcmp(child->name, (const xmlChar *) "vthk") == 0) ret = parse_double(doc, child, &args->params[GH_VTH_K], (const xmlChar*) VALUE);
                if (xmlStrcmp(child->name, (const xmlChar *) "kk") == 0) ret = parse_double(doc, child, &args->params[GH_K_K], (const xmlChar*) VALUE);

                if (xmlStrcmp(child->name, (const xmlChar *) "gks") == 0) ret = parse_double(doc, child, &args->params[GH_G_KS], (const xmlChar*) VALUE);
                if (xmlStrcmp(child->name, (const xmlChar *) "vthks") == 0) ret = parse_double(doc, child, &args->params[GH_VTH_KS], (const xmlChar*) VALUE);
                if (xmlStrcmp(child->name, (const xmlChar *) "kks") == 0) ret = parse_double(doc, child, &args->params[GH_K_KS], (const xmlChar*) VALUE);

                if (xmlStrcmp(child->name, (const xmlChar *) "gl") == 0) ret = parse_double(doc, child, &args->params[GH_G_L], (const xmlChar*) VALUE);
                if (xmlStrcmp(child->name, (const xmlChar *) "el") == 0) ret = parse_double(doc, child, &args->params[GH_E_L], (const xmlChar*) VALUE);

                if (xmlStrcmp(child->name, (const xmlChar *) "c") == 0) ret = parse_double(doc, child, &args->params[GH_CM], (const xmlChar*) VALUE);
                if (xmlStrcmp(child->name, (const xmlChar *) "epsilon") == 0) ret = parse_double(doc, child, &args->params[GH_EPSILON], (const xmlChar*) VALUE);
                if (xmlStrcmp(child->name, (const xmlChar *) "delta") == 0) ret = parse_double(doc, child, &args->params[GH_DELTA], (const xmlChar*) VALUE);
                if (xmlStrcmp(child->name, (const xmlChar *) "i") == 0) ret = parse_double(doc, child, &args->params[GH_I], (const xmlChar*) VALUE);

                if (xmlStrcmp(child->name, (const xmlChar *) "method") == 0) ret = parse_double(doc, child, &args->params[GH_DT], (const xmlChar*) VALUE);

                if (ret != OK) return ret;

                child = child->next;
            }
        }

    cur = cur->next;
    }

    return OK;
}