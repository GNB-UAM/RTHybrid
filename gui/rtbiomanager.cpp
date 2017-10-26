#include "rtbiomanager.h"
#include "ui_rtbiomanager.h"
#include <QMessageBox>
#include <string>
#include "clamp/includes/clamp.h"

RTBiomanager::RTBiomanager(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::RTBiomanager)
{
    ui->setupUi(this);

}

RTBiomanager::~RTBiomanager()
{
    delete ui;
}



void RTBiomanager::on_simulate_clicked()
{
    clamp_args args;

    int autocalIndex=0;
    std::string aux_in, aux_out;


    args.input = NULL;
    args.output = NULL;
    args.vars = NULL;
    args.params = NULL;
    args.g_real_to_virtual = NULL;
    args.g_virtual_to_real = NULL;

    args.model = ui->neuronModelPages->currentIndex();
    args.synapse = ui->synapseModelPages->currentIndex();
    autocalIndex = ui->autocalPages->currentIndex();

    args.imp = ui->checkImp->isChecked();
    args.anti = ui->checkAnti->isChecked();
    args.freq = ui->textFreq->toPlainText().toDouble() * 1000;
    args.time_var = ui->textTime->toPlainText().toInt();
    aux_in = ui->textChannelInput->toPlainText().toStdString();
    aux_out = ui->textChannelOutput->toPlainText().toStdString();

    args.input = (char *) malloc (sizeof(char) * aux_in.length() + 1);
    args.output = (char *) malloc (sizeof(char) * aux_out.length() + 1);

    strcpy(args.input, aux_in.c_str());
    strcpy(args.output, aux_out.c_str());

    switch (args.model) {
        case IZHIKEVICH: //Izhikevich
            args.vars = (double*) malloc (sizeof(double) * 2);
            args.params = (double *) malloc (sizeof(double) * 5);

            args.vars[X] = ui->textIzVIni->toPlainText().toDouble();
            args.vars[Y] = ui->textIzUIni->toPlainText().toDouble();

            args.params[A_IZ] = ui->textIzA->toPlainText().toDouble();
            args.params[B_IZ] = ui->textIzB->toPlainText().toDouble();
            args.params[C_IZ] = ui->textIzC->toPlainText().toDouble();
            args.params[D_IZ] = ui->textIzD->toPlainText().toDouble();
            args.params[I_IZ] = ui->textIzI->toPlainText().toDouble();

            break;
        case HR: //Hindmarsh-Rose
            args.vars = (double*) malloc (sizeof(double) * 3);
            args.params = (double *) malloc (sizeof(double) * 3);

            args.vars[X] = ui->textHrXIni->toPlainText().toDouble();
            args.vars[Y] = ui->textHrYIni->toPlainText().toDouble();
            args.vars[Z] = ui->textHrZIni->toPlainText().toDouble();

            args.params[R_HR] = ui->textHrR->toPlainText().toDouble();
            args.params[S_HR] = ui->textHrS->toPlainText().toDouble();
            args.params[I_HR] = ui->textHrI->toPlainText().toDouble();

            break;
        case RLK: //Rulkov
            args.vars = (double*) malloc (sizeof(double) * 2);
            args.params = (double *) malloc (sizeof(double) * 8);

            args.vars[X] = ui->textRlkXIni->toPlainText().toDouble();
            args.vars[Y] = ui->textRlkYIni->toPlainText().toDouble();

            args.params[ALPHA_RLK] = ui->textRlkAlpha->toPlainText().toDouble();
            args.params[SIGMA_RLK] = ui->textRlkSigma->toPlainText().toDouble();
            args.params[MU_RLK] = ui->textRlkMu->toPlainText().toDouble();
            args.params[I_RLK] = ui->textRlkI->toPlainText().toDouble();

            break;
        default:
            break;
    }

    if (autocalIndex == 0){
        switch (args.synapse) {
            case ELECTRIC: //Electrical
                args.g_virtual_to_real = (double *) malloc (sizeof(double) * 1);
                args.g_real_to_virtual = (double *) malloc (sizeof(double) * 1);
                args.g_virtual_to_real[0] = ui->textSynElec_gMtoE->toPlainText().toDouble();
                args.g_real_to_virtual[0] = ui->textSynElec_gEtoM->toPlainText().toDouble();


                break;
            case CHEMICAL: //Gradual chemical
                args.g_virtual_to_real = (double *) malloc (sizeof(double) * 2);
                args.g_real_to_virtual = (double *) malloc (sizeof(double) * 2);

                args.g_virtual_to_real[G_FAST] = ui->textSynGrad_gMtoE_fast->toPlainText().toDouble();
                args.g_virtual_to_real[G_SLOW] = ui->textSynGrad_gMtoE_slow->toPlainText().toDouble();
                args.g_real_to_virtual[G_FAST] = ui->textSynGrad_gEtoM_fast->toPlainText().toDouble();
                args.g_real_to_virtual[G_SLOW] = ui->textSynGrad_gEtoM_slow->toPlainText().toDouble();

                break;

            default:
                break;
        }
    }

    switch (autocalIndex) {
        case 1: //Electric conductance MSE
            args.mode_auto_cal = 1;

        case 2: //Gradual MAP

            args.mode_auto_cal = 7;
            args.synapse = CHEMICAL;

            args.g_virtual_to_real = (double *) malloc (sizeof(double) * 2);
            args.g_real_to_virtual = (double *) malloc (sizeof(double) * 2);

            if (ui->gradualModelToExternalSelect->currentIndex() == G_FAST){
                args.g_virtual_to_real[G_FAST] = ui->chemMap_MaxToExternal->value();
                args.g_virtual_to_real[G_SLOW] = 0;
            }else{
                args.g_virtual_to_real[G_SLOW] = ui->chemMap_MaxToExternal->value();
                args.g_virtual_to_real[G_FAST] = 0;
            }

            if (ui->gradualExternalToModelSelect->currentIndex() == G_FAST){
                args.g_real_to_virtual[G_FAST] = ui->chemMap_MaxToModel->value();
                args.g_real_to_virtual[G_SLOW] = 0;
            }else{
                args.g_real_to_virtual[G_SLOW] = ui->chemMap_MaxToModel->value();
                args.g_real_to_virtual[G_FAST] = 0;
            }

            args.step_v_to_r = ui->chemMap_StepToExternal->value();
            args.step_r_to_v = ui->chemMap_StepToModel->value();

        default:
            break;
    }





    int ret = clamp(&args);

    QMessageBox msgBox;
    msgBox.setText("Clamp finished");

    if (ret == 1) {
        msgBox.setInformativeText("OK");
    } else {
        msgBox.setInformativeText("ERR");
    }

    msgBox.exec();


}



void RTBiomanager::on_neuronModelCombo_activated(int index)
{
    ui->neuronModelPages->setCurrentIndex(index);


}

void RTBiomanager::on_synapseModelCombo_activated(int index)
{
    ui->synapseModelPages->setCurrentIndex(index);
}

void RTBiomanager::on_autocalCombo_activated(int index)
{
    ui->autocalPages->setCurrentIndex(index);
    if(index!=0){
        ui->synapseModelCombo->setEnabled(false);
        ui->frameSynapse->setEnabled(false);
    }else{
        ui->synapseModelCombo->setEnabled(true);
        ui->frameSynapse->setEnabled(true);
    }
}
