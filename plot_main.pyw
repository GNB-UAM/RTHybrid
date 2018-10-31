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
		self.setWindowIcon(QtGui.QIcon('assets/logo_rthy.png'))
		self.expand=False
		self.show()

		# Init and variables
		self.path_text = 'Select file...'
		self.route = self.path_text
		self.filename = ''
		self.filenotes = ''
		self.fileday = ''
		self.day_route = None

		# Buttons conectors
		self.ui.pushButton_plot.clicked.connect(self.pyplot_call)
		self.ui.pushButton_selectfile.clicked.connect(self.file_explorer)
		self.ui.pushButton_selectlast.clicked.connect(self.get_last)
		self.ui.pushButton_savenotes.clicked.connect(self.save_notes)
		self.ui.pushButton_saveday.clicked.connect(self.save_day)
		self.ui.pushButton_reload.clicked.connect(self.day_resume_reload)
		self.ui.frecuency.valueChanged.connect(self.cal_time)
		self.ui.edit_mode.clicked.connect(self.editable_on)
		self.ui.push_resize.clicked.connect(self.size)

	#########################
	#   Plot program call   #
	#########################
	def pyplot_call(self):
		self.route = self.ui.textBrowser_experiment.toPlainText()
		error_plot='None'
		program  = 'python3 plot_lib/plot.py'

		# File to plot
		program += ' -f ' + self.route
		if self.route == self.path_text:
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
		self.route = self.ui.textBrowser_experiment.toPlainText()

		if self.route.find('s_data.txt') != -1:
			# We want to stay in the same day
			result = self.route.split('/')[-2]
			self.route = QtWidgets.QFileDialog.getOpenFileName(self, 'Select file', 'data/'+result, 'Text files (*_data.txt);;All files (*)')[0]
		else:
			# No day choose yet
			self.route = QtWidgets.QFileDialog.getOpenFileName(self, 'Select file', 'data', 'Text files (*_data.txt);;All files (*)')[0]
		
		if self.route != '':
			self.filename = self.route.split('/')[-2] +'/'+ self.route.split('/')[-1]
			self.fileday = '/'.join ( self.route.split('/')[:-1] ) + '/log.txt'
		else:
			self.filename = ''
			self.fileday = ''

		self.init_experiment()

	def get_last(self):
		# Get last day
		folders = [f for f in os.listdir('data') if os.path.dirname(os.path.join('data', f))]
		folders.sort(key=lambda x: os.path.getmtime('data/'+x))

		# No days
		if len(folders)==0:
			self.ui.pushButton_savenotes.setDisabled(True)
			self.ui.pushButton_savenotes.setStyleSheet("")
			self.route = self.path_text
			self.fileday = ''
			return

		# Get las file of the day
		onlyfiles = [f for f in os.listdir('data/'+folders[-1]) if os.path.isfile(os.path.join('data/'+folders[-1], f)) and f.find('_data.txt')!=-1]
		onlyfiles.sort(key=lambda x: os.path.getmtime('data/'+folders[-1]+'/'+x))

		self.filename = folders[-1]+'/'+onlyfiles[-1]
		self.route = os.getcwd()+"/data/"+folders[-1]+'/'+onlyfiles[-1]
		self.fileday = os.getcwd()+"/data/"+folders[-1]+'/log.txt'
		self.init_experiment()

	def init_experiment(self):
		if self.route=='' or self.route==self.path_text:
			# Bad
			self.ui.textBrowser_experiment.setPlainText(self.path_text)
			self.route = self.path_text

			self.ui.pushButton_plot.setDisabled(True)
			self.ui.pushButton_plot.setStyleSheet("")

			# Notes
			self.ui.pushButton_savenotes.setDisabled(True)
			self.ui.pushButton_savenotes.setStyleSheet("")
			self.ui.textEdit_notes.setDisabled(True)
			self.ui.textEdit_notes.setStyleSheet("background-color: rgb(235, 235, 235);")

			self.filenotes = ''
			self.ui.textEdit_notes.setPlainText('')

		else:
			# Good
			self.ui.textBrowser_experiment.setPlainText(self.route)
			self.num_lines = sum(1 for line in open(self.route)) - 1

			self.ui.pushButton_plot.setEnabled(True)
			self.ui.pushButton_plot.setStyleSheet("background:rgb(32, 74, 135); color:white")

			# Notes
			self.ui.pushButton_savenotes.setEnabled(True)
			self.ui.pushButton_savenotes.setStyleSheet("background:rgb(78, 154, 6); color:white;")
			self.ui.textEdit_notes.setEnabled(True)
			self.ui.textEdit_notes.setStyleSheet("background-color: rgb(245, 245, 245);")

			self.exp_notes()
			self.day_resume()
	
		self.cal_time()
		
	def day_resume(self):
		tam = len (self.filenotes.split('/')[-1:][0]) + 1
		self.day_route = self.route[:-tam]+'log.txt'
		txt=''
		with open(self.day_route, 'r') as f:
			txt = f.read()
		self.ui.textEdit_resume.setText(txt)
		self.ui.textEdit_resume.setEnabled(True)

		self.ui.edit_mode.setEnabled(True)

		self.ui.pushButton_reload.setEnabled(True)
		self.ui.pushButton_reload.setStyleSheet("background:rgb(78, 154, 6);")

		self.ui.textEdit_resume.setStyleSheet("background-color: rgb(245, 245, 245);")
		self.ui.textEdit_resume.verticalScrollBar().setValue(self.ui.textEdit_resume.verticalScrollBar().maximum())

	def day_resume_reload(self):
		txt=''
		with open(self.day_route, 'r') as f:
			txt = f.read()
		self.ui.textEdit_resume.setText( txt )
		self.ui.textEdit_resume.verticalScrollBar().setValue(self.ui.textEdit_resume.verticalScrollBar().maximum())
	
	def exp_notes(self):
		self.filenotes = self.route[:-8]+'log.txt'
		txt=''
		if os.path.isfile(self.filenotes) == False:
			txt = self.filename+'\n------------------------------------------------------\n\n'
		else:
			with open(self.filenotes, 'r') as f:
				txt = f.read()
		self.ui.textEdit_notes.setText( txt )

	def save_notes(self):
		with open(self.filenotes, 'w') as f:
			f.write( self.ui.textEdit_notes.toPlainText() )

	def save_day(self):
		with open(self.fileday, 'w') as f:
			f.write( self.ui.textEdit_resume.toPlainText() )

	def editable_on(self):
		if self.ui.edit_mode.isChecked() == True:
			self.ui.pushButton_saveday.setEnabled(True)
			self.ui.pushButton_saveday.setStyleSheet("background:rgb(78, 154, 6); color:white;")
			self.ui.textEdit_resume.setTextInteractionFlags(QtCore.Qt.TextEditable | QtCore.Qt.TextSelectableByMouse | QtCore.Qt.TextSelectableByKeyboard);

		else:
			self.ui.pushButton_saveday.setDisabled(True)
			self.ui.pushButton_saveday.setStyleSheet("")
			self.ui.textEdit_resume.setTextInteractionFlags(QtCore.Qt.TextSelectableByMouse | QtCore.Qt.TextSelectableByKeyboard);

	def cal_time(self):
		if self.route == self.path_text:
			self.ui.label_time.setText('-')
			return

		segs = int (self.num_lines / self.ui.frecuency.value())
		if segs > 59:
			mins = int (segs/60)
			segs = segs-(mins*60)
			self.ui.label_time.setText(str(mins)+'m '+str(segs)+'s')
		else:
			self.ui.label_time.setText(str(segs)+'s')

	def size(self):
		if self.expand==True:
			self.resize(510,0)
			self.expand=False
		else:
			self.resize(1450,0)
			self.expand=True



############
#   MAIN   #
############
if __name__ == "__main__":
	app = QtWidgets.QApplication(sys.argv)
	myapp = Interface()
	myapp.resize(510, 0)
	myapp.show()
	sys.exit(app.exec_())