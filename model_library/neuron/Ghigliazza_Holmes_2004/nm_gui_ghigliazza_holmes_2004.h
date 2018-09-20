#ifndef NM_GUI_GHIGLIAZZA_HOLMES_2004_H
#define NM_GUI_GHIGLIAZZA_HOLMES_2004_H

#include <QWidget>
#include <QSettings>
#include "nm_ghigliazza_holmes_2004.h"

namespace Ui {
class NM_GUI_Ghigliazza_Holmes_2004;
}

class NM_GUI_Ghigliazza_Holmes_2004 : public QWidget
{
    Q_OBJECT

public:
    explicit NM_GUI_Ghigliazza_Holmes_2004(clamp_args * args = NULL, QWidget *parent = 0);
    ~NM_GUI_Ghigliazza_Holmes_2004();

private slots:
    void on_pushButton_accept_clicked();

private:
    Ui::NM_GUI_Ghigliazza_Holmes_2004 *ui;
    clamp_args * args;
    QSettings * settings;

    void saveSettings();
    void loadSettings();
};

#endif // NM_GUI_GHIGLIAZZA_HOLMES_2004_H
