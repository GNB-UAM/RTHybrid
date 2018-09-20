#include "nm_gui_hindmarsh_rose_1986.h"
#include "ui_nm_gui_hindmarsh_rose_1986.h"

NM_GUI_Hindmarsh_Rose_1986::NM_GUI_Hindmarsh_Rose_1986(clamp_args * args, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::NM_GUI_Hindmarsh_Rose_1986)
{
    this->settings = new QSettings("RTHybrid", "Hindmarsh_Rose_1986");
    //printf("HR %s\n", settings->fileName().toStdString().c_str());

    this->args = args;
    ui->setupUi(this);

    loadSettings();
}

NM_GUI_Hindmarsh_Rose_1986::~NM_GUI_Hindmarsh_Rose_1986()
{
    delete ui;
}

void NM_GUI_Hindmarsh_Rose_1986::on_pushButton_accept_clicked()
{
    args->vars = (double*) malloc (sizeof(double) * 3);
    args->params = (double *) malloc (sizeof(double) * 4);

    args->vars[HR_X] = ui->doubleX->value();
    args->vars[HR_Y] = ui->doubleY->value();
    args->vars[HR_Z] = ui->doubleZ->value();

    args->params[HR_R] = ui->doubleR->value();
    args->params[HR_S] = ui->doubleS->value();
    args->params[HR_I] = ui->doubleI->value();
    args->params[HR_DT] = ui->comboBoxIntegration->currentIndex();

    saveSettings();

    this->close();
}

void NM_GUI_Hindmarsh_Rose_1986::saveSettings() {
    settings->setValue("X", ui->doubleX->value());
    settings->setValue("Y", ui->doubleY->value());
    settings->setValue("Z", ui->doubleZ->value());

    settings->setValue("R", ui->doubleR->value());
    settings->setValue("S", ui->doubleS->value());
    settings->setValue("I", ui->doubleI->value());
    settings->setValue("DT", ui->comboBoxIntegration->currentIndex());
}

void NM_GUI_Hindmarsh_Rose_1986::loadSettings() {
    if (settings->value("DT", -1).toInt() == -1) return; //No settings saved yet

    ui->doubleX->setValue(settings->value("X").toDouble());
    ui->doubleY->setValue(settings->value("Y").toDouble());
    ui->doubleZ->setValue(settings->value("Z").toDouble());

    ui->doubleR->setValue(settings->value("R").toDouble());
    ui->doubleS->setValue(settings->value("S").toDouble());
    ui->doubleI->setValue(settings->value("I").toDouble());
    ui->comboBoxIntegration->setCurrentIndex(settings->value("DT").toInt());
}
