import serial, time
import pandas as pd
import matplotlib.pyplot as plt
from scipy import stats
import numpy as np


'''
extra = 0
pdn = 2
lpn = 1
start = 861 * 10000

upper_th_pd = 0.8
upper_th_lp = 0.8
lower_th_pd = 0.1
lower_th_lp = 0.4

filename = "16h44m42s-06-Feb-2018_robot.txt"
dataset = pd.read_csv(filename, delimiter=' ', header=0)
data = dataset.values
v_pd = data[start:,pdn]
v_lp = data[start:,lpn]
'''
'''
t = 3
pdn = 5
lpn = 4
start = 0

upper_th_pd = 0.8
upper_th_lp = 0.8
lower_th_pd = 0.1
lower_th_lp = 0.1

filename = "gh_cpg4.txt"
dataset = pd.read_csv(filename, delimiter=' ', header=1)
data = dataset.values
v_pd = data[start:,pdn]
v_lp = data[start:,lpn]
'''
'''
t = 3
pdn = 2
lpn = 3
start = 10000

upper_th_pd = 0.8
upper_th_lp = 0.8
lower_th_pd = 0.3
lower_th_lp = 0.45

filename = "res_GH_63.00_0.85.txt"
dataset = pd.read_csv(filename, delimiter=' ', header=1)
data = dataset.values
v_pd = data[start:,pdn]
v_lp = data[start:,lpn]
'''

'''
t = 3
pdn = 2
lpn = 3
start = 10000

upper_th_pd = 0.8
upper_th_lp = 0.8
lower_th_pd = 0.1
lower_th_lp = 0.45

filename = "res_GH_75.00_0.90.txt"
dataset = pd.read_csv(filename, delimiter=' ', header=1)
data = dataset.values
v_pd = data[start:,pdn]
v_lp = data[start:,lpn]
'''

'''
t = 3
pdn = 2
lpn = 3
start = 100000

upper_th_pd = 0.8
upper_th_lp = 0.8
lower_th_pd = 0.1
lower_th_lp = 0.1

filename = "res_GH_36.00_0.50.txt"
dataset = pd.read_csv(filename, delimiter=' ', header=1)
data = dataset.values
v_pd = data[start:-start,pdn]
v_lp = data[start:-start,lpn]
'''


t = 3
pdn = 2
lpn = 3
start = 10*10000
end = 42*10000

upper_th_pd = 0.8
upper_th_lp = 0.8
lower_th_pd = 0.1
lower_th_lp = 0.1

filename = "data/2019y_6m_6d/16h_20m_58s_data.txt"
dataset = pd.read_csv(filename, delimiter=' ', header=1)
data = dataset.values
v_pd = data[start:-end,pdn]
v_lp = data[start:-end,lpn]

plt.plot(v_pd)
plt.plot(v_lp)
plt.show()


'''
ser = serial.Serial('/dev/rfcomm0', 19200)
n = 2
'''




flag_v_pd = 0
times_v_pd = []
times2_v_pd = []
events_v_pd = []
events2_v_pd = []
min_v_pd = min(v_pd[0:15000])
max_v_pd = max(v_pd[0:15000])
r_v_pd = max_v_pd - min_v_pd

flag_v_lp = 0
times_v_lp = []
times2_v_lp = []
events_v_lp = []
events2_v_lp = []
min_v_lp = min(v_lp[0:15000])
max_v_lp = max(v_lp[0:15000])
r_v_lp = max_v_lp - min_v_lp

n0 = []
n1 = []
n0_e = []
n1_e = []
flag_n0 = 0
flag_n1 = 0


lppd_interval = []
delay = []
period = []
end_lp = []

last_spike_lp_t = 0
last_spike_lp_v = 0
last_spike_pd_t = 0
last_spike_pd_v = 0

