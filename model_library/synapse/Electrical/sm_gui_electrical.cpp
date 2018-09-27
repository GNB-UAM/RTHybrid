#include "sm_gui_electrical.h"
#include "ui_sm_gui_electrical.h"

SM_GUI_Electrical::SM_GUI_Electrical(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::SM_GUI_Electrical)
{
    ui->setupUi(this);
}

SM_GUI_Electrical::~SM_GUI_Electrical()
{
    delete ui;
}
