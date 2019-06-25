#include "nm_bluetooth.h"
#include "../../integration_methods.h"
#include "../neuron_models_aux_functions.h"

#include <SerialStream.h>
#include <iostream>

using namespace LibSerial;

SerialStream serial_stream;

/**
 * @file nm_bluetooth.h
 * @brief Source file for the Bluetooth model functions.
 */

/** @name Bluetooth
 * Bluetooth neuron model.
 */
///@{

double nm_bluetooth_set_pts_burst (double pts_live, neuron_model * nm);



/**
 * @brief Bluetooth neuron model.
 * @param[in] nm Neuron model structure
 * @param[in] syn Synapse input current value
 */

void nm_bluetooth (neuron_model nm, double syn) {
	//nm.method(nm_bluetooth_f, nm.dim, nm.params[NM_BLUETOOTH_DT], nm.vars, nm.params, syn);

	char next_char = '1';
	//serial_stream >> next_char;

	double range = nm.max - nm.min;
	double th_up = nm.min + (range * 0.8);
	double th_lo = nm.min + (range * 0.1);
	double flag = 0;
	double burst_dur = nm.pts_burst;

	//printf("%c\n", next_char);
	//printf("v2 %f\n", syn);

	if (syn > th_up && nm.params[NM_BLUETOOTH_DT] == 1) {
		nm.params[NM_BLUETOOTH_DT] = 0;
		burst_dur = nm.params[NM_BLUETOOTH_COUNTER] / 10000;
		//serial_stream << burst_dur << std::endl;
		printf("dur %f\n", burst_dur);
		nm.params[NM_BLUETOOTH_COUNTER] = 0;

	} else if (syn < th_lo && nm.params[NM_BLUETOOTH_DT] == 0) {
		nm.params[NM_BLUETOOTH_DT] = 1;
	}

	nm.params[NM_BLUETOOTH_COUNTER]++;

	if (next_char == '1') { //Luz?
		//double pts_pulse = nm.pts_burst * nm.params[NM_BLUETOOTH_PER];
		//printf("counter %f pulse %f\n", nm.params[NM_BLUETOOTH_COUNTER], pts_pulse);
		nm.vars[0] = nm.params[NM_BLUETOOTH_MAX];

		/*if (nm.params[NM_BLUETOOTH_COUNTER] >= pts_pulse) {
			nm.params[NM_BLUETOOTH_COUNTER] = 0;
		} else {
			if (nm.params[NM_BLUETOOTH_COUNTER] < (pts_pulse / 2)) {
				nm.vars[0] = nm.params[NM_BLUETOOTH_MAX];
			} else {
				nm.vars[0] = 0;
			}

			//printf("out %f\n\n", nm.vars[1]);

			nm.params[NM_BLUETOOTH_COUNTER]++;
		}*/
	} else {
		nm.vars[0] = 0;
		//nm.params[NM_BLUETOOTH_COUNTER] = 0;
	}

	//serial_stream << "25a500p" << std::endl;


	/*lp_v = nm.vars[0];
	pd_v = nm.vars[1];*/



	return;
}

/**
 * @brief Initializes Bluetooth neuron model.
 * @param[in] nm Pointer to the neuron model structure
 * @param[in] vars Array with the initial values of the model variables
 * @param[in] params Array with the values of the mode parameters
 */

void nm_bluetooth_init (neuron_model * nm, double * vars, double * params) {
	nm->dim = NM_BLUETOOTH_N_VARS;
	nm->vars = (double *) malloc (sizeof(double) * nm->dim);
	copy_1d_array(vars, nm->vars, nm->dim);

	nm->n_params = NM_BLUETOOTH_N_PARAMS;
	nm->params = (double *) malloc (sizeof(double) * nm->n_params);
	copy_1d_array(params, nm->params, nm->n_params);

	nm->params[NM_BLUETOOTH_COUNTER] = 0;
	nm->params[NM_BLUETOOTH_DT] = 0;

	nm->max = 55;
	nm->min = -65;
	nm->pts_burst = -1.0;

	nm->func = &nm_bluetooth;
	nm->set_pts_burst = &nm_bluetooth_set_pts_burst;

	//if (serial_stream.IsOpen() == true) serial_stream.Close();

	if (serial_stream.IsOpen() == false){
		//serial_stream.Open("/dev/ttyUSB1");
		serial_stream.Open("/dev/rfcomm0");
		serial_stream.SetBaudRate(SerialStreamBuf::BAUD_19200);
		serial_stream.SetCharSize(SerialStreamBuf::CHAR_SIZE_8);
	}
	

	return;
}

/**
 * @brief Sets Bluetooth model number of points per burst.
 *
 * The number of points per burst of the model is equalized to the number of points per burst of the living neuron.
 * @param[in] pts_live Number of points in a living neuron burst
 * @param[in] nm Pointer to the neuron model structure
 * @return Integration step, if none -1
 */

double nm_bluetooth_set_pts_burst (double pts_live, neuron_model * nm) {
    nm->pts_burst = pts_live;
    
    return -1;
}

///@} 