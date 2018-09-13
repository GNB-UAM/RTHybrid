import pandas as pd
import numpy as np
import matplotlib.pyplot as plt
import matplotlib.gridspec as gridspec
import argparse
import math

import plot_analysis as pa

##################
##################
# STANDAR PLOTS  #
##################
##################

def plot_times_measures(data):
	syn_ml_max = np.max(data.syn_ml) / 1000
	syn_ml_mean = np.mean(data.syn_ml) / 1000
	syn_ml_std = np.std(data.syn_ml)/ 10000

	read = data.read
	read_max = np.max(data.read)/ 1000
	read_mean = np.mean(data.read)/ 1000
	read_std = np.std(data.read)/ 1000

	drift = data.drift
	drift_max = np.max(data.drift)/ 1000
	drift_mean = np.mean(data.drift)/ 1000
	drift_std = np.std(data.drift)/ 1000

	syn_lm1_max = np.max(data.syn_lm1)/ 1000
	syn_lm1_mean = np.mean(data.syn_lm1)/ 1000
	syn_lm1_std = np.std(data.syn_lm1)/ 1000

	syn_lm2_max = np.max(data.syn_lm2)/ 1000
	syn_lm2_mean = np.mean(data.syn_lm2)/ 1000
	syn_lm2_std = np.std(data.syn_lm2)/ 1000

	neuron = data.neuron
	neuron_max = np.max(data.neuron)/ 1000
	neuron_mean = np.mean(data.neuron)/ 1000
	neuron_std = np.std(data.neuron)/ 1000

	send = data.send
	send_max = np.max(data.send)/ 1000
	send_mean = np.mean(data.send)/ 1000
	send_std = np.std(data.send)/ 1000

	wait = data.wait
	wait_max = np.max(data.wait)/ 1000
	wait_mean = np.mean(data.wait)/ 1000
	wait_std = np.std(data.wait)/ 1000

	lat = data.lat
	lat_max = np.max(data.lat)/ 1000
	lat_mean = np.mean(data.lat)/ 1000
	lat_std = np.std(data.lat)/ 1000

	syn = []
	for i in range(len(data.syn_ml)):
		syn.append(data.syn_ml[i] + data.syn_lm1[i] + data.syn_lm2[i])

	syn_max = np.max(syn)/ 1000
	syn_mean = np.mean(syn)/ 1000
	syn_std = np.std(syn)/ 1000


	N = 7

	ind = np.arange(N)  # the x locations for the groups
	width = .9       # the width of the bars

	fig, ax = plt.subplots(figsize=(7,7))


	maxt = (lat_max, read_max, drift_max, syn_max, neuron_max, send_max, wait_max)
	means = (lat_mean, read_mean, drift_mean, syn_mean, neuron_mean, send_mean, wait_mean)
	stds = (lat_std, read_std, drift_std, syn_std, neuron_std, send_std, wait_std)

	rects1 = ax.bar(ind + width/2, maxt, width, color="#6699ff")
	rects2 = ax.bar(ind + width/2, means, width, alpha=0.8, yerr=stds, capsize=10, ecolor="black", color="#000099")


	font = {'family': 'serif',
	        'color':  'black',
	        'weight': 'normal',
	        'size': 10,
	        }

	# add some text for labels, title and axes ticks
	ax.set_ylabel('Time (us)')
	ax.set_ylim(0, 150)
	#ax.set_yscale('log')
	ax.set_title('Time measures for each operation within a real-time interval')
	ax.set_xticks(ind + width / 2)
	ax.set_xticklabels(('Wake latency', 'DAQ read/write', 'Drift compensation', 'Synapse models', 'Neuron models', 'Send', 'Wait until next interval'))

	ax.legend((rects1[0], rects2[0]), ('Max', 'Mean'))

	'''
	def autolabel(rects):
	    for rect in rects:
	        height = rect.get_height()
	        ax.text(rect.get_x() + rect.get_width()/2., 1.05*height,
	                '%.2f' % float(height),
	                ha='center', va='bottom', fontdict = font)
	

	autolabel(rects1)
	autolabel(rects2)
	'''

	plt.tight_layout()
	plt.show()


