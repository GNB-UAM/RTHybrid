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
		self.v_live = data[:, 8]

		self.data_in = []
		for j in range(8, 8 + self.n_in_chan):
			self.data_in.append(data[:, j])

		self.data_out = []
		for j in range(8 + self.n_in_chan, 8 + self.n_in_chan + self.n_out_chan):
			self.data_out.append(data[:, j])

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
		for j in range(4, 4+self.n_extra_data):
			self.data_extra.append(data[:, j])
