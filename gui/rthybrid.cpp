#include "rthybrid.h"

#include <QMessageBox>
#include <string>
#include <QSound>
#include <QMovie>
#include <QMainWindow>
#include <QCloseEvent>
#include "model_library/Izhikevich_2003/nm_gui_izhikevich_2003.h"


RTHybrid::RTHybrid(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::RTHybrid)
{
    ui->setupUi(this);
    this->setFixedSize(this->width(),this->height());

    this->args.vars = NULL;
    this->args.params = NULL;

    /*movie = new QMovie("resources/neuron.gif");
    ui->label_gif->setMovie(movie);
    movie->stop();*/

    ui->centralWidget->setStyleSheet("#centralWidget{ background-color: qlineargradient(spread:pad, x1:0.5, y1:1, x2:0.5, y2:0, stop:0 rgba(13, 71, 161, 255), stop:1 rgba(95, 134, 194, 255)); }");
    ui->centralWidget->repaint();

    /*QPixmap pixmapTarget = QPixmap("resources/interaccion.png");
    pixmapTarget = pixmapTarget.scaled(261, 147, Qt::KeepAspectRatio, Qt::SmoothTransformation);
    ui->label_gif->setPixmap(pixmapTarget);*/

    QPixmap pixmapTarget = QPixmap("resources/interaction_living.png");
    pixmapTarget = pixmapTarget.scaled(121, 121, Qt::KeepAspectRatio, Qt::SmoothTransformation);
    ui->label_interaction_living->setPixmap(pixmapTarget);
}

RTHybrid::~RTHybrid()
{
    delete ui;
}

void RTHybrid::closeEvent (QCloseEvent *event)
{
    if (this->isClampRunning) {
        QMessageBox::StandardButton resBtn = QMessageBox::question( this, "RTHybrid",
                                                                    tr("An experiment is running. Are you sure you want to exit?\n"),
                                                                    QMessageBox::No | QMessageBox::Yes,
                                                                    QMessageBox::Yes);
        if (resBtn != QMessageBox::Yes) {
            event->ignore();
        } else {
            if (kill(cl->getPid(), SIGINT) < 0) perror("Error killing clamp thread");
            event->accept();
        }
    } else {
        event->accept();
    }


}

