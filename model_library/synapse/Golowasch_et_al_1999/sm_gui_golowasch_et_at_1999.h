#ifndef SM_GUI_GOLOWASCH_ET_AT_1999_H
#define SM_GUI_GOLOWASCH_ET_AT_1999_H

#include <QWidget>

namespace Ui {
class SM_GUI_Golowasch_et_at_1999;
}

class SM_GUI_Golowasch_et_at_1999 : public QWidget
{
    Q_OBJECT

public:
    explicit SM_GUI_Golowasch_et_at_1999(QWidget *parent = 0);
    ~SM_GUI_Golowasch_et_at_1999();

private:
    Ui::SM_GUI_Golowasch_et_at_1999 *ui;
};

#endif // SM_GUI_GOLOWASCH_ET_AT_1999_H
