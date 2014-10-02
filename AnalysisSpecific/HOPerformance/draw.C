void draw(){

  /*
   * Jet resolution
   */
  
  TFile *file = new TFile("Myroot.root");

  TH1F *h = new TH1F("h","h",100,-0.5,0.5);
  TH1F *h2 = new TH1F("h2","h2",100,-0.5,0.5);

  JetAnalysis->Draw("(r_jet_pt-r_gjet_pt)/r_gjet_pt >> h","r_jet_pt_wHO!=999 && r_jet_HO_match==1 && r_gjet_pt!=999");
  JetAnalysis->Draw("(r_jet_pt_wHO-r_gjet_pt)/r_gjet_pt >> h2","r_jet_pt_wHO !=999 && r_jet_HO_match==1 && r_gjet_pt !=999");

  TCanvas *c = MakeCanvas("Jet_resolution");
  InitHist(h, "(E_{reco} - E_{gen})/E_{gen}","Events",1);
  InitHist(h2, "","",2);
  
  h->SetLineWidth(3);

  h->Draw("hep");
  h2->Draw("hepsame");

  TLegend *leg = new TLegend(0.6,0.6,0.8,0.9);
  LegendSettings(leg);
  addLegend(h2, leg, "w/o HO", 3, 1);
  addLegend(h, leg, "w/ HO", 3, 1);

  leg->Draw();
  c->SaveAs("jet_resolution.gif");

  MakeCanvas("temp");


  /*
   * MET comparison
   */

  TH1F *h_met[2][5];
  TString gname[5] = {"r_HO20","r_HO30","r_HO40","r_HO50","r_HO70"};
  TString tname[5] = {"HO > 20 GeV","HO > 30 GeV","HO > 40 GeV","HO > 50 GeV","HO > 70 GeV"};

  for(int iho=0; iho<2; iho++){
    for(int ith=0; ith<5; ith++){
      
      TString hname = (iho==0) ? "h_noho_" : "h_ho_";
      hname += ith;

      h_met[iho][ith] = new TH1F(hname, hname, 50,0,1000);
      InitHist(h_met[iho][ith], "E_{T}^{miss} (GeV)","",iho+1);

      TString cname = (iho==0) ? "r_met2 >> " : "r_met >> ";
      cname += hname;
      
      TString dname = gname[ith];
      dname += "==1";

      EventAnalysis->Draw(cname, dname);

    }
  }

  TCanvas *can = (TCanvas*) MakeCanvas("MET",950,700);
  can->Divide(3,2);

  TLegend *leg_met[5];

  for(int ith=0; ith<5; ith++){

    can->cd(ith+1);

    h_met[1][ith]->Draw("hep");
    h_met[0][ith]->Draw("hepsame");
    
    leg_met[ith] = new TLegend(0.32,0.67,0.88,0.9);
    LegendSettings(leg_met[ith]);
    
    addLegend(h_met[0][ith], leg_met[ith], "w/o HO", 1);
    addLegend(h_met[1][ith], leg_met[ith], "w/ HO", 1);
    leg_met[ith]->AddEntry(h_met[1][ith], tname[ith], "");

    leg_met[ith]->Draw();
  }

  can->SaveAs("met_comparison_HOcut.gif");


  /*
   * Jet resolution as a function of jet pT, eta
   */

  TCanvas *can_pt = (TCanvas *) MakeCanvas("resolution_pt");
  TLegend *leg_jet_pt = new TLegend(0.32,0.67,0.88,0.9);
  TLegend *leg_jet_eta = new TLegend(0.42,0.21,0.88,0.44);
  LegendSettings(leg_jet_pt);
  LegendSettings(leg_jet_eta);

  TH2F* h_resolution_pt[2];
  TH2F* h_resolution_eta[2];

  TH1D* h_profile_pt[2];
  TH1D* h_profile_eta[2];

  for(int iho=0; iho<2; iho++){

    TString hname = (iho==0) ? "h_res_pt_ho" : "h_res_pt_noho";
    h_resolution_pt[iho] = new TH2F(hname, hname, 20,0,3000,100,-1,1);
      
    TString cname = (iho==0) ? "(r_jet_pt-r_gjet_pt)/r_gjet_pt:r_gjet_pt >> " : "(r_jet_pt_wHO-r_gjet_pt)/r_gjet_pt:r_gjet_pt >> ";
    cname += hname;
    //    JetAnalysis->Draw(cname,"r_jet_pt_wHO !=999 && r_jet_HO_match==1 && r_gjet_pt !=999");
    JetAnalysis->Draw(cname,"r_jet_pt_wHO !=999 && r_gjet_pt !=999");

    h_profile_pt[iho] = (TH1D*) h_resolution_pt[iho]->ProfileX();
    InitHist(h_profile_pt[iho], "Genjet pT (GeV)","(E_{reco} - E_{gen})/E_{gen}",2-iho);

    hname = (iho==0) ? "h_res_eta_ho" : "h_res_eta_noho";
    h_resolution_eta[iho] = new TH2F(hname, hname, 20,-5,5,100,-1,1);
      
    cname = (iho==0) ? "(r_jet_pt-r_gjet_pt)/r_gjet_pt:r_gjet_eta >> " : "(r_jet_pt_wHO-r_gjet_pt)/r_gjet_pt:r_gjet_eta >> ";
    cname += hname;
    JetAnalysis->Draw(cname,"r_jet_pt_wHO !=999 && r_gjet_pt !=999");

    h_profile_eta[iho] = (TH1D*) h_resolution_eta[iho]->ProfileX();
    InitHist(h_profile_eta[iho], "Genjet #eta","(E_{reco} - E_{gen})/E_{gen}",2-iho);
  }
  

  h_profile_pt[1]->Draw("");
  h_profile_pt[0]->Draw("same");

  addLegend(h_profile_pt[1], leg_jet_pt, "w/o HO", 1,2);
  addLegend(h_profile_pt[0], leg_jet_pt, "w/ HO", 1,2);
  
  leg_jet_pt->Draw();

  can_pt->SaveAs("jet_resolution_pt_dep.gif");

  TCanvas *can_eta = (TCanvas*) MakeCanvas("resolution_eta");

  h_profile_eta[1]->Draw("");
  h_profile_eta[0]->Draw("same");


  addLegend(h_profile_eta[1], leg_jet_eta, "w/o HO", 1,2);
  addLegend(h_profile_eta[0], leg_jet_eta, "w/ HO", 1,2);
  
  leg_jet_eta->Draw();

  can_eta->SaveAs("jet_resolution_eta_dep.gif");


  /*
   * MET dist. as a function of maximum HO energy (or energy fraction)
   */


  TCanvas *can_met = (TCanvas *) MakeCanvas("met_resolution");

  TH2F* h_met_max[2];
  TH2F* h_met_frac[2];

  TH1D* h_met_profile_max[2];
  TH1D* h_met_profile_frac[2];

  for(int iho=0; iho<2; iho++){

    TString hname = (iho==0) ? "h_res_max_ho" : "h_res_max_noho";
    h_met_max[iho] = new TH2F(hname, hname, 10,0,100,100,0,1000);
      
    TString cname = (iho==0) ? "r_met:r_maxHO >> " : "r_met2:r_maxHO >> ";
    cname += hname;
    EventAnalysis->Draw(cname,"");

    h_met_profile_max[iho] = (TH1D*) h_met_max[iho]->ProfileX();
    InitHist(h_met_profile_max[iho], "Max HO energy (GeV)","Mean of the E_{T}^{miss} (GeV)",2-iho);


    hname = (iho==0) ? "h_res_frac_ho" : "h_res_frac_noho";
    h_met_frac[iho] = new TH2F(hname, hname, 10,0,0.8,100,0,1000);
      
    cname = (iho==0) ? "r_met:r_maxjfrac >> " : "r_met2:r_maxjfrac >> ";
    cname += hname;

    EventAnalysis->Draw(cname,"");

    h_met_profile_frac[iho] = (TH1D*) h_met_frac[iho]->ProfileX();
    InitHist(h_met_profile_frac[iho], "Max HO energy fraction","Mean of the E_{T}^{miss} (GeV)",2-iho);
  }
  
  TLegend *leg_met_max = new TLegend(0.23,0.20,0.79,0.43);
  TLegend *leg_met_frac = new TLegend(0.24, 0.67, 0.7, 0.9);
  LegendSettings(leg_met_max);
  LegendSettings(leg_met_frac);

  h_met_profile_max[1]->SetMinimum(0);
  h_met_profile_max[1]->Draw("");
  h_met_profile_max[0]->Draw("same");

  addLegend(h_met_profile_max[1], leg_met_max, "w/o HO", 1,2);
  addLegend(h_met_profile_max[0], leg_met_max, "w/ HO", 1,2);

  leg_met_max->Draw();
  can_met->SaveAs("Met_resolution_maxHO.gif");

  
  TCanvas *can_met_frac = (TCanvas *) MakeCanvas("met_resolution_frac");
  h_met_profile_frac[1]->SetMinimum(0);
  h_met_profile_frac[1]->Draw("");
  h_met_profile_frac[0]->Draw("same");

  addLegend(h_met_profile_frac[1], leg_met_frac, "w/o HO", 1,2);
  addLegend(h_met_profile_frac[0], leg_met_frac, "w/ HO", 1,2);

  leg_met_frac->Draw();
  can_met_frac->SaveAs("Met_resolution_frac.gif");


  /*
   * MET correlation 
   */

  /*
   * MET comparison
   */


  MakeCanvas("tmp_met_cor");
  TH2F *h_met_cor[5];

  for(int ith=0; ith<5; ith++){
      
    TString hname = "h_metcor_";
    hname += ith;

    h_met_cor[ith] = new TH2F(hname, hname, 50,0,1000,50,0,1000);
    InitHist(h_met_cor[ith], "E_{T}^{miss} (GeV) w/ HO","E_{T}^{miss} (GeV) w/o HO",1);
    
    TString dname = gname[ith];
    dname += "==1";

    TString cond = "r_met2:r_met >> ";
    cond += hname;
    EventAnalysis->Draw(cond, dname);
  }

  TCanvas *can_cor = (TCanvas*) MakeCanvas("MET_cor",950,700);
  can_cor->Divide(3,2);

  TLegend *legg[5];
  TH1D *pro_met[5];


  for(int ith=0; ith<5; ith++){


    legg[ith] = new TLegend(0.56,0.14,0.9,0.34);
    LegendSettings(legg[ith]);

    can_cor->cd(ith+1);
    //    can_cor->cd(ith+1)->SetPadLeftMargin(1.);
    h_met_cor[ith]->SetMarkerSize(0.1);
    h_met_cor[ith]->Draw("");
    pro_met[ith] = h_met_cor[ith]->ProfileX();
    pro_met[ith]->SetMarkerColor(kRed);
    pro_met[ith]->SetMarkerSize(0.1);
    pro_met[ith]->SetLineColor(kRed);
    pro_met[ith]->Draw("same");

    legg[ith]->AddEntry(pro_met[ith],tname[ith],"");
    legg[ith]->Draw();
  }

  can_cor->SaveAs("met_correlation.gif");



}
