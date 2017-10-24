#ifdef __cplusplus
extern "C" {
#endif

#ifndef XML_CLAMP_PARSER_H__
#define XML_CLAMP_PARSER_H__

#include "../../common/includes/xml_parser_functions.h"
#include "types_clamp.h"
#include "model_library.h"

int xml_clamp_parser (char * file, clamp_args * args);

#endif // XML_CLAMP_PARSER_H__

#ifdef __cplusplus
}
#endif
