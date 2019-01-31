#ifndef NM_GUI_HINDMARSH_ROSE_1986_H
#define NM_GUI_HINDMARSH_ROSE_1986_H

#include <QWidget>
#include <QSettings>
#include "nm_hindmarsh_rose_1986.h"

namespace Ui {
class NM_GUI_Hindmarsh_Rose_1986;
}

class NM_GUI_Hindmarsh_Rose_1986 : public QWidget
{
    Q_OBJECT

public:
    explicit NM_GUI_Hindmarsh_Rose_1986(clamp_args * args = NULL, QWidget *parent = 0);
    ~NM_GUI_Hindmarsh_Rose_1986();

private slots:
    void on_pushButton_accept_clicked();

private:
    Ui::NM_GUI_Hindmarsh_Rose_1986 *ui;
    clamp_args * args;
    QSettings * settings;

    void saveSettings();
    void loadSettings();
};

#endif // NM_GUI_HINDMARSH_ROSE_1986_H
