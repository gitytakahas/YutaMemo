//TString fname = "BDT_training_ss_f3.root";
//TString fname = "BDT_training_ss_f12_antiE.root";
TString fname = "BDT_training_ss_f3_signal.root";
TFile *file = new TFile(fname);

//const int np = 6;  

//TString process[np] = {"VV", "signal", "ttH", "reducible", "tt", "data"};
//TString process_id[np] = {"bdt_evt_processid<=1",
//			  "bdt_evt_processid==6",
//			  "bdt_evt_processid==7",
//			  "bdt_evt_processid==8",
//			  "bdt_evt_processid==2 || bdt_evt_processid==3",
//			  "bdt_evt_processid==100"};
//Int_t color[np] = {2,3,4,5,6,1};

const int np = 5;  
TString process[np] = {"VV", "EWK", "reducible", "t#bar{t}", "data"};
TString process_id[np] = {"bdt_evt_processid<=2",
			  "bdt_evt_processid>=5 && bdt_evt_processid<=14",
			  "bdt_evt_processid==17",
			  "bdt_evt_processid==3 || bdt_evt_processid==4",
			  "bdt_evt_processid==100"};

Int_t color[np] = {2,8,3,4,1};

void makeplot(TTree *tree, TString var, TString xtitle, Int_t nbin, Float_t xmin, Float_t xmax){

  TH1F *hist[np];
  THStack *hs = new THStack();

  TLegend *leg = new TLegend(0.72,0.7,0.92,0.9);
  LegendSettings(leg);

  for(int ip=0; ip<np; ip++){

    TString hname = "h_";
    hname += var;
    hname += "_";
    hname += process[ip];
    
    hist[ip] = new TH1F(hname, hname, nbin, xmin, xmax);
    InitHist(hist[ip], xtitle, "", color[ip]);
    
    TString dname = var;
    dname += " >> ";
    dname += hname;

    TString cond = "(";
    cond += process_id[ip];
    cond += ")*bdt_evt_weight";

    tree->Draw(dname, cond);    
    std::cout << process[ip] << " " << hist[ip]->GetSumOfWeights() << std::endl;

    //    leg->AddEntry(hist[ip], process[ip], "f");

    if(process[ip]!="data"){
      hs->Add(hist[ip]);
      leg->AddEntry(hist[ip], process[ip], "f");
    }else{
      hist[ip]->SetLineWidth(2);
      hist[ip]->SetMarkerSize(0.5);
      leg->AddEntry(hist[ip], process[ip], "lep");
    }
  }

  TString fname = "frame_";
  fname += var;

  Float_t max = hs->GetMaximum()*2;
  if(max < hist[np-1]->GetMaximum()*2){
    max = hist[np-1]->GetMaximum()*2;
  }
  std::cout << max << std::endl;

  //  TH2F *frame = new TH2F(fname, fname, nbin, xmin, xmax, nbin, 0., max);
  //  frame->Draw();
  
  TString cname = var;
  cname += "_can";
  can = MakeCanvas(cname);

  //  if(max < hist[np-1]->GetMaximum()*1.2){
  hs->SetMaximum(max);
  //  hist[np-1]->SetMarkerStyle(20);
  hist[np-1]->SetMaximum(max);
  hist[np-1]->GetXaxis()->SetTitle(xtitle);
  hist[np-1]->GetYaxis()->SetTitle("Entries");
  hist[np-1]->Draw("e");
  hs->Draw("hsame");
  hist[np-1]->Draw("esame");

  leg->Draw();
  TString savename = cname;
  savename += ".gif";
  can->SaveAs(savename);
}