for i in range(len(v_pd)):
		#time.sleep(0.0001)

		if (v_pd[i] > (min_v_pd + r_v_pd*upper_th_pd) and flag_v_pd == 1):
			flag_v_pd = 0

			if (len(times_v_lp) > 0):
				lppd_interval.append(i - times_v_lp[-1])

			if (len(end_lp) > 0 and len(times_v_lp) > 0):	
				delay.append(i - end_lp[-1])

			times_v_pd.append(i)
			events_v_pd.append(v_pd[i])
		elif(v_pd[i] > (min_v_pd + r_v_pd*upper_th_pd)):
			last_spike_pd_t = i
			last_spike_pd_v = v_pd[i]
		elif (v_pd[i] < (min_v_pd + r_v_pd*lower_th_pd) and flag_v_pd == 0):
			flag_v_pd = 1

			if (last_spike_pd_v != 0):
				times2_v_pd.append(last_spike_pd_t)
				events2_v_pd.append(last_spike_pd_v)

		if (v_lp[i] > (min_v_lp + r_v_lp*upper_th_lp) and flag_v_lp == 1):
			flag_v_lp = 0

			if (len(times_v_lp) > 0):	
				period.append(i - times_v_lp[-1])
				#ser.write("%01#RDD0010000107**\r".encode())

			times_v_lp.append(i)
			events_v_lp.append(v_lp[i])
		elif(v_lp[i] > (min_v_lp + r_v_lp*upper_th_lp)):
			last_spike_lp_t = i
			last_spike_lp_v = v_lp[i]
		elif (v_lp[i] < (min_v_lp + r_v_lp*lower_th_lp) and flag_v_lp == 0):
			flag_v_lp = 1

			if (last_spike_lp_v != 0):
				end_lp.append(last_spike_lp_t)
				times2_v_lp.append(last_spike_lp_t)
				events2_v_lp.append(last_spike_lp_v)


		if (i % 15000 == 0):
			min_v_lp = min(v_lp[i:i+15000])
			max_v_lp = max(v_lp[i:i+15000])

			min_v_pd = min(v_pd[i:i+15000])
			max_v_pd = max(v_pd[i:i+15000])

		#print("v_pd %d v_lp %d"%(flag_v_pd, flag_v_lp))

		'''
		if (flag_v_pd == 1 and flag_v_lp == 0):
			if (len(lppd_interval) > 0 and len(period) > 0):
				print(lppd_interval[-1] / period[-1])
		'''

		'''
		if (flag_v_pd == 1 and flag_v_lp == 0):
			n = 0
		elif(flag_v_pd == 0 and flag_v_lp == 1):
			n = 1

		if (n == 0 and flag_n0 == 0):
			ser.write(b'0')
			flag_n0 = 1
			flag_n1 = 0
			n0.append(i)
			n0_e.append(0)
		elif (n == 1 and flag_n1 == 0):
			ser.write(b'1')
			flag_n1 = 1
			flag_n0 = 0
			n1.append(i)
			n1_e.append(0)
		'''



#ser.close()




plt.plot(times_v_pd, events_v_pd, "o")
plt.plot(times2_v_pd, events2_v_pd, "o")
plt.plot(v_pd)

plt.plot(times_v_lp, events_v_lp, "o")
plt.plot(times2_v_lp, events2_v_lp, "o")
plt.plot(v_lp)

plt.plot(n0, n0_e, "o")
plt.plot(n1, n1_e, "o")
plt.show()

print(len(period))
print(len(lppd_interval))
print(len(delay))

#Discard extra intervals
if (len(period) < len(lppd_interval)):
	lppd_interval = lppd_interval[:len(period) - len(lppd_interval)]

if (len(period) < len(delay)):
	delay = delay[:len(period) - len(delay)]

if (len(period) > len(lppd_interval)):
	period = period[:len(lppd_interval) - len(period)]

#To seconds
period = [x/10000 for x in period]
lppd_interval = [y/10000 for y in lppd_interval]
delay = [z/10000 for z in delay]

#Calculate R2
slope_interval, intercept_interval, r_interval, pvalue_interval, std_error_interval = stats.linregress(period, lppd_interval)
slope_delay, intercept_delay, r_delay, pvalue_delay, std_error_delay = stats.linregress(period, delay)

r2_interval = r_interval*r_interval
r2_delay = r_delay*r_delay

print("Interval: %f %f"%(slope_interval, r2_interval))
print("Delay: %f %f"%(slope_delay, r2_delay))


#Print invariant
plt.scatter(period, lppd_interval, c=np.linspace(0, len(v_lp)/10000, len(period)), cmap=plt.get_cmap("Blues"))
plt.colorbar()
plt.scatter(period, delay, c=np.linspace(0, len(v_lp)/10000, len(period)), cmap=plt.get_cmap("Reds"))
plt.colorbar()

plt.plot(period, intercept_interval+(slope_interval*np.asarray(period)), alpha=0.5, color='blue', label="R2 LPPD=%f"%r2_interval)
plt.plot(period, intercept_delay+(slope_delay*np.asarray(period)), alpha=0.5, color='red', label="R2 Delay=%f"%r2_delay)
plt.legend()

plt.xlabel('Period (s)')
plt.ylabel('LPPD interval/Delay (s)')

plt.show()

'''
ser = serial.Serial('/dev/rfcomm4', 19200)
#ser = serial.Serial('/dev/ttyUSB0', 9600)

print(ser)


while(1):
	n = input("")

	if (n == "0"):
		ser.write(b'0')
	else:
		ser.write(b'1')
'''
'''
ser.write(b'1')

time.sleep(2)

ser.write(b'0')

time.sleep(2)

ser.write(b'1')
'''


'''
time.sleep(2)
rawString = ser.readline()
print(rawString)
ser.close()
''' 
