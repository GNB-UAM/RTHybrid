/**
 * @file nm_xml_ghigliazza_holmes_2004.h
 * @brief Header file for the Ghigliazza and Holmes model functions XML parser functions.
 */


#ifndef NM_XML_GHIGLIAZZA_HOLMES_2004_H
#define NM_XML_GHIGLIAZZA_HOLMES_2004_H


#include "../../../common/includes/xml_parser_functions.h" 

#ifdef __cplusplus
extern "C" {
#endif

#include "nm_ghigliazza_holmes_2004.h"

int parse_nm_ghigliazza_holmes_2004 (xmlDocPtr doc, xmlNodePtr cur, clamp_args * args);

#ifdef __cplusplus
}
#endif

#endif // NM_XML_GHIGLIAZZA_HOLMES_2004_H