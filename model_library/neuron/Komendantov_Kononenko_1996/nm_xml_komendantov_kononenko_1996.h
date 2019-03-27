/**
 * @file nm_xml_komendantov_kononenko_1996.h
 * @brief Header file for the Komendantov_Kononenko_1996 neuron model functions XML parser functions.
 */

#ifndef NM_XML_KOMENDANTOV_KONONENKO_1996_H
#define NM_XML_KOMENDANTOV_KONONENKO_1996_H

#include "../../../common/includes/xml_parser_functions.h"

#ifdef __cplusplus
extern "C" {
#endif

#include "nm_komendantov_kononenko_1996.h"

int parse_nm_komendantov_kononenko_1996 (xmlDocPtr doc, xmlNodePtr cur, clamp_args * args);

#ifdef __cplusplus
}
#endif

#endif // NM_XML_KOMENDANTOV_KONONENKO_1996_H