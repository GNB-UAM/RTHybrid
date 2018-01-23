import pandas as pd
import numpy as np
import matplotlib.pyplot as plt
import matplotlib.gridspec as gridspec
import argparse
import math

class DataStruct1():
	def __init__(self, ap):
		#ARGUMENTS
		ap.add_argument("-f", "--file", required=True, help="Path to the input file")
		ap.add_argument("-n", "--name", required=False, help="Output name of the output file")
		ap.add_argument("-t", "--title", required=False, help="Tittle")
		ap.add_argument("-s", "--start", required=False, help="First data", default=0)
		ap.add_argument("-e", "--end", required=False, help="Last data")
		ap.add_argument("-fr", "--freq", required=False, help="Freq. for start and end")
		ap.add_argument("-j", "--jump", required=False, help="Plot less points", default=0)


		args = vars(ap.parse_args())

		filename = args["file"]+"_1.txt"

		if(args["end"]!=None and args["freq"]!=None):
			args["end"] = int(args["end"]) * int(args["freq"])

		if(args["start"]!=None and args["freq"]!=None):
			args["start"] = int(args["start"]) * int(args["freq"])

		if(args["end"]==None):
			args["end"] = sum(1 for line in open(filename,'r'))

		if(int(args["start"]) >= int(args["end"])):
			print("ERROR: Start data must be less than End data")

		self.file = filename
		self.name = args["name"]
		self.title = args["title"]

		#FILE
		file = open(filename,'r')
		line = file.readline()
		channels = line.split(' ')

		#NUM CHANNELS
		self.n_in_chan = int(channels[0])
		self.n_out_chan = int(channels[1]) 
		print("Recorder in channels  = " + str(self.n_in_chan))
		print("Recorder out channels = " + str(self.n_out_chan))
		file.close()

		#READ DATA
		dataset = pd.read_csv(filename, delimiter=' ', header=1)
		array = dataset.values
		data = array[int(args["start"]):int(args["end"]),:]

		#DATA TO VARIABLES
		self.t_unix = data[:,0]
		self.time = data[:,1] / 1000
		self.i = data[:,2]
		self.lat = data[:,3]
		self.v_model = data[:,4]
		self.v_model_scaled = data[:,5]
		self.c_model = data[:,6]
		self.c_viva = data[:,7]
		#self.v_live = data[:, 8]

		self.data_in = []
		for j in range(8, 8 + self.n_in_chan):
			self.data_in.append(data[:, j])

		self.data_out = []
		for j in range(8 + self.n_in_chan, 8 + self.n_in_chan + self.n_out_chan):
			self.data_out.append(data[:, j])

		if (int(args["jump"])>0):
			new_t_unix = []
			new_time = []
			new_i = []
			new_lat = []
			new_v_model = []
			new_v_model_scaled = []
			new_c_model = []
			new_c_viva = []
			new_data_in = []
			new_data_out = []
			for j in range(len(self.time)):
				if (j%int(args["jump"])) == 0:
					new_t_unix.append(self.t_unix[j])
					new_time.append(self.time[j])
					new_i.append(self.i[j])
					new_lat.append(self.lat[j])
					new_v_model.append(self.v_model[j])
					new_v_model_scaled.append(self.v_model_scaled[j])
					new_c_model.append(self.c_model[j])
					new_c_viva.append(self.c_viva[j])

			self.t_unix = new_t_unix 
			self.time = new_time
			self.i = new_i 
			self.lat = new_lat 
			self.v_model = new_v_model 
			self.v_model_scaled = new_v_model_scaled 
			self.c_model = new_c_model 
			self.c_viva = new_c_viva 	

			np_data_in = np.matrix(self.data_in)
			np_data_in = np_data_in[:,::int(args["jump"])]
			self.data_in = np_data_in.tolist()

			np_data_out = np.matrix(self.data_out)
			np_data_out = np_data_out[:,::int(args["jump"])]
			self.data_out = np_data_out.tolist()


class DataStruct2():
	def __init__(self, ap):

		#ARGUMENTS
		args = vars(ap.parse_args())
		filename = args["file"]+"_2.txt"
		self.file = filename

		#PRIMERA LINEA ES EL MODO DE AUTOCAL Y EL NUMERO DE DATOS
		file = open(filename,'r')
		line = file.readline()
		channels = line.split(' ')
		self.autocal = int(channels[0])
		print("Autocal mode = " + str(self.autocal))
		self.n_extra_data = int(channels[1]) 
		print("Num extra columns = " + str(self.n_extra_data))

		#READ DATA
		dataset = pd.read_csv(filename, delimiter=' ', header=1)
		array = dataset.values

		if(args["end"]!=None and args["freq"]!=None):
			args["end"] = int(args["end"]) * int(args["freq"])

		if(args["start"]!=None and args["freq"]!=None):
			args["start"] = int(args["start"]) * int(args["freq"])

		if(args["end"]==None):
			args["end"] = sum(1 for line in open(filename,'r'))
			
		data = array[int(args["start"]):int(args["end"]),:]

		#DATA TO VARIABLES
		self.time = data[:, 0] / 1000
		self.index = data[:,1]	
		self.ecm = data[:,2]	
		self.extra = data[:,3]	

		self.data_extra = []

		if (int(args["jump"])==0):
			for j in range(4, 4+self.n_extra_data):
				self.data_extra.append(data[:, j])

		else:
			for j in range(4, 4+self.n_extra_data):
				tmp=[]
				for i in range(len(self.time)):
					if (i%int(args["jump"])) == 0:
						tmp.append(data[:, j][i])
				self.data_extra.append(tmp)

			new_time = []
			new_index  = []
			new_ecm = []
			new_extra = []

			for j in range(len(self.time)):
				if (j%int(args["jump"])) == 0:
					new_time.append(self.time[j])
					new_index.append(self.index[j])
					new_ecm.append(self.ecm[j])
					new_extra.append(self.extra[j])

			self.time = new_time
			self.index = new_index
			self.ecm = new_ecm
			self.extra = new_extra

			np_extra = np.matrix(self.extra)
			np_extra = np_extra[:,::int(args["jump"])]
			self.extra = list(np_extra)