def plot_times_stacked(data):
	syn_ml_max = np.max(data.syn_ml) / 1000
	syn_ml_mean = np.mean(data.syn_ml) / 1000
	syn_ml_std = np.std(data.syn_ml)/ 10000

	read = data.read
	read_max = np.max(data.read)/ 1000
	read_mean = np.mean(data.read)/ 1000
	read_std = np.std(data.read)/ 1000

	drift = data.drift
	drift_max = np.max(data.drift)/ 1000
	drift_mean = np.mean(data.drift)/ 1000
	drift_std = np.std(data.drift)/ 1000

	syn_lm1_max = np.max(data.syn_lm1)/ 1000
	syn_lm1_mean = np.mean(data.syn_lm1)/ 1000
	syn_lm1_std = np.std(data.syn_lm1)/ 1000

	syn_lm2_max = np.max(data.syn_lm2)/ 1000
	syn_lm2_mean = np.mean(data.syn_lm2)/ 1000
	syn_lm2_std = np.std(data.syn_lm2)/ 1000

	neuron = data.neuron
	neuron_max = np.max(data.neuron)/ 1000
	neuron_mean = np.mean(data.neuron)/ 1000
	neuron_std = np.std(data.neuron)/ 1000

	send = data.send
	send_max = np.max(data.send)/ 1000
	send_mean = np.mean(data.send)/ 1000
	send_std = np.std(data.send)/ 1000

	wait = data.wait
	wait_max = np.max(data.wait)/ 1000
	wait_mean = np.mean(data.wait)/ 1000
	wait_std = np.std(data.wait)/ 1000

	lat = data.lat
	lat_max = np.max(data.lat)/ 1000
	lat_mean = np.mean(data.lat)/ 1000
	lat_std = np.std(data.lat)/ 1000

	syn = []
	for i in range(len(data.syn_ml)):
		syn.append(data.syn_ml[i] + data.syn_lm1[i] + data.syn_lm2[i])

	syn_max = np.max(syn)/ 1000
	syn_mean = np.mean(syn)/ 1000
	syn_std = np.std(syn)/ 1000


	N = 1

	ind = np.arange(N)    # the x locations for the groups
	width = 0.35       # the width of the bars: can also be len(x) sequence

	bottom3= lat_mean + read_mean
	bottom4= bottom3 + drift_mean
	bottom5= bottom4 + syn_mean
	bottom6= bottom5 + neuron_mean
	bottom7= bottom6 + send_mean

	p1 = plt.barh(ind, lat_mean, width, color="#ff0000")
	p2 = plt.barh(ind, read_mean, width,
	             left=lat_mean, color="#ff9900")
	p3 = plt.barh(ind, drift_mean, width,
	             left=bottom3, color="#ffff66")
	p4 = plt.barh(ind, syn_mean, width,
	             left=bottom4, color="#ff6699")
	p5 = plt.barh(ind, neuron_mean, width,
	             left=bottom5, color="#00cc00")
	p6 = plt.barh(ind, send_mean, width,
	             left=bottom6, color="#cc33ff")
	p7 = plt.barh(ind, wait_mean, width,
	             left=bottom7, color="#3399ff")

	font = {'family': 'serif',
		        'color':  'black',
		        'weight': 'normal',
		        'size': 10,
		        }

	
	plt.xlabel('Time (us)')
	plt.title('Average time distribution over real-time intervals')
	#plt.yticks(ind, (values_hr.model, values_rlk.model, values_gh.model, values_wang.model))
	#plt.xticks(np.arange(0, 81, 10))
	plt.xlim(0,100)
	plt.legend((p1[0], p2[0], p3[0], p4[0], p5[0], p6[0]), ('Wake latency', 'DAQ read/write', 'Drift compensation', 'Synapse models', 'Neuron model', 'Send to msg queue', 'Wait until next interval'))

	plt.tight_layout()
	plt.show()

