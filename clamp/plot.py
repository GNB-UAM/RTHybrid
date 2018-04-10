import pandas as pd
import numpy as np
import matplotlib.pyplot as plt
import matplotlib.gridspec as gridspec
import argparse
import math

import plot_aux as aux
import plot_funcs as funcs
import plot_autocal as autocal

args  = aux.arguments()
data1 = aux.DataStruct1(args)
#data2 = aux.DataStruct2(args)

#funcs.plot_voltage(data1, data2, args)
#funcs.save_events(data1, data2, args)

#autocal.plot_autocal(data1, data2, args)
#funcs.plot_regularity(data1, data2, args)


#funcs.plot_voltage_g_current(data1, data2, args)

#funcs.plot_voltage_current(data1, data2, args)

funcs.plot_lat_dist(data1)
funcs.plot_lat(data1)



