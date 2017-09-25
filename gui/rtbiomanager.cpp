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
    double x_ini, y_ini, z_ini, e;
    int calib = 0, anti = 0, freq = 0, dur = 0;
    char * inputChannels, * outputChannels;
    std::string aux_in, aux_out;

    /* Izhikevich params */
    double a, b, c, d;

    /* Hindmarsh-Rose params */
    double r, s;

    /* Rulkov params */
    double alpha, sigma, mu;

    /* Synapse params */
    double * modelToReal;
    double * externalToModel;

    neuronIndex = ui->neuronModelPages->currentIndex();
    synapseIndex = ui->synapseModelPages->currentIndex();

    switch (neuronIndex) {
        case 0: //Izhikevich
            x_ini = ui->textIzVIni->toPlainText().toDouble();
            y_ini = ui->textIzUIni->toPlainText().toDouble();

            a = ui->textIzA->toPlainText().toDouble();
            b = ui->textIzB->toPlainText().toDouble();
            c = ui->textIzC->toPlainText().toDouble();
            d = ui->textIzD->toPlainText().toDouble();

            e = ui->textIzI->toPlainText().toDouble();
            break;
        case 1: //Hindmarsh-Rose
            x_ini = ui->textHrXIni->toPlainText().toDouble();
            y_ini = ui->textHrYIni->toPlainText().toDouble();
            z_ini = ui->textHrZIni->toPlainText().toDouble();

            r = ui->textHrR->toPlainText().toDouble();
            s = ui->textHrS->toPlainText().toDouble();

            e = ui->textHrI->toPlainText().toDouble();
            break;
        case 2: //Rulkov
            x_ini = ui->textRlkXIni->toPlainText().toDouble();
            y_ini = ui->textRlkYIni->toPlainText().toDouble();

            alpha = ui->textRlkAlpha->toPlainText().toDouble();
            sigma = ui->textRlkSigma->toPlainText().toDouble();
            mu = ui->textRlkMu->toPlainText().toDouble();

            e = ui->textRlkI->toPlainText().toDouble();
            break;
        default:
            break;
    }

    switch (synapseIndex) {
        case 0: //Electrical
            modelToReal = (double *) malloc (sizeof(double));
            modelToReal[0] = ui->textSynElec_gMtoE->toPlainText().toDouble();

            externalToModel = (double *) malloc (sizeof(double));
            externalToModel[0] = ui->textSynElec_gEtoM->toPlainText().toDouble();
            break;
        case 1: //Gradual chemical
            modelToReal = (double *) malloc (sizeof(double) * 2);
            modelToReal[0] = ui->textSynGrad_gMtoE_fast->toPlainText().toDouble();
            modelToReal[1] = ui->textSynGrad_gMtoE_slow->toPlainText().toDouble();

            externalToModel = (double *) malloc (sizeof(double) * 2);
            externalToModel[0] = ui->textSynGrad_gEtoM_fast->toPlainText().toDouble();
            externalToModel[1] = ui->textSynGrad_gEtoM_slow->toPlainText().toDouble();
            break;

        default:
            break;
    }


    calib = ui->checkCalib->isChecked();
    anti = ui->checkAnti->isChecked();
    freq = ui->textFreq->toPlainText().toInt();
    dur = ui->textTime->toPlainText().toInt();
    aux_in = ui->textChannelInput->toPlainText().toStdString();
    aux_out = ui->textChannelOutput->toPlainText().toStdString();

    inputChannels = (char *) malloc (sizeof(char) * aux_in.length() + 1);
    outputChannels = (char *) malloc (sizeof(char) * aux_out.length() + 1);

    strcpy(inputChannels, aux_in.c_str());
    strcpy(outputChannels, aux_out.c_str());

    int ret = clamp(freq, dur, neuronIndex, synapseIndex,calib, anti, 0, inputChannels, outputChannels);

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
