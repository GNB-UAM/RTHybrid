#include "nm_gui_hindmarsh_rose_1986.h"
#include "ui_nm_gui_hindmarsh_rose_1986.h"

NM_GUI_Hindmarsh_Rose_1986::NM_GUI_Hindmarsh_Rose_1986(clamp_args * args, QWidget *parent) :
	QDialog(parent),
	ui(new Ui::NM_GUI_Hindmarsh_Rose_1986)
{
	this->settings = new QSettings("RTHybrid", "NM_Hindmarsh_Rose_1986");
	this->args = args;
	ui->setupUi(this);
	loadSettings();
}

NM_GUI_Hindmarsh_Rose_1986::~NM_GUI_Hindmarsh_Rose_1986(){
	 delete ui;
}

void NM_GUI_Hindmarsh_Rose_1986::on_pushButton_accept_clicked() {
	args->vars = (double*) malloc (sizeof(double) * 3);
	args->params = (double *) malloc (sizeof(double) * 10);

	args->vars[NM_HINDMARSH_ROSE_1986_V] = ui->doubleSpinBox_v->value();
	args->vars[NM_HINDMARSH_ROSE_1986_Y] = ui->doubleSpinBox_y->value();
	args->vars[NM_HINDMARSH_ROSE_1986_Z] = ui->doubleSpinBox_z->value();

	args->params[NM_HINDMARSH_ROSE_1986_B] = ui->doubleSpinBox_b->value();
	args->params[NM_HINDMARSH_ROSE_1986_A] = ui->doubleSpinBox_a->value();
	args->params[NM_HINDMARSH_ROSE_1986_I] = ui->doubleSpinBox_i->value();
	args->params[NM_HINDMARSH_ROSE_1986_C] = ui->doubleSpinBox_c->value();
	args->params[NM_HINDMARSH_ROSE_1986_D] = ui->doubleSpinBox_d->value();
	args->params[NM_HINDMARSH_ROSE_1986_R] = ui->doubleSpinBox_r->value();
	args->params[NM_HINDMARSH_ROSE_1986_S] = ui->doubleSpinBox_s->value();
	args->params[NM_HINDMARSH_ROSE_1986_XR] = ui->doubleSpinBox_xr->value();
	args->params[NM_HINDMARSH_ROSE_1986_DT] = ui->comboBoxIntegrationMethod->currentIndex();

	saveSettings();
	this->close();
}

void NM_GUI_Hindmarsh_Rose_1986::saveSettings() {
	settings->setValue("NM_HINDMARSH_ROSE_1986_V", ui->doubleSpinBox_v->value());
	settings->setValue("NM_HINDMARSH_ROSE_1986_Y", ui->doubleSpinBox_y->value());
	settings->setValue("NM_HINDMARSH_ROSE_1986_Z", ui->doubleSpinBox_z->value());

	settings->setValue("NM_HINDMARSH_ROSE_1986_B", ui->doubleSpinBox_b->value());
	settings->setValue("NM_HINDMARSH_ROSE_1986_A", ui->doubleSpinBox_a->value());
	settings->setValue("NM_HINDMARSH_ROSE_1986_I", ui->doubleSpinBox_i->value());
	settings->setValue("NM_HINDMARSH_ROSE_1986_C", ui->doubleSpinBox_c->value());
	settings->setValue("NM_HINDMARSH_ROSE_1986_D", ui->doubleSpinBox_d->value());
	settings->setValue("NM_HINDMARSH_ROSE_1986_R", ui->doubleSpinBox_r->value());
	settings->setValue("NM_HINDMARSH_ROSE_1986_S", ui->doubleSpinBox_s->value());
	settings->setValue("NM_HINDMARSH_ROSE_1986_XR", ui->doubleSpinBox_xr->value());
	settings->setValue("NM_HINDMARSH_ROSE_1986_DT", ui->comboBoxIntegrationMethod->currentIndex());
}

void NM_GUI_Hindmarsh_Rose_1986::loadSettings() {
	if (settings->value("NM_HINDMARSH_ROSE_1986_DT", -1).toInt() == -1) return; //No settings saved yet

	ui->doubleSpinBox_v->setValue(settings->value("NM_HINDMARSH_ROSE_1986_V").toDouble());
	ui->doubleSpinBox_y->setValue(settings->value("NM_HINDMARSH_ROSE_1986_Y").toDouble());
	ui->doubleSpinBox_z->setValue(settings->value("NM_HINDMARSH_ROSE_1986_Z").toDouble());

	ui->doubleSpinBox_b->setValue(settings->value("NM_HINDMARSH_ROSE_1986_B").toDouble());
	ui->doubleSpinBox_a->setValue(settings->value("NM_HINDMARSH_ROSE_1986_A").toDouble());
    ui->doubleSpinBox_i->setValue(settings->value("NM_HINDMARSH_ROSE_1986_I").toDouble());
	ui->doubleSpinBox_c->setValue(settings->value("NM_HINDMARSH_ROSE_1986_C").toDouble());
	ui->doubleSpinBox_d->setValue(settings->value("NM_HINDMARSH_ROSE_1986_D").toDouble());
	ui->doubleSpinBox_r->setValue(settings->value("NM_HINDMARSH_ROSE_1986_R").toDouble());
	ui->doubleSpinBox_s->setValue(settings->value("NM_HINDMARSH_ROSE_1986_S").toDouble());
	ui->doubleSpinBox_xr->setValue(settings->value("NM_HINDMARSH_ROSE_1986_XR").toDouble());
	ui->comboBoxIntegrationMethod->setCurrentIndex(settings->value("NM_HINDMARSH_ROSE_1986_DT").toInt());
}
