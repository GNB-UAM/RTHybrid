#include "nm_gui_bluetooth.h"
#include "ui_nm_gui_bluetooth.h"

NM_GUI_Bluetooth::NM_GUI_Bluetooth(clamp_args * args, QWidget *parent) :
	QDialog(parent),
	ui(new Ui::NM_GUI_Bluetooth)
{
	this->settings = new QSettings("RTHybrid", "NM_Bluetooth");
	this->args = args;
	ui->setupUi(this);
	loadSettings();
}

NM_GUI_Bluetooth::~NM_GUI_Bluetooth(){
	 delete ui;
}

void NM_GUI_Bluetooth::on_pushButton_accept_clicked() {
	args->vars = (double*) malloc (sizeof(double) * 2);
	args->params = (double *) malloc (sizeof(double) * 1);

    /*args->vars[NM_BLUETOOTH_N1] = ui->doubleSpinBox_n1->value();
	args->vars[NM_BLUETOOTH_N2] = ui->doubleSpinBox_n2->value();

    args->params[NM_BLUETOOTH_DT] = ui->comboBoxIntegrationMethod->currentIndex();*/

	saveSettings();
	this->close();
}

void NM_GUI_Bluetooth::saveSettings() {
    /*settings->setValue("NM_BLUETOOTH_N1", ui->doubleSpinBox_n1->value());
	settings->setValue("NM_BLUETOOTH_N2", ui->doubleSpinBox_n2->value());

    settings->setValue("NM_BLUETOOTH_DT", ui->comboBoxIntegrationMethod->currentIndex());*/
}

void NM_GUI_Bluetooth::loadSettings() {
	if (settings->value("NM_BLUETOOTH_DT", -1).toInt() == -1) return; //No settings saved yet

    /*ui->doubleSpinBox_n1->setValue(settings->value("NM_BLUETOOTH_N1").toDouble());
	ui->doubleSpinBox_n2->setValue(settings->value("NM_BLUETOOTH_N2").toDouble());

    ui->comboBoxIntegrationMethod->setCurrentIndex(settings->value("NM_BLUETOOTH_DT").toInt());*/
}
