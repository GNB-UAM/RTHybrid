#ifndef RTHYBRID_H
#define RTHYBRID_H

#include "ui_rthybrid.h"
#include "clamplauncher.h"

namespace Ui {
class RTHybrid;
}

class RTHybrid : public QMainWindow
{
    Q_OBJECT

public:
    explicit RTHybrid(QWidget *parent = 0);
    ~RTHybrid();
    void closeEvent (QCloseEvent *event);

private slots:
    void on_buttonStart_clicked();

    void on_buttonStop_clicked();

    /*void on_neuronModelCombo_activated(int index);

    void on_synapseModelCombo_activated(int index);

    void on_autocalCombo_activated(int index);*/

    void on_autoDetect_clicked();

    void clampEnd();


    /*void on_doubleSpinBox_gl_EtoM_fast_g_valueChanged(double arg1);

    void on_doubleSpinBox_gl_EtoM_slow_g_valueChanged(double arg1);

    void on_doubleSpinBox_gl_MtoE_fast_g_valueChanged(double arg1);

    void on_doubleSpinBox_gl_MtoE_slow_g_valueChanged(double arg1);

    void on_doubleSynElec_gMtoE_valueChanged(double arg1);

    void on_doubleSynElec_gEtoM_valueChanged(double arg1);

    void on_buttonIzConfig_clicked();*/

    void on_textChannelInput_textChanged();

    std::string neuron_models_switch(int index);

    void on_pushButton_neuron_config_clicked();

    void on_combo_neuron_activated(int index);

    void synapse_models_switch(int index, void ** syn_args, unsigned int direction);

    void synapse_models_graphics_ltom(int model_ltom, void * syn_args_ltom, int model_mtol, void * syn_args_mtol);

    void synapse_models_graphics_mtol(int model_mtol, void * syn_args_mtol, int model_ltom, void * syn_args_ltom);

    void on_combo_synLtoM_activated(int index);

    void on_combo_synMtoL_activated(int index);

    void on_pushButton_synLtoM_config_clicked();

    void on_pushButton_synMtoL_config_clicked();

private:
    Ui::RTHybrid *ui;
    QMovie *movie;
    ClampLauncher * cl;
    unsigned short isClampRunning = false;
    clamp_args args;
};

#endif // RTHYBRID_H
