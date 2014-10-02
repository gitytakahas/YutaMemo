#define anal_cxx
#include "anal.h"
#include <TH2.h>
#include <TStyle.h>
#include <TCanvas.h>

void anal::StartLoop(){
  
  file = new TFile("Myroot.root","recreate");

  HO_tree = new TTree("HOAnalysis","HOAnalysis");
  HO_tree->Branch("r_HO_isSignal",&r_HO_isSignal,"r_HO_isSignal/I");
  HO_tree->Branch("r_HO_energy",&r_HO_energy,"r_HO_energy/F");
  HO_tree->Branch("r_HO_efrac",&r_HO_efrac,"r_HO_efrac/F");
  HO_tree->Branch("r_HO_eta",&r_HO_eta,"r_HO_eta/F");
  HO_tree->Branch("r_HO_phi",&r_HO_phi,"r_HO_phi/F");
  HO_tree->Branch("r_HO_jetenergy",&r_HO_jetenergy,"r_HO_jetenergy/F");
  HO_tree->Branch("r_HO_ieta",&r_HO_ieta,"r_HO_ieta/I");
  HO_tree->Branch("r_HO_abs_ieta",&r_HO_abs_ieta,"r_HO_abs_ieta/I");
  HO_tree->Branch("r_HO_iphi",&r_HO_iphi,"r_HO_iphi/I");

  Event_tree = new TTree("EventAnalysis","EventAnalysis");
  Event_tree->Branch("r_njet",&r_njet,"r_njet/I");
  Event_tree->Branch("r_nHO",&r_nHO,"r_nHO/I");
  Event_tree->Branch("r_nHO_isSignal",&r_nHO_isSignal,"r_nHO_isSignal/I");
  Event_tree->Branch("r_met",&r_met,"r_met/F");
  Event_tree->Branch("r_met2",&r_met2,"r_met2/F");
  Event_tree->Branch("r_nmuon",&r_nmuon,"r_nmuon/I");
  Event_tree->Branch("r_nelectron",&r_nelectron,"r_nelectron/I");
  Event_tree->Branch("r_maxjfrac",&r_maxjfrac,"r_maxjfrac/F");
  Event_tree->Branch("r_maxHO",&r_maxHO,"r_maxHO/F");
  Event_tree->Branch("r_HO20",&r_HO20,"r_HO20/I");
  Event_tree->Branch("r_HO30",&r_HO30,"r_HO30/I");
  Event_tree->Branch("r_HO40",&r_HO40,"r_HO40/I");
  Event_tree->Branch("r_HO50",&r_HO50,"r_HO50/I");
  Event_tree->Branch("r_HO70",&r_HO70,"r_HO70/I");

  Jet_tree = new TTree("JetAnalysis","JetAnalysis");
  Jet_tree->Branch("r_jet_pt",&r_jet_pt,"r_jet_pt/F");
  Jet_tree->Branch("r_gjet_pt",&r_gjet_pt,"r_gjet_pt/F");
  Jet_tree->Branch("r_gjet_eta",&r_gjet_eta,"r_gjet_eta/F");
  Jet_tree->Branch("r_gjet_phi",&r_gjet_phi,"r_gjet_phi/F");
  Jet_tree->Branch("r_jet_eta",&r_jet_eta,"r_jet_eta/F");
  Jet_tree->Branch("r_jet_phi",&r_jet_phi,"r_jet_phi/F");
  Jet_tree->Branch("r_jet_dr",&r_jet_dr,"r_jet_dr/F");
  Jet_tree->Branch("r_jet_pt_wHO",&r_jet_pt_wHO,"r_jet_pt_wHO/F");
  Jet_tree->Branch("r_jet_HO_match",&r_jet_HO_match,"r_jet_HO_match/I");
  Jet_tree->Branch("r_jet_HOenergy",&r_jet_HOenergy,"r_jet_HOenergy/F");

  Muon_tree = new TTree("MuonAnalysis","MuonAnalysis");
  Muon_tree->Branch("isMatch",&isMatch,"isMatch/I");
  Muon_tree->Branch("r_muon_pt",&r_muon_pt,"r_muon_pt/F");
  Muon_tree->Branch("r_muon_eta",&r_muon_eta,"r_muon_eta/F");
  Muon_tree->Branch("r_muon_phi",&r_muon_phi,"r_muon_phi/F");


  for(int iphi=0; iphi<72; iphi++){
    for(int ieta=0; ieta<21; ieta++){
      TString hname = "h_ho_phi";
      hname += iphi;
      hname += "_eta";
      hname += ieta;
	
      h_ho[iphi][ieta] = new TH1F(hname, hname, 30,0,200);
    }
  }

  for(int ieta=0; ieta<10; ieta++){
    TString hname = "h_ho_signal_eta";
    hname += ieta;
    
    h_ho_signal[ieta] = new TH1F(hname, hname, 30,0,200);

    hname = "h_ho_noise_eta";
    hname += ieta;
    
    h_ho_noise[ieta] = new TH1F(hname, hname, 30,0,200);

    hname = "h_ho_muon_signal_eta";
    hname += ieta;
    
    h_ho_muon_signal[ieta] = new TH1F(hname, hname, 30,0,200);

    hname = "h_ho_muon_noise_eta";
    hname += ieta;
    
    h_ho_muon_noise[ieta] = new TH1F(hname, hname, 30,0,200);
}

  for(int iho=0; iho<2; iho++){
    for(int ijet=0; ijet<20; ijet++){
      TString hname = (iho==0) ? "h_noho_jet_" : "h_ho_jet";
      hname += ijet;

      h_jet_resolution[iho][ijet] = new TH1F(hname, hname, 100,0,3000);
    }
  }

}
void anal::EndLoop(){
  file->Write();
  file->Close();
}


