/********************************************************************************
** Form generated from reading UI file 'sm_gui_greenberg_manor_2005.ui'
**
** Created by: Qt User Interface Compiler version 5.7.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SM_GUI_GREENBERG_MANOR_2005_H
#define UI_SM_GUI_GREENBERG_MANOR_2005_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QDialog>
#include <QtWidgets/QDoubleSpinBox>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>

QT_BEGIN_NAMESPACE

class Ui_SM_GUI_Greenberg_Manor_2005
{
public:
    QPushButton *pushButton_accept;
    QLabel *label;
    QLabel *label_2;
    QLabel *label_3;
    QLabel *label_4;
    QLabel *label_5;
    QLabel *label_6;
    QLabel *label_7;
    QLabel *label_8;
    QLabel *label_9;
    QLabel *label_10;
    QLabel *label_11;
    QDoubleSpinBox *doubleSpinBox_g;
    QDoubleSpinBox *doubleSpinBox_esyn;
    QDoubleSpinBox *doubleSpinBox_p;
    QDoubleSpinBox *doubleSpinBox_v12_m;
    QDoubleSpinBox *doubleSpinBox_k_m;
    QDoubleSpinBox *doubleSpinBox_tau_hi_m;
    QDoubleSpinBox *doubleSpinBox_tau_lo_m;
    QDoubleSpinBox *doubleSpinBox_v12_h;
    QDoubleSpinBox *doubleSpinBox_q;
    QDoubleSpinBox *doubleSpinBox_k_h;
    QDoubleSpinBox *doubleSpinBox_tau_lo_h;
    QDoubleSpinBox *doubleSpinBox_tau_hi_h;
    QComboBox *comboBoxIntegration;
    QDoubleSpinBox *doubleSpinBox_dt;

    void setupUi(QDialog *SM_GUI_Greenberg_Manor_2005)
    {
        if (SM_GUI_Greenberg_Manor_2005->objectName().isEmpty())
            SM_GUI_Greenberg_Manor_2005->setObjectName(QStringLiteral("SM_GUI_Greenberg_Manor_2005"));
        SM_GUI_Greenberg_Manor_2005->setWindowModality(Qt::ApplicationModal);
        SM_GUI_Greenberg_Manor_2005->resize(430, 383);
        pushButton_accept = new QPushButton(SM_GUI_Greenberg_Manor_2005);
        pushButton_accept->setObjectName(QStringLiteral("pushButton_accept"));
        pushButton_accept->setGeometry(QRect(170, 350, 82, 23));
        label = new QLabel(SM_GUI_Greenberg_Manor_2005);
        label->setObjectName(QStringLiteral("label"));
        label->setGeometry(QRect(30, 22, 61, 15));
        label_2 = new QLabel(SM_GUI_Greenberg_Manor_2005);
        label_2->setObjectName(QStringLiteral("label_2"));
        label_2->setGeometry(QRect(140, 60, 131, 16));
        label_3 = new QLabel(SM_GUI_Greenberg_Manor_2005);
        label_3->setObjectName(QStringLiteral("label_3"));
        label_3->setGeometry(QRect(20, 100, 91, 16));
        label_4 = new QLabel(SM_GUI_Greenberg_Manor_2005);
        label_4->setObjectName(QStringLiteral("label_4"));
        label_4->setGeometry(QRect(20, 130, 91, 16));
        label_5 = new QLabel(SM_GUI_Greenberg_Manor_2005);
        label_5->setObjectName(QStringLiteral("label_5"));
        label_5->setGeometry(QRect(20, 160, 71, 16));
        label_6 = new QLabel(SM_GUI_Greenberg_Manor_2005);
        label_6->setObjectName(QStringLiteral("label_6"));
        label_6->setGeometry(QRect(20, 190, 111, 16));
        label_7 = new QLabel(SM_GUI_Greenberg_Manor_2005);
        label_7->setObjectName(QStringLiteral("label_7"));
        label_7->setGeometry(QRect(20, 220, 101, 16));
        label_8 = new QLabel(SM_GUI_Greenberg_Manor_2005);
        label_8->setObjectName(QStringLiteral("label_8"));
        label_8->setGeometry(QRect(300, 60, 131, 16));
        label_9 = new QLabel(SM_GUI_Greenberg_Manor_2005);
        label_9->setObjectName(QStringLiteral("label_9"));
        label_9->setGeometry(QRect(240, 20, 61, 16));
        label_10 = new QLabel(SM_GUI_Greenberg_Manor_2005);
        label_10->setObjectName(QStringLiteral("label_10"));
        label_10->setGeometry(QRect(40, 270, 141, 16));
        label_11 = new QLabel(SM_GUI_Greenberg_Manor_2005);
        label_11->setObjectName(QStringLiteral("label_11"));
        label_11->setGeometry(QRect(260, 270, 111, 16));
        doubleSpinBox_g = new QDoubleSpinBox(SM_GUI_Greenberg_Manor_2005);
        doubleSpinBox_g->setObjectName(QStringLiteral("doubleSpinBox_g"));
        doubleSpinBox_g->setGeometry(QRect(94, 18, 91, 24));
        doubleSpinBox_g->setDecimals(5);
        doubleSpinBox_g->setMinimum(-999);
        doubleSpinBox_g->setMaximum(999.99);
        doubleSpinBox_esyn = new QDoubleSpinBox(SM_GUI_Greenberg_Manor_2005);
        doubleSpinBox_esyn->setObjectName(QStringLiteral("doubleSpinBox_esyn"));
        doubleSpinBox_esyn->setGeometry(QRect(310, 16, 91, 24));
        doubleSpinBox_esyn->setDecimals(5);
        doubleSpinBox_esyn->setMinimum(-999);
        doubleSpinBox_esyn->setMaximum(999.99);
        doubleSpinBox_esyn->setValue(-5);
        doubleSpinBox_p = new QDoubleSpinBox(SM_GUI_Greenberg_Manor_2005);
        doubleSpinBox_p->setObjectName(QStringLiteral("doubleSpinBox_p"));
        doubleSpinBox_p->setGeometry(QRect(146, 93, 91, 24));
        doubleSpinBox_p->setDecimals(5);
        doubleSpinBox_p->setMinimum(-999);
        doubleSpinBox_p->setMaximum(999.99);
        doubleSpinBox_p->setValue(1);
        doubleSpinBox_v12_m = new QDoubleSpinBox(SM_GUI_Greenberg_Manor_2005);
        doubleSpinBox_v12_m->setObjectName(QStringLiteral("doubleSpinBox_v12_m"));
        doubleSpinBox_v12_m->setGeometry(QRect(146, 123, 91, 24));
        doubleSpinBox_v12_m->setDecimals(5);
        doubleSpinBox_v12_m->setMinimum(-999);
        doubleSpinBox_v12_m->setMaximum(999.99);
        doubleSpinBox_v12_m->setValue(22);
        doubleSpinBox_k_m = new QDoubleSpinBox(SM_GUI_Greenberg_Manor_2005);
        doubleSpinBox_k_m->setObjectName(QStringLiteral("doubleSpinBox_k_m"));
        doubleSpinBox_k_m->setGeometry(QRect(146, 153, 91, 24));
        doubleSpinBox_k_m->setDecimals(5);
        doubleSpinBox_k_m->setMinimum(-999);
        doubleSpinBox_k_m->setMaximum(999.99);
        doubleSpinBox_k_m->setValue(4);
        doubleSpinBox_tau_hi_m = new QDoubleSpinBox(SM_GUI_Greenberg_Manor_2005);
        doubleSpinBox_tau_hi_m->setObjectName(QStringLiteral("doubleSpinBox_tau_hi_m"));
        doubleSpinBox_tau_hi_m->setGeometry(QRect(146, 183, 91, 24));
        doubleSpinBox_tau_hi_m->setDecimals(5);
        doubleSpinBox_tau_hi_m->setMinimum(-99999);
        doubleSpinBox_tau_hi_m->setMaximum(100000);
        doubleSpinBox_tau_hi_m->setValue(1);
        doubleSpinBox_tau_lo_m = new QDoubleSpinBox(SM_GUI_Greenberg_Manor_2005);
        doubleSpinBox_tau_lo_m->setObjectName(QStringLiteral("doubleSpinBox_tau_lo_m"));
        doubleSpinBox_tau_lo_m->setGeometry(QRect(146, 213, 91, 24));
        doubleSpinBox_tau_lo_m->setDecimals(5);
        doubleSpinBox_tau_lo_m->setMinimum(-99999);
        doubleSpinBox_tau_lo_m->setMaximum(100000);
        doubleSpinBox_tau_lo_m->setValue(1);
        doubleSpinBox_v12_h = new QDoubleSpinBox(SM_GUI_Greenberg_Manor_2005);
        doubleSpinBox_v12_h->setObjectName(QStringLiteral("doubleSpinBox_v12_h"));
        doubleSpinBox_v12_h->setGeometry(QRect(305, 123, 91, 24));
        doubleSpinBox_v12_h->setDecimals(5);
        doubleSpinBox_v12_h->setMinimum(-999);
        doubleSpinBox_v12_h->setMaximum(999.99);
        doubleSpinBox_v12_h->setValue(18);
        doubleSpinBox_q = new QDoubleSpinBox(SM_GUI_Greenberg_Manor_2005);
        doubleSpinBox_q->setObjectName(QStringLiteral("doubleSpinBox_q"));
        doubleSpinBox_q->setGeometry(QRect(305, 93, 91, 24));
        doubleSpinBox_q->setDecimals(5);
        doubleSpinBox_q->setMinimum(-999);
        doubleSpinBox_q->setMaximum(999.99);
        doubleSpinBox_q->setValue(1);
        doubleSpinBox_k_h = new QDoubleSpinBox(SM_GUI_Greenberg_Manor_2005);
        doubleSpinBox_k_h->setObjectName(QStringLiteral("doubleSpinBox_k_h"));
        doubleSpinBox_k_h->setGeometry(QRect(305, 153, 91, 24));
        doubleSpinBox_k_h->setDecimals(5);
        doubleSpinBox_k_h->setMinimum(-999);
        doubleSpinBox_k_h->setMaximum(999.99);
        doubleSpinBox_k_h->setValue(2.5);
        doubleSpinBox_tau_lo_h = new QDoubleSpinBox(SM_GUI_Greenberg_Manor_2005);
        doubleSpinBox_tau_lo_h->setObjectName(QStringLiteral("doubleSpinBox_tau_lo_h"));
        doubleSpinBox_tau_lo_h->setGeometry(QRect(305, 213, 91, 24));
        doubleSpinBox_tau_lo_h->setDecimals(5);
        doubleSpinBox_tau_lo_h->setMinimum(-99999);
        doubleSpinBox_tau_lo_h->setMaximum(100000);
        doubleSpinBox_tau_lo_h->setValue(300);
        doubleSpinBox_tau_hi_h = new QDoubleSpinBox(SM_GUI_Greenberg_Manor_2005);
        doubleSpinBox_tau_hi_h->setObjectName(QStringLiteral("doubleSpinBox_tau_hi_h"));
        doubleSpinBox_tau_hi_h->setGeometry(QRect(305, 183, 91, 24));
        doubleSpinBox_tau_hi_h->setDecimals(5);
        doubleSpinBox_tau_hi_h->setMinimum(-99999);
        doubleSpinBox_tau_hi_h->setMaximum(100000);
        doubleSpinBox_tau_hi_h->setValue(1900);
        comboBoxIntegration = new QComboBox(SM_GUI_Greenberg_Manor_2005);
        comboBoxIntegration->setObjectName(QStringLiteral("comboBoxIntegration"));
        comboBoxIntegration->setGeometry(QRect(40, 300, 141, 23));
        doubleSpinBox_dt = new QDoubleSpinBox(SM_GUI_Greenberg_Manor_2005);
        doubleSpinBox_dt->setObjectName(QStringLiteral("doubleSpinBox_dt"));
        doubleSpinBox_dt->setGeometry(QRect(260, 297, 91, 24));
        doubleSpinBox_dt->setDecimals(5);
        doubleSpinBox_dt->setMinimum(0);
        doubleSpinBox_dt->setMaximum(100000);
        doubleSpinBox_dt->setValue(0.001);

        retranslateUi(SM_GUI_Greenberg_Manor_2005);

        comboBoxIntegration->setCurrentIndex(3);


        QMetaObject::connectSlotsByName(SM_GUI_Greenberg_Manor_2005);
    } // setupUi

    void retranslateUi(QDialog *SM_GUI_Greenberg_Manor_2005)
    {
        SM_GUI_Greenberg_Manor_2005->setWindowTitle(QApplication::translate("SM_GUI_Greenberg_Manor_2005", "Greenberg_Manor_2005 synapse parameters", Q_NULLPTR));
        pushButton_accept->setText(QApplication::translate("SM_GUI_Greenberg_Manor_2005", "Accept", Q_NULLPTR));
        label->setText(QApplication::translate("SM_GUI_Greenberg_Manor_2005", "g (in uS)", Q_NULLPTR));
        label_2->setText(QApplication::translate("SM_GUI_Greenberg_Manor_2005", "m state variable", Q_NULLPTR));
        label_3->setText(QApplication::translate("SM_GUI_Greenberg_Manor_2005", "Gating power", Q_NULLPTR));
        label_4->setText(QApplication::translate("SM_GUI_Greenberg_Manor_2005", "V1/2 (%)", Q_NULLPTR));
        label_5->setText(QApplication::translate("SM_GUI_Greenberg_Manor_2005", "k (%)", Q_NULLPTR));
        label_6->setText(QApplication::translate("SM_GUI_Greenberg_Manor_2005", "Tau high (in ms)", Q_NULLPTR));
        label_7->setText(QApplication::translate("SM_GUI_Greenberg_Manor_2005", "Tau low (in ms)", Q_NULLPTR));
        label_8->setText(QApplication::translate("SM_GUI_Greenberg_Manor_2005", "h state variable", Q_NULLPTR));
        label_9->setText(QApplication::translate("SM_GUI_Greenberg_Manor_2005", "Esyn (%)", Q_NULLPTR));
        label_10->setText(QApplication::translate("SM_GUI_Greenberg_Manor_2005", "Integration method", Q_NULLPTR));
        label_11->setText(QApplication::translate("SM_GUI_Greenberg_Manor_2005", "Integration step", Q_NULLPTR));
        comboBoxIntegration->clear();
        comboBoxIntegration->insertItems(0, QStringList()
         << QApplication::translate("SM_GUI_Greenberg_Manor_2005", "Euler", Q_NULLPTR)
         << QApplication::translate("SM_GUI_Greenberg_Manor_2005", "Heun", Q_NULLPTR)
         << QApplication::translate("SM_GUI_Greenberg_Manor_2005", "Runge-Kutta 4", Q_NULLPTR)
         << QApplication::translate("SM_GUI_Greenberg_Manor_2005", "Runge-Kutta (6)5", Q_NULLPTR)
        );
    } // retranslateUi

};

namespace Ui {
    class SM_GUI_Greenberg_Manor_2005: public Ui_SM_GUI_Greenberg_Manor_2005 {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SM_GUI_GREENBERG_MANOR_2005_H
