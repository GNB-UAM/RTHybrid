/**
 * @file sm_xml_greenberg_manor_2005.h
 * @brief Header file for the Greenberg_Manor_2005 synapse model XML parser functions.
 */


#ifndef SM_XML_GREENBERG_MANOR_2005_H
#define SM_XML_GREENBERG_MANOR_2005_H


#include "../../../common/includes/xml_parser_functions.h" 

#ifdef __cplusplus
extern "C" {
#endif

#include "sm_greenberg_manor_2005.h"

int parse_sm_greenberg_manor_2005 (xmlDocPtr doc, xmlNodePtr cur, void ** syn_args);

#ifdef __cplusplus
}
#endif

#endif // SM_XML_GREENBERG_MANOR_2005_H