void RTHybrid::on_buttonStart_clicked()
{
    std::string aux_in, aux_out;
    int autocalIndex = ui->autocalPages->currentIndex();

    args.input_channels = NULL;
    args.output_channels = NULL;
    /*args.vars = NULL;
    args.params = NULL;*/
    args.syn_args_live_to_model = NULL;
    args.syn_args_model_to_live = NULL;

    args.model = ui->neuronModelPages->currentIndex();
    args.synapse = ui->synapseModelPages->currentIndex();
    args.mode_auto_cal = ui->autocalPages->currentIndex();

    args.imp = ui->checkImp->isChecked();

    args.freq = ui->intFreq->value();
    args.time_var = ui->intTime->value();
    args.before = ui->intTimeBefore->value();
    args.after = ui->intTimeAfter->value();
    args.observation = ui->intTimeObservation->value();

    /* Mientras no se use la autocal */
    autocalIndex = 0;



    /*if (!ui->autoDetect->isChecked()) {
        args.sec_per_burst = ui->doubleSecPerBurst->value();
    } else {
        args.sec_per_burst = -1;
    }*/

    args.sec_per_burst = (!ui->autoDetect->isChecked()) ?  ui->doubleSecPerBurst->value() : -1;
    args.check_drift = (ui->checkDrift->isChecked()) ? TRUE : FALSE;

    aux_in = ui->textChannelInput->toPlainText().toStdString();
    aux_out = ui->textChannelOutput->toPlainText().toStdString();

    args.input_channels = (char *) malloc (sizeof(char) * aux_in.length() + 1);
    args.output_channels = (char *) malloc (sizeof(char) * aux_out.length() + 1);

    strcpy(args.input_channels, aux_in.c_str());
    strcpy(args.output_channels, aux_out.c_str());

    args.input_factor = ui->doubleInputFactor->value();
    args.output_factor = ui->doubleOutputFactor->value();

    switch (args.model) {
        case EMPTY_NEURON:
            break;
        case IZ: //Izhikevich
            /*args.vars = (double*) malloc (sizeof(double) * 2);
            args.params = (double *) malloc (sizeof(double) * 6);

            args.vars[VAR_X] = ui->doubleIzVini->value();
            args.vars[VAR_Y] = ui->doubleIzUini->value();

            args.params[IZ_A] = ui->doubleIzA->value();
            args.params[IZ_B] = ui->doubleIzB->value();
            args.params[IZ_C] = ui->doubleIzC->value();
            args.params[IZ_D] = ui->doubleIzD->value();
            args.params[IZ_I] = ui->doubleIzI->value();
            args.params[IZ_DT] = 0.001;*/

            break;
        case HR: //Hindmarsh-Rose
            args.vars = (double*) malloc (sizeof(double) * 3);
            args.params = (double *) malloc (sizeof(double) * 4);

            args.vars[VAR_X] = ui->doubleHrXIni->value();
            args.vars[VAR_Y] = ui->doubleHrYIni->value();
            args.vars[VAR_Z] = ui->doubleHrZIni->value();

            args.params[HR_R] = ui->doubleHrR->value();
            args.params[HR_S] = ui->doubleHrS->value();
            args.params[HR_I] = ui->doubleHrI->value();
            args.params[HR_DT] = 0.001;

            break;
        case RLK: //Rulkov
            args.vars = (double*) malloc (sizeof(double) * 2);
            args.params = (double *) malloc (sizeof(double) * 8);

            args.vars[VAR_X] = ui->doubleRlkXIni->value();
            args.vars[VAR_Y] = ui->doubleRlkYIni->value();

            args.params[RLK_ALPHA] = ui->doubleRlkAlpha->value();
            args.params[RLK_SIGMA] = ui->doubleRlkSigma->value();
            args.params[RLK_MU] = ui->doubleRlkMu->value();
            args.params[RLK_I] = ui->doubleRlkI->value();
            args.params[RLK_OLD] = 0.0;
            args.params[RLK_INTER] = 0.0;

            break;
        case GH: //Ghigliazza-Holmes
            args.vars = (double*) malloc (sizeof(double) * 3);
            args.params = (double *) malloc (sizeof(double) * 18);

            args.vars[VAR_X] = ui->doubleGhX0->value();

            args.params[GH_I] = ui->doubleGhIext->value();
            args.params[GH_G_CA] = ui->doubleGhGca->value();
            args.params[GH_G_K] = ui->doubleGhGk->value();
            args.params[GH_G_L] = ui->doubleGhGl->value();
            args.params[GH_G_KS] = ui->doubleGhGks->value();
            args.params[GH_CM] = ui->doubleGhC->value();
            args.params[GH_E_CA] = ui->doubleGhEca->value();
            args.params[GH_E_K] = ui->doubleGhEk->value();
            args.params[GH_E_L] = ui->doubleGhEl->value();
            args.params[GH_EPSILON] = ui->doubleGhEpsilon->value();
            args.params[GH_DELTA] = ui->doubleGhDelta->value();
            args.params[GH_K_CA] = ui->doubleGhKca->value();
            args.params[GH_K_K] = ui->doubleGhKk->value();
            args.params[GH_K_KS] = ui->doubleGhKks->value();
            args.params[GH_VTH_CA] = ui->doubleGhVthca->value();
            args.params[GH_VTH_K] = ui->doubleGhVthk->value();
            args.params[GH_VTH_KS] = ui->doubleGhVthks->value();

            break;
        case WANG:
            args.vars = (double*) malloc (sizeof(double) * 6);
            args.params = (double *) malloc (sizeof(double) * 15);

            args.vars[VAR_X] = -66.5;

            args.params[WANG_I] = 2.5;
            args.params[WANG_G_NA] = 52.0;
            args.params[WANG_G_NAP] = 0.1;
            args.params[WANG_G_K] = 20.0;
            args.params[WANG_G_KS] = 14.0;
            args.params[WANG_G_L] = 0.1;
            args.params[WANG_CM] = 1.0;
            args.params[WANG_V_NA] = 55.0;
            args.params[WANG_V_K] = -90.0;
            args.params[WANG_V_L] = -60.0;
            args.params[WANG_SIGMA] = 0.0;
            args.params[WANG_PHI] = 28.57;
            args.params[WANG_RHO] = 0.6;
            args.params[WANG_TAUM] = 6.0;

            break;
        default:
            break;
    }

    //args.anti = false;

    if (autocalIndex == 0 || autocalIndex == 3){
        switch (args.synapse) {
            case EMPTY_SYN:
                break;
            case ELECTRIC: //Electrical
                {
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
                args_live_to_model_gl->s_fast = ui->spinBox_gl_EtoM_fast_s->value();
                args_live_to_model_gl->s_slow = ui->spinBox_gl_EtoM_slow_s->value();

                args_model_to_live_gl->g[GL_G_FAST] = ui->doubleSpinBox_gl_MtoE_fast_g->value();
                args_model_to_live_gl->g[GL_G_SLOW] = ui->doubleSpinBox_gl_MtoE_slow_g->value();
                args_model_to_live_gl->v_fast = ui->spinBox_gl_MtoE_fast_vth->value();
                args_model_to_live_gl->v_slow = ui->spinBox_gl_MtoE_slow_vth->value();
                args_model_to_live_gl->k1 = ui->doubleSpinBox_gl_MtoE_slow_k1->value();
                args_model_to_live_gl->k2 = ui->doubleSpinBox_gl_MtoE_slow_k2->value();
                args_model_to_live_gl->s_fast = ui->spinBox_gl_MtoE_fast_s->value();
                args_model_to_live_gl->s_slow = ui->spinBox_gl_MtoE_slow_s->value();

                break;
            }
            default:
                break;
        }
    }


    switch (autocalIndex) {
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
        case 3:
        {
            args.auto_cal_val_1 = ui->autocal_reg_per->value();
            args.mode_auto_cal = 9;
            break;
        }

        default:
            args.mode_auto_cal = 0;
            break;
    }




    //movie->start();
    ui->centralWidget->setStyleSheet("#centralWidget{ background-color: rgb(230, 230, 230); }");
    //ui->centralWidget->setStyleSheet("#centralWidget{ background-color: qlineargradient(spread:pad, x1:0.5, y1:1, x2:0.5, y2:0, stop:0 rgba(13, 71, 161, 255), stop:1 rgba(95, 134, 194, 255)); }");
    ui->centralWidget->repaint();

    //int ret = clamp(&args);
    cl = new ClampLauncher(args);
    cl->setObjectName("ClampLauncher");
    connect(cl, &ClampLauncher::finished, cl, &QObject::deleteLater);
    connect(cl, &ClampLauncher::finished, this, &RTHybrid::clampEnd);
    ui->buttonStart->setEnabled(false);

    this->isClampRunning = true;
    cl->start();
    ui->buttonStop->setEnabled(true);
}

