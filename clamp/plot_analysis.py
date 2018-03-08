import pandas as pd
import numpy as np
import matplotlib.pyplot as plt
import matplotlib.gridspec as gridspec
import argparse
import math

def events_to_file(events, file_name):
	print(file_name)
	f = open(file_name, 'w')
	for event in events:
		s =  '{0:.3f}'.format(event*1000)+" -1\n"
		f.write(s) 
	f.close()

def regularity(events):
	acc, counter, var = 0, 0, 0
	times, periods, res = [], [], []
	num_events = 20

	for i in range(len(events)-1):
		periods.append (events[i+1]-events[i])
		acc += events[i+1]-events[i]
		counter += 1
		if counter == 1:
			time = events[i]
		if counter == num_events:
			mean = acc / num_events
			for j in range(num_events):
				tmp = periods[i]-mean
				var += tmp*tmp
			var /= num_events
			#res.append (mean)
			res.append (math.sqrt(var)/mean*100)
			times.append (events[i])
			acc, counter, var = 0, 0, 0

	return times, res

def regularity2(events):
	num_events = 40
	coefs, times = [], []
	for i in range(len(events)-num_events):
		sub_events = events[i:i+num_events]
		r = cal_coef_var(sub_events)
		coefs.append(r)
		times.append ( (events[i]+events[i+num_events]) / 2 )
	return times, coefs

def cal_coef_var(events, print_on=False):
	acc, counter, var = 0, 0, 0
	periods = []
	for i in range(len(events)-1):
		periods.append (events[i+1]-events[i])
		acc += events[i+1]-events[i]
		counter += 1
	mean = acc / counter
	for p in periods:
		tmp = p - mean
		var += tmp*tmp
	var = var / len(periods)
	if print_on==True:
		print(math.sqrt(var)/mean*100)
	return math.sqrt(var)/mean*100


def periodo(t, t_ms, v, freq, plot_on=False, all_events=False):
	s_interval = 20
	times, times_ms, events, minis, maxis = [], [], [], [], [] 
	up = None

	num_intervals = len(v)/(freq*s_interval)
	for i in range(int(num_intervals)):
		time, time_ms, event, mini, maxi, up = periodo_internal( t[ i*freq*s_interval : (i+1)*freq*s_interval ], t_ms[ i*freq*s_interval : (i+1)*freq*s_interval ], v[ i*freq*s_interval : (i+1)*freq*s_interval ], i*s_interval, freq, up, all_events)
		times.extend(time)
		times_ms.extend(time_ms)
		events.extend(event)
		np.append(minis, mini)
		np.append(maxis, maxi)

	#Plot
	if plot_on==True:
		t = np.linspace(0,len(v), len(v))
		t = t / freq
		plt.figure(figsize=(7,4))
		plt.plot(t, v, color='C1',linewidth=0.5)
		#plt.axhline(y=maxis, color='r', linestyle='--', linewidth=0.2)
		#plt.axhline(y=minis, color='g', linestyle='--', linewidth=0.2)
		plt.plot(times, events, 'o', label="Event")
		plt.xlabel("Time (s)")
		plt.ylabel("Voltage")
		plt.title("Event detection")
		plt.legend(loc=1, framealpha=1.0)
		plt.tight_layout()
		plt.show()

	return times, times_ms, events, minis, maxis

def periodo_internal(t, t_ms, v, base_time, freq, up, all_events, plot_on=False):
	porcentaje_min = 0.2
	porcentaje_max = 0.75

	########PARA COGER TODOS
	if all_events==True:
		porcentaje_min = 0.65

	# max & min
	min_v = min(v)
	max_v = max(v)
	range_v = max_v - min_v

	min_r_v = min_v + range_v*porcentaje_min
	max_r_v = min_v + range_v*porcentaje_max

	if up==None:
		if v[0]>max_r_v:
			up = True
		else:
			up = False

	changes=0
	times=[]
	times_ms=[]
	res=[]

	for i in range(len(v)):
		#Up threshold pass first time after down threshold
		if up==False and v[i]>max_r_v:
			changes+=1
			times.append(base_time + i/freq)
			times_ms.append(t_ms[i])
			res.append(max_r_v)
			up = True
		#Down threshold activate up threshold
		elif up==True and v[i]<min_r_v:
			up = False

	#Plot
	if plot_on==True:
		t = np.linspace(0,len(v), len(v))
		t = t / 10000 + base_time
		plt.figure(figsize=(7,4))
		plt.plot(t, v, color='C1',linewidth=0.5)
		plt.axhline(y=max_r_v, color='r', linestyle='--', linewidth=0.2)
		plt.axhline(y=min_r_v, color='g', linestyle='--', linewidth=0.2)
		plt.plot(times, res, 'o', label="Event")
		plt.xlabel("Time (s)")
		plt.ylabel("Voltage")
		plt.title("Event detection")
		plt.legend(loc=1, framealpha=1.0)
		plt.tight_layout()
		plt.show()

	return times, times_ms, res, min_r_v, max_r_v, up

def num_disp(array):
	t, r, min, max = periodo(array)
	return len(r)


def analisis_para_mapa(v1, v2, g1, g2, args):
	#Si los datos que han llegado hasta aqui estan pochos avisamos
	for i in range(len(g1)):
		if i>0:
			if g1[i-1]!=g1[i] or g2[i-1]!=g2[i]:
				print("Big trouble - g's diferentes")
				print(g1)
				print(len(g1))
				print(g2)
				print(len(g2))

	#Tiempos de disparo de cada señal
	times_a, res_a, asd1, asd2 = periodo(v1, args.freq)
	times_b, res_b, asd3, asd4 = periodo(v2, args.freq)

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

	'''
	plt.figure(figsize=(7,4))
	plt.plot(times_a, res_a, 'o', label="a")
	plt.plot(times_b, res_b, 'o', label="b")
	plt.show()
	'''

	return suma

