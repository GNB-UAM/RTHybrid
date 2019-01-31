#ifndef SM_GUI_GREENBERG_MANOR_2005_H
#define SM_GUI_GREENBERG_MANOR_2005_H

#include <QDialog>
#include <QSettings>
#include "sm_greenberg_manor_2005.h"

namespace Ui {
class SM_GUI_Greenberg_Manor_2005;
}

class SM_GUI_Greenberg_Manor_2005 : public QDialog
{
    Q_OBJECT

public:
    explicit SM_GUI_Greenberg_Manor_2005(void ** args = NULL, unsigned int direction = 2, QWidget *parent = 0);
    ~SM_GUI_Greenberg_Manor_2005();

private slots:
	void on_pushButton_accept_clicked();

private:
    Ui::SM_GUI_Greenberg_Manor_2005 *ui;
    void ** args;
    QSettings * settings;

    void saveSettings();
    void loadSettings();
};

#endif // SM_GUI_GREENBERG_MANOR_2005_H
