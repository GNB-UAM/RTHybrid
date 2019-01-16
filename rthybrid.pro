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
UI_DIR = ui/
QMAKE_CLEAN += $$TARGET

QMAKE_LIBS += -lpthread -lrt -lm -lxml2
QMAKE_CFLAGS += -D_GNU_SOURCE -I/usr/include/libxml2
QMAKE_CXXFLAGS += -I/usr/include/libxml2

#QMAKE_LIBS += -lpthread -lrt -lm $(shell xml2-config --libs)
#QMAKE_CFLAGS += -D_GNU_SOURCE $(shell xml2-config --cflags)
#QMAKE_CXXFLAGS += $(shell xml2-config --cflags)


isol_core {
    message(Compiling with binding core $${CORE}...)
    QMAKE_CFLAGS += -D__CORE__=$${CORE}
}


IPIPE = $$system(dmesg | grep -i xenomai)
contains( IPIPE, Xenomai ): {
    XEN_VERSION = $$system(/usr/xenomai/bin/xeno-config --version)
    message("Compiling for Xenomai "$$XEN_VERSION)

    QMAKE_LIBS += -lanalogy $(shell /usr/xenomai/bin/xeno-config --skin=posix --ldflags)
    QMAKE_CFLAGS += $(shell /usr/xenomai/bin/xeno-config --skin=posix --cflags) -D__XENO__
    QMAKE_CC = $(shell /usr/xenomai/bin/xeno-config --cc)

    contains(XEN_VERSION, '.*2\.[0-9]\.[0-9].*') {
        QMAKE_LIBS += -lrtdm
    }

    SOURCES += \ 
        clamp/src/analogy_functions.c \
        clamp/src/xddp_functions.c \

} else {
    KERNEL_VERSION = $$system(uname -r)
    message("Compiling for Linux "$$KERNEL_VERSION)

    QMAKE_LIBS += -lcomedi

    SOURCES += \ 
        clamp/src/comedi_functions.c \
        clamp/src/queue_functions.c \
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


SOURCES += \
    common/src/aux_functions.c \
    common/src/file_selector_functions.c \
    common/src/xml_parser_functions.c \
    gui/rthybrid.cpp \
    gui/rthybrid_xml_main.cpp \
    gui/clamplauncher.cpp \
    gui/main.cpp \
    clamp/src/calibrate_functions_phase1.c \
    clamp/src/calibrate_functions_phase2.c \
    clamp/src/calibrate_functions_phase2_a.c \
    clamp/src/clamp.c \
    clamp/src/rt_thread_functions.c \
    clamp/src/time_functions.c \
    clamp/src/writer_thread_functions.c \
    clamp/src/xml_clamp_parser.c \
    model_library/integration_methods.c \
    model_library/neuron/neuron_models_aux_functions.c \
    model_library/neuron/Wang_1993/nm_gui_wang_1993.cpp \
    model_library/neuron/Ghigliazza_Holmes_2004/nm_gui_ghigliazza_holmes_2004.cpp \
    model_library/neuron/Hindmarsh_Rose_1986/nm_gui_hindmarsh_rose_1986.cpp \
    model_library/neuron/Izhikevich_2003/nm_gui_izhikevich_2003.cpp \
    model_library/neuron/Rulkov_2002/nm_gui_rulkov_2002.cpp \
    model_library/neuron/Izhikevich_2003/nm_izhikevich_2003.c \
    model_library/neuron/Hindmarsh_Rose_1986/nm_hindmarsh_rose_1986.c \
    model_library/neuron/Rulkov_2002/nm_rulkov_2002.c \
    model_library/neuron/Ghigliazza_Holmes_2004/nm_ghigliazza_holmes_2004.c \
    model_library/neuron/Wang_1993/nm_wang_1993.c \
    model_library/neuron/neuron_models_functions.c \
    model_library/neuron/Empty/nm_empty.c \
    model_library/synapse/Electrical/sm_gui_electrical.cpp \
    model_library/synapse/Empty/sm_empty.c \
    model_library/synapse/synapse_models_functions.c \
    model_library/synapse/Electrical/sm_electrical.c \
    model_library/synapse/Golowasch_et_al_1999/sm_golowasch_et_al_1999.c \
    model_library/synapse/Electrical/sm_xml_electrical.c \
    model_library/synapse/Golowasch_et_al_1999/sm_xml_golowasch_et_al_1999.c \
    model_library/neuron/Ghigliazza_Holmes_2004/nm_xml_ghigliazza_holmes_2004.c \
    model_library/neuron/Izhikevich_2003/nm_xml_izhikevich_2003.c \
    model_library/neuron/Wang_1993/nm_xml_wang_1993.c \
    model_library/neuron/Hindmarsh_Rose_1986/nm_xml_hindmarsh_rose_1986.c \
    model_library/neuron/Rulkov_2002/nm_xml_rulkov_2002.c \
    model_library/synapse/Golowasch_et_al_1999/sm_gui_golowasch_et_al_1999.cpp \
    model_library/synapse/Destexhe_et_al_1994/sm_destexhe_et_al_1994.c \
    model_library/synapse/Destexhe_et_al_1994/sm_gui_destexhe_et_al_1994.cpp \
    model_library/synapse/Destexhe_et_al_1994/sm_xml_destexhe_et_al_1994.c \
    model_library/synapse/Greenberg_Manor_2005/sm_gui_greenberg_manor_2005.cpp \
    model_library/synapse/Greenberg_Manor_2005/sm_greenberg_manor_2005.c \
    model_library/synapse/Greenberg_Manor_2005/sm_xml_greenberg_manor_2005.c

HEADERS += \
    common/includes/file_selector_functions.h \
    common/includes/xml_parser_functions.h \
    common/includes/types.h \
    gui/rthybrid.h \
    gui/rthybrid_xml_main.h \
    gui/clamplauncher.h \
    clamp/includes/calibrate_functions_phase1.h \
    clamp/includes/calibrate_functions_phase2.h \
    clamp/includes/calibrate_functions_phase2_a.h \
    clamp/includes/clamp.h \
    clamp/includes/device_functions.h \
    clamp/includes/queue_functions.h \
    clamp/includes/rt_thread_functions.h \
    clamp/includes/time_functions.h \
    clamp/includes/types_clamp.h \
    clamp/includes/writer_thread_functions.h \
    clamp/includes/xml_clamp_parser.h \
    moc/moc_predefs.h \
    model_library/integration_methods.h \
    model_library/neuron/Wang_1993/nm_gui_wang_1993.h \
    model_library/neuron/Ghigliazza_Holmes_2004/nm_gui_ghigliazza_holmes_2004.h \
    model_library/neuron/Hindmarsh_Rose_1986/nm_gui_hindmarsh_rose_1986.h \
    model_library/neuron/Izhikevich_2003/nm_gui_izhikevich_2003.h \
    model_library/neuron/Rulkov_2002/nm_gui_rulkov_2002.h \
    model_library/neuron/Izhikevich_2003/nm_izhikevich_2003.h \
    model_library/neuron/Hindmarsh_Rose_1986/nm_hindmarsh_rose_1986.h \
    model_library/neuron/Rulkov_2002/nm_rulkov_2002.h \
    model_library/neuron/Ghigliazza_Holmes_2004/nm_ghigliazza_holmes_2004.h \
    model_library/neuron/Wang_1993/nm_wang_1993.h \
    model_library/neuron/neuron_models_functions.h \
    model_library/neuron/Empty/nm_empty.h \
    model_library/synapse/Electrical/sm_gui_electrical.h \
    model_library/synapse/Empty/sm_empty.h \
    model_library/synapse/synapse_models_functions.h \
    model_library/synapse/Electrical/sm_electrical.h \
    model_library/synapse/Golowasch_et_al_1999/sm_golowasch_et_al_1999.h \
    model_library/synapse/Golowasch_et_al_1999/sm_xml_golowasch_et_al_1999.h \
    model_library/synapse/Electrical/sm_xml_electrical.h \
    model_library/xml_models.h \
    model_library/neuron/Ghigliazza_Holmes_2004/nm_xml_ghigliazza_holmes_2004.h \
    model_library/neuron/Izhikevich_2003/nm_xml_izhikevich_2003.h \
    model_library/neuron/Wang_1993/nm_xml_wang_1993.h \
    model_library/neuron/Hindmarsh_Rose_1986/nm_xml_hindmarsh_rose_1986.h \
    model_library/neuron/Rulkov_2002/nm_xml_rulkov_2002.h \
    model_library/synapse/Golowasch_et_al_1999/sm_gui_golowasch_et_al_1999.h \
    model_library/synapse/Destexhe_et_al_1994/sm_destexhe_et_al_1994.h \
    model_library/synapse/Destexhe_et_al_1994/sm_gui_destexhe_et_al_1994.h \
    model_library/synapse/Destexhe_et_al_1994/sm_xml_destexhe_et_al_1994.h \
    model_library/synapse/Greenberg_Manor_2005/sm_greenberg_manor_2005.h \
    model_library/synapse/Greenberg_Manor_2005/sm_gui_greenberg_manor_2005.h \
    model_library/synapse/Greenberg_Manor_2005/sm_xml_greenberg_manor_2005.h \
    model_library/neuron/neuron_models_aux_functions.h

FORMS += \
    gui/rthybrid.ui \
    model_library/neuron/Wang_1993/nm_gui_wang_1993.ui \
    model_library/neuron/Ghigliazza_Holmes_2004/nm_gui_ghigliazza_holmes_2004.ui \
    model_library/neuron/Hindmarsh_Rose_1986/nm_gui_hindmarsh_rose_1986.ui \
    model_library/neuron/Izhikevich_2003/nm_gui_izhikevich_2003.ui \
    model_library/neuron/Rulkov_2002/nm_gui_rulkov_2002.ui \
    model_library/synapse/Electrical/sm_gui_electrical.ui \
    model_library/synapse/Golowasch_et_al_1999/sm_gui_golowasch_et_al_1999.ui \
    model_library/synapse/Destexhe_et_al_1994/sm_gui_destexhe_et_al_1994.ui \
    model_library/synapse/Greenberg_Manor_2005/sm_gui_greenberg_manor_2005.ui
