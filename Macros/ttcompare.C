const int np = 2;
TString process[np] = {"No tt weight", "tt weight"};
Int_t color[np] = {2,4};


void makeplot(TString var, TString xtitle, Int_t nbin, Float_t xmin, Float_t xmax){

  TH1F *hist[np];

  TLegend *leg = new TLegend(0.2, 0.94,0.72,0.98);
  LegendSettings(leg);

  Float_t max = 0;

  TString filename[2] = {"BDT_training_ss_f12.root",
			 "BDT_training_ss_f12_weight.root"};

  for(int ifile=0; ifile < np; ifile++){

    TFile *file = new TFile(filename[ifile]);
    
    TString hname = "h_";
    hname += var;
    hname += "_";
    hname += ifile;
    
    hist[ifile] = new TH1F(hname, hname, nbin, xmin, xmax);
    hist[ifile]->Sumw2();
    InitHist(hist[ifile], xtitle, "", color[ifile]);
    
    TString dname = var;
    dname += " >> ";
    dname += hname;

    TString cond = "(bdt_evt_processid>=4 && bdt_evt_processid<=5)*abs(bdt_evt_weight)";

    Tree->Draw(dname, cond);    
    //    std::cout << process[ifile] << " " << hist[ifile]->GetSumOfWeights() << std::endl;

    hist[ifile]->SetLineWidth(2);
    hist[ifile]->SetMarkerSize(0.5);    
    //    hist[ifile]->Scale(1/hist[ifile]->GetSumOfWeights());
    leg->AddEntry(hist[ifile], process[ifile], "lep");

    if(hist[ifile]->GetMaximum() > max){
      max = hist[ifile]->GetMaximum();
    }
  }


  TString cname = var;
  cname += "_can";
  can = MakeCanvas(cname);

  for(int ip=0; ip < np; ip++){
    hist[ip]->SetMaximum(max*1.5);
    hist[ip]->SetMinimum(0);
    hist[ip]->GetXaxis()->SetTitle(xtitle);
    hist[ip]->GetYaxis()->SetTitle("a.u");

    std::cout << hist[ip]->GetSumOfWeights() << std::endl;
    if(ip==0) hist[ip]->Draw("he");
    else hist[ip]->Draw("hsame");

  }

  leg->Draw();
  TString savename = "ttcompare/";
  savename += cname;
  savename += "_compare_ttbar.gif";
  can->SaveAs(savename);
  
  file->Close();
}

