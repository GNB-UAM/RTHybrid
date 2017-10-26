/********************************************************************************
** Form generated from reading UI file 'rtbiomanager.ui'
**
** Created by: Qt User Interface Compiler version 5.7.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_RTBIOMANAGER_H
#define UI_RTBIOMANAGER_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QDoubleSpinBox>
#include <QtWidgets/QFrame>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QPlainTextEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStackedWidget>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_RTBiomanager
{
public:
    QWidget *centralWidget;
    QPushButton *simulate;
    QFrame *frameSynapse;
    QStackedWidget *synapseModelPages;
    QWidget *pageSynElec;
    QLabel *label_27;
    QPlainTextEdit *textSynElec_gMtoE;
    QLabel *label_28;
    QPlainTextEdit *textSynElec_gEtoM;
    QWidget *pageSynGrad;
    QLabel *label_29;
    QPlainTextEdit *textSynGrad_gMtoE_slow;
    QPlainTextEdit *textSynGrad_gMtoE_fast;
    QLabel *label_31;
    QPlainTextEdit *textSynGrad_gEtoM_slow;
    QPlainTextEdit *textSynGrad_gEtoM_fast;
    QLabel *label_30;
    QLabel *label_32;
    QLabel *label_33;
    QLabel *label_34;
    QFrame *line;
    QLabel *label;
    QPlainTextEdit *textFreq;
    QPlainTextEdit *textTime;
    QLabel *label_2;
    QCheckBox *checkImp;
    QCheckBox *checkAnti;
    QLabel *label_3;
    QLabel *label_4;
    QLabel *label_5;
    QPlainTextEdit *textChannelInput;
    QPlainTextEdit *textChannelOutput;
    QLabel *label_6;
    QComboBox *neuronModelCombo;
    QLabel *label_7;
    QComboBox *synapseModelCombo;
    QFrame *frameNeuron;
    QStackedWidget *neuronModelPages;
    QWidget *pageIz;
    QPlainTextEdit *textIzA;
    QPlainTextEdit *textIzB;
    QPlainTextEdit *textIzC;
    QPlainTextEdit *textIzD;
    QPlainTextEdit *textIzI;
    QPlainTextEdit *textIzUIni;
    QPlainTextEdit *textIzVIni;
    QLabel *label_8;
    QLabel *label_11;
    QLabel *label_12;
    QLabel *label_13;
    QLabel *label_14;
    QLabel *label_15;
    QLabel *label_16;
    QWidget *pageHr;
    QLabel *label_20;
    QPlainTextEdit *textHrYIni;
    QPlainTextEdit *textHrI;
    QLabel *label_19;
    QLabel *label_18;
    QPlainTextEdit *textHrXIni;
    QLabel *label_9;
    QPlainTextEdit *textHrR;
    QPlainTextEdit *textHrS;
    QLabel *label_17;
    QLabel *label_21;
    QPlainTextEdit *textHrZIni;
    QWidget *pageRlk;
    QLabel *label_25;
    QPlainTextEdit *textRlkI;
    QPlainTextEdit *textRlkXIni;
    QPlainTextEdit *textRlkAlpha;
    QPlainTextEdit *textRlkSigma;
    QLabel *label_24;
    QLabel *label_10;
    QLabel *label_22;
    QLabel *label_23;
    QPlainTextEdit *textRlkYIni;
    QPlainTextEdit *textRlkMu;
    QLabel *label_26;
    QLabel *label_43;
    QComboBox *autocalCombo;
    QFrame *frameAutocal;
    QStackedWidget *autocalPages;
    QWidget *pageOff;
    QWidget *pageElectricalConductanceMSE;
    QPlainTextEdit *plainTextEdit;
    QWidget *pageGradualMap;
    QLabel *label_69;
    QComboBox *gradualModelToExternalSelect;
    QComboBox *gradualExternalToModelSelect;
    QLabel *label_70;
    QLabel *label_71;
    QLabel *label_72;
    QLabel *label_73;
    QDoubleSpinBox *chemMap_MaxToExternal;
    QDoubleSpinBox *chemMap_MaxToModel;
    QDoubleSpinBox *chemMap_StepToExternal;
    QDoubleSpinBox *chemMap_StepToModel;

    void setupUi(QMainWindow *RTBiomanager)
    {
        if (RTBiomanager->objectName().isEmpty())
            RTBiomanager->setObjectName(QStringLiteral("RTBiomanager"));
        RTBiomanager->resize(1091, 594);
        centralWidget = new QWidget(RTBiomanager);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        simulate = new QPushButton(centralWidget);
        simulate->setObjectName(QStringLiteral("simulate"));
        simulate->setGeometry(QRect(890, 290, 82, 23));
        frameSynapse = new QFrame(centralWidget);
        frameSynapse->setObjectName(QStringLiteral("frameSynapse"));
        frameSynapse->setGeometry(QRect(210, 180, 581, 151));
        frameSynapse->setFrameShape(QFrame::StyledPanel);
        frameSynapse->setFrameShadow(QFrame::Raised);
        synapseModelPages = new QStackedWidget(frameSynapse);
        synapseModelPages->setObjectName(QStringLiteral("synapseModelPages"));
        synapseModelPages->setGeometry(QRect(10, 10, 561, 131));
        pageSynElec = new QWidget();
        pageSynElec->setObjectName(QStringLiteral("pageSynElec"));
        label_27 = new QLabel(pageSynElec);
        label_27->setObjectName(QStringLiteral("label_27"));
        label_27->setGeometry(QRect(1, 2, 261, 16));
        textSynElec_gMtoE = new QPlainTextEdit(pageSynElec);
        textSynElec_gMtoE->setObjectName(QStringLiteral("textSynElec_gMtoE"));
        textSynElec_gMtoE->setGeometry(QRect(260, 0, 104, 21));
        QFont font;
        font.setFamily(QStringLiteral("DejaVu Sans"));
        font.setPointSize(10);
        textSynElec_gMtoE->setFont(font);
        label_28 = new QLabel(pageSynElec);
        label_28->setObjectName(QStringLiteral("label_28"));
        label_28->setGeometry(QRect(0, 32, 261, 16));
        textSynElec_gEtoM = new QPlainTextEdit(pageSynElec);
        textSynElec_gEtoM->setObjectName(QStringLiteral("textSynElec_gEtoM"));
        textSynElec_gEtoM->setGeometry(QRect(260, 30, 104, 21));
        textSynElec_gEtoM->setFont(font);
        synapseModelPages->addWidget(pageSynElec);
        pageSynGrad = new QWidget();
        pageSynGrad->setObjectName(QStringLiteral("pageSynGrad"));
        label_29 = new QLabel(pageSynGrad);
        label_29->setObjectName(QStringLiteral("label_29"));
        label_29->setGeometry(QRect(1, 2, 261, 16));
        textSynGrad_gMtoE_slow = new QPlainTextEdit(pageSynGrad);
        textSynGrad_gMtoE_slow->setObjectName(QStringLiteral("textSynGrad_gMtoE_slow"));
        textSynGrad_gMtoE_slow->setGeometry(QRect(333, 0, 104, 21));
        textSynGrad_gMtoE_slow->setFont(font);
        textSynGrad_gMtoE_fast = new QPlainTextEdit(pageSynGrad);
        textSynGrad_gMtoE_fast->setObjectName(QStringLiteral("textSynGrad_gMtoE_fast"));
        textSynGrad_gMtoE_fast->setGeometry(QRect(333, 30, 104, 21));
        textSynGrad_gMtoE_fast->setFont(font);
        label_31 = new QLabel(pageSynGrad);
        label_31->setObjectName(QStringLiteral("label_31"));
        label_31->setGeometry(QRect(1, 80, 261, 16));
        textSynGrad_gEtoM_slow = new QPlainTextEdit(pageSynGrad);
        textSynGrad_gEtoM_slow->setObjectName(QStringLiteral("textSynGrad_gEtoM_slow"));
        textSynGrad_gEtoM_slow->setGeometry(QRect(333, 78, 104, 21));
        textSynGrad_gEtoM_slow->setFont(font);
        textSynGrad_gEtoM_fast = new QPlainTextEdit(pageSynGrad);
        textSynGrad_gEtoM_fast->setObjectName(QStringLiteral("textSynGrad_gEtoM_fast"));
        textSynGrad_gEtoM_fast->setGeometry(QRect(333, 108, 104, 21));
        textSynGrad_gEtoM_fast->setFont(font);
        label_30 = new QLabel(pageSynGrad);
        label_30->setObjectName(QStringLiteral("label_30"));
        label_30->setGeometry(QRect(295, 4, 61, 15));
        label_32 = new QLabel(pageSynGrad);
        label_32->setObjectName(QStringLiteral("label_32"));
        label_32->setGeometry(QRect(295, 33, 61, 15));
        label_33 = new QLabel(pageSynGrad);
        label_33->setObjectName(QStringLiteral("label_33"));
        label_33->setGeometry(QRect(295, 80, 61, 15));
        label_34 = new QLabel(pageSynGrad);
        label_34->setObjectName(QStringLiteral("label_34"));
        label_34->setGeometry(QRect(295, 109, 61, 15));
        line = new QFrame(pageSynGrad);
        line->setObjectName(QStringLiteral("line"));
        line->setGeometry(QRect(0, 60, 441, 16));
        line->setFrameShape(QFrame::HLine);
        line->setFrameShadow(QFrame::Sunken);
        synapseModelPages->addWidget(pageSynGrad);
        label = new QLabel(centralWidget);
        label->setObjectName(QStringLiteral("label"));
        label->setGeometry(QRect(810, 50, 111, 16));
        textFreq = new QPlainTextEdit(centralWidget);
        textFreq->setObjectName(QStringLiteral("textFreq"));
        textFreq->setGeometry(QRect(940, 40, 104, 31));
        textTime = new QPlainTextEdit(centralWidget);
        textTime->setObjectName(QStringLiteral("textTime"));
        textTime->setGeometry(QRect(940, 80, 104, 31));
        label_2 = new QLabel(centralWidget);
        label_2->setObjectName(QStringLiteral("label_2"));
        label_2->setGeometry(QRect(820, 90, 81, 16));
        checkImp = new QCheckBox(centralWidget);
        checkImp->setObjectName(QStringLiteral("checkImp"));
        checkImp->setGeometry(QRect(820, 250, 88, 21));
        checkAnti = new QCheckBox(centralWidget);
        checkAnti->setObjectName(QStringLiteral("checkAnti"));
        checkAnti->setGeometry(QRect(940, 250, 88, 21));
        label_3 = new QLabel(centralWidget);
        label_3->setObjectName(QStringLiteral("label_3"));
        label_3->setGeometry(QRect(810, 140, 241, 16));
        QFont font1;
        font1.setFamily(QStringLiteral("DejaVu Sans Mono"));
        font1.setBold(true);
        font1.setItalic(true);
        font1.setWeight(75);
        label_3->setFont(font1);
        label_4 = new QLabel(centralWidget);
        label_4->setObjectName(QStringLiteral("label_4"));
        label_4->setGeometry(QRect(820, 170, 61, 15));
        label_5 = new QLabel(centralWidget);
        label_5->setObjectName(QStringLiteral("label_5"));
        label_5->setGeometry(QRect(820, 210, 61, 15));
        textChannelInput = new QPlainTextEdit(centralWidget);
        textChannelInput->setObjectName(QStringLiteral("textChannelInput"));
        textChannelInput->setGeometry(QRect(940, 160, 104, 31));
        textChannelOutput = new QPlainTextEdit(centralWidget);
        textChannelOutput->setObjectName(QStringLiteral("textChannelOutput"));
        textChannelOutput->setGeometry(QRect(940, 200, 104, 31));
        label_6 = new QLabel(centralWidget);
        label_6->setObjectName(QStringLiteral("label_6"));
        label_6->setGeometry(QRect(20, 20, 171, 31));
        label_6->setAlignment(Qt::AlignCenter);
        neuronModelCombo = new QComboBox(centralWidget);
        neuronModelCombo->setObjectName(QStringLiteral("neuronModelCombo"));
        neuronModelCombo->setGeometry(QRect(20, 60, 171, 31));
        label_7 = new QLabel(centralWidget);
        label_7->setObjectName(QStringLiteral("label_7"));
        label_7->setGeometry(QRect(20, 180, 171, 31));
        label_7->setAlignment(Qt::AlignCenter);
        synapseModelCombo = new QComboBox(centralWidget);
        synapseModelCombo->setObjectName(QStringLiteral("synapseModelCombo"));
        synapseModelCombo->setGeometry(QRect(20, 220, 171, 31));
        frameNeuron = new QFrame(centralWidget);
        frameNeuron->setObjectName(QStringLiteral("frameNeuron"));
        frameNeuron->setGeometry(QRect(210, 20, 581, 141));
        frameNeuron->setFrameShape(QFrame::StyledPanel);
        frameNeuron->setFrameShadow(QFrame::Raised);
        neuronModelPages = new QStackedWidget(frameNeuron);
        neuronModelPages->setObjectName(QStringLiteral("neuronModelPages"));
        neuronModelPages->setGeometry(QRect(10, 10, 561, 121));
        pageIz = new QWidget();
        pageIz->setObjectName(QStringLiteral("pageIz"));
        textIzA = new QPlainTextEdit(pageIz);
        textIzA->setObjectName(QStringLiteral("textIzA"));
        textIzA->setGeometry(QRect(40, 0, 104, 21));
        textIzA->setFont(font);
        textIzB = new QPlainTextEdit(pageIz);
        textIzB->setObjectName(QStringLiteral("textIzB"));
        textIzB->setGeometry(QRect(40, 30, 104, 21));
        textIzB->setFont(font);
        textIzC = new QPlainTextEdit(pageIz);
        textIzC->setObjectName(QStringLiteral("textIzC"));
        textIzC->setGeometry(QRect(40, 60, 104, 21));
        textIzC->setFont(font);
        textIzD = new QPlainTextEdit(pageIz);
        textIzD->setObjectName(QStringLiteral("textIzD"));
        textIzD->setGeometry(QRect(40, 90, 104, 21));
        textIzD->setFont(font);
        textIzI = new QPlainTextEdit(pageIz);
        textIzI->setObjectName(QStringLiteral("textIzI"));
        textIzI->setGeometry(QRect(220, 0, 104, 21));
        textIzI->setFont(font);
        textIzUIni = new QPlainTextEdit(pageIz);
        textIzUIni->setObjectName(QStringLiteral("textIzUIni"));
        textIzUIni->setGeometry(QRect(220, 60, 104, 21));
        textIzUIni->setFont(font);
        textIzVIni = new QPlainTextEdit(pageIz);
        textIzVIni->setObjectName(QStringLiteral("textIzVIni"));
        textIzVIni->setGeometry(QRect(220, 30, 104, 21));
        textIzVIni->setFont(font);
        label_8 = new QLabel(pageIz);
        label_8->setObjectName(QStringLiteral("label_8"));
        label_8->setGeometry(QRect(20, 0, 21, 16));
        label_11 = new QLabel(pageIz);
        label_11->setObjectName(QStringLiteral("label_11"));
        label_11->setGeometry(QRect(20, 30, 21, 16));
        label_12 = new QLabel(pageIz);
        label_12->setObjectName(QStringLiteral("label_12"));
        label_12->setGeometry(QRect(20, 60, 21, 16));
        label_13 = new QLabel(pageIz);
        label_13->setObjectName(QStringLiteral("label_13"));
        label_13->setGeometry(QRect(20, 90, 21, 16));
        label_14 = new QLabel(pageIz);
        label_14->setObjectName(QStringLiteral("label_14"));
        label_14->setGeometry(QRect(190, 0, 21, 16));
        label_15 = new QLabel(pageIz);
        label_15->setObjectName(QStringLiteral("label_15"));
        label_15->setGeometry(QRect(180, 30, 31, 16));
        label_16 = new QLabel(pageIz);
        label_16->setObjectName(QStringLiteral("label_16"));
        label_16->setGeometry(QRect(180, 60, 31, 16));
        neuronModelPages->addWidget(pageIz);
        pageHr = new QWidget();
        pageHr->setObjectName(QStringLiteral("pageHr"));
        label_20 = new QLabel(pageHr);
        label_20->setObjectName(QStringLiteral("label_20"));
        label_20->setGeometry(QRect(180, 30, 31, 16));
        textHrYIni = new QPlainTextEdit(pageHr);
        textHrYIni->setObjectName(QStringLiteral("textHrYIni"));
        textHrYIni->setGeometry(QRect(220, 60, 104, 21));
        textHrYIni->setFont(font);
        textHrI = new QPlainTextEdit(pageHr);
        textHrI->setObjectName(QStringLiteral("textHrI"));
        textHrI->setGeometry(QRect(220, 0, 104, 21));
        textHrI->setFont(font);
        label_19 = new QLabel(pageHr);
        label_19->setObjectName(QStringLiteral("label_19"));
        label_19->setGeometry(QRect(190, 0, 21, 16));
        label_18 = new QLabel(pageHr);
        label_18->setObjectName(QStringLiteral("label_18"));
        label_18->setGeometry(QRect(20, 30, 21, 16));
        textHrXIni = new QPlainTextEdit(pageHr);
        textHrXIni->setObjectName(QStringLiteral("textHrXIni"));
        textHrXIni->setGeometry(QRect(220, 30, 104, 21));
        textHrXIni->setFont(font);
        label_9 = new QLabel(pageHr);
        label_9->setObjectName(QStringLiteral("label_9"));
        label_9->setGeometry(QRect(20, 0, 21, 16));
        textHrR = new QPlainTextEdit(pageHr);
        textHrR->setObjectName(QStringLiteral("textHrR"));
        textHrR->setGeometry(QRect(40, 0, 104, 21));
        textHrR->setFont(font);
        textHrS = new QPlainTextEdit(pageHr);
        textHrS->setObjectName(QStringLiteral("textHrS"));
        textHrS->setGeometry(QRect(40, 30, 104, 21));
        textHrS->setFont(font);
        label_17 = new QLabel(pageHr);
        label_17->setObjectName(QStringLiteral("label_17"));
        label_17->setGeometry(QRect(180, 60, 31, 16));
        label_21 = new QLabel(pageHr);
        label_21->setObjectName(QStringLiteral("label_21"));
        label_21->setGeometry(QRect(180, 90, 31, 16));
        textHrZIni = new QPlainTextEdit(pageHr);
        textHrZIni->setObjectName(QStringLiteral("textHrZIni"));
        textHrZIni->setGeometry(QRect(220, 90, 104, 21));
        textHrZIni->setFont(font);
        neuronModelPages->addWidget(pageHr);
        pageRlk = new QWidget();
        pageRlk->setObjectName(QStringLiteral("pageRlk"));
        label_25 = new QLabel(pageRlk);
        label_25->setObjectName(QStringLiteral("label_25"));
        label_25->setGeometry(QRect(180, 30, 31, 16));
        textRlkI = new QPlainTextEdit(pageRlk);
        textRlkI->setObjectName(QStringLiteral("textRlkI"));
        textRlkI->setGeometry(QRect(220, 0, 104, 21));
        textRlkI->setFont(font);
        textRlkXIni = new QPlainTextEdit(pageRlk);
        textRlkXIni->setObjectName(QStringLiteral("textRlkXIni"));
        textRlkXIni->setGeometry(QRect(220, 60, 104, 21));
        textRlkXIni->setFont(font);
        textRlkAlpha = new QPlainTextEdit(pageRlk);
        textRlkAlpha->setObjectName(QStringLiteral("textRlkAlpha"));
        textRlkAlpha->setGeometry(QRect(50, 0, 104, 21));
        textRlkAlpha->setFont(font);
        textRlkSigma = new QPlainTextEdit(pageRlk);
        textRlkSigma->setObjectName(QStringLiteral("textRlkSigma"));
        textRlkSigma->setGeometry(QRect(50, 30, 104, 21));
        textRlkSigma->setFont(font);
        label_24 = new QLabel(pageRlk);
        label_24->setObjectName(QStringLiteral("label_24"));
        label_24->setGeometry(QRect(189, 2, 21, 16));
        label_10 = new QLabel(pageRlk);
        label_10->setObjectName(QStringLiteral("label_10"));
        label_10->setGeometry(QRect(2, 1, 41, 20));
        label_22 = new QLabel(pageRlk);
        label_22->setObjectName(QStringLiteral("label_22"));
        label_22->setGeometry(QRect(181, 64, 31, 16));
        label_23 = new QLabel(pageRlk);
        label_23->setObjectName(QStringLiteral("label_23"));
        label_23->setGeometry(QRect(0, 30, 41, 20));
        textRlkYIni = new QPlainTextEdit(pageRlk);
        textRlkYIni->setObjectName(QStringLiteral("textRlkYIni"));
        textRlkYIni->setGeometry(QRect(220, 30, 104, 21));
        textRlkYIni->setFont(font);
        textRlkMu = new QPlainTextEdit(pageRlk);
        textRlkMu->setObjectName(QStringLiteral("textRlkMu"));
        textRlkMu->setGeometry(QRect(50, 60, 104, 21));
        textRlkMu->setFont(font);
        label_26 = new QLabel(pageRlk);
        label_26->setObjectName(QStringLiteral("label_26"));
        label_26->setGeometry(QRect(11, 62, 21, 16));
        neuronModelPages->addWidget(pageRlk);
        label_43 = new QLabel(centralWidget);
        label_43->setObjectName(QStringLiteral("label_43"));
        label_43->setGeometry(QRect(20, 350, 171, 31));
        label_43->setLayoutDirection(Qt::LeftToRight);
        label_43->setAlignment(Qt::AlignCenter);
        autocalCombo = new QComboBox(centralWidget);
        autocalCombo->setObjectName(QStringLiteral("autocalCombo"));
        autocalCombo->setGeometry(QRect(20, 390, 171, 31));
        frameAutocal = new QFrame(centralWidget);
        frameAutocal->setObjectName(QStringLiteral("frameAutocal"));
        frameAutocal->setGeometry(QRect(210, 350, 581, 171));
        frameAutocal->setFrameShape(QFrame::StyledPanel);
        frameAutocal->setFrameShadow(QFrame::Raised);
        autocalPages = new QStackedWidget(frameAutocal);
        autocalPages->setObjectName(QStringLiteral("autocalPages"));
        autocalPages->setGeometry(QRect(10, 10, 561, 151));
        pageOff = new QWidget();
        pageOff->setObjectName(QStringLiteral("pageOff"));
        autocalPages->addWidget(pageOff);
        pageElectricalConductanceMSE = new QWidget();
        pageElectricalConductanceMSE->setObjectName(QStringLiteral("pageElectricalConductanceMSE"));
        plainTextEdit = new QPlainTextEdit(pageElectricalConductanceMSE);
        plainTextEdit->setObjectName(QStringLiteral("plainTextEdit"));
        plainTextEdit->setGeometry(QRect(120, 50, 104, 70));
        autocalPages->addWidget(pageElectricalConductanceMSE);
        pageGradualMap = new QWidget();
        pageGradualMap->setObjectName(QStringLiteral("pageGradualMap"));
        label_69 = new QLabel(pageGradualMap);
        label_69->setObjectName(QStringLiteral("label_69"));
        label_69->setGeometry(QRect(30, 50, 181, 31));
        label_69->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        gradualModelToExternalSelect = new QComboBox(pageGradualMap);
        gradualModelToExternalSelect->setObjectName(QStringLiteral("gradualModelToExternalSelect"));
        gradualModelToExternalSelect->setGeometry(QRect(210, 50, 79, 31));
        gradualExternalToModelSelect = new QComboBox(pageGradualMap);
        gradualExternalToModelSelect->setObjectName(QStringLiteral("gradualExternalToModelSelect"));
        gradualExternalToModelSelect->setGeometry(QRect(210, 100, 79, 31));
        label_70 = new QLabel(pageGradualMap);
        label_70->setObjectName(QStringLiteral("label_70"));
        label_70->setGeometry(QRect(30, 100, 191, 31));
        label_70->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        label_71 = new QLabel(pageGradualMap);
        label_71->setObjectName(QStringLiteral("label_71"));
        label_71->setGeometry(QRect(160, 0, 181, 31));
        label_71->setAlignment(Qt::AlignCenter);
        label_72 = new QLabel(pageGradualMap);
        label_72->setObjectName(QStringLiteral("label_72"));
        label_72->setGeometry(QRect(270, 0, 181, 31));
        label_72->setAlignment(Qt::AlignCenter);
        label_73 = new QLabel(pageGradualMap);
        label_73->setObjectName(QStringLiteral("label_73"));
        label_73->setGeometry(QRect(380, 0, 181, 31));
        label_73->setAlignment(Qt::AlignCenter);
        chemMap_MaxToExternal = new QDoubleSpinBox(pageGradualMap);
        chemMap_MaxToExternal->setObjectName(QStringLiteral("chemMap_MaxToExternal"));
        chemMap_MaxToExternal->setGeometry(QRect(330, 50, 68, 31));
        chemMap_MaxToExternal->setSingleStep(0.1);
        chemMap_MaxToModel = new QDoubleSpinBox(pageGradualMap);
        chemMap_MaxToModel->setObjectName(QStringLiteral("chemMap_MaxToModel"));
        chemMap_MaxToModel->setGeometry(QRect(330, 100, 68, 31));
        chemMap_MaxToModel->setSingleStep(0.1);
        chemMap_StepToExternal = new QDoubleSpinBox(pageGradualMap);
        chemMap_StepToExternal->setObjectName(QStringLiteral("chemMap_StepToExternal"));
        chemMap_StepToExternal->setGeometry(QRect(440, 50, 68, 31));
        chemMap_StepToExternal->setSingleStep(0.1);
        chemMap_StepToModel = new QDoubleSpinBox(pageGradualMap);
        chemMap_StepToModel->setObjectName(QStringLiteral("chemMap_StepToModel"));
        chemMap_StepToModel->setGeometry(QRect(440, 100, 68, 31));
        chemMap_StepToModel->setSingleStep(0.1);
        autocalPages->addWidget(pageGradualMap);
        RTBiomanager->setCentralWidget(centralWidget);

        retranslateUi(RTBiomanager);

        synapseModelPages->setCurrentIndex(0);
        neuronModelPages->setCurrentIndex(0);
        autocalPages->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(RTBiomanager);
    } // setupUi

    void retranslateUi(QMainWindow *RTBiomanager)
    {
        RTBiomanager->setWindowTitle(QApplication::translate("RTBiomanager", "RTBiomanager", Q_NULLPTR));
        simulate->setText(QApplication::translate("RTBiomanager", "Start", Q_NULLPTR));
        label_27->setText(QApplication::translate("RTBiomanager", "Model to external neuron conductance: ", Q_NULLPTR));
        textSynElec_gMtoE->setPlainText(QApplication::translate("RTBiomanager", "0.02", Q_NULLPTR));
        label_28->setText(QApplication::translate("RTBiomanager", "External neuron to model conductance:", Q_NULLPTR));
        textSynElec_gEtoM->setPlainText(QApplication::translate("RTBiomanager", "0.2", Q_NULLPTR));
        label_29->setText(QApplication::translate("RTBiomanager", "Model to external neuron conductances: ", Q_NULLPTR));
        textSynGrad_gMtoE_slow->setPlainText(QApplication::translate("RTBiomanager", "0.1", Q_NULLPTR));
        textSynGrad_gMtoE_fast->setPlainText(QApplication::translate("RTBiomanager", "0.0", Q_NULLPTR));
        label_31->setText(QApplication::translate("RTBiomanager", "External neuron to model conductances:", Q_NULLPTR));
        textSynGrad_gEtoM_slow->setPlainText(QApplication::translate("RTBiomanager", "0.3", Q_NULLPTR));
        textSynGrad_gEtoM_fast->setPlainText(QApplication::translate("RTBiomanager", "0.0", Q_NULLPTR));
        label_30->setText(QApplication::translate("RTBiomanager", "Slow", Q_NULLPTR));
        label_32->setText(QApplication::translate("RTBiomanager", "Fast", Q_NULLPTR));
        label_33->setText(QApplication::translate("RTBiomanager", "Slow", Q_NULLPTR));
        label_34->setText(QApplication::translate("RTBiomanager", "Fast", Q_NULLPTR));
        label->setText(QApplication::translate("RTBiomanager", "Frequency (kHz)", Q_NULLPTR));
        textFreq->setPlainText(QApplication::translate("RTBiomanager", "10", Q_NULLPTR));
        textTime->setPlainText(QApplication::translate("RTBiomanager", "5", Q_NULLPTR));
        label_2->setText(QApplication::translate("RTBiomanager", "Duration (s)", Q_NULLPTR));
        checkImp->setText(QApplication::translate("RTBiomanager", "Important", Q_NULLPTR));
        checkAnti->setText(QApplication::translate("RTBiomanager", "Antiphase", Q_NULLPTR));
        label_3->setText(QApplication::translate("RTBiomanager", "Channels (separated by commas)", Q_NULLPTR));
        label_4->setText(QApplication::translate("RTBiomanager", "Input", Q_NULLPTR));
        label_5->setText(QApplication::translate("RTBiomanager", "Output", Q_NULLPTR));
        label_6->setText(QApplication::translate("RTBiomanager", "Neuron model", Q_NULLPTR));
        neuronModelCombo->clear();
        neuronModelCombo->insertItems(0, QStringList()
         << QApplication::translate("RTBiomanager", "Izhikevich", Q_NULLPTR)
         << QApplication::translate("RTBiomanager", "Hindmarsh-Rose", Q_NULLPTR)
         << QApplication::translate("RTBiomanager", "Rulkov Map", Q_NULLPTR)
        );
        label_7->setText(QApplication::translate("RTBiomanager", "Synapse model", Q_NULLPTR));
        synapseModelCombo->clear();
        synapseModelCombo->insertItems(0, QStringList()
         << QApplication::translate("RTBiomanager", "Electrical", Q_NULLPTR)
         << QApplication::translate("RTBiomanager", "Gradual chemical", Q_NULLPTR)
        );
        textIzA->setPlainText(QApplication::translate("RTBiomanager", "0.02", Q_NULLPTR));
        textIzB->setPlainText(QApplication::translate("RTBiomanager", "0.2", Q_NULLPTR));
        textIzC->setPlainText(QApplication::translate("RTBiomanager", "-50.0", Q_NULLPTR));
        textIzD->setPlainText(QApplication::translate("RTBiomanager", "2.0", Q_NULLPTR));
        textIzI->setPlainText(QApplication::translate("RTBiomanager", "10.0", Q_NULLPTR));
        textIzUIni->setPlainText(QApplication::translate("RTBiomanager", "-5.544592", Q_NULLPTR));
        textIzVIni->setPlainText(QApplication::translate("RTBiomanager", "30.240263", Q_NULLPTR));
        label_8->setText(QApplication::translate("RTBiomanager", "A", Q_NULLPTR));
        label_11->setText(QApplication::translate("RTBiomanager", "B", Q_NULLPTR));
        label_12->setText(QApplication::translate("RTBiomanager", "C", Q_NULLPTR));
        label_13->setText(QApplication::translate("RTBiomanager", "D", Q_NULLPTR));
        label_14->setText(QApplication::translate("RTBiomanager", "I", Q_NULLPTR));
        label_15->setText(QApplication::translate("RTBiomanager", "V Ini", Q_NULLPTR));
        label_16->setText(QApplication::translate("RTBiomanager", "U Ini", Q_NULLPTR));
        label_20->setText(QApplication::translate("RTBiomanager", "X Ini", Q_NULLPTR));
        textHrYIni->setPlainText(QApplication::translate("RTBiomanager", "-1.936878", Q_NULLPTR));
        textHrI->setPlainText(QApplication::translate("RTBiomanager", "3.0", Q_NULLPTR));
        label_19->setText(QApplication::translate("RTBiomanager", "I", Q_NULLPTR));
        label_18->setText(QApplication::translate("RTBiomanager", "S", Q_NULLPTR));
        textHrXIni->setPlainText(QApplication::translate("RTBiomanager", "-0.712841", Q_NULLPTR));
        label_9->setText(QApplication::translate("RTBiomanager", "R", Q_NULLPTR));
        textHrR->setPlainText(QApplication::translate("RTBiomanager", "0.0021", Q_NULLPTR));
        textHrS->setPlainText(QApplication::translate("RTBiomanager", "4.0", Q_NULLPTR));
        label_17->setText(QApplication::translate("RTBiomanager", "Y Ini", Q_NULLPTR));
        label_21->setText(QApplication::translate("RTBiomanager", "Z Ini", Q_NULLPTR));
        textHrZIni->setPlainText(QApplication::translate("RTBiomanager", "3.165682", Q_NULLPTR));
        label_25->setText(QApplication::translate("RTBiomanager", "X Ini", Q_NULLPTR));
        textRlkI->setPlainText(QApplication::translate("RTBiomanager", "1.0", Q_NULLPTR));
        textRlkXIni->setPlainText(QApplication::translate("RTBiomanager", "-4.919226", Q_NULLPTR));
        textRlkAlpha->setPlainText(QApplication::translate("RTBiomanager", "6.0", Q_NULLPTR));
        textRlkSigma->setPlainText(QApplication::translate("RTBiomanager", "0.1", Q_NULLPTR));
        label_24->setText(QApplication::translate("RTBiomanager", "I", Q_NULLPTR));
        label_10->setText(QApplication::translate("RTBiomanager", "Alpha", Q_NULLPTR));
        label_22->setText(QApplication::translate("RTBiomanager", "Y Ini", Q_NULLPTR));
        label_23->setText(QApplication::translate("RTBiomanager", "Sigma", Q_NULLPTR));
        textRlkYIni->setPlainText(QApplication::translate("RTBiomanager", "-1.701747", Q_NULLPTR));
        textRlkMu->setPlainText(QApplication::translate("RTBiomanager", "0.001", Q_NULLPTR));
        label_26->setText(QApplication::translate("RTBiomanager", "Mu", Q_NULLPTR));
        label_43->setText(QApplication::translate("RTBiomanager", "Calibration & exploration", Q_NULLPTR));
        autocalCombo->clear();
        autocalCombo->insertItems(0, QStringList()
         << QApplication::translate("RTBiomanager", "Off", Q_NULLPTR)
         << QApplication::translate("RTBiomanager", "Electrical conductance", Q_NULLPTR)
         << QApplication::translate("RTBiomanager", "Gradual chemical map", Q_NULLPTR)
        );
        plainTextEdit->setPlainText(QApplication::translate("RTBiomanager", "Elect\n"
"", Q_NULLPTR));
        label_69->setText(QApplication::translate("RTBiomanager", "Model to external neuron:", Q_NULLPTR));
        gradualModelToExternalSelect->clear();
        gradualModelToExternalSelect->insertItems(0, QStringList()
         << QApplication::translate("RTBiomanager", "Fast", Q_NULLPTR)
         << QApplication::translate("RTBiomanager", "Slow", Q_NULLPTR)
        );
        gradualExternalToModelSelect->clear();
        gradualExternalToModelSelect->insertItems(0, QStringList()
         << QApplication::translate("RTBiomanager", "Fast", Q_NULLPTR)
         << QApplication::translate("RTBiomanager", "Slow", Q_NULLPTR)
        );
        label_70->setText(QApplication::translate("RTBiomanager", "External to model neuron:", Q_NULLPTR));
        label_71->setText(QApplication::translate("RTBiomanager", "Synapsis\n"
"speed", Q_NULLPTR));
        label_72->setText(QApplication::translate("RTBiomanager", "Max\n"
"conduntance", Q_NULLPTR));
        label_73->setText(QApplication::translate("RTBiomanager", "Increase\n"
"Step", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class RTBiomanager: public Ui_RTBiomanager {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_RTBIOMANAGER_H
