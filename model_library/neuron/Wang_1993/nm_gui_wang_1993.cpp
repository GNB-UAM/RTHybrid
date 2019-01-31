#include "nm_gui_wang_1993.h"
#include "ui_nm_gui_wang_1993.h"

NM_GUI_Wang_1993::NM_GUI_Wang_1993(clamp_args * args, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::NM_GUI_Wang_1993)
{
    this->settings = new QSettings("RTHybrid", "NM_Wang_1993");
    //printf("Wang %s\n", settings->fileName().toStdString().c_str());

    this->args = args;
    ui->setupUi(this);

    loadSettings();
}

NM_GUI_Wang_1993::~NM_GUI_Wang_1993()
{
    delete ui;
}

void NM_GUI_Wang_1993::on_pushButton_accept_clicked()
{
    args->vars = (double*) malloc (sizeof(double) * 6);
    args->params = (double *) malloc (sizeof(double) * 15);

    args->vars[WANG_V] = ui->doubleSpinBox_V->value();

    args->params[WANG_I] = ui->doubleSpinBox_i->value();
    args->params[WANG_G_NA] = ui->doubleSpinBox_g_Na->value();
    args->params[WANG_G_NAP] = ui->doubleSpinBox_g_NaP->value();
    args->params[WANG_G_K] = ui->doubleSpinBox_g_K->value();
    args->params[WANG_G_KS] = ui->doubleSpinBox_g_KS->value();
    args->params[WANG_G_L] = ui->doubleSpinBox_g_L->value();
    args->params[WANG_CM] = ui->doubleSpinBox_cm->value();
    args->params[WANG_V_NA] = ui->doubleSpinBox_V_Na->value();
    args->params[WANG_V_K] = ui->doubleSpinBox_V_K->value();
    args->params[WANG_V_L] = ui->doubleSpinBox_V_L->value();
    args->params[WANG_SIGMA] = ui->doubleSpinBox_sigma->value();
    args->params[WANG_PHI] = ui->doubleSpinBox_phi->value();
    args->params[WANG_RHO] = ui->doubleSpinBox_rho->value();
    args->params[WANG_TAUM] = ui->doubleSpinBox_taum->value();

    args->params[WANG_DT] = ui->comboBoxIntegration->currentIndex();

    saveSettings();

    this->close();
}

void NM_GUI_Wang_1993::saveSettings() {
    settings->setValue("WANG_V", ui->doubleSpinBox_V->value());

    settings->setValue("WANG_I", ui->doubleSpinBox_i->value());
    settings->setValue("WANG_G_NA", ui->doubleSpinBox_g_Na->value());
    settings->setValue("WANG_G_NAP", ui->doubleSpinBox_g_NaP->value());
    settings->setValue("WANG_G_K", ui->doubleSpinBox_g_K->value());
    settings->setValue("WANG_G_KS", ui->doubleSpinBox_g_KS->value());
    settings->setValue("WANG_G_L", ui->doubleSpinBox_g_L->value());
    settings->setValue("WANG_CM", ui->doubleSpinBox_cm->value());
    settings->setValue("WANG_V_NA", ui->doubleSpinBox_V_Na->value());
    settings->setValue("WANG_V_K", ui->doubleSpinBox_V_K->value());
    settings->setValue("WANG_V_L", ui->doubleSpinBox_V_L->value());
    settings->setValue("WANG_SIGMA", ui->doubleSpinBox_sigma->value());
    settings->setValue("WANG_PHI", ui->doubleSpinBox_phi->value());
    settings->setValue("WANG_RHO", ui->doubleSpinBox_rho->value());
    settings->setValue("WANG_TAUM", ui->doubleSpinBox_taum->value());

    settings->setValue("WANG_DT", ui->comboBoxIntegration->currentIndex());
}

void NM_GUI_Wang_1993::loadSettings() {
    if (settings->value("WANG_DT", -1).toInt() == -1) return; //No settings saved yet

    ui->doubleSpinBox_V->setValue(settings->value("WANG_V").toDouble());

    ui->doubleSpinBox_i->setValue(settings->value("WANG_I").toDouble());
    ui->doubleSpinBox_g_Na->setValue(settings->value("WANG_G_NA").toDouble());
    ui->doubleSpinBox_g_NaP->setValue(settings->value("WANG_G_NAP").toDouble());
    ui->doubleSpinBox_g_K->setValue(settings->value("WANG_G_K").toDouble());
    ui->doubleSpinBox_g_KS->setValue(settings->value("WANG_G_KS").toDouble());
    ui->doubleSpinBox_g_L->setValue(settings->value("WANG_G_L").toDouble());
    ui->doubleSpinBox_cm->setValue(settings->value("WANG_CM").toDouble());
    ui->doubleSpinBox_V_Na->setValue(settings->value("WANG_V_NA").toDouble());
    ui->doubleSpinBox_V_K->setValue(settings->value("WANG_V_K").toDouble());
    ui->doubleSpinBox_V_L->setValue(settings->value("WANG_V_L").toDouble());
    ui->doubleSpinBox_sigma->setValue(settings->value("WANG_SIGMA").toDouble());
    ui->doubleSpinBox_phi->setValue(settings->value("WANG_PHI").toDouble());
    ui->doubleSpinBox_rho->setValue(settings->value("WANG_RHO").toDouble());
    ui->doubleSpinBox_taum->setValue(settings->value("WANG_TAUM").toDouble());

    ui->comboBoxIntegration->setCurrentIndex(settings->value("WANG_DT").toInt());
}
