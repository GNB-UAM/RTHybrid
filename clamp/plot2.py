import pandas as pd
import numpy as np
import matplotlib.pyplot as plt
import matplotlib.gridspec as gridspec
import argparse
import math

ap = argparse.ArgumentParser()
ap.add_argument("-f", "--file", required=True, help="date")
#ap.add_argument("-n", "--name", required=True, help="output name")
ap.add_argument("-c", "--calibration", required=True, help="calibration")
args = vars(ap.parse_args())

##### FICHERO 1
dataset = pd.read_csv(args["file"]+"_1.txt", delimiter=' ', header=1)
array = dataset.values
data = array[1:,:]
data = data[:-1]

t = t_absol = data[:,1] / 1000
v_model_scaled = data[:, 5]
v_live = data[:, 8]

##### FICHERO 2

dataset = pd.read_csv(args["file"]+"_2.txt", delimiter=' ', header=None)
array = dataset.values
array = array[:-1]

time = array[:, 0] / 1000
index = array[:,1]
ecm = array[:,2]
extra = array[:,3]
g0 = array[:,4]

def c7():
	g1 = array[:,5]
	g2 = array[:,6]
	g3 = array[:,7]

	f, axarr = plt.subplots(2, sharex=True, figsize=(8.5,4.1))

	axarr[0].plot(t, v_model_scaled, label="Modelo", linewidth=0.4)
	axarr[0].plot(t, v_live, label="Viva", linewidth=0.4)
	axarr[0].set_title("Voltaje")
	axarr[0].legend()

	axarr[1].plot(time, g0)
	axarr[1].plot(time, g3)
	axarr[1].set_title("Conductancias")
	axarr[1].legend()

	plt.xlabel("Tiempo (s)")
	plt.tight_layout()
	plt.show()

def c8():
	g1 = array[:,5]
	g2 = array[:,6]
	g3 = array[:,7]

	f, axarr = plt.subplots(3, sharex=True, figsize=(8.5,6.1))

	time_a, res_a, min_a, max_a = periodo(v_live)
	time_b, res_b, min_b, max_b = periodo(v_model_scaled)

	res_times = []
	#Recorremos elementos
	for i in range(len(time_a)):
		#Para cada elementos recorremos su entorno
		tmp_min = 99999
		for j in range(50):
			if i-j>=0 and i-j<len(time_b):
				tmp = abs(time_a[i]-time_b[i-j])
				if tmp<tmp_min:
					tmp_min=tmp
			if i+j<len(time_b):
				tmp = abs(time_a[i]-time_b[i+j])
				if tmp<tmp_min:
					tmp_min=tmp
		res_times.append(tmp_min)

	axarr[0].plot(t, v_model_scaled, label="Modelo", linewidth=0.4)
	axarr[0].plot(t, v_live, label="Viva", linewidth=0.4)
	axarr[0].plot(time_a, res_a, 'o', linewidth=0.4)
	axarr[0].plot(time_b, res_b, 'o', linewidth=0.4)
	axarr[0].axhline(y=max_a, color='C1', linestyle='--', linewidth=0.2)
	axarr[0].axhline(y=min_a, color='C1', linestyle='--', linewidth=0.2)
	axarr[0].axhline(y=max_b, color='C2', linestyle='--', linewidth=0.2)
	axarr[0].axhline(y=min_b, color='C2', linestyle='--', linewidth=0.2)
	axarr[0].set_title("Voltaje")
	axarr[0].legend()

	axarr[1].plot(time, ecm)
	axarr[1].plot(time, extra)
	axarr[1].set_title("Conductancias")
	axarr[1].legend()

	t2 = np.linspace(0, t[len(t)-1], num=len(res_times))
	axarr[2].plot(t2, res_times)
	axarr[2].set_title("Desfase")
	axarr[2].legend()

	plt.xlabel("Tiempo (s)")
	plt.tight_layout()
	plt.show()

def periodo(array):
	min=99999
	max=-99999
	v = array
	for elem in array:
		if elem>max:
			max=elem
		elif elem<min:
			min=elem

	porcentaje_mini = 0.25
	porcentaje_maxi = 0.4
	if min>0:
		min = min + min*porcentaje_mini;
	else:
		min = min - min*porcentaje_mini;
	
	if max>0:
		max = max - max*porcentaje_maxi;
	else:
		max = max + max*porcentaje_maxi;

	up = False
	if v[0]>max:
		up = True

	changes=0
	times=[]
	res=[]

	for i in range(len(v)):
		if up==False and v[i]>max:
			changes+=1
			times.append(i/10000)
			res.append(max)
			up = True
		elif up==True and v[i]<min:
			up = False

	t = np.linspace(0,len(v), len(v))
	t = t / 10000
	return times, res, min, max

def c6():

	f, axarr = plt.subplots(3, sharex=True, figsize=(8.5,5.1))

	axarr[0].plot(t, v_model_scaled, label="Modelo", linewidth=0.4)
	axarr[0].plot(t, v_live, label="Viva", linewidth=0.4)
	axarr[0].set_title("Voltaje")
	axarr[0].legend()

	axarr[1].plot(time, ecm)
	axarr[1].set_title("ECM")
	axarr[1].legend()

	axarr[2].plot(time, extra)
	axarr[2].set_title("Parametro que cambia")
	axarr[2].legend()

	plt.xlabel("Tiempo (s)")
	plt.tight_layout()
	plt.show()


def c1():
	
	aux=[]
	for i in range(len(ecm)):
		if i>0:
			if ecm[i]!=ecm[i-1] and t[i]<5:
				aux.append(ecm[i])

	ini = sum(aux) / len (aux)
	

	f, axarr = plt.subplots(3, sharex=True, figsize=(8.5,5.1))

	axarr[0].plot(t, v_model_scaled, label="Modelo", linewidth=0.4)
	axarr[0].plot(t, v_live, label="Viva", linewidth=0.4)
	axarr[0].set_title("Voltaje")
	axarr[0].legend(loc=1)

	axarr[1].plot(time, ecm)
	axarr[1].set_title("ECM")
	axarr[1].axhline(y=ini, color='r', linestyle='--', linewidth=0.4, label="ECM medio inicial")
	axarr[1].axhline(y=ini*0.4, color='g', linestyle='--', linewidth=0.4, label="ECM objetivo")
	#axarr[1].axvline(x=5, color='b', linestyle='--', linewidth=0.4, label="Inicio")
	axarr[1].legend(loc=1)

	axarr[2].plot(time, g0)
	axarr[2].set_title("Conductancia")
	axarr[2].legend(loc=1)

	plt.xlim([0, 20])
	plt.xlabel("Tiempo (s)")
	plt.tight_layout()
	plt.show()


if args["calibration"]=="1":
	c1()


if args["calibration"]=="6":
	c6()

if args["calibration"]=="7":
	c7()

if args["calibration"]=="8":
	c8()