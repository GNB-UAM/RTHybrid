#include "sm_gui_electrical.h"
#include "ui_sm_gui_electrical.h"

SM_GUI_Electrical::SM_GUI_Electrical(void * args, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::SM_GUI_Electrical)
{
    this->settings = new QSettings("RTHybrid", "SM_Electrical");

    this->args = args;
    ui->setupUi(this);

    loadSettings();
}

SM_GUI_Electrical::~SM_GUI_Electrical()
{
    delete ui;
}

void SM_GUI_Electrical::on_pushButton_accept_clicked()
{
    args = (syn_elec_args *) malloc (sizeof(syn_elec_args));
    syn_elec_args * aux_args = (syn_elec_args *) args;

    aux_args->g[ELEC_G] = ui->double_g->value();
    aux_args->anti = (ui->checkAnti->isChecked()) ? -1 : 1;

    saveSettings();

    this->close();
}

void SM_GUI_Electrical::saveSettings() {
    settings->setValue("g", ui->double_g->value());
    settings->setValue("anti", ui->checkAnti->isChecked());
}

void SM_GUI_Electrical::loadSettings() {
    if (settings->value("anti", -2).toInt() == -2) return; //No settings saved yet

    ui->double_g->setValue((settings->value("g").toDouble());
    ui->checkAnti->setChecked(settings->value("anti").toBool());
}
