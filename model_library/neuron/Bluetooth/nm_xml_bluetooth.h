/**
 * @file nm_xml_bluetooth.h
 * @brief Header file for the Bluetooth neuron model functions XML parser functions.
 */

#ifndef NM_XML_BLUETOOTH_H
#define NM_XML_BLUETOOTH_H

#include "../../../common/includes/xml_parser_functions.h"

#ifdef __cplusplus
extern "C" {
#endif

#include "nm_bluetooth.h"

int parse_nm_bluetooth (xmlDocPtr doc, xmlNodePtr cur, clamp_args * args);

#ifdef __cplusplus
}
#endif

#endif // NM_XML_BLUETOOTH_H