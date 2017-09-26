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
    int neuronIndex = 0, synapseIndex = 0;

    /* Common neuron models params */
    double freq = 0;
    int calib = 0, anti = 0, dur = 0;
    char * inputChannels, * outputChannels;
    std::string aux_in, aux_out;
    double * vars, * params;

    /* Synapse params */
    double * modelToReal;
    double * externalToModel;
    double * gVirtualToReal;
    double * gRealToVirtual;

    neuronIndex = ui->neuronModelPages->currentIndex();
    synapseIndex = ui->synapseModelPages->currentIndex();


    calib = ui->checkCalib->isChecked();
    anti = ui->checkAnti->isChecked();
    freq = ui->textFreq->toPlainText().toDouble() * 1000;
    dur = ui->textTime->toPlainText().toInt();
    aux_in = ui->textChannelInput->toPlainText().toStdString();
    aux_out = ui->textChannelOutput->toPlainText().toStdString();

    inputChannels = (char *) malloc (sizeof(char) * aux_in.length() + 1);
    outputChannels = (char *) malloc (sizeof(char) * aux_out.length() + 1);

    strcpy(inputChannels, aux_in.c_str());
    strcpy(outputChannels, aux_out.c_str());

    switch (neuronIndex) {
        case IZHIKEVICH: //Izhikevich
            vars = (double*) malloc (sizeof(double) * 2);
            params = (double *) malloc (sizeof(double) * 5);

            vars[X] = ui->textIzVIni->toPlainText().toDouble();
            vars[Y] = ui->textIzUIni->toPlainText().toDouble();

            params[A_IZ] = ui->textIzA->toPlainText().toDouble();
            params[B_IZ] = ui->textIzB->toPlainText().toDouble();
            params[C_IZ] = ui->textIzC->toPlainText().toDouble();
            params[D_IZ] = ui->textIzD->toPlainText().toDouble();
            params[I_IZ] = ui->textIzI->toPlainText().toDouble();

            break;
        case HR: //Hindmarsh-Rose
            vars = (double*) malloc (sizeof(double) * 3);
            params = (double *) malloc (sizeof(double) * 3);

            vars[X] = ui->textHrXIni->toPlainText().toDouble();
            vars[Y] = ui->textHrYIni->toPlainText().toDouble();
            vars[Z] = ui->textHrZIni->toPlainText().toDouble();

            params[R_HR] = ui->textHrR->toPlainText().toDouble();
            params[S_HR] = ui->textHrS->toPlainText().toDouble();
            params[I_HR] = ui->textHrI->toPlainText().toDouble();

            break;
        case RLK: //Rulkov
            vars = (double*) malloc (sizeof(double) * 2);
            params = (double *) malloc (sizeof(double) * 8);

            vars[X] = ui->textRlkXIni->toPlainText().toDouble();
            vars[Y] = ui->textRlkYIni->toPlainText().toDouble();

            params[ALPHA_RLK] = ui->textRlkAlpha->toPlainText().toDouble();
            params[SIGMA_RLK] = ui->textRlkSigma->toPlainText().toDouble();
            params[MU_RLK] = ui->textRlkMu->toPlainText().toDouble();
            params[I_RLK] = ui->textRlkI->toPlainText().toDouble();
            params[OLD_RLK] = 0.0;
            params[PTS_RLK] = freq;
            params[J_RLK] = ((params[PTS_RLK] - 400) / 400) + 1;
            params[INTER_RLK] = 0.0;

            break;
        default:
            break;
    }

    switch (synapseIndex) {
        case ELECTRIC: //Electrical
            modelToReal = (double *) malloc (sizeof(double));
            modelToReal[0] = ui->textSynElec_gMtoE->toPlainText().toDouble();

            externalToModel = (double *) malloc (sizeof(double));
            externalToModel[0] = ui->textSynElec_gEtoM->toPlainText().toDouble();


            gVirtualToReal = (double *) malloc (sizeof(double) * 1);
            gRealToVirtual = (double *) malloc (sizeof(double) * 1);
            gVirtualToReal[0] = ui->textSynElec_gMtoE->toPlainText().toDouble();
            gRealToVirtual[0] = ui->textSynElec_gEtoM->toPlainText().toDouble();

            break;
        case CHEMICAL: //Gradual chemical
            modelToReal = (double *) malloc (sizeof(double) * 2);
            modelToReal[0] = ui->textSynGrad_gMtoE_fast->toPlainText().toDouble();
            modelToReal[1] = ui->textSynGrad_gMtoE_slow->toPlainText().toDouble();

            externalToModel = (double *) malloc (sizeof(double) * 2);
            externalToModel[0] = ui->textSynGrad_gEtoM_fast->toPlainText().toDouble();
            externalToModel[1] = ui->textSynGrad_gEtoM_slow->toPlainText().toDouble();

            gVirtualToReal = (double *) malloc (sizeof(double) * 2);
            gRealToVirtual = (double *) malloc (sizeof(double) * 2);

            gVirtualToReal[G_FAST] = ui->textSynGrad_gMtoE_fast->toPlainText().toDouble();
            gVirtualToReal[G_SLOW] = ui->textSynGrad_gMtoE_slow->toPlainText().toDouble();
            gRealToVirtual[G_FAST] = ui->textSynGrad_gEtoM_fast->toPlainText().toDouble();
            gRealToVirtual[G_SLOW] = ui->textSynGrad_gEtoM_slow->toPlainText().toDouble();

            break;

        default:
            break;
    }



    int ret = clamp(freq, dur, neuronIndex, synapseIndex,calib, anti, 0, inputChannels, outputChannels, vars, params, gVirtualToReal, gRealToVirtual);

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
