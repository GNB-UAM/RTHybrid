import pandas as pd
import numpy as np
import matplotlib.pyplot as plt
import matplotlib.gridspec as gridspec
import argparse
import math

def periodo(array):
	freq=10000
	porcentaje_mini = 0.05
	porcentaje_maxi = 0.3

	#Linear search max & min
	min_ped=99999
	max_ped=-99999
	v = array
	for elem in array:
		if elem>max_ped:
			max_ped=elem
		elif elem<min_ped:
			min_ped=elem

	#Ajusting min & max
	if min_ped>0:
		min_ped = min_ped + min_ped*porcentaje_mini;
	else:
		min_ped = min_ped - min_ped*porcentaje_mini;
	
	if max_ped>0:
		max_ped = max_ped - max_ped*porcentaje_maxi;
	else:
		max_ped = max_ped + max_ped*porcentaje_maxi;

	#Take note of the time of the events
	up = False
	if v[0]>max_ped:
		up = True

	changes=0
	times=[]
	res=[]

	for i in range(len(v)):
		#Up threshold pass first time after down threshold
		if up==False and v[i]>max_ped:
			changes+=1
			times.append(i/freq)
			res.append(max_ped)
			up = True
		#Down threshold activate up threshold
		elif up==True and v[i]<min_ped:
			up = False

	#Plot
	if 1==0:
		t = np.linspace(0,len(v), len(v))
		t = t / 10000
		plt.figure(figsize=(7,4))
		plt.plot(t, v, color='C1',linewidth=0.5)
		plt.axhline(y=max_ped, color='r', linestyle='--', linewidth=0.2, label="Detección de ráfaga")
		plt.axhline(y=min_ped, color='g', linestyle='--', linewidth=0.2, label="Interruptor de búsqueda")
		plt.plot(times, res, 'o', label="Evento detectado")
		plt.xlabel("Tiempo (s)")
		plt.ylabel("Voltaje")
		plt.title("Detección de eventos")
		plt.legend()
		plt.tight_layout()
		plt.show()
	

	return times, res, min_ped, max_ped

def num_disp(array):
	t, r, min, max = periodo(array)
	return len(r)


def analisis_para_mapa(v1, v2, g1, g2):
	#Si los datos que han llegado hasta aqui estan pochos avisamos
	for i in range(len(g1)):
		if i>0:
			if g1[i-1]!=g1[i] or g2[i-1]!=g2[i]:
				print("Big trouble - Tamaño malo")
				print(g1)
				print(g2)

	#Tiempos de disparo de cada señal
	times_a, res_a, asd1, asd2 = periodo(v1)
	times_b, res_b, asd3, asd4 = periodo(v2)

	plt.figure(figsize=(7,4))
	plt.plot(times_a, res_a, 'o', label="a")
	plt.plot(times_b, res_b, 'o', label="b")
	plt.show()

	#Diferencia entre disparos muy tocha, parece no haber sincro
	if abs(len(times_a)-len(times_b))>2:
		print("Size so different")
		return 0

	#Ajustamos el inicio para que siempre sea de la misma neurona
	res = []
	if times_a[0]>times_b[0]:
		del times_b[0]

	if times_a[0]>times_b[0]:
		print("ERR???")
		if len(times_b)<=len(times_a):
			for i in range(len(times_b)):
				if times_a[i]<times_b[i]:
					print("No ording at firing")
					return 0
				res.append(times_a[i]-times_b[i])
		else:
			for i in range(len(times_a)):
				if times_a[i]<times_b[i]:
					print("No ording at firing")
					return 0
				res.append(times_a[i]-times_b[i])
	
	else:
		if len(times_b)<=len(times_a):
			for i in range(len(times_b)):
				if times_a[i]>times_b[i]:
					print("No ording at firing")
					return 0
				res.append(times_b[i]-times_a[i])
		else:
			for i in range(len(times_a)):
				if times_a[i]>times_b[i]:
					print("No ording at firing")
					return 0 
				res.append(times_b[i]-times_a[i])

	
	suma=0
	for ele in res:
		suma+=ele
	suma=suma/len(res)
	
	print(str(g2[0])+" - "+str(g1[0])+" = "+str(suma))

	return suma

