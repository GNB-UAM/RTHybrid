#ifndef NM_GUI_NOWOTNY_ET_AL_2008_H
#define NM_GUI_NOWOTNY_ET_AL_2008_H

#include <QDialog>
#include <QSettings>
#include "nm_nowotny_et_al_2008.h"

namespace Ui {
class NM_GUI_Nowotny_et_al_2008;
}

class NM_GUI_Nowotny_et_al_2008 : public QDialog
{
    Q_OBJECT

public:
    explicit NM_GUI_Nowotny_et_al_2008(clamp_args * args = NULL, QWidget *parent = 0);
    ~NM_GUI_Nowotny_et_al_2008();

private slots:
    void on_pushButton_accept_clicked();

private:
    Ui::NM_GUI_Nowotny_et_al_2008 *ui;
    clamp_args * args;
    QSettings * settings;

    void saveSettings();
    void loadSettings();
};

#endif // NM_GUI_NOWOTNY_ET_AL_2008_H
