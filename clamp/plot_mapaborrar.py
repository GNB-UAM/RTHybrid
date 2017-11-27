import pandas as pd
import numpy as np
import matplotlib.pyplot as plt
import matplotlib.gridspec as gridspec
import argparse
import math

##### FICHERO 1
dataset = pd.read_csv("data/2017y_6m_19d/20h_21m_49s_1.txt", delimiter=' ', header=1)
array = dataset.values
data = array[1:,:]
data = data[:-1]

t = data[:,1] / 1000
v_model_scaled = data[:, 5]
v_live = data[:, 8]

dataset = pd.read_csv("data/2017y_6m_19d/20h_21m_49s_2.txt", delimiter=' ', header=None)
array = dataset.values
array = array[:-1]

time = array[:, 0] / 1000
index = array[:,1]
ecm = array[:,2]
extra = array[:,3]
g0 = array[:,4]#####
g1 = array[:,5]
g2 = array[:,6]
g3 = array[:,7]#####

def analisis(v1, v2, g1, g2):
	for i in range(len(g1)):
		if i>0:
			if g1[i-1]!=g1[i] or g2[i-1]!=g2[i]:
				print("Big trouble")
				print(i)
	a = num_disp(v1)
	b = num_disp(v2)

	print("Disp: "+str(a) +" vs "+str(b))

	if abs(a-b)>1:
		return 0
	else:
		return 1



segundos=100000
old=50000
new=150000

matrix = [[0 for x in range(12)] for y in range(5)] 

a=0
b=0

for i in range(5*12):
	matrix[a][b] = analisis(v_live[old:new-200], v_model_scaled[old:new-200], g0[old:new-200], g3[old:new-200])
	old=new
	new=old+segundos
	a+=1
	if a==5:
		a=0
		b+=1

x=[]
y=[]
for i in range(5):
	for j in range(12):
		if matrix[i][j]==1:
			x.append(i)
			y.append(j)


fig = plt.figure()  # create a figure object
ax = fig.add_subplot(1, 1, 1)  # create an axes object in the figure
my_xticks = ['0', '0.2', '0.4', '0.6', '0.8']
my_yticks = ['0', '0.01', '0.02', '0.03', '0.04', '0.05', '0.06', '0.07', '0.08', '0.09', '0.10', '0.11']
#locs, labels = plt.xticks(x, my_xticks)
#plt.setp(labels, 'rotation')
plt.plot(x, y, "o")
ax.set_xticks(range(5))
ax.set_xticklabels(my_xticks)
ax.set_yticks(range(12))
ax.set_yticklabels(my_yticks)
plt.show()

