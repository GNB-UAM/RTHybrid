/********************************************************************************
** Form generated from reading UI file 'rtbiomanager.ui'
**
** Created by: Qt User Interface Compiler version 5.9.2
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
#include <QtWidgets/QSpinBox>
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
    QLabel *label_28;
    QDoubleSpinBox *doubleSynElec_gMtoE;
    QDoubleSpinBox *doubleSynElec_gEtoM;
    QWidget *pageSynGrad;
    QLabel *label_29;
    QLabel *label_31;
    QLabel *label_30;
    QLabel *label_32;
    QLabel *label_33;
    QLabel *label_34;
    QDoubleSpinBox *doubleSynGrad_gMtoE_slow;
    QDoubleSpinBox *doubleSynGrad_gMtoE_fast;
    QDoubleSpinBox *doubleSynGrad_gEtoM_slow;
    QDoubleSpinBox *doubleSynGrad_gEtoM_fast;
    QFrame *line;
    QLabel *label;
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
    QLabel *label_8;
    QLabel *label_11;
    QLabel *label_12;
    QLabel *label_13;
    QLabel *label_14;
    QLabel *label_15;
    QLabel *label_16;
    QDoubleSpinBox *doubleIzA;
    QDoubleSpinBox *doubleIzB;
    QDoubleSpinBox *doubleIzC;
    QDoubleSpinBox *doubleIzD;
    QDoubleSpinBox *doubleIzI;
    QDoubleSpinBox *doubleIzVini;
    QDoubleSpinBox *doubleIzUini;
    QWidget *pageHr;
    QLabel *label_20;
    QLabel *label_19;
    QLabel *label_18;
    QLabel *label_9;
    QLabel *label_17;
    QLabel *label_21;
    QDoubleSpinBox *doubleHrR;
    QDoubleSpinBox *doubleHrS;
    QDoubleSpinBox *doubleHrI;
    QDoubleSpinBox *doubleHrXIni;
    QDoubleSpinBox *doubleHrYIni;
    QDoubleSpinBox *doubleHrZIni;
    QWidget *pageRlk;
    QLabel *label_25;
    QLabel *label_24;
    QLabel *label_10;
    QLabel *label_22;
    QLabel *label_23;
    QLabel *label_26;
    QDoubleSpinBox *doubleRlkAlpha;
    QDoubleSpinBox *doubleRlkSigma;
    QDoubleSpinBox *doubleRlkMu;
    QDoubleSpinBox *doubleRlkI;
    QDoubleSpinBox *doubleRlkXIni;
    QDoubleSpinBox *doubleRlkYIni;
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
    QLabel *label_35;
    QLabel *label_36;
    QSpinBox *intFreq;
    QSpinBox *intTime;
    QSpinBox *intTimeBefore;
    QSpinBox *intTimeAfter;
    QLabel *label_37;

    void setupUi(QMainWindow *RTBiomanager)
    {
        if (RTBiomanager->objectName().isEmpty())
            RTBiomanager->setObjectName(QStringLiteral("RTBiomanager"));
        RTBiomanager->resize(1286, 716);
        centralWidget = new QWidget(RTBiomanager);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        simulate = new QPushButton(centralWidget);
        simulate->setObjectName(QStringLiteral("simulate"));
        simulate->setGeometry(QRect(1100, 490, 82, 23));
        frameSynapse = new QFrame(centralWidget);
        frameSynapse->setObjectName(QStringLiteral("frameSynapse"));
        frameSynapse->setGeometry(QRect(230, 180, 761, 231));
        frameSynapse->setFrameShape(QFrame::StyledPanel);
        frameSynapse->setFrameShadow(QFrame::Raised);
        synapseModelPages = new QStackedWidget(frameSynapse);
        synapseModelPages->setObjectName(QStringLiteral("synapseModelPages"));
        synapseModelPages->setGeometry(QRect(10, 10, 741, 211));
        pageSynElec = new QWidget();
        pageSynElec->setObjectName(QStringLiteral("pageSynElec"));
        label_27 = new QLabel(pageSynElec);
        label_27->setObjectName(QStringLiteral("label_27"));
        label_27->setGeometry(QRect(170, 40, 261, 21));
        label_28 = new QLabel(pageSynElec);
        label_28->setObjectName(QStringLiteral("label_28"));
        label_28->setGeometry(QRect(170, 120, 261, 21));
        doubleSynElec_gMtoE = new QDoubleSpinBox(pageSynElec);
        doubleSynElec_gMtoE->setObjectName(QStringLiteral("doubleSynElec_gMtoE"));
        doubleSynElec_gMtoE->setGeometry(QRect(480, 40, 91, 24));
        doubleSynElec_gMtoE->setSingleStep(0.05);
        doubleSynElec_gMtoE->setValue(0.2);
        doubleSynElec_gEtoM = new QDoubleSpinBox(pageSynElec);
        doubleSynElec_gEtoM->setObjectName(QStringLiteral("doubleSynElec_gEtoM"));
        doubleSynElec_gEtoM->setGeometry(QRect(480, 120, 91, 24));
        doubleSynElec_gEtoM->setSingleStep(0.05);
        doubleSynElec_gEtoM->setValue(0.2);
        synapseModelPages->addWidget(pageSynElec);
        pageSynGrad = new QWidget();
        pageSynGrad->setObjectName(QStringLiteral("pageSynGrad"));
        label_29 = new QLabel(pageSynGrad);
        label_29->setObjectName(QStringLiteral("label_29"));
        label_29->setGeometry(QRect(90, 10, 261, 16));
        QFont font;
        font.setBold(true);
        font.setWeight(75);
        label_29->setFont(font);
        label_31 = new QLabel(pageSynGrad);
        label_31->setObjectName(QStringLiteral("label_31"));
        label_31->setGeometry(QRect(440, 10, 261, 16));
        label_31->setFont(font);
        label_30 = new QLabel(pageSynGrad);
        label_30->setObjectName(QStringLiteral("label_30"));
        label_30->setGeometry(QRect(130, 40, 61, 15));
        label_32 = new QLabel(pageSynGrad);
        label_32->setObjectName(QStringLiteral("label_32"));
        label_32->setGeometry(QRect(250, 40, 61, 15));
        label_33 = new QLabel(pageSynGrad);
        label_33->setObjectName(QStringLiteral("label_33"));
        label_33->setGeometry(QRect(480, 40, 61, 15));
        label_34 = new QLabel(pageSynGrad);
        label_34->setObjectName(QStringLiteral("label_34"));
        label_34->setGeometry(QRect(600, 40, 61, 15));
        doubleSynGrad_gMtoE_slow = new QDoubleSpinBox(pageSynGrad);
        doubleSynGrad_gMtoE_slow->setObjectName(QStringLiteral("doubleSynGrad_gMtoE_slow"));
        doubleSynGrad_gMtoE_slow->setGeometry(QRect(100, 70, 91, 24));
        doubleSynGrad_gMtoE_slow->setSingleStep(0.05);
        doubleSynGrad_gMtoE_slow->setValue(0.1);
        doubleSynGrad_gMtoE_fast = new QDoubleSpinBox(pageSynGrad);
        doubleSynGrad_gMtoE_fast->setObjectName(QStringLiteral("doubleSynGrad_gMtoE_fast"));
        doubleSynGrad_gMtoE_fast->setGeometry(QRect(220, 70, 91, 24));
        doubleSynGrad_gMtoE_fast->setSingleStep(0.05);
        doubleSynGrad_gMtoE_fast->setValue(0);
        doubleSynGrad_gEtoM_slow = new QDoubleSpinBox(pageSynGrad);
        doubleSynGrad_gEtoM_slow->setObjectName(QStringLiteral("doubleSynGrad_gEtoM_slow"));
        doubleSynGrad_gEtoM_slow->setGeometry(QRect(450, 70, 91, 24));
        doubleSynGrad_gEtoM_slow->setSingleStep(0.05);
        doubleSynGrad_gEtoM_slow->setValue(0);
        doubleSynGrad_gEtoM_fast = new QDoubleSpinBox(pageSynGrad);
        doubleSynGrad_gEtoM_fast->setObjectName(QStringLiteral("doubleSynGrad_gEtoM_fast"));
        doubleSynGrad_gEtoM_fast->setGeometry(QRect(570, 70, 91, 24));
        doubleSynGrad_gEtoM_fast->setSingleStep(0.05);
        doubleSynGrad_gEtoM_fast->setValue(0.1);
        line = new QFrame(pageSynGrad);
        line->setObjectName(QStringLiteral("line"));
        line->setGeometry(QRect(140, 110, 481, 20));
        line->setFrameShape(QFrame::HLine);
        line->setFrameShadow(QFrame::Sunken);
        synapseModelPages->addWidget(pageSynGrad);
        label = new QLabel(centralWidget);
        label->setObjectName(QStringLiteral("label"));
        label->setGeometry(QRect(1027, 32, 111, 31));
        label_2 = new QLabel(centralWidget);
        label_2->setObjectName(QStringLiteral("label_2"));
        label_2->setGeometry(QRect(1037, 77, 81, 21));
        checkImp = new QCheckBox(centralWidget);
        checkImp->setObjectName(QStringLiteral("checkImp"));
        checkImp->setGeometry(QRect(1030, 350, 88, 21));
        checkAnti = new QCheckBox(centralWidget);
        checkAnti->setObjectName(QStringLiteral("checkAnti"));
        checkAnti->setGeometry(QRect(1150, 350, 88, 21));
        label_3 = new QLabel(centralWidget);
        label_3->setObjectName(QStringLiteral("label_3"));
        label_3->setGeometry(QRect(1020, 210, 261, 20));
        QFont font1;
        font1.setFamily(QStringLiteral("DejaVu Sans Mono"));
        font1.setBold(true);
        font1.setItalic(true);
        font1.setWeight(75);
        label_3->setFont(font1);
        label_4 = new QLabel(centralWidget);
        label_4->setObjectName(QStringLiteral("label_4"));
        label_4->setGeometry(QRect(1030, 250, 61, 31));
        label_5 = new QLabel(centralWidget);
        label_5->setObjectName(QStringLiteral("label_5"));
        label_5->setGeometry(QRect(1030, 300, 61, 31));
        textChannelInput = new QPlainTextEdit(centralWidget);
        textChannelInput->setObjectName(QStringLiteral("textChannelInput"));
        textChannelInput->setGeometry(QRect(1150, 250, 104, 31));
        textChannelOutput = new QPlainTextEdit(centralWidget);
        textChannelOutput->setObjectName(QStringLiteral("textChannelOutput"));
        textChannelOutput->setGeometry(QRect(1150, 300, 104, 31));
        label_6 = new QLabel(centralWidget);
        label_6->setObjectName(QStringLiteral("label_6"));
        label_6->setGeometry(QRect(20, 40, 171, 31));
        label_6->setAlignment(Qt::AlignCenter);
        neuronModelCombo = new QComboBox(centralWidget);
        neuronModelCombo->setObjectName(QStringLiteral("neuronModelCombo"));
        neuronModelCombo->setGeometry(QRect(20, 80, 171, 31));
        label_7 = new QLabel(centralWidget);
        label_7->setObjectName(QStringLiteral("label_7"));
        label_7->setGeometry(QRect(20, 200, 171, 31));
        label_7->setAlignment(Qt::AlignCenter);
        synapseModelCombo = new QComboBox(centralWidget);
        synapseModelCombo->setObjectName(QStringLiteral("synapseModelCombo"));
        synapseModelCombo->setGeometry(QRect(20, 240, 171, 31));
        frameNeuron = new QFrame(centralWidget);
        frameNeuron->setObjectName(QStringLiteral("frameNeuron"));
        frameNeuron->setGeometry(QRect(230, 20, 761, 141));
        frameNeuron->setFrameShape(QFrame::StyledPanel);
        frameNeuron->setFrameShadow(QFrame::Raised);
        neuronModelPages = new QStackedWidget(frameNeuron);
        neuronModelPages->setObjectName(QStringLiteral("neuronModelPages"));
        neuronModelPages->setGeometry(QRect(10, 10, 741, 121));
        pageIz = new QWidget();
        pageIz->setObjectName(QStringLiteral("pageIz"));
        label_8 = new QLabel(pageIz);
        label_8->setObjectName(QStringLiteral("label_8"));
        label_8->setGeometry(QRect(100, 30, 21, 21));
        label_11 = new QLabel(pageIz);
        label_11->setObjectName(QStringLiteral("label_11"));
        label_11->setGeometry(QRect(100, 60, 21, 21));
        label_12 = new QLabel(pageIz);
        label_12->setObjectName(QStringLiteral("label_12"));
        label_12->setGeometry(QRect(300, 30, 21, 21));
        label_13 = new QLabel(pageIz);
        label_13->setObjectName(QStringLiteral("label_13"));
        label_13->setGeometry(QRect(300, 60, 21, 21));
        label_14 = new QLabel(pageIz);
        label_14->setObjectName(QStringLiteral("label_14"));
        label_14->setGeometry(QRect(500, 20, 21, 21));
        label_15 = new QLabel(pageIz);
        label_15->setObjectName(QStringLiteral("label_15"));
        label_15->setGeometry(QRect(490, 50, 31, 21));
        label_16 = new QLabel(pageIz);
        label_16->setObjectName(QStringLiteral("label_16"));
        label_16->setGeometry(QRect(490, 80, 31, 21));
        doubleIzA = new QDoubleSpinBox(pageIz);
        doubleIzA->setObjectName(QStringLiteral("doubleIzA"));
        doubleIzA->setGeometry(QRect(130, 30, 101, 24));
        doubleIzA->setDecimals(3);
        doubleIzA->setMinimum(-99);
        doubleIzA->setSingleStep(0.01);
        doubleIzA->setValue(0.02);
        doubleIzB = new QDoubleSpinBox(pageIz);
        doubleIzB->setObjectName(QStringLiteral("doubleIzB"));
        doubleIzB->setGeometry(QRect(130, 60, 101, 24));
        doubleIzB->setMinimum(-99);
        doubleIzB->setSingleStep(0.1);
        doubleIzB->setValue(0.2);
        doubleIzC = new QDoubleSpinBox(pageIz);
        doubleIzC->setObjectName(QStringLiteral("doubleIzC"));
        doubleIzC->setGeometry(QRect(330, 30, 101, 24));
        doubleIzC->setMinimum(-99);
        doubleIzC->setValue(-50);
        doubleIzD = new QDoubleSpinBox(pageIz);
        doubleIzD->setObjectName(QStringLiteral("doubleIzD"));
        doubleIzD->setGeometry(QRect(330, 60, 101, 24));
        doubleIzD->setMinimum(-99);
        doubleIzD->setSingleStep(0.1);
        doubleIzD->setValue(2);
        doubleIzI = new QDoubleSpinBox(pageIz);
        doubleIzI->setObjectName(QStringLiteral("doubleIzI"));
        doubleIzI->setGeometry(QRect(540, 20, 101, 24));
        doubleIzI->setValue(10);
        doubleIzVini = new QDoubleSpinBox(pageIz);
        doubleIzVini->setObjectName(QStringLiteral("doubleIzVini"));
        doubleIzVini->setGeometry(QRect(540, 50, 101, 24));
        doubleIzVini->setDecimals(6);
        doubleIzVini->setValue(30.2403);
        doubleIzUini = new QDoubleSpinBox(pageIz);
        doubleIzUini->setObjectName(QStringLiteral("doubleIzUini"));
        doubleIzUini->setGeometry(QRect(540, 80, 101, 24));
        doubleIzUini->setDecimals(6);
        doubleIzUini->setMinimum(-1e+7);
        doubleIzUini->setMaximum(1e+7);
        doubleIzUini->setValue(-5.54459);
        neuronModelPages->addWidget(pageIz);
        pageHr = new QWidget();
        pageHr->setObjectName(QStringLiteral("pageHr"));
        label_20 = new QLabel(pageHr);
        label_20->setObjectName(QStringLiteral("label_20"));
        label_20->setGeometry(QRect(410, 20, 31, 21));
        label_19 = new QLabel(pageHr);
        label_19->setObjectName(QStringLiteral("label_19"));
        label_19->setGeometry(QRect(170, 80, 21, 21));
        label_18 = new QLabel(pageHr);
        label_18->setObjectName(QStringLiteral("label_18"));
        label_18->setGeometry(QRect(170, 50, 21, 21));
        label_9 = new QLabel(pageHr);
        label_9->setObjectName(QStringLiteral("label_9"));
        label_9->setGeometry(QRect(170, 20, 21, 21));
        label_17 = new QLabel(pageHr);
        label_17->setObjectName(QStringLiteral("label_17"));
        label_17->setGeometry(QRect(410, 50, 31, 16));
        label_21 = new QLabel(pageHr);
        label_21->setObjectName(QStringLiteral("label_21"));
        label_21->setGeometry(QRect(410, 80, 31, 16));
        doubleHrR = new QDoubleSpinBox(pageHr);
        doubleHrR->setObjectName(QStringLiteral("doubleHrR"));
        doubleHrR->setGeometry(QRect(190, 20, 101, 24));
        doubleHrR->setDecimals(6);
        doubleHrR->setMinimum(-99.99);
        doubleHrR->setSingleStep(0.0001);
        doubleHrR->setValue(0.0021);
        doubleHrS = new QDoubleSpinBox(pageHr);
        doubleHrS->setObjectName(QStringLiteral("doubleHrS"));
        doubleHrS->setGeometry(QRect(190, 50, 101, 24));
        doubleHrS->setDecimals(2);
        doubleHrS->setMinimum(-99.99);
        doubleHrS->setSingleStep(0.1);
        doubleHrS->setValue(4);
        doubleHrI = new QDoubleSpinBox(pageHr);
        doubleHrI->setObjectName(QStringLiteral("doubleHrI"));
        doubleHrI->setGeometry(QRect(190, 80, 101, 24));
        doubleHrI->setDecimals(2);
        doubleHrI->setMinimum(-99.99);
        doubleHrI->setSingleStep(0.1);
        doubleHrI->setValue(3);
        doubleHrXIni = new QDoubleSpinBox(pageHr);
        doubleHrXIni->setObjectName(QStringLiteral("doubleHrXIni"));
        doubleHrXIni->setGeometry(QRect(460, 20, 101, 24));
        doubleHrXIni->setDecimals(6);
        doubleHrXIni->setMinimum(-99.99);
        doubleHrXIni->setSingleStep(0.1);
        doubleHrXIni->setValue(-0.712841);
        doubleHrYIni = new QDoubleSpinBox(pageHr);
        doubleHrYIni->setObjectName(QStringLiteral("doubleHrYIni"));
        doubleHrYIni->setGeometry(QRect(460, 50, 101, 24));
        doubleHrYIni->setDecimals(6);
        doubleHrYIni->setMinimum(-99.99);
        doubleHrYIni->setSingleStep(0.1);
        doubleHrYIni->setValue(-1.93688);
        doubleHrZIni = new QDoubleSpinBox(pageHr);
        doubleHrZIni->setObjectName(QStringLiteral("doubleHrZIni"));
        doubleHrZIni->setGeometry(QRect(460, 80, 101, 24));
        doubleHrZIni->setDecimals(6);
        doubleHrZIni->setMinimum(-99.99);
        doubleHrZIni->setSingleStep(0.1);
        doubleHrZIni->setValue(3.16568);
        neuronModelPages->addWidget(pageHr);
        pageRlk = new QWidget();
        pageRlk->setObjectName(QStringLiteral("pageRlk"));
        label_25 = new QLabel(pageRlk);
        label_25->setObjectName(QStringLiteral("label_25"));
        label_25->setGeometry(QRect(400, 50, 31, 16));
        label_24 = new QLabel(pageRlk);
        label_24->setObjectName(QStringLiteral("label_24"));
        label_24->setGeometry(QRect(410, 22, 21, 16));
        label_10 = new QLabel(pageRlk);
        label_10->setObjectName(QStringLiteral("label_10"));
        label_10->setGeometry(QRect(153, 21, 41, 21));
        label_22 = new QLabel(pageRlk);
        label_22->setObjectName(QStringLiteral("label_22"));
        label_22->setGeometry(QRect(400, 84, 31, 16));
        label_23 = new QLabel(pageRlk);
        label_23->setObjectName(QStringLiteral("label_23"));
        label_23->setGeometry(QRect(151, 50, 41, 21));
        label_26 = new QLabel(pageRlk);
        label_26->setObjectName(QStringLiteral("label_26"));
        label_26->setGeometry(QRect(162, 82, 21, 21));
        doubleRlkAlpha = new QDoubleSpinBox(pageRlk);
        doubleRlkAlpha->setObjectName(QStringLiteral("doubleRlkAlpha"));
        doubleRlkAlpha->setGeometry(QRect(210, 20, 101, 24));
        doubleRlkAlpha->setMinimum(-99.99);
        doubleRlkAlpha->setValue(6);
        doubleRlkSigma = new QDoubleSpinBox(pageRlk);
        doubleRlkSigma->setObjectName(QStringLiteral("doubleRlkSigma"));
        doubleRlkSigma->setGeometry(QRect(210, 50, 101, 24));
        doubleRlkSigma->setMinimum(-99.99);
        doubleRlkSigma->setSingleStep(0.1);
        doubleRlkSigma->setValue(0.1);
        doubleRlkMu = new QDoubleSpinBox(pageRlk);
        doubleRlkMu->setObjectName(QStringLiteral("doubleRlkMu"));
        doubleRlkMu->setGeometry(QRect(210, 80, 101, 24));
        doubleRlkMu->setDecimals(4);
        doubleRlkMu->setMinimum(-99.99);
        doubleRlkMu->setSingleStep(0.001);
        doubleRlkMu->setValue(0.001);
        doubleRlkI = new QDoubleSpinBox(pageRlk);
        doubleRlkI->setObjectName(QStringLiteral("doubleRlkI"));
        doubleRlkI->setGeometry(QRect(460, 20, 101, 24));
        doubleRlkI->setMinimum(-99.99);
        doubleRlkI->setValue(1);
        doubleRlkXIni = new QDoubleSpinBox(pageRlk);
        doubleRlkXIni->setObjectName(QStringLiteral("doubleRlkXIni"));
        doubleRlkXIni->setGeometry(QRect(460, 50, 101, 24));
        doubleRlkXIni->setDecimals(6);
        doubleRlkXIni->setMinimum(-99.99);
        doubleRlkXIni->setSingleStep(0.01);
        doubleRlkXIni->setValue(-1.70175);
        doubleRlkYIni = new QDoubleSpinBox(pageRlk);
        doubleRlkYIni->setObjectName(QStringLiteral("doubleRlkYIni"));
        doubleRlkYIni->setGeometry(QRect(460, 80, 101, 24));
        doubleRlkYIni->setDecimals(6);
        doubleRlkYIni->setMinimum(-99.99);
        doubleRlkYIni->setSingleStep(0.01);
        doubleRlkYIni->setValue(-4.91923);
        neuronModelPages->addWidget(pageRlk);
        label_43 = new QLabel(centralWidget);
        label_43->setObjectName(QStringLiteral("label_43"));
        label_43->setGeometry(QRect(20, 450, 171, 31));
        label_43->setLayoutDirection(Qt::LeftToRight);
        label_43->setAlignment(Qt::AlignCenter);
        autocalCombo = new QComboBox(centralWidget);
        autocalCombo->setObjectName(QStringLiteral("autocalCombo"));
        autocalCombo->setGeometry(QRect(20, 490, 171, 31));
        frameAutocal = new QFrame(centralWidget);
        frameAutocal->setObjectName(QStringLiteral("frameAutocal"));
        frameAutocal->setGeometry(QRect(230, 430, 761, 221));
        frameAutocal->setFrameShape(QFrame::StyledPanel);
        frameAutocal->setFrameShadow(QFrame::Raised);
        autocalPages = new QStackedWidget(frameAutocal);
        autocalPages->setObjectName(QStringLiteral("autocalPages"));
        autocalPages->setGeometry(QRect(10, 10, 741, 201));
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
        label_69->setGeometry(QRect(130, 80, 181, 31));
        label_69->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        gradualModelToExternalSelect = new QComboBox(pageGradualMap);
        gradualModelToExternalSelect->setObjectName(QStringLiteral("gradualModelToExternalSelect"));
        gradualModelToExternalSelect->setGeometry(QRect(310, 80, 79, 31));
        gradualExternalToModelSelect = new QComboBox(pageGradualMap);
        gradualExternalToModelSelect->setObjectName(QStringLiteral("gradualExternalToModelSelect"));
        gradualExternalToModelSelect->setGeometry(QRect(310, 130, 79, 31));
        label_70 = new QLabel(pageGradualMap);
        label_70->setObjectName(QStringLiteral("label_70"));
        label_70->setGeometry(QRect(130, 130, 191, 31));
        label_70->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        label_71 = new QLabel(pageGradualMap);
        label_71->setObjectName(QStringLiteral("label_71"));
        label_71->setGeometry(QRect(260, 30, 181, 31));
        label_71->setAlignment(Qt::AlignCenter);
        label_72 = new QLabel(pageGradualMap);
        label_72->setObjectName(QStringLiteral("label_72"));
        label_72->setGeometry(QRect(370, 30, 181, 31));
        label_72->setAlignment(Qt::AlignCenter);
        label_73 = new QLabel(pageGradualMap);
        label_73->setObjectName(QStringLiteral("label_73"));
        label_73->setGeometry(QRect(480, 30, 181, 31));
        label_73->setAlignment(Qt::AlignCenter);
        chemMap_MaxToExternal = new QDoubleSpinBox(pageGradualMap);
        chemMap_MaxToExternal->setObjectName(QStringLiteral("chemMap_MaxToExternal"));
        chemMap_MaxToExternal->setGeometry(QRect(430, 80, 68, 31));
        chemMap_MaxToExternal->setSingleStep(0.1);
        chemMap_MaxToExternal->setValue(0.4);
        chemMap_MaxToModel = new QDoubleSpinBox(pageGradualMap);
        chemMap_MaxToModel->setObjectName(QStringLiteral("chemMap_MaxToModel"));
        chemMap_MaxToModel->setGeometry(QRect(430, 130, 68, 31));
        chemMap_MaxToModel->setSingleStep(0.01);
        chemMap_MaxToModel->setValue(0.06);
        chemMap_StepToExternal = new QDoubleSpinBox(pageGradualMap);
        chemMap_StepToExternal->setObjectName(QStringLiteral("chemMap_StepToExternal"));
        chemMap_StepToExternal->setGeometry(QRect(540, 80, 68, 31));
        chemMap_StepToExternal->setSingleStep(0.1);
        chemMap_StepToExternal->setValue(0.1);
        chemMap_StepToModel = new QDoubleSpinBox(pageGradualMap);
        chemMap_StepToModel->setObjectName(QStringLiteral("chemMap_StepToModel"));
        chemMap_StepToModel->setGeometry(QRect(540, 130, 68, 31));
        chemMap_StepToModel->setSingleStep(0.01);
        chemMap_StepToModel->setValue(0.01);
        autocalPages->addWidget(pageGradualMap);
        label_35 = new QLabel(centralWidget);
        label_35->setObjectName(QStringLiteral("label_35"));
        label_35->setGeometry(QRect(1025, 111, 121, 31));
        label_36 = new QLabel(centralWidget);
        label_36->setObjectName(QStringLiteral("label_36"));
        label_36->setGeometry(QRect(1030, 150, 111, 31));
        intFreq = new QSpinBox(centralWidget);
        intFreq->setObjectName(QStringLiteral("intFreq"));
        intFreq->setGeometry(QRect(1160, 30, 81, 31));
        intFreq->setSingleStep(10);
        intFreq->setValue(10);
        intTime = new QSpinBox(centralWidget);
        intTime->setObjectName(QStringLiteral("intTime"));
        intTime->setGeometry(QRect(1160, 70, 81, 31));
        intTime->setSingleStep(1);
        intTime->setValue(5);
        intTimeBefore = new QSpinBox(centralWidget);
        intTimeBefore->setObjectName(QStringLiteral("intTimeBefore"));
        intTimeBefore->setGeometry(QRect(1160, 110, 81, 31));
        intTimeBefore->setSingleStep(1);
        intTimeBefore->setValue(5);
        intTimeAfter = new QSpinBox(centralWidget);
        intTimeAfter->setObjectName(QStringLiteral("intTimeAfter"));
        intTimeAfter->setGeometry(QRect(1160, 150, 81, 31));
        intTimeAfter->setSingleStep(1);
        intTimeAfter->setValue(5);
        label_37 = new QLabel(centralWidget);
        label_37->setObjectName(QStringLiteral("label_37"));
        label_37->setGeometry(QRect(1040, 420, 61, 15));
        RTBiomanager->setCentralWidget(centralWidget);

        retranslateUi(RTBiomanager);

        synapseModelPages->setCurrentIndex(1);
        neuronModelPages->setCurrentIndex(0);
        autocalPages->setCurrentIndex(2);
        gradualExternalToModelSelect->setCurrentIndex(1);


        QMetaObject::connectSlotsByName(RTBiomanager);
    } // setupUi

    void retranslateUi(QMainWindow *RTBiomanager)
    {
        RTBiomanager->setWindowTitle(QApplication::translate("RTBiomanager", "RTBiomanager", Q_NULLPTR));
        simulate->setText(QApplication::translate("RTBiomanager", "Start", Q_NULLPTR));
        label_27->setText(QApplication::translate("RTBiomanager", "Model to external neuron conductance: ", Q_NULLPTR));
        label_28->setText(QApplication::translate("RTBiomanager", "External neuron to model conductance:", Q_NULLPTR));
        label_29->setText(QApplication::translate("RTBiomanager", "To external neuron conductances:", Q_NULLPTR));
        label_31->setText(QApplication::translate("RTBiomanager", "To model neuron conductances:", Q_NULLPTR));
        label_30->setText(QApplication::translate("RTBiomanager", "Slow", Q_NULLPTR));
        label_32->setText(QApplication::translate("RTBiomanager", "Fast", Q_NULLPTR));
        label_33->setText(QApplication::translate("RTBiomanager", "Slow", Q_NULLPTR));
        label_34->setText(QApplication::translate("RTBiomanager", "Fast", Q_NULLPTR));
        label->setText(QApplication::translate("RTBiomanager", "Frequency (kHz)", Q_NULLPTR));
        label_2->setText(QApplication::translate("RTBiomanager", "Duration (s)", Q_NULLPTR));
        checkImp->setText(QApplication::translate("RTBiomanager", "Important", Q_NULLPTR));
        checkAnti->setText(QApplication::translate("RTBiomanager", "Antiphase", Q_NULLPTR));
        label_3->setText(QApplication::translate("RTBiomanager", "Channels (separated by commas):", Q_NULLPTR));
        label_4->setText(QApplication::translate("RTBiomanager", "Input", Q_NULLPTR));
        label_5->setText(QApplication::translate("RTBiomanager", "Output", Q_NULLPTR));
        textChannelInput->setPlainText(QApplication::translate("RTBiomanager", "0", Q_NULLPTR));
        textChannelOutput->setPlainText(QApplication::translate("RTBiomanager", "0,1", Q_NULLPTR));
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
        label_8->setText(QApplication::translate("RTBiomanager", "A", Q_NULLPTR));
        label_11->setText(QApplication::translate("RTBiomanager", "B", Q_NULLPTR));
        label_12->setText(QApplication::translate("RTBiomanager", "C", Q_NULLPTR));
        label_13->setText(QApplication::translate("RTBiomanager", "D", Q_NULLPTR));
        label_14->setText(QApplication::translate("RTBiomanager", "I", Q_NULLPTR));
        label_15->setText(QApplication::translate("RTBiomanager", "V Ini", Q_NULLPTR));
        label_16->setText(QApplication::translate("RTBiomanager", "U Ini", Q_NULLPTR));
        label_20->setText(QApplication::translate("RTBiomanager", "X Ini", Q_NULLPTR));
        label_19->setText(QApplication::translate("RTBiomanager", "I", Q_NULLPTR));
        label_18->setText(QApplication::translate("RTBiomanager", "S", Q_NULLPTR));
        label_9->setText(QApplication::translate("RTBiomanager", "R", Q_NULLPTR));
        label_17->setText(QApplication::translate("RTBiomanager", "Y Ini", Q_NULLPTR));
        label_21->setText(QApplication::translate("RTBiomanager", "Z Ini", Q_NULLPTR));
        label_25->setText(QApplication::translate("RTBiomanager", "X Ini", Q_NULLPTR));
        label_24->setText(QApplication::translate("RTBiomanager", "I", Q_NULLPTR));
        label_10->setText(QApplication::translate("RTBiomanager", "Alpha", Q_NULLPTR));
        label_22->setText(QApplication::translate("RTBiomanager", "Y Ini", Q_NULLPTR));
        label_23->setText(QApplication::translate("RTBiomanager", "Sigma", Q_NULLPTR));
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
        label_35->setText(QApplication::translate("RTBiomanager", "Before control (s)", Q_NULLPTR));
        label_36->setText(QApplication::translate("RTBiomanager", "After control (s)", Q_NULLPTR));
        label_37->setText(QApplication::translate("RTBiomanager", "Burst/s", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class RTBiomanager: public Ui_RTBiomanager {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_RTBIOMANAGER_H
