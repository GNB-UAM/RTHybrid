#ifndef NM_IZHIKEVICH_H
#define NM_IZHIKEVICH_H

#include <QWidget>
#include <QSettings>
#include "../../../clamp/includes/types_clamp.h"
#include "../../../clamp/includes/neuron_models_functions.h"

namespace Ui {
class NM_Izhikevich;
}

class NM_Izhikevich : public QWidget
{
    Q_OBJECT

public:
    explicit NM_Izhikevich(clamp_args * args = NULL, QWidget *parent = 0);
    ~NM_Izhikevich();

private slots:
    void on_pushButton_accept_clicked();

private:
    Ui::NM_Izhikevich *ui;
    clamp_args * args;
    QSettings * settings;

    void saveSettings();
    void loadSettings();
};

#endif // NM_IZHIKEVICH_H
