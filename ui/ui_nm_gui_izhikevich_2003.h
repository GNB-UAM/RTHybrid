/********************************************************************************
** Form generated from reading UI file 'nm_gui_izhikevich_2003.ui'
**
** Created by: Qt User Interface Compiler version 5.7.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_NM_GUI_IZHIKEVICH_2003_H
#define UI_NM_GUI_IZHIKEVICH_2003_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QDoubleSpinBox>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_NM_GUI_Izhikevich_2003
{
public:
    QLabel *label;
    QLabel *label_2;
    QLabel *label_3;
    QLabel *label_4;
    QLabel *label_5;
    QLabel *label_6;
    QLabel *label_7;
    QLabel *label_8;
    QLabel *label_9;
    QDoubleSpinBox *doubleIzA;
    QDoubleSpinBox *doubleIzB;
    QDoubleSpinBox *doubleIzC;
    QDoubleSpinBox *doubleIzD;
    QDoubleSpinBox *doubleIzVIni;
    QDoubleSpinBox *doubleIzUIni;
    QComboBox *comboBoxIntegration;
    QPushButton *pushButton_accept;
    QDoubleSpinBox *doubleIzI;
    QLabel *label_10;

    void setupUi(QWidget *NM_GUI_Izhikevich_2003)
    {
        if (NM_GUI_Izhikevich_2003->objectName().isEmpty())
            NM_GUI_Izhikevich_2003->setObjectName(QStringLiteral("NM_GUI_Izhikevich_2003"));
        NM_GUI_Izhikevich_2003->setWindowModality(Qt::ApplicationModal);
        NM_GUI_Izhikevich_2003->resize(699, 211);
        label = new QLabel(NM_GUI_Izhikevich_2003);
        label->setObjectName(QStringLiteral("label"));
        label->setGeometry(QRect(30, 20, 81, 16));
        label_2 = new QLabel(NM_GUI_Izhikevich_2003);
        label_2->setObjectName(QStringLiteral("label_2"));
        label_2->setGeometry(QRect(280, 20, 91, 16));
        label_3 = new QLabel(NM_GUI_Izhikevich_2003);
        label_3->setObjectName(QStringLiteral("label_3"));
        label_3->setGeometry(QRect(500, 20, 141, 16));
        label_4 = new QLabel(NM_GUI_Izhikevich_2003);
        label_4->setObjectName(QStringLiteral("label_4"));
        label_4->setGeometry(QRect(30, 60, 61, 15));
        label_5 = new QLabel(NM_GUI_Izhikevich_2003);
        label_5->setObjectName(QStringLiteral("label_5"));
        label_5->setGeometry(QRect(30, 90, 61, 15));
        label_6 = new QLabel(NM_GUI_Izhikevich_2003);
        label_6->setObjectName(QStringLiteral("label_6"));
        label_6->setGeometry(QRect(30, 120, 61, 15));
        label_7 = new QLabel(NM_GUI_Izhikevich_2003);
        label_7->setObjectName(QStringLiteral("label_7"));
        label_7->setGeometry(QRect(30, 150, 61, 15));
        label_8 = new QLabel(NM_GUI_Izhikevich_2003);
        label_8->setObjectName(QStringLiteral("label_8"));
        label_8->setGeometry(QRect(240, 60, 61, 15));
        label_9 = new QLabel(NM_GUI_Izhikevich_2003);
        label_9->setObjectName(QStringLiteral("label_9"));
        label_9->setGeometry(QRect(240, 100, 61, 15));
        doubleIzA = new QDoubleSpinBox(NM_GUI_Izhikevich_2003);
        doubleIzA->setObjectName(QStringLiteral("doubleIzA"));
        doubleIzA->setGeometry(QRect(50, 50, 101, 24));
        doubleIzA->setDecimals(5);
        doubleIzA->setMinimum(-99);
        doubleIzA->setSingleStep(0.01);
        doubleIzA->setValue(0.02);
        doubleIzB = new QDoubleSpinBox(NM_GUI_Izhikevich_2003);
        doubleIzB->setObjectName(QStringLiteral("doubleIzB"));
        doubleIzB->setGeometry(QRect(50, 80, 101, 24));
        doubleIzB->setDecimals(5);
        doubleIzB->setMinimum(-99);
        doubleIzB->setSingleStep(0.01);
        doubleIzB->setValue(0.2);
        doubleIzC = new QDoubleSpinBox(NM_GUI_Izhikevich_2003);
        doubleIzC->setObjectName(QStringLiteral("doubleIzC"));
        doubleIzC->setGeometry(QRect(50, 110, 101, 24));
        doubleIzC->setDecimals(5);
        doubleIzC->setMinimum(-99);
        doubleIzC->setSingleStep(0.01);
        doubleIzC->setValue(-50);
        doubleIzD = new QDoubleSpinBox(NM_GUI_Izhikevich_2003);
        doubleIzD->setObjectName(QStringLiteral("doubleIzD"));
        doubleIzD->setGeometry(QRect(50, 140, 101, 24));
        doubleIzD->setDecimals(5);
        doubleIzD->setMinimum(-99);
        doubleIzD->setSingleStep(0.01);
        doubleIzD->setValue(2);
        doubleIzVIni = new QDoubleSpinBox(NM_GUI_Izhikevich_2003);
        doubleIzVIni->setObjectName(QStringLiteral("doubleIzVIni"));
        doubleIzVIni->setGeometry(QRect(270, 50, 101, 24));
        doubleIzVIni->setDecimals(5);
        doubleIzVIni->setMinimum(-99);
        doubleIzVIni->setSingleStep(0.01);
        doubleIzVIni->setValue(30.2403);
        doubleIzUIni = new QDoubleSpinBox(NM_GUI_Izhikevich_2003);
        doubleIzUIni->setObjectName(QStringLiteral("doubleIzUIni"));
        doubleIzUIni->setGeometry(QRect(270, 100, 101, 24));
        doubleIzUIni->setDecimals(5);
        doubleIzUIni->setMinimum(-99);
        doubleIzUIni->setSingleStep(0.01);
        doubleIzUIni->setValue(-5.54459);
        comboBoxIntegration = new QComboBox(NM_GUI_Izhikevich_2003);
        comboBoxIntegration->setObjectName(QStringLiteral("comboBoxIntegration"));
        comboBoxIntegration->setGeometry(QRect(490, 50, 141, 23));
        pushButton_accept = new QPushButton(NM_GUI_Izhikevich_2003);
        pushButton_accept->setObjectName(QStringLiteral("pushButton_accept"));
        pushButton_accept->setGeometry(QRect(520, 140, 82, 23));
        doubleIzI = new QDoubleSpinBox(NM_GUI_Izhikevich_2003);
        doubleIzI->setObjectName(QStringLiteral("doubleIzI"));
        doubleIzI->setGeometry(QRect(50, 170, 101, 24));
        doubleIzI->setDecimals(5);
        doubleIzI->setMinimum(-99);
        doubleIzI->setSingleStep(0.01);
        doubleIzI->setValue(10);
        label_10 = new QLabel(NM_GUI_Izhikevich_2003);
        label_10->setObjectName(QStringLiteral("label_10"));
        label_10->setGeometry(QRect(33, 178, 61, 15));

        retranslateUi(NM_GUI_Izhikevich_2003);

        comboBoxIntegration->setCurrentIndex(3);


        QMetaObject::connectSlotsByName(NM_GUI_Izhikevich_2003);
    } // setupUi

    void retranslateUi(QWidget *NM_GUI_Izhikevich_2003)
    {
        NM_GUI_Izhikevich_2003->setWindowTitle(QApplication::translate("NM_GUI_Izhikevich_2003", "Izhikevich (2003) neuron model", Q_NULLPTR));
        label->setText(QApplication::translate("NM_GUI_Izhikevich_2003", "Parameters", Q_NULLPTR));
        label_2->setText(QApplication::translate("NM_GUI_Izhikevich_2003", "Initial values", Q_NULLPTR));
        label_3->setText(QApplication::translate("NM_GUI_Izhikevich_2003", "Integration method", Q_NULLPTR));
        label_4->setText(QApplication::translate("NM_GUI_Izhikevich_2003", "A", Q_NULLPTR));
        label_5->setText(QApplication::translate("NM_GUI_Izhikevich_2003", "B", Q_NULLPTR));
        label_6->setText(QApplication::translate("NM_GUI_Izhikevich_2003", "C", Q_NULLPTR));
        label_7->setText(QApplication::translate("NM_GUI_Izhikevich_2003", "D", Q_NULLPTR));
        label_8->setText(QApplication::translate("NM_GUI_Izhikevich_2003", "V", Q_NULLPTR));
        label_9->setText(QApplication::translate("NM_GUI_Izhikevich_2003", "U", Q_NULLPTR));
        comboBoxIntegration->clear();
        comboBoxIntegration->insertItems(0, QStringList()
         << QApplication::translate("NM_GUI_Izhikevich_2003", "Euler", Q_NULLPTR)
         << QApplication::translate("NM_GUI_Izhikevich_2003", "Heun", Q_NULLPTR)
         << QApplication::translate("NM_GUI_Izhikevich_2003", "Runge-Kutta 4", Q_NULLPTR)
         << QApplication::translate("NM_GUI_Izhikevich_2003", "Runge-Kutta (6)5", Q_NULLPTR)
        );
        pushButton_accept->setText(QApplication::translate("NM_GUI_Izhikevich_2003", "Accept", Q_NULLPTR));
        label_10->setText(QApplication::translate("NM_GUI_Izhikevich_2003", "I", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class NM_GUI_Izhikevich_2003: public Ui_NM_GUI_Izhikevich_2003 {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_NM_GUI_IZHIKEVICH_2003_H
