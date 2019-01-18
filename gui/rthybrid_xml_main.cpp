#include "rthybrid_xml_main.h"
#include "../clamp/includes/xml_clamp_parser.h"
#include "../clamp/includes/clamp.h"

rthybrid_xml_main::rthybrid_xml_main()
{

}

int rthybrid_xml_main::xml_init(char * file) {
    clamp_args args;

    time_t t;
    struct tm tm;
    char * hour = NULL;

    if (xml_clamp_parser(file, &args) == ERR) {
        printf("Error when parsing file %s\n", file);
        return ERR;
    }


    t = time(NULL);
    tm = *localtime(&t);

    asprintf(&(args.data_path), "data/%dy_%dm_%dd", tm.tm_year + 1900, tm.tm_mon + 1, tm.tm_mday);


    struct stat st = {0};

    if (stat("data", &st) == -1) {
        mkdir("data", 0777);
    }

    if (stat(args.data_path, &st) == -1) {
        mkdir(args.data_path, 0777);
    }

    asprintf(&hour, "/%dh_%dm_%ds", tm.tm_hour, tm.tm_min, tm.tm_sec);
    asprintf(&(args.filename), "%s%s", args.data_path, hour);

    printf("- File: %s\n", args.filename);
    fflush(NULL);

    free_pointers(1, &hour);

    return clamp(&args);
    /*clamp_launcher cl;
    return cl.start(&args);*/
}
