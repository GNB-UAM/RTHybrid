#ifndef NM_GUI_IZHIKEVICH_2003_H
#define NM_GUI_IZHIKEVICH_2003_H

#include <QWidget>
#include <QSettings>
#include "../../clamp/includes/types_clamp.h"
#include "../../clamp/includes/neuron_models_functions.h"

namespace Ui {
class NM_GUI_Izhikevich_2003;
}

class NM_GUI_Izhikevich_2003 : public QWidget
{
    Q_OBJECT

public:
    explicit NM_GUI_Izhikevich_2003(clamp_args * args = NULL, QWidget *parent = 0);
    ~NM_GUI_Izhikevich_2003();

private slots:
    void on_pushButton_accept_clicked();

private:
    Ui::NM_GUI_Izhikevich_2003 *ui;
    clamp_args * args;
    QSettings * settings;

    void saveSettings();
    void loadSettings();
};

#endif // NM_GUI_IZHIKEVICH_2003_H
