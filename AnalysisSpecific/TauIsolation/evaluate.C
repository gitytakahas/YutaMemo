#include <iostream>
#include <string>
#include "TFile.h"
#include "TTree.h"
#include "TString.h"
#include "TArrayF.h"
#include "TMath.h"

void evaluate(TString filename, TString output, TString param){
  
  std::cout << "input file = " << filename << std::endl;
  std::cout << "output file = " << output << std::endl;
  std::cout << "parameter file = " << param << std::endl;
  
  TString label[5] = {".root",
		      "_Weight1.root",
		      "_Weight1NQ.root",
		      "_Weight2.root",
		      "_Weight2NQ.root"};

  Float_t dbeta_barrel[5];
  Float_t dbeta_endcap[5];
  Float_t dbeta_all[5];

  Float_t offset_barrel[5];
  Float_t offset_endcap[5];
  Float_t offset_all[5];

  Float_t wrms_barrel[5];
  Float_t wrms_endcap[5];
  Float_t wrms_all[5];

  for(int ilabel=0; ilabel<5; ilabel++){
    TString pname = param;
    pname += label[ilabel];
    TFile *pfile = new TFile(pname);

    TH1F *h_dbeta_barrel = (TH1F*) gROOT->FindObject("dbeta_barrel_PUiso");
    TH1F *h_dbeta_endcap = (TH1F*) gROOT->FindObject("dbeta_endcap_PUiso");
    TH1F *h_dbeta_all = (TH1F*) gROOT->FindObject("dbeta_all_PUiso");
    
    TH1F *h_offset_barrel = (TH1F*) gROOT->FindObject("offset_barrel_PUiso");
    TH1F *h_offset_endcap = (TH1F*) gROOT->FindObject("offset_endcap_PUiso");
    TH1F *h_offset_all = (TH1F*) gROOT->FindObject("offset_all_PUiso");
    
    TH1F *h_wrms_barrel = (TH1F*) gROOT->FindObject("wrms_barrel_PUiso");
    TH1F *h_wrms_endcap = (TH1F*) gROOT->FindObject("wrms_endcap_PUiso");
    TH1F *h_wrms_all = (TH1F*) gROOT->FindObject("wrms_all_PUiso");

    dbeta_barrel[ilabel] = h_dbeta_barrel->GetMean();
    dbeta_endcap[ilabel] = h_dbeta_endcap->GetMean();
    dbeta_all[ilabel] = h_dbeta_all->GetMean();

    offset_barrel[ilabel] = h_offset_barrel->GetMean();
    offset_endcap[ilabel] = h_offset_endcap->GetMean();
    offset_all[ilabel] = h_offset_all->GetMean();
    
    wrms_barrel[ilabel] = h_wrms_barrel->GetMean();
    wrms_endcap[ilabel] = h_wrms_endcap->GetMean();
    wrms_all[ilabel] = h_wrms_all->GetMean();

  }
  

  TFile *lFile = new TFile(filename);
  TTree *lTree = (TTree*) lFile->FindObjectAny("TauTreeProducer");

  double ltau_eta = 0;
  lTree->SetBranchAddress("tau_eta", &ltau_eta);

  TFile *lOFile = new TFile(output,"RECREATE");
  TTree *lOTree = lTree->CloneTree(0);
   

  double tau_iso_dbeta;
  double tau_iso_offset;
  double tau_iso_wrms;
  double tau_iso_cmb_dbeta;
  double tau_iso_cmb_offset;
  double tau_iso_cmb_wrms;

  double tau_iso_dbetaWeight1;
  double tau_iso_offsetWeight1;
  double tau_iso_wrmsWeight1;
  double tau_iso_cmb_dbetaWeight1;
  double tau_iso_cmb_offsetWeight1;
  double tau_iso_cmb_wrmsWeight1;

  double tau_iso_dbetaWeight2;
  double tau_iso_offsetWeight2;
  double tau_iso_wrmsWeight2;
  double tau_iso_cmb_dbetaWeight2;
  double tau_iso_cmb_offsetWeight2;
  double tau_iso_cmb_wrmsWeight2;

  double tau_iso_dbetaWeight1NQ;
  double tau_iso_offsetWeight1NQ;
  double tau_iso_wrmsWeight1NQ;
  double tau_iso_cmb_dbetaWeight1NQ;
  double tau_iso_cmb_offsetWeight1NQ;
  double tau_iso_cmb_wrmsWeight1NQ;

  double tau_iso_dbetaWeight2NQ;
  double tau_iso_offsetWeight2NQ;
  double tau_iso_wrmsWeight2NQ;
  double tau_iso_cmb_dbetaWeight2NQ;
  double tau_iso_cmb_offsetWeight2NQ;
  double tau_iso_cmb_wrmsWeight2NQ;

  lOTree->Branch("tau_iso_dbeta", &tau_iso_dbeta, "tau_iso_dbeta/D");
  lOTree->Branch("tau_iso_offset", &tau_iso_offset, "tau_iso_offset/D");
  lOTree->Branch("tau_iso_wrms", &tau_iso_wrms, "tau_iso_wrms/D");
  lOTree->Branch("tau_iso_cmb_dbeta", &tau_iso_cmb_dbeta, "tau_iso_cmb_dbeta/D");
  lOTree->Branch("tau_iso_cmb_offset", &tau_iso_cmb_offset, "tau_iso_cmb_offset/D");
  lOTree->Branch("tau_iso_cmb_wrms", &tau_iso_cmb_wrms, "tau_iso_cmb_wrms/D");

  lOTree->Branch("tau_iso_dbetaWeight1", &tau_iso_dbetaWeight1, "tau_iso_dbetaWeight1/D");
  lOTree->Branch("tau_iso_offsetWeight1", &tau_iso_offsetWeight1, "tau_iso_offsetWeight1/D");
  lOTree->Branch("tau_iso_wrmsWeight1", &tau_iso_wrmsWeight1, "tau_iso_wrmsWeight1/D");
  lOTree->Branch("tau_iso_cmb_dbetaWeight1", &tau_iso_cmb_dbetaWeight1, "tau_iso_cmb_dbetaWeight1/D");
  lOTree->Branch("tau_iso_cmb_offsetWeight1", &tau_iso_cmb_offsetWeight1, "tau_iso_cmb_offsetWeight1/D");
  lOTree->Branch("tau_iso_cmb_wrmsWeight1", &tau_iso_cmb_wrmsWeight1, "tau_iso_cmb_wrmsWeight1/D");

  lOTree->Branch("tau_iso_dbetaWeight2", &tau_iso_dbetaWeight2, "tau_iso_dbetaWeight2/D");
  lOTree->Branch("tau_iso_offsetWeight2", &tau_iso_offsetWeight2, "tau_iso_offsetWeight2/D");
  lOTree->Branch("tau_iso_wrmsWeight2", &tau_iso_wrmsWeight2, "tau_iso_wrmsWeight2/D");
  lOTree->Branch("tau_iso_cmb_dbetaWeight2", &tau_iso_cmb_dbetaWeight2, "tau_iso_cmb_dbetaWeight2/D");
  lOTree->Branch("tau_iso_cmb_offsetWeight2", &tau_iso_cmb_offsetWeight2, "tau_iso_cmb_offsetWeight2/D");
  lOTree->Branch("tau_iso_cmb_wrmsWeight2", &tau_iso_cmb_wrmsWeight2, "tau_iso_cmb_wrmsWeight2/D");

  lOTree->Branch("tau_iso_dbetaWeight1NQ", &tau_iso_dbetaWeight1NQ, "tau_iso_dbetaWeight1NQ/D");
  lOTree->Branch("tau_iso_offsetWeight1NQ", &tau_iso_offsetWeight1NQ, "tau_iso_offsetWeight1NQ/D");
  lOTree->Branch("tau_iso_wrmsWeight1NQ", &tau_iso_wrmsWeight1NQ, "tau_iso_wrmsWeight1NQ/D");
  lOTree->Branch("tau_iso_cmb_dbetaWeight1NQ", &tau_iso_cmb_dbetaWeight1NQ, "tau_iso_cmb_dbetaWeight1NQ/D");
  lOTree->Branch("tau_iso_cmb_offsetWeight1NQ", &tau_iso_cmb_offsetWeight1NQ, "tau_iso_cmb_offsetWeight1NQ/D");
  lOTree->Branch("tau_iso_cmb_wrmsWeight1NQ", &tau_iso_cmb_wrmsWeight1NQ, "tau_iso_cmb_wrmsWeight1NQ/D");

  lOTree->Branch("tau_iso_dbetaWeight2NQ", &tau_iso_dbetaWeight2NQ, "tau_iso_dbetaWeight2NQ/D");
  lOTree->Branch("tau_iso_offsetWeight2NQ", &tau_iso_offsetWeight2NQ, "tau_iso_offsetWeight2NQ/D");
  lOTree->Branch("tau_iso_wrmsWeight2NQ", &tau_iso_wrmsWeight2NQ, "tau_iso_wrmsWeight2NQ/D");
  lOTree->Branch("tau_iso_cmb_dbetaWeight2NQ", &tau_iso_cmb_dbetaWeight2NQ, "tau_iso_cmb_dbetaWeight2NQ/D");
  lOTree->Branch("tau_iso_cmb_offsetWeight2NQ", &tau_iso_cmb_offsetWeight2NQ, "tau_iso_cmb_offsetWeight2NQ/D");
  lOTree->Branch("tau_iso_cmb_wrmsWeight2NQ", &tau_iso_cmb_wrmsWeight2NQ, "tau_iso_cmb_wrmsWeight2NQ/D");

  for (Long64_t i0=0; i0<lTree->GetEntries(); i0++) {
    lTree->GetEntry(i0);

    if(TMath::Abs(ltau_eta) < 1.479){
      tau_iso_dbeta = dbeta_barrel[0];
      tau_iso_offset = offset_barrel[0];
      tau_iso_wrms = wrms_barrel[0];

      tau_iso_dbetaWeight1 = dbeta_barrel[1];
      tau_iso_offsetWeight1 = offset_barrel[1];
      tau_iso_wrmsWeight1 = wrms_barrel[1];

      tau_iso_dbetaWeight1NQ = dbeta_barrel[2];
      tau_iso_offsetWeight1NQ = offset_barrel[2];
      tau_iso_wrmsWeight1NQ = wrms_barrel[2];

      tau_iso_dbetaWeight2 = dbeta_barrel[3];
      tau_iso_offsetWeight2 = offset_barrel[3];
      tau_iso_wrmsWeight2 = wrms_barrel[3];

      tau_iso_dbetaWeight2NQ = dbeta_barrel[4];
      tau_iso_offsetWeight2NQ = offset_barrel[4];
      tau_iso_wrmsWeight2NQ = wrms_barrel[4];

    }else if(TMath::Abs(ltau_eta) > 1.479){

      tau_iso_dbeta = dbeta_endcap[0];
      tau_iso_offset = offset_endcap[0];
      tau_iso_wrms = wrms_endcap[0];

      tau_iso_dbetaWeight1 = dbeta_endcap[1];
      tau_iso_offsetWeight1 = offset_endcap[1];
      tau_iso_wrmsWeight1 = wrms_endcap[1];

      tau_iso_dbetaWeight1NQ = dbeta_endcap[2];
      tau_iso_offsetWeight1NQ = offset_endcap[2];
      tau_iso_wrmsWeight1NQ = wrms_endcap[2];

      tau_iso_dbetaWeight2 = dbeta_endcap[3];
      tau_iso_offsetWeight2 = offset_endcap[3];
      tau_iso_wrmsWeight2 = wrms_endcap[3];

      tau_iso_dbetaWeight2NQ = dbeta_endcap[4];
      tau_iso_offsetWeight2NQ = offset_endcap[4];
      tau_iso_wrmsWeight2NQ = wrms_endcap[4];

    }

    tau_iso_cmb_dbeta = dbeta_all[0];
    tau_iso_cmb_offset = offset_all[0];
    tau_iso_cmb_wrms = wrms_all[0];

    tau_iso_cmb_dbetaWeight1 = dbeta_all[1];
    tau_iso_cmb_offsetWeight1 = offset_all[1];
    tau_iso_cmb_wrmsWeight1 = wrms_all[1];

    tau_iso_cmb_dbetaWeight1NQ = dbeta_all[2];
    tau_iso_cmb_offsetWeight1NQ = offset_all[2];
    tau_iso_cmb_wrmsWeight1NQ = wrms_all[2];

    tau_iso_cmb_dbetaWeight2 = dbeta_all[3];
    tau_iso_cmb_offsetWeight2 = offset_all[3];
    tau_iso_cmb_wrmsWeight2 = wrms_all[3];

    tau_iso_cmb_dbetaWeight2NQ = dbeta_all[4];
    tau_iso_cmb_offsetWeight2NQ = offset_all[4];
    tau_iso_cmb_wrmsWeight2NQ = wrms_all[4];

    lOTree->Fill();    
  }

  lOTree->Write();
  lOFile->Close();

  delete lFile;
  lFile = 0; lTree = 0; lOTree = 0;

}

