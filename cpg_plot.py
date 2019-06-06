import pandas as pd
import numpy as np
import matplotlib.pyplot as plt

filename = "salida.txt"
dataset = pd.read_csv(filename, delimiter=' ', header=0)
data = dataset.values

neuron1 = data[:,0]
neuron2 = data[:,1]
c12 = data[:,2]
c21 = data[:,3]

#Crete and size
plt.figure(figsize=(12,8))

#Plots
ax1 = plt.subplot(2, 1, 1)
plt.plot(neuron1, label="neuron1", linewidth=0.8)
plt.plot(neuron2, label="neuron2", linewidth=0.8)
plt.ylabel("Voltage")
plt.legend(loc=1, framealpha=1.0)

ax2 = plt.subplot(2, 1, 2, sharex=ax1)
plt.plot(c12, label="c12", linewidth=0.8)
plt.plot(c21, label="c21", linewidth=0.8)
plt.ylabel("Current")
plt.legend(loc=1, framealpha=1.0)

#Details
plt.xlabel("Time (s)")
plt.tight_layout()
plt.show()
