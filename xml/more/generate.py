lista1 = [35.0,34.0,33.0,32.0,31.0,30.0,29.0,28.0,27.0,26.0,25.0,24.0,23.0,22.0,21.0,20.0]
lista2 = [0.15, 0.2, 0.25, 0.3, 0.35, 0.4, 0.45, 0.5, 0.55, 0.6]

counter = 0
f_res = open("script.sh", 'w')
f_res.write("#!/bin/bash\n")
for i in range(len(lista2)):
	for j in range(len(lista1)):
		f  = open(str(counter)+".xml", 'w')
		f.write('<clamp>\n')

		f.write('<model type="1">\n')
		f.write('<vars>\n')
		f.write('	<x val="30.24"/>\n')
		f.write('	<y val="-5.5"/>\n')
		f.write('</vars>\n')
		f.write('<params>\n')
		f.write('	<a val="0.02"/>\n')
		f.write('	<b val="0.2"/>\n')
		f.write('	<c val="-50.0"/>\n')
		f.write('	<d val="2.0"/>\n')
		f.write('	<i val="10.0"/>\n')
		f.write('</params>\n')
		f.write('</model>\n')

		f.write('<synapse type="2">\n')
		f.write('	<g_real_to_virtual_fast val="'+str(lista2[i])+'"/>\n')
		f.write('	<syn_gradual_vfast_to_model val="'+str(lista1[j])+'"/>\n')

		f.write('	<g_real_to_virtual_slow val="0.0"/>\n')
		f.write('	<syn_gradual_vslow_to_model val="0.0"/>\n')
		f.write('	<syn_gradual_k1_to_model val="14.0"/>\n')
		f.write('	<syn_gradual_k2_to_model val="4.0"/>\n')

		f.write('	<g_virtual_to_real_fast val="0.0"/>\n')
		f.write('	<syn_gradual_vfast_to_living val="0.0"/>\n')

		f.write('	<g_virtual_to_real_slow val="0.00"/>\n')
		f.write('	<syn_gradual_vslow_to_living val="15.0"/>\n')
		f.write('	<syn_gradual_k1_to_living val="14.0"/>\n')
		f.write('	<syn_gradual_k2_to_living val="4.0"/>\n')
		f.write('</synapse>\n')

		f.write('<calib type="0"></calib>\n')

		f.write('<freq val="10"/>\n')

		f.write('<times>\n')
		f.write('	<before val="0"/>\n')
		f.write('	<duration val="300"/>\n')
		f.write('	<after val="0"/>\n')
		f.write('</times>\n')

		f.write('<output val="0"/>\n')

		f.write('<input val="0"/>\n')

		f.write('<imp val="0"/>\n')

		f.write('<firing_rate val="-1"/>\n')

		f.write('<anti val="0"/>\n')

		f.write('</clamp>\n')

		f_res.write('./clamp/stand_alone_clamp -x xml/more/'+str(counter)+'.xml\n')
		counter += 1 

f.close()
f_res.close()