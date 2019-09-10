#include "nm_gui_nowotny_et_al_2008.h"
#include "ui_nm_gui_nowotny_et_al_2008.h"

NM_GUI_Nowotny_et_al_2008::NM_GUI_Nowotny_et_al_2008(clamp_args * args, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::NM_GUI_Nowotny_et_al_2008)
{
    this->settings = new QSettings("RTHybrid", "NM_Nowotny_et_al_2008");
    this->args = args;
    ui->setupUi(this);
    loadSettings();
}

NM_GUI_Nowotny_et_al_2008::~NM_GUI_Nowotny_et_al_2008(){
     delete ui;
}

void NM_GUI_Nowotny_et_al_2008::on_pushButton_accept_clicked() {
    args->vars = (double*) malloc (sizeof(double) * 16);
    args->params = (double *) malloc (sizeof(double) * 75);

    /*args->vars[NM_NOWOTNY_ET_AL_2008_MNA] = ui->doubleSpinBox_mna->value();
    args->vars[NM_NOWOTNY_ET_AL_2008_HNA] = ui->doubleSpinBox_hna->value();
    args->vars[NM_NOWOTNY_ET_AL_2008_MKD] = ui->doubleSpinBox_mkd->value();
    args->vars[NM_NOWOTNY_ET_AL_2008_MM] = ui->doubleSpinBox_mm->value();
    args->vars[NM_NOWOTNY_ET_AL_2008_VAXON] = ui->doubleSpinBox_Vaxon->value();
    args->vars[NM_NOWOTNY_ET_AL_2008_MCAT] = ui->doubleSpinBox_mcat->value();
    args->vars[NM_NOWOTNY_ET_AL_2008_HCAT] = ui->doubleSpinBox_hcat->value();
    args->vars[NM_NOWOTNY_ET_AL_2008_MCAS] = ui->doubleSpinBox_mcas->value();
    args->vars[NM_NOWOTNY_ET_AL_2008_CA] = ui->doubleSpinBox_Ca->value();
    args->vars[NM_NOWOTNY_ET_AL_2008_MKCA] = ui->doubleSpinBox_mkca->value();
    args->vars[NM_NOWOTNY_ET_AL_2008_HKCA] = ui->doubleSpinBox_hkca->value();
    args->vars[NM_NOWOTNY_ET_AL_2008_MA] = ui->doubleSpinBox_ma->value();
    args->vars[NM_NOWOTNY_ET_AL_2008_HA1] = ui->doubleSpinBox_ha1->value();
    args->vars[NM_NOWOTNY_ET_AL_2008_HA2] = ui->doubleSpinBox_ha2->value();
    args->vars[NM_NOWOTNY_ET_AL_2008_MH] = ui->doubleSpinBox_mh->value();
    args->vars[NM_NOWOTNY_ET_AL_2008_V] = ui->doubleSpinBox_V->value();

    args->params[NM_NOWOTNY_ET_AL_2008_GNA] = ui->doubleSpinBox_gna->value();
    args->params[NM_NOWOTNY_ET_AL_2008_VNA] = ui->doubleSpinBox_Vna->value();
    args->params[NM_NOWOTNY_ET_AL_2008_AREAAXON] = ui->doubleSpinBox_AreaAxon->value();
    args->params[NM_NOWOTNY_ET_AL_2008_GKD] = ui->doubleSpinBox_gkd->value();
    args->params[NM_NOWOTNY_ET_AL_2008_VKD] = ui->doubleSpinBox_Vkd->value();
    args->params[NM_NOWOTNY_ET_AL_2008_GM] = ui->doubleSpinBox_gm->value();
    args->params[NM_NOWOTNY_ET_AL_2008_VM] = ui->doubleSpinBox_Vm->value();
    args->params[NM_NOWOTNY_ET_AL_2008_VMM] = ui->doubleSpinBox_Vmm->value();
    args->params[NM_NOWOTNY_ET_AL_2008_SMM] = ui->doubleSpinBox_Smm->value();
    args->params[NM_NOWOTNY_ET_AL_2008_KMM] = ui->doubleSpinBox_kmm->value();
    args->params[NM_NOWOTNY_ET_AL_2008_VKMM] = ui->doubleSpinBox_Vkmm->value();
    args->params[NM_NOWOTNY_ET_AL_2008_SKMM] = ui->doubleSpinBox_Skmm->value();
    args->params[NM_NOWOTNY_ET_AL_2008_GLA] = ui->doubleSpinBox_gla->value();
    args->params[NM_NOWOTNY_ET_AL_2008_VL] = ui->doubleSpinBox_Vl->value();
    args->params[NM_NOWOTNY_ET_AL_2008_GVV] = ui->doubleSpinBox_gvv->value();
    args->params[NM_NOWOTNY_ET_AL_2008_CMA] = ui->doubleSpinBox_Cma->value();
    args->params[NM_NOWOTNY_ET_AL_2008_GCAT] = ui->doubleSpinBox_gcat->value();
    args->params[NM_NOWOTNY_ET_AL_2008_GCAS] = ui->doubleSpinBox_gcas->value();
    args->params[NM_NOWOTNY_ET_AL_2008_PCA] = ui->doubleSpinBox_Pca->value();
    args->params[NM_NOWOTNY_ET_AL_2008_RTF] = ui->doubleSpinBox_RTF->value();
    args->params[NM_NOWOTNY_ET_AL_2008_CAOUT] = ui->doubleSpinBox_Caout->value();
    args->params[NM_NOWOTNY_ET_AL_2008_AREASOMA] = ui->doubleSpinBox_AreaSoma->value();
    args->params[NM_NOWOTNY_ET_AL_2008_VMCAT] = ui->doubleSpinBox_Vmcat->value();
    args->params[NM_NOWOTNY_ET_AL_2008_SMCAT] = ui->doubleSpinBox_Smcat->value();
    args->params[NM_NOWOTNY_ET_AL_2008_KMCAT] = ui->doubleSpinBox_kmcat->value();
    args->params[NM_NOWOTNY_ET_AL_2008_VHCAT] = ui->doubleSpinBox_Vhcat->value();
    args->params[NM_NOWOTNY_ET_AL_2008_SHCAT] = ui->doubleSpinBox_Shcat->value();
    args->params[NM_NOWOTNY_ET_AL_2008_KHCAT] = ui->doubleSpinBox_khcat->value();
    args->params[NM_NOWOTNY_ET_AL_2008_VKHCAT] = ui->doubleSpinBox_Vkhcat->value();
    args->params[NM_NOWOTNY_ET_AL_2008_SKHCAT] = ui->doubleSpinBox_Skhcat->value();
    args->params[NM_NOWOTNY_ET_AL_2008_VMCAS] = ui->doubleSpinBox_Vmcas->value();
    args->params[NM_NOWOTNY_ET_AL_2008_SMCAS] = ui->doubleSpinBox_Smcas->value();
    args->params[NM_NOWOTNY_ET_AL_2008_KMCAS] = ui->doubleSpinBox_kmcas->value();
    args->params[NM_NOWOTNY_ET_AL_2008_CICA] = ui->doubleSpinBox_cica->value();
    args->params[NM_NOWOTNY_ET_AL_2008_KCA] = ui->doubleSpinBox_kca->value();
    args->params[NM_NOWOTNY_ET_AL_2008_CA0] = ui->doubleSpinBox_Ca0->value();
    args->params[NM_NOWOTNY_ET_AL_2008_GKCA] = ui->doubleSpinBox_gkca->value();
    args->params[NM_NOWOTNY_ET_AL_2008_VKCA] = ui->doubleSpinBox_Vkca->value();
    args->params[NM_NOWOTNY_ET_AL_2008_VMKCA1] = ui->doubleSpinBox_Vmkca1->value();
    args->params[NM_NOWOTNY_ET_AL_2008_F] = ui->doubleSpinBox_f->value();
    args->params[NM_NOWOTNY_ET_AL_2008_SMKCA1] = ui->doubleSpinBox_Smkca1->value();
    args->params[NM_NOWOTNY_ET_AL_2008_VMKCA2] = ui->doubleSpinBox_Vmkca2->value();
    args->params[NM_NOWOTNY_ET_AL_2008_SMKCA2] = ui->doubleSpinBox_Smkca2->value();
    args->params[NM_NOWOTNY_ET_AL_2008_CMKCA] = ui->doubleSpinBox_cmkca->value();
    args->params[NM_NOWOTNY_ET_AL_2008_KMKCA] = ui->doubleSpinBox_kmkca->value();
    args->params[NM_NOWOTNY_ET_AL_2008_CHKCA1] = ui->doubleSpinBox_chkca1->value();
    args->params[NM_NOWOTNY_ET_AL_2008_CHKCA2] = ui->doubleSpinBox_chkca2->value();
    args->params[NM_NOWOTNY_ET_AL_2008_KHKCA] = ui->doubleSpinBox_khkca->value();
    args->params[NM_NOWOTNY_ET_AL_2008_GA] = ui->doubleSpinBox_ga->value();
    args->params[NM_NOWOTNY_ET_AL_2008_VA] = ui->doubleSpinBox_Va->value();
    args->params[NM_NOWOTNY_ET_AL_2008_VAA] = ui->doubleSpinBox_Vaa->value();
    args->params[NM_NOWOTNY_ET_AL_2008_SAA] = ui->doubleSpinBox_Saa->value();
    args->params[NM_NOWOTNY_ET_AL_2008_VMA] = ui->doubleSpinBox_Vma->value();
    args->params[NM_NOWOTNY_ET_AL_2008_SMA] = ui->doubleSpinBox_Sma->value();
    args->params[NM_NOWOTNY_ET_AL_2008_KMA] = ui->doubleSpinBox_kma->value();
    args->params[NM_NOWOTNY_ET_AL_2008_VHA] = ui->doubleSpinBox_Vha->value();
    args->params[NM_NOWOTNY_ET_AL_2008_SHA] = ui->doubleSpinBox_Sha->value();
    args->params[NM_NOWOTNY_ET_AL_2008_KHA1] = ui->doubleSpinBox_kha1->value();
    args->params[NM_NOWOTNY_ET_AL_2008_KHA2] = ui->doubleSpinBox_kha2->value();
    args->params[NM_NOWOTNY_ET_AL_2008_VKHA2] = ui->doubleSpinBox_Vkha2->value();
    args->params[NM_NOWOTNY_ET_AL_2008_SKHA2] = ui->doubleSpinBox_Skha2->value();
    args->params[NM_NOWOTNY_ET_AL_2008_GH] = ui->doubleSpinBox_gh->value();
    args->params[NM_NOWOTNY_ET_AL_2008_VH] = ui->doubleSpinBox_Vh->value();
    args->params[NM_NOWOTNY_ET_AL_2008_VMH] = ui->doubleSpinBox_Vmh->value();
    args->params[NM_NOWOTNY_ET_AL_2008_SMH] = ui->doubleSpinBox_Smh->value();
    args->params[NM_NOWOTNY_ET_AL_2008_KMH] = ui->doubleSpinBox_kmh->value();
    args->params[NM_NOWOTNY_ET_AL_2008_VKMH] = ui->doubleSpinBox_Vkmh->value();
    args->params[NM_NOWOTNY_ET_AL_2008_SKMH] = ui->doubleSpinBox_Skmh->value();
    args->params[NM_NOWOTNY_ET_AL_2008_GLS] = ui->doubleSpinBox_gls->value();
    args->params[NM_NOWOTNY_ET_AL_2008_I] = ui->doubleSpinBox_i->value();
    args->params[NM_NOWOTNY_ET_AL_2008_IOFFSET] = ui->doubleSpinBox_ioffset->value();
    args->params[NM_NOWOTNY_ET_AL_2008_SYN] = ui->doubleSpinBox_syn->value();
    args->params[NM_NOWOTNY_ET_AL_2008_ISCALE] = ui->doubleSpinBox_iscale->value();
    args->params[NM_NOWOTNY_ET_AL_2008_CMS] = ui->doubleSpinBox_Cms->value();
    args->params[NM_NOWOTNY_ET_AL_2008_DT] = ui->comboBoxIntegrationMethod->currentIndex();*/

    saveSettings();
    this->close();
}

void NM_GUI_Nowotny_et_al_2008::saveSettings() {
    /*settings->setValue("NM_NOWOTNY_ET_AL_2008_MNA", ui->doubleSpinBox_mna->value());
    settings->setValue("NM_NOWOTNY_ET_AL_2008_HNA", ui->doubleSpinBox_hna->value());
    settings->setValue("NM_NOWOTNY_ET_AL_2008_MKD", ui->doubleSpinBox_mkd->value());
    settings->setValue("NM_NOWOTNY_ET_AL_2008_MM", ui->doubleSpinBox_mm->value());
    settings->setValue("NM_NOWOTNY_ET_AL_2008_VAXON", ui->doubleSpinBox_Vaxon->value());
    settings->setValue("NM_NOWOTNY_ET_AL_2008_MCAT", ui->doubleSpinBox_mcat->value());
    settings->setValue("NM_NOWOTNY_ET_AL_2008_HCAT", ui->doubleSpinBox_hcat->value());
    settings->setValue("NM_NOWOTNY_ET_AL_2008_MCAS", ui->doubleSpinBox_mcas->value());
    settings->setValue("NM_NOWOTNY_ET_AL_2008_CA", ui->doubleSpinBox_Ca->value());
    settings->setValue("NM_NOWOTNY_ET_AL_2008_MKCA", ui->doubleSpinBox_mkca->value());
    settings->setValue("NM_NOWOTNY_ET_AL_2008_HKCA", ui->doubleSpinBox_hkca->value());
    settings->setValue("NM_NOWOTNY_ET_AL_2008_MA", ui->doubleSpinBox_ma->value());
    settings->setValue("NM_NOWOTNY_ET_AL_2008_HA1", ui->doubleSpinBox_ha1->value());
    settings->setValue("NM_NOWOTNY_ET_AL_2008_HA2", ui->doubleSpinBox_ha2->value());
    settings->setValue("NM_NOWOTNY_ET_AL_2008_MH", ui->doubleSpinBox_mh->value());
    settings->setValue("NM_NOWOTNY_ET_AL_2008_V", ui->doubleSpinBox_V->value());

    settings->setValue("NM_NOWOTNY_ET_AL_2008_GNA", ui->doubleSpinBox_gna->value());
    settings->setValue("NM_NOWOTNY_ET_AL_2008_VNA", ui->doubleSpinBox_Vna->value());
    settings->setValue("NM_NOWOTNY_ET_AL_2008_AREAAXON", ui->doubleSpinBox_AreaAxon->value());
    settings->setValue("NM_NOWOTNY_ET_AL_2008_GKD", ui->doubleSpinBox_gkd->value());
    settings->setValue("NM_NOWOTNY_ET_AL_2008_VKD", ui->doubleSpinBox_Vkd->value());
    settings->setValue("NM_NOWOTNY_ET_AL_2008_GM", ui->doubleSpinBox_gm->value());
    settings->setValue("NM_NOWOTNY_ET_AL_2008_VM", ui->doubleSpinBox_Vm->value());
    settings->setValue("NM_NOWOTNY_ET_AL_2008_VMM", ui->doubleSpinBox_Vmm->value());
    settings->setValue("NM_NOWOTNY_ET_AL_2008_SMM", ui->doubleSpinBox_Smm->value());
    settings->setValue("NM_NOWOTNY_ET_AL_2008_KMM", ui->doubleSpinBox_kmm->value());
    settings->setValue("NM_NOWOTNY_ET_AL_2008_VKMM", ui->doubleSpinBox_Vkmm->value());
    settings->setValue("NM_NOWOTNY_ET_AL_2008_SKMM", ui->doubleSpinBox_Skmm->value());
    settings->setValue("NM_NOWOTNY_ET_AL_2008_GLA", ui->doubleSpinBox_gla->value());
    settings->setValue("NM_NOWOTNY_ET_AL_2008_VL", ui->doubleSpinBox_Vl->value());
    settings->setValue("NM_NOWOTNY_ET_AL_2008_GVV", ui->doubleSpinBox_gvv->value());
    settings->setValue("NM_NOWOTNY_ET_AL_2008_CMA", ui->doubleSpinBox_Cma->value());
    settings->setValue("NM_NOWOTNY_ET_AL_2008_GCAT", ui->doubleSpinBox_gcat->value());
    settings->setValue("NM_NOWOTNY_ET_AL_2008_GCAS", ui->doubleSpinBox_gcas->value());
    settings->setValue("NM_NOWOTNY_ET_AL_2008_PCA", ui->doubleSpinBox_Pca->value());
    settings->setValue("NM_NOWOTNY_ET_AL_2008_RTF", ui->doubleSpinBox_RTF->value());
    settings->setValue("NM_NOWOTNY_ET_AL_2008_CAOUT", ui->doubleSpinBox_Caout->value());
    settings->setValue("NM_NOWOTNY_ET_AL_2008_AREASOMA", ui->doubleSpinBox_AreaSoma->value());
    settings->setValue("NM_NOWOTNY_ET_AL_2008_VMCAT", ui->doubleSpinBox_Vmcat->value());
    settings->setValue("NM_NOWOTNY_ET_AL_2008_SMCAT", ui->doubleSpinBox_Smcat->value());
    settings->setValue("NM_NOWOTNY_ET_AL_2008_KMCAT", ui->doubleSpinBox_kmcat->value());
    settings->setValue("NM_NOWOTNY_ET_AL_2008_VHCAT", ui->doubleSpinBox_Vhcat->value());
    settings->setValue("NM_NOWOTNY_ET_AL_2008_SHCAT", ui->doubleSpinBox_Shcat->value());
    settings->setValue("NM_NOWOTNY_ET_AL_2008_KHCAT", ui->doubleSpinBox_khcat->value());
    settings->setValue("NM_NOWOTNY_ET_AL_2008_VKHCAT", ui->doubleSpinBox_Vkhcat->value());
    settings->setValue("NM_NOWOTNY_ET_AL_2008_SKHCAT", ui->doubleSpinBox_Skhcat->value());
    settings->setValue("NM_NOWOTNY_ET_AL_2008_VMCAS", ui->doubleSpinBox_Vmcas->value());
    settings->setValue("NM_NOWOTNY_ET_AL_2008_SMCAS", ui->doubleSpinBox_Smcas->value());
    settings->setValue("NM_NOWOTNY_ET_AL_2008_KMCAS", ui->doubleSpinBox_kmcas->value());
    settings->setValue("NM_NOWOTNY_ET_AL_2008_CICA", ui->doubleSpinBox_cica->value());
    settings->setValue("NM_NOWOTNY_ET_AL_2008_KCA", ui->doubleSpinBox_kca->value());
    settings->setValue("NM_NOWOTNY_ET_AL_2008_CA0", ui->doubleSpinBox_Ca0->value());
    settings->setValue("NM_NOWOTNY_ET_AL_2008_GKCA", ui->doubleSpinBox_gkca->value());
    settings->setValue("NM_NOWOTNY_ET_AL_2008_VKCA", ui->doubleSpinBox_Vkca->value());
    settings->setValue("NM_NOWOTNY_ET_AL_2008_VMKCA1", ui->doubleSpinBox_Vmkca1->value());
    settings->setValue("NM_NOWOTNY_ET_AL_2008_F", ui->doubleSpinBox_f->value());
    settings->setValue("NM_NOWOTNY_ET_AL_2008_SMKCA1", ui->doubleSpinBox_Smkca1->value());
    settings->setValue("NM_NOWOTNY_ET_AL_2008_VMKCA2", ui->doubleSpinBox_Vmkca2->value());
    settings->setValue("NM_NOWOTNY_ET_AL_2008_SMKCA2", ui->doubleSpinBox_Smkca2->value());
    settings->setValue("NM_NOWOTNY_ET_AL_2008_CMKCA", ui->doubleSpinBox_cmkca->value());
    settings->setValue("NM_NOWOTNY_ET_AL_2008_KMKCA", ui->doubleSpinBox_kmkca->value());
    settings->setValue("NM_NOWOTNY_ET_AL_2008_CHKCA1", ui->doubleSpinBox_chkca1->value());
    settings->setValue("NM_NOWOTNY_ET_AL_2008_CHKCA2", ui->doubleSpinBox_chkca2->value());
    settings->setValue("NM_NOWOTNY_ET_AL_2008_KHKCA", ui->doubleSpinBox_khkca->value());
    settings->setValue("NM_NOWOTNY_ET_AL_2008_GA", ui->doubleSpinBox_ga->value());
    settings->setValue("NM_NOWOTNY_ET_AL_2008_VA", ui->doubleSpinBox_Va->value());
    settings->setValue("NM_NOWOTNY_ET_AL_2008_VAA", ui->doubleSpinBox_Vaa->value());
    settings->setValue("NM_NOWOTNY_ET_AL_2008_SAA", ui->doubleSpinBox_Saa->value());
    settings->setValue("NM_NOWOTNY_ET_AL_2008_VMA", ui->doubleSpinBox_Vma->value());
    settings->setValue("NM_NOWOTNY_ET_AL_2008_SMA", ui->doubleSpinBox_Sma->value());
    settings->setValue("NM_NOWOTNY_ET_AL_2008_KMA", ui->doubleSpinBox_kma->value());
    settings->setValue("NM_NOWOTNY_ET_AL_2008_VHA", ui->doubleSpinBox_Vha->value());
    settings->setValue("NM_NOWOTNY_ET_AL_2008_SHA", ui->doubleSpinBox_Sha->value());
    settings->setValue("NM_NOWOTNY_ET_AL_2008_KHA1", ui->doubleSpinBox_kha1->value());
    settings->setValue("NM_NOWOTNY_ET_AL_2008_KHA2", ui->doubleSpinBox_kha2->value());
    settings->setValue("NM_NOWOTNY_ET_AL_2008_VKHA2", ui->doubleSpinBox_Vkha2->value());
    settings->setValue("NM_NOWOTNY_ET_AL_2008_SKHA2", ui->doubleSpinBox_Skha2->value());
    settings->setValue("NM_NOWOTNY_ET_AL_2008_GH", ui->doubleSpinBox_gh->value());
    settings->setValue("NM_NOWOTNY_ET_AL_2008_VH", ui->doubleSpinBox_Vh->value());
    settings->setValue("NM_NOWOTNY_ET_AL_2008_VMH", ui->doubleSpinBox_Vmh->value());
    settings->setValue("NM_NOWOTNY_ET_AL_2008_SMH", ui->doubleSpinBox_Smh->value());
    settings->setValue("NM_NOWOTNY_ET_AL_2008_KMH", ui->doubleSpinBox_kmh->value());
    settings->setValue("NM_NOWOTNY_ET_AL_2008_VKMH", ui->doubleSpinBox_Vkmh->value());
    settings->setValue("NM_NOWOTNY_ET_AL_2008_SKMH", ui->doubleSpinBox_Skmh->value());
    settings->setValue("NM_NOWOTNY_ET_AL_2008_GLS", ui->doubleSpinBox_gls->value());
    settings->setValue("NM_NOWOTNY_ET_AL_2008_I", ui->doubleSpinBox_i->value());
    settings->setValue("NM_NOWOTNY_ET_AL_2008_IOFFSET", ui->doubleSpinBox_ioffset->value());
    settings->setValue("NM_NOWOTNY_ET_AL_2008_SYN", ui->doubleSpinBox_syn->value());
    settings->setValue("NM_NOWOTNY_ET_AL_2008_ISCALE", ui->doubleSpinBox_iscale->value());
    settings->setValue("NM_NOWOTNY_ET_AL_2008_CMS", ui->doubleSpinBox_Cms->value());
    settings->setValue("NM_NOWOTNY_ET_AL_2008_DT", ui->comboBoxIntegrationMethod->currentIndex());*/
}

