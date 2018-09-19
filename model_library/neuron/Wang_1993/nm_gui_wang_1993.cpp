#include "nm_gui_wang_1993.h"
#include "ui_nm_gui_wang_1993.h"

NM_GUI_Wang_1993::NM_GUI_Wang_1993(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::NM_GUI_Wang_1993)
{
    ui->setupUi(this);
}

NM_GUI_Wang_1993::~NM_GUI_Wang_1993()
{
    delete ui;
}
