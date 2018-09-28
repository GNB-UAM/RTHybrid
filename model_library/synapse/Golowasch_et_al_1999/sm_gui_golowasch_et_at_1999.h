#ifndef SM_GUI_GOLOWASCH_ET_AT_1999_H
#define SM_GUI_GOLOWASCH_ET_AT_1999_H

#include <QWidget>
#include <QSettings>
#include "sm_golowasch_et_al_1999.h"

namespace Ui {
class SM_GUI_Golowasch_et_at_1999;
}

class SM_GUI_Golowasch_et_at_1999 : public QWidget
{
    Q_OBJECT

public:
    explicit SM_GUI_Golowasch_et_at_1999(void * args = NULL, QWidget *parent = 0);
    ~SM_GUI_Golowasch_et_at_1999();

private:
    Ui::SM_GUI_Golowasch_et_at_1999 *ui;
    void * args;
    QSettings * settings;

    void saveSettings();
    void loadSettings();
};

#endif // SM_GUI_GOLOWASCH_ET_AT_1999_H
