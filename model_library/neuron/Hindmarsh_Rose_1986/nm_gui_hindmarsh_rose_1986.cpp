#include "nm_gui_hindmarsh_rose_1986.h"
#include "ui_nm_gui_hindmarsh_rose_1986.h"

NM_GUI_Hindmarsh_Rose_1986::NM_GUI_Hindmarsh_Rose_1986(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::NM_GUI_Hindmarsh_Rose_1986)
{
    ui->setupUi(this);
}

NM_GUI_Hindmarsh_Rose_1986::~NM_GUI_Hindmarsh_Rose_1986()
{
    delete ui;
}

void NM_GUI_Hindmarsh_Rose_1986::on_pushButton_accept_clicked()
{

}
