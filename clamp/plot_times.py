import pandas as pd
import numpy as np
import matplotlib.pyplot as plt
import matplotlib.patches as mpatches
import matplotlib.gridspec as gridspec
import argparse
import math

import plot_aux_new as aux
import plot_funcs as funcs
import plot_autocal as autocal

dpi = 1


class Values():
	def __init__(self, data, model):
		self.model = model

		self.syn_ml_max = np.max(data.syn_ml) / 1000
		self.syn_ml_mean = np.mean(data.syn_ml) / 1000
		self.syn_ml_std = np.std(data.syn_ml)/ 10000

		self.read = data.read
		self.read_max = np.max(data.read)/ 1000
		self.read_mean = np.mean(data.read)/ 1000
		self.read_std = np.std(data.read)/ 1000

		self.drift = data.drift
		self.drift_max = np.max(data.drift)/ 1000
		self.drift_mean = np.mean(data.drift)/ 1000
		self.drift_std = np.std(data.drift)/ 1000

		self.syn_lm1_max = np.max(data.syn_lm1)/ 1000
		self.syn_lm1_mean = np.mean(data.syn_lm1)/ 1000
		self.syn_lm1_std = np.std(data.syn_lm1)/ 1000

		self.syn_lm2_max = np.max(data.syn_lm2)/ 1000
		self.syn_lm2_mean = np.mean(data.syn_lm2)/ 1000
		self.syn_lm2_std = np.std(data.syn_lm2)/ 1000

		self.neuron = data.neuron
		self.neuron_max = np.max(data.neuron)/ 1000
		self.neuron_mean = np.mean(data.neuron)/ 1000
		self.neuron_std = np.std(data.neuron)/ 1000

		self.send = data.send
		self.send_max = np.max(data.send)/ 1000
		self.send_mean = np.mean(data.send)/ 1000
		self.send_std = np.std(data.send)/ 1000

		self.wait = data.wait
		self.wait_max = np.max(data.wait)/ 1000
		self.wait_mean = np.mean(data.wait)/ 1000
		self.wait_std = np.std(data.wait)/ 1000

		self.lat = data.lat
		self.lat_max = np.max(data.lat)/ 1000
		self.lat_mean = np.mean(data.lat)/ 1000
		self.lat_std = np.std(data.lat)/ 1000

		self.syn = []
		for i in range(len(data.syn_ml)):
			self.syn.append(data.syn_ml[i] + data.syn_lm1[i] + data.syn_lm2[i])

		self.syn_max = np.max(self.syn)/ 1000
		self.syn_mean = np.mean(self.syn)/ 1000
		self.syn_std = np.std(self.syn)/ 1000

	def plotBarTimes(self):
		N = 7

		ind = np.arange(1,N+1)  # the x locations for the groups
		width = .9       # the width of the bars

		fig, ax = plt.subplots(figsize=(8,5))
		dpi = fig.dpi


		maxt = (self.lat_max, self.read_max, self.drift_max, self.syn_max, self.neuron_max, self.send_max, self.wait_max)
		means = (self.lat_mean, self.read_mean, self.drift_mean, self.syn_mean, self.neuron_mean, self.send_mean, self.wait_mean)
		stds = (self.lat_std, self.read_std, self.drift_std, self.syn_std, self.neuron_std, self.send_std, self.wait_std)

		#rects1 = ax.bar(ind, maxt, width, color="#6699ff")
		rects1 = ax.bar(ind, means, width, yerr=stds, capsize=10, ecolor="black", color="#000099")
		#rects2 = ax.bar(ind + width/2, means, width, alpha=0.8, yerr=stds, capsize=10, ecolor="black", color="#000099")


		font = {'family': 'serif',
		        'color':  'black',
		        'weight': 'normal',
		        'size': 10,
		        }

		# add some text for labels, title and axes ticks
		ax.set_ylabel('Time (us)')
		ax.set_ylim(0, 150)
		#ax.set_yscale('log')
		ax.set_title(self.model)
		ax.set_xticks(ind + width / 2)
		ax.set_xticklabels(('Wake latency', 'DAQ read/write', 'Drift compensation', 'Synapse models', 'Neuron model', 'Send to msg queue', 'Wait until next interval'), rotation=40)

		#ax.legend(rects1[0], 'Mean')


		plt.tight_layout()
		#plt.show()


	def plotBoxTimes(self):
		data = [self.lat, self.read, self.drift, self.syn, self.neuron, self.send, self.wait]

		for i in range(len(data)):
			data[i] = [x/1000 for x in data[i]]

		font = {'family': 'serif',
		        'color':  'black',
		        'weight': 'normal',
		        'size': 10,
		        }

		flierprops = dict(marker='+', markerfacecolor='none',
                  linestyle='none', markeredgecolor='#3399ff')
		whiskerprops = dict(linestyle='--')
			
		# multiple box plots on one figure
		#fig = plt.figure(figsize=(7,7))
		plt.ylim(0, 150)
		plt.title(self.model)
		plt.ylabel("Time (us)")
		plt.boxplot(data, flierprops=flierprops)
		plt.xticks([1,2,3,4,5,6, 7], ['Wake latency', 'DAQ read/write', 'Drift compensation', 'Synapse models', 'Neuron model', 'Send to msg queue', 'Wait until next interval'], rotation=40)

		mean_legend = mpatches.Patch(color='#000099', label='Mean')
		max_legend = mpatches.Patch(color='#3399ff', label='Outliers')
		plt.legend(handles=[mean_legend, max_legend])
		
		plt.tight_layout()
		plt.savefig('barbox_'+self.model+'.png', dpi=500)
		#plt.show()



	def plotOverLimit(self):
		l = len(self.lat)

		print("\n%s"%(self.model))

		for i in range(l):
			aux = (self.lat[i] + self.read[i] + self.drift[i] + self.syn[i] + self.neuron[i] + self.send[i]) / 1000
			if aux >= 100:
				next_aux = (self.read[i+1] + self.drift[i+1] + self.syn[i+1] + self.neuron[i+1] + self.send[i+1]) / 1000
				print("iter %d time %d neuron %d wait %d next %d"%(i, aux, self.neuron[i]/1000, self.wait[i]/1000, next_aux))


		N = 4

		ind = np.arange(N)    # the x locations for the groups
		width = 0.8       # the width of the bars: can also be len(x) sequence

		plt.figure(figsize=(15,4))

		lats = [self.lat[1104498-1]/1000, self.lat[1104498]/1000, self.lat[1104498+1]/1000, self.lat[1104498+2]/1000]
		daq = [self.read[1104498-1]/1000, self.read[1104498]/1000, self.read[1104498+1]/1000, self.read[1104498+2]/1000]
		drift = [self.drift[1104498-1]/1000, self.drift[1104498]/1000, self.drift[1104498+1]/1000, self.drift[1104498+2]/1000]
		syn = [self.syn[1104498-1]/1000, self.syn[1104498]/1000, self.syn[1104498+1]/1000, self.syn[1104498+2]/1000]
		neuron = [self.neuron[1104498-1]/1000, self.neuron[1104498]/1000, self.neuron[1104498+1]/1000, self.neuron[1104498+2]/1000]
		send = [self.send[1104498-1]/1000, self.send[1104498]/1000, self.send[1104498+1]/1000, self.send[1104498+2]/1000]
		wait = [self.wait[1104498-1]/1000, self.wait[1104498]/1000, self.wait[1104498+1]/1000, self.wait[1104498+2]/1000]

		bottom3=[i+j for i,j in zip(lats, daq)]
		bottom4=[i+j for i,j in zip(bottom3, drift)]
		bottom5=[i+j for i,j in zip(bottom4, syn)]
		bottom6=[i+j for i,j in zip(bottom5, neuron)]
		bottom7=[i+j for i,j in zip(bottom6, send)]

		p1 = plt.barh(ind, lats, width, color="#ff0000")
		p2 = plt.barh(ind, daq, width,
		             left=lats, color="#ff9900")
		p3 = plt.barh(ind, drift, width,
		             left=bottom3, color="#ffff66")
		p4 = plt.barh(ind, syn, width,
		             left=bottom4, color="#ff6699")
		p5 = plt.barh(ind, neuron, width,
		             left=bottom5, color="#00cc00")
		p6 = plt.barh(ind, send, width,
		             left=bottom6, color="#cc33ff")
		p7 = plt.barh(ind, wait, width,
		             left=bottom7, color="#3399ff")

		font = {'family': 'serif',
			        'color':  'black',
			        'weight': 'normal',
			        'size': 10,
			        }

		
		plt.xlabel('Time (us)')
		plt.title('Average time distribution over real-time intervals')
		plt.yticks(ind, ("Iteration N-1", "Iteration N", "Iteration N+1", "Iteration N+2"))
		plt.xticks(np.arange(0, 101, 10))
		plt.xlim(0,100)
		plt.legend((p1[0], p2[0], p3[0], p4[0], p5[0], p6[0], p7[0]), ('Wake latency', 'DAQ read/write', 'Drift compensation', 'Synapse models', 'Neuron model', 'Send to msg queue', 'Wait until next interval'))

		plt.tight_layout()
		plt.show()

		return


