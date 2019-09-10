#include "nm_xml_nowotny_et_al_2008.h"

/**
 * @file nm_xml_nowotny_et_al_2008.c
 * @brief Source file with the Nowotny_et_al_2008 neuron model functions.
 */

/**
 * @brief Imports the parameters of the Nowotny_et_al_2008 neuron model from an XML file.
 * @param[in] doc XML pointer to the document
 * @param[in] cur Cursor to navigate the XML file.
 * @param[in/out] args Pointer to the main arguments structure
 * @return #OK if it works, #ERR if there is an error
 */

int parse_nm_nowotny_et_al_2008 (xmlDocPtr doc, xmlNodePtr cur, clamp_args * args) {
	xmlNodePtr child =  NULL;
	int ret = OK;

	if ((!doc) || (!cur) || (!args)) return ERR;

	args->vars = (double*) malloc (sizeof(double) * 16);
	args->params = (double *) malloc (sizeof(double) * 75);

	while (cur != NULL) {
		if (xmlStrcmp(cur->name, (const xmlChar *) "vars") == 0) {
			child = cur->xmlChildrenNode;

			while (child != NULL) {

				if (xmlStrcmp(child->name, (const xmlChar *) "mna") == 0) ret = parse_double(doc, child, &args->vars[NM_NOWOTNY_ET_AL_2008_MNA], (const xmlChar*) VALUE);
				if (xmlStrcmp(child->name, (const xmlChar *) "hna") == 0) ret = parse_double(doc, child, &args->vars[NM_NOWOTNY_ET_AL_2008_HNA], (const xmlChar*) VALUE);
				if (xmlStrcmp(child->name, (const xmlChar *) "mkd") == 0) ret = parse_double(doc, child, &args->vars[NM_NOWOTNY_ET_AL_2008_MKD], (const xmlChar*) VALUE);
				if (xmlStrcmp(child->name, (const xmlChar *) "mm") == 0) ret = parse_double(doc, child, &args->vars[NM_NOWOTNY_ET_AL_2008_MM], (const xmlChar*) VALUE);
				if (xmlStrcmp(child->name, (const xmlChar *) "Vaxon") == 0) ret = parse_double(doc, child, &args->vars[NM_NOWOTNY_ET_AL_2008_VAXON], (const xmlChar*) VALUE);
				if (xmlStrcmp(child->name, (const xmlChar *) "mcat") == 0) ret = parse_double(doc, child, &args->vars[NM_NOWOTNY_ET_AL_2008_MCAT], (const xmlChar*) VALUE);
				if (xmlStrcmp(child->name, (const xmlChar *) "hcat") == 0) ret = parse_double(doc, child, &args->vars[NM_NOWOTNY_ET_AL_2008_HCAT], (const xmlChar*) VALUE);
				if (xmlStrcmp(child->name, (const xmlChar *) "mcas") == 0) ret = parse_double(doc, child, &args->vars[NM_NOWOTNY_ET_AL_2008_MCAS], (const xmlChar*) VALUE);
				if (xmlStrcmp(child->name, (const xmlChar *) "Ca") == 0) ret = parse_double(doc, child, &args->vars[NM_NOWOTNY_ET_AL_2008_CA], (const xmlChar*) VALUE);
				if (xmlStrcmp(child->name, (const xmlChar *) "mkca") == 0) ret = parse_double(doc, child, &args->vars[NM_NOWOTNY_ET_AL_2008_MKCA], (const xmlChar*) VALUE);
				if (xmlStrcmp(child->name, (const xmlChar *) "hkca") == 0) ret = parse_double(doc, child, &args->vars[NM_NOWOTNY_ET_AL_2008_HKCA], (const xmlChar*) VALUE);
				if (xmlStrcmp(child->name, (const xmlChar *) "ma") == 0) ret = parse_double(doc, child, &args->vars[NM_NOWOTNY_ET_AL_2008_MA], (const xmlChar*) VALUE);
				if (xmlStrcmp(child->name, (const xmlChar *) "ha1") == 0) ret = parse_double(doc, child, &args->vars[NM_NOWOTNY_ET_AL_2008_HA1], (const xmlChar*) VALUE);
				if (xmlStrcmp(child->name, (const xmlChar *) "ha2") == 0) ret = parse_double(doc, child, &args->vars[NM_NOWOTNY_ET_AL_2008_HA2], (const xmlChar*) VALUE);
				if (xmlStrcmp(child->name, (const xmlChar *) "mh") == 0) ret = parse_double(doc, child, &args->vars[NM_NOWOTNY_ET_AL_2008_MH], (const xmlChar*) VALUE);
				if (xmlStrcmp(child->name, (const xmlChar *) "V") == 0) ret = parse_double(doc, child, &args->vars[NM_NOWOTNY_ET_AL_2008_V], (const xmlChar*) VALUE);
				if (ret != OK) return ret;

				child = child->next;
			}
		}
		else if (xmlStrcmp(cur->name, (const xmlChar *) "params") == 0) {
			child = cur->xmlChildrenNode;

			while (child != NULL) {

				if (xmlStrcmp(child->name, (const xmlChar *) "gna") == 0) ret = parse_double(doc, child, &args->params[NM_NOWOTNY_ET_AL_2008_GNA], (const xmlChar*) VALUE);
				if (xmlStrcmp(child->name, (const xmlChar *) "Vna") == 0) ret = parse_double(doc, child, &args->params[NM_NOWOTNY_ET_AL_2008_VNA], (const xmlChar*) VALUE);
				if (xmlStrcmp(child->name, (const xmlChar *) "AreaAxon") == 0) ret = parse_double(doc, child, &args->params[NM_NOWOTNY_ET_AL_2008_AREAAXON], (const xmlChar*) VALUE);
				if (xmlStrcmp(child->name, (const xmlChar *) "gkd") == 0) ret = parse_double(doc, child, &args->params[NM_NOWOTNY_ET_AL_2008_GKD], (const xmlChar*) VALUE);
				if (xmlStrcmp(child->name, (const xmlChar *) "Vkd") == 0) ret = parse_double(doc, child, &args->params[NM_NOWOTNY_ET_AL_2008_VKD], (const xmlChar*) VALUE);
				if (xmlStrcmp(child->name, (const xmlChar *) "gm") == 0) ret = parse_double(doc, child, &args->params[NM_NOWOTNY_ET_AL_2008_GM], (const xmlChar*) VALUE);
				if (xmlStrcmp(child->name, (const xmlChar *) "Vm") == 0) ret = parse_double(doc, child, &args->params[NM_NOWOTNY_ET_AL_2008_VM], (const xmlChar*) VALUE);
				if (xmlStrcmp(child->name, (const xmlChar *) "Vmm") == 0) ret = parse_double(doc, child, &args->params[NM_NOWOTNY_ET_AL_2008_VMM], (const xmlChar*) VALUE);
				if (xmlStrcmp(child->name, (const xmlChar *) "Smm") == 0) ret = parse_double(doc, child, &args->params[NM_NOWOTNY_ET_AL_2008_SMM], (const xmlChar*) VALUE);
				if (xmlStrcmp(child->name, (const xmlChar *) "kmm") == 0) ret = parse_double(doc, child, &args->params[NM_NOWOTNY_ET_AL_2008_KMM], (const xmlChar*) VALUE);
				if (xmlStrcmp(child->name, (const xmlChar *) "Vkmm") == 0) ret = parse_double(doc, child, &args->params[NM_NOWOTNY_ET_AL_2008_VKMM], (const xmlChar*) VALUE);
				if (xmlStrcmp(child->name, (const xmlChar *) "Skmm") == 0) ret = parse_double(doc, child, &args->params[NM_NOWOTNY_ET_AL_2008_SKMM], (const xmlChar*) VALUE);
				if (xmlStrcmp(child->name, (const xmlChar *) "gla") == 0) ret = parse_double(doc, child, &args->params[NM_NOWOTNY_ET_AL_2008_GLA], (const xmlChar*) VALUE);
				if (xmlStrcmp(child->name, (const xmlChar *) "Vl") == 0) ret = parse_double(doc, child, &args->params[NM_NOWOTNY_ET_AL_2008_VL], (const xmlChar*) VALUE);
				if (xmlStrcmp(child->name, (const xmlChar *) "gvv") == 0) ret = parse_double(doc, child, &args->params[NM_NOWOTNY_ET_AL_2008_GVV], (const xmlChar*) VALUE);
				if (xmlStrcmp(child->name, (const xmlChar *) "Cma") == 0) ret = parse_double(doc, child, &args->params[NM_NOWOTNY_ET_AL_2008_CMA], (const xmlChar*) VALUE);
				if (xmlStrcmp(child->name, (const xmlChar *) "gcat") == 0) ret = parse_double(doc, child, &args->params[NM_NOWOTNY_ET_AL_2008_GCAT], (const xmlChar*) VALUE);
				if (xmlStrcmp(child->name, (const xmlChar *) "gcas") == 0) ret = parse_double(doc, child, &args->params[NM_NOWOTNY_ET_AL_2008_GCAS], (const xmlChar*) VALUE);
				if (xmlStrcmp(child->name, (const xmlChar *) "Pca") == 0) ret = parse_double(doc, child, &args->params[NM_NOWOTNY_ET_AL_2008_PCA], (const xmlChar*) VALUE);
				if (xmlStrcmp(child->name, (const xmlChar *) "RTF") == 0) ret = parse_double(doc, child, &args->params[NM_NOWOTNY_ET_AL_2008_RTF], (const xmlChar*) VALUE);
				if (xmlStrcmp(child->name, (const xmlChar *) "Caout") == 0) ret = parse_double(doc, child, &args->params[NM_NOWOTNY_ET_AL_2008_CAOUT], (const xmlChar*) VALUE);
				if (xmlStrcmp(child->name, (const xmlChar *) "AreaSoma") == 0) ret = parse_double(doc, child, &args->params[NM_NOWOTNY_ET_AL_2008_AREASOMA], (const xmlChar*) VALUE);
				if (xmlStrcmp(child->name, (const xmlChar *) "Vmcat") == 0) ret = parse_double(doc, child, &args->params[NM_NOWOTNY_ET_AL_2008_VMCAT], (const xmlChar*) VALUE);
				if (xmlStrcmp(child->name, (const xmlChar *) "Smcat") == 0) ret = parse_double(doc, child, &args->params[NM_NOWOTNY_ET_AL_2008_SMCAT], (const xmlChar*) VALUE);
				if (xmlStrcmp(child->name, (const xmlChar *) "kmcat") == 0) ret = parse_double(doc, child, &args->params[NM_NOWOTNY_ET_AL_2008_KMCAT], (const xmlChar*) VALUE);
				if (xmlStrcmp(child->name, (const xmlChar *) "Vhcat") == 0) ret = parse_double(doc, child, &args->params[NM_NOWOTNY_ET_AL_2008_VHCAT], (const xmlChar*) VALUE);
				if (xmlStrcmp(child->name, (const xmlChar *) "Shcat") == 0) ret = parse_double(doc, child, &args->params[NM_NOWOTNY_ET_AL_2008_SHCAT], (const xmlChar*) VALUE);
				if (xmlStrcmp(child->name, (const xmlChar *) "khcat") == 0) ret = parse_double(doc, child, &args->params[NM_NOWOTNY_ET_AL_2008_KHCAT], (const xmlChar*) VALUE);
				if (xmlStrcmp(child->name, (const xmlChar *) "Vkhcat") == 0) ret = parse_double(doc, child, &args->params[NM_NOWOTNY_ET_AL_2008_VKHCAT], (const xmlChar*) VALUE);
				if (xmlStrcmp(child->name, (const xmlChar *) "Skhcat") == 0) ret = parse_double(doc, child, &args->params[NM_NOWOTNY_ET_AL_2008_SKHCAT], (const xmlChar*) VALUE);
				if (xmlStrcmp(child->name, (const xmlChar *) "Vmcas") == 0) ret = parse_double(doc, child, &args->params[NM_NOWOTNY_ET_AL_2008_VMCAS], (const xmlChar*) VALUE);
				if (xmlStrcmp(child->name, (const xmlChar *) "Smcas") == 0) ret = parse_double(doc, child, &args->params[NM_NOWOTNY_ET_AL_2008_SMCAS], (const xmlChar*) VALUE);
				if (xmlStrcmp(child->name, (const xmlChar *) "kmcas") == 0) ret = parse_double(doc, child, &args->params[NM_NOWOTNY_ET_AL_2008_KMCAS], (const xmlChar*) VALUE);
				if (xmlStrcmp(child->name, (const xmlChar *) "cica") == 0) ret = parse_double(doc, child, &args->params[NM_NOWOTNY_ET_AL_2008_CICA], (const xmlChar*) VALUE);
				if (xmlStrcmp(child->name, (const xmlChar *) "kca") == 0) ret = parse_double(doc, child, &args->params[NM_NOWOTNY_ET_AL_2008_KCA], (const xmlChar*) VALUE);
				if (xmlStrcmp(child->name, (const xmlChar *) "Ca0") == 0) ret = parse_double(doc, child, &args->params[NM_NOWOTNY_ET_AL_2008_CA0], (const xmlChar*) VALUE);
				if (xmlStrcmp(child->name, (const xmlChar *) "gkca") == 0) ret = parse_double(doc, child, &args->params[NM_NOWOTNY_ET_AL_2008_GKCA], (const xmlChar*) VALUE);
				if (xmlStrcmp(child->name, (const xmlChar *) "Vkca") == 0) ret = parse_double(doc, child, &args->params[NM_NOWOTNY_ET_AL_2008_VKCA], (const xmlChar*) VALUE);
				if (xmlStrcmp(child->name, (const xmlChar *) "Vmkca1") == 0) ret = parse_double(doc, child, &args->params[NM_NOWOTNY_ET_AL_2008_VMKCA1], (const xmlChar*) VALUE);
				if (xmlStrcmp(child->name, (const xmlChar *) "f") == 0) ret = parse_double(doc, child, &args->params[NM_NOWOTNY_ET_AL_2008_F], (const xmlChar*) VALUE);
				if (xmlStrcmp(child->name, (const xmlChar *) "Smkca1") == 0) ret = parse_double(doc, child, &args->params[NM_NOWOTNY_ET_AL_2008_SMKCA1], (const xmlChar*) VALUE);
				if (xmlStrcmp(child->name, (const xmlChar *) "Vmkca2") == 0) ret = parse_double(doc, child, &args->params[NM_NOWOTNY_ET_AL_2008_VMKCA2], (const xmlChar*) VALUE);
				if (xmlStrcmp(child->name, (const xmlChar *) "Smkca2") == 0) ret = parse_double(doc, child, &args->params[NM_NOWOTNY_ET_AL_2008_SMKCA2], (const xmlChar*) VALUE);
				if (xmlStrcmp(child->name, (const xmlChar *) "cmkca") == 0) ret = parse_double(doc, child, &args->params[NM_NOWOTNY_ET_AL_2008_CMKCA], (const xmlChar*) VALUE);
				if (xmlStrcmp(child->name, (const xmlChar *) "kmkca") == 0) ret = parse_double(doc, child, &args->params[NM_NOWOTNY_ET_AL_2008_KMKCA], (const xmlChar*) VALUE);
				if (xmlStrcmp(child->name, (const xmlChar *) "chkca1") == 0) ret = parse_double(doc, child, &args->params[NM_NOWOTNY_ET_AL_2008_CHKCA1], (const xmlChar*) VALUE);
				if (xmlStrcmp(child->name, (const xmlChar *) "chkca2") == 0) ret = parse_double(doc, child, &args->params[NM_NOWOTNY_ET_AL_2008_CHKCA2], (const xmlChar*) VALUE);
				if (xmlStrcmp(child->name, (const xmlChar *) "khkca") == 0) ret = parse_double(doc, child, &args->params[NM_NOWOTNY_ET_AL_2008_KHKCA], (const xmlChar*) VALUE);
				if (xmlStrcmp(child->name, (const xmlChar *) "ga") == 0) ret = parse_double(doc, child, &args->params[NM_NOWOTNY_ET_AL_2008_GA], (const xmlChar*) VALUE);
				if (xmlStrcmp(child->name, (const xmlChar *) "Va") == 0) ret = parse_double(doc, child, &args->params[NM_NOWOTNY_ET_AL_2008_VA], (const xmlChar*) VALUE);
				if (xmlStrcmp(child->name, (const xmlChar *) "Vaa") == 0) ret = parse_double(doc, child, &args->params[NM_NOWOTNY_ET_AL_2008_VAA], (const xmlChar*) VALUE);
				if (xmlStrcmp(child->name, (const xmlChar *) "Saa") == 0) ret = parse_double(doc, child, &args->params[NM_NOWOTNY_ET_AL_2008_SAA], (const xmlChar*) VALUE);
				if (xmlStrcmp(child->name, (const xmlChar *) "Vma") == 0) ret = parse_double(doc, child, &args->params[NM_NOWOTNY_ET_AL_2008_VMA], (const xmlChar*) VALUE);
				if (xmlStrcmp(child->name, (const xmlChar *) "Sma") == 0) ret = parse_double(doc, child, &args->params[NM_NOWOTNY_ET_AL_2008_SMA], (const xmlChar*) VALUE);
				if (xmlStrcmp(child->name, (const xmlChar *) "kma") == 0) ret = parse_double(doc, child, &args->params[NM_NOWOTNY_ET_AL_2008_KMA], (const xmlChar*) VALUE);
				if (xmlStrcmp(child->name, (const xmlChar *) "Vha") == 0) ret = parse_double(doc, child, &args->params[NM_NOWOTNY_ET_AL_2008_VHA], (const xmlChar*) VALUE);
				if (xmlStrcmp(child->name, (const xmlChar *) "Sha") == 0) ret = parse_double(doc, child, &args->params[NM_NOWOTNY_ET_AL_2008_SHA], (const xmlChar*) VALUE);
				if (xmlStrcmp(child->name, (const xmlChar *) "kha1") == 0) ret = parse_double(doc, child, &args->params[NM_NOWOTNY_ET_AL_2008_KHA1], (const xmlChar*) VALUE);
				if (xmlStrcmp(child->name, (const xmlChar *) "kha2") == 0) ret = parse_double(doc, child, &args->params[NM_NOWOTNY_ET_AL_2008_KHA2], (const xmlChar*) VALUE);
				if (xmlStrcmp(child->name, (const xmlChar *) "Vkha2") == 0) ret = parse_double(doc, child, &args->params[NM_NOWOTNY_ET_AL_2008_VKHA2], (const xmlChar*) VALUE);
				if (xmlStrcmp(child->name, (const xmlChar *) "Skha2") == 0) ret = parse_double(doc, child, &args->params[NM_NOWOTNY_ET_AL_2008_SKHA2], (const xmlChar*) VALUE);
				if (xmlStrcmp(child->name, (const xmlChar *) "gh") == 0) ret = parse_double(doc, child, &args->params[NM_NOWOTNY_ET_AL_2008_GH], (const xmlChar*) VALUE);
				if (xmlStrcmp(child->name, (const xmlChar *) "Vh") == 0) ret = parse_double(doc, child, &args->params[NM_NOWOTNY_ET_AL_2008_VH], (const xmlChar*) VALUE);
				if (xmlStrcmp(child->name, (const xmlChar *) "Vmh") == 0) ret = parse_double(doc, child, &args->params[NM_NOWOTNY_ET_AL_2008_VMH], (const xmlChar*) VALUE);
				if (xmlStrcmp(child->name, (const xmlChar *) "Smh") == 0) ret = parse_double(doc, child, &args->params[NM_NOWOTNY_ET_AL_2008_SMH], (const xmlChar*) VALUE);
				if (xmlStrcmp(child->name, (const xmlChar *) "kmh") == 0) ret = parse_double(doc, child, &args->params[NM_NOWOTNY_ET_AL_2008_KMH], (const xmlChar*) VALUE);
				if (xmlStrcmp(child->name, (const xmlChar *) "Vkmh") == 0) ret = parse_double(doc, child, &args->params[NM_NOWOTNY_ET_AL_2008_VKMH], (const xmlChar*) VALUE);
				if (xmlStrcmp(child->name, (const xmlChar *) "Skmh") == 0) ret = parse_double(doc, child, &args->params[NM_NOWOTNY_ET_AL_2008_SKMH], (const xmlChar*) VALUE);
				if (xmlStrcmp(child->name, (const xmlChar *) "gls") == 0) ret = parse_double(doc, child, &args->params[NM_NOWOTNY_ET_AL_2008_GLS], (const xmlChar*) VALUE);
				if (xmlStrcmp(child->name, (const xmlChar *) "i") == 0) ret = parse_double(doc, child, &args->params[NM_NOWOTNY_ET_AL_2008_I], (const xmlChar*) VALUE);
				if (xmlStrcmp(child->name, (const xmlChar *) "ioffset") == 0) ret = parse_double(doc, child, &args->params[NM_NOWOTNY_ET_AL_2008_IOFFSET], (const xmlChar*) VALUE);
				if (xmlStrcmp(child->name, (const xmlChar *) "iscale") == 0) ret = parse_double(doc, child, &args->params[NM_NOWOTNY_ET_AL_2008_ISCALE], (const xmlChar*) VALUE);
				if (xmlStrcmp(child->name, (const xmlChar *) "Cms") == 0) ret = parse_double(doc, child, &args->params[NM_NOWOTNY_ET_AL_2008_CMS], (const xmlChar*) VALUE);
				if (xmlStrcmp(child->name, (const xmlChar *) "method") == 0) ret = parse_double(doc, child, &args->params[NM_NOWOTNY_ET_AL_2008_DT], (const xmlChar*) VALUE);

				if (ret != OK) return ret;

				child = child->next;
			}
		}

	cur = cur->next;
	}

	return OK;
}