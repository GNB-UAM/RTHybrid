#include "sm_gui_destexhe_et_al_1994.h"
#include "ui_sm_gui_destexhe_et_al_1994.h"

SM_GUI_Destexhe_et_al_1994::SM_GUI_Destexhe_et_al_1994(void ** args, unsigned int direction, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SM_GUI_Destexhe_et_al_1994)
{
	switch (direction) {
        case 0:
            this->settings = new QSettings("RTHybrid", "SM_Destexhe_et_al_1994_LtoM");
            break;
        case 1:
            this->settings = new QSettings("RTHybrid", "SM_Destexhe_et_al_1994_MtoL");
            break;
        default:
            return;
    }

    this->args = args;
    ui->setupUi(this);

    loadSettings();
}

SM_GUI_Destexhe_et_al_1994::~SM_GUI_Destexhe_et_al_1994()
{
    delete ui;
}


void SM_GUI_Destexhe_et_al_1994::on_pushButton_accept_clicked()
{
    (*args) = (sm_destexhe_et_al_1994_args *) malloc (sizeof(sm_destexhe_et_al_1994_args));
    sm_destexhe_et_al_1994_args * aux_args = (sm_destexhe_et_al_1994_args *) (*args);
    double v_min = -65.0;

    aux_args->alpha = (ui->doubleSpinBox_alpha->value() / 1000.0) * ui->doubleSpinBox_freq->value();
    aux_args->beta = (ui->doubleSpinBox_beta->value()  / 1000.0) * ui->doubleSpinBox_freq->value();
    aux_args->g[SM_DESTEXHE_ET_AL_1994_G] = ui->doubleSpinBox_g->value();
    aux_args->tmax = ui->doubleSpinBox_tmax->value();
    aux_args->pulse_duration = ui->doubleSpinBox_pulse_duration->value() * ui->doubleSpinBox_freq->value();
    //aux_args->e_syn_per = (ui->doubleSpinBox_esyn->value() - v_min) / 100.0;
    aux_args->e_syn_per = ui->doubleSpinBox_esyn->value() / 100.0;

    saveSettings();

    this->close();
}

void SM_GUI_Destexhe_et_al_1994::saveSettings() {
    settings->setValue("alpha", ui->doubleSpinBox_alpha->value());
    settings->setValue("beta", ui->doubleSpinBox_beta->value());
    settings->setValue("e_syn", ui->doubleSpinBox_esyn->value());
    settings->setValue("g", ui->doubleSpinBox_g->value());
    settings->setValue("tmax", ui->doubleSpinBox_tmax->value());
    settings->setValue("pulse_duration", ui->doubleSpinBox_pulse_duration->value());
    settings->setValue("freq", ui->doubleSpinBox_freq->value());
}

void SM_GUI_Destexhe_et_al_1994::loadSettings() {
    if (settings->value("freq", -1).toDouble() < 0) return; // No settings saved yet

    ui->doubleSpinBox_alpha->setValue(settings->value("alpha").toDouble());
    ui->doubleSpinBox_beta->setValue(settings->value("beta").toDouble());
    ui->doubleSpinBox_esyn->setValue(settings->value("e_syn").toDouble());
    ui->doubleSpinBox_g->setValue(settings->value("g").toDouble());
    ui->doubleSpinBox_tmax->setValue(settings->value("tmax").toDouble());
    ui->doubleSpinBox_pulse_duration->setValue(settings->value("pulse_duration").toDouble());
    ui->doubleSpinBox_freq->setValue(settings->value("freq").toDouble());
}
