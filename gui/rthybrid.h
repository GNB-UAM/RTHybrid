#ifndef RTHYBRID_H
#define RTHYBRID_H

#include "ui_rthybrid.h"
#include "clamplauncher.h"

namespace Ui {
class RTHybrid;
}

class RTHybrid : public QMainWindow
{
    Q_OBJECT

public:
    explicit RTHybrid(QWidget *parent = 0);
    ~RTHybrid();
    void closeEvent (QCloseEvent *event);

private slots:
    void on_buttonStart_clicked();

    void on_buttonStop_clicked();

    void on_neuronModelCombo_activated(int index);

    void on_synapseModelCombo_activated(int index);

    void on_autocalCombo_activated(int index);

    void on_autoDetect_clicked();

    void clampEnd();


private:
    Ui::RTHybrid *ui;
    QMovie *movie;
    ClampLauncher * cl;
    unsigned short isClampRunning = false;
};

#endif // RTHYBRID_H
