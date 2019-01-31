/**
 * @file nm_xml_rulkov_2002.h
 * @brief Header file for the Rulkov neuron model functions XML parser functions.
 */


#ifndef NM_XML_RULKOV_2002_H
#define NM_XML_RULKOV_2002_H


#include "../../../common/includes/xml_parser_functions.h" 

#ifdef __cplusplus
extern "C" {
#endif

#include "nm_rulkov_2002.h"

int parse_nm_rulkov_2002 (xmlDocPtr doc, xmlNodePtr cur, clamp_args * args);

#ifdef __cplusplus
}
#endif

#endif // NM_XML_RULKOV_2002_H
