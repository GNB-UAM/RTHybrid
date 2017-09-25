import pandas as pd
import numpy as np
import matplotlib.pyplot as plt
import matplotlib.gridspec as gridspec
import argparse
import math

ap = argparse.ArgumentParser()
ap.add_argument("-f", "--file", required=True,
	help="path to the input file")
ap.add_argument("-n", "--name", required=True,
	help="output name")
ap.add_argument("-t", "--title", required=True,
	help="title")
args = vars(ap.parse_args())

file = open(args["file"],'r')
line = file.readline()
channels = line.split(' ')

n_in_chan = int(channels[0])
n_out_chan = int(channels[1]) 
print(n_in_chan)
print(n_out_chan)
file.close()

dataset = pd.read_csv(args["file"], delimiter=' ', header=1)
array = dataset.values
data = array[1:,:]

t_unix = data[:, 0]
t_absol = data[:,1]
i = data[:,2]
lat = data[:, 3]

v_model = data[:, 4]
v_model_scaled = data[:, 5]
c_model = data[:, 6]
c_viva = data[:, 7]


data_in = []
for j in range(8, 8 + n_in_chan):
	data_in.append(data[:, j])

data_out = []
for j in range(8 + n_in_chan, 8 + n_in_chan + n_out_chan):
	data_out.append(data[:, j])


plt.figure(figsize=(12,6))
plt.plot(t_absol, v_model_scaled, label="Modelo Izhikevich")
plt.plot(t_absol, data_in[0], label="Neurona electrónica")
plt.plot(t_absol, c_model, label="c_model", linewidth=0.1)
plt.plot(t_absol, c_viva, label="c_real", linewidth=0.1)
plt.legend()
plt.xlabel("Tiempo (s)")
plt.ylabel("Voltaje")
plt.title("Modelo escalado a señal externa")
plt.show()

'''
iteration
absolute send time
v
u
active part time
iteration time
awake delay time
sleep time

iteration = array[:,0]
absol = array[:,1]
v = array[:,2]
u = array[:,3]
model = array[:,4]
loop = array[:,5]
awake = array[:,6]
sleep = array[:,7]
'''

def plot_voltage(n_points, v):
	plt.plot(t_absol[:n_points], v[:n_points], '-')
	plt.title(args["title"])
	plt.xlabel("Time (s)")
	plt.ylabel("Voltage (mV)")
	plt.legend()

	#for i in np.arange(0, (n_points/10) + 0.1, 0.1):
		#plt.axvline(x=i, color='r')

	plt.savefig("figures/"+args["name"]+"_voltage.pdf")
	plt.show()


def plot_model_time():
	plt.plot(iteration, model)
	plt.title("Izhikevich "+args["title"]+" model time")
	plt.xlabel("Iteration")
	plt.ylabel("Time (ms)")
	#plt.ylim(0, 0.2)
	plt.axhline(y=0.1, color='r')
	plt.savefig("figures/"+args["name"]+"_model.pdf")
	plt.show()


def plot_iter_time():
	plt.plot(iteration, loop)
	plt.title("Izhikevich "+args["title"]+" iteration time")
	plt.xlabel("Iteration")
	plt.ylabel("Time (ms)")
	plt.axhline(y=0.1, color='r')
	#plt.ylim(0, 0.2)
	plt.savefig("figures/"+args["name"]+"_iter.pdf")
	plt.show()


def plot_iter_model_time():
	plt.plot(iteration, model)
	plt.plot(iteration, loop)
	plt.title("Izhikevich "+args["title"]+" iteration and model time")
	plt.xlabel("Iteration")
	plt.ylabel("Time (ms)")
	plt.axhline(y=0.1, color='r')
	#plt.ylim(0, 0.2)
	plt.savefig("figures/"+args["name"]+"_iter_model.pdf")
	plt.show()

def plot_awake_time():
	plt.figure(figsize=(8,2))
	plt.plot(iteration, awake)
	plt.title("Izhikevich "+args["title"]+" jitter")
	plt.xlabel("Iteration")
	plt.ylabel("Latency (ms)")
	#plt.axhline(y=0.1, color='r')
	#plt.ylim(0, 0.2)
	plt.savefig("figures/"+args["name"]+"_awake.pdf", bbox_inches='tight')
	plt.show()

def plot_sleep_time():
	plt.plot(iteration, awake)
	plt.title("Izhikevich "+args["title"]+" sleep time")
	plt.xlabel("Iteration")
	plt.ylabel("Time (ms)")
	plt.axhline(y=0.1, color='r')
	#plt.ylim(0, 0.2)
	plt.savefig("figures/"+args["name"]+"_sleep.pdf")
	plt.show()

