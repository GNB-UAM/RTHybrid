#ifndef NM_GUI_CPG_MODEL_H
#define NM_GUI_CPG_MODEL_H

#include <QDialog>
#include <QSettings>
#include "../Komendantov_Kononenko_1996/nm_komendantov_kononenko_1996.h"

namespace Ui {
class NM_GUI_CPG_Model;
}

class NM_GUI_CPG_Model : public QDialog
{
	Q_OBJECT

public:
	explicit NM_GUI_CPG_Model(clamp_args * args = NULL, QWidget *parent = 0);
	~NM_GUI_CPG_Model();

private slots:
	void on_pushButton_accept_clicked();

private:
	Ui::NM_GUI_CPG_Model *ui;
	clamp_args * args;
	QSettings * settings;

	void saveSettings();
	void loadSettings();
};

#endif // NM_GUI_CPG_MODEL_H
