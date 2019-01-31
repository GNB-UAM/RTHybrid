import pandas as pd
import numpy as np
import matplotlib.pyplot as plt
import matplotlib.gridspec as gridspec
import argparse
import math

class arguments():
	def __init__(self):
		# Possible arguments and details
		ap = argparse.ArgumentParser()
		ap.add_argument("-f", "--file",   required=True,  help="Path to the input file")
		ap.add_argument("-n", "--name",   required=False, help="Output name of the output file")
		ap.add_argument("-t", "--title",  required=False, help="Tittle")
		ap.add_argument("-fr", "--freq",  required=False, default=10000,    help="Freq. for start and end")
		ap.add_argument("-s", "--start",  required=False, default=0,        help="First data")
		ap.add_argument("-e", "--end",    required=False, help="Last data")
		ap.add_argument("-j", "--jump",   required=False, default=0,        help="Plot less points")
		ap.add_argument("-d", "--drift",  required=False, default=1,        help="Fix_drift activated")
		args = vars(ap.parse_args())

		# Parse and save arguments
		self.file    = args["file"]
		self.name    = args["name"] 
		self.title   = args["title"]
		self.freq    = int(args["freq"])
		self.jump    = int(args["jump"])
		self.drift   = int(args["drift"])
		self.start   = int(args["start"]) * self.freq

		# End is a special case
		if(args["end"]!=None):
			# Parameter case
			self.end = int(args["end"]) * int(args["freq"])
		else:
			# All the file
			self.end = sum(1 for line in open(self.file+"_1.txt",'r'))

		# Error control
		if(self.start >= self.end):
			print("ERROR: --start must be less than --end")

class DataStruct1():
	def __init__(self, args):
		#FILE
		filename   = args.file+"_1.txt"
		self.name  = args.name
		self.title = args.title

		file = open(filename,'r')
		line = file.readline()
		channels = line.split(' ')

		#NUM CHANNELS
		self.n_in_chan  = int(channels[0])
		self.n_out_chan = int(channels[1]) 
		print("Recorder in channels  = " + str(self.n_in_chan))
		print("Recorder out channels = " + str(self.n_out_chan))
		file.close()

		#READ DATA
		dataset = pd.read_csv(filename, delimiter=' ', header=1+args.start, nrows=args.end - args.start)
		data = dataset.values

		#DATA TO VARIABLES
		self.t_unix         = data[:,0]
		self.time           = data[:,1] / 1000
		self.time_ms        = data[:,1]
		self.i              = data[:,2]
		self.lat            = data[:,3]
		self.v_model        = data[:,4]
		self.v_model_scaled = data[:,5]
		self.c_model        = data[:,6]
		#self.c_viva         = data[:,7]
		#self.v_live         = data[:, 8]

		'''
		self.data_in = []
		for j in range(8, 8 + self.n_in_chan):
			self.data_in.append(data[:, j])

		self.data_out = []
		for j in range(8 + self.n_in_chan, 8 + self.n_in_chan + self.n_out_chan):
			self.data_out.append(data[:, j])
		'''

		if args.drift == 1:
			#READ DATA
			filename_drift = args.file+"_drift.txt"
			dataset_drift  = pd.read_csv(filename_drift, delimiter=' ', header=args.start, nrows=args.end - args.start)
			data_drift     = dataset_drift.values
			self.min_window = data_drift[:,0]
			self.max_window = data_drift[:,1]

		# Jump delete data for a more quick plot
		if (args.jump>0):
			new_t_unix, new_time, new_i, new_lat = [], [], [], []
			new_v_model, new_v_model_scaled, new_c_model, new_c_viva = [], [], [], []
			new_data_in, new_data_out = [], []
			if args.drift == 1:
				new_min_window = []
				new_max_window = []

			for j in range(len(self.time)):
				# Only one of #jump data is saved
				if (j%args.jump) == 0:
					new_t_unix.append(self.t_unix[j])
					new_time.append(self.time[j])
					new_i.append(self.i[j])
					new_lat.append(self.lat[j])
					new_v_model.append(self.v_model[j])
					new_v_model_scaled.append(self.v_model_scaled[j])
					new_c_model.append(self.c_model[j])
					new_c_viva.append(self.c_viva[j])
					if args.drift == 1:
						new_min_window.append(self.min_window[j])
						new_max_window.append(self.max_window[j])

			# Re-asing
			self.t_unix = new_t_unix 
			self.time = new_time
			self.i = new_i 
			self.lat = new_lat 
			self.v_model = new_v_model 
			self.v_model_scaled = new_v_model_scaled 
			self.c_model = new_c_model 
			self.c_viva = new_c_viva
			if args.drift == 1:
				self.min_window = new_min_window
				self.max_window = new_max_window 	

			# Conversions
			np_data_in = np.matrix(self.data_in)
			np_data_in = np_data_in[:,::args.jump]
			self.data_in = np_data_in.tolist()

			np_data_out = np.matrix(self.data_out)
			np_data_out = np_data_out[:,::args.jump]
			self.data_out = np_data_out.tolist()


class DataStruct2():
	def __init__(self, args):
		#ARGUMENTS
		filename = args.file+"_2.txt"
		self.name = args.name
		self.title = args.title

		#PRIMERA LINEA ES EL MODO DE AUTOCAL Y EL NUMERO DE DATOS
		file = open(filename,'r')
		line = file.readline()
		channels = line.split(' ')
		self.autocal = int(channels[0])
		print("Autocal mode = " + str(self.autocal))
		self.n_extra_data = int(channels[1]) 
		print("Num extra columns = " + str(self.n_extra_data))

		#READ DATA
		dataset = pd.read_csv(filename, delimiter=' ', header=1+args.start, nrows=args.end - args.start)
		data = dataset.values	

		#DATA TO VARIABLES
		self.time  = data[:, 0] / 1000
		self.index = data[:, 1]	
		self.ecm   = data[:, 2]	
		self.extra = data[:, 3]	

		self.data_extra = []

		if (args.jump==0):
			for j in range(4, 4+self.n_extra_data):
				self.data_extra.append(data[:, j])

		else:
			for j in range(4, 4+self.n_extra_data):
				tmp=[]
				for i in range(len(self.time)):
					if (i%args.jump) == 0:
						tmp.append(data[:, j][i])
				self.data_extra.append(tmp)

			new_time = []
			new_index  = []
			new_ecm = []
			new_extra = []

			for j in range(len(self.time)):
				if (j%args.jump) == 0:
					new_time.append(self.time[j])
					new_index.append(self.index[j])
					new_ecm.append(self.ecm[j])
					new_extra.append(self.extra[j])

			self.time = new_time
			self.index = new_index
			self.ecm = new_ecm
			self.extra = new_extra

			np_extra = np.matrix(self.extra)
			np_extra = np_extra[:,::args.jump]
			self.extra = list(np_extra)
