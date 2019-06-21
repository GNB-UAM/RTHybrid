/********************************************************************************
** Form generated from reading UI file 'nm_gui_cpg_model.ui'
**
** Created by: Qt User Interface Compiler version 5.7.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_NM_GUI_CPG_MODEL_H
#define UI_NM_GUI_CPG_MODEL_H

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

class Ui_NM_GUI_CPG_Model
{
public:
    QPushButton *pushButton_accept;
    QDoubleSpinBox *doubleSpinBox_V;
    QDoubleSpinBox *doubleSpinBox_Cm;
    QDoubleSpinBox *doubleSpinBox_g_na;
    QDoubleSpinBox *doubleSpinBox_g_na_v;
    QDoubleSpinBox *doubleSpinBox_i;
    QDoubleSpinBox *doubleSpinBox_g_b;
    QDoubleSpinBox *doubleSpinBox_V_na;
    QDoubleSpinBox *doubleSpinBox_g_k;
    QDoubleSpinBox *doubleSpinBox_V_k;
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
    QLabel *label_12;
    QLabel *label_13;
    QLabel *label_14;
    QLabel *label_15;
    QLabel *label_16;
    QLabel *label_17;
    QLabel *label_18;
    QLabel *label_19;
    QLabel *label_20;
    QDoubleSpinBox *doubleSpinBox_V_b;
    QDoubleSpinBox *doubleSpinBox_g_na_ttx;
    QDoubleSpinBox *doubleSpinBox_g_k_tea;
    QDoubleSpinBox *doubleSpinBox_g_ca;
    QDoubleSpinBox *doubleSpinBox_V_ca;
    QDoubleSpinBox *doubleSpinBox_g_ca_ca;
    QDoubleSpinBox *doubleSpinBox_k_beta;
    QDoubleSpinBox *doubleSpinBox_beta;
    QDoubleSpinBox *doubleSpinBox_k_s;
    QDoubleSpinBox *doubleSpinBox_rho;
    QComboBox *comboBoxIntegrationMethod;
    QDoubleSpinBox *doubleSpinBox_g_fast;
    QDoubleSpinBox *doubleSpinBox_v_fast;
    QLabel *label_21;
    QLabel *label_22;

    void setupUi(QDialog *NM_GUI_CPG_Model)
    {
        if (NM_GUI_CPG_Model->objectName().isEmpty())
            NM_GUI_CPG_Model->setObjectName(QStringLiteral("NM_GUI_CPG_Model"));
        NM_GUI_CPG_Model->setWindowModality(Qt::ApplicationModal);
        NM_GUI_CPG_Model->resize(609, 462);
        pushButton_accept = new QPushButton(NM_GUI_CPG_Model);
        pushButton_accept->setObjectName(QStringLiteral("pushButton_accept"));
        pushButton_accept->setGeometry(QRect(480, 420, 82, 23));
        doubleSpinBox_V = new QDoubleSpinBox(NM_GUI_CPG_Model);
        doubleSpinBox_V->setObjectName(QStringLiteral("doubleSpinBox_V"));
        doubleSpinBox_V->setGeometry(QRect(50, 30, 101, 24));
        doubleSpinBox_V->setDecimals(4);
        doubleSpinBox_V->setMinimum(-999);
        doubleSpinBox_V->setMaximum(999.99);
        doubleSpinBox_V->setValue(-55);
        doubleSpinBox_Cm = new QDoubleSpinBox(NM_GUI_CPG_Model);
        doubleSpinBox_Cm->setObjectName(QStringLiteral("doubleSpinBox_Cm"));
        doubleSpinBox_Cm->setGeometry(QRect(400, 30, 101, 24));
        doubleSpinBox_Cm->setDecimals(4);
        doubleSpinBox_Cm->setMinimum(-999);
        doubleSpinBox_Cm->setMaximum(999.99);
        doubleSpinBox_Cm->setValue(0.02);
        doubleSpinBox_g_na = new QDoubleSpinBox(NM_GUI_CPG_Model);
        doubleSpinBox_g_na->setObjectName(QStringLiteral("doubleSpinBox_g_na"));
        doubleSpinBox_g_na->setGeometry(QRect(90, 110, 101, 24));
        doubleSpinBox_g_na->setDecimals(4);
        doubleSpinBox_g_na->setMinimum(-999);
        doubleSpinBox_g_na->setMaximum(999.99);
        doubleSpinBox_g_na->setValue(0.0231);
        doubleSpinBox_g_na_v = new QDoubleSpinBox(NM_GUI_CPG_Model);
        doubleSpinBox_g_na_v->setObjectName(QStringLiteral("doubleSpinBox_g_na_v"));
        doubleSpinBox_g_na_v->setGeometry(QRect(90, 140, 101, 24));
        doubleSpinBox_g_na_v->setDecimals(4);
        doubleSpinBox_g_na_v->setMinimum(-999);
        doubleSpinBox_g_na_v->setMaximum(999.99);
        doubleSpinBox_g_na_v->setValue(0.11);
        doubleSpinBox_i = new QDoubleSpinBox(NM_GUI_CPG_Model);
        doubleSpinBox_i->setObjectName(QStringLiteral("doubleSpinBox_i"));
        doubleSpinBox_i->setGeometry(QRect(220, 30, 101, 24));
        doubleSpinBox_i->setDecimals(4);
        doubleSpinBox_i->setMinimum(-999);
        doubleSpinBox_i->setMaximum(999.99);
        doubleSpinBox_g_b = new QDoubleSpinBox(NM_GUI_CPG_Model);
        doubleSpinBox_g_b->setObjectName(QStringLiteral("doubleSpinBox_g_b"));
        doubleSpinBox_g_b->setGeometry(QRect(480, 110, 101, 24));
        doubleSpinBox_g_b->setDecimals(4);
        doubleSpinBox_g_b->setMinimum(-999);
        doubleSpinBox_g_b->setMaximum(999.99);
        doubleSpinBox_g_b->setValue(0.165);
        doubleSpinBox_V_na = new QDoubleSpinBox(NM_GUI_CPG_Model);
        doubleSpinBox_V_na->setObjectName(QStringLiteral("doubleSpinBox_V_na"));
        doubleSpinBox_V_na->setGeometry(QRect(90, 170, 101, 24));
        doubleSpinBox_V_na->setDecimals(4);
        doubleSpinBox_V_na->setMinimum(-999);
        doubleSpinBox_V_na->setMaximum(999.99);
        doubleSpinBox_V_na->setValue(40);
        doubleSpinBox_g_k = new QDoubleSpinBox(NM_GUI_CPG_Model);
        doubleSpinBox_g_k->setObjectName(QStringLiteral("doubleSpinBox_g_k"));
        doubleSpinBox_g_k->setGeometry(QRect(290, 110, 101, 24));
        doubleSpinBox_g_k->setDecimals(4);
        doubleSpinBox_g_k->setMinimum(-999);
        doubleSpinBox_g_k->setMaximum(999.99);
        doubleSpinBox_g_k->setValue(0.25);
        doubleSpinBox_V_k = new QDoubleSpinBox(NM_GUI_CPG_Model);
        doubleSpinBox_V_k->setObjectName(QStringLiteral("doubleSpinBox_V_k"));
        doubleSpinBox_V_k->setGeometry(QRect(290, 140, 101, 24));
        doubleSpinBox_V_k->setDecimals(4);
        doubleSpinBox_V_k->setMinimum(-999);
        doubleSpinBox_V_k->setMaximum(999.99);
        doubleSpinBox_V_k->setValue(-70);
        label = new QLabel(NM_GUI_CPG_Model);
        label->setObjectName(QStringLiteral("label"));
        label->setGeometry(QRect(20, 30, 61, 15));
        label_2 = new QLabel(NM_GUI_CPG_Model);
        label_2->setObjectName(QStringLiteral("label_2"));
        label_2->setGeometry(QRect(190, 30, 61, 15));
        label_3 = new QLabel(NM_GUI_CPG_Model);
        label_3->setObjectName(QStringLiteral("label_3"));
        label_3->setGeometry(QRect(370, 30, 61, 15));
        label_4 = new QLabel(NM_GUI_CPG_Model);
        label_4->setObjectName(QStringLiteral("label_4"));
        label_4->setGeometry(QRect(20, 140, 61, 15));
        label_5 = new QLabel(NM_GUI_CPG_Model);
        label_5->setObjectName(QStringLiteral("label_5"));
        label_5->setGeometry(QRect(20, 180, 61, 15));
        label_6 = new QLabel(NM_GUI_CPG_Model);
        label_6->setObjectName(QStringLiteral("label_6"));
        label_6->setGeometry(QRect(20, 110, 61, 15));
        label_7 = new QLabel(NM_GUI_CPG_Model);
        label_7->setObjectName(QStringLiteral("label_7"));
        label_7->setGeometry(QRect(240, 110, 61, 15));
        label_8 = new QLabel(NM_GUI_CPG_Model);
        label_8->setObjectName(QStringLiteral("label_8"));
        label_8->setGeometry(QRect(240, 140, 61, 15));
        label_9 = new QLabel(NM_GUI_CPG_Model);
        label_9->setObjectName(QStringLiteral("label_9"));
        label_9->setGeometry(QRect(430, 110, 61, 15));
        label_10 = new QLabel(NM_GUI_CPG_Model);
        label_10->setObjectName(QStringLiteral("label_10"));
        label_10->setGeometry(QRect(430, 140, 61, 15));
        label_11 = new QLabel(NM_GUI_CPG_Model);
        label_11->setObjectName(QStringLiteral("label_11"));
        label_11->setGeometry(QRect(20, 240, 61, 15));
        label_12 = new QLabel(NM_GUI_CPG_Model);
        label_12->setObjectName(QStringLiteral("label_12"));
        label_12->setGeometry(QRect(20, 270, 61, 15));
        label_13 = new QLabel(NM_GUI_CPG_Model);
        label_13->setObjectName(QStringLiteral("label_13"));
        label_13->setGeometry(QRect(240, 240, 61, 15));
        label_14 = new QLabel(NM_GUI_CPG_Model);
        label_14->setObjectName(QStringLiteral("label_14"));
        label_14->setGeometry(QRect(430, 240, 61, 15));
        label_15 = new QLabel(NM_GUI_CPG_Model);
        label_15->setObjectName(QStringLiteral("label_15"));
        label_15->setGeometry(QRect(430, 270, 61, 15));
        label_16 = new QLabel(NM_GUI_CPG_Model);
        label_16->setObjectName(QStringLiteral("label_16"));
        label_16->setGeometry(QRect(240, 270, 61, 15));
        label_17 = new QLabel(NM_GUI_CPG_Model);
        label_17->setObjectName(QStringLiteral("label_17"));
        label_17->setGeometry(QRect(240, 300, 61, 15));
        label_18 = new QLabel(NM_GUI_CPG_Model);
        label_18->setObjectName(QStringLiteral("label_18"));
        label_18->setGeometry(QRect(430, 300, 61, 15));
        label_19 = new QLabel(NM_GUI_CPG_Model);
        label_19->setObjectName(QStringLiteral("label_19"));
        label_19->setGeometry(QRect(430, 330, 61, 15));
        label_20 = new QLabel(NM_GUI_CPG_Model);
        label_20->setObjectName(QStringLiteral("label_20"));
        label_20->setGeometry(QRect(20, 430, 131, 16));
        doubleSpinBox_V_b = new QDoubleSpinBox(NM_GUI_CPG_Model);
        doubleSpinBox_V_b->setObjectName(QStringLiteral("doubleSpinBox_V_b"));
        doubleSpinBox_V_b->setGeometry(QRect(480, 140, 101, 24));
        doubleSpinBox_V_b->setDecimals(4);
        doubleSpinBox_V_b->setMinimum(-999);
        doubleSpinBox_V_b->setMaximum(999.99);
        doubleSpinBox_V_b->setValue(-58);
        doubleSpinBox_g_na_ttx = new QDoubleSpinBox(NM_GUI_CPG_Model);
        doubleSpinBox_g_na_ttx->setObjectName(QStringLiteral("doubleSpinBox_g_na_ttx"));
        doubleSpinBox_g_na_ttx->setGeometry(QRect(90, 240, 101, 24));
        doubleSpinBox_g_na_ttx->setDecimals(4);
        doubleSpinBox_g_na_ttx->setMinimum(-999);
        doubleSpinBox_g_na_ttx->setMaximum(999.99);
        doubleSpinBox_g_na_ttx->setValue(400);
        doubleSpinBox_g_k_tea = new QDoubleSpinBox(NM_GUI_CPG_Model);
        doubleSpinBox_g_k_tea->setObjectName(QStringLiteral("doubleSpinBox_g_k_tea"));
        doubleSpinBox_g_k_tea->setGeometry(QRect(90, 270, 101, 24));
        doubleSpinBox_g_k_tea->setDecimals(4);
        doubleSpinBox_g_k_tea->setMinimum(-999);
        doubleSpinBox_g_k_tea->setMaximum(999.99);
        doubleSpinBox_g_k_tea->setValue(10);
        doubleSpinBox_g_ca = new QDoubleSpinBox(NM_GUI_CPG_Model);
        doubleSpinBox_g_ca->setObjectName(QStringLiteral("doubleSpinBox_g_ca"));
        doubleSpinBox_g_ca->setGeometry(QRect(300, 240, 101, 24));
        doubleSpinBox_g_ca->setDecimals(4);
        doubleSpinBox_g_ca->setMinimum(-999);
        doubleSpinBox_g_ca->setMaximum(999.99);
        doubleSpinBox_g_ca->setValue(1.5);
        doubleSpinBox_V_ca = new QDoubleSpinBox(NM_GUI_CPG_Model);
        doubleSpinBox_V_ca->setObjectName(QStringLiteral("doubleSpinBox_V_ca"));
        doubleSpinBox_V_ca->setGeometry(QRect(300, 270, 101, 24));
        doubleSpinBox_V_ca->setDecimals(4);
        doubleSpinBox_V_ca->setMinimum(-999);
        doubleSpinBox_V_ca->setMaximum(999.99);
        doubleSpinBox_V_ca->setValue(150);
        doubleSpinBox_g_ca_ca = new QDoubleSpinBox(NM_GUI_CPG_Model);
        doubleSpinBox_g_ca_ca->setObjectName(QStringLiteral("doubleSpinBox_g_ca_ca"));
        doubleSpinBox_g_ca_ca->setGeometry(QRect(300, 300, 101, 24));
        doubleSpinBox_g_ca_ca->setDecimals(4);
        doubleSpinBox_g_ca_ca->setMinimum(-999);
        doubleSpinBox_g_ca_ca->setMaximum(999.99);
        doubleSpinBox_g_ca_ca->setValue(0.02);
        doubleSpinBox_k_beta = new QDoubleSpinBox(NM_GUI_CPG_Model);
        doubleSpinBox_k_beta->setObjectName(QStringLiteral("doubleSpinBox_k_beta"));
        doubleSpinBox_k_beta->setGeometry(QRect(480, 240, 101, 24));
        doubleSpinBox_k_beta->setDecimals(1);
        doubleSpinBox_k_beta->setMinimum(-999);
        doubleSpinBox_k_beta->setMaximum(100000);
        doubleSpinBox_k_beta->setValue(15000);
        doubleSpinBox_beta = new QDoubleSpinBox(NM_GUI_CPG_Model);
        doubleSpinBox_beta->setObjectName(QStringLiteral("doubleSpinBox_beta"));
        doubleSpinBox_beta->setGeometry(QRect(480, 270, 101, 24));
        doubleSpinBox_beta->setDecimals(8);
        doubleSpinBox_beta->setMinimum(-999);
        doubleSpinBox_beta->setMaximum(999.99);
        doubleSpinBox_beta->setValue(4e-5);
        doubleSpinBox_k_s = new QDoubleSpinBox(NM_GUI_CPG_Model);
        doubleSpinBox_k_s->setObjectName(QStringLiteral("doubleSpinBox_k_s"));
        doubleSpinBox_k_s->setGeometry(QRect(480, 300, 101, 24));
        doubleSpinBox_k_s->setDecimals(4);
        doubleSpinBox_k_s->setMinimum(-999);
        doubleSpinBox_k_s->setMaximum(999.99);
        doubleSpinBox_k_s->setValue(50);
        doubleSpinBox_rho = new QDoubleSpinBox(NM_GUI_CPG_Model);
        doubleSpinBox_rho->setObjectName(QStringLiteral("doubleSpinBox_rho"));
        doubleSpinBox_rho->setGeometry(QRect(480, 330, 101, 24));
        doubleSpinBox_rho->setDecimals(4);
        doubleSpinBox_rho->setMinimum(-999);
        doubleSpinBox_rho->setMaximum(999.99);
        doubleSpinBox_rho->setValue(0.002);
        comboBoxIntegrationMethod = new QComboBox(NM_GUI_CPG_Model);
        comboBoxIntegrationMethod->setObjectName(QStringLiteral("comboBoxIntegrationMethod"));
        comboBoxIntegrationMethod->setGeometry(QRect(160, 430, 161, 23));
        doubleSpinBox_g_fast = new QDoubleSpinBox(NM_GUI_CPG_Model);
        doubleSpinBox_g_fast->setObjectName(QStringLiteral("doubleSpinBox_g_fast"));
        doubleSpinBox_g_fast->setGeometry(QRect(90, 340, 101, 24));
        doubleSpinBox_g_fast->setValue(0.2);
        doubleSpinBox_v_fast = new QDoubleSpinBox(NM_GUI_CPG_Model);
        doubleSpinBox_v_fast->setObjectName(QStringLiteral("doubleSpinBox_v_fast"));
        doubleSpinBox_v_fast->setGeometry(QRect(90, 370, 101, 24));
        doubleSpinBox_v_fast->setValue(30);
        label_21 = new QLabel(NM_GUI_CPG_Model);
        label_21->setObjectName(QStringLiteral("label_21"));
        label_21->setGeometry(QRect(20, 340, 61, 15));
        label_22 = new QLabel(NM_GUI_CPG_Model);
        label_22->setObjectName(QStringLiteral("label_22"));
        label_22->setGeometry(QRect(20, 380, 61, 15));

        retranslateUi(NM_GUI_CPG_Model);

        comboBoxIntegrationMethod->setCurrentIndex(3);


        QMetaObject::connectSlotsByName(NM_GUI_CPG_Model);
    } // setupUi

    void retranslateUi(QDialog *NM_GUI_CPG_Model)
    {
        NM_GUI_CPG_Model->setWindowTitle(QApplication::translate("NM_GUI_CPG_Model", "Komendantov Kononenko (1996) neuron model", Q_NULLPTR));
        pushButton_accept->setText(QApplication::translate("NM_GUI_CPG_Model", "Accept", Q_NULLPTR));
        label->setText(QApplication::translate("NM_GUI_CPG_Model", "v0", Q_NULLPTR));
        label_2->setText(QApplication::translate("NM_GUI_CPG_Model", "Iext", Q_NULLPTR));
        label_3->setText(QApplication::translate("NM_GUI_CPG_Model", "Cm", Q_NULLPTR));
        label_4->setText(QApplication::translate("NM_GUI_CPG_Model", "g_na_v", Q_NULLPTR));
        label_5->setText(QApplication::translate("NM_GUI_CPG_Model", "V_na", Q_NULLPTR));
        label_6->setText(QApplication::translate("NM_GUI_CPG_Model", "g_na", Q_NULLPTR));
        label_7->setText(QApplication::translate("NM_GUI_CPG_Model", "g_k", Q_NULLPTR));
        label_8->setText(QApplication::translate("NM_GUI_CPG_Model", "V_k", Q_NULLPTR));
        label_9->setText(QApplication::translate("NM_GUI_CPG_Model", "g_b", Q_NULLPTR));
        label_10->setText(QApplication::translate("NM_GUI_CPG_Model", "V_b", Q_NULLPTR));
        label_11->setText(QApplication::translate("NM_GUI_CPG_Model", "g_na_ttx", Q_NULLPTR));
        label_12->setText(QApplication::translate("NM_GUI_CPG_Model", "g_k_tea", Q_NULLPTR));
        label_13->setText(QApplication::translate("NM_GUI_CPG_Model", "g_ca", Q_NULLPTR));
        label_14->setText(QApplication::translate("NM_GUI_CPG_Model", "k_beta", Q_NULLPTR));
        label_15->setText(QApplication::translate("NM_GUI_CPG_Model", "beta", Q_NULLPTR));
        label_16->setText(QApplication::translate("NM_GUI_CPG_Model", "V_ca", Q_NULLPTR));
        label_17->setText(QApplication::translate("NM_GUI_CPG_Model", "g_ca_ca", Q_NULLPTR));
        label_18->setText(QApplication::translate("NM_GUI_CPG_Model", "k_s", Q_NULLPTR));
        label_19->setText(QApplication::translate("NM_GUI_CPG_Model", "rho", Q_NULLPTR));
        label_20->setText(QApplication::translate("NM_GUI_CPG_Model", "Integration method", Q_NULLPTR));
        comboBoxIntegrationMethod->clear();
        comboBoxIntegrationMethod->insertItems(0, QStringList()
         << QApplication::translate("NM_GUI_CPG_Model", "Euler", Q_NULLPTR)
         << QApplication::translate("NM_GUI_CPG_Model", "Heun", Q_NULLPTR)
         << QApplication::translate("NM_GUI_CPG_Model", "Runge-Kutta 4", Q_NULLPTR)
         << QApplication::translate("NM_GUI_CPG_Model", "Runge-Kutta (6)5", Q_NULLPTR)
        );
        label_21->setText(QApplication::translate("NM_GUI_CPG_Model", "g fast", Q_NULLPTR));
        label_22->setText(QApplication::translate("NM_GUI_CPG_Model", "v fast", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class NM_GUI_CPG_Model: public Ui_NM_GUI_CPG_Model {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_NM_GUI_CPG_MODEL_H
