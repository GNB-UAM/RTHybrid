#include "../includes/xml_parser_functions.h"


int parse_int (xmlDocPtr doc, xmlNodePtr cur, int * num, const xmlChar * label) {
	xmlChar * val = NULL;
     
    if ((!doc) || (!cur) || (!num)) return ERR;
     
    val = xmlGetProp(cur, label);
     
    if(val == NULL) return ERR;
     
    //sscanf((char*)valor, "%ld", id);
    *num = strtol(val, NULL, 10);
    xmlFree(val);
     
    return OK;
}


int parse_double (xmlDocPtr doc, xmlNodePtr cur, double * num, const xmlChar * label) {
	xmlChar * val = NULL;
     
    if ((!doc) || (!cur) || (!num)) return ERR;
     
    val = xmlGetProp(cur, label);
     
    if(val == NULL) return ERR;
     
    //sscanf((char*)valor, "%ld", id);
    *num = strtof(val, NULL);
    xmlFree(val);
     
    return OK;
}


int parse_string (xmlDocPtr doc, xmlNodePtr cur, char * str, const xmlChar * label) {
	xmlChar * val = NULL;
     
    if ((!doc) || (!cur) || (!str)) return ERR;
     
    val = xmlGetProp(cur, label);
     
    if(val == NULL) return ERR;
    
    str = (char *) malloc (xmlStrlen(val) + 1);
    strcpy(str, (char *) val);
    xmlFree(val);
     
    return OK;
}