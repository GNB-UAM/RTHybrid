/**
 * @file nm_xml_hindmarsh_rose_1986.h
 * @brief Header file for the Hindmarsh and Rose neuron model functions XML parser functions.
 */


#ifndef NM_XML_HINDMARSH_ROSE_1986_H
#define NM_XML_HINDMARSH_ROSE_1986_H


#include "../../../common/includes/xml_parser_functions.h" 

#ifdef __cplusplus
extern "C" {
#endif

#include "nm_hindmarsh_rose_1986.h"

int parse_nm_hindmarsh_rose_1986 (xmlDocPtr doc, xmlNodePtr cur, clamp_args * args);

#ifdef __cplusplus
}
#endif

#endif // NM_XML_HINDMARSH_ROSE_1986_H
