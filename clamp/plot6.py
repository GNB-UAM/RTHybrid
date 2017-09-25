import pandas as pd
import numpy as np
import matplotlib.pyplot as plt
import matplotlib.gridspec as gridspec
import argparse
import math

f, axarr = plt.subplots(1, 3, sharex=True, sharey=False, figsize=(8,4))
f.suptitle("Relación de potenciales - sinapsis eléctrica")

##### FICHERO 1
dataset = pd.read_csv("data/2017y_6m_19d/19h_51m_15s_1.txt", delimiter=' ', header=1)
array = dataset.values
data = array[1:,:]
data = data[:-1]

t = data[:,1] / 1000
v_model_scaled = data[:, 5]
v_live = data[:, 8]

axarr[0].plot(v_model_scaled[00000:50000], v_live[00000:50000], label="", linewidth=0.1)
tam=len(v_model_scaled)
axarr[1].plot(v_model_scaled[tam-50000:tam-1], v_live[tam-50000:tam-1], label="", linewidth=0.1)
axarr[0].set_ylabel("Voltaje neurona viva")

##### FICHERO 1

dataset = pd.read_csv("data/2017y_6m_19d/19h_57m_19s_1.txt", delimiter=' ', header=1)
array = dataset.values
data = array[1:,:]
data = data[:-1]

t = data[:,1] / 1000
v_model_scaled = data[:, 5]
v_live = data[:, 8]

tam=len(v_model_scaled)
axarr[2].plot(v_model_scaled[tam-50000:tam-1], v_live[tam-50000:tam-1], label="", linewidth=0.1)


plt.xlim([-6.8, -2.8])
axarr[0].set_ylim(-6, -3.4)
axarr[1].set_ylim(-6, -3.4)
axarr[2].set_ylim(-6, -3.4)
axarr[0].set_xlabel("Voltaje (Modelo de Izhikevich)")
axarr[1].set_xlabel("Voltaje (Modelo de Izhikevich)")
axarr[2].set_xlabel("Voltaje (Modelo de Izhikevich)")
axarr[0].set_title("Sin conexión")
axarr[1].set_title("Conexión en fase")
axarr[2].set_title("Conexión en antifase")
plt.show()

