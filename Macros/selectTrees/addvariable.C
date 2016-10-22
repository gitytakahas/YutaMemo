#include <iostream>
#include <string>
#include "TFile.h"
#include "TTree.h"
#include "TMath.h"

void addvariable(TString filename, TString output, TString treename){
  
  std::cout << "input file = " <<  filename << std::endl;
  std::cout << "output file = " <<  output << std::endl;
  std::cout << "tree name = " <<  treename << std::endl;

  TFile *lFile = new TFile(filename);
  TTree *lTree = (TTree*) lFile->FindObjectAny(treename);

  Int_t b_channel = 0;
  lTree->SetBranchAddress("channel", &b_channel);

  TFile *lOFile = new TFile(output,"RECREATE");
  TTree *lOTree = lTree->CloneTree(0);
  lOTree->SetName("tree");
  //  Float_t lnewweight;
  //  lOTree->Branch("newweight", &lnewweight, "lnewweight/F");
   

  for (Long64_t i0=0; i0<lTree->GetEntries(); i0++) {
    lTree->GetEntry(i0);

    if(b_channel==1 && treename=="tree_mutau"){
      lOTree->Fill();
      //      std::cout << "mutau" << std::endl;
    }else if(b_channel==2 && treename=="tree_eletau"){
      lOTree->Fill();
    }
    //    lnewweight = 1;


  }

  lOTree->Write();
  lOFile->Close();

  delete lFile;

  lFile = 0; lTree = 0; lOTree = 0;

}

