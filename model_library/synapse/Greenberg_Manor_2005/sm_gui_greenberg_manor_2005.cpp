#include "sm_gui_greenberg_manor_2005.h"
#include "ui_sm_gui_greenberg_manor_2005.h"

SM_GUI_Greenberg_Manor_2005::SM_GUI_Greenberg_Manor_2005(void ** args, unsigned int direction, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SM_GUI_Greenberg_Manor_2005)
{
	switch (direction) {
        case 0:
            this->settings = new QSettings("RTHybrid", "SM_Greenberg_Manor_2005_LtoM");
            break;
        case 1:
            this->settings = new QSettings("RTHybrid", "SM_Greenberg_Manor_2005_MtoL");
            break;
        default:
            return;
    }

    this->args = args;
    ui->setupUi(this);

    loadSettings();
}

SM_GUI_Greenberg_Manor_2005::~SM_GUI_Greenberg_Manor_2005()
{
    delete ui;
}


void SM_GUI_Greenberg_Manor_2005::on_pushButton_accept_clicked()
{
    (*args) = (sm_greenberg_manor_2005_args *) malloc (sizeof(sm_greenberg_manor_2005_args));
    sm_greenberg_manor_2005_args * aux_args = (sm_greenberg_manor_2005_args *) (*args);

    aux_args->dt = ui->doubleSpinBox_dt->value();
    aux_args->method = ui->comboBoxIntegration->currentIndex();
    aux_args->g[SM_GREENBERG_MANOR_2005_G] = ui->doubleSpinBox_g->value();
    aux_args->e_syn_per = ui->doubleSpinBox_esyn->value();

    aux_args->p = ui->doubleSpinBox_p->value();
    aux_args->k_m = ui->doubleSpinBox_k_m->value();
    aux_args->v12_m = ui->doubleSpinBox_v12_m->value();
    aux_args->tau_hi_m = ui->doubleSpinBox_tau_hi_m->value();
    aux_args->tau_lo_m = ui->doubleSpinBox_tau_lo_m->value();

    aux_args->q = ui->doubleSpinBox_q->value();
    aux_args->k_h = ui->doubleSpinBox_k_h->value();
    aux_args->v12_h = ui->doubleSpinBox_v12_h->value();
    aux_args->tau_hi_h = ui->doubleSpinBox_tau_hi_h->value();
    aux_args->tau_lo_h = ui->doubleSpinBox_tau_lo_h->value();

    saveSettings();

    this->close();
}

void SM_GUI_Greenberg_Manor_2005::saveSettings() {
    settings->setValue("dt", ui->doubleSpinBox_dt->value());
    settings->setValue("method", ui->comboBoxIntegration->currentIndex());
    settings->setValue("g", ui->doubleSpinBox_g->value());
    settings->setValue("e_syn_per", ui->doubleSpinBox_esyn->value());

    settings->setValue("p", ui->doubleSpinBox_p->value());
    settings->setValue("k_m", ui->doubleSpinBox_k_m->value());
    settings->setValue("v12_m", ui->doubleSpinBox_v12_m->value());
    settings->setValue("tau_hi_m", ui->doubleSpinBox_tau_hi_m->value());
    settings->setValue("tau_lo_m", ui->doubleSpinBox_tau_lo_m->value());

    settings->setValue("q", ui->doubleSpinBox_q->value());
    settings->setValue("k_h", ui->doubleSpinBox_k_h->value());
    settings->setValue("v12_h", ui->doubleSpinBox_v12_h->value());
    settings->setValue("tau_hi_h", ui->doubleSpinBox_tau_hi_h->value());
    settings->setValue("tau_lo_h", ui->doubleSpinBox_tau_lo_h->value());
}

void SM_GUI_Greenberg_Manor_2005::loadSettings() {
    if (settings->value("dt", -1).toDouble() == -1) return; // No settings saved yet

    ui->doubleSpinBox_dt->setValue(settings->value("dt").toDouble());
    ui->comboBoxIntegration->setCurrentIndex(settings->value("method").toInt());
    ui->doubleSpinBox_g->setValue(settings->value("g").toDouble());
    ui->doubleSpinBox_esyn->setValue(settings->value("e_syn_per").toDouble());

    ui->doubleSpinBox_p->setValue(settings->value("p").toDouble());
    ui->doubleSpinBox_k_m->setValue(settings->value("k_m").toDouble());
    ui->doubleSpinBox_v12_m->setValue(settings->value("v12_m").toDouble());
    ui->doubleSpinBox_tau_hi_m->setValue(settings->value("tau_hi_m").toDouble());
    ui->doubleSpinBox_tau_lo_m->setValue(settings->value("tau_lo_m").toDouble());

    ui->doubleSpinBox_q->setValue(settings->value("q").toDouble());
    ui->doubleSpinBox_k_h->setValue(settings->value("k_h").toDouble());
    ui->doubleSpinBox_v12_h->setValue(settings->value("v12_h").toDouble());
    ui->doubleSpinBox_tau_hi_h->setValue(settings->value("tau_hi_h").toDouble());
    ui->doubleSpinBox_tau_lo_h->setValue(settings->value("tau_lo_h").toDouble());
}
