#include "sm_gui_golowasch_et_at_1999.h"
#include "ui_sm_gui_golowasch_et_at_1999.h"

SM_GUI_Golowasch_et_at_1999::SM_GUI_Golowasch_et_at_1999(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::SM_GUI_Golowasch_et_at_1999)
{
    ui->setupUi(this);
}

SM_GUI_Golowasch_et_at_1999::~SM_GUI_Golowasch_et_at_1999()
{
    delete ui;
}
