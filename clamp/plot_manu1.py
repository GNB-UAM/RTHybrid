import pandas as pd
import numpy as np
import matplotlib.pyplot as plt
import matplotlib.gridspec as gridspec
import argparse
import math

f, axarr = plt.subplots(2, 2, sharex=True, sharey=False, figsize=(10,5))
f.suptitle("SINAPSIS ELÉCTRICA")

##### FICHERO 1
dataset = pd.read_csv("data/2017y_6m_19d/19h_51m_15s_1.txt", delimiter=' ', header=1)
array = dataset.values
data = array[1:,:]
data = data[:-1]

t = data[:,1] / 1000
v_model_scaled = data[:, 5]
v_live = data[:, 8]

axarr[0, 0].plot(t, v_model_scaled, label="", linewidth=0.3)
axarr[0, 0].plot(t, v_live, label="", linewidth=0.4)
axarr[0, 0].set_title("Modelo Izhikevich - Fase")
axarr[0, 0].set_ylim(-6, -3.4)
axarr[0, 0].legend()
axarr[0, 0].set_ylabel("Voltaje (mV)")

##### FICHERO 2
dataset = pd.read_csv("data/2017y_6m_19d/19h_53m_37s_1.txt", delimiter=' ', header=1)
array = dataset.values
data = array[1:,:]
data = data[:-1]

t = data[:,1] / 1000
v_model_scaled = data[:, 5]
v_live = data[:, 8]

axarr[0, 1].plot(t, v_model_scaled, label="Modelo", linewidth=0.3)
axarr[0, 1].plot(t, v_live, label="Viva", linewidth=0.4)
axarr[0, 1].set_title("Mapa de Rulkov - Fase")
axarr[0, 1].set_ylim(-6, -3.4)
axarr[0, 1].legend(loc=1)

##### FICHERO 3
dataset = pd.read_csv("data/2017y_6m_19d/21h_40m_42s_1.txt", delimiter=' ', header=1)
array = dataset.values
data = array[1:,:]
data = data[:-1]

t = data[:,1] / 1000
v_model_scaled = data[:, 5]
v_live = data[:, 8]

axarr[1, 0].plot(t, v_model_scaled, label="", linewidth=0.3)
axarr[1, 0].plot(t, v_live, label="", linewidth=0.4)
axarr[1, 0].set_title("Modelo Hindmarsh-Rose - Antifase")
axarr[1, 0].set_ylim(-5.7, -3.2)
axarr[1, 0].legend()
axarr[1, 0].set_xlabel("Tiempo (s)")
axarr[1, 0].set_ylabel("Voltaje (mV)")

##### FICHERO 4
dataset = pd.read_csv("data/2017y_6m_19d/21h_39m_46s_1.txt", delimiter=' ', header=1)
array = dataset.values
data = array[1:,:]
data = data[:-1]

t = data[:,1] / 1000
v_model_scaled = data[:, 5] * 0.6 - 1.6
v_live = data[:, 8] 

axarr[1, 1].plot(t, v_model_scaled, label="", linewidth=0.3)
axarr[1, 1].plot(t, v_live, label="", linewidth=0.4)

axarr[1, 1].set_title("Mapa de Rulkov - Antifase")
axarr[1, 1].set_ylim(-5.7, -3.2)
axarr[1, 1].legend()
axarr[1, 1].set_xlabel("Tiempo (s)")

##### FIN
plt.xlim([10, 15])
#plt.tight_layout()
plt.show()