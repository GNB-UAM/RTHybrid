#!/bin/bash
sudo /usr/lib/x86_64-linux-gnu/qt5/bin/qmake -spec linux-g++ CONFIG+=release CONFIG+=qml_release -o Makefile rthybrid.pro
make clean
make
echo "\nCompilation ended"
