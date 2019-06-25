/********************************************************************************
** Form generated from reading UI file 'nm_gui_bluetooth.ui'
**
** Created by: Qt User Interface Compiler version 5.7.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_NM_GUI_BLUETOOTH_H
#define UI_NM_GUI_BLUETOOTH_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_NM_GUI_Bluetooth
{
public:
    QPushButton *pushButton_accept;

    void setupUi(QWidget *NM_GUI_Bluetooth)
    {
        if (NM_GUI_Bluetooth->objectName().isEmpty())
            NM_GUI_Bluetooth->setObjectName(QStringLiteral("NM_GUI_Bluetooth"));
        NM_GUI_Bluetooth->setWindowModality(Qt::ApplicationModal);
        NM_GUI_Bluetooth->resize(511, 152);
        pushButton_accept = new QPushButton(NM_GUI_Bluetooth);
        pushButton_accept->setObjectName(QStringLiteral("pushButton_accept"));
        pushButton_accept->setGeometry(QRect(406, 70, 82, 23));

        retranslateUi(NM_GUI_Bluetooth);

        QMetaObject::connectSlotsByName(NM_GUI_Bluetooth);
    } // setupUi

    void retranslateUi(QWidget *NM_GUI_Bluetooth)
    {
        NM_GUI_Bluetooth->setWindowTitle(QApplication::translate("NM_GUI_Bluetooth", "Rulkov (2002) neuron model", Q_NULLPTR));
        pushButton_accept->setText(QApplication::translate("NM_GUI_Bluetooth", "Accept", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class NM_GUI_Bluetooth: public Ui_NM_GUI_Bluetooth {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_NM_GUI_BLUETOOTH_H
