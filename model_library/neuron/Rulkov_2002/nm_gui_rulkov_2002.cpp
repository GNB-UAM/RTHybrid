#include "nm_gui_rulkov_2002.h"
#include "ui_nm_gui_rulkov_2002.h"

NM_GUI_Rulkov_2002::NM_GUI_Rulkov_2002(clamp_args * args, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::NM_GUI_Rulkov_2002)
{
    this->settings = new QSettings("RTHybrid", "Rulkov_2002");
    //printf("Rulkov %s\n", settings->fileName().toStdString().c_str());

    this->args = args;
    ui->setupUi(this);

    loadSettings();
}

NM_GUI_Rulkov_2002::~NM_GUI_Rulkov_2002()
{
    delete ui;
}

void NM_GUI_Rulkov_2002::on_pushButton_accept_clicked()
{
    args->vars = (double*) malloc (sizeof(double) * 2);
    args->params = (double *) malloc (sizeof(double) * 8);

    args->vars[RLK_X] = ui->doubleRlkXIni->value();
    args->vars[RLK_Y] = ui->doubleRlkYIni->value();

    args->params[RLK_ALPHA] = ui->doubleRlkAlpha->value();
    args->params[RLK_SIGMA] = ui->doubleRlkSigma->value();
    args->params[RLK_MU] = ui->doubleRlkMu->value();
    args->params[RLK_I] = ui->doubleRlkI->value();
    args->params[RLK_OLD] = 0.0;
    args->params[RLK_INTER] = 0.0;

    saveSettings();

    this->close();
}

void NM_GUI_Rulkov_2002::saveSettings() {
    settings->setValue("X", ui->doubleRlkXIni->value());
    settings->setValue("Y", ui->doubleRlkYIni->value());

    settings->setValue("ALPHA", ui->doubleRlkAlpha->value());
    settings->setValue("SIGMA", ui->doubleRlkSigma->value());
    settings->setValue("MU", ui->doubleRlkMu->value());
    settings->setValue("I", ui->doubleRlkI->value());
}

void NM_GUI_Rulkov_2002::loadSettings() {
    if (settings->value("X", -9999).toInt() == -1) return; //No settings saved yet

    ui->doubleRlkXIni->setValue(settings->value("X").toDouble());
    ui->doubleRlkYIni->setValue(settings->value("Y").toDouble());

    ui->doubleRlkAlpha->setValue(settings->value("ALPHA").toDouble());
    ui->doubleRlkSigma->setValue(settings->value("SIGMA").toDouble());
    ui->doubleRlkMu->setValue(settings->value("MU").toDouble());
    ui->doubleRlkI->setValue(settings->value("I").toDouble());
}
