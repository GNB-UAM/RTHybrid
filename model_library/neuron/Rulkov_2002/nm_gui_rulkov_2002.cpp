#include "nm_gui_rulkov_2002.h"
#include "ui_nm_gui_rulkov_2002.h"

NM_GUI_Rulkov_2002::NM_GUI_Rulkov_2002(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::NM_GUI_Rulkov_2002)
{
    ui->setupUi(this);
}

NM_GUI_Rulkov_2002::~NM_GUI_Rulkov_2002()
{
    delete ui;
}

void NM_GUI_Rulkov_2002::on_pushButton_accept_clicked()
{

}
