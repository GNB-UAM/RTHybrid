#include "nm_gui_ghigliazza_holmes_2004.h"
#include "ui_nm_gui_ghigliazza_holmes_2004.h"

NM_GUI_Ghigliazza_Holmes_2004::NM_GUI_Ghigliazza_Holmes_2004(clamp_args * args, QWidget *parent) :
	QDialog(parent),
	ui(new Ui::NM_GUI_Ghigliazza_Holmes_2004)
{
	this->settings = new QSettings("RTHybrid", "NM_Ghigliazza_Holmes_2004");
	this->args = args;
	ui->setupUi(this);
	loadSettings();
}

NM_GUI_Ghigliazza_Holmes_2004::~NM_GUI_Ghigliazza_Holmes_2004(){
	 delete ui;
}

void NM_GUI_Ghigliazza_Holmes_2004::on_pushButton_accept_clicked() {
	args->vars = (double*) malloc (sizeof(double) * 3);
	args->params = (double *) malloc (sizeof(double) * 19);

    args->vars[NM_GHIGLIAZZA_HOLMES_2004_V] = ui->doubleSpinBox_v->value();

    args->params[NM_GHIGLIAZZA_HOLMES_2004_I] = ui->doubleSpinBox_i->value();
	args->params[NM_GHIGLIAZZA_HOLMES_2004_CM] = ui->doubleSpinBox_Cm->value();
	args->params[NM_GHIGLIAZZA_HOLMES_2004_EPSILON] = ui->doubleSpinBox_epsilon->value();
	args->params[NM_GHIGLIAZZA_HOLMES_2004_DELTA] = ui->doubleSpinBox_delta->value();
	args->params[NM_GHIGLIAZZA_HOLMES_2004_GCA] = ui->doubleSpinBox_gca->value();
	args->params[NM_GHIGLIAZZA_HOLMES_2004_ECA] = ui->doubleSpinBox_eca->value();
	args->params[NM_GHIGLIAZZA_HOLMES_2004_GK] = ui->doubleSpinBox_gk->value();
	args->params[NM_GHIGLIAZZA_HOLMES_2004_EK] = ui->doubleSpinBox_ek->value();
	args->params[NM_GHIGLIAZZA_HOLMES_2004_GKS] = ui->doubleSpinBox_gks->value();
	args->params[NM_GHIGLIAZZA_HOLMES_2004_GL] = ui->doubleSpinBox_gl->value();
	args->params[NM_GHIGLIAZZA_HOLMES_2004_EL] = ui->doubleSpinBox_el->value();
	args->params[NM_GHIGLIAZZA_HOLMES_2004_KK] = ui->doubleSpinBox_kk->value();
	args->params[NM_GHIGLIAZZA_HOLMES_2004_VTHK] = ui->doubleSpinBox_vthk->value();
	args->params[NM_GHIGLIAZZA_HOLMES_2004_KKS] = ui->doubleSpinBox_kks->value();
	args->params[NM_GHIGLIAZZA_HOLMES_2004_VTHKS] = ui->doubleSpinBox_vthks->value();
	args->params[NM_GHIGLIAZZA_HOLMES_2004_KCA] = ui->doubleSpinBox_kca->value();
	args->params[NM_GHIGLIAZZA_HOLMES_2004_VTHCA] = ui->doubleSpinBox_vthca->value();
	args->params[NM_GHIGLIAZZA_HOLMES_2004_DT] = ui->comboBoxIntegrationMethod->currentIndex();

	saveSettings();
	this->close();
}

