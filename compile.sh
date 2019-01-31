#!/bin/bash
while getopts c: option
do
	case "${option}"
	in
	c) CORE_NUMBER=${OPTARG};;
	esac
done

if [ -z ${CORE_NUMBER+x} ]; 
	then sudo /usr/lib/x86_64-linux-gnu/qt5/bin/qmake -spec linux-g++ CONFIG+=release CONFIG+=qml_release -o Makefile rthybrid.pro; 
	else sudo /usr/lib/x86_64-linux-gnu/qt5/bin/qmake -spec linux-g++ CONFIG+=release CONFIG+=qml_release CONFIG+=isol_core CORE=$CORE_NUMBER -o Makefile rthybrid.pro; 
fi

#sudo /usr/lib/x86_64-linux-gnu/qt5/bin/qmake -spec linux-g++ CONFIG+=release CONFIG+=qml_release -o Makefile rthybrid.pro
make clean
make
echo "\nCompilation ended"
