#include "rthybrid.h"
#include "ui_rthybrid.h"
#include <QMessageBox>
#include <string>
#include "clamp/includes/clamp.h"
#include <QSound>
#include <QMovie>

RTHybrid::RTHybrid(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::RTHybrid)
{
    ui->setupUi(this);
    this->setFixedSize(this->width(),this->height());

    movie = new QMovie("resources/neuron.gif");
    ui->label_gif->setMovie(movie);
    movie->stop();
}

RTHybrid::~RTHybrid()
{
    delete ui;
}

void RTHybrid::on_simulate_clicked()
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
    args.mode_auto_cal = ui->autocalPages->currentIndex();

    args.imp = ui->checkImp->isChecked();

    args.freq = ui->intFreq->value() * 1000.0;
    args.time_var = ui->intTime->value();
    args.before = ui->intTimeBefore->value();
    args.after = ui->intTimeAfter->value();
    if (!ui->autoDetect->isChecked()) {
        args.firing_rate = ui->doubleSecPerBurst->value();
    } else {
        args.firing_rate = -1;
    }

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

            args.vars[X] = ui->doubleIzVini->value();
            args.vars[Y] = ui->doubleIzUini->value();

            args.params[A_IZ] = ui->doubleIzA->value();
            args.params[B_IZ] = ui->doubleIzB->value();
            args.params[C_IZ] = ui->doubleIzC->value();
            args.params[D_IZ] = ui->doubleIzD->value();
            args.params[I_IZ] = ui->doubleIzI->value();

            break;
        case HR: //Hindmarsh-Rose
            args.vars = (double*) malloc (sizeof(double) * 3);
            args.params = (double *) malloc (sizeof(double) * 3);

            args.vars[X] = ui->doubleHrXIni->value();
            args.vars[Y] = ui->doubleHrYIni->value();
            args.vars[Z] = ui->doubleHrZIni->value();

            args.params[R_HR] = ui->doubleHrR->value();
            args.params[S_HR] = ui->doubleHrS->value();
            args.params[I_HR] = ui->doubleHrI->value();

            break;
        case RLK: //Rulkov
            args.vars = (double*) malloc (sizeof(double) * 2);
            args.params = (double *) malloc (sizeof(double) * 8);

            args.vars[X] = ui->doubleRlkXIni->value();
            args.vars[Y] = ui->doubleRlkYIni->value();

            args.params[ALPHA_RLK] = ui->doubleRlkAlpha->value();
            args.params[SIGMA_RLK] = ui->doubleRlkSigma->value();
            args.params[MU_RLK] = ui->doubleRlkMu->value();
            args.params[I_RLK] = ui->doubleRlkI->value();

            break;
        default:
            break;
    }

    //args.anti = false;

    if (args.mode_auto_cal == 0){
        switch (args.synapse) {
            case ELECTRIC: //Electrical
                {
                /*args.g_virtual_to_real = (double *) malloc (sizeof(double) * 1);
                args.g_real_to_virtual = (double *) malloc (sizeof(double) * 1);
                args.g_virtual_to_real[0] = ui->doubleSynElec_gMtoE->value();
                args.g_real_to_virtual[0] = ui->doubleSynElec_gEtoM->value();
                args.anti = ui->checkAnti->isChecked();*/

                args.syn_args_live_to_model = (syn_elec_args *) malloc (sizeof(syn_elec_args));
                args.syn_args_model_to_live = (syn_elec_args *) malloc (sizeof(syn_elec_args));

                syn_elec_args * args_live_to_model_elec = (syn_elec_args *) args.syn_args_live_to_model;
                syn_elec_args * args_model_to_live_elec = (syn_elec_args *) args.syn_args_model_to_live;

                args_live_to_model_elec->g[ELEC_G] = ui->doubleSynElec_gEtoM->value();
                args_model_to_live_elec->g[ELEC_G] = ui->doubleSynElec_gMtoE->value();

                if (ui->checkAnti->isChecked()) {
                    args_model_to_live_elec->anti = -1;
                    args_live_to_model_elec->anti = -1;
                } else {
                    args_model_to_live_elec->anti = 1;
                    args_live_to_model_elec->anti = 1;
                }


                break;
                }
            case GOLOWASCH: //Gradual chemical
                {
                /*args.g_virtual_to_real = (double *) malloc (sizeof(double) * 1);
                args.g_real_to_virtual = (double *) malloc (sizeof(double) * 1);*/

                args.syn_args_live_to_model = (syn_gl_args *) malloc (sizeof(syn_gl_args));
                args.syn_args_model_to_live = (syn_gl_args *) malloc (sizeof(syn_gl_args));

                syn_gl_args * args_live_to_model_gl = (syn_gl_args *) args.syn_args_live_to_model;
                syn_gl_args * args_model_to_live_gl = (syn_gl_args *) args.syn_args_model_to_live;

                args_live_to_model_gl->g[GL_G_FAST] = ui->doubleSpinBox_gl_EtoM_fast_g->value();
                args_live_to_model_gl->g[GL_G_SLOW] = ui->doubleSpinBox_gl_EtoM_slow_g->value();
                args_live_to_model_gl->v_fast = ui->spinBox_gl_EtoM_fast_vth->value();
                args_live_to_model_gl->v_slow = ui->spinBox_gl_EtoM_slow_vth->value();
                args_live_to_model_gl->k1 = ui->doubleSpinBox_gl_EtoM_slow_k1->value();
                args_live_to_model_gl->k2 = ui->doubleSpinBox_gl_EtoM_slow_k2->value();

                args_model_to_live_gl->g[GL_G_FAST] = ui->doubleSpinBox_gl_MtoE_fast_g->value();
                args_model_to_live_gl->g[GL_G_SLOW] = ui->doubleSpinBox_gl_MtoE_slow_g->value();
                args_model_to_live_gl->v_fast = ui->spinBox_gl_MtoE_fast_vth->value();
                args_model_to_live_gl->v_slow = ui->spinBox_gl_MtoE_slow_vth->value();
                args_model_to_live_gl->k1 = ui->doubleSpinBox_gl_MtoE_slow_k1->value();
                args_model_to_live_gl->k2 = ui->doubleSpinBox_gl_MtoE_slow_k2->value();

                /*args.g_virtual_to_real[0] = ui
                args.g_real_to_virtual[0] = ui->doubleSynGrad_gEtoM_fast->value();

                args.syn_gradual_k1 = ui->doubleSynGrad_k1->value();
                args.syn_gradual_k2 = ui->doubleSynGrad_k2->value();
                args.syn_gradual_vfast = ui->doubleSynGrad_vfast->value();
                args.syn_gradual_vslow = ui->doubleSynGrad_vslow->value();*/

                break;
            }

            case PRINZ: //Prinz graded chemical
                {
                /*args.g_virtual_to_real = (double *) malloc (sizeof(double) * 1);
                args.g_real_to_virtual = (double *) malloc (sizeof(double) * 1);

                args.g_virtual_to_real[0] = ui->doubleSynPrinz_gMtoE->value();
                args.g_real_to_virtual[0] = ui->doubleSynPrinz_gEtoM->value();

                args.syn_gradual_k1 = ui->doubleSynPrinz_kEtoM->value();
                args.syn_gradual_k2 = ui->doubleSynPrinz_kMtoE->value();
                args.syn_gradual_vfast = ui->doubleSynPrinz_delta->value();
                args.syn_gradual_vslow = ui->doubleSynPrinz_vth->value();*/

                break;
                }

            default:
                break;
        }
    } else {
        switch (args.mode_auto_cal) {

            case 1: //Electric conductance MSE
            {
                args.synapse = ELECTRIC;

                args.syn_args_live_to_model = (syn_elec_args *) malloc (sizeof(syn_elec_args));
                args.syn_args_model_to_live = (syn_elec_args *) malloc (sizeof(syn_elec_args));

                syn_elec_args * args_live_to_model_elec = (syn_elec_args *) args.syn_args_live_to_model;
                syn_elec_args * args_model_to_live_elec = (syn_elec_args *) args.syn_args_model_to_live;

                args_live_to_model_elec->g[ELEC_G] = 0.0;
                args_model_to_live_elec->g[ELEC_G] = 0.0;

                args_model_to_live_elec->anti = 1;
                args_live_to_model_elec->anti = 1;

                if (ui->radioButtonMSE_percentagereduction->isChecked()==true){

                    args.mode_auto_cal = 1;
                    args.auto_cal_val_1 = ui->doubleMSE_percentagereduction->value();

                } else if (ui->radioButtonMSE_slopereduction->isChecked()==true){

                    args.mode_auto_cal = 2;
                    args.auto_cal_val_1 = ui->doubleMSE_slopereduction->value();

                }


                break;
            }

            case 2: //Gradual MAP
            {
                args.mode_auto_cal = 7;
                args.synapse = GOLOWASCH;

                args.syn_args_live_to_model = (syn_gl_args *) malloc (sizeof(syn_gl_args));
                args.syn_args_model_to_live = (syn_gl_args *) malloc (sizeof(syn_gl_args));

                syn_gl_args * args_live_to_model_gl = (syn_gl_args *) args.syn_args_live_to_model;
                syn_gl_args * args_model_to_live_gl = (syn_gl_args *) args.syn_args_model_to_live;

                if (ui->gradualModelToExternalSelect->currentIndex() == GL_G_FAST){
                    args_model_to_live_gl->g[GL_G_FAST] = ui->chemMap_MaxToExternal->value();
                    args_model_to_live_gl->g[GL_G_SLOW] = 0.0;
                }else{
                    args_model_to_live_gl->g[GL_G_FAST] = 0.0;
                    args_model_to_live_gl->g[GL_G_SLOW] = ui->chemMap_MaxToExternal->value();
                }

                if (ui->gradualExternalToModelSelect->currentIndex() == GL_G_FAST){
                    args_live_to_model_gl->g[GL_G_FAST] = ui->chemMap_MaxToModel->value();
                    args_live_to_model_gl->g[GL_G_SLOW] = 0.0;
                }else{
                    args_live_to_model_gl->g[GL_G_FAST] = 0.0;
                    args_live_to_model_gl->g[GL_G_SLOW] = ui->chemMap_MaxToModel->value();
                }

                args.step_v_to_r = ui->chemMap_StepToExternal->value();
                args.step_r_to_v = ui->chemMap_StepToModel->value();


                args_live_to_model_gl->v_fast = ui->doubleSynGrad_vfast_map->value();
                args_live_to_model_gl->v_slow = ui->doubleSynGrad_vslow_map->value();
                args_live_to_model_gl->k1 = ui->doubleSynGrad_k1_map->value();
                args_live_to_model_gl->k2 = ui->doubleSynGrad_k2_map->value();

                args_model_to_live_gl->v_fast = ui->doubleSynGrad_vfast_map->value();
                args_model_to_live_gl->v_slow = ui->doubleSynGrad_vslow_map->value();
                args_model_to_live_gl->k1 = ui->doubleSynGrad_k1_map->value();
                args_model_to_live_gl->k2 = ui->doubleSynGrad_k2_map->value();

                break;
            }

            default:
                args.mode_auto_cal = 0;
                break;
        }
    }




    movie->start();
    ui->centralWidget->setStyleSheet("#centralWidget{ background-color: qlineargradient(spread:pad, x1:0.5, y1:1, x2:0.5, y2:0, stop:0 rgba(13, 71, 161, 255), stop:1 rgba(95, 134, 194, 255)); }");
    ui->centralWidget->repaint();
    int ret = clamp(&args);
    ui->centralWidget->setStyleSheet("#centralWidget{ background-color: rgb(230, 230, 230); }");
    movie->stop();

    if(ui->checksound->isChecked())
        QSound::play("resources/epic_alarm.wav");
    QMessageBox msgBox;
    msgBox.setText("Clamp finished");

    if (ret == 1) {
        msgBox.setInformativeText("OK");
    } else {
        msgBox.setInformativeText("ERR");
    }

    msgBox.exec();
}

void RTHybrid::on_neuronModelCombo_activated(int index)
{
    ui->neuronModelPages->setCurrentIndex(index);
}

void RTHybrid::on_synapseModelCombo_activated(int index)
{
    ui->synapseModelPages->setCurrentIndex(index);
}

void RTHybrid::on_autocalCombo_activated(int index)
{
    ui->autocalPages->setCurrentIndex(index);
    if(index!=0){
        //General stuff for all autocals
        ui->synapseModelCombo->setEnabled(false);
        ui->frameSynapse->setEnabled(false);
        //Particular behaviors
        if(index==2){
            ui->intTime->setEnabled(false);
        }else{
            ui->intTime->setEnabled(true);
        }
    }else{
        //Autocal modes off
        ui->synapseModelCombo->setEnabled(true);
        ui->frameSynapse->setEnabled(true);
        ui->intTime->setEnabled(true);
    }
}

void RTHybrid::on_autoDetect_clicked()
{
    if (ui->autoDetect->isChecked()) {
        ui->doubleSecPerBurst->setEnabled(false);
    } else {
        ui->doubleSecPerBurst->setEnabled(true);
    }
}
