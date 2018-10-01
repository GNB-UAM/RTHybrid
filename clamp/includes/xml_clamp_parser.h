/*#ifdef __cplusplus
extern "C" {
#endif*/

#ifndef XML_CLAMP_PARSER_H__
#define XML_CLAMP_PARSER_H__

#include "../../common/includes/xml_parser_functions.h"
#include "types_clamp.h"
#include "../../model_library/neuron/neuron_models_functions.h"
#include "../../model_library/synapse/synapse_models_functions.h"

#include "../../model_library/xml_models.h"

#ifdef __cplusplus
extern "C" {
#endif

int xml_clamp_parser (char * file, clamp_args * args);

#ifdef __cplusplus
}
#endif

#endif // XML_CLAMP_PARSER_H__

/*#ifdef __cplusplus
}
#endif*/
