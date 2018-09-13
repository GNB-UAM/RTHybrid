#ifndef NM_GUI_HINDMARSH_ROSE_1986_H
#define NM_GUI_HINDMARSH_ROSE_1986_H

#include <QWidget>

namespace Ui {
class NM_GUI_Hindmarsh_Rose_1986;
}

class NM_GUI_Hindmarsh_Rose_1986 : public QWidget
{
    Q_OBJECT

public:
    explicit NM_GUI_Hindmarsh_Rose_1986(QWidget *parent = 0);
    ~NM_GUI_Hindmarsh_Rose_1986();

private:
    Ui::NM_GUI_Hindmarsh_Rose_1986 *ui;
};

#endif // NM_GUI_HINDMARSH_ROSE_1986_H
