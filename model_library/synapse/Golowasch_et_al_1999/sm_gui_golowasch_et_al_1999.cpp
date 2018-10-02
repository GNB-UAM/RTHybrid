#include "sm_gui_golowasch_et_al_1999.h"
#include "ui_sm_gui_golowasch_et_al_1999.h"

SM_GUI_Golowasch_et_al_1999::SM_GUI_Golowasch_et_al_1999(void ** args, unsigned int direction, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SM_GUI_Golowasch_et_al_1999)
{
    switch (direction) {
        case 0:
            this->settings = new QSettings("RTHybrid", "SM_Golowasch_et_al_1999_LtoM");
            break;
        case 1:
            this->settings = new QSettings("RTHybrid", "SM_Golowasch_et_al_1999_MtoL");
            break;
        default:
            return;
    }

    this->args = args;
    ui->setupUi(this);

    loadSettings();
}

SM_GUI_Golowasch_et_al_1999::~SM_GUI_Golowasch_et_al_1999()
{
    delete ui;
}

void SM_GUI_Golowasch_et_al_1999::on_pushButton_accept_clicked()
{
    (*args) = (syn_gl_args *) malloc (sizeof(syn_gl_args));
    syn_gl_args * aux_args = (syn_gl_args *) (*args);

    aux_args->g[GL_G_FAST] = ui->double_gFast->value();
    aux_args->v_fast = ui->double_vthFast->value();
    aux_args->s_fast = ui->double_sFast->value();

    aux_args->g[GL_G_SLOW] = ui->double_gSlow->value();
    aux_args->v_slow = ui->double_vthSlow->value();
    aux_args->s_slow = ui->double_sSlow->value();
    aux_args->k1 = ui->double_k1->value();
    aux_args->k2 = ui->double_k2->value();

    saveSettings();

    this->close();
}

void SM_GUI_Golowasch_et_al_1999::saveSettings() {
    settings->setValue("gFast", ui->double_gFast->value());
    settings->setValue("vthFast", ui->double_vthFast->value());
    settings->setValue("sFast", ui->double_sFast->value());

    settings->setValue("gSlow", ui->double_gSlow->value());
    settings->setValue("vthSlow", ui->double_vthSlow->value());
    settings->setValue("sSlow", ui->double_sSlow->value());
    settings->setValue("k1", ui->double_k1->value());
    settings->setValue("k2", ui->double_k2->value());
}

void SM_GUI_Golowasch_et_al_1999::loadSettings() {
    if (settings->value("vthSlow", -1).toDouble() == -2) return; //No settings saved yet

    ui->double_gFast->setValue(settings->value("gFast").toDouble());
    ui->double_vthFast->setValue(settings->value("vthFast").toDouble());
    ui->double_sFast->setValue(settings->value("sFast").toDouble());

    ui->double_gSlow->setValue(settings->value("gSlow").toDouble());
    ui->double_vthSlow->setValue(settings->value("vthSlow").toDouble());
    ui->double_sSlow->setValue(settings->value("sSlow").toDouble());
    ui->double_k1->setValue(settings->value("k1").toDouble());
    ui->double_k2->setValue(settings->value("k2").toDouble());
}
