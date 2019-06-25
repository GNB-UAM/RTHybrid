/********************************************************************************
** Form generated from reading UI file 'sm_gui_electrical.ui'
**
** Created by: Qt User Interface Compiler version 5.7.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SM_GUI_ELECTRICAL_H
#define UI_SM_GUI_ELECTRICAL_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QDialog>
#include <QtWidgets/QDoubleSpinBox>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>

QT_BEGIN_NAMESPACE

class Ui_SM_GUI_Electrical
{
public:
    QDoubleSpinBox *double_g;
    QLabel *label_27;
    QCheckBox *checkAnti;
    QPushButton *pushButton_accept;

    void setupUi(QDialog *SM_GUI_Electrical)
    {
        if (SM_GUI_Electrical->objectName().isEmpty())
            SM_GUI_Electrical->setObjectName(QStringLiteral("SM_GUI_Electrical"));
        SM_GUI_Electrical->setWindowModality(Qt::NonModal);
        SM_GUI_Electrical->resize(358, 96);
        double_g = new QDoubleSpinBox(SM_GUI_Electrical);
        double_g->setObjectName(QStringLiteral("double_g"));
        double_g->setGeometry(QRect(120, 20, 91, 24));
        double_g->setDecimals(4);
        double_g->setSingleStep(0.05);
        double_g->setValue(0.2);
        label_27 = new QLabel(SM_GUI_Electrical);
        label_27->setObjectName(QStringLiteral("label_27"));
        label_27->setGeometry(QRect(50, 21, 61, 21));
        checkAnti = new QCheckBox(SM_GUI_Electrical);
        checkAnti->setObjectName(QStringLiteral("checkAnti"));
        checkAnti->setGeometry(QRect(247, 22, 88, 21));
        checkAnti->setChecked(true);
        pushButton_accept = new QPushButton(SM_GUI_Electrical);
        pushButton_accept->setObjectName(QStringLiteral("pushButton_accept"));
        pushButton_accept->setGeometry(QRect(140, 60, 82, 23));

        retranslateUi(SM_GUI_Electrical);

        QMetaObject::connectSlotsByName(SM_GUI_Electrical);
    } // setupUi

    void retranslateUi(QDialog *SM_GUI_Electrical)
    {
        SM_GUI_Electrical->setWindowTitle(QApplication::translate("SM_GUI_Electrical", "Electrical synapse parameters", Q_NULLPTR));
        label_27->setText(QApplication::translate("SM_GUI_Electrical", "g (in uS):", Q_NULLPTR));
        checkAnti->setText(QApplication::translate("SM_GUI_Electrical", "Antiphase", Q_NULLPTR));
        pushButton_accept->setText(QApplication::translate("SM_GUI_Electrical", "Accept", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class SM_GUI_Electrical: public Ui_SM_GUI_Electrical {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SM_GUI_ELECTRICAL_H
