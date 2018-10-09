#ifndef SM_GUI_DESTEXHE_ET_AL_1994_H
#define SM_GUI_DESTEXHE_ET_AL_1994_H

#include <QDialog>
#include <QSettings>
#include "sm_destexhe_et_al_1994.h"

namespace Ui {
class SM_GUI_Destexhe_et_al_1994;
}

class SM_GUI_Destexhe_et_al_1994 : public QDialog
{
    Q_OBJECT

public:
    explicit SM_GUI_Destexhe_et_al_1994(void ** args = NULL, unsigned int direction = 2, QWidget *parent = 0);
    ~SM_GUI_Destexhe_et_al_1994();

private slots:
	void on_pushButton_accept_clicked();

private:
    Ui::SM_GUI_Destexhe_et_al_1994 *ui;
    void ** args;
    QSettings * settings;

    void saveSettings();
    void loadSettings();
};

#endif // SM_GUI_DESTEXHE_ET_AL_1994_H
