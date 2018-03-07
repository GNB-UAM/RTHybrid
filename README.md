# RTHybrid
RTHybrid is a real-time neuron and synapse model library designed to build electrophysiological hybrid circuits with living neurons. It works with Xenomai 2, Xenomai 3, Preempt-RT and also non real-time Linux.

### Developed by
Rodrigo Amaducci (rodrigo.amaducci@uam.es - [scholar](https://scholar.google.es/citations?user=Lq4ogOQAAAAJ))

Manuel Reyes-Sanchez (manuel.reyes@uam.es - [scholar](https://scholar.google.es/citations?user=JlKzj1cAAAAJ))

Grupo de Neurocomputación Biológica [(GNB)](http://arantxa.ii.uam.es/~gnb/) - Escuela Politécnica Superior [(EPS)](http://www.uam.es/ss/Satellite/EscuelaPolitecnica/es/home.htm)

Universidad Autónoma de Madrid [(UAM)](http://www.uam.es)


## Dependencies
- Linux RT kernel (RT PREEMPT)
- Comedi and DAQ
- Qt

## Install
- Detailed installation instructions for each platform can be found [here](https://github.com/RoyVII/RTHybrid/wiki/Installation-guide).


## Data file details
See data/about.txt

## Plots
Some Python Matplotlib programs are included. The programs read the files properly and include the data in Python variables. You can adapt the programs to plot what you need. 

## Neuron models included
- Hindmarsh–Rose
- Izhikevich
- Rulkov map

## Synapsis models included
- Electrical synapse
- Gradual chemical synapse
