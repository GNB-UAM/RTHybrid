#include "nm_gui_izhikevich_2003.h"
#include "ui_nm_gui_izhikevich_2003.h"

NM_GUI_Izhikevich_2003::NM_GUI_Izhikevich_2003(clamp_args * args, QWidget *parent) :
	QDialog(parent),
	ui(new Ui::NM_GUI_Izhikevich_2003)
{
	this->settings = new QSettings("RTHybrid", "NM_Izhikevich_2003");
	this->args = args;
	ui->setupUi(this);
	loadSettings();
}

NM_GUI_Izhikevich_2003::~NM_GUI_Izhikevich_2003(){
	 delete ui;
}

void NM_GUI_Izhikevich_2003::on_pushButton_accept_clicked() {
	args->vars = (double*) malloc (sizeof(double) * 2);
	args->params = (double *) malloc (sizeof(double) * 7);

	args->vars[NM_IZHIKEVICH_2003_V] = ui->doubleSpinBox_v->value();
	args->vars[NM_IZHIKEVICH_2003_U] = ui->doubleSpinBox_u->value();

    args->params[NM_IZHIKEVICH_2003_I] = ui->doubleSpinBox_i->value();
	args->params[NM_IZHIKEVICH_2003_A] = ui->doubleSpinBox_a->value();
	args->params[NM_IZHIKEVICH_2003_B] = ui->doubleSpinBox_b->value();
	args->params[NM_IZHIKEVICH_2003_D] = ui->doubleSpinBox_d->value();
	args->params[NM_IZHIKEVICH_2003_C] = ui->doubleSpinBox_c->value();
	args->params[NM_IZHIKEVICH_2003_DT] = ui->comboBoxIntegrationMethod->currentIndex();

	saveSettings();
	this->close();
}

void NM_GUI_Izhikevich_2003::saveSettings() {
	settings->setValue("NM_IZHIKEVICH_2003_V", ui->doubleSpinBox_v->value());
	settings->setValue("NM_IZHIKEVICH_2003_U", ui->doubleSpinBox_u->value());

    settings->setValue("NM_IZHIKEVICH_2003_I", ui->doubleSpinBox_i->value());
	settings->setValue("NM_IZHIKEVICH_2003_A", ui->doubleSpinBox_a->value());
	settings->setValue("NM_IZHIKEVICH_2003_B", ui->doubleSpinBox_b->value());
	settings->setValue("NM_IZHIKEVICH_2003_D", ui->doubleSpinBox_d->value());
	settings->setValue("NM_IZHIKEVICH_2003_C", ui->doubleSpinBox_c->value());
	settings->setValue("NM_IZHIKEVICH_2003_DT", ui->comboBoxIntegrationMethod->currentIndex());
}

void NM_GUI_Izhikevich_2003::loadSettings() {
	if (settings->value("NM_IZHIKEVICH_2003_DT", -1).toInt() == -1) return; //No settings saved yet

	ui->doubleSpinBox_v->setValue(settings->value("NM_IZHIKEVICH_2003_V").toDouble());
	ui->doubleSpinBox_u->setValue(settings->value("NM_IZHIKEVICH_2003_U").toDouble());

    ui->doubleSpinBox_i->setValue(settings->value("NM_IZHIKEVICH_2003_I").toDouble());
	ui->doubleSpinBox_a->setValue(settings->value("NM_IZHIKEVICH_2003_A").toDouble());
	ui->doubleSpinBox_b->setValue(settings->value("NM_IZHIKEVICH_2003_B").toDouble());
	ui->doubleSpinBox_d->setValue(settings->value("NM_IZHIKEVICH_2003_D").toDouble());
	ui->doubleSpinBox_c->setValue(settings->value("NM_IZHIKEVICH_2003_C").toDouble());
	ui->comboBoxIntegrationMethod->setCurrentIndex(settings->value("NM_IZHIKEVICH_2003_DT").toInt());
}