void RTHybrid::clampEnd() {
    ui->centralWidget->setStyleSheet("#centralWidget{ background-color: qlineargradient(spread:pad, x1:0.5, y1:1, x2:0.5, y2:0, stop:0 rgba(13, 71, 161, 255), stop:1 rgba(95, 134, 194, 255)); }");
    ui->centralWidget->repaint();
    //movie->stop();

    this->isClampRunning = false;

    ui->buttonStart->setEnabled(true);
    ui->buttonStop->setEnabled(false);

    if(ui->checksound->isChecked())
        QSound::play("resources/alarm_beep.wav");

    QMessageBox msgBox;
    msgBox.setText("Finished");
    msgBox.exec();

}

void RTHybrid::on_buttonStop_clicked()
{
    if (kill(cl->getPid(), SIGINT) < 0) perror("Error killing clamp thread");
}

void RTHybrid::on_neuronModelCombo_activated(int index)
{
    std::string res = "";

    ui->neuronModelPages->setCurrentIndex(index);

    switch (index) {
    case IZ:
    {
        res = "resources/interaction_model_izhikevich.png";
        free_pointers(2, &(this->args.vars), &(this->args.params));
        NM_GUI_Izhikevich_2003 * nmiz = new NM_GUI_Izhikevich_2003(&(this->args));
        nmiz->setWindowFlags(Qt::CustomizeWindowHint | Qt::WindowTitleHint | Qt::WindowMinMaxButtonsHint);
        nmiz->show();
        break;
    }
    case HR:
        res = "resources/interaction_model_hindmarsh_rose.png";
        break;
    case RLK:
        res = "resources/interaction_model_rulkov.png";
        break;
    case GH:
        res = "resources/interaction_model_ghigliazza_holmes.png";
        break;
    default:
        res = "resources/interaction_none.png";
        break;
    }

    QPixmap pixmapTarget = QPixmap(res.c_str());
    pixmapTarget = pixmapTarget.scaled(121, 121, Qt::KeepAspectRatio, Qt::SmoothTransformation);
    ui->label_interaction_model->setPixmap(pixmapTarget);
}