def plot_voltage(data1, data2, args):
	#Crete and size
	fig = plt.figure(figsize=(12,4))
    
	#Plots
	ax1 = plt.subplot(1, 1, 1)
	plot_line_voltage(data1, data2, args)
	
	#Details
	plt.xlabel("Time (s)")
	plt.tight_layout()
	plt.show()

def plot_voltage_current(data1, data2, args):
	#Crete and size
	plt.figure(figsize=(12,8))

	#Plots
	ax1 = plt.subplot(2, 1, 1)
	plot_line_voltage(data1, data2, args)

	ax2 = plt.subplot(2, 1, 2, sharex=ax1)
	#plot_line_current(data1, data2, args)
	plot_line_durneuron(data1, data2, args)
	
	#Details
	plt.xlabel("Time (s)")
	plt.tight_layout()
	plt.show()

def plot_voltage_g_current(data1, data2, args):
	plt.figure(figsize=(12,8))

	ax1 = plt.subplot(3, 1, 1)
	plt.title("Hybrid connection")
	plot_line_voltage(data1, data2, args)

	ax2 = plt.subplot(3, 1, 2, sharex=ax1)
	# No en funcion por no ser universal
	plt.plot(data1.time, data2.data_extra[0], label="Real to Model - Fast", linewidth=0.8)
	plt.plot(data1.time, data2.data_extra[1], label="Real to Model - Slow", linewidth=0.8)
	plt.plot(data1.time, data2.data_extra[2], label="Model to Real - Fast", linewidth=0.8)
	plt.plot(data1.time, data2.data_extra[3], label="Model to Real - Slow", linewidth=0.8)
	plt.ylabel("Conductance")
	plt.legend()

	ax3 = plt.subplot(3, 1, 3, sharex=ax1)
	plot_line_current(data1, data2, args)
	
	plt.xlabel("Time (s)")
	plt.tight_layout()
	plt.show()

def plot_regularity(data1, data2, args):
	t_exp  = (5+480) * args.freq
	t_post = (5+480+480) * args.freq

	times = pa.periodo(data1.time[:t_exp], data1.time_ms[:t_exp], data1.data_in[0][:t_exp], args.freq)[0]
	pa.cal_coef_var(times, True)

	times = pa.periodo(data1.time[t_exp:t_post], data1.time_ms[t_exp:t_post], data1.data_in[0][t_exp:t_post], args.freq)[0]
	pa.cal_coef_var(times, True)	

	times = pa.periodo(data1.time[t_post:], data1.time_ms[t_post:], data1.data_in[0][t_post:], args.freq)[0]
	pa.cal_coef_var(times, True)

	##############################
	##############################

	times = pa.periodo(data1.time, data1.time_ms, data1.v_model_scaled, args.freq)[0]
	times1, res1 = pa.regularity2(times)

	times = pa.periodo(data1.time, data1.time_ms, data1.data_in[0], args.freq)[0]
	times2, res2 = pa.regularity2(times)

	#Crete and size
	plt.figure(figsize=(12,8))

	#Plots
	ax1 = plt.subplot(2, 1, 1)
	plot_line_voltage(data1, data2, args)

	ax2 = plt.subplot(2, 1, 2, sharex=ax1)
	plt.plot(times1, res1, label="Model neuron period variance (%)", linewidth=0.8)
	plt.plot(times2, res2, label="Living neuron period variance (%)", linewidth=0.8)
	plt.ylim([0, 100])
	plt.ylabel("Variance percentage")
	plt.legend(loc=1, framealpha=1.0)
	
	#Details
	plt.xlabel("Time (s)")
	plt.tight_layout()
	plt.show()

def save_events(data1, data2, args):
	times = pa.periodo(data1.time, data1.time_ms, data1.v_model_scaled, args.freq, all_events=True)[0]
	pa.events_to_file(times, 'extra/'+args.file+'_1_events_model.txt')
	times = pa.periodo(data1.time, data1.time_ms, data1.data_in[0], args.freq, all_events=True)[0]
	pa.events_to_file(times, 'extra/'+args.file+'_1_events_live.txt')


