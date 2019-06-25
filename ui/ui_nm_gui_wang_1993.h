/********************************************************************************
** Form generated from reading UI file 'nm_gui_wang_1993.ui'
**
** Created by: Qt User Interface Compiler version 5.7.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_NM_GUI_WANG_1993_H
#define UI_NM_GUI_WANG_1993_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QDoubleSpinBox>
#include <QtWidgets/QFrame>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_NM_GUI_Wang_1993
{
public:
    QLabel *label_8;
    QLabel *label_9;
    QLabel *label_10;
    QGroupBox *groupBox_InitialValues;
    QLabel *label_14;
    QDoubleSpinBox *doubleSpinBox_V;
    QGroupBox *groupBox_Parameters;
    QGroupBox *groupBox_Channels;
    QLabel *label_5;
    QLabel *label_2;
    QLabel *label_3;
    QLabel *label_4;
    QLabel *label;
    QLabel *label_6;
    QDoubleSpinBox *doubleSpinBox_g_Na;
    QDoubleSpinBox *doubleSpinBox_g_NaP;
    QDoubleSpinBox *doubleSpinBox_g_K;
    QDoubleSpinBox *doubleSpinBox_g_KS;
    QDoubleSpinBox *doubleSpinBox_g_L;
    QDoubleSpinBox *doubleSpinBox_V_K;
    QDoubleSpinBox *doubleSpinBox_V_L;
    QLabel *label_7;
    QDoubleSpinBox *doubleSpinBox_V_Na;
    QFrame *line;
    QFrame *line_2;
    QFrame *line_3;
    QLabel *label_12;
    QLabel *label_13;
    QDoubleSpinBox *doubleSpinBox_sigma;
    QDoubleSpinBox *doubleSpinBox_phi;
    QDoubleSpinBox *doubleSpinBox_taum;
    QLabel *label_11;
    QDoubleSpinBox *doubleSpinBox_rho;
    QDoubleSpinBox *doubleSpinBox_i;
    QDoubleSpinBox *doubleSpinBox_cm;
    QPushButton *pushButton_accept;
    QGroupBox *groupBox_Integration;
    QComboBox *comboBoxIntegration;

    void setupUi(QWidget *NM_GUI_Wang_1993)
    {
        if (NM_GUI_Wang_1993->objectName().isEmpty())
            NM_GUI_Wang_1993->setObjectName(QStringLiteral("NM_GUI_Wang_1993"));
        NM_GUI_Wang_1993->setWindowModality(Qt::ApplicationModal);
        NM_GUI_Wang_1993->resize(522, 440);
        label_8 = new QLabel(NM_GUI_Wang_1993);
        label_8->setObjectName(QStringLiteral("label_8"));
        label_8->setGeometry(QRect(30, 44, 61, 15));
        label_9 = new QLabel(NM_GUI_Wang_1993);
        label_9->setObjectName(QStringLiteral("label_9"));
        label_9->setGeometry(QRect(200, 44, 61, 15));
        label_10 = new QLabel(NM_GUI_Wang_1993);
        label_10->setObjectName(QStringLiteral("label_10"));
        label_10->setGeometry(QRect(340, 44, 61, 15));
        groupBox_InitialValues = new QGroupBox(NM_GUI_Wang_1993);
        groupBox_InitialValues->setObjectName(QStringLiteral("groupBox_InitialValues"));
        groupBox_InitialValues->setGeometry(QRect(20, 370, 131, 61));
        label_14 = new QLabel(groupBox_InitialValues);
        label_14->setObjectName(QStringLiteral("label_14"));
        label_14->setGeometry(QRect(10, 34, 21, 16));
        doubleSpinBox_V = new QDoubleSpinBox(groupBox_InitialValues);
        doubleSpinBox_V->setObjectName(QStringLiteral("doubleSpinBox_V"));
        doubleSpinBox_V->setGeometry(QRect(30, 30, 91, 24));
        doubleSpinBox_V->setDecimals(5);
        doubleSpinBox_V->setMinimum(-999);
        doubleSpinBox_V->setMaximum(999.99);
        doubleSpinBox_V->setSingleStep(0.1);
        doubleSpinBox_V->setValue(-66.5);
        groupBox_Parameters = new QGroupBox(NM_GUI_Wang_1993);
        groupBox_Parameters->setObjectName(QStringLiteral("groupBox_Parameters"));
        groupBox_Parameters->setGeometry(QRect(20, 10, 481, 351));
        groupBox_Channels = new QGroupBox(groupBox_Parameters);
        groupBox_Channels->setObjectName(QStringLiteral("groupBox_Channels"));
        groupBox_Channels->setGeometry(QRect(10, 100, 461, 241));
        label_5 = new QLabel(groupBox_Channels);
        label_5->setObjectName(QStringLiteral("label_5"));
        label_5->setGeometry(QRect(10, 208, 91, 16));
        label_2 = new QLabel(groupBox_Channels);
        label_2->setObjectName(QStringLiteral("label_2"));
        label_2->setGeometry(QRect(10, 97, 161, 16));
        label_3 = new QLabel(groupBox_Channels);
        label_3->setObjectName(QStringLiteral("label_3"));
        label_3->setGeometry(QRect(10, 137, 111, 16));
        label_4 = new QLabel(groupBox_Channels);
        label_4->setObjectName(QStringLiteral("label_4"));
        label_4->setGeometry(QRect(10, 167, 141, 21));
        label = new QLabel(groupBox_Channels);
        label->setObjectName(QStringLiteral("label"));
        label->setGeometry(QRect(10, 67, 111, 16));
        label_6 = new QLabel(groupBox_Channels);
        label_6->setObjectName(QStringLiteral("label_6"));
        label_6->setGeometry(QRect(190, 30, 91, 16));
        doubleSpinBox_g_Na = new QDoubleSpinBox(groupBox_Channels);
        doubleSpinBox_g_Na->setObjectName(QStringLiteral("doubleSpinBox_g_Na"));
        doubleSpinBox_g_Na->setGeometry(QRect(190, 63, 91, 24));
        doubleSpinBox_g_Na->setDecimals(5);
        doubleSpinBox_g_Na->setMinimum(-999);
        doubleSpinBox_g_Na->setMaximum(999.99);
        doubleSpinBox_g_Na->setSingleStep(0.1);
        doubleSpinBox_g_Na->setValue(52);
        doubleSpinBox_g_NaP = new QDoubleSpinBox(groupBox_Channels);
        doubleSpinBox_g_NaP->setObjectName(QStringLiteral("doubleSpinBox_g_NaP"));
        doubleSpinBox_g_NaP->setGeometry(QRect(190, 94, 91, 24));
        doubleSpinBox_g_NaP->setDecimals(5);
        doubleSpinBox_g_NaP->setMinimum(-999);
        doubleSpinBox_g_NaP->setMaximum(999.99);
        doubleSpinBox_g_NaP->setSingleStep(0.1);
        doubleSpinBox_g_NaP->setValue(0.1);
        doubleSpinBox_g_K = new QDoubleSpinBox(groupBox_Channels);
        doubleSpinBox_g_K->setObjectName(QStringLiteral("doubleSpinBox_g_K"));
        doubleSpinBox_g_K->setGeometry(QRect(190, 132, 91, 24));
        doubleSpinBox_g_K->setDecimals(5);
        doubleSpinBox_g_K->setMinimum(-999);
        doubleSpinBox_g_K->setMaximum(999.99);
        doubleSpinBox_g_K->setSingleStep(0.1);
        doubleSpinBox_g_K->setValue(20);
        doubleSpinBox_g_KS = new QDoubleSpinBox(groupBox_Channels);
        doubleSpinBox_g_KS->setObjectName(QStringLiteral("doubleSpinBox_g_KS"));
        doubleSpinBox_g_KS->setGeometry(QRect(190, 163, 91, 24));
        doubleSpinBox_g_KS->setDecimals(5);
        doubleSpinBox_g_KS->setMinimum(-999);
        doubleSpinBox_g_KS->setMaximum(999.99);
        doubleSpinBox_g_KS->setSingleStep(0.1);
        doubleSpinBox_g_KS->setValue(14);
        doubleSpinBox_g_L = new QDoubleSpinBox(groupBox_Channels);
        doubleSpinBox_g_L->setObjectName(QStringLiteral("doubleSpinBox_g_L"));
        doubleSpinBox_g_L->setGeometry(QRect(190, 204, 91, 24));
        doubleSpinBox_g_L->setDecimals(5);
        doubleSpinBox_g_L->setMinimum(-999);
        doubleSpinBox_g_L->setMaximum(999.99);
        doubleSpinBox_g_L->setSingleStep(0.1);
        doubleSpinBox_g_L->setValue(0.1);
        doubleSpinBox_V_K = new QDoubleSpinBox(groupBox_Channels);
        doubleSpinBox_V_K->setObjectName(QStringLiteral("doubleSpinBox_V_K"));
        doubleSpinBox_V_K->setGeometry(QRect(333, 146, 91, 24));
        doubleSpinBox_V_K->setDecimals(5);
        doubleSpinBox_V_K->setMinimum(-999);
        doubleSpinBox_V_K->setMaximum(999.99);
        doubleSpinBox_V_K->setSingleStep(0.1);
        doubleSpinBox_V_K->setValue(-90);
        doubleSpinBox_V_L = new QDoubleSpinBox(groupBox_Channels);
        doubleSpinBox_V_L->setObjectName(QStringLiteral("doubleSpinBox_V_L"));
        doubleSpinBox_V_L->setGeometry(QRect(333, 204, 91, 24));
        doubleSpinBox_V_L->setDecimals(5);
        doubleSpinBox_V_L->setMinimum(-999);
        doubleSpinBox_V_L->setMaximum(999.99);
        doubleSpinBox_V_L->setSingleStep(0.1);
        doubleSpinBox_V_L->setValue(-60);
        label_7 = new QLabel(groupBox_Channels);
        label_7->setObjectName(QStringLiteral("label_7"));
        label_7->setGeometry(QRect(321, 30, 141, 16));
        doubleSpinBox_V_Na = new QDoubleSpinBox(groupBox_Channels);
        doubleSpinBox_V_Na->setObjectName(QStringLiteral("doubleSpinBox_V_Na"));
        doubleSpinBox_V_Na->setGeometry(QRect(333, 78, 91, 24));
        doubleSpinBox_V_Na->setDecimals(5);
        doubleSpinBox_V_Na->setMinimum(-999);
        doubleSpinBox_V_Na->setMaximum(999.99);
        doubleSpinBox_V_Na->setSingleStep(0.1);
        doubleSpinBox_V_Na->setValue(55);
        line = new QFrame(groupBox_Channels);
        line->setObjectName(QStringLiteral("line"));
        line->setGeometry(QRect(10, 117, 431, 16));
        line->setFrameShape(QFrame::HLine);
        line->setFrameShadow(QFrame::Sunken);
        line_2 = new QFrame(groupBox_Channels);
        line_2->setObjectName(QStringLiteral("line_2"));
        line_2->setGeometry(QRect(10, 187, 431, 16));
        line_2->setFrameShape(QFrame::HLine);
        line_2->setFrameShadow(QFrame::Sunken);
        line_3 = new QFrame(groupBox_Channels);
        line_3->setObjectName(QStringLiteral("line_3"));
        line_3->setGeometry(QRect(10, 50, 431, 16));
        line_3->setFrameShape(QFrame::HLine);
        line_3->setFrameShadow(QFrame::Sunken);
        label_12 = new QLabel(groupBox_Parameters);
        label_12->setObjectName(QStringLiteral("label_12"));
        label_12->setGeometry(QRect(10, 67, 61, 15));
        label_13 = new QLabel(groupBox_Parameters);
        label_13->setObjectName(QStringLiteral("label_13"));
        label_13->setGeometry(QRect(180, 68, 61, 15));
        doubleSpinBox_sigma = new QDoubleSpinBox(groupBox_Parameters);
        doubleSpinBox_sigma->setObjectName(QStringLiteral("doubleSpinBox_sigma"));
        doubleSpinBox_sigma->setGeometry(QRect(60, 29, 91, 24));
        doubleSpinBox_sigma->setDecimals(5);
        doubleSpinBox_sigma->setMinimum(-999);
        doubleSpinBox_sigma->setMaximum(999.99);
        doubleSpinBox_sigma->setSingleStep(0.1);
        doubleSpinBox_phi = new QDoubleSpinBox(groupBox_Parameters);
        doubleSpinBox_phi->setObjectName(QStringLiteral("doubleSpinBox_phi"));
        doubleSpinBox_phi->setGeometry(QRect(210, 28, 91, 24));
        doubleSpinBox_phi->setDecimals(5);
        doubleSpinBox_phi->setMinimum(-999);
        doubleSpinBox_phi->setMaximum(999.99);
        doubleSpinBox_phi->setSingleStep(0.1);
        doubleSpinBox_phi->setValue(28.57);
        doubleSpinBox_taum = new QDoubleSpinBox(groupBox_Parameters);
        doubleSpinBox_taum->setObjectName(QStringLiteral("doubleSpinBox_taum"));
        doubleSpinBox_taum->setGeometry(QRect(370, 64, 91, 24));
        doubleSpinBox_taum->setDecimals(5);
        doubleSpinBox_taum->setMinimum(-999);
        doubleSpinBox_taum->setMaximum(999.99);
        doubleSpinBox_taum->setSingleStep(0.1);
        doubleSpinBox_taum->setValue(6);
        label_11 = new QLabel(groupBox_Parameters);
        label_11->setObjectName(QStringLiteral("label_11"));
        label_11->setGeometry(QRect(320, 70, 61, 15));
        doubleSpinBox_rho = new QDoubleSpinBox(groupBox_Parameters);
        doubleSpinBox_rho->setObjectName(QStringLiteral("doubleSpinBox_rho"));
        doubleSpinBox_rho->setGeometry(QRect(370, 30, 91, 24));
        doubleSpinBox_rho->setDecimals(5);
        doubleSpinBox_rho->setMinimum(-999);
        doubleSpinBox_rho->setMaximum(999.99);
        doubleSpinBox_rho->setSingleStep(0.1);
        doubleSpinBox_rho->setValue(0.6);
        doubleSpinBox_i = new QDoubleSpinBox(groupBox_Parameters);
        doubleSpinBox_i->setObjectName(QStringLiteral("doubleSpinBox_i"));
        doubleSpinBox_i->setGeometry(QRect(60, 64, 91, 24));
        doubleSpinBox_i->setDecimals(5);
        doubleSpinBox_i->setMinimum(-999);
        doubleSpinBox_i->setMaximum(999.99);
        doubleSpinBox_i->setSingleStep(0.1);
        doubleSpinBox_i->setValue(2.5);
        doubleSpinBox_cm = new QDoubleSpinBox(groupBox_Parameters);
        doubleSpinBox_cm->setObjectName(QStringLiteral("doubleSpinBox_cm"));
        doubleSpinBox_cm->setGeometry(QRect(210, 64, 91, 24));
        doubleSpinBox_cm->setDecimals(5);
        doubleSpinBox_cm->setMinimum(-999);
        doubleSpinBox_cm->setMaximum(999.99);
        doubleSpinBox_cm->setSingleStep(0.1);
        doubleSpinBox_cm->setValue(1);
        pushButton_accept = new QPushButton(NM_GUI_Wang_1993);
        pushButton_accept->setObjectName(QStringLiteral("pushButton_accept"));
        pushButton_accept->setGeometry(QRect(400, 390, 82, 23));
        groupBox_Integration = new QGroupBox(NM_GUI_Wang_1993);
        groupBox_Integration->setObjectName(QStringLiteral("groupBox_Integration"));
        groupBox_Integration->setGeometry(QRect(170, 370, 181, 61));
        comboBoxIntegration = new QComboBox(groupBox_Integration);
        comboBoxIntegration->setObjectName(QStringLiteral("comboBoxIntegration"));
        comboBoxIntegration->setEnabled(false);
        comboBoxIntegration->setGeometry(QRect(10, 30, 161, 23));
        groupBox_Parameters->raise();
        groupBox_InitialValues->raise();
        label_8->raise();
        label_9->raise();
        label_10->raise();
        pushButton_accept->raise();
        groupBox_Integration->raise();

        retranslateUi(NM_GUI_Wang_1993);

        comboBoxIntegration->setCurrentIndex(3);


        QMetaObject::connectSlotsByName(NM_GUI_Wang_1993);
    } // setupUi

    void retranslateUi(QWidget *NM_GUI_Wang_1993)
    {
        NM_GUI_Wang_1993->setWindowTitle(QApplication::translate("NM_GUI_Wang_1993", "Wang (1993) neuron model", Q_NULLPTR));
        label_8->setText(QApplication::translate("NM_GUI_Wang_1993", "Sigma", Q_NULLPTR));
        label_9->setText(QApplication::translate("NM_GUI_Wang_1993", "Phi", Q_NULLPTR));
        label_10->setText(QApplication::translate("NM_GUI_Wang_1993", "Rho", Q_NULLPTR));
        groupBox_InitialValues->setTitle(QApplication::translate("NM_GUI_Wang_1993", "Initial values", Q_NULLPTR));
        label_14->setText(QApplication::translate("NM_GUI_Wang_1993", "V", Q_NULLPTR));
        groupBox_Parameters->setTitle(QApplication::translate("NM_GUI_Wang_1993", "Parameters", Q_NULLPTR));
        groupBox_Channels->setTitle(QApplication::translate("NM_GUI_Wang_1993", "Ionic channels", Q_NULLPTR));
        label_5->setText(QApplication::translate("NM_GUI_Wang_1993", "Leakage (L)", Q_NULLPTR));
        label_2->setText(QApplication::translate("NM_GUI_Wang_1993", "Persistent sodium (NaP)", Q_NULLPTR));
        label_3->setText(QApplication::translate("NM_GUI_Wang_1993", "Potassium (K)", Q_NULLPTR));
        label_4->setText(QApplication::translate("NM_GUI_Wang_1993", "Slow potassium (KS)", Q_NULLPTR));
        label->setText(QApplication::translate("NM_GUI_Wang_1993", "Sodium (Na)", Q_NULLPTR));
        label_6->setText(QApplication::translate("NM_GUI_Wang_1993", "Conductance", Q_NULLPTR));
        label_7->setText(QApplication::translate("NM_GUI_Wang_1993", "Reversal potential", Q_NULLPTR));
        label_12->setText(QApplication::translate("NM_GUI_Wang_1993", "Iext", Q_NULLPTR));
        label_13->setText(QApplication::translate("NM_GUI_Wang_1993", "Cm", Q_NULLPTR));
        label_11->setText(QApplication::translate("NM_GUI_Wang_1993", "Tau_m", Q_NULLPTR));
        pushButton_accept->setText(QApplication::translate("NM_GUI_Wang_1993", "Accept", Q_NULLPTR));
        groupBox_Integration->setTitle(QApplication::translate("NM_GUI_Wang_1993", "Integration method", Q_NULLPTR));
        comboBoxIntegration->clear();
        comboBoxIntegration->insertItems(0, QStringList()
         << QApplication::translate("NM_GUI_Wang_1993", "Euler", Q_NULLPTR)
         << QApplication::translate("NM_GUI_Wang_1993", "Heun", Q_NULLPTR)
         << QApplication::translate("NM_GUI_Wang_1993", "Runge-Kutta 4", Q_NULLPTR)
         << QApplication::translate("NM_GUI_Wang_1993", "Runge-Kutta (6)5", Q_NULLPTR)
        );
    } // retranslateUi

};

namespace Ui {
    class NM_GUI_Wang_1993: public Ui_NM_GUI_Wang_1993 {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_NM_GUI_WANG_1993_H