void RTHybrid::on_synapseModelCombo_activated(int index)
{
    std::string res = "", legend = "resources/interaction_none.png";
    QPixmap pixmapTarget;

    res = "resources/interaction_none.png";
    pixmapTarget = QPixmap(res.c_str());
    pixmapTarget = pixmapTarget.scaled(181, 41, Qt::KeepAspectRatio, Qt::SmoothTransformation);
    ui->label_interaction_syn_both->setPixmap(pixmapTarget);

    pixmapTarget = QPixmap(res.c_str());
    pixmapTarget = pixmapTarget.scaled(261, 61, Qt::KeepAspectRatio, Qt::SmoothTransformation);
    ui->label_interaction_syn_living_to_model->setPixmap(pixmapTarget);

    pixmapTarget = QPixmap(res.c_str());
    pixmapTarget = pixmapTarget.scaled(261, 61, Qt::KeepAspectRatio, Qt::SmoothTransformation);
    ui->label_interaction_syn_model_to_living->setPixmap(pixmapTarget);

    ui->synapseModelPages->setCurrentIndex(index);

    switch (index) {
    case ELECTRIC:

        if (ui->doubleSynElec_gEtoM->value() != 0) {
            if (ui->doubleSynElec_gMtoE->value() != 0) {
                res = "resources/interaction_syn_elec_both.png";
            } else {
                res = "resources/interaction_syn_elec_ltm.png";
            }
        } else {
            if (ui->doubleSynElec_gMtoE->value() != 0) {
                res = "resources/interaction_syn_elec_mtl.png";
            } else {
                res = "resources/interaction_none.png";
            }
        }

        pixmapTarget = QPixmap(res.c_str());
        pixmapTarget = pixmapTarget.scaled(181, 41, Qt::KeepAspectRatio, Qt::SmoothTransformation);
        ui->label_interaction_syn_both->setPixmap(pixmapTarget);
        break;
    case GOLOWASCH:
        if (ui->doubleSpinBox_gl_EtoM_fast_g->value() != 0.0) {
            if (ui->doubleSpinBox_gl_EtoM_slow_g->value() != 0.0) {
                res = "resources/interaction_syn_gl_ltm_fs.png";
            } else {
                res = "resources/interaction_syn_gl_ltm_f.png";
            }
        } else if (ui->doubleSpinBox_gl_EtoM_slow_g->value() != 0.0) {
            res = "resources/interaction_syn_gl_ltm_s.png";
        }

        pixmapTarget = QPixmap(res.c_str());
        pixmapTarget = pixmapTarget.scaled(261, 61, Qt::KeepAspectRatio, Qt::SmoothTransformation);
        ui->label_interaction_syn_living_to_model->setPixmap(pixmapTarget);

        if (ui->doubleSpinBox_gl_MtoE_fast_g->value() != 0.0) {
            if (ui->doubleSpinBox_gl_MtoE_slow_g->value() != 0.0) {
                res = "resources/interaction_syn_gl_mtl_fs.png";
            } else {
                res = "resources/interaction_syn_gl_mtl_f.png";
            }
        } else if (ui->doubleSpinBox_gl_MtoE_slow_g->value() != 0.0) {
            res = "resources/interaction_syn_gl_mtl_s.png";
        }

        pixmapTarget = QPixmap(res.c_str());
        pixmapTarget = pixmapTarget.scaled(261, 61, Qt::KeepAspectRatio, Qt::SmoothTransformation);
        ui->label_interaction_syn_model_to_living->setPixmap(pixmapTarget);

        legend = "resources/interaction_syn_gl_legend.png";

        break;
    default:
        break;
    }

    pixmapTarget = QPixmap(legend.c_str());
    pixmapTarget = pixmapTarget.scaled(151, 41, Qt::KeepAspectRatio, Qt::SmoothTransformation);
    ui->label_interaction_legend->setPixmap(pixmapTarget);
}

