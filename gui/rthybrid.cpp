#include "rthybrid.h"

#include <QMessageBox>
#include <string>
#include <QSound>
#include <QMovie>
#include <QMainWindow>
#include <QCloseEvent>
#include <QEventLoop>

#include "model_library/neuron/Izhikevich_2003/nm_gui_izhikevich_2003.h"
#include "model_library/neuron/Hindmarsh_Rose_1986/nm_gui_hindmarsh_rose_1986.h"
#include "model_library/neuron/Rulkov_2002/nm_gui_rulkov_2002.h"
#include "model_library/neuron/Ghigliazza_Holmes_2004/nm_gui_ghigliazza_holmes_2004.h"
#include "model_library/neuron/Wang_1993/nm_gui_wang_1993.h"

#include "model_library/synapse/Electrical/sm_gui_electrical.h"
#include "model_library/synapse/Golowasch_et_al_1999/sm_gui_golowasch_et_al_1999.h"
#include "model_library/synapse/Destexhe_et_al_1994/sm_gui_destexhe_et_al_1994.h"
#include "model_library/synapse/Greenberg_Manor_2005/sm_gui_greenberg_manor_2005.h"


RTHybrid::RTHybrid(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::RTHybrid)
{
    ui->setupUi(this);
    this->setFixedSize(this->width(),this->height());

    this->settings = new QSettings("RTHybrid", "RTHybrid");

    this->args.vars = NULL;
    this->args.params = NULL;
    this->args.syn_args_live_to_model = NULL;
    this->args.syn_args_model_to_live = NULL;

    this->args.model = 0;
    this->args.synapse_ltom = 0;
    this->args.synapse_mtol = 0;

    /*movie = new QMovie("resources/neuron.gif");
    ui->label_gif->setMovie(movie);
    movie->stop();*/

    ui->centralWidget->setStyleSheet("#centralWidget{ background-color: qlineargradient(spread:pad, x1:0.5, y1:1, x2:0.5, y2:0, stop:0 rgba(13, 71, 161, 255), stop:1 rgba(95, 134, 194, 255)); }");
    ui->centralWidget->repaint();

    /*QPixmap pixmapTarget = QPixmap("resources/interaccion.png");
    pixmapTarget = pixmapTarget.scaled(261, 147, Qt::KeepAspectRatio, Qt::SmoothTransformation);
    ui->label_gif->setPixmap(pixmapTarget);*/

    QPixmap pixmapTarget = QPixmap("resources/neuron/living.png");
    pixmapTarget = pixmapTarget.scaled(121, 121, Qt::KeepAspectRatio, Qt::SmoothTransformation);
    ui->label_interaction_living->setPixmap(pixmapTarget);

    loadSettings();
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
            free_pointers(4, &(this->args.vars), &(this->args.params), &(this->args.syn_args_live_to_model), &(this->args.syn_args_model_to_live));
            saveSettings();
            event->accept();
        }
    } else {
        free_pointers(4, &(this->args.vars), &(this->args.params), &(this->args.syn_args_live_to_model), &(this->args.syn_args_model_to_live));
        saveSettings();
        event->accept();
    }

}

