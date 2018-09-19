#ifndef NM_GUI_WANG_1993_H
#define NM_GUI_WANG_1993_H

#include <QWidget>
#include <QSettings>
#include "nm_wang_1993.h"

namespace Ui {
class NM_GUI_Wang_1993;
}

class NM_GUI_Wang_1993 : public QWidget
{
    Q_OBJECT

public:
    explicit NM_GUI_Wang_1993(QWidget *parent = 0);
    ~NM_GUI_Wang_1993();

private:
    Ui::NM_GUI_Wang_1993 *ui;
    clamp_args * args;
    QSettings * settings;

    void saveSettings();
    void loadSettings();
};

#endif // NM_GUI_WANG_1993_H
