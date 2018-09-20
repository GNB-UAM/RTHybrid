#ifndef NM_GUI_RULKOV_2002_H
#define NM_GUI_RULKOV_2002_H

#include <QWidget>
#include <QSettings>
#include "nm_rulkov_2002.h"

namespace Ui {
class NM_GUI_Rulkov_2002;
}

class NM_GUI_Rulkov_2002 : public QWidget
{
    Q_OBJECT

public:
    explicit NM_GUI_Rulkov_2002(clamp_args * args = NULL, QWidget *parent = 0);
    ~NM_GUI_Rulkov_2002();

private slots:
    void on_pushButton_accept_clicked();

private:
    Ui::NM_GUI_Rulkov_2002 *ui;
    clamp_args * args;
    QSettings * settings;

    void saveSettings();
    void loadSettings();
};

#endif // NM_GUI_RULKOV_2002_H
