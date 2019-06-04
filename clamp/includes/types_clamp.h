/**
 * @file types_clamp.h
 * @brief Header file containing the main structures used by RTHybrid.
 */

#ifdef __cplusplus
extern "C" {
#endif

#ifndef TYPES_CLAMP_H__
#define TYPES_CLAMP_H__


#include "../../common/includes/types.h"
#include "../../common/includes/file_selector_functions.h"


/**
 * @brief Structure that stores the parameters regarding the integration.
 *
 * It will be initialized with the information of an specific model in #init_synapse_model.
 */
typedef struct {
    void (*method)
        (void (*f) (double *, double *, double *, double),
        int dim, double dt, double * vars,
        double * params, double aux);                   /**< Pointer to the function with the integration method. */
    double dt;                                          /**< Integration step. */
} integration_params;


/* Neuron model struct */
typedef struct neuron_model neuron_model;

/**
 * @brief Structure that stores all the parameters and variables of a neuron model.
 *
 * It will be initialized with the information of an specific model in #init_neuron_model.
 */ 
struct neuron_model {
    void (*func)(neuron_model nm, double);				/**< Pointer to the main function of the model (defined in neuron_models_functions.h) */ 
    double (*set_pts_burst)(double, neuron_model * nm);	/**< Pointer to the function that sets the number of points per burst of the model (defined in neuron_models_functions.h) */
    void (*method)
        (void (*f) (double *, double *, double *, double), 
        int dim, double dt, double * vars, 
        double * params, double aux);                   /**< Pointer to the function with the integration method. */ 
    unsigned int type;									/**< Integer that identifies the model (using the macros defined in neuron_models_functions.h) */
    unsigned int dim;									/**< Dimension (number of variables) of the model */
    unsigned int n_params;								/**< Number of parameters of the model */
    double * vars;										/**< Array with the variables of the model */
    double * params;									/**< Array with the parameters of the model */
    double min;											/**< Minimum membrane potential value of the model */
    double max;											/**< Maximum membrane potential value of the model */
    double pts_burst;									/**< Number of points per burst of the model */
};


/* Synapse model struct */
typedef struct synapse_model synapse_model;

/**
 * @brief Structure that stores all the parameters and variables of a synapse model.
 *
 * It will be initialized with the information of an specific model in #init_synapse_model.
 */ 
struct synapse_model {
    void (*func)(double, double, synapse_model*, double*);	/**< Pointer to the main function of the model (defined in synapse_models_functions.h) */
    void (*set_online_parameters)
        (synapse_model * sm,                                /**< Pointer to the function that sets the amplitude scale and offset parameters synapse model. (defined in synapse_models_functions.h) */
         double scale,
         double offset,
         double min,
         double max,
         integration_params int_params);
    unsigned int type;										/**< Integer that identifies the model (using the macros defined in synapse_models_functions.h) */
    double * g;												/**< Array with the conductances of the synapse */
    double scale;											/**< Amplitude scale of the living neuron signal regarding to the neuron model */
    double offset;											/**< Amplitude offset of the living neuron signal regarding to the neuron model */
    double min;                                             /**< Minimum amplitude value of the presynaptic neuron signal */
    double max;                                             /**< Maximum amplitude value of the presynaptic neuron signal */
    unsigned int calibrate;									/**< Indicates the neuron which amplitude will be calibrated to the other one range. It can be the pre-synaptic one (#SYN_CALIB_PRE) or the post-synaptic (#SYN_CALIB_POST)*/
    void * type_params;										/**< Pointer to the structure storing the specific parameters for a type of synapse (defined in synapse_models_functions.h)*/
};


/**
 * @brief Structure that stores the input arguments for the rt_thread.
 *
 * It will be initialized with the information of an specific model in #init_synapse_model.
 */
typedef struct {
    neuron_model nm;				/**< Neuron model structure*/
    synapse_model sm_model_to_live;	/**< Synapse model from the model to the living neuron structure*/
    synapse_model sm_live_to_model;	/**< Synapse model from the living neuron to the model structure*/
    synapse_model sm_live_to_model_scaled; /**< Synapse model from the living neuron to the model structure (to scale to the living neuron range)*/
    
    long time_var;					/**< Duration of the interaction*/
    int before;						/**< Before interaction control time*/
    int after;						/**< After interaction control time*/
    int observation;                /**< Duration of the pre-calibration observation*/
    
    char * filename;				/**< Output filename*/
    void * msqid;					/**< Message queue identifier*/
    unsigned short data_file_id;    /**< Data recording file descriptor*/
    unsigned short events_file_id;  /**< Events recording file descriptor*/

    int period;						/**< Real-time period (duration of the interval) in seconds*/
    int freq;						/**< Real-time frequency (points per second) in Hz*/
	double sec_per_burst;			/**< Duration of a burst wanted in seconds. If this value is -1, then the duration is the one from the living neuron*/
    unsigned short check_drift;     /**< Signal drift compensation is on (1) or off (0)*/

    unsigned int n_in_chan;			/**< Number of DAQ input channels*/
    unsigned int n_out_chan;		/**< Number of DAQ output channels*/
    int * in_channels;				/**< Array of DAQ input channels identifiers*/
    int * out_channels;				/**< Array of DAQ output channels identifiers*/
    double input_factor;			/**< Input scaling factor due to the experimental setup*/
    double output_factor;			/**< Output voltage/current conversion factor due to the experimental setup*/

    int calibration;				/**< Auto-calibration or exploration mode selected*/
    double step_v_to_r;				/**< Auxiliar parameter for exploration*/
    double step_r_to_v;				/**< Auxiliar parameter for exploration*/
    double auto_cal_val_1;			/**< Auxiliar parameter for exploration*/
} rt_args;


/* writer_thread struct */
typedef struct {
    char * filename;				/**< */
    char * path;					/**< */
    void * msqid;					/**< */
    long points;					/**< */
    int s_points;					/**< */
    int type_syn;					/**< */
    int model;						/**< */
    int period;						/**< */
    int freq;						/**< */
    int time_var;					/**< */
    int calibration;				/**< */
    int important;					/**< */
    synapse_model sm_model_to_live;	/**< */
    synapse_model sm_live_to_model;	/**< */
} writer_args;

typedef struct {
    double min_abs_model;
    double max_abs_model;
    double min_abs_real;
    double max_abs_real;
    double min_rel_model;
    double max_rel_model;
    double min_rel_real;
    double max_rel_real;
    double scale_virtual_to_real;
    double scale_real_to_virtual;
    double offset_virtual_to_real;
    double offset_real_to_virtual;
    double * g_virtual_to_real;
    double * g_real_to_virtual;
    double syn_gradual_k1;
    double syn_gradual_k2;
} calibration_args;

typedef struct {
    unsigned int detect_on;
    double first_spike_times[6]; //N
    double between_firsts_periods[5]; //N - 1
    unsigned index;
    double sum_acc;
    double per;
    double thresh_up;
    double thresh_down;
    double var;

    /* Cosas que se le pasan desde rt */
    struct timespec * ts;
    double v;
    synapse_model * sm_live_to_model;
    synapse_model * sm_model_to_live;
} regularity_control_args;


typedef struct {
    double * scale_virtual_to_real;
    double * scale_real_to_virtual;
    double * offset_virtual_to_real;
    double * offset_real_to_virtual;
    double * max_window;
    double * min_window;
    double * max_rel_real;
    double * min_rel_real;
    double max_abs_model;
    double min_abs_model;
    synapse_model * sm_model_to_live;
    synapse_model * sm_live_to_model;
    synapse_model * sm_live_to_model_scaled;
} fix_drift_args;


typedef struct {
    double freq;
    int observation;
    int after;
    int time_var;
    int before;
    int model;
    int synapse_mtol;
    int synapse_ltom;
    int mode_auto_cal;
    int imp;
    char * input_channels;
    char * output_channels;
    double * vars;
    double * params;
    double * g_virtual_to_real;
    double * g_real_to_virtual;
    double step_v_to_r;
    double step_r_to_v;
    double sec_per_burst;
    unsigned short check_drift;
    double auto_cal_val_1;
    void * syn_args_model_to_live;
    void * syn_args_live_to_model;
    double input_factor;			/**< Input scaling factor due to the experimental setup*/
    double output_factor;			/**< Output voltage/current conversion factor due to the experimental setup*/
    char * filename;
    char * data_path;
} clamp_args;

#endif // TYPES_CLAMP_H__

#ifdef __cplusplus
}
#endif