Float_t returndR(Float_t eta1, Float_t eta2, Float_t phi1, Float_t phi2){
  Float_t deta = (eta1-eta2);
  Float_t dphi = (phi1-phi2);
  Float_t dr = TMath::Sqrt(deta*deta+dphi*dphi);
  return dr;
}

Float_t returnPhiID(Float_t phi){
  Int_t iphi = phi/0.087;
  if(phi < 0) iphi = int(36. + (TMath::Pi() + phi)/0.087);
  return iphi;
}
	
Float_t returnEtaID(Float_t eta){
  //  Int_t ieta = int(9. + eta/0.087);
  Int_t ieta = int(TMath::Abs(eta)/0.087);
  
  Int_t _eta_ = 0;
  if(eta > 0) _eta_ = ieta + 1;
  else _eta_ = -ieta - 1;
  return _eta_;
}

Float_t returnAbsEtaID(Float_t eta){
  Int_t ieta = int(TMath::Abs(eta)/0.087);
  return ieta;
}



void anal::Loop()
{

  if (fChain == 0) return;

  Long64_t nentries = fChain->GetEntriesFast();
  Long64_t nbytes = 0, nb = 0;

  for (Long64_t jentry=0; jentry < nentries;jentry++) {
    Long64_t ientry = LoadTree(jentry);
    if (ientry < 0) break;
    nb = fChain->GetEntry(jentry);   nbytes += nb;

    if(jentry%10000==0){
      std::cout << jentry << "/" << fChain->GetEntries() << std::endl;
    }


    /*
     * HO loop
     */

    Float_t max_jfrac = -999;
    Float_t maxHO = -999;
    Int_t HO_isSignal = 0;

    Bool_t flag_HO20 = false;
    Bool_t flag_HO30 = false;
    Bool_t flag_HO40 = false;
    Bool_t flag_HO50 = false;
    Bool_t flag_HO70 = false;

    for(int iho=0; iho < HO_; iho++){
	
      bool flag_associatedjet = false;
      Float_t ho_eta = HO_eta[iho];
      Float_t ho_phi = HO_phi[iho];
      Float_t ho_energy = HO_pt[iho];
      Int_t iphi = returnPhiID(ho_phi);
      Int_t ieta = returnEtaID(ho_eta);
      //      Int_t abs_ieta = returnAbsEtaID(ho_eta);
      Int_t abs_ieta = TMath::Abs(ieta);

      if(ho_energy < 5) continue;

      if(ho_energy > 20) flag_HO20 = true;
      if(ho_energy > 30) flag_HO30 = true;
      if(ho_energy > 40) flag_HO40 = true;
      if(ho_energy > 50) flag_HO50 = true;
      if(ho_energy > 70) flag_HO70 = true;


      if(ho_energy > maxHO){
	maxHO = ho_energy;
      }

      Float_t min_jet_energy = -1;
      Float_t min_dr = 999;

      for(int ijet=0; ijet < PFJet_; ijet++){
	if(PFJet_pt[ijet] < 50) continue;
	Float_t jet_eta = PFJet_eta[ijet];
	Float_t jet_phi = PFJet_phi[ijet];
	Float_t dR = returndR(jet_eta, ho_eta, jet_phi, ho_phi);

	if(dR < 0.5 && min_dr > dR){
	  flag_associatedjet = true;
	  min_dr = dR;
	  min_jet_energy = PFJet_pt[ijet];
	}
      }
	
      Float_t frac = (float)(ho_energy/min_jet_energy);

      r_HO_energy = ho_energy;
      r_HO_jetenergy = min_jet_energy;
      r_HO_efrac = frac;
      r_HO_eta = ho_eta;
      r_HO_phi = ho_phi;
      r_HO_ieta = ieta;
      r_HO_abs_ieta = abs_ieta;
      r_HO_iphi = iphi;
      r_HO_isSignal = flag_associatedjet;

      if(flag_associatedjet) HO_isSignal++;
      HO_tree->Fill();


      if(max_jfrac < frac && frac > 0){
	max_jfrac = frac;
      }
	

      if(flag_associatedjet==false){
	if(iphi < 72 and ieta >= -10 && ieta <= 10){
	  h_ho[iphi][ieta+10]->Fill(ho_energy);
	}else{
	  std::cout << iphi << " " << ieta << std::endl;
	}
      }
      

      if(abs_ieta<=10){
	if(flag_associatedjet) h_ho_signal[abs_ieta-1]->Fill(ho_energy);
	else h_ho_noise[abs_ieta-1]->Fill(ho_energy);
      }

      
      
      Bool_t flag_associatedmuon = false;
      for(int imuon=0; imuon<Muon_;imuon++){
	if(Muon_pt[imuon] < 10) continue;
	if(Muon_nTkHits[imuon] + Muon_nPixHits[imuon] <= 5) continue;
	if(Muon_muNchi2[imuon] > 10) continue;
	if(Muon_nMatch[imuon] <=1 ) continue;

	Float_t muon_eta = Muon_eta[imuon];
	Float_t muon_phi = Muon_phi[imuon];
	Float_t dR = returndR(muon_eta, ho_eta, muon_phi, ho_phi);

	if(dR < 0.3){
	  flag_associatedmuon = true;
	}
      }


      if(abs_ieta<=10){
	if(flag_associatedmuon) h_ho_muon_signal[abs_ieta-1]->Fill(ho_energy);
	else h_ho_muon_noise[abs_ieta-1]->Fill(ho_energy);
      }
	
    }

    /*
     * Jet loop
     */

    for(int ijet=0; ijet < PFJet_; ijet++){
      Float_t jet_pt = PFJet_pt[ijet];
      Float_t jet_eta = PFJet_eta[ijet];
      Float_t jet_phi = PFJet_phi[ijet];
      Bool_t flag_HO = false;

      Float_t min_ho_energy = 999;
      Float_t min_ho_dr = 999;

      for(int iho=0; iho < HO_; iho++){
	
	Float_t ho_eta = HO_eta[iho];
	Float_t ho_phi = HO_phi[iho];
	Float_t ho_energy = HO_pt[iho];
	if(ho_energy < 5) continue;

	Float_t dR = returndR(jet_eta, ho_eta, jet_phi, ho_phi);
	
	if(dR < 0.5 && min_ho_dr > dR){
	  flag_HO = true;
	  min_ho_dr = dR;
	  min_ho_energy = ho_energy;
	}
      }

      Float_t min_jet_dr = 999;
      Float_t min_jet_pt = 999;

      for(int ijet2=0; ijet2 < PFJet2_; ijet2++){
	Float_t jet_pt2 = PFJet2_pt[ijet2];
	Float_t jet_eta2 = PFJet2_eta[ijet2];
	Float_t jet_phi2 = PFJet2_phi[ijet2];
	Float_t dR = returndR(jet_eta, jet_eta2, jet_phi, jet_phi2);

	if(dR < 0.3 && min_jet_dr > dR){
	  min_jet_dr = dR;
	  min_jet_pt = jet_pt2;
	}
      }
	

      // association of the genjets
      Float_t min_gjet_dr = 999;
      Float_t min_gjet_pt = 999;
      Float_t min_gjet_eta = 999;
      Float_t min_gjet_phi = 999;

      for(int genjet=0; genjet < GenJet_; genjet++){
	Float_t gjet_pt = GenJet_pt[genjet];
	Float_t gjet_eta = GenJet_eta[genjet];
	Float_t gjet_phi = GenJet_phi[genjet];
	Float_t dR = returndR(jet_eta, gjet_eta, gjet_phi, gjet_phi);
	
	if(dR < 0.3 && min_gjet_dr > dR){
	  min_gjet_dr = dR;
	  min_gjet_pt = gjet_pt;
	  min_gjet_eta = gjet_eta;
	  min_gjet_phi = gjet_phi;
	}
      }

      
      r_jet_pt = jet_pt;
      r_gjet_pt = min_gjet_pt;
      r_gjet_eta = min_gjet_eta;
      r_gjet_phi = min_gjet_phi;
      r_jet_eta = jet_eta;
      r_jet_phi = jet_phi;
      r_jet_HO_match = flag_HO;
      r_jet_HOenergy = min_ho_energy;
      r_jet_dr = min_jet_dr;
      r_jet_pt_wHO = min_jet_pt;
      Jet_tree->Fill();


      //      if(flag_HO==true && min_jet_pt!=999 && jet_pt!=999){
      //      if(flag_HO==true && min_jet_pt!=999 && jet_pt!=999){
      if(flag_HO==true){

	Int_t ibin_jet = (jet_pt/150.);
	//	std::cout << jet_pt << " " << ibin_jet << std::endl;
	if(ibin_jet >=0 && ibin_jet <20){
	  h_jet_resolution[1][ibin_jet]->Fill(jet_pt);
	}

//	Int_t ibin_jet_noho = (min_jet_pt/150.);
//
//	if(ibin_jet_noho >=0 && ibin_jet_noho <20){
//	  h_jet_resolution[0][ibin_jet_noho]->Fill(min_jet_pt);
//	}
      }


    }

    Int_t nmuon = 0;
    for(int imuon=0; imuon<Muon_;imuon++){
      if(Muon_pt[imuon] < 10) continue;
      if(Muon_nTkHits[imuon] + Muon_nPixHits[imuon] <= 5) continue;
      if(Muon_muNchi2[imuon] > 10) continue;
      if(Muon_nMatch[imuon] <=1 ) continue;

      nmuon++;

      Bool_t muon_match = false;
      for(int igen=0; igen<GenParticle_; igen++){
	if(TMath::Abs(GenParticle_pdgid[igen])!=13) continue;
	//	if(GenParticle_status[igen]!=1) continue;
	
	Float_t gen_eta = GenParticle_eta[igen];
	Float_t gen_phi = GenParticle_phi[igen];
	Float_t muon_eta = Muon_eta[imuon];
	Float_t muon_phi = Muon_phi[imuon];
	
	Float_t dR = returndR(muon_eta, gen_eta, muon_phi, gen_phi);
	
	if(dR < 0.5){
	  muon_match = true;
	}
      }

      
      isMatch = muon_match;
      r_muon_pt = Muon_pt[imuon];
      r_muon_eta = Muon_eta[imuon];
      r_muon_phi = Muon_phi[imuon];
      Muon_tree->Fill();
    }



    /*
     * Event loop
     */


    r_nHO = HO_;
    r_njet = PFJet_;
    r_nHO_isSignal = HO_isSignal;
    r_met = MET;
    r_met2 = MET2;
    r_maxjfrac = max_jfrac;
    r_maxHO = maxHO;
    r_HO20 = flag_HO20;
    r_HO30 = flag_HO30;
    r_HO40 = flag_HO40;
    r_HO50 = flag_HO50;
    r_HO70 = flag_HO70;
    r_nmuon = nmuon;
    r_nelectron = Electron_;



    for(int ijet=0; ijet < PFJet2_; ijet++){
      Float_t jet_pt = PFJet2_pt[ijet];
      Int_t ibin_jet_noho = (jet_pt/150.);
      
      if(ibin_jet_noho >=0 && ibin_jet_noho <20){
	h_jet_resolution[0][ibin_jet_noho]->Fill(jet_pt);
      }
	

      
    }

      
    Event_tree->Fill();

  }
}
