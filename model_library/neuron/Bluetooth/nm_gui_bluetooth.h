#ifndef NM_GUI_BLUETOOTH_H
#define NM_GUI_BLUETOOTH_H

#include <QDialog>
#include <QSettings>
#include "nm_bluetooth.h"

namespace Ui {
class NM_GUI_Bluetooth;
}

class NM_GUI_Bluetooth : public QDialog
{
	Q_OBJECT

public:
	explicit NM_GUI_Bluetooth(clamp_args * args = NULL, QWidget *parent = 0);
	~NM_GUI_Bluetooth();

private slots:
	void on_pushButton_accept_clicked();

private:
	Ui::NM_GUI_Bluetooth *ui;
	clamp_args * args;
	QSettings * settings;

	void saveSettings();
	void loadSettings();
};

#endif // NM_GUI_BLUETOOTH_H