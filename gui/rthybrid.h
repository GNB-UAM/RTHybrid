#ifndef RTHYBRID_H
#define RTHYBRID_H

#include "ui_rthybrid.h"
//#include "clamp_launcher.h"

namespace Ui {
class RTHybrid;
}

class RTHybrid : public QMainWindow
{
    Q_OBJECT

public:
    explicit RTHybrid(QWidget *parent = 0);
    ~RTHybrid();

private slots:
    void on_simulate_clicked();

    void on_neuronModelCombo_activated(int index);

    void on_synapseModelCombo_activated(int index);

    void on_autocalCombo_activated(int index);

    void on_autoDetect_clicked();

private:
    Ui::RTHybrid *ui;
    QMovie *movie;
};

#endif // RTHYBRID_H