void ttcompare(){
  
  gROOT->SetBatch(true);
  
  Int_t nbin = 20;

  makeplot("bdt_muon_pt", "muon pT (GeV)", nbin, 0, 200);
  makeplot("bdt_muon_eta", "muon eta", nbin, -3, 3);
  makeplot("bdt_muon_phi", "muon phi", nbin, -TMath::Pi(), TMath::Pi());
  makeplot("bdt_muon_MT", "muon MT", nbin, 0, 200);
  //  makeplot("bdt_muon_reliso", "muon relative isolation", nbin, 0, 1);
  //  makeplot("bdt_muon_dxy", "muon dxy", nbin, -1,1);
  //  makeplot("bdt_muon_dz", "muon dz", nbin, -1,1);
  //  makeplot("bdt_muon_dB3D", "muon dB3D", nbin, -1,1);

  makeplot("bdt_electron_pt", "electron pT (GeV)", nbin, 0, 200);
  makeplot("bdt_electron_eta", "electron eta", nbin, -3, 3);
  makeplot("bdt_electron_phi", "electron phi", nbin, -TMath::Pi(), TMath::Pi());
  makeplot("bdt_electron_MT", "electron MT", nbin, 0, 200);
  //  makeplot("bdt_electron_reliso", "electron relative isolation", nbin, 0, 1);
  //  makeplot("bdt_electron_dxy", "electron dxy", nbin, -1,1);
  //  makeplot("bdt_electron_dz", "electron dz", nbin, -1,1);
  //  makeplot("bdt_electron_dB3D", "electron dB3D", nbin, -1,1);

  makeplot("bdt_tau_pt", "tau pT (GeV)", nbin, 0, 200);
  makeplot("bdt_tau_eta", "tau eta", nbin, -3, 3);
  makeplot("bdt_tau_phi", "tau phi", nbin, -TMath::Pi(), TMath::Pi());
  makeplot("bdt_tau_MT", "tau MT", nbin, 0, 200);
  makeplot("bdt_tau_decaymode", "tau decaymode", 10, 0, 10);
  //  makeplot("bdt_tau_isolation", "tau isolation", nbin, 0, 100);
  //  makeplot("bdt_tau_dxy", "tau dxy", nbin, -1,1);
  //  makeplot("bdt_tau_dz", "tau dz", nbin, -1,1);
  //  makeplot("bdt_tau_dB3D", "tau dB3D", nbin, -1,1);

  makeplot("bdt_evt_Mem", "M(e#mu)", nbin, 0, 200);
  makeplot("bdt_evt_dphi_metmu", "#Delta#phi(met, #mu)", nbin, -2*TMath::Pi(), 2*TMath::Pi());
  makeplot("bdt_evt_dphi_mete", "#Delta#phi(met, e)", nbin, -2*TMath::Pi(), 2*TMath::Pi());
  makeplot("bdt_evt_dphi_mettau", "#Delta#phi(met, #tau)", nbin, -2*TMath::Pi(), 2*TMath::Pi());
  makeplot("bdt_evt_Met", "M(e, #tau)", nbin, 0,200);
  makeplot("bdt_evt_Mmt", "M(#mu, #tau)", nbin, 0,200);
  makeplot("bdt_evt_LT", "LT(sub leading lepton, #tau)", nbin, 0,300);
  makeplot("bdt_evt_sumjetpt", "#Sigma jet pT", nbin, 0,600);
  makeplot("bdt_evt_HT", "HT", nbin, 0,600);
  makeplot("bdt_evt_H", "H", nbin, 0,1500);
  makeplot("bdt_evt_centrality", "centrality", nbin, 0, 1);
  makeplot("bdt_evt_sphericity", "sphericity", nbin, 0, 1);
  makeplot("bdt_evt_aplanarity", "aplanarity", nbin, 0, 0.2);
  makeplot("bdt_evt_maxMT", "max MT", nbin, 0, 200);
  makeplot("bdt_evt_deltaeta", "#Delta#eta", nbin, -5, 5);
  makeplot("bdt_evt_njet_or", "Number of jet (OR)", 8, 0, 8);
  makeplot("bdt_evt_nbjet", "Number of bjet", 5, 0, 5);
  makeplot("bdt_evt_max_jet_eta", "Max jet eta", nbin, -5, 5);
  makeplot("bdt_evt_missing_et", "missing ET", nbin, 0, 200);
  makeplot("bdt_evt_missing_phi", "missing ET phi", nbin, -TMath::Pi(), TMath::Pi());
  makeplot("bdt_evt_leading_btag", "leading btag", nbin, 0.65, 1);
  makeplot("bdt_evt_sleading_btag", "sub leading btag", nbin, 0.65, 1);
  makeplot("bdt_evt_dr_mujet", "#Delta R (#mu, jet)", nbin, 0., 4);
  makeplot("bdt_evt_dr_ejet", "#Delta R (e, jet)", nbin, 0., 4);
  makeplot("bdt_evt_dr_taujet", "#Delta R (#tau, jet)", nbin, 0., 4);
  makeplot("bdt_evt_dr_ejet_csv", "CSV (e jet)", nbin, 0., 1.);
  makeplot("bdt_evt_dr_mujet_csv", "CSV (#mu jet)", nbin, 0., 1.);
  makeplot("bdt_evt_dr_taujet_csv", "CSV (#tau jet)", nbin, 0., 1.);


}
