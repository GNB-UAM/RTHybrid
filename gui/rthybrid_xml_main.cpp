#include "rthybrid_xml_main.h"
#include "../clamp/includes/xml_clamp_parser.h"
#include "../clamp/includes/clamp.h"

rthybrid_xml_main::rthybrid_xml_main()
{

}

int rthybrid_xml_main::xml_init(char * file) {
    clamp_args args;

    if (xml_clamp_parser(file, &args) == ERR) {
        return ERR;
    }

    return clamp(&args);
    /*clamp_launcher cl;
    return cl.start(&args);*/
}