void RTHybrid::on_autocalCombo_activated(int index)
{
    ui->autocalPages->setCurrentIndex(index);

    switch(index) {
        ui->intTime->setEnabled(true);

        case 1:
            ui->synapseModelCombo->setEnabled(false);
            ui->frameSynapse->setEnabled(false);
            break;
        case 2:
            ui->synapseModelCombo->setEnabled(false);
            ui->frameSynapse->setEnabled(false);
            ui->intTime->setEnabled(false);
            break;
        case 3:
            ui->synapseModelCombo->setEnabled(true);
            ui->frameSynapse->setEnabled(true);
            break;
        default:
            ui->synapseModelCombo->setEnabled(true);
            ui->frameSynapse->setEnabled(true);
            ui->intTime->setEnabled(true);
            break;
    }

    /*if(index!=0){
        ui->synapseModelCombo->setEnabled(false);
        ui->frameSynapse->setEnabled(false);

        if(index==2){
            ui->intTime->setEnabled(false);
        }else{
            ui->intTime->setEnabled(true);
        }
    }else{
        ui->synapseModelCombo->setEnabled(true);
        ui->frameSynapse->setEnabled(true);
        ui->intTime->setEnabled(true);
    }*/
}

void RTHybrid::on_autoDetect_clicked()
{
    if (ui->autoDetect->isChecked()) {
        ui->doubleSecPerBurst->setEnabled(false);
    } else {
        ui->doubleSecPerBurst->setEnabled(true);
    }
}

void RTHybrid::on_doubleSpinBox_gl_EtoM_fast_g_valueChanged(double arg1)
{
    std::string res = "";
    QPixmap pixmapTarget;

    if (arg1 != 0.0) {
        if (ui->doubleSpinBox_gl_EtoM_slow_g->value() != 0.0) {
            res = "resources/interaction_syn_gl_ltm_fs.png";
        } else {
            res = "resources/interaction_syn_gl_ltm_f.png";
        }
    } else {
        if (ui->doubleSpinBox_gl_EtoM_slow_g->value() != 0.0) {
            res = "resources/interaction_syn_gl_ltm_s.png";
        } else {
            res = "resources/interaction_none.png";
        }
    }

    pixmapTarget = QPixmap(res.c_str());
    pixmapTarget = pixmapTarget.scaled(261, 61, Qt::KeepAspectRatio, Qt::SmoothTransformation);
    ui->label_interaction_syn_living_to_model->setPixmap(pixmapTarget);
}

void RTHybrid::on_doubleSpinBox_gl_EtoM_slow_g_valueChanged(double arg1)
{
    std::string res = "";
    QPixmap pixmapTarget;

    if (ui->doubleSpinBox_gl_EtoM_fast_g->value() != 0.0) {
        if (arg1 != 0.0) {
            res = "resources/interaction_syn_gl_ltm_fs.png";
        } else {
            res = "resources/interaction_syn_gl_ltm_f.png";
        }
    } else {
        if (arg1 != 0.0) {
            res = "resources/interaction_syn_gl_ltm_s.png";
        } else {
            res = "resources/interaction_none.png";
        }
    }

    pixmapTarget = QPixmap(res.c_str());
    pixmapTarget = pixmapTarget.scaled(261, 61, Qt::KeepAspectRatio, Qt::SmoothTransformation);
    ui->label_interaction_syn_living_to_model->setPixmap(pixmapTarget);
}