def plot_together():
	plt.plot(iteration, loop)
	plt.fill_between(iteration, 0, loop, alpha=0.5,label="Complete")
	plt.plot(iteration, model, label="T1+T2+T3")
	#plt.plot(iteration, sleep, label="T4")
	plt.title("Izhikevich "+args["title"]+"")
	plt.xlabel("Iteration")
	plt.ylabel("Time (ms)")
	plt.axhline(y=0.1, color='r')
	plt.legend()
	#plt.ylim(0, 0.2)
	plt.savefig("figures/"+args["name"]+"_together.pdf")
	plt.show()

def plot_lat_dist():
	lats = [int(math.modf(x/1000)[1]) for x in lat]
	'''
	plt.hist(lats, bins=np.arange(max(lats)+2)-0.5, log="True", ec='black')
	plt.xticks(np.linspace(0, max(lats), 11))
	plt.xlabel("Latency (μs)")
	plt.ylabel("Ocurrences")
	plt.grid()
	plt.title("Izhikevich "+args["title"]+" latencies")
	plt.savefig("figures/"+args["name"]+"_lat_hist.pdf")
	plt.show()
	'''


	hist = np.histogram(lats, bins=np.arange(max(lats)+2))
	values = hist[0]
	edges = hist[1][:-1]

	if len(values) > 100:
		fig = plt.figure(figsize=(12,6))
		gs = gridspec.GridSpec(1, 4)
		ax1 = plt.subplot(gs[0, :3])
		ax2 = plt.subplot(gs[0, 3], sharey=ax1)
		#gs.tight_layout(fig)

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

	plt.suptitle(args["title"]+" latencies")
	plt.savefig("figures/"+args["name"]+"_lat_hist.pdf")

	plt.show()

def plot_lat_dist_esp():
	lats = [int(math.modf(x/1000)[1]) for x in lat]
	'''
	plt.hist(lats, bins=np.arange(max(lats)+2)-0.5, log="True", ec='black')
	plt.xticks(np.linspace(0, max(lats), 11))
	plt.xlabel("Latency (μs)")
	plt.ylabel("Ocurrences")
	plt.grid()
	plt.title("Izhikevich "+args["title"]+" latencies")
	plt.savefig("figures/"+args["name"]+"_lat_hist.pdf")
	plt.show()
	'''


	hist = np.histogram(lats, bins=np.arange(max(lats)+2))
	values = hist[0]
	edges = hist[1][:-1]

	if len(values) > 100:
		fig = plt.figure(figsize=(12,6))
		gs = gridspec.GridSpec(1, 4)
		ax1 = plt.subplot(gs[0, :3])
		ax2 = plt.subplot(gs[0, 3], sharey=ax1)
		#gs.tight_layout(fig)

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

		ax1.set_ylabel("Número de ocurrencias")
		ax1.set_xlabel("Latencias (μs)")
	else:
		plt.figure(figsize=(8,4))
		plt.bar(edges, values)
		plt.yscale("log")
		plt.grid()
		plt.ylim(bottom=0.1)
		plt.ylabel("Número de ocurrencias")
		plt.xlabel("Latencias (μs)")

	#plt.suptitle(args["title"]+" latencies")
	plt.suptitle("Latencias con tiempo real activado")
	plt.savefig("figures/"+args["name"]+"_lat_hist.pdf")
	plt.tight_layout()
	plt.show()


def plot_lat_dist2():
	values = awake
	edges = np.arange(len(awake))

	if len(values) > 100:
		fig = plt.figure(figsize=(20,10))
		gs = gridspec.GridSpec(1, 4)
		ax1 = plt.subplot(gs[0, :3])
		ax2 = plt.subplot(gs[0, 3], sharey=ax1)
		#gs.tight_layout(fig)

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
		plt.figure(figsize=(20,10))
		plt.bar(edges, values)
		plt.yscale("log")
		plt.grid()
		plt.ylim(bottom=0.1)
		plt.ylabel("Ocurrences")
		plt.xlabel("Latencies (μs)")

	plt.suptitle("Izhikevich "+args["title"]+" latencies")
	plt.savefig("figures/"+args["name"]+"_lat_hist.pdf")

	plt.show()




#Main
#plot_voltage(len(v_model), v_model)
#plot_voltage(len(data_in[0]), data_in[0])
#plot_voltage(len(data_in[1]), data_in[1])
#plot_model_time()
#plot_iter_time()
#plot_iter_model_time()
#plot_awake_time()
plot_lat_dist_esp()
#plot_lat_dist2()
#plot_sleep_time()
#plot_together()


