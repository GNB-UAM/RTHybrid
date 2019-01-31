/**
 * @file nm_xml_wang_1993.h
 * @brief Header file for the Wang neuron model functions XML parser functions.
 */


#ifndef NM_XML_WANG_1993_H
#define NM_XML_WANG_1993_H


#include "../../../common/includes/xml_parser_functions.h" 

#ifdef __cplusplus
extern "C" {
#endif

#include "nm_wang_1993.h"

int parse_nm_wang_1993 (xmlDocPtr doc, xmlNodePtr cur, clamp_args * args);

#ifdef __cplusplus
}
#endif

#endif // NM_XML_WANG_1993_H
