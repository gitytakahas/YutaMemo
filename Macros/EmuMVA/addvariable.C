#include <iostream>
#include <string>
#include "TFile.h"
#include "TTree.h"
#include "TMath.h"

void addvariable(TString filename, TString output){
  
  std::cout << "input file = " <<  filename << std::endl;
  std::cout << "output file = " <<  output << std::endl;

  cout << "Processing " << filename << " -> " << output << endl;

  TFile *lFile = new TFile(filename);
  TTree *lTree = (TTree*) lFile->FindObjectAny("H2TauTauTreeProducerTauTau");

  Float_t l1_pt = 0;
  lTree->SetBranchAddress("l1Pt", &l1_pt);
  Float_t l2_pt = 0;
  lTree->SetBranchAddress("l2Pt", &l2_pt);


  TFile *lOFile = new TFile(output,"RECREATE");
  TTree *lOTree = lTree->CloneTree(0);
   
  Float_t lnewweight;
  lOTree->Branch("newweight", &lnewweight, "lnewweight/F");
   

  for (Long64_t i0=0; i0<lTree->GetEntries(); i0++) {
    lTree->GetEntry(i0);

    std::cout << l1_pt << " " << l2_pt << std::endl;
    lnewweight = 1;

    lOTree->Fill();    
  }

  lOTree->Write();
  lOFile->Close();

  delete lFile;

  lFile = 0; lTree = 0; lOTree = 0;

}

