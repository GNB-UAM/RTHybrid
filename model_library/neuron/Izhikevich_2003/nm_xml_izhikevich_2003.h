/**
 * @file nm_xml_izhikevich_2003.h
 * @brief Header file for the Izhikevich neuron model XML parser functions.
 */


#ifndef NM_XML_IZHIKEVICH_2003_H
#define NM_XML_IZHIKEVICH_2003_H


#include "../../../common/includes/xml_parser_functions.h" 

#ifdef __cplusplus
extern "C" {
#endif

#include "nm_izhikevich_2003.h"

int parse_nm_izhikevich_2003 (xmlDocPtr doc, xmlNodePtr cur, clamp_args * args);

#ifdef __cplusplus
}
#endif

#endif // NM_XML_IZHIKEVICH_2003_H
 
 