void NM_GUI_Nowotny_et_al_2008::loadSettings() {
    /*if (settings->value("NM_NOWOTNY_ET_AL_2008_DT", -1).toInt() == -1) return; //No settings saved yet

    ui->doubleSpinBox_mna->setValue(settings->value("NM_NOWOTNY_ET_AL_2008_MNA").toDouble());
    ui->doubleSpinBox_hna->setValue(settings->value("NM_NOWOTNY_ET_AL_2008_HNA").toDouble());
    ui->doubleSpinBox_mkd->setValue(settings->value("NM_NOWOTNY_ET_AL_2008_MKD").toDouble());
    ui->doubleSpinBox_mm->setValue(settings->value("NM_NOWOTNY_ET_AL_2008_MM").toDouble());
    ui->doubleSpinBox_Vaxon->setValue(settings->value("NM_NOWOTNY_ET_AL_2008_VAXON").toDouble());
    ui->doubleSpinBox_mcat->setValue(settings->value("NM_NOWOTNY_ET_AL_2008_MCAT").toDouble());
    ui->doubleSpinBox_hcat->setValue(settings->value("NM_NOWOTNY_ET_AL_2008_HCAT").toDouble());
    ui->doubleSpinBox_mcas->setValue(settings->value("NM_NOWOTNY_ET_AL_2008_MCAS").toDouble());
    ui->doubleSpinBox_Ca->setValue(settings->value("NM_NOWOTNY_ET_AL_2008_CA").toDouble());
    ui->doubleSpinBox_mkca->setValue(settings->value("NM_NOWOTNY_ET_AL_2008_MKCA").toDouble());
    ui->doubleSpinBox_hkca->setValue(settings->value("NM_NOWOTNY_ET_AL_2008_HKCA").toDouble());
    ui->doubleSpinBox_ma->setValue(settings->value("NM_NOWOTNY_ET_AL_2008_MA").toDouble());
    ui->doubleSpinBox_ha1->setValue(settings->value("NM_NOWOTNY_ET_AL_2008_HA1").toDouble());
    ui->doubleSpinBox_ha2->setValue(settings->value("NM_NOWOTNY_ET_AL_2008_HA2").toDouble());
    ui->doubleSpinBox_mh->setValue(settings->value("NM_NOWOTNY_ET_AL_2008_MH").toDouble());
    ui->doubleSpinBox_V->setValue(settings->value("NM_NOWOTNY_ET_AL_2008_V").toDouble());

    ui->doubleSpinBox_gna->setValue(settings->value("NM_NOWOTNY_ET_AL_2008_GNA").toDouble());
    ui->doubleSpinBox_Vna->setValue(settings->value("NM_NOWOTNY_ET_AL_2008_VNA").toDouble());
    ui->doubleSpinBox_AreaAxon->setValue(settings->value("NM_NOWOTNY_ET_AL_2008_AREAAXON").toDouble());
    ui->doubleSpinBox_gkd->setValue(settings->value("NM_NOWOTNY_ET_AL_2008_GKD").toDouble());
    ui->doubleSpinBox_Vkd->setValue(settings->value("NM_NOWOTNY_ET_AL_2008_VKD").toDouble());
    ui->doubleSpinBox_gm->setValue(settings->value("NM_NOWOTNY_ET_AL_2008_GM").toDouble());
    ui->doubleSpinBox_Vm->setValue(settings->value("NM_NOWOTNY_ET_AL_2008_VM").toDouble());
    ui->doubleSpinBox_Vmm->setValue(settings->value("NM_NOWOTNY_ET_AL_2008_VMM").toDouble());
    ui->doubleSpinBox_Smm->setValue(settings->value("NM_NOWOTNY_ET_AL_2008_SMM").toDouble());
    ui->doubleSpinBox_kmm->setValue(settings->value("NM_NOWOTNY_ET_AL_2008_KMM").toDouble());
    ui->doubleSpinBox_Vkmm->setValue(settings->value("NM_NOWOTNY_ET_AL_2008_VKMM").toDouble());
    ui->doubleSpinBox_Skmm->setValue(settings->value("NM_NOWOTNY_ET_AL_2008_SKMM").toDouble());
    ui->doubleSpinBox_gla->setValue(settings->value("NM_NOWOTNY_ET_AL_2008_GLA").toDouble());
    ui->doubleSpinBox_Vl->setValue(settings->value("NM_NOWOTNY_ET_AL_2008_VL").toDouble());
    ui->doubleSpinBox_gvv->setValue(settings->value("NM_NOWOTNY_ET_AL_2008_GVV").toDouble());
    ui->doubleSpinBox_Cma->setValue(settings->value("NM_NOWOTNY_ET_AL_2008_CMA").toDouble());
    ui->doubleSpinBox_gcat->setValue(settings->value("NM_NOWOTNY_ET_AL_2008_GCAT").toDouble());
    ui->doubleSpinBox_gcas->setValue(settings->value("NM_NOWOTNY_ET_AL_2008_GCAS").toDouble());
    ui->doubleSpinBox_Pca->setValue(settings->value("NM_NOWOTNY_ET_AL_2008_PCA").toDouble());
    ui->doubleSpinBox_RTF->setValue(settings->value("NM_NOWOTNY_ET_AL_2008_RTF").toDouble());
    ui->doubleSpinBox_Caout->setValue(settings->value("NM_NOWOTNY_ET_AL_2008_CAOUT").toDouble());
    ui->doubleSpinBox_AreaSoma->setValue(settings->value("NM_NOWOTNY_ET_AL_2008_AREASOMA").toDouble());
    ui->doubleSpinBox_Vmcat->setValue(settings->value("NM_NOWOTNY_ET_AL_2008_VMCAT").toDouble());
    ui->doubleSpinBox_Smcat->setValue(settings->value("NM_NOWOTNY_ET_AL_2008_SMCAT").toDouble());
    ui->doubleSpinBox_kmcat->setValue(settings->value("NM_NOWOTNY_ET_AL_2008_KMCAT").toDouble());
    ui->doubleSpinBox_Vhcat->setValue(settings->value("NM_NOWOTNY_ET_AL_2008_VHCAT").toDouble());
    ui->doubleSpinBox_Shcat->setValue(settings->value("NM_NOWOTNY_ET_AL_2008_SHCAT").toDouble());
    ui->doubleSpinBox_khcat->setValue(settings->value("NM_NOWOTNY_ET_AL_2008_KHCAT").toDouble());
    ui->doubleSpinBox_Vkhcat->setValue(settings->value("NM_NOWOTNY_ET_AL_2008_VKHCAT").toDouble());
    ui->doubleSpinBox_Skhcat->setValue(settings->value("NM_NOWOTNY_ET_AL_2008_SKHCAT").toDouble());
    ui->doubleSpinBox_Vmcas->setValue(settings->value("NM_NOWOTNY_ET_AL_2008_VMCAS").toDouble());
    ui->doubleSpinBox_Smcas->setValue(settings->value("NM_NOWOTNY_ET_AL_2008_SMCAS").toDouble());
    ui->doubleSpinBox_kmcas->setValue(settings->value("NM_NOWOTNY_ET_AL_2008_KMCAS").toDouble());
    ui->doubleSpinBox_cica->setValue(settings->value("NM_NOWOTNY_ET_AL_2008_CICA").toDouble());
    ui->doubleSpinBox_kca->setValue(settings->value("NM_NOWOTNY_ET_AL_2008_KCA").toDouble());
    ui->doubleSpinBox_Ca0->setValue(settings->value("NM_NOWOTNY_ET_AL_2008_CA0").toDouble());
    ui->doubleSpinBox_gkca->setValue(settings->value("NM_NOWOTNY_ET_AL_2008_GKCA").toDouble());
    ui->doubleSpinBox_Vkca->setValue(settings->value("NM_NOWOTNY_ET_AL_2008_VKCA").toDouble());
    ui->doubleSpinBox_Vmkca1->setValue(settings->value("NM_NOWOTNY_ET_AL_2008_VMKCA1").toDouble());
    ui->doubleSpinBox_f->setValue(settings->value("NM_NOWOTNY_ET_AL_2008_F").toDouble());
    ui->doubleSpinBox_Smkca1->setValue(settings->value("NM_NOWOTNY_ET_AL_2008_SMKCA1").toDouble());
    ui->doubleSpinBox_Vmkca2->setValue(settings->value("NM_NOWOTNY_ET_AL_2008_VMKCA2").toDouble());
    ui->doubleSpinBox_Smkca2->setValue(settings->value("NM_NOWOTNY_ET_AL_2008_SMKCA2").toDouble());
    ui->doubleSpinBox_cmkca->setValue(settings->value("NM_NOWOTNY_ET_AL_2008_CMKCA").toDouble());
    ui->doubleSpinBox_kmkca->setValue(settings->value("NM_NOWOTNY_ET_AL_2008_KMKCA").toDouble());
    ui->doubleSpinBox_chkca1->setValue(settings->value("NM_NOWOTNY_ET_AL_2008_CHKCA1").toDouble());
    ui->doubleSpinBox_chkca2->setValue(settings->value("NM_NOWOTNY_ET_AL_2008_CHKCA2").toDouble());
    ui->doubleSpinBox_khkca->setValue(settings->value("NM_NOWOTNY_ET_AL_2008_KHKCA").toDouble());
    ui->doubleSpinBox_ga->setValue(settings->value("NM_NOWOTNY_ET_AL_2008_GA").toDouble());
    ui->doubleSpinBox_Va->setValue(settings->value("NM_NOWOTNY_ET_AL_2008_VA").toDouble());
    ui->doubleSpinBox_Vaa->setValue(settings->value("NM_NOWOTNY_ET_AL_2008_VAA").toDouble());
    ui->doubleSpinBox_Saa->setValue(settings->value("NM_NOWOTNY_ET_AL_2008_SAA").toDouble());
    ui->doubleSpinBox_Vma->setValue(settings->value("NM_NOWOTNY_ET_AL_2008_VMA").toDouble());
    ui->doubleSpinBox_Sma->setValue(settings->value("NM_NOWOTNY_ET_AL_2008_SMA").toDouble());
    ui->doubleSpinBox_kma->setValue(settings->value("NM_NOWOTNY_ET_AL_2008_KMA").toDouble());
    ui->doubleSpinBox_Vha->setValue(settings->value("NM_NOWOTNY_ET_AL_2008_VHA").toDouble());
    ui->doubleSpinBox_Sha->setValue(settings->value("NM_NOWOTNY_ET_AL_2008_SHA").toDouble());
    ui->doubleSpinBox_kha1->setValue(settings->value("NM_NOWOTNY_ET_AL_2008_KHA1").toDouble());
    ui->doubleSpinBox_kha2->setValue(settings->value("NM_NOWOTNY_ET_AL_2008_KHA2").toDouble());
    ui->doubleSpinBox_Vkha2->setValue(settings->value("NM_NOWOTNY_ET_AL_2008_VKHA2").toDouble());
    ui->doubleSpinBox_Skha2->setValue(settings->value("NM_NOWOTNY_ET_AL_2008_SKHA2").toDouble());
    ui->doubleSpinBox_gh->setValue(settings->value("NM_NOWOTNY_ET_AL_2008_GH").toDouble());
    ui->doubleSpinBox_Vh->setValue(settings->value("NM_NOWOTNY_ET_AL_2008_VH").toDouble());
    ui->doubleSpinBox_Vmh->setValue(settings->value("NM_NOWOTNY_ET_AL_2008_VMH").toDouble());
    ui->doubleSpinBox_Smh->setValue(settings->value("NM_NOWOTNY_ET_AL_2008_SMH").toDouble());
    ui->doubleSpinBox_kmh->setValue(settings->value("NM_NOWOTNY_ET_AL_2008_KMH").toDouble());
    ui->doubleSpinBox_Vkmh->setValue(settings->value("NM_NOWOTNY_ET_AL_2008_VKMH").toDouble());
    ui->doubleSpinBox_Skmh->setValue(settings->value("NM_NOWOTNY_ET_AL_2008_SKMH").toDouble());
    ui->doubleSpinBox_gls->setValue(settings->value("NM_NOWOTNY_ET_AL_2008_GLS").toDouble());
    ui->doubleSpinBox_i->setValue(settings->value("NM_NOWOTNY_ET_AL_2008_I").toDouble());
    ui->doubleSpinBox_ioffset->setValue(settings->value("NM_NOWOTNY_ET_AL_2008_IOFFSET").toDouble());
    ui->doubleSpinBox_syn->setValue(settings->value("NM_NOWOTNY_ET_AL_2008_SYN").toDouble());
    ui->doubleSpinBox_iscale->setValue(settings->value("NM_NOWOTNY_ET_AL_2008_ISCALE").toDouble());
    ui->doubleSpinBox_Cms->setValue(settings->value("NM_NOWOTNY_ET_AL_2008_CMS").toDouble());
    ui->comboBoxIntegrationMethod->setCurrentIndex(settings->value("NM_NOWOTNY_ET_AL_2008_DT").toInt());*/
}
