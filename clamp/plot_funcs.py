import pandas as pd
import numpy as np
import matplotlib.pyplot as plt
import matplotlib.gridspec as gridspec
import argparse
import math

#########
# Voltage
#########
def plot_voltage(data):
	plt.figure(figsize=(12,8))

	ax1 = plt.subplot(2, 1, 1)
	plt.title("Hybrid connection")
	plt.plot(data.time, data.v_model_scaled, label="Model neuron", linewidth=0.8)
	plt.plot(data.time, data.data_in[0], label="Real neuron", linewidth=0.8)
	plt.ylabel("Voltage")
	plt.legend()

	ax2 = plt.subplot(2, 1, 2, sharex=ax1)
	plt.plot(data.time, data.c_viva, label="Current real to model", linewidth=0.8)
	plt.plot(data.time, data.c_model, label="Current model to real", linewidth=0.8)
	plt.plot(data.time, data.v_model, label="m", linewidth=0.8)
	plt.ylabel("Current")
	plt.legend()
	
	plt.xlabel("Time (s)")
	plt.tight_layout()
	plt.show()

def plot_voltage_events(data, data2):
	plt.figure(figsize=(12,8))

	ax1 = plt.subplot(3, 1, 1)
	plt.title("Hybrid connection")
	plt.plot(data.time, data.v_model_scaled, label="Model neuron", linewidth=0.8)
	plt.plot(data.time, data.data_in[0], label="Real neuron", linewidth=0.8)
	plt.ylabel("Voltage")
	plt.legend()

	ax2 = plt.subplot(3, 1, 2, sharex=ax1)
	plt.plot(data.time, data2.data_extra[0], label="Real to Model - Fast", linewidth=0.8)
	plt.plot(data.time, data2.data_extra[1], label="Real to Model - Slow", linewidth=0.8)
	plt.plot(data.time, data2.data_extra[2], label="Model to Real - Fast", linewidth=0.8)
	plt.plot(data.time, data2.data_extra[3], label="Model to Real - Slow", linewidth=0.8)
	plt.ylabel("Conductance")
	plt.legend()

	ax3 = plt.subplot(3, 1, 3, sharex=ax1)
	plt.plot(data.time, data.c_viva, label="Current real to model", linewidth=0.8)
	plt.plot(data.time, data.c_model, label="Current model to real", linewidth=0.8)
	plt.ylabel("Current")
	plt.legend()
	
	plt.xlabel("Time (s)")
	plt.tight_layout()
	plt.show()


#########
# Latencies
#########
def plot_lat_dist(data):
	lats = [int(math.modf(x/1000)[1]) for x in data.lat]
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


def plot_lat(data):
	lats = [int(math.modf(x/1000)[1]) for x in data.lat]
	
	plt.figure(figsize=(12,6))
	plt.plot(data.time, lats, label="Latencies", linewidth=0.8)
	plt.legend()
	plt.xlabel("Time (s)")
	plt.ylabel("Latency (us)")
	plt.title("Latency values")
	plt.tight_layout()
	plt.show()