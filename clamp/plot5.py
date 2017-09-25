import pandas as pd
import numpy as np
import matplotlib.pyplot as plt
import matplotlib.gridspec as gridspec
import argparse
import math

#f, axarr = plt.subplots(2, 2, sharex=True, sharey=False, figsize=(10,5))

plt.figure(figsize=(10,5))
ax1 = plt.subplot2grid((2,2), (0, 0))
ax2 = plt.subplot2grid((2,2), (0, 1))
ax3 = plt.subplot2grid((2,2), (1, 0), colspan=2)
ax1.set_xlim([10, 15])
ax2.set_xlim([10, 15])

plt.suptitle("SINAPSIS QUÍMICA")

##### FICHERO 1
dataset = pd.read_csv("data/2017y_6m_19d/20h_53m_33s_1.txt", delimiter=' ', header=1)
array = dataset.values
data = array[1:,:]
data = data[:-1]

t = data[:,1] / 1000
v_model_scaled = data[:, 5]
v_live = data[:, 8]

ax1.plot(t, v_model_scaled, label="", linewidth=0.3)
ax1.plot(t, v_live, label="", linewidth=0.4)
ax1.set_title("Modelo Izhikevich")
ax1.legend()
ax1.set_ylabel("Voltaje (mV)")

##### FICHERO 2
dataset = pd.read_csv("data/2017y_6m_19d/20h_55m_0s_1.txt", delimiter=' ', header=1)
array = dataset.values
data = array[1:,:]
data = data[:-1]

t = data[:,1] / 1000
v_model_scaled = data[:, 5]
v_live = data[:, 8]

ax2.plot(t, v_model_scaled, label="Modelo", linewidth=0.3)
ax2.plot(t, v_live, label="Viva", linewidth=0.4)
ax2.set_title("Modelo Hindmarsh-Rose")
ax2.legend()
ax2.legend(loc=1)

##### FICHERO 3
dataset = pd.read_csv("data/2017y_6m_19d/20h_57m_47s_1.txt", delimiter=' ', header=1)
array = dataset.values
data = array[1:,:]
data = data[:-1]

t = data[:,1] / 1000
v_model_scaled = data[:, 5]
v_live = data[:, 8]

ax3.plot(t, v_model_scaled, label="", linewidth=0.3)
ax3.plot(t, v_live, label="", linewidth=0.4)
ax3.set_title("Mapa de Rulkov")
ax3.legend()
ax1.set_xlabel("Tiempo (s)")
ax2.set_xlabel("Tiempo (s)")
ax3.set_xlabel("Tiempo (s)")
ax3.set_ylabel("Voltaje (mV)")


##### FIN
plt.xlim([10, 20])
plt.tight_layout()
plt.show()