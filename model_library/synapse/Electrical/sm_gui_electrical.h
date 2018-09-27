#ifndef SM_GUI_ELECTRICAL_H
#define SM_GUI_ELECTRICAL_H

#include <QWidget>

namespace Ui {
class SM_GUI_Electrical;
}

class SM_GUI_Electrical : public QWidget
{
    Q_OBJECT

public:
    explicit SM_GUI_Electrical(QWidget *parent = 0);
    ~SM_GUI_Electrical();

private:
    Ui::SM_GUI_Electrical *ui;
};

#endif // SM_GUI_ELECTRICAL_H
