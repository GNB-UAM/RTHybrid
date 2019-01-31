 /**
 * @file sm_xml_golowasch_et_al_1999.h
 * @brief Header file for the Golowasch et al. synapse model XML parser functions.
 */


#ifndef SM_XML_GOLOWASCH_ET_AL_1999_H
#define SM_XML_GOLOWASCH_ET_AL_1999_H


#include "../../../common/includes/xml_parser_functions.h"

#ifdef __cplusplus
extern "C" {
#endif

#include "sm_golowasch_et_al_1999.h"

int parse_sm_golowasch_et_al_1999 (xmlDocPtr doc, xmlNodePtr cur, void ** syn_args);

#ifdef __cplusplus
}
#endif

#endif // SM_XML_GOLOWASCH_ET_AL_1999_H
 
