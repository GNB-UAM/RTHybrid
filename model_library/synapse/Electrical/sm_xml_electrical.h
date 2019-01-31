/**
 * @file sm_xml_electrical.h
 * @brief Header file for the Electrical synapse model XML parser functions.
 */


#ifndef SM_XML_ELECTRICAL_H
#define SM_XML_ELECTRICAL_H


#include "../../../common/includes/xml_parser_functions.h" 

#ifdef __cplusplus
extern "C" {
#endif

#include "sm_electrical.h"

int parse_sm_electrical (xmlDocPtr doc, xmlNodePtr cur, void ** syn_args);

#ifdef __cplusplus
}
#endif

#endif // SM_XML_ELECTRICAL_H
 
