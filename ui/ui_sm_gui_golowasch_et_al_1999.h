/********************************************************************************
** Form generated from reading UI file 'sm_gui_golowasch_et_al_1999.ui'
**
** Created by: Qt User Interface Compiler version 5.7.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SM_GUI_GOLOWASCH_ET_AL_1999_H
#define UI_SM_GUI_GOLOWASCH_ET_AL_1999_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QDialog>
#include <QtWidgets/QDoubleSpinBox>
#include <QtWidgets/QFrame>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpinBox>

QT_BEGIN_NAMESPACE

class Ui_SM_GUI_Golowasch_et_al_1999
{
public:
    QLabel *label_101;
    QDoubleSpinBox *double_gSlow;
    QLabel *label_29;
    QLabel *label_77;
    QLabel *label_85;
    QSpinBox *double_vthFast;
    QSpinBox *double_vthSlow;
    QDoubleSpinBox *double_k1;
    QLabel *label_76;
    QLabel *label_30;
    QLabel *label_106;
    QLabel *label_103;
    QDoubleSpinBox *double_gFast;
    QLabel *label_96;
    QDoubleSpinBox *double_k2;
    QLabel *label_95;
    QSpinBox *double_sFast;
    QLabel *label_87;
    QFrame *line_3;
    QFrame *line;
    QLabel *label_78;
    QLabel *label_67;
    QSpinBox *double_sSlow;
    QLabel *label_105;
    QPushButton *pushButton_accept;

    void setupUi(QDialog *SM_GUI_Golowasch_et_al_1999)
    {
        if (SM_GUI_Golowasch_et_al_1999->objectName().isEmpty())
            SM_GUI_Golowasch_et_al_1999->setObjectName(QStringLiteral("SM_GUI_Golowasch_et_al_1999"));
        SM_GUI_Golowasch_et_al_1999->setWindowModality(Qt::ApplicationModal);
        SM_GUI_Golowasch_et_al_1999->resize(400, 294);
        label_101 = new QLabel(SM_GUI_Golowasch_et_al_1999);
        label_101->setObjectName(QStringLiteral("label_101"));
        label_101->setGeometry(QRect(230, 70, 61, 15));
        double_gSlow = new QDoubleSpinBox(SM_GUI_Golowasch_et_al_1999);
        double_gSlow->setObjectName(QStringLiteral("double_gSlow"));
        double_gSlow->setGeometry(QRect(100, 110, 81, 24));
        double_gSlow->setDecimals(4);
        double_gSlow->setSingleStep(0.1);
        double_gSlow->setValue(0);
        label_29 = new QLabel(SM_GUI_Golowasch_et_al_1999);
        label_29->setObjectName(QStringLiteral("label_29"));
        label_29->setGeometry(QRect(30, 20, 61, 15));
        label_77 = new QLabel(SM_GUI_Golowasch_et_al_1999);
        label_77->setObjectName(QStringLiteral("label_77"));
        label_77->setGeometry(QRect(30, 113, 61, 16));
        label_85 = new QLabel(SM_GUI_Golowasch_et_al_1999);
        label_85->setObjectName(QStringLiteral("label_85"));
        label_85->setGeometry(QRect(348, 40, 16, 16));
        double_vthFast = new QSpinBox(SM_GUI_Golowasch_et_al_1999);
        double_vthFast->setObjectName(QStringLiteral("double_vthFast"));
        double_vthFast->setGeometry(QRect(290, 37, 51, 24));
        double_vthFast->setMaximum(100);
        double_vthFast->setValue(25);
        double_vthSlow = new QSpinBox(SM_GUI_Golowasch_et_al_1999);
        double_vthSlow->setObjectName(QStringLiteral("double_vthSlow"));
        double_vthSlow->setGeometry(QRect(290, 97, 51, 24));
        double_vthSlow->setMaximum(100);
        double_vthSlow->setValue(15);
        double_k1 = new QDoubleSpinBox(SM_GUI_Golowasch_et_al_1999);
        double_k1->setObjectName(QStringLiteral("double_k1"));
        double_k1->setGeometry(QRect(140, 160, 81, 24));
        double_k1->setDecimals(4);
        double_k1->setSingleStep(0.001);
        double_k1->setValue(14);
        label_76 = new QLabel(SM_GUI_Golowasch_et_al_1999);
        label_76->setObjectName(QStringLiteral("label_76"));
        label_76->setGeometry(QRect(30, 53, 61, 16));
        label_30 = new QLabel(SM_GUI_Golowasch_et_al_1999);
        label_30->setObjectName(QStringLiteral("label_30"));
        label_30->setGeometry(QRect(30, 82, 61, 15));
        label_106 = new QLabel(SM_GUI_Golowasch_et_al_1999);
        label_106->setObjectName(QStringLiteral("label_106"));
        label_106->setGeometry(QRect(350, 130, 16, 16));
        label_103 = new QLabel(SM_GUI_Golowasch_et_al_1999);
        label_103->setObjectName(QStringLiteral("label_103"));
        label_103->setGeometry(QRect(230, 130, 61, 15));
        double_gFast = new QDoubleSpinBox(SM_GUI_Golowasch_et_al_1999);
        double_gFast->setObjectName(QStringLiteral("double_gFast"));
        double_gFast->setGeometry(QRect(99, 50, 81, 24));
        double_gFast->setDecimals(4);
        double_gFast->setSingleStep(0.1);
        double_gFast->setValue(0.2);
        label_96 = new QLabel(SM_GUI_Golowasch_et_al_1999);
        label_96->setObjectName(QStringLiteral("label_96"));
        label_96->setGeometry(QRect(250, 163, 21, 16));
        double_k2 = new QDoubleSpinBox(SM_GUI_Golowasch_et_al_1999);
        double_k2->setObjectName(QStringLiteral("double_k2"));
        double_k2->setGeometry(QRect(280, 160, 81, 24));
        double_k2->setDecimals(4);
        double_k2->setSingleStep(0.001);
        double_k2->setValue(4);
        label_95 = new QLabel(SM_GUI_Golowasch_et_al_1999);
        label_95->setObjectName(QStringLiteral("label_95"));
        label_95->setGeometry(QRect(110, 163, 21, 16));
        double_sFast = new QSpinBox(SM_GUI_Golowasch_et_al_1999);
        double_sFast->setObjectName(QStringLiteral("double_sFast"));
        double_sFast->setGeometry(QRect(290, 64, 51, 24));
        double_sFast->setMaximum(100);
        double_sFast->setValue(5);
        label_87 = new QLabel(SM_GUI_Golowasch_et_al_1999);
        label_87->setObjectName(QStringLiteral("label_87"));
        label_87->setGeometry(QRect(348, 100, 16, 16));
        line_3 = new QFrame(SM_GUI_Golowasch_et_al_1999);
        line_3->setObjectName(QStringLiteral("line_3"));
        line_3->setGeometry(QRect(70, 84, 291, 20));
        line_3->setFrameShape(QFrame::HLine);
        line_3->setFrameShadow(QFrame::Sunken);
        line = new QFrame(SM_GUI_Golowasch_et_al_1999);
        line->setObjectName(QStringLiteral("line"));
        line->setGeometry(QRect(70, 19, 291, 20));
        line->setFrameShape(QFrame::HLine);
        line->setFrameShadow(QFrame::Sunken);
        label_78 = new QLabel(SM_GUI_Golowasch_et_al_1999);
        label_78->setObjectName(QStringLiteral("label_78"));
        label_78->setGeometry(QRect(230, 100, 51, 16));
        label_67 = new QLabel(SM_GUI_Golowasch_et_al_1999);
        label_67->setObjectName(QStringLiteral("label_67"));
        label_67->setGeometry(QRect(230, 40, 51, 16));
        double_sSlow = new QSpinBox(SM_GUI_Golowasch_et_al_1999);
        double_sSlow->setObjectName(QStringLiteral("double_sSlow"));
        double_sSlow->setGeometry(QRect(289, 127, 51, 24));
        double_sSlow->setMaximum(100);
        double_sSlow->setValue(1);
        label_105 = new QLabel(SM_GUI_Golowasch_et_al_1999);
        label_105->setObjectName(QStringLiteral("label_105"));
        label_105->setGeometry(QRect(350, 70, 16, 16));
        pushButton_accept = new QPushButton(SM_GUI_Golowasch_et_al_1999);
        pushButton_accept->setObjectName(QStringLiteral("pushButton_accept"));
        pushButton_accept->setGeometry(QRect(160, 250, 82, 23));

        retranslateUi(SM_GUI_Golowasch_et_al_1999);

        QMetaObject::connectSlotsByName(SM_GUI_Golowasch_et_al_1999);
    } // setupUi

    void retranslateUi(QDialog *SM_GUI_Golowasch_et_al_1999)
    {
        SM_GUI_Golowasch_et_al_1999->setWindowTitle(QApplication::translate("SM_GUI_Golowasch_et_al_1999", "Golowash et al. 1999 synapse parameters", Q_NULLPTR));
        label_101->setText(QApplication::translate("SM_GUI_Golowasch_et_al_1999", "s_fast", Q_NULLPTR));
        label_29->setText(QApplication::translate("SM_GUI_Golowasch_et_al_1999", "Fast", Q_NULLPTR));
        label_77->setText(QApplication::translate("SM_GUI_Golowasch_et_al_1999", "g (in uS):", Q_NULLPTR));
        label_85->setText(QApplication::translate("SM_GUI_Golowasch_et_al_1999", "%", Q_NULLPTR));
        label_76->setText(QApplication::translate("SM_GUI_Golowasch_et_al_1999", "g (in uS):", Q_NULLPTR));
        label_30->setText(QApplication::translate("SM_GUI_Golowasch_et_al_1999", "Slow", Q_NULLPTR));
        label_106->setText(QApplication::translate("SM_GUI_Golowasch_et_al_1999", "%", Q_NULLPTR));
        label_103->setText(QApplication::translate("SM_GUI_Golowasch_et_al_1999", "s_slow", Q_NULLPTR));
        label_96->setText(QApplication::translate("SM_GUI_Golowasch_et_al_1999", "k2", Q_NULLPTR));
        label_95->setText(QApplication::translate("SM_GUI_Golowasch_et_al_1999", "k1", Q_NULLPTR));
        label_87->setText(QApplication::translate("SM_GUI_Golowasch_et_al_1999", "%", Q_NULLPTR));
        label_78->setText(QApplication::translate("SM_GUI_Golowasch_et_al_1999", "V_slow", Q_NULLPTR));
        label_67->setText(QApplication::translate("SM_GUI_Golowasch_et_al_1999", "V_fast", Q_NULLPTR));
        label_105->setText(QApplication::translate("SM_GUI_Golowasch_et_al_1999", "%", Q_NULLPTR));
        pushButton_accept->setText(QApplication::translate("SM_GUI_Golowasch_et_al_1999", "Accept", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class SM_GUI_Golowasch_et_al_1999: public Ui_SM_GUI_Golowasch_et_al_1999 {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SM_GUI_GOLOWASCH_ET_AL_1999_H
