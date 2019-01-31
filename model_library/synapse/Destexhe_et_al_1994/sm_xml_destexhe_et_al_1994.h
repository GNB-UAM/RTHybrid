/**
 * @file sm_xml_destexhe_et_al_1994.h
 * @brief Header file for the Destexhe_et_al_1994 synapse model XML parser functions.
 */


#ifndef SM_XML_DESTEXHE_ET_AL_1994_H
#define SM_XML_DESTEXHE_ET_AL_1994_H


#include "../../../common/includes/xml_parser_functions.h" 

#ifdef __cplusplus
extern "C" {
#endif

#include "sm_destexhe_et_al_1994.h"

int parse_sm_destexhe_et_al_1994 (xmlDocPtr doc, xmlNodePtr cur, void ** syn_args);

#ifdef __cplusplus
}
#endif

#endif // SM_XML_DESTEXHE_ET_AL_1994_H
