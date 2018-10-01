/*#ifdef __cplusplus
extern "C" {
#endif*/

#ifndef XML_PARSER_FUNCTIONS_H__
#define XML_PARSER_FUNCTIONS_H__

#include "types.h"
#include <libxml/xmlmemory.h>
#include <libxml/parser.h>

#define VALUE "val"
#define TYPE "type"

int parse_int (xmlDocPtr doc, xmlNodePtr cur, int * num, const xmlChar * label);
int parse_double (xmlDocPtr doc, xmlNodePtr cur, double * num, const xmlChar * label);
int parse_string (xmlDocPtr doc, xmlNodePtr cur, char ** str, const xmlChar * label);


#endif // XML_PARSER_FUNCTIONS_H__

/*#ifdef __cplusplus
}
#endif*/
