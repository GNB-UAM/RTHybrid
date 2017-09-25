#ifndef RTBIOMANAGER_H
#define RTBIOMANAGER_H

#include <QMainWindow>

namespace Ui {
class RTBiomanager;
}

class RTBiomanager : public QMainWindow
{
    Q_OBJECT

public:
    explicit RTBiomanager(QWidget *parent = 0);
    ~RTBiomanager();

private slots:
    void on_simulate_clicked();

    void on_neuronModelCombo_activated(int index);

    void on_synapseModelCombo_activated(int index);

private:
    Ui::RTBiomanager *ui;
};

#endif // RTBIOMANAGER_H
