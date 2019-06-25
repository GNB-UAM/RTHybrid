/********************************************************************************
** Form generated from reading UI file 'nm_gui_rulkov_2002.ui'
**
** Created by: Qt User Interface Compiler version 5.7.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_NM_GUI_RULKOV_2002_H
#define UI_NM_GUI_RULKOV_2002_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QDoubleSpinBox>
#include <QtWidgets/QFrame>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_NM_GUI_Rulkov_2002
{
public:
    QDoubleSpinBox *doubleRlkMu;
    QLabel *label_10;
    QDoubleSpinBox *doubleRlkI;
    QDoubleSpinBox *doubleRlkYIni;
    QLabel *label_26;
    QDoubleSpinBox *doubleRlkXIni;
    QLabel *label_24;
    QLabel *label_23;
    QLabel *label_25;
    QLabel *label_22;
    QDoubleSpinBox *doubleRlkSigma;
    QDoubleSpinBox *doubleRlkAlpha;
    QFrame *line;
    QLabel *label;
    QLabel *label_2;
    QFrame *line_2;
    QPushButton *pushButton_accept;

    void setupUi(QWidget *NM_GUI_Rulkov_2002)
    {
        if (NM_GUI_Rulkov_2002->objectName().isEmpty())
            NM_GUI_Rulkov_2002->setObjectName(QStringLiteral("NM_GUI_Rulkov_2002"));
        NM_GUI_Rulkov_2002->setWindowModality(Qt::ApplicationModal);
        NM_GUI_Rulkov_2002->resize(511, 152);
        doubleRlkMu = new QDoubleSpinBox(NM_GUI_Rulkov_2002);
        doubleRlkMu->setObjectName(QStringLiteral("doubleRlkMu"));
        doubleRlkMu->setGeometry(QRect(90, 90, 101, 24));
        doubleRlkMu->setDecimals(4);
        doubleRlkMu->setMinimum(-99.99);
        doubleRlkMu->setSingleStep(0.001);
        doubleRlkMu->setValue(0.001);
        label_10 = new QLabel(NM_GUI_Rulkov_2002);
        label_10->setObjectName(QStringLiteral("label_10"));
        label_10->setGeometry(QRect(33, 31, 41, 21));
        doubleRlkI = new QDoubleSpinBox(NM_GUI_Rulkov_2002);
        doubleRlkI->setObjectName(QStringLiteral("doubleRlkI"));
        doubleRlkI->setGeometry(QRect(90, 120, 101, 24));
        doubleRlkI->setMinimum(-99.99);
        doubleRlkI->setValue(1);
        doubleRlkYIni = new QDoubleSpinBox(NM_GUI_Rulkov_2002);
        doubleRlkYIni->setObjectName(QStringLiteral("doubleRlkYIni"));
        doubleRlkYIni->setGeometry(QRect(258, 86, 101, 24));
        doubleRlkYIni->setDecimals(6);
        doubleRlkYIni->setMinimum(-99.99);
        doubleRlkYIni->setSingleStep(0.01);
        doubleRlkYIni->setValue(-4.91923);
        label_26 = new QLabel(NM_GUI_Rulkov_2002);
        label_26->setObjectName(QStringLiteral("label_26"));
        label_26->setGeometry(QRect(42, 92, 21, 21));
        doubleRlkXIni = new QDoubleSpinBox(NM_GUI_Rulkov_2002);
        doubleRlkXIni->setObjectName(QStringLiteral("doubleRlkXIni"));
        doubleRlkXIni->setGeometry(QRect(258, 56, 101, 24));
        doubleRlkXIni->setDecimals(6);
        doubleRlkXIni->setMinimum(-99.99);
        doubleRlkXIni->setSingleStep(0.01);
        doubleRlkXIni->setValue(-1.70175);
        label_24 = new QLabel(NM_GUI_Rulkov_2002);
        label_24->setObjectName(QStringLiteral("label_24"));
        label_24->setGeometry(QRect(41, 124, 21, 16));
        label_23 = new QLabel(NM_GUI_Rulkov_2002);
        label_23->setObjectName(QStringLiteral("label_23"));
        label_23->setGeometry(QRect(31, 60, 41, 21));
        label_25 = new QLabel(NM_GUI_Rulkov_2002);
        label_25->setObjectName(QStringLiteral("label_25"));
        label_25->setGeometry(QRect(230, 56, 31, 16));
        label_22 = new QLabel(NM_GUI_Rulkov_2002);
        label_22->setObjectName(QStringLiteral("label_22"));
        label_22->setGeometry(QRect(230, 90, 31, 16));
        doubleRlkSigma = new QDoubleSpinBox(NM_GUI_Rulkov_2002);
        doubleRlkSigma->setObjectName(QStringLiteral("doubleRlkSigma"));
        doubleRlkSigma->setGeometry(QRect(90, 60, 101, 24));
        doubleRlkSigma->setMinimum(-99.99);
        doubleRlkSigma->setSingleStep(0.1);
        doubleRlkSigma->setValue(0.1);
        doubleRlkAlpha = new QDoubleSpinBox(NM_GUI_Rulkov_2002);
        doubleRlkAlpha->setObjectName(QStringLiteral("doubleRlkAlpha"));
        doubleRlkAlpha->setGeometry(QRect(90, 30, 101, 24));
        doubleRlkAlpha->setMinimum(-99.99);
        doubleRlkAlpha->setValue(6);
        line = new QFrame(NM_GUI_Rulkov_2002);
        line->setObjectName(QStringLiteral("line"));
        line->setGeometry(QRect(200, 24, 20, 121));
        line->setFrameShape(QFrame::VLine);
        line->setFrameShadow(QFrame::Sunken);
        label = new QLabel(NM_GUI_Rulkov_2002);
        label->setObjectName(QStringLiteral("label"));
        label->setGeometry(QRect(72, 6, 81, 16));
        label_2 = new QLabel(NM_GUI_Rulkov_2002);
        label_2->setObjectName(QStringLiteral("label_2"));
        label_2->setGeometry(QRect(261, 6, 121, 16));
        line_2 = new QFrame(NM_GUI_Rulkov_2002);
        line_2->setObjectName(QStringLiteral("line_2"));
        line_2->setGeometry(QRect(370, 23, 20, 121));
        line_2->setFrameShape(QFrame::VLine);
        line_2->setFrameShadow(QFrame::Sunken);
        pushButton_accept = new QPushButton(NM_GUI_Rulkov_2002);
        pushButton_accept->setObjectName(QStringLiteral("pushButton_accept"));
        pushButton_accept->setGeometry(QRect(406, 70, 82, 23));

        retranslateUi(NM_GUI_Rulkov_2002);

        QMetaObject::connectSlotsByName(NM_GUI_Rulkov_2002);
    } // setupUi

    void retranslateUi(QWidget *NM_GUI_Rulkov_2002)
    {
        NM_GUI_Rulkov_2002->setWindowTitle(QApplication::translate("NM_GUI_Rulkov_2002", "Rulkov (2002) neuron model", Q_NULLPTR));
        label_10->setText(QApplication::translate("NM_GUI_Rulkov_2002", "Alpha", Q_NULLPTR));
        label_26->setText(QApplication::translate("NM_GUI_Rulkov_2002", "Mu", Q_NULLPTR));
        label_24->setText(QApplication::translate("NM_GUI_Rulkov_2002", "Iext", Q_NULLPTR));
        label_23->setText(QApplication::translate("NM_GUI_Rulkov_2002", "Sigma", Q_NULLPTR));
        label_25->setText(QApplication::translate("NM_GUI_Rulkov_2002", "X", Q_NULLPTR));
        label_22->setText(QApplication::translate("NM_GUI_Rulkov_2002", "Y", Q_NULLPTR));
        label->setText(QApplication::translate("NM_GUI_Rulkov_2002", "Parameters", Q_NULLPTR));
        label_2->setText(QApplication::translate("NM_GUI_Rulkov_2002", "Initial values", Q_NULLPTR));
        pushButton_accept->setText(QApplication::translate("NM_GUI_Rulkov_2002", "Accept", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class NM_GUI_Rulkov_2002: public Ui_NM_GUI_Rulkov_2002 {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_NM_GUI_RULKOV_2002_H
