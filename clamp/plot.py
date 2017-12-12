import pandas as pd
import numpy as np
import matplotlib.pyplot as plt
import matplotlib.gridspec as gridspec
import argparse
import math

import plot_aux as aux
import plot_funcs as funcs
import plot_autocal as autocal

ap = argparse.ArgumentParser()
data1 = aux.DataStruct1(ap)
data2 = aux.DataStruct2(ap)

#funcs.plot_voltage(data1)
funcs.plot_voltage_events(data1, data2)
funcs.plot_lat_dist(data1)
funcs.plot_lat(data1)

#autocal.plot_autocal(data1, data2)



