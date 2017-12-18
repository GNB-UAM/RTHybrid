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
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QPlainTextEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QRadioButton>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QStackedWidget>
#include <QtWidgets/QTextBrowser>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_RTBiomanager
{
public:
    QWidget *centralWidget;
    QFrame *frameSynapse;
    QStackedWidget *synapseModelPages;
    QWidget *pageSynElec;
    QLabel *label_27;
    QLabel *label_28;
    QDoubleSpinBox *doubleSynElec_gMtoE;
    QDoubleSpinBox *doubleSynElec_gEtoM;
    QCheckBox *checkAnti;
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
    QLabel *label_38;
    QLabel *label_39;
    QDoubleSpinBox *doubleSynGrad_k1;
    QLabel *label_40;
    QDoubleSpinBox *doubleSynGrad_k2;
    QLabel *label_44;
    QLabel *label_45;
    QWidget *layoutWidget;
    QHBoxLayout *horizontalLayout_3;
    QDoubleSpinBox *doubleSynGrad_vslow;
    QLabel *label_46;
    QWidget *layoutWidget1;
    QHBoxLayout *horizontalLayout_4;
    QDoubleSpinBox *doubleSynGrad_vfast;
    QLabel *label_47;
    QLabel *label;
    QLabel *label_2;
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
    QTextBrowser *textBrowser;
    QWidget *pageElectricalConductanceMSE;
    QWidget *layoutWidget2;
    QHBoxLayout *horizontalLayout_2;
    QDoubleSpinBox *doubleMSE_slopereduction;
    QLabel *label_42;
    QWidget *layoutWidget3;
    QVBoxLayout *verticalLayout;
    QRadioButton *radioButtonMSE_percentagereduction;
    QRadioButton *radioButtonMSE_slopereduction;
    QWidget *layoutWidget4;
    QHBoxLayout *horizontalLayout;
    QDoubleSpinBox *doubleMSE_percentagereduction;
    QLabel *label_41;
    QFrame *frame_tmp;
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
    QLabel *label_52;
    QWidget *layoutWidget5;
    QHBoxLayout *horizontalLayout_8;
    QLabel *label_48;
    QDoubleSpinBox *doubleSynGrad_k1_map;
    QWidget *layoutWidget6;
    QHBoxLayout *horizontalLayout_9;
    QLabel *label_49;
    QDoubleSpinBox *doubleSynGrad_k2_map;
    QWidget *layoutWidget7;
    QHBoxLayout *horizontalLayout_10;
    QLabel *label_50;
    QHBoxLayout *horizontalLayout_5;
    QDoubleSpinBox *doubleSynGrad_vfast_map;
    QLabel *label_53;
    QWidget *layoutWidget8;
    QHBoxLayout *horizontalLayout_11;
    QLabel *label_51;
    QHBoxLayout *horizontalLayout_7;
    QDoubleSpinBox *doubleSynGrad_vslow_map;
    QLabel *label_55;
    QLabel *label_35;
    QLabel *label_36;
    QSpinBox *intFreq;
    QSpinBox *intTime;
    QSpinBox *intTimeBefore;
    QSpinBox *intTimeAfter;
    QLabel *label_37;
    QCheckBox *autoDetect;
    QDoubleSpinBox *doubleSecPerBurst;
    QFrame *frameAux;
    QFrame *frameAux2;
    QFrame *frameAux3;
    QFrame *frameAux4;
    QPushButton *simulate;
    QCheckBox *checkImp;

    void setupUi(QMainWindow *RTBiomanager)
    {
        if (RTBiomanager->objectName().isEmpty())
            RTBiomanager->setObjectName(QStringLiteral("RTBiomanager"));
        RTBiomanager->resize(1341, 716);
        RTBiomanager->setStyleSheet(QLatin1String("#centralWidget{\n"
"	background-color: rgb(230, 230, 230);\n"
"	/*Gradiente azul\n"
"	background-color: qlineargradient(spread:pad, x1:0.5, y1:1, x2:0.5, y2:0, stop:0 rgba(13, 71, 161, 255), stop:1 rgba(95, 134, 194, 255));*/\n"
"}\n"
"\n"
"#frameAutocal, #frameSynapse, #frameNeuron, #frameAux,  #frameAux2, #frameAux3, #frameAux4{\n"
"	background-color: rgb(255, 255, 255);\n"
"}\n"
"\n"
"#frame_tmp {\n"
"  background-color:rgb(255,255,255);\n"
"  border: white;\n"
"}\n"
"\n"
"\n"
"	\n"
"\n"
""));
        centralWidget = new QWidget(RTBiomanager);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        centralWidget->setLayoutDirection(Qt::LeftToRight);
        centralWidget->setStyleSheet(QStringLiteral(""));
        frameSynapse = new QFrame(centralWidget);
        frameSynapse->setObjectName(QStringLiteral("frameSynapse"));
        frameSynapse->setGeometry(QRect(270, 180, 761, 271));
        frameSynapse->setFrameShape(QFrame::StyledPanel);
        frameSynapse->setFrameShadow(QFrame::Raised);
        synapseModelPages = new QStackedWidget(frameSynapse);
        synapseModelPages->setObjectName(QStringLiteral("synapseModelPages"));
        synapseModelPages->setGeometry(QRect(10, 10, 741, 251));
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
        doubleSynElec_gMtoE->setDecimals(4);
        doubleSynElec_gMtoE->setSingleStep(0.05);
        doubleSynElec_gMtoE->setValue(0.2);
        doubleSynElec_gEtoM = new QDoubleSpinBox(pageSynElec);
        doubleSynElec_gEtoM->setObjectName(QStringLiteral("doubleSynElec_gEtoM"));
        doubleSynElec_gEtoM->setGeometry(QRect(480, 120, 91, 24));
        doubleSynElec_gEtoM->setDecimals(4);
        doubleSynElec_gEtoM->setSingleStep(0.05);
        doubleSynElec_gEtoM->setValue(0.2);
        checkAnti = new QCheckBox(pageSynElec);
        checkAnti->setObjectName(QStringLiteral("checkAnti"));
        checkAnti->setGeometry(QRect(330, 190, 88, 21));
        checkAnti->setChecked(true);
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
        doubleSynGrad_gMtoE_slow->setDecimals(4);
        doubleSynGrad_gMtoE_slow->setSingleStep(0.01);
        doubleSynGrad_gMtoE_slow->setValue(0.02);
        doubleSynGrad_gMtoE_fast = new QDoubleSpinBox(pageSynGrad);
        doubleSynGrad_gMtoE_fast->setObjectName(QStringLiteral("doubleSynGrad_gMtoE_fast"));
        doubleSynGrad_gMtoE_fast->setGeometry(QRect(220, 70, 91, 24));
        doubleSynGrad_gMtoE_fast->setDecimals(4);
        doubleSynGrad_gMtoE_fast->setSingleStep(0.05);
        doubleSynGrad_gMtoE_fast->setValue(0);
        doubleSynGrad_gEtoM_slow = new QDoubleSpinBox(pageSynGrad);
        doubleSynGrad_gEtoM_slow->setObjectName(QStringLiteral("doubleSynGrad_gEtoM_slow"));
        doubleSynGrad_gEtoM_slow->setGeometry(QRect(450, 70, 91, 24));
        doubleSynGrad_gEtoM_slow->setDecimals(4);
        doubleSynGrad_gEtoM_slow->setSingleStep(0.05);
        doubleSynGrad_gEtoM_slow->setValue(0);
        doubleSynGrad_gEtoM_fast = new QDoubleSpinBox(pageSynGrad);
        doubleSynGrad_gEtoM_fast->setObjectName(QStringLiteral("doubleSynGrad_gEtoM_fast"));
        doubleSynGrad_gEtoM_fast->setGeometry(QRect(570, 70, 91, 24));
        doubleSynGrad_gEtoM_fast->setDecimals(4);
        doubleSynGrad_gEtoM_fast->setSingleStep(0.05);
        doubleSynGrad_gEtoM_fast->setValue(0.2);
        line = new QFrame(pageSynGrad);
        line->setObjectName(QStringLiteral("line"));
        line->setGeometry(QRect(140, 120, 481, 20));
        line->setFrameShape(QFrame::HLine);
        line->setFrameShadow(QFrame::Sunken);
        label_38 = new QLabel(pageSynGrad);
        label_38->setObjectName(QStringLiteral("label_38"));
        label_38->setGeometry(QRect(260, 150, 261, 16));
        label_38->setFont(font);
        label_38->setAlignment(Qt::AlignCenter);
        label_39 = new QLabel(pageSynGrad);
        label_39->setObjectName(QStringLiteral("label_39"));
        label_39->setGeometry(QRect(130, 180, 61, 15));
        doubleSynGrad_k1 = new QDoubleSpinBox(pageSynGrad);
        doubleSynGrad_k1->setObjectName(QStringLiteral("doubleSynGrad_k1"));
        doubleSynGrad_k1->setGeometry(QRect(100, 210, 91, 24));
        doubleSynGrad_k1->setDecimals(4);
        doubleSynGrad_k1->setMinimum(-99);
        doubleSynGrad_k1->setSingleStep(0.05);
        doubleSynGrad_k1->setValue(1);
        label_40 = new QLabel(pageSynGrad);
        label_40->setObjectName(QStringLiteral("label_40"));
        label_40->setGeometry(QRect(250, 180, 61, 15));
        doubleSynGrad_k2 = new QDoubleSpinBox(pageSynGrad);
        doubleSynGrad_k2->setObjectName(QStringLiteral("doubleSynGrad_k2"));
        doubleSynGrad_k2->setGeometry(QRect(220, 210, 91, 24));
        doubleSynGrad_k2->setDecimals(4);
        doubleSynGrad_k2->setMinimum(-99);
        doubleSynGrad_k2->setSingleStep(0.005);
        doubleSynGrad_k2->setValue(0.03);
        label_44 = new QLabel(pageSynGrad);
        label_44->setObjectName(QStringLiteral("label_44"));
        label_44->setGeometry(QRect(450, 180, 61, 15));
        label_45 = new QLabel(pageSynGrad);
        label_45->setObjectName(QStringLiteral("label_45"));
        label_45->setGeometry(QRect(590, 180, 61, 15));
        layoutWidget = new QWidget(pageSynGrad);
        layoutWidget->setObjectName(QStringLiteral("layoutWidget"));
        layoutWidget->setGeometry(QRect(570, 210, 72, 25));
        horizontalLayout_3 = new QHBoxLayout(layoutWidget);
        horizontalLayout_3->setSpacing(6);
        horizontalLayout_3->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_3->setObjectName(QStringLiteral("horizontalLayout_3"));
        horizontalLayout_3->setContentsMargins(0, 0, 0, 0);
        doubleSynGrad_vslow = new QDoubleSpinBox(layoutWidget);
        doubleSynGrad_vslow->setObjectName(QStringLiteral("doubleSynGrad_vslow"));
        doubleSynGrad_vslow->setDecimals(0);
        doubleSynGrad_vslow->setMinimum(0);
        doubleSynGrad_vslow->setSingleStep(5);
        doubleSynGrad_vslow->setValue(50);

        horizontalLayout_3->addWidget(doubleSynGrad_vslow);

        label_46 = new QLabel(layoutWidget);
        label_46->setObjectName(QStringLiteral("label_46"));

        horizontalLayout_3->addWidget(label_46);

        layoutWidget1 = new QWidget(pageSynGrad);
        layoutWidget1->setObjectName(QStringLiteral("layoutWidget1"));
        layoutWidget1->setGeometry(QRect(430, 210, 72, 25));
        horizontalLayout_4 = new QHBoxLayout(layoutWidget1);
        horizontalLayout_4->setSpacing(6);
        horizontalLayout_4->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_4->setObjectName(QStringLiteral("horizontalLayout_4"));
        horizontalLayout_4->setContentsMargins(0, 0, 0, 0);
        doubleSynGrad_vfast = new QDoubleSpinBox(layoutWidget1);
        doubleSynGrad_vfast->setObjectName(QStringLiteral("doubleSynGrad_vfast"));
        doubleSynGrad_vfast->setDecimals(0);
        doubleSynGrad_vfast->setMinimum(0);
        doubleSynGrad_vfast->setMaximum(100);
        doubleSynGrad_vfast->setSingleStep(5);
        doubleSynGrad_vfast->setValue(25);

        horizontalLayout_4->addWidget(doubleSynGrad_vfast);

        label_47 = new QLabel(layoutWidget1);
        label_47->setObjectName(QStringLiteral("label_47"));

        horizontalLayout_4->addWidget(label_47);

        synapseModelPages->addWidget(pageSynGrad);
        label = new QLabel(centralWidget);
        label->setObjectName(QStringLiteral("label"));
        label->setGeometry(QRect(1070, 40, 111, 31));
        label_2 = new QLabel(centralWidget);
        label_2->setObjectName(QStringLiteral("label_2"));
        label_2->setGeometry(QRect(1080, 85, 81, 21));
        label_3 = new QLabel(centralWidget);
        label_3->setObjectName(QStringLiteral("label_3"));
        label_3->setGeometry(QRect(1060, 220, 261, 20));
        QFont font1;
        font1.setFamily(QStringLiteral("DejaVu Sans Mono"));
        font1.setBold(true);
        font1.setItalic(true);
        font1.setWeight(75);
        label_3->setFont(font1);
        label_4 = new QLabel(centralWidget);
        label_4->setObjectName(QStringLiteral("label_4"));
        label_4->setGeometry(QRect(1070, 260, 61, 31));
        label_5 = new QLabel(centralWidget);
        label_5->setObjectName(QStringLiteral("label_5"));
        label_5->setGeometry(QRect(1070, 310, 61, 31));
        textChannelInput = new QPlainTextEdit(centralWidget);
        textChannelInput->setObjectName(QStringLiteral("textChannelInput"));
        textChannelInput->setGeometry(QRect(1190, 260, 104, 31));
        textChannelOutput = new QPlainTextEdit(centralWidget);
        textChannelOutput->setObjectName(QStringLiteral("textChannelOutput"));
        textChannelOutput->setGeometry(QRect(1190, 310, 104, 31));
        label_6 = new QLabel(centralWidget);
        label_6->setObjectName(QStringLiteral("label_6"));
        label_6->setGeometry(QRect(30, 30, 211, 31));
        label_6->setAlignment(Qt::AlignCenter);
        neuronModelCombo = new QComboBox(centralWidget);
        neuronModelCombo->setObjectName(QStringLiteral("neuronModelCombo"));
        neuronModelCombo->setGeometry(QRect(40, 70, 191, 31));
        label_7 = new QLabel(centralWidget);
        label_7->setObjectName(QStringLiteral("label_7"));
        label_7->setGeometry(QRect(30, 190, 211, 31));
        label_7->setAlignment(Qt::AlignCenter);
        synapseModelCombo = new QComboBox(centralWidget);
        synapseModelCombo->setObjectName(QStringLiteral("synapseModelCombo"));
        synapseModelCombo->setGeometry(QRect(40, 230, 191, 31));
        frameNeuron = new QFrame(centralWidget);
        frameNeuron->setObjectName(QStringLiteral("frameNeuron"));
        frameNeuron->setGeometry(QRect(270, 20, 761, 141));
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
        label_43->setGeometry(QRect(30, 480, 211, 31));
        label_43->setLayoutDirection(Qt::LeftToRight);
        label_43->setAlignment(Qt::AlignCenter);
        autocalCombo = new QComboBox(centralWidget);
        autocalCombo->setObjectName(QStringLiteral("autocalCombo"));
        autocalCombo->setGeometry(QRect(40, 520, 191, 31));
        frameAutocal = new QFrame(centralWidget);
        frameAutocal->setObjectName(QStringLiteral("frameAutocal"));
        frameAutocal->setGeometry(QRect(270, 470, 761, 221));
        frameAutocal->setStyleSheet(QStringLiteral(""));
        frameAutocal->setFrameShape(QFrame::StyledPanel);
        frameAutocal->setFrameShadow(QFrame::Raised);
        autocalPages = new QStackedWidget(frameAutocal);
        autocalPages->setObjectName(QStringLiteral("autocalPages"));
        autocalPages->setGeometry(QRect(10, 10, 741, 201));
        pageOff = new QWidget();
        pageOff->setObjectName(QStringLiteral("pageOff"));
        textBrowser = new QTextBrowser(pageOff);
        textBrowser->setObjectName(QStringLiteral("textBrowser"));
        textBrowser->setGeometry(QRect(-10, 0, 761, 201));
        textBrowser->setFrameShape(QFrame::NoFrame);
        textBrowser->setFrameShadow(QFrame::Plain);
        textBrowser->setLineWidth(0);
        textBrowser->setOpenExternalLinks(true);
        autocalPages->addWidget(pageOff);
        pageElectricalConductanceMSE = new QWidget();
        pageElectricalConductanceMSE->setObjectName(QStringLiteral("pageElectricalConductanceMSE"));
        layoutWidget2 = new QWidget(pageElectricalConductanceMSE);
        layoutWidget2->setObjectName(QStringLiteral("layoutWidget2"));
        layoutWidget2->setGeometry(QRect(530, 120, 72, 41));
        horizontalLayout_2 = new QHBoxLayout(layoutWidget2);
        horizontalLayout_2->setSpacing(6);
        horizontalLayout_2->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        horizontalLayout_2->setContentsMargins(0, 0, 0, 0);
        doubleMSE_slopereduction = new QDoubleSpinBox(layoutWidget2);
        doubleMSE_slopereduction->setObjectName(QStringLiteral("doubleMSE_slopereduction"));
        doubleMSE_slopereduction->setDecimals(0);
        doubleMSE_slopereduction->setSingleStep(1);
        doubleMSE_slopereduction->setValue(40);

        horizontalLayout_2->addWidget(doubleMSE_slopereduction);

        label_42 = new QLabel(layoutWidget2);
        label_42->setObjectName(QStringLiteral("label_42"));

        horizontalLayout_2->addWidget(label_42);

        layoutWidget3 = new QWidget(pageElectricalConductanceMSE);
        layoutWidget3->setObjectName(QStringLiteral("layoutWidget3"));
        layoutWidget3->setGeometry(QRect(150, 0, 378, 201));
        verticalLayout = new QVBoxLayout(layoutWidget3);
        verticalLayout->setSpacing(6);
        verticalLayout->setContentsMargins(11, 11, 11, 11);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        radioButtonMSE_percentagereduction = new QRadioButton(layoutWidget3);
        radioButtonMSE_percentagereduction->setObjectName(QStringLiteral("radioButtonMSE_percentagereduction"));
        radioButtonMSE_percentagereduction->setChecked(true);

        verticalLayout->addWidget(radioButtonMSE_percentagereduction);

        radioButtonMSE_slopereduction = new QRadioButton(layoutWidget3);
        radioButtonMSE_slopereduction->setObjectName(QStringLiteral("radioButtonMSE_slopereduction"));
        radioButtonMSE_slopereduction->setEnabled(true);
        QSizePolicy sizePolicy(QSizePolicy::Minimum, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(radioButtonMSE_slopereduction->sizePolicy().hasHeightForWidth());
        radioButtonMSE_slopereduction->setSizePolicy(sizePolicy);

        verticalLayout->addWidget(radioButtonMSE_slopereduction);

        layoutWidget4 = new QWidget(pageElectricalConductanceMSE);
        layoutWidget4->setObjectName(QStringLiteral("layoutWidget4"));
        layoutWidget4->setGeometry(QRect(530, 40, 72, 41));
        horizontalLayout = new QHBoxLayout(layoutWidget4);
        horizontalLayout->setSpacing(6);
        horizontalLayout->setContentsMargins(11, 11, 11, 11);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        horizontalLayout->setContentsMargins(0, 0, 0, 0);
        doubleMSE_percentagereduction = new QDoubleSpinBox(layoutWidget4);
        doubleMSE_percentagereduction->setObjectName(QStringLiteral("doubleMSE_percentagereduction"));
        doubleMSE_percentagereduction->setDecimals(0);
        doubleMSE_percentagereduction->setSingleStep(1);
        doubleMSE_percentagereduction->setValue(40);

        horizontalLayout->addWidget(doubleMSE_percentagereduction);

        label_41 = new QLabel(layoutWidget4);
        label_41->setObjectName(QStringLiteral("label_41"));

        horizontalLayout->addWidget(label_41);

        frame_tmp = new QFrame(pageElectricalConductanceMSE);
        frame_tmp->setObjectName(QStringLiteral("frame_tmp"));
        frame_tmp->setEnabled(false);
        frame_tmp->setGeometry(QRect(70, 100, 591, 71));
        QPalette palette;
        QBrush brush(QColor(255, 255, 255, 255));
        brush.setStyle(Qt::SolidPattern);
        palette.setBrush(QPalette::Active, QPalette::Button, brush);
        palette.setBrush(QPalette::Active, QPalette::Base, brush);
        palette.setBrush(QPalette::Active, QPalette::Window, brush);
        palette.setBrush(QPalette::Inactive, QPalette::Button, brush);
        palette.setBrush(QPalette::Inactive, QPalette::Base, brush);
        palette.setBrush(QPalette::Inactive, QPalette::Window, brush);
        palette.setBrush(QPalette::Disabled, QPalette::Button, brush);
        palette.setBrush(QPalette::Disabled, QPalette::Base, brush);
        palette.setBrush(QPalette::Disabled, QPalette::Window, brush);
        frame_tmp->setPalette(palette);
        frame_tmp->setFrameShape(QFrame::StyledPanel);
        frame_tmp->setFrameShadow(QFrame::Raised);
        autocalPages->addWidget(pageElectricalConductanceMSE);
        pageGradualMap = new QWidget();
        pageGradualMap->setObjectName(QStringLiteral("pageGradualMap"));
        label_69 = new QLabel(pageGradualMap);
        label_69->setObjectName(QStringLiteral("label_69"));
        label_69->setGeometry(QRect(20, 80, 181, 31));
        label_69->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        gradualModelToExternalSelect = new QComboBox(pageGradualMap);
        gradualModelToExternalSelect->setObjectName(QStringLiteral("gradualModelToExternalSelect"));
        gradualModelToExternalSelect->setGeometry(QRect(200, 80, 79, 31));
        gradualExternalToModelSelect = new QComboBox(pageGradualMap);
        gradualExternalToModelSelect->setObjectName(QStringLiteral("gradualExternalToModelSelect"));
        gradualExternalToModelSelect->setGeometry(QRect(200, 130, 79, 31));
        label_70 = new QLabel(pageGradualMap);
        label_70->setObjectName(QStringLiteral("label_70"));
        label_70->setGeometry(QRect(20, 130, 191, 31));
        label_70->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        label_71 = new QLabel(pageGradualMap);
        label_71->setObjectName(QStringLiteral("label_71"));
        label_71->setGeometry(QRect(200, 30, 81, 31));
        label_71->setAlignment(Qt::AlignCenter);
        label_72 = new QLabel(pageGradualMap);
        label_72->setObjectName(QStringLiteral("label_72"));
        label_72->setGeometry(QRect(310, 30, 91, 31));
        label_72->setAlignment(Qt::AlignCenter);
        label_73 = new QLabel(pageGradualMap);
        label_73->setObjectName(QStringLiteral("label_73"));
        label_73->setGeometry(QRect(430, 30, 71, 31));
        label_73->setAlignment(Qt::AlignCenter);
        chemMap_MaxToExternal = new QDoubleSpinBox(pageGradualMap);
        chemMap_MaxToExternal->setObjectName(QStringLiteral("chemMap_MaxToExternal"));
        chemMap_MaxToExternal->setGeometry(QRect(320, 80, 68, 31));
        chemMap_MaxToExternal->setDecimals(3);
        chemMap_MaxToExternal->setSingleStep(0.01);
        chemMap_MaxToExternal->setValue(0.06);
        chemMap_MaxToModel = new QDoubleSpinBox(pageGradualMap);
        chemMap_MaxToModel->setObjectName(QStringLiteral("chemMap_MaxToModel"));
        chemMap_MaxToModel->setGeometry(QRect(320, 130, 68, 31));
        chemMap_MaxToModel->setDecimals(3);
        chemMap_MaxToModel->setSingleStep(0.1);
        chemMap_MaxToModel->setValue(0.4);
        chemMap_StepToExternal = new QDoubleSpinBox(pageGradualMap);
        chemMap_StepToExternal->setObjectName(QStringLiteral("chemMap_StepToExternal"));
        chemMap_StepToExternal->setGeometry(QRect(430, 80, 68, 31));
        chemMap_StepToExternal->setDecimals(3);
        chemMap_StepToExternal->setSingleStep(0.01);
        chemMap_StepToExternal->setValue(0.01);
        chemMap_StepToModel = new QDoubleSpinBox(pageGradualMap);
        chemMap_StepToModel->setObjectName(QStringLiteral("chemMap_StepToModel"));
        chemMap_StepToModel->setGeometry(QRect(430, 130, 68, 31));
        chemMap_StepToModel->setDecimals(3);
        chemMap_StepToModel->setSingleStep(0.05);
        chemMap_StepToModel->setValue(0.1);
        label_52 = new QLabel(pageGradualMap);
        label_52->setObjectName(QStringLiteral("label_52"));
        label_52->setGeometry(QRect(490, 30, 261, 16));
        label_52->setFont(font);
        label_52->setAlignment(Qt::AlignCenter);
        layoutWidget5 = new QWidget(pageGradualMap);
        layoutWidget5->setObjectName(QStringLiteral("layoutWidget5"));
        layoutWidget5->setGeometry(QRect(560, 60, 108, 25));
        horizontalLayout_8 = new QHBoxLayout(layoutWidget5);
        horizontalLayout_8->setSpacing(6);
        horizontalLayout_8->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_8->setObjectName(QStringLiteral("horizontalLayout_8"));
        horizontalLayout_8->setContentsMargins(0, 0, 0, 0);
        label_48 = new QLabel(layoutWidget5);
        label_48->setObjectName(QStringLiteral("label_48"));

        horizontalLayout_8->addWidget(label_48);

        doubleSynGrad_k1_map = new QDoubleSpinBox(layoutWidget5);
        doubleSynGrad_k1_map->setObjectName(QStringLiteral("doubleSynGrad_k1_map"));
        doubleSynGrad_k1_map->setDecimals(4);
        doubleSynGrad_k1_map->setMinimum(-99);
        doubleSynGrad_k1_map->setSingleStep(0.05);
        doubleSynGrad_k1_map->setValue(1);

        horizontalLayout_8->addWidget(doubleSynGrad_k1_map);

        layoutWidget6 = new QWidget(pageGradualMap);
        layoutWidget6->setObjectName(QStringLiteral("layoutWidget6"));
        layoutWidget6->setGeometry(QRect(560, 90, 108, 25));
        horizontalLayout_9 = new QHBoxLayout(layoutWidget6);
        horizontalLayout_9->setSpacing(6);
        horizontalLayout_9->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_9->setObjectName(QStringLiteral("horizontalLayout_9"));
        horizontalLayout_9->setContentsMargins(0, 0, 0, 0);
        label_49 = new QLabel(layoutWidget6);
        label_49->setObjectName(QStringLiteral("label_49"));

        horizontalLayout_9->addWidget(label_49);

        doubleSynGrad_k2_map = new QDoubleSpinBox(layoutWidget6);
        doubleSynGrad_k2_map->setObjectName(QStringLiteral("doubleSynGrad_k2_map"));
        doubleSynGrad_k2_map->setDecimals(4);
        doubleSynGrad_k2_map->setMinimum(-99);
        doubleSynGrad_k2_map->setSingleStep(0.005);
        doubleSynGrad_k2_map->setValue(0.03);

        horizontalLayout_9->addWidget(doubleSynGrad_k2_map);

        layoutWidget7 = new QWidget(pageGradualMap);
        layoutWidget7->setObjectName(QStringLiteral("layoutWidget7"));
        layoutWidget7->setGeometry(QRect(560, 120, 121, 27));
        horizontalLayout_10 = new QHBoxLayout(layoutWidget7);
        horizontalLayout_10->setSpacing(6);
        horizontalLayout_10->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_10->setObjectName(QStringLiteral("horizontalLayout_10"));
        horizontalLayout_10->setContentsMargins(0, 0, 0, 0);
        label_50 = new QLabel(layoutWidget7);
        label_50->setObjectName(QStringLiteral("label_50"));

        horizontalLayout_10->addWidget(label_50);

        horizontalLayout_5 = new QHBoxLayout();
        horizontalLayout_5->setSpacing(6);
        horizontalLayout_5->setObjectName(QStringLiteral("horizontalLayout_5"));
        doubleSynGrad_vfast_map = new QDoubleSpinBox(layoutWidget7);
        doubleSynGrad_vfast_map->setObjectName(QStringLiteral("doubleSynGrad_vfast_map"));
        doubleSynGrad_vfast_map->setDecimals(0);
        doubleSynGrad_vfast_map->setMinimum(0);
        doubleSynGrad_vfast_map->setMaximum(100);
        doubleSynGrad_vfast_map->setSingleStep(5);
        doubleSynGrad_vfast_map->setValue(25);

        horizontalLayout_5->addWidget(doubleSynGrad_vfast_map);

        label_53 = new QLabel(layoutWidget7);
        label_53->setObjectName(QStringLiteral("label_53"));

        horizontalLayout_5->addWidget(label_53);


        horizontalLayout_10->addLayout(horizontalLayout_5);

        layoutWidget8 = new QWidget(pageGradualMap);
        layoutWidget8->setObjectName(QStringLiteral("layoutWidget8"));
        layoutWidget8->setGeometry(QRect(560, 150, 120, 27));
        horizontalLayout_11 = new QHBoxLayout(layoutWidget8);
        horizontalLayout_11->setSpacing(6);
        horizontalLayout_11->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_11->setObjectName(QStringLiteral("horizontalLayout_11"));
        horizontalLayout_11->setContentsMargins(0, 0, 0, 0);
        label_51 = new QLabel(layoutWidget8);
        label_51->setObjectName(QStringLiteral("label_51"));

        horizontalLayout_11->addWidget(label_51);

        horizontalLayout_7 = new QHBoxLayout();
        horizontalLayout_7->setSpacing(6);
        horizontalLayout_7->setObjectName(QStringLiteral("horizontalLayout_7"));
        doubleSynGrad_vslow_map = new QDoubleSpinBox(layoutWidget8);
        doubleSynGrad_vslow_map->setObjectName(QStringLiteral("doubleSynGrad_vslow_map"));
        doubleSynGrad_vslow_map->setDecimals(0);
        doubleSynGrad_vslow_map->setMinimum(0);
        doubleSynGrad_vslow_map->setSingleStep(5);
        doubleSynGrad_vslow_map->setValue(50);

        horizontalLayout_7->addWidget(doubleSynGrad_vslow_map);

        label_55 = new QLabel(layoutWidget8);
        label_55->setObjectName(QStringLiteral("label_55"));

        horizontalLayout_7->addWidget(label_55);


        horizontalLayout_11->addLayout(horizontalLayout_7);

        autocalPages->addWidget(pageGradualMap);
        label_35 = new QLabel(centralWidget);
        label_35->setObjectName(QStringLiteral("label_35"));
        label_35->setGeometry(QRect(1068, 119, 121, 31));
        label_36 = new QLabel(centralWidget);
        label_36->setObjectName(QStringLiteral("label_36"));
        label_36->setGeometry(QRect(1073, 158, 111, 31));
        intFreq = new QSpinBox(centralWidget);
        intFreq->setObjectName(QStringLiteral("intFreq"));
        intFreq->setGeometry(QRect(1203, 38, 81, 31));
        intFreq->setSingleStep(10);
        intFreq->setValue(10);
        intTime = new QSpinBox(centralWidget);
        intTime->setObjectName(QStringLiteral("intTime"));
        intTime->setGeometry(QRect(1203, 78, 81, 31));
        intTime->setMaximum(99999);
        intTime->setSingleStep(10);
        intTime->setValue(10);
        intTimeBefore = new QSpinBox(centralWidget);
        intTimeBefore->setObjectName(QStringLiteral("intTimeBefore"));
        intTimeBefore->setGeometry(QRect(1203, 118, 81, 31));
        intTimeBefore->setMaximum(99999);
        intTimeBefore->setSingleStep(1);
        intTimeBefore->setValue(5);
        intTimeAfter = new QSpinBox(centralWidget);
        intTimeAfter->setObjectName(QStringLiteral("intTimeAfter"));
        intTimeAfter->setGeometry(QRect(1203, 158, 81, 31));
        intTimeAfter->setMaximum(99999);
        intTimeAfter->setSingleStep(1);
        intTimeAfter->setValue(5);
        label_37 = new QLabel(centralWidget);
        label_37->setObjectName(QStringLiteral("label_37"));
        label_37->setGeometry(QRect(1070, 380, 61, 15));
        autoDetect = new QCheckBox(centralWidget);
        autoDetect->setObjectName(QStringLiteral("autoDetect"));
        autoDetect->setGeometry(QRect(1216, 376, 101, 21));
        autoDetect->setChecked(true);
        doubleSecPerBurst = new QDoubleSpinBox(centralWidget);
        doubleSecPerBurst->setObjectName(QStringLiteral("doubleSecPerBurst"));
        doubleSecPerBurst->setEnabled(false);
        doubleSecPerBurst->setGeometry(QRect(1140, 375, 68, 24));
        doubleSecPerBurst->setDecimals(3);
        doubleSecPerBurst->setSingleStep(0.1);
        doubleSecPerBurst->setValue(0.25);
        frameAux = new QFrame(centralWidget);
        frameAux->setObjectName(QStringLiteral("frameAux"));
        frameAux->setGeometry(QRect(20, 20, 231, 101));
        frameAux->setFrameShape(QFrame::StyledPanel);
        frameAux->setFrameShadow(QFrame::Raised);
        frameAux2 = new QFrame(centralWidget);
        frameAux2->setObjectName(QStringLiteral("frameAux2"));
        frameAux2->setGeometry(QRect(20, 180, 231, 101));
        frameAux2->setFrameShape(QFrame::StyledPanel);
        frameAux2->setFrameShadow(QFrame::Raised);
        frameAux3 = new QFrame(centralWidget);
        frameAux3->setObjectName(QStringLiteral("frameAux3"));
        frameAux3->setGeometry(QRect(20, 470, 231, 101));
        frameAux3->setFrameShape(QFrame::StyledPanel);
        frameAux3->setFrameShadow(QFrame::Raised);
        frameAux4 = new QFrame(centralWidget);
        frameAux4->setObjectName(QStringLiteral("frameAux4"));
        frameAux4->setGeometry(QRect(1050, 20, 271, 461));
        frameAux4->setFrameShape(QFrame::StyledPanel);
        frameAux4->setFrameShadow(QFrame::Raised);
        simulate = new QPushButton(frameAux4);
        simulate->setObjectName(QStringLiteral("simulate"));
        simulate->setGeometry(QRect(160, 410, 82, 23));
        checkImp = new QCheckBox(frameAux4);
        checkImp->setObjectName(QStringLiteral("checkImp"));
        checkImp->setGeometry(QRect(30, 410, 88, 21));
        RTBiomanager->setCentralWidget(centralWidget);
        frameAux4->raise();
        frameAux->raise();
        frameAux2->raise();
        frameAux3->raise();
        frameSynapse->raise();
        label->raise();
        label_2->raise();
        label_3->raise();
        label_4->raise();
        label_5->raise();
        textChannelInput->raise();
        textChannelOutput->raise();
        label_6->raise();
        neuronModelCombo->raise();
        label_7->raise();
        synapseModelCombo->raise();
        frameNeuron->raise();
        label_43->raise();
        autocalCombo->raise();
        frameAutocal->raise();
        label_35->raise();
        label_36->raise();
        intFreq->raise();
        intTime->raise();
        intTimeBefore->raise();
        intTimeAfter->raise();
        label_37->raise();
        autoDetect->raise();
        doubleSecPerBurst->raise();

        retranslateUi(RTBiomanager);

        synapseModelPages->setCurrentIndex(0);
        neuronModelPages->setCurrentIndex(0);
        autocalPages->setCurrentIndex(0);
        gradualModelToExternalSelect->setCurrentIndex(1);
        gradualExternalToModelSelect->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(RTBiomanager);
    } // setupUi

    void retranslateUi(QMainWindow *RTBiomanager)
    {
        RTBiomanager->setWindowTitle(QApplication::translate("RTBiomanager", "RTBiomanager", Q_NULLPTR));
        label_27->setText(QApplication::translate("RTBiomanager", "Model to external neuron conductance: ", Q_NULLPTR));
        label_28->setText(QApplication::translate("RTBiomanager", "External neuron to model conductance:", Q_NULLPTR));
        checkAnti->setText(QApplication::translate("RTBiomanager", "Antiphase", Q_NULLPTR));
        label_29->setText(QApplication::translate("RTBiomanager", "To external neuron conductances:", Q_NULLPTR));
        label_31->setText(QApplication::translate("RTBiomanager", "To model neuron conductances:", Q_NULLPTR));
        label_30->setText(QApplication::translate("RTBiomanager", "Slow", Q_NULLPTR));
        label_32->setText(QApplication::translate("RTBiomanager", "Fast", Q_NULLPTR));
        label_33->setText(QApplication::translate("RTBiomanager", "Slow", Q_NULLPTR));
        label_34->setText(QApplication::translate("RTBiomanager", "Fast", Q_NULLPTR));
        label_38->setText(QApplication::translate("RTBiomanager", "Synapse parameters:", Q_NULLPTR));
        label_39->setText(QApplication::translate("RTBiomanager", "k1", Q_NULLPTR));
        label_40->setText(QApplication::translate("RTBiomanager", "k2", Q_NULLPTR));
        label_44->setText(QApplication::translate("RTBiomanager", "V fast", Q_NULLPTR));
        label_45->setText(QApplication::translate("RTBiomanager", "V slow", Q_NULLPTR));
        label_46->setText(QApplication::translate("RTBiomanager", "%", Q_NULLPTR));
        label_47->setText(QApplication::translate("RTBiomanager", "%", Q_NULLPTR));
        label->setText(QApplication::translate("RTBiomanager", "Frequency (kHz)", Q_NULLPTR));
        label_2->setText(QApplication::translate("RTBiomanager", "Duration (s)", Q_NULLPTR));
        label_3->setText(QApplication::translate("RTBiomanager", "Channels (separated by commas):", Q_NULLPTR));
        label_4->setText(QApplication::translate("RTBiomanager", "Input", Q_NULLPTR));
        label_5->setText(QApplication::translate("RTBiomanager", "Output", Q_NULLPTR));
        textChannelInput->setPlainText(QApplication::translate("RTBiomanager", "0", Q_NULLPTR));
        textChannelOutput->setPlainText(QApplication::translate("RTBiomanager", "0", Q_NULLPTR));
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
        textBrowser->setHtml(QApplication::translate("RTBiomanager", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"</style></head><body style=\" font-family:'Sans'; font-size:10pt; font-weight:400; font-style:normal;\">\n"
"<p align=\"center\" style=\"-qt-paragraph-type:empty; margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><br /></p>\n"
"<p align=\"center\" style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-size:12pt; font-weight:600;\">No calibration &amp; exploration (c&amp;e) mode selected.</span></p>\n"
"<p align=\"center\" style=\"-qt-paragraph-type:empty; margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px; font-size:12pt; font-weight:600;\"><br /></p>\n"
"<p align=\"center\" style=\" margin-top:0px"
                        "; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-size:12pt; font-style:italic;\">Choose mode in the left selector.</span></p>\n"
"<p align=\"center\" style=\"-qt-paragraph-type:empty; margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px; font-size:12pt; font-style:italic;\"><br /></p>\n"
"<p align=\"center\" style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-size:12pt; text-decoration: underline;\">Note</span><span style=\" font-size:12pt;\">: c&amp;e auto-select configurations and </span></p>\n"
"<p align=\"center\" style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-size:12pt;\">change parameters during the experiment.</span></p>\n"
"<p align=\"center\" style=\"-qt-paragraph-type:empty; margin-top:0px; margin-bottom:0px; "
                        "margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px; font-size:12pt;\"><br /></p>\n"
"<p align=\"center\" style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-size:12pt;\">For more information see documentation:</span></p>\n"
"<p align=\"center\" style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-size:12pt;\">(!ref)</span></p></body></html>", Q_NULLPTR));
        label_42->setText(QApplication::translate("RTBiomanager", "%", Q_NULLPTR));
        radioButtonMSE_percentagereduction->setText(QApplication::translate("RTBiomanager", "MSE percentage reduction.              Reduction target =", Q_NULLPTR));
        radioButtonMSE_slopereduction->setText(QApplication::translate("RTBiomanager", "MSE slope.                                        Reduction target =", Q_NULLPTR));
        label_41->setText(QApplication::translate("RTBiomanager", "%", Q_NULLPTR));
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
        label_52->setText(QApplication::translate("RTBiomanager", "Synapse parameters:", Q_NULLPTR));
        label_48->setText(QApplication::translate("RTBiomanager", "k1", Q_NULLPTR));
        label_49->setText(QApplication::translate("RTBiomanager", "k2", Q_NULLPTR));
        label_50->setText(QApplication::translate("RTBiomanager", "V fast ", Q_NULLPTR));
        label_53->setText(QApplication::translate("RTBiomanager", "%", Q_NULLPTR));
        label_51->setText(QApplication::translate("RTBiomanager", "V slow", Q_NULLPTR));
        label_55->setText(QApplication::translate("RTBiomanager", "%", Q_NULLPTR));
        label_35->setText(QApplication::translate("RTBiomanager", "Before control (s)", Q_NULLPTR));
        label_36->setText(QApplication::translate("RTBiomanager", "After control (s)", Q_NULLPTR));
        label_37->setText(QApplication::translate("RTBiomanager", "s/Burst", Q_NULLPTR));
        autoDetect->setText(QApplication::translate("RTBiomanager", "Auto detect", Q_NULLPTR));
        simulate->setText(QApplication::translate("RTBiomanager", "Start", Q_NULLPTR));
        checkImp->setText(QApplication::translate("RTBiomanager", "Important", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class RTBiomanager: public Ui_RTBiomanager {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_RTBIOMANAGER_H
