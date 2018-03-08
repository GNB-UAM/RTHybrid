#ifdef __cplusplus
extern "C" {
#endif

#ifndef XML_CLAMP_PARSER_H__
#define XML_CLAMP_PARSER_H__

#include "../../common/includes/xml_parser_functions.h"
#include "types_clamp.h"
#include "neuron_models_functions.h"
#include "synapse_models_functions.h"

int xml_clamp_parser (char * file, clamp_args * args);

#endif // XML_CLAMP_PARSER_H__

#ifdef __cplusplus
}
#endif