void draw(){

  gROOT->SetBatch(true);
  
  Int_t nbin = 20;

  makeplot(Tree, "bdt_muon_pt", "muon pT (GeV)", nbin, 0, 200);
  makeplot(Tree, "bdt_muon_eta", "muon eta", nbin, -3, 3);
  makeplot(Tree, "bdt_muon_phi", "muon phi", nbin, -TMath::Pi(), TMath::Pi());
  makeplot(Tree, "bdt_muon_MT", "muon MT", nbin, 0, 200);
  makeplot(Tree, "bdt_muon_reliso", "muon relative isolation", nbin, 0, 1);
  //  makeplot(Tree, "bdt_muon_dxy", "muon dxy", nbin, -1,1);
  //  makeplot(Tree, "bdt_muon_dz", "muon dz", nbin, -1,1);
  //  makeplot(Tree, "bdt_muon_dB3D", "muon dB3D", nbin, -1,1);

  makeplot(Tree, "bdt_electron_pt", "electron pT (GeV)", nbin, 0, 200);
  makeplot(Tree, "bdt_electron_eta", "electron eta", nbin, -3, 3);
  makeplot(Tree, "bdt_electron_phi", "electron phi", nbin, -TMath::Pi(), TMath::Pi());
  makeplot(Tree, "bdt_electron_MT", "electron MT", nbin, 0, 200);
  makeplot(Tree, "bdt_electron_reliso", "electron relative isolation", nbin, 0, 1);
  //  makeplot(Tree, "bdt_electron_dxy", "electron dxy", nbin, -1,1);
  //  makeplot(Tree, "bdt_electron_dz", "electron dz", nbin, -1,1);
  //  makeplot(Tree, "bdt_electron_dB3D", "electron dB3D", nbin, -1,1);

  makeplot(Tree, "bdt_tau_pt", "tau pT (GeV)", nbin, 0, 200);
  makeplot(Tree, "bdt_tau_eta", "tau eta", nbin, -3, 3);
  makeplot(Tree, "bdt_tau_phi", "tau phi", nbin, -TMath::Pi(), TMath::Pi());
  makeplot(Tree, "bdt_tau_MT", "tau MT", nbin, 0, 200);
  makeplot(Tree, "bdt_tau_decaymode", "tau decaymode", 10, 0, 10);
  makeplot(Tree, "bdt_tau_isolation", "tau isolation", nbin, 0, 100);
  //  makeplot(Tree, "bdt_tau_dxy", "tau dxy", nbin, -1,1);
  //  makeplot(Tree, "bdt_tau_dz", "tau dz", nbin, -1,1);
  //  makeplot(Tree, "bdt_tau_dB3D", "tau dB3D", nbin, -1,1);

  makeplot(Tree, "bdt_evt_Mem", "M(e#mu)", nbin, 0, 200);
  makeplot(Tree, "bdt_evt_dphi_metmu", "#Delta#phi(met, #mu)", nbin, -2*TMath::Pi(), 2*TMath::Pi());
  makeplot(Tree, "bdt_evt_dphi_mete", "#Delta#phi(met, e)", nbin, -2*TMath::Pi(), 2*TMath::Pi());
  makeplot(Tree, "bdt_evt_dphi_mettau", "#Delta#phi(met, #tau)", nbin, -2*TMath::Pi(), 2*TMath::Pi());
  makeplot(Tree, "bdt_evt_Met", "M(e, #tau)", nbin, 0,200);
  makeplot(Tree, "bdt_evt_Mmt", "M(#mu, #tau)", nbin, 0,200);
  makeplot(Tree, "bdt_evt_LT", "LT(sub leading lepton, #tau)", nbin, 0,300);
  makeplot(Tree, "bdt_evt_sumjetpt", "#Sigma jet pT", nbin, 0,600);
  makeplot(Tree, "bdt_evt_HT", "HT", nbin, 0,600);
  makeplot(Tree, "bdt_evt_H", "H", nbin, 0,1500);
  makeplot(Tree, "bdt_evt_centrality", "centrality", nbin, 0, 1);
  makeplot(Tree, "bdt_evt_sphericity", "sphericity", nbin, 0, 1);
  makeplot(Tree, "bdt_evt_aplanarity", "aplanarity", nbin, 0, 0.2);
  makeplot(Tree, "bdt_evt_maxMT", "max MT", nbin, 0, 200);
  makeplot(Tree, "bdt_evt_deltaeta", "#Delta#eta", nbin, -5, 5);
  makeplot(Tree, "bdt_evt_njet_or", "Number of jet (OR)", 8, 0, 8);
  makeplot(Tree, "bdt_evt_nbjet", "Number of bjet", 5, 0, 5);
  makeplot(Tree, "bdt_evt_max_jet_eta", "Max jet eta", nbin, -5, 5);
  makeplot(Tree, "bdt_evt_missing_et", "missing ET", nbin, 0, 200);
  makeplot(Tree, "bdt_evt_missing_phi", "missing ET phi", nbin, -TMath::Pi(), TMath::Pi());
  makeplot(Tree, "bdt_evt_leading_btag", "leading btag", nbin, 0.65, 1);
  makeplot(Tree, "bdt_evt_sleading_btag", "sub leading btag", nbin, 0.65, 1);
  makeplot(Tree, "bdt_evt_dr_mujet", "#Delta R (#mu, jet)", nbin, 0., 4);
  makeplot(Tree, "bdt_evt_dr_ejet", "#Delta R (e, jet)", nbin, 0., 4);
  makeplot(Tree, "bdt_evt_dr_taujet", "#Delta R (#tau, jet)", nbin, 0., 4);
  makeplot(Tree, "bdt_evt_dr_ejet_csv", "CSV (e jet)", nbin, 0., 1.);
  makeplot(Tree, "bdt_evt_dr_mujet_csv", "CSV (#mu jet)", nbin, 0., 1.);
  makeplot(Tree, "bdt_evt_dr_taujet_csv", "CSV (#tau jet)", nbin, 0., 1.);


}
