#ifndef TYPES_H__
#define TYPES_H__

#define ERR -1
#define OK 0
#define TRUE 1
#define FALSE 0


/* Print colors */
#define PRINT_BLACK "\033[30;1m"
#define PRINT_RED "\033[31;1m"
#define PRINT_GREEN "\033[32;1m"
#define PRINT_YELLOW "\033[33;1m"
#define PRINT_BLUE "\033[34;1m"
#define PRINT_MAGENTA "\033[35;1m"
#define PRINT_CYAN "\033[36;1m"
#define PRINT_WHITE "\033[37;1m"
#define PRINT_RESET "\033[00m"

typedef struct {
    void (*func)(int, double, double*, double*, double);
    void (*ini)(double*, double*, double*, double*);
    void (*syn)(double, double, double*, double*, double*);
    double * vars;
    double * params;
    double * g_virtual_to_real;
    double * g_real_to_virtual;
    int dim;
    double dt;
    int type_syn;
    long points;
    int s_points;
    void * msqid;
    int period;
    int n_in_chan;
    int n_out_chan;
    int * in_channels;
    int * out_channels;
    int freq;
    int rafaga_modelo_pts;
    char * filename;
    int calibration;
    int anti;
    int model;
} rt_args;

typedef struct {
    char * filename;
    char * path;
    void * msqid;
    long points;
    int s_points;
    int type_syn;
    int model;
    int period;
    int freq;
    int time_var;
    int calibration;
    int anti;
    int important;
} writer_args;

typedef struct {
    double min_abs_model;
    double max_model;
    double min_abs_real;
    double max_real;
    double scale_virtual_to_real;
    double scale_real_to_virtual;
    double offset_virtual_to_real;
    double offset_real_to_virtual;
    double max_real_relativo;
    double min_real;
} calibration_args;

#endif
