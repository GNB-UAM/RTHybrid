/**
 * @file nm_xml_cpg_model.h
 * @brief Header file for the CPG_Model neuron model functions XML parser functions.
 */

#ifndef NM_XML_CPG_MODEL_H
#define NM_XML_CPG_MODEL_H

#include "../../../common/includes/xml_parser_functions.h"

#ifdef __cplusplus
extern "C" {
#endif

#include "../Komendantov_Kononenko_1996/nm_komendantov_kononenko_1996.h"

int parse_nm_cpg_model (xmlDocPtr doc, xmlNodePtr cur, clamp_args * args);

#ifdef __cplusplus
}
#endif

#endif // NM_XML_CPG_MODEL_H