void NM_GUI_Ghigliazza_Holmes_2004::saveSettings() {
    settings->setValue("NM_GHIGLIAZZA_HOLMES_2004_V", ui->doubleSpinBox_v->value());

    settings->setValue("NM_GHIGLIAZZA_HOLMES_2004_I", ui->doubleSpinBox_i->value());
	settings->setValue("NM_GHIGLIAZZA_HOLMES_2004_CM", ui->doubleSpinBox_Cm->value());
	settings->setValue("NM_GHIGLIAZZA_HOLMES_2004_EPSILON", ui->doubleSpinBox_epsilon->value());
	settings->setValue("NM_GHIGLIAZZA_HOLMES_2004_DELTA", ui->doubleSpinBox_delta->value());
	settings->setValue("NM_GHIGLIAZZA_HOLMES_2004_GCA", ui->doubleSpinBox_gca->value());
	settings->setValue("NM_GHIGLIAZZA_HOLMES_2004_ECA", ui->doubleSpinBox_eca->value());
	settings->setValue("NM_GHIGLIAZZA_HOLMES_2004_GK", ui->doubleSpinBox_gk->value());
	settings->setValue("NM_GHIGLIAZZA_HOLMES_2004_EK", ui->doubleSpinBox_ek->value());
	settings->setValue("NM_GHIGLIAZZA_HOLMES_2004_GKS", ui->doubleSpinBox_gks->value());
	settings->setValue("NM_GHIGLIAZZA_HOLMES_2004_GL", ui->doubleSpinBox_gl->value());
	settings->setValue("NM_GHIGLIAZZA_HOLMES_2004_EL", ui->doubleSpinBox_el->value());
	settings->setValue("NM_GHIGLIAZZA_HOLMES_2004_KK", ui->doubleSpinBox_kk->value());
	settings->setValue("NM_GHIGLIAZZA_HOLMES_2004_VTHK", ui->doubleSpinBox_vthk->value());
	settings->setValue("NM_GHIGLIAZZA_HOLMES_2004_KKS", ui->doubleSpinBox_kks->value());
	settings->setValue("NM_GHIGLIAZZA_HOLMES_2004_VTHKS", ui->doubleSpinBox_vthks->value());
	settings->setValue("NM_GHIGLIAZZA_HOLMES_2004_KCA", ui->doubleSpinBox_kca->value());
	settings->setValue("NM_GHIGLIAZZA_HOLMES_2004_VTHCA", ui->doubleSpinBox_vthca->value());
	settings->setValue("NM_GHIGLIAZZA_HOLMES_2004_DT", ui->comboBoxIntegrationMethod->currentIndex());
}

void NM_GUI_Ghigliazza_Holmes_2004::loadSettings() {
	if (settings->value("NM_GHIGLIAZZA_HOLMES_2004_DT", -1).toInt() == -1) return; //No settings saved yet

    ui->doubleSpinBox_v->setValue(settings->value("NM_GHIGLIAZZA_HOLMES_2004_V").toDouble());

    ui->doubleSpinBox_i->setValue(settings->value("NM_GHIGLIAZZA_HOLMES_2004_I").toDouble());
	ui->doubleSpinBox_Cm->setValue(settings->value("NM_GHIGLIAZZA_HOLMES_2004_CM").toDouble());
	ui->doubleSpinBox_epsilon->setValue(settings->value("NM_GHIGLIAZZA_HOLMES_2004_EPSILON").toDouble());
	ui->doubleSpinBox_delta->setValue(settings->value("NM_GHIGLIAZZA_HOLMES_2004_DELTA").toDouble());
	ui->doubleSpinBox_gca->setValue(settings->value("NM_GHIGLIAZZA_HOLMES_2004_GCA").toDouble());
	ui->doubleSpinBox_eca->setValue(settings->value("NM_GHIGLIAZZA_HOLMES_2004_ECA").toDouble());
	ui->doubleSpinBox_gk->setValue(settings->value("NM_GHIGLIAZZA_HOLMES_2004_GK").toDouble());
	ui->doubleSpinBox_ek->setValue(settings->value("NM_GHIGLIAZZA_HOLMES_2004_EK").toDouble());
	ui->doubleSpinBox_gks->setValue(settings->value("NM_GHIGLIAZZA_HOLMES_2004_GKS").toDouble());
	ui->doubleSpinBox_gl->setValue(settings->value("NM_GHIGLIAZZA_HOLMES_2004_GL").toDouble());
	ui->doubleSpinBox_el->setValue(settings->value("NM_GHIGLIAZZA_HOLMES_2004_EL").toDouble());
	ui->doubleSpinBox_kk->setValue(settings->value("NM_GHIGLIAZZA_HOLMES_2004_KK").toDouble());
	ui->doubleSpinBox_vthk->setValue(settings->value("NM_GHIGLIAZZA_HOLMES_2004_VTHK").toDouble());
	ui->doubleSpinBox_kks->setValue(settings->value("NM_GHIGLIAZZA_HOLMES_2004_KKS").toDouble());
	ui->doubleSpinBox_vthks->setValue(settings->value("NM_GHIGLIAZZA_HOLMES_2004_VTHKS").toDouble());
	ui->doubleSpinBox_kca->setValue(settings->value("NM_GHIGLIAZZA_HOLMES_2004_KCA").toDouble());
	ui->doubleSpinBox_vthca->setValue(settings->value("NM_GHIGLIAZZA_HOLMES_2004_VTHCA").toDouble());
	ui->comboBoxIntegrationMethod->setCurrentIndex(settings->value("NM_GHIGLIAZZA_HOLMES_2004_DT").toInt());
}