void RTHybrid::on_buttonStart_clicked()
{
    std::string aux_in, aux_out;
    //int autocalIndex = ui->autocalPages->currentIndex();
    time_t t;
    struct tm tm;
    char * path = NULL;
    char * hour = NULL;

    saveSettings();

    args.input_channels = NULL;
    args.output_channels = NULL;
    /*args.vars = NULL;
    args.params = NULL;
    args.syn_args_live_to_model = NULL;
    args.syn_args_model_to_live = NULL;*/

    args.model = ui->combo_neuron->currentIndex();
    args.synapse_mtol = ui->combo_synMtoL->currentIndex();
    args.synapse_ltom = ui->combo_synLtoM->currentIndex();
    //args.mode_auto_cal = ui->autocalPages->currentIndex();

    args.imp = ui->checkImp->isChecked();

    args.freq = ui->intFreq->value();
    args.time_var = ui->intTime->value();
    args.before = ui->intTimeBefore->value();
    args.after = ui->intTimeAfter->value();
    args.observation = ui->intTimeObservation->value();

    /* Mientras no se use la autocal */
    //autocalIndex = 0;



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


    t = time(NULL);
    tm = *localtime(&t);

    asprintf(&(this->args.data_path), "data/%dy_%dm_%dd", tm.tm_year + 1900, tm.tm_mon + 1, tm.tm_mday);


    struct stat st = {0};

    umask(0000);

    if (stat("data", &st) == -1) {
        mkdir("data", 0777);
    }

    if (stat(this->args.data_path, &st) == -1) {
        mkdir(this->args.data_path, 0777);
    }

    asprintf(&hour, "/%dh_%dm_%ds", tm.tm_hour, tm.tm_min, tm.tm_sec);
    asprintf(&(this->args.filename), "%s%s", this->args.data_path, hour);

    ui->plainTextEdit_file->clear();
    ui->plainTextEdit_file->appendPlainText(this->args.filename);
    free_pointers(1, &hour);



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
    //free_pointers(4, &(this->args.vars), &(this->args.params), &(this->args.syn_args_live_to_model), &(this->args.syn_args_model_to_live)); //Ya no se libera aqui
}


void RTHybrid::saveSettings() {
    settings->setValue("frequency", ui->intFreq->value());
    settings->setValue("observation_time", ui->intTimeObservation->value());
    settings->setValue("duration_time", ui->intTime->value());
    settings->setValue("before_time", ui->intTimeBefore->value());
    settings->setValue("after_time", ui->intTimeBefore->value());

    settings->setValue("input_channels", ui->textChannelInput->toPlainText());
    settings->setValue("output_channels", ui->textChannelOutput->toPlainText());

    settings->setValue("input_factor", ui->doubleInputFactor->value());
    settings->setValue("output_factor", ui->doubleOutputFactor->value());

    settings->setValue("drift", ui->checkDrift->isChecked());
    settings->setValue("sec_per_burst", ui->doubleSecPerBurst->value());
    settings->setValue("auto_detect", ui->autoDetect->isChecked());
    settings->setValue("end_sound", ui->checksound->isChecked());

    /* Los modelos tendrían que abrir sus ventanas para inicializarse al cargar
     *
     * settings->setValue("neuron_model", ui->combo_neuron->currentIndex());
    settings->setValue("synapse_model_ltom", ui->combo_synLtoM->currentIndex());
    settings->setValue("synapse_model_mtol", ui->combo_synMtoL->currentIndex());*/
}

void RTHybrid::loadSettings() {
    if (settings->value("frequency", -1).toInt() == -1) return; //No settings saved yet

    ui->intFreq->setValue(settings->value("frequency").toInt());
    ui->intTimeObservation->setValue(settings->value("observation_time").toInt());
    ui->intTime->setValue(settings->value("duration_time").toInt());
    ui->intTimeBefore->setValue(settings->value("before_time").toInt());
    ui->intTimeAfter->setValue(settings->value("after_time").toInt());

    ui->textChannelInput->setPlainText(settings->value("input_channels").toString());
    ui->textChannelOutput->setPlainText(settings->value("output_channels").toString());

    ui->doubleInputFactor->setValue(settings->value("input_factor").toDouble());
    ui->doubleOutputFactor->setValue(settings->value("output_factor").toDouble());

    ui->checkDrift->setChecked(settings->value("drift").toBool());
    ui->doubleSecPerBurst->setValue(settings->value("sec_per_burst").toDouble());
    ui->autoDetect->setChecked(settings->value("auto_detect").toBool());
    ui->checksound->setChecked(settings->value("end_sound").toBool());
}