def plot_stacked_barplot(values_hr, values_rlk, values_gh, values_wang):
	N = 4

	ind = np.arange(N)    # the x locations for the groups
	width = 0.8       # the width of the bars: can also be len(x) sequence

	plt.figure(figsize=(15,4))

	lats = [values_hr.lat_mean, values_rlk.lat_mean, values_gh.lat_mean, values_wang.lat_mean]
	daq = [values_hr.read_mean, values_rlk.read_mean, values_gh.read_mean, values_wang.read_mean]
	drift = [values_hr.drift_mean, values_rlk.drift_mean, values_gh.drift_mean, values_wang.drift_mean]
	syn = [values_hr.syn_mean, values_rlk.syn_mean, values_gh.syn_mean, values_wang.syn_mean]
	neuron = [values_hr.neuron_mean, values_rlk.neuron_mean, values_gh.neuron_mean, values_wang.neuron_mean]
	send = [values_hr.send_mean, values_rlk.send_mean, values_gh.send_mean, values_wang.send_mean]
	wait = [values_hr.wait_mean, values_rlk.wait_mean, values_gh.wait_mean, values_wang.wait_mean]

	bottom3=[i+j for i,j in zip(lats, daq)]
	bottom4=[i+j for i,j in zip(bottom3, drift)]
	bottom5=[i+j for i,j in zip(bottom4, syn)]
	bottom6=[i+j for i,j in zip(bottom5, neuron)]
	bottom7=[i+j for i,j in zip(bottom6, send)]

	p1 = plt.barh(ind, lats, width, color="#ff0000")
	p2 = plt.barh(ind, daq, width,
	             left=lats, color="#ff9900")
	p3 = plt.barh(ind, drift, width,
	             left=bottom3, color="#ffff66")
	p4 = plt.barh(ind, syn, width,
	             left=bottom4, color="#ff6699")
	p5 = plt.barh(ind, neuron, width,
	             left=bottom5, color="#00cc00")
	p6 = plt.barh(ind, send, width,
	             left=bottom6, color="#cc33ff")
	p7 = plt.barh(ind, wait, width,
	             left=bottom7, color="#3399ff")

	font = {'family': 'serif',
		        'color':  'black',
		        'weight': 'normal',
		        'size': 10,
		        }

	
	plt.xlabel('Time (us)')
	plt.title('Average time distribution over real-time intervals')
	plt.yticks(ind, (values_hr.model, values_rlk.model, values_gh.model, values_wang.model))
	plt.xticks(np.arange(0, 101, 10))
	plt.xlim(0,100)
	plt.legend((p1[0], p2[0], p3[0], p4[0], p5[0], p6[0], p7[0]), ('Wake latency', 'DAQ read/write', 'Drift compensation', 'Synapse models', 'Neuron model', 'Send to msg queue', 'Wait until next interval'))

	plt.tight_layout()
	plt.show()





args  = aux.arguments()
args.file="data/2018y_9m_6d/10h_55m_34s"
data_hr = aux.DataStruct1(args)
values_hr = Values(data_hr, "Hindmarsh-Rose")

args.file="data/2018y_9m_6d/11h_0m_56s"
data_rlk = aux.DataStruct1(args)
values_rlk = Values(data_rlk, "Rulkov")

args.file="data/2018y_9m_6d/11h_6m_16s"
data_gh = aux.DataStruct1(args)
values_gh = Values(data_gh, "Ghigliazza-Holmes")

args.file="data/2018y_9m_6d/11h_11m_56s"
data_wang = aux.DataStruct1(args)
values_wang = Values(data_wang, "Wang")

'''
values_hr.plotBarTimes()
values_hr.plotBoxTimes()

values_rlk.plotBarTimes()
values_rlk.plotBoxTimes()

values_gh.plotBarTimes()
values_gh.plotBoxTimes()

values_wang.plotBarTimes()
values_wang.plotBoxTimes()

plt.close()
'''


values_hr.plotOverLimit()

values_rlk.plotOverLimit()

values_gh.plotOverLimit()

values_wang.plotOverLimit()

plot_stacked_barplot(values_hr, values_rlk, values_gh, values_wang)
 