###########################
#   Internal lines plots  #
###########################
def plot_line_voltage(data1, data2, args):
	plt.plot(data1.time, data1.v_model_scaled, label="Model neuron", linewidth=0.8)
	plt.plot(data1.time, data1.data_in[0], label="Living neuron", linewidth=0.8)
	if args.drift==1:
		plt.plot(data1.time, data1.min_window, "g", linewidth=0.8)
		plt.plot(data1.time, data1.max_window, "g", linewidth=0.8)
	plt.ylabel("Voltage")
	plt.legend(loc=1, framealpha=1.0)

def plot_line_current(data1, data2, args):
	plt.plot(data1.time, data1.c_viva, label="Current real to model", linewidth=0.8)
	plt.plot(data1.time, data1.c_model, label="Current model to real", linewidth=0.8)
	plt.ylabel("Current")
	plt.legend(loc=1, framealpha=1.0)


def plot_line_durneuron(data1, data2, args):
	plt.plot(data1.time, data1.neuron, label="Model neuron", linewidth=0.8)
	plt.ylabel("dur")
	plt.legend(loc=1, framealpha=1.0)

##################
##################
# NO STANDAR PLOTS 
##################
##################

##################
##################
#    LATENCIES   #
##################
##################
def plot_lat_dist(data1):
	lats = [int(math.modf(x/1000)[1]) for x in data1.lat]
	hist = np.histogram(lats, bins=np.arange(max(lats)+2))
	values = hist[0]
	edges = hist[1][:-1]

	if len(values) > 100:
		fig = plt.figure(figsize=(12,6))
		gs = gridspec.GridSpec(1, 4)
		ax1 = plt.subplot(gs[0, :3])
		ax2 = plt.subplot(gs[0, 3], sharey=ax1)

		ax1.bar(edges[:30], values[:30])
		ax2.bar(edges[-10:], values[-10:], color="red")

		ax1.spines['right'].set_visible(False)
		ax2.spines['left'].set_visible(False)

		ax2.tick_params(labelleft='off', left='off', which='both')
		ax2.ticklabel_format(useOffset=False)
		ax2.xaxis.tick_bottom()

		ax1.set_yscale("log")
		ax2.set_yscale("log")

		ax1.set_ylim(bottom=0.1)
		ax2.set_ylim(bottom=0.1)

		ax1.grid()
		ax2.grid()

		d = .015  # how big to make the diagonal lines in axes coordinates

		# arguments to pass to plot, just so we don't keep repeating them
		kwargs = dict(transform=ax1.transAxes, color='k', clip_on=False)
		ax1.plot((1, 1), (-d, +d), **kwargs)        # top-right diagonal
		ax1.plot((1, 1), (1 - d, 1 + d), **kwargs)  # bottom-right diagonal

		kwargs.update(transform=ax2.transAxes)  # switch to the bottom axes
		ax2.plot((0, 0), (-d, +d), **kwargs)  # top-left diagonal
		ax2.plot((0, 0), (1 - d, 1 + d), **kwargs)  # bottom-left diagonal

		ax1.set_ylabel("Ocurrences")
		ax1.set_xlabel("Latencies (μs)")

	else:
		plt.figure(figsize=(12,6))
		plt.bar(edges, values)
		plt.yscale("log")
		plt.grid()
		plt.ylim(bottom=0.1)
		plt.ylabel("Ocurrences")
		plt.xlabel("Latencies (μs)")

	plt.suptitle("Latencies")
	plt.tight_layout()
	plt.subplots_adjust(left=0.06, right=0.98, top=0.93, bottom=0.1)
	plt.show()

def plot_lat(data1):
	lats = [int(math.modf(x/1000)[1]) for x in data1.lat]
	
	plt.figure(figsize=(12,6))
	plt.plot(data1.time, lats, label="Latencies", linewidth=0.8)
	plt.legend()
	plt.xlabel("Time (s)")
	plt.ylabel("Latency (us)")
	plt.title("Latency values")
	plt.tight_layout()
	plt.show()