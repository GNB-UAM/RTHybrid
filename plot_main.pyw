import sys
import os
from plot_lib.plot_interface import *
import subprocess

class Interface(QtWidgets.QMainWindow):

	def __init__(self, parent=None):
		# Qt
		QtWidgets.QMainWindow.__init__(self, parent)
		self.ui = Ui_MainWindow()
		self.ui.setupUi(self)

		# Init and variables
		self.path_text = 'Select file...'
		self.filename = self.path_text
		self.filenotes = ''
		self.day_route = None

		# Buttons conectors
		self.ui.pushButton_plot.clicked.connect(self.pyplot_call)
		self.ui.pushButton_selectfile.clicked.connect(self.file_explorer)
		self.ui.pushButton_selectlast.clicked.connect(self.get_last)
		self.ui.pushButton_savenotes.clicked.connect(self.save_file)
		self.ui.pushButton_reload.clicked.connect(self.day_resume_reload)
		self.ui.frecuency.valueChanged.connect(self.cal_time)


	#########################
	#   Plot program call   #
	#########################
	def pyplot_call(self):
		self.filename = self.ui.textBrowser_experiment.toPlainText()
		error_plot='None'
		program  = 'python3 plot_lib/plot.py'

		# File to plot
		program += ' -f ' + self.filename
		if self.filename == self.path_text:
			error_plot='You have to select a file'
			self.ui.textBrowser_experiment.setPlainText( self.path_text )

		# Jump points
		program += ' -j ' + str( self.ui.JumpPointsValue.value() )

		# Frecuency
		program += ' -fr ' + str ( self.ui.frecuency.value() )

		# Start and end poinst
		if self.ui.PlotAll.isChecked() == False:
			s = self.ui.spinBox_from_m.value()*60 + self.ui.spinBox_from_s.value()
			e = self.ui.spinBox_to_m.value()*60   + self.ui.spinBox_to_s.value()
			if (s>=e):
				error_plot='End time must be greater than start time'
			program += ' -s ' + str(s)
			program += ' -e ' + str(e)

		# Latency
		if self.ui.latency_on.isChecked() == True:
			program += ' -lat 1'
			
		# Drift
		program += ' -d 0 '

		# Errors
		if error_plot != 'None':
			QtWidgets.QMessageBox.warning(self, "Can't plot", error_plot)

		# Plot
		else:
			print(program)
			pid=os.fork()
			if pid==0: # new process
				os.system(program)
				exit()

	##############################
	#  Funcs for custom actions  #
	##############################

	def file_explorer(self):
		self.filename = self.ui.textBrowser_experiment.toPlainText()

		if self.filename.find('s_data.txt') != -1:
			# We want to stay in the same day
			result = self.filename.split('/')[-2]
			self.filename = QtWidgets.QFileDialog.getOpenFileName(self, 'Select file', 'data/'+result, 'Text files (*_data.txt);;All files (*)')[0]
		else:
			# No day choose yet
			self.filename = QtWidgets.QFileDialog.getOpenFileName(self, 'Select file', 'data', 'Text files (*_data.txt);;All files (*)')[0]
		
		self.init_experiment()

	def get_last(self):
		# Get last day
		folders = [f for f in os.listdir('data') if os.path.dirname(os.path.join('data', f))]
		folders.sort(key=lambda x: os.path.getmtime('data/'+x))

		# No days
		if len(folders)==0:
			self.ui.pushButton_savenotes.setDisabled(True)
			self.filename = self.path_text
			return

		# Get las file of the day
		onlyfiles = [f for f in os.listdir('data/'+folders[-1]) if os.path.isfile(os.path.join('data/'+folders[-1], f)) and f.find('_data.txt')!=-1]
		onlyfiles.sort(key=lambda x: os.path.getmtime('data/'+folders[-1]+'/'+x))

		self.filename = os.getcwd()+"/data/"+folders[-1]+'/'+onlyfiles[-1]
		self.init_experiment()

	def init_experiment(self):
		if self.filename=='' or self.filename==self.path_text:
			# Bad
			self.ui.textBrowser_experiment.setPlainText(self.path_text)
			self.filename = self.path_text

			# Notes
			self.ui.pushButton_savenotes.setDisabled(True)
			self.ui.textEdit_notes.setDisabled(True)
			self.ui.textEdit_notes.setStyleSheet("background-color: rgb(235, 235, 235);")

			self.filenotes = ''
			self.ui.textEdit_notes.setPlainText('')

		else:
			# Good
			self.ui.textBrowser_experiment.setPlainText(self.filename)
			self.num_lines = sum(1 for line in open(self.filename)) - 1

			# Notes
			self.ui.pushButton_savenotes.setEnabled(True)
			self.ui.textEdit_notes.setEnabled(True)
			self.ui.textEdit_notes.setStyleSheet("background-color: rgb(245, 245, 245);")

			self.exp_notes()
			self.day_resume()
	
		self.cal_time()
		
	def day_resume(self):
		tam = len (self.filenotes.split('/')[-1:][0]) + 1
		self.day_route = self.filename[:-tam]+'log.txt'
		txt=''
		with open(self.day_route, 'r') as f:
			txt = f.read()
		self.ui.textBrowser_resume.setText(txt)
		self.ui.textBrowser_resume.setEnabled(True)
		self.ui.pushButton_reload.setEnabled(True)

		self.ui.textBrowser_resume.setStyleSheet("background-color: rgb(245, 245, 245);")
		self.ui.textBrowser_resume.verticalScrollBar().setValue(self.ui.textBrowser_resume.verticalScrollBar().maximum())

	def day_resume_reload(self):
		txt=''
		with open(self.day_route, 'r') as f:
			txt = f.read()
		self.ui.textBrowser_resume.setText( txt )
		self.ui.textBrowser_resume.verticalScrollBar().setValue(self.ui.textBrowser_resume.verticalScrollBar().maximum())
	
	def exp_notes(self):
		self.filenotes = self.filename[:-8]+'log.txt'
		txt=''
		if os.path.isfile(self.filenotes) == False:
			txt = '-------------------------------------------------------------------\n'+self.filenotes+'\n-------------------------------------------------------------------\n\n'
		else:
			with open(self.filenotes, 'r') as f:
				txt = f.read()
		self.ui.textEdit_notes.setText( txt )

	def save_file(self):
		with open(self.filenotes, 'w') as f:
			f.write( self.ui.textEdit_notes.toPlainText() )

	def cal_time(self):
		if self.filename == self.path_text:
			self.ui.label_time.setText('-')
			return

		segs = int (self.num_lines / self.ui.frecuency.value())
		if segs > 59:
			mins = int (segs/60)
			segs = segs-(mins*60)
			self.ui.label_time.setText(str(mins)+'m '+str(segs)+'s')
		else:
			self.ui.label_time.setText(str(segs)+'s')


############
#   MAIN   #
############
if __name__ == "__main__":
	app = QtWidgets.QApplication(sys.argv)

	myapp = Interface()
	myapp.show()

	sys.exit(app.exec_())