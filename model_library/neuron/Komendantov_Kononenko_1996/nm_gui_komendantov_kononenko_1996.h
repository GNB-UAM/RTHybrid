#ifndef NM_GUI_KOMENDANTOV_KONONENKO_1996_H
#define NM_GUI_KOMENDANTOV_KONONENKO_1996_H

#include <QDialog>
#include <QSettings>
#include "nm_komendantov_kononenko_1996.h"

namespace Ui {
class NM_GUI_Komendantov_Kononenko_1996;
}

class NM_GUI_Komendantov_Kononenko_1996 : public QDialog
{
	Q_OBJECT

public:
	explicit NM_GUI_Komendantov_Kononenko_1996(clamp_args * args = NULL, QWidget *parent = 0);
	~NM_GUI_Komendantov_Kononenko_1996();

private slots:
	void on_pushButton_accept_clicked();

private:
	Ui::NM_GUI_Komendantov_Kononenko_1996 *ui;
	clamp_args * args;
	QSettings * settings;

	void saveSettings();
	void loadSettings();
};

#endif // NM_GUI_KOMENDANTOV_KONONENKO_1996_H
