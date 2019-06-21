/********************************************************************************
** Form generated from reading UI file 'nm_gui_hindmarsh_rose_1986.ui'
**
** Created by: Qt User Interface Compiler version 5.7.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_NM_GUI_HINDMARSH_ROSE_1986_H
#define UI_NM_GUI_HINDMARSH_ROSE_1986_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QDoubleSpinBox>
#include <QtWidgets/QFrame>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_NM_GUI_Hindmarsh_Rose_1986
{
public:
    QLabel *label_9;
    QDoubleSpinBox *doubleI;
    QDoubleSpinBox *doubleY;
    QLabel *label_18;
    QLabel *label_17;
    QDoubleSpinBox *doubleS;
    QLabel *label_20;
    QDoubleSpinBox *doubleX;
    QLabel *label_21;
    QLabel *label_19;
    QDoubleSpinBox *doubleZ;
    QDoubleSpinBox *doubleR;
    QLabel *label;
    QLabel *label_2;
    QFrame *line;
    QFrame *line_2;
    QComboBox *comboBoxIntegration;
    QPushButton *pushButton_accept;
    QLabel *label_3;

    void setupUi(QWidget *NM_GUI_Hindmarsh_Rose_1986)
    {
        if (NM_GUI_Hindmarsh_Rose_1986->objectName().isEmpty())
            NM_GUI_Hindmarsh_Rose_1986->setObjectName(QStringLiteral("NM_GUI_Hindmarsh_Rose_1986"));
        NM_GUI_Hindmarsh_Rose_1986->setWindowModality(Qt::ApplicationModal);
        NM_GUI_Hindmarsh_Rose_1986->resize(554, 144);
        label_9 = new QLabel(NM_GUI_Hindmarsh_Rose_1986);
        label_9->setObjectName(QStringLiteral("label_9"));
        label_9->setGeometry(QRect(40, 40, 21, 21));
        doubleI = new QDoubleSpinBox(NM_GUI_Hindmarsh_Rose_1986);
        doubleI->setObjectName(QStringLiteral("doubleI"));
        doubleI->setGeometry(QRect(60, 100, 101, 24));
        doubleI->setDecimals(2);
        doubleI->setMinimum(-99.99);
        doubleI->setSingleStep(0.1);
        doubleI->setValue(3);
        doubleY = new QDoubleSpinBox(NM_GUI_Hindmarsh_Rose_1986);
        doubleY->setObjectName(QStringLiteral("doubleY"));
        doubleY->setGeometry(QRect(220, 70, 101, 24));
        doubleY->setDecimals(6);
        doubleY->setMinimum(-99.99);
        doubleY->setSingleStep(0.1);
        doubleY->setValue(-1.93688);
        label_18 = new QLabel(NM_GUI_Hindmarsh_Rose_1986);
        label_18->setObjectName(QStringLiteral("label_18"));
        label_18->setGeometry(QRect(40, 70, 21, 21));
        label_17 = new QLabel(NM_GUI_Hindmarsh_Rose_1986);
        label_17->setObjectName(QStringLiteral("label_17"));
        label_17->setGeometry(QRect(200, 70, 31, 16));
        doubleS = new QDoubleSpinBox(NM_GUI_Hindmarsh_Rose_1986);
        doubleS->setObjectName(QStringLiteral("doubleS"));
        doubleS->setGeometry(QRect(60, 70, 101, 24));
        doubleS->setDecimals(2);
        doubleS->setMinimum(-99.99);
        doubleS->setSingleStep(0.1);
        doubleS->setValue(4);
        label_20 = new QLabel(NM_GUI_Hindmarsh_Rose_1986);
        label_20->setObjectName(QStringLiteral("label_20"));
        label_20->setGeometry(QRect(200, 40, 31, 21));
        doubleX = new QDoubleSpinBox(NM_GUI_Hindmarsh_Rose_1986);
        doubleX->setObjectName(QStringLiteral("doubleX"));
        doubleX->setGeometry(QRect(220, 40, 101, 24));
        doubleX->setDecimals(6);
        doubleX->setMinimum(-99.99);
        doubleX->setSingleStep(0.1);
        doubleX->setValue(-0.712841);
        label_21 = new QLabel(NM_GUI_Hindmarsh_Rose_1986);
        label_21->setObjectName(QStringLiteral("label_21"));
        label_21->setGeometry(QRect(200, 100, 31, 16));
        label_19 = new QLabel(NM_GUI_Hindmarsh_Rose_1986);
        label_19->setObjectName(QStringLiteral("label_19"));
        label_19->setGeometry(QRect(40, 100, 21, 21));
        doubleZ = new QDoubleSpinBox(NM_GUI_Hindmarsh_Rose_1986);
        doubleZ->setObjectName(QStringLiteral("doubleZ"));
        doubleZ->setGeometry(QRect(220, 100, 101, 24));
        doubleZ->setDecimals(6);
        doubleZ->setMinimum(-99.99);
        doubleZ->setSingleStep(0.1);
        doubleZ->setValue(3.16568);
        doubleR = new QDoubleSpinBox(NM_GUI_Hindmarsh_Rose_1986);
        doubleR->setObjectName(QStringLiteral("doubleR"));
        doubleR->setGeometry(QRect(60, 40, 101, 24));
        doubleR->setDecimals(6);
        doubleR->setMinimum(-99.99);
        doubleR->setSingleStep(0.0001);
        doubleR->setValue(0.0021);
        label = new QLabel(NM_GUI_Hindmarsh_Rose_1986);
        label->setObjectName(QStringLiteral("label"));
        label->setGeometry(QRect(68, 14, 91, 16));
        label_2 = new QLabel(NM_GUI_Hindmarsh_Rose_1986);
        label_2->setObjectName(QStringLiteral("label_2"));
        label_2->setGeometry(QRect(228, 14, 101, 16));
        line = new QFrame(NM_GUI_Hindmarsh_Rose_1986);
        line->setObjectName(QStringLiteral("line"));
        line->setGeometry(QRect(170, 34, 20, 91));
        line->setFrameShape(QFrame::VLine);
        line->setFrameShadow(QFrame::Sunken);
        line_2 = new QFrame(NM_GUI_Hindmarsh_Rose_1986);
        line_2->setObjectName(QStringLiteral("line_2"));
        line_2->setGeometry(QRect(330, 34, 20, 91));
        line_2->setFrameShape(QFrame::VLine);
        line_2->setFrameShadow(QFrame::Sunken);
        comboBoxIntegration = new QComboBox(NM_GUI_Hindmarsh_Rose_1986);
        comboBoxIntegration->setObjectName(QStringLiteral("comboBoxIntegration"));
        comboBoxIntegration->setEnabled(false);
        comboBoxIntegration->setGeometry(QRect(380, 44, 141, 23));
        pushButton_accept = new QPushButton(NM_GUI_Hindmarsh_Rose_1986);
        pushButton_accept->setObjectName(QStringLiteral("pushButton_accept"));
        pushButton_accept->setGeometry(QRect(408, 100, 82, 23));
        label_3 = new QLabel(NM_GUI_Hindmarsh_Rose_1986);
        label_3->setObjectName(QStringLiteral("label_3"));
        label_3->setGeometry(QRect(389, 14, 141, 16));

        retranslateUi(NM_GUI_Hindmarsh_Rose_1986);

        comboBoxIntegration->setCurrentIndex(3);


        QMetaObject::connectSlotsByName(NM_GUI_Hindmarsh_Rose_1986);
    } // setupUi

    void retranslateUi(QWidget *NM_GUI_Hindmarsh_Rose_1986)
    {
        NM_GUI_Hindmarsh_Rose_1986->setWindowTitle(QApplication::translate("NM_GUI_Hindmarsh_Rose_1986", "Hindmarsh-Rose (1986) neuron model", Q_NULLPTR));
        label_9->setText(QApplication::translate("NM_GUI_Hindmarsh_Rose_1986", "R", Q_NULLPTR));
        label_18->setText(QApplication::translate("NM_GUI_Hindmarsh_Rose_1986", "S", Q_NULLPTR));
        label_17->setText(QApplication::translate("NM_GUI_Hindmarsh_Rose_1986", "Y", Q_NULLPTR));
        label_20->setText(QApplication::translate("NM_GUI_Hindmarsh_Rose_1986", "X", Q_NULLPTR));
        label_21->setText(QApplication::translate("NM_GUI_Hindmarsh_Rose_1986", "Z", Q_NULLPTR));
        label_19->setText(QApplication::translate("NM_GUI_Hindmarsh_Rose_1986", "I", Q_NULLPTR));
        label->setText(QApplication::translate("NM_GUI_Hindmarsh_Rose_1986", "Parameters", Q_NULLPTR));
        label_2->setText(QApplication::translate("NM_GUI_Hindmarsh_Rose_1986", "Initial values", Q_NULLPTR));
        comboBoxIntegration->clear();
        comboBoxIntegration->insertItems(0, QStringList()
         << QApplication::translate("NM_GUI_Hindmarsh_Rose_1986", "Euler", Q_NULLPTR)
         << QApplication::translate("NM_GUI_Hindmarsh_Rose_1986", "Heun", Q_NULLPTR)
         << QApplication::translate("NM_GUI_Hindmarsh_Rose_1986", "Runge-Kutta 4", Q_NULLPTR)
         << QApplication::translate("NM_GUI_Hindmarsh_Rose_1986", "Runge-Kutta (6)5", Q_NULLPTR)
        );
        pushButton_accept->setText(QApplication::translate("NM_GUI_Hindmarsh_Rose_1986", "Accept", Q_NULLPTR));
        label_3->setText(QApplication::translate("NM_GUI_Hindmarsh_Rose_1986", "Integration method", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class NM_GUI_Hindmarsh_Rose_1986: public Ui_NM_GUI_Hindmarsh_Rose_1986 {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_NM_GUI_HINDMARSH_ROSE_1986_H
