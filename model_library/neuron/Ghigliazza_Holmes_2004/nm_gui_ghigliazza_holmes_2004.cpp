#include "nm_gui_ghigliazza_holmes_2004.h"
#include "ui_nm_gui_ghigliazza_holmes_2004.h"

NM_GUI_Ghigliazza_Holmes_2004::NM_GUI_Ghigliazza_Holmes_2004(clamp_args * args, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::NM_GUI_Ghigliazza_Holmes_2004)
{
    this->settings = new QSettings("RTHybrid", "NM_Ghigliazza_Holmes_2004");
    //printf("GH %s\n", settings->fileName().toStdString().c_str());

    this->args = args;
    ui->setupUi(this);

    loadSettings();
}

NM_GUI_Ghigliazza_Holmes_2004::~NM_GUI_Ghigliazza_Holmes_2004()
{
    delete ui;
}

void NM_GUI_Ghigliazza_Holmes_2004::on_pushButton_accept_clicked()
{
    args->vars = (double*) malloc (sizeof(double) * 3);
    args->params = (double *) malloc (sizeof(double) * 18);

    args->vars[GH_V] = ui->doubleGhX0->value();

    args->params[GH_I] = ui->doubleGhIext->value();
    args->params[GH_G_CA] = ui->doubleGhGca->value();
    args->params[GH_G_K] = ui->doubleGhGk->value();
    args->params[GH_G_L] = ui->doubleGhGl->value();
    args->params[GH_G_KS] = ui->doubleGhGks->value();
    args->params[GH_CM] = ui->doubleGhC->value();
    args->params[GH_E_CA] = ui->doubleGhEca->value();
    args->params[GH_E_K] = ui->doubleGhEk->value();
    args->params[GH_E_L] = ui->doubleGhEl->value();
    args->params[GH_EPSILON] = ui->doubleGhEpsilon->value();
    args->params[GH_DELTA] = ui->doubleGhDelta->value();
    args->params[GH_K_CA] = ui->doubleGhKca->value();
    args->params[GH_K_K] = ui->doubleGhKk->value();
    args->params[GH_K_KS] = ui->doubleGhKks->value();
    args->params[GH_VTH_CA] = ui->doubleGhVthca->value();
    args->params[GH_VTH_K] = ui->doubleGhVthk->value();
    args->params[GH_VTH_KS] = ui->doubleGhVthks->value();

    args->params[GH_DT] = ui->comboBoxIntegration->currentIndex();

    saveSettings();

    this->close();
}

void NM_GUI_Ghigliazza_Holmes_2004::saveSettings() {
    settings->setValue("GH_V", ui->doubleGhX0->value());

    settings->setValue("GH_I", ui->doubleGhIext->value());
    settings->setValue("GH_G_CA", ui->doubleGhGca->value());
    settings->setValue("GH_G_K", ui->doubleGhGk->value());
    settings->setValue("GH_G_L", ui->doubleGhGl->value());
    settings->setValue("GH_G_KS", ui->doubleGhGks->value());
    settings->setValue("GH_CM", ui->doubleGhC->value());
    settings->setValue("GH_E_CA", ui->doubleGhEca->value());
    settings->setValue("GH_E_K", ui->doubleGhEk->value());
    settings->setValue("GH_E_L", ui->doubleGhEl->value());
    settings->setValue("GH_EPSILON", ui->doubleGhEpsilon->value());
    settings->setValue("GH_DELTA", ui->doubleGhDelta->value());
    settings->setValue("GH_K_CA", ui->doubleGhKca->value());
    settings->setValue("GH_K_K", ui->doubleGhKk->value());
    settings->setValue("GH_K_KS", ui->doubleGhKks->value());
    settings->setValue("GH_VTH_CA", ui->doubleGhVthca->value());
    settings->setValue("GH_VTH_K", ui->doubleGhVthk->value());
    settings->setValue("GH_VTH_KS", ui->doubleGhVthks->value());

    settings->setValue("GH_DT", ui->comboBoxIntegration->currentIndex());
}

void NM_GUI_Ghigliazza_Holmes_2004::loadSettings() {
    if (settings->value("GH_DT", -1).toInt() == -1) return; //No settings saved yet

    ui->doubleGhX0->setValue(settings->value("GH_V").toDouble());

    ui->doubleGhIext->setValue(settings->value("GH_I").toDouble());
    ui->doubleGhGca->setValue(settings->value("GH_G_CA").toDouble());
    ui->doubleGhGk->setValue(settings->value("GH_G_K").toDouble());
    ui->doubleGhGl->setValue(settings->value("GH_G_L").toDouble());
    ui->doubleGhGks->setValue(settings->value("GH_G_KS").toDouble());
    ui->doubleGhC->setValue(settings->value("GH_CM").toDouble());
    ui->doubleGhEca->setValue(settings->value("GH_E_CA").toDouble());
    ui->doubleGhEk->setValue(settings->value("GH_E_K").toDouble());
    ui->doubleGhEl->setValue(settings->value("GH_E_L").toDouble());
    ui->doubleGhEpsilon->setValue(settings->value("GH_EPSILON").toDouble());
    ui->doubleGhDelta->setValue(settings->value("GH_DELTA").toDouble());
    ui->doubleGhKca->setValue(settings->value("GH_K_CA").toDouble());
    ui->doubleGhKk->setValue(settings->value("GH_K_K").toDouble());
    ui->doubleGhKks->setValue(settings->value("GH_K_KS").toDouble());
    ui->doubleGhVthca->setValue(settings->value("GH_VTH_CA").toDouble());
    ui->doubleGhVthk->setValue(settings->value("GH_VTH_K").toDouble());
    ui->doubleGhVthks->setValue(settings->value("GH_VTH_KS").toDouble());

    ui->comboBoxIntegration->setCurrentIndex(settings->value("GH_DT").toInt());
}

