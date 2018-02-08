#-------------------------------------------------
#
# Project created by QtCreator 2017-09-18T17:58:06
#
#-------------------------------------------------

QT       += core gui multimedia

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = RTHybrid
TEMPLATE = app

OBJECTS_DIR = obj/
MOC_DIR = moc/
QMAKE_CLEAN += $$TARGET

QMAKE_LIBS += -lpthread -lrt -lm
QMAKE_CFLAGS += -D_GNU_SOURCE

exists(/usr/xenomai/bin/xeno-config) {
    XEN_VERSION = $$system(/usr/xenomai/bin/xeno-config --version)
    message("Compiling for Xenomai "$$XEN_VERSION)

    QMAKE_LIBS += -lanalogy $(shell /usr/xenomai/bin/xeno-config --skin=posix --ldflags)
    QMAKE_CFLAGS += $(shell /usr/xenomai/bin/xeno-config --skin=posix --cflags)
    QMAKE_CC = $(shell /usr/xenomai/bin/xeno-config --cc)

    contains(XEN_VERSION, '.*2\.[0-9]\.[0-9].*') {
        QMAKE_LIBS += -lrtdm
    }

    SOURCES += \ 
    	clamp/src/analogy_functions.c \

} else {
    KERNEL_VERSION = $$system(uname -r)
    message("Compiling for Linux "$$KERNEL_VERSION)

    QMAKE_LIBS += -lcomedi

    SOURCES += \ 
    	clamp/src/comedi_functions.c \
}




# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0


SOURCES += gui/main.cpp \
    clamp/src/model_library.c \
    clamp/src/rt_thread_functions.c \
    clamp/src/writer_thread_functions.c \
    clamp/src/calibrate_functions_phase2_a.c \
    clamp/src/calibrate_functions_phase1.c \
    clamp/src/calibrate_functions_phase2.c \
    clamp/src/time_functions.c \
    clamp/src/queue_functions.c \
    clamp/src/clamp.c \
    common/src/aux_functions.c \
    gui/rthybrid.cpp

HEADERS += \
    clamp/includes/calibrate_functions_phase1.h \
    clamp/includes/calibrate_functions_phase2.h \
    clamp/includes/calibrate_functions_phase2_a.h \
    clamp/includes/device_functions.h \
    clamp/includes/model_library.h \
    clamp/includes/queue_functions.h \
    clamp/includes/rt_thread_functions.h \
    clamp/includes/time_functions.h \
    common/includes/types.h \
    clamp/includes/writer_thread_functions.h \
    clamp/includes/clamp.h \
    clamp/includes/types_clamp.h \
    gui/rthybrid.h

FORMS += \
    gui/rthybrid.ui