/*void RTHybrid::on_autocalCombo_activated(int index)
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

    if(index!=0){
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
    }
}*/

void RTHybrid::on_autoDetect_clicked()
{
    if (ui->autoDetect->isChecked()) {
        ui->doubleSecPerBurst->setEnabled(false);
    } else {
        ui->doubleSecPerBurst->setEnabled(true);
    }
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


std::string RTHybrid::neuron_models_switch(int index) {
    std::string res = "";

    switch (index) {
    case NM_IZHIKEVICH_2003:
    {
        res = "resources/neuron/izhikevich_2003.png";
        free_pointers(2, &(this->args.vars), &(this->args.params));
        NM_GUI_Izhikevich_2003 * nm = new NM_GUI_Izhikevich_2003(&(this->args));
        nm->setWindowFlags(Qt::CustomizeWindowHint | Qt::WindowTitleHint | Qt::WindowMinMaxButtonsHint);
        nm->show();
        break;
    }
    case NM_HINDMARSH_ROSE_1986:
    {
        res = "resources/neuron/hindmarsh_rose_1986.png";
        free_pointers(2, &(this->args.vars), &(this->args.params));
        NM_GUI_Hindmarsh_Rose_1986 * nm = new NM_GUI_Hindmarsh_Rose_1986(&(this->args));
        nm->setWindowFlags(Qt::CustomizeWindowHint | Qt::WindowTitleHint | Qt::WindowMinMaxButtonsHint);
        nm->show();
        break;
    }
    case NM_RULKOV_2002:
    {
        res = "resources/neuron/rulkov_2002.png";
        free_pointers(2, &(this->args.vars), &(this->args.params));
        NM_GUI_Rulkov_2002 * nm = new NM_GUI_Rulkov_2002(&(this->args));
        nm->setWindowFlags(Qt::CustomizeWindowHint | Qt::WindowTitleHint | Qt::WindowMinMaxButtonsHint);
        nm->show();
        break;
    }
    case NM_GHIGLIAZZA_HOLMES_2004:
    {
        res = "resources/neuron/ghigliazza_holmes_2004.png";
        free_pointers(2, &(this->args.vars), &(this->args.params));
        NM_GUI_Ghigliazza_Holmes_2004 * nm = new NM_GUI_Ghigliazza_Holmes_2004(&(this->args));
        nm->setWindowFlags(Qt::CustomizeWindowHint | Qt::WindowTitleHint | Qt::WindowMinMaxButtonsHint);
        nm->show();
        break;
    }
    case NM_WANG_1993:
    {
        res = "resources/neuron/wang_1993.png";
        free_pointers(2, &(this->args.vars), &(this->args.params));
        NM_GUI_Wang_1993 * nm = new NM_GUI_Wang_1993(&(this->args));
        nm->setWindowFlags(Qt::CustomizeWindowHint | Qt::WindowTitleHint | Qt::WindowMinMaxButtonsHint);
        nm->show();
        break;
    }
    default:
        res = "resources/interaction_none.png";
        free_pointers(2, &(this->args.vars), &(this->args.params));
        break;
    }

    return res;
}

void RTHybrid::on_pushButton_neuron_config_clicked()
{
    int index = ui->combo_neuron->currentIndex();

    neuron_models_switch(index);
}

void RTHybrid::on_combo_neuron_activated(int index)
{
    std::string res = neuron_models_switch(index);

    QPixmap pixmapTarget = QPixmap(res.c_str());
    pixmapTarget = pixmapTarget.scaled(121, 121, Qt::KeepAspectRatio, Qt::SmoothTransformation);
    ui->label_interaction_model->setPixmap(pixmapTarget);
}


void RTHybrid::synapse_models_switch(int index, void ** syn_args, unsigned int direction) {
    switch (index) {
    case SM_ELECTRICAL:
    {
        free_pointers(1, syn_args);
        SM_GUI_Electrical * sm = new SM_GUI_Electrical(syn_args, direction);
        sm->setWindowFlags(Qt::CustomizeWindowHint | Qt::WindowTitleHint | Qt::WindowMinMaxButtonsHint);
        sm->exec();
        break;
    }
    case SM_GOLOWASCH_ET_AL_1999:
    {
        free_pointers(1, syn_args);
        SM_GUI_Golowasch_et_al_1999 * sm = new SM_GUI_Golowasch_et_al_1999(syn_args, direction);
        sm->setWindowFlags(Qt::CustomizeWindowHint | Qt::WindowTitleHint | Qt::WindowMinMaxButtonsHint);
        sm->exec();
        break;
    }
    case SM_DESTEXHE_ET_AL_1994:
    {
        free_pointers(1, syn_args);
        SM_GUI_Destexhe_et_al_1994 * sm = new SM_GUI_Destexhe_et_al_1994(syn_args, direction);
        sm->setWindowFlags(Qt::CustomizeWindowHint | Qt::WindowTitleHint | Qt::WindowMinMaxButtonsHint);
        sm->exec();
        break;
    }
    case SM_GREENBERG_MANOR_2005:
    {
        free_pointers(1, syn_args);
        SM_GUI_Greenberg_Manor_2005 * sm = new SM_GUI_Greenberg_Manor_2005(syn_args, direction);
        sm->setWindowFlags(Qt::CustomizeWindowHint | Qt::WindowTitleHint | Qt::WindowMinMaxButtonsHint);
        sm->exec();
        break;
    }
    default:
        free_pointers(1, syn_args);
        break;
    }

}

void RTHybrid::synapse_models_graphics_ltom(int model_ltom, void * syn_args_ltom, int model_mtol, void * syn_args_mtol) {
    std::string res = "", legend = "resources/interaction_none.png";
    QPixmap pixmapTarget;
    unsigned int elec_mtol = 0;

    if (model_mtol == SM_ELECTRICAL) {
        syn_elec_args * aux_syn_args_mtol = (syn_elec_args *) syn_args_mtol;
        if (aux_syn_args_mtol->g[ELEC_G] != 0.0) {
            elec_mtol = 1;
        }
    } else if (model_mtol == SM_GOLOWASCH_ET_AL_1999) {
        legend = "resources/synapse/golowasch_et_al_1999_legend.png";
    }

    if (elec_mtol == 0) {
        res = "resources/interaction_none.png";
    } else {
        res = "resources/synapse/electrical_mtol.png";
    }

    pixmapTarget = QPixmap(res.c_str());
    pixmapTarget = pixmapTarget.scaled(181, 41, Qt::KeepAspectRatio, Qt::SmoothTransformation);
    ui->label_interaction_syn_both->setPixmap(pixmapTarget);

    res = "resources/interaction_none.png";
    pixmapTarget = QPixmap(res.c_str());
    pixmapTarget = pixmapTarget.scaled(261, 61, Qt::KeepAspectRatio, Qt::SmoothTransformation);
    ui->label_interaction_syn_living_to_model->setPixmap(pixmapTarget);


    switch (model_ltom) {
    case SM_ELECTRICAL:
    {
        syn_elec_args * aux_syn_args = (syn_elec_args *) syn_args_ltom;

        if (aux_syn_args->g[ELEC_G] != 0.0) {
            if (elec_mtol == 1) {
                res = "resources/synapse/electrical_both.png";
            } else {
                res = "resources/synapse/electrical_ltom.png";
            }
        } else {
            if (elec_mtol == 1) {
                res = "resources/synapse/electrical_mtol.png";
            } else {
                res = "resources/interaction_none.png";
            }
        }

        pixmapTarget = QPixmap(res.c_str());
        pixmapTarget = pixmapTarget.scaled(181, 41, Qt::KeepAspectRatio, Qt::SmoothTransformation);
        ui->label_interaction_syn_both->setPixmap(pixmapTarget);

        break;
    }
    case SM_GOLOWASCH_ET_AL_1999:
    {
        syn_gl_args * aux_syn_args = (syn_gl_args *) syn_args_ltom;

        if (aux_syn_args->g[GL_G_FAST] != 0.0) {
            if (aux_syn_args->g[GL_G_SLOW] != 0.0) {
                res = "resources/synapse/golowasch_et_al_1999_ltom_fs.png";
            } else {
                res = "resources/synapse/golowasch_et_al_1999_ltom_f.png";
            }
        } else if (aux_syn_args->g[GL_G_SLOW] != 0.0) {
            res = "resources/synapse/golowasch_et_al_1999_ltom_s.png";
        }

        pixmapTarget = QPixmap(res.c_str());
        pixmapTarget = pixmapTarget.scaled(261, 61, Qt::KeepAspectRatio, Qt::SmoothTransformation);
        ui->label_interaction_syn_living_to_model->setPixmap(pixmapTarget);
        legend = "resources/synapse/golowasch_et_al_1999_legend.png";

        break;
    }
    case SM_GREENBERG_MANOR_2005:
    {
        sm_greenberg_manor_2005_args * aux_syn_args = (sm_greenberg_manor_2005_args *) syn_args_ltom;

        if (aux_syn_args->g[SM_GREENBERG_MANOR_2005_G] != 0.0) {
            res = "resources/synapse/greenberg_manor_2005_ltom.png";
        }

        pixmapTarget = QPixmap(res.c_str());
        pixmapTarget = pixmapTarget.scaled(261, 61, Qt::KeepAspectRatio, Qt::SmoothTransformation);
        ui->label_interaction_syn_living_to_model->setPixmap(pixmapTarget);

        break;
    }
    default:
        break;
    }

    pixmapTarget = QPixmap(legend.c_str());
    pixmapTarget = pixmapTarget.scaled(151, 41, Qt::KeepAspectRatio, Qt::SmoothTransformation);
    ui->label_interaction_syn_legend->setPixmap(pixmapTarget);
}

void RTHybrid::synapse_models_graphics_mtol(int model_mtol, void * syn_args_mtol, int model_ltom, void * syn_args_ltom) {
    std::string res = "", legend = "resources/interaction_none.png";
    QPixmap pixmapTarget;
    unsigned int elec_ltom = 0;

    if (model_ltom == SM_ELECTRICAL) {
        syn_elec_args * aux_syn_args_ltom = (syn_elec_args *) syn_args_ltom;
        if (aux_syn_args_ltom->g[ELEC_G] != 0.0) {
            elec_ltom = 1;
        }
    } else if (model_ltom == SM_GOLOWASCH_ET_AL_1999) {
        legend = "resources/synapse/golowasch_et_al_1999_legend.png";
    }

    if (elec_ltom == 0) {
        res = "resources/interaction_none.png";
    } else {
        res = "resources/synapse/electrical_ltom.png";
    }

    pixmapTarget = QPixmap(res.c_str());
    pixmapTarget = pixmapTarget.scaled(181, 41, Qt::KeepAspectRatio, Qt::SmoothTransformation);
    ui->label_interaction_syn_both->setPixmap(pixmapTarget);

    res = "resources/interaction_none.png";
    pixmapTarget = QPixmap(res.c_str());
    pixmapTarget = pixmapTarget.scaled(261, 61, Qt::KeepAspectRatio, Qt::SmoothTransformation);
    ui->label_interaction_syn_model_to_living->setPixmap(pixmapTarget);


    switch (model_mtol) {
    case SM_ELECTRICAL:
    {
        syn_elec_args * aux_syn_args = (syn_elec_args *) syn_args_mtol;

        if (aux_syn_args->g[ELEC_G] != 0.0) {
            if (elec_ltom == 1) {
                res = "resources/synapse/electrical_both.png";
            } else {
                res = "resources/synapse/electrical_mtol.png";
            }
        } else {
            if (elec_ltom == 1) {
                res = "resources/synapse/electrical_ltom.png";
            } else {
                res = "resources/interaction_none.png";
            }
        }

        pixmapTarget = QPixmap(res.c_str());
        pixmapTarget = pixmapTarget.scaled(181, 41, Qt::KeepAspectRatio, Qt::SmoothTransformation);
        ui->label_interaction_syn_both->setPixmap(pixmapTarget);

        break;
    }
    case SM_GOLOWASCH_ET_AL_1999:
    {
        syn_gl_args * aux_syn_args = (syn_gl_args *) syn_args_mtol;

        if (aux_syn_args->g[GL_G_FAST] != 0.0) {
            if (aux_syn_args->g[GL_G_SLOW] != 0.0) {
                res = "resources/synapse/golowasch_et_al_1999_mtol_fs.png";
            } else {
                res = "resources/synapse/golowasch_et_al_1999_mtol_f.png";
            }
        } else if (aux_syn_args->g[GL_G_SLOW] != 0.0) {
            res = "resources/synapse/golowasch_et_al_1999_mtol_s.png";
        }

        pixmapTarget = QPixmap(res.c_str());
        pixmapTarget = pixmapTarget.scaled(261, 61, Qt::KeepAspectRatio, Qt::SmoothTransformation);
        ui->label_interaction_syn_model_to_living->setPixmap(pixmapTarget);
        legend = "resources/synapse/golowasch_et_al_1999_legend.png";

        break;
    }
    case SM_GREENBERG_MANOR_2005:
    {
        sm_greenberg_manor_2005_args * aux_syn_args = (sm_greenberg_manor_2005_args *) syn_args_mtol;

        if (aux_syn_args->g[SM_GREENBERG_MANOR_2005_G] != 0.0) {
            res = "resources/synapse/greenberg_manor_2005_mtol.png";
        }

        pixmapTarget = QPixmap(res.c_str());
        pixmapTarget = pixmapTarget.scaled(261, 61, Qt::KeepAspectRatio, Qt::SmoothTransformation);
        ui->label_interaction_syn_model_to_living->setPixmap(pixmapTarget);

        break;
    }
    default:
        break;
    }

    pixmapTarget = QPixmap(legend.c_str());
    pixmapTarget = pixmapTarget.scaled(151, 41, Qt::KeepAspectRatio, Qt::SmoothTransformation);
    ui->label_interaction_syn_legend->setPixmap(pixmapTarget);
}

void RTHybrid::on_combo_synLtoM_activated(int index)
{
    synapse_models_switch(index, &(this->args.syn_args_live_to_model), 0);

    synapse_models_graphics_ltom(index, this->args.syn_args_live_to_model, ui->combo_synMtoL->currentIndex(), this->args.syn_args_model_to_live);
}

void RTHybrid::on_combo_synMtoL_activated(int index)
{
    synapse_models_switch(index, &(this->args.syn_args_model_to_live), 1);

    synapse_models_graphics_mtol(index, this->args.syn_args_model_to_live, ui->combo_synLtoM->currentIndex(), this->args.syn_args_live_to_model);
}

void RTHybrid::on_pushButton_synLtoM_config_clicked()
{
    int index = ui->combo_synLtoM->currentIndex();
    synapse_models_switch(index, &(this->args.syn_args_live_to_model), 0);

    synapse_models_graphics_ltom(index, this->args.syn_args_live_to_model, ui->combo_synMtoL->currentIndex(), this->args.syn_args_model_to_live);
}

void RTHybrid::on_pushButton_synMtoL_config_clicked()
{
    int index = ui->combo_synMtoL->currentIndex();
    synapse_models_switch(index, &(this->args.syn_args_model_to_live), 1);

    synapse_models_graphics_mtol(index, this->args.syn_args_model_to_live, ui->combo_synLtoM->currentIndex(), this->args.syn_args_live_to_model);
}