void RTHybrid::on_doubleSpinBox_gl_MtoE_fast_g_valueChanged(double arg1)
{
    std::string res = "";
    QPixmap pixmapTarget;

    if (arg1 != 0.0) {
        if (ui->doubleSpinBox_gl_MtoE_slow_g->value() != 0.0) {
            res = "resources/interaction_syn_gl_mtl_fs.png";
        } else {
            res = "resources/interaction_syn_gl_mtl_f.png";
        }
    } else {
        if (ui->doubleSpinBox_gl_MtoE_slow_g->value() != 0.0) {
            res = "resources/interaction_syn_gl_mtl_s.png";
        } else {
            res = "resources/interaction_none.png";
        }
    }

    pixmapTarget = QPixmap(res.c_str());
    pixmapTarget = pixmapTarget.scaled(261, 61, Qt::KeepAspectRatio, Qt::SmoothTransformation);
    ui->label_interaction_syn_model_to_living->setPixmap(pixmapTarget);
}

void RTHybrid::on_doubleSpinBox_gl_MtoE_slow_g_valueChanged(double arg1)
{
    std::string res = "";
    QPixmap pixmapTarget;

    if (ui->doubleSpinBox_gl_MtoE_fast_g->value() != 0.0) {
        if (arg1 != 0.0) {
            res = "resources/interaction_syn_gl_mtl_fs.png";
        } else {
            res = "resources/interaction_syn_gl_mtl_f.png";
        }
    } else {
        if (arg1 != 0.0) {
            res = "resources/interaction_syn_gl_mtl_s.png";
        } else {
            res = "resources/interaction_none.png";
        }
    }

    pixmapTarget = QPixmap(res.c_str());
    pixmapTarget = pixmapTarget.scaled(261, 61, Qt::KeepAspectRatio, Qt::SmoothTransformation);
    ui->label_interaction_syn_model_to_living->setPixmap(pixmapTarget);
}

void RTHybrid::on_doubleSynElec_gMtoE_valueChanged(double arg1)
{
    std::string res = "";
    QPixmap pixmapTarget;

    if (ui->doubleSynElec_gEtoM->value() != 0.0) {
        if (arg1 != 0.0) {
            res = "resources/interaction_syn_elec_both.png";
        } else {
            res = "resources/interaction_syn_elec_ltm.png";
        }
    } else {
        if (arg1 != 0.0) {
            res = "resources/interaction_syn_elec_mtl.png";
        } else {
            res = "resources/interaction_none.png";
        }
    }

    pixmapTarget = QPixmap(res.c_str());
    pixmapTarget = pixmapTarget.scaled(181, 41, Qt::KeepAspectRatio, Qt::SmoothTransformation);
    ui->label_interaction_syn_both->setPixmap(pixmapTarget);

}

void RTHybrid::on_doubleSynElec_gEtoM_valueChanged(double arg1)
{
    std::string res = "";
    QPixmap pixmapTarget;

    if (ui->doubleSynElec_gMtoE->value() != 0.0) {
        if (arg1 != 0.0) {
            res = "resources/interaction_syn_elec_both.png";
        } else {
            res = "resources/interaction_syn_elec_mtl.png";
        }
    } else {
        if (arg1 != 0.0) {
            res = "resources/interaction_syn_elec_ltm.png";
        } else {
            res = "resources/interaction_none.png";
        }
    }

    pixmapTarget = QPixmap(res.c_str());
    pixmapTarget = pixmapTarget.scaled(181, 41, Qt::KeepAspectRatio, Qt::SmoothTransformation);
    ui->label_interaction_syn_both->setPixmap(pixmapTarget);

}

void RTHybrid::on_buttonIzConfig_clicked()
{
    NM_GUI_Izhikevich_2003 * nmiz = new NM_GUI_Izhikevich_2003(&(this->args));
    nmiz->setWindowFlags(Qt::CustomizeWindowHint | Qt::WindowTitleHint | Qt::WindowMinMaxButtonsHint);
    nmiz->show();
}

void RTHybrid::on_textChannelInput_textChanged()
{
    if (ui->textChannelInput->toPlainText().isEmpty()) {
        ui->doubleSecPerBurst->setEnabled(true);
        ui->autoDetect->setChecked(false);
        ui->autoDetect->setEnabled(false);
        ui->checkDrift->setChecked(false);
        ui->checkDrift->setEnabled(false);
    } else if (ui->autoDetect->isEnabled() == false) {
        ui->autoDetect->setEnabled(true);
        ui->checkDrift->setEnabled(true);
    }
}
