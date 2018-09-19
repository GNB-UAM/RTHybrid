#include "nm_gui_ghigliazza_holmes_2004.h"
#include "ui_nm_gui_ghigliazza_holmes_2004.h"

NM_GUI_Ghigliazza_Holmes_2004::NM_GUI_Ghigliazza_Holmes_2004(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::NM_GUI_Ghigliazza_Holmes_2004)
{
    ui->setupUi(this);
}

NM_GUI_Ghigliazza_Holmes_2004::~NM_GUI_Ghigliazza_Holmes_2004()
{
    delete ui;
}

void NM_GUI_Ghigliazza_Holmes_2004::on_pushButton_accept_clicked()
{

}
