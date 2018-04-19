import pandas as pd
import numpy as np
import matplotlib.pyplot as plt
import matplotlib.gridspec as gridspec
import argparse
import math

import plot_aux as aux
import plot_funcs as funcs
import plot_autocal as autocal

filename = "data/2018y_4m_19d/16h_37m_30s_data.txt"
dataset = pd.read_csv(filename, delimiter=' ', header=1)
data = dataset.values


print("file loaded")

t = data[:,0]
l = data[:,1]
v = data[:,2]
m = data[:,3]

plt.figure(figsize=(12,6))
plt.plot(t, v)
plt.plot(t, m)
plt.tight_layout()
plt.show()



lats = [int(math.modf(x/1000)[1]) for x in l]
	
plt.figure(figsize=(12,6))
plt.plot(t, lats, label="Latencies", linewidth=0.8)
plt.legend()
plt.xlabel("Time (s)")
plt.ylabel("Latency (us)")
plt.title("Latency values")
plt.tight_layout()
plt.show()


