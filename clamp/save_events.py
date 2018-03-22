import plot_aux as aux
import plot_funcs as funcs
import plot_autocal as autocal

args  = aux.arguments()
data1 = aux.DataStruct1(args)
data2 = aux.DataStruct2(args)

funcs.save_events(data1, data2, args)