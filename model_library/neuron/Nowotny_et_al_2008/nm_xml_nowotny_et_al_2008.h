/**
 * @file nm_xml_nowotny_et_al_2008.h
 * @brief Header file for the Nowotny_et_al_2008 neuron model functions XML parser functions.
 */

#ifndef NM_XML_NOWOTNY_ET_AL_2008_H
#define NM_XML_NOWOTNY_ET_AL_2008_H

#include "../../../common/includes/xml_parser_functions.h"

#ifdef __cplusplus
extern "C" {
#endif

#include "nm_nowotny_et_al_2008.h"

int parse_nm_nowotny_et_al_2008 (xmlDocPtr doc, xmlNodePtr cur, clamp_args * args);

#ifdef __cplusplus
}
#endif

#endif // NM_XML_NOWOTNY_ET_AL_2008_H