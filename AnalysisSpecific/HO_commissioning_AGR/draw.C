void DecorateCanvas(TCanvas *c, bool log){
  c->SetBorderSize(2);
  if(log) c->SetLogy();
  c->SetLeftMargin(0.15);
  c->SetRightMargin(0.09);
  c->SetTopMargin(0.067);
  c->SetBottomMargin(0.13);
  c->SetFrameBorderMode(0);
  c->SetFrameLineWidth(2);
  c->SetFrameBorderMode(0);  
}

void DecorateHistogram(TH1F *h, TString xtitle, TString ytitle){
  h->SetLineWidth(2);
  h->SetLineColor(1);
  h->GetXaxis()->SetTitle(xtitle);
  h->GetXaxis()->SetLabelFont(42);
  h->GetXaxis()->SetTitleSize(0.05);
  h->GetYaxis()->SetTitle(ytitle);
  h->GetYaxis()->SetTitleSize(0.05);
  h->GetYaxis()->SetTitleOffset(1.2);
  h->GetZaxis()->SetLabelSize(0.035);
  h->GetZaxis()->SetTitleSize(0.035);

}

void DecorateHistogram(TH2F *h, TString xtitle, TString ytitle){
  h->GetXaxis()->SetTitle(xtitle);
  h->GetXaxis()->SetLabelFont(42);
  h->GetXaxis()->SetTitleSize(0.05);
  h->GetYaxis()->SetTitle(ytitle);
  h->GetYaxis()->SetTitleSize(0.05);
  h->GetYaxis()->SetTitleOffset(1.2);
  h->GetZaxis()->SetLabelSize(0.035);
  h->GetZaxis()->SetTitleSize(0.035);
}

void DecorateHistogram(TH2D *h, TString xtitle, TString ytitle){
  h->GetXaxis()->SetTitle(xtitle);
  h->GetXaxis()->SetLabelFont(42);
  h->GetXaxis()->SetTitleSize(0.05);
  h->GetYaxis()->SetTitle(ytitle);
  h->GetYaxis()->SetTitleSize(0.05);
  h->GetYaxis()->SetTitleOffset(1.2);
  h->GetZaxis()->SetLabelSize(0.035);
  h->GetZaxis()->SetTitleSize(0.035);
}

void draw(){


  gStyle->SetOptTitle(0);
  gStyle->SetOptStat(0);

  //  TFile *f = new TFile("Myroot_save.root");
  TFile *f = new TFile("Myroot.root");

  
  TCanvas *c1 = new TCanvas("c1", "c1",620,620);
  DecorateCanvas(c1, true);

  TH1F *HO_energy = new TH1F("HO_energy","HO_energy",200,-1,20);
  HO_tree->Draw("HO_energy >> HO_energy");
  DecorateHistogram(HO_energy, "HO energy (GeV)", "# hits");

  HO_energy->Draw("");
  c1->SaveAs("HO_energy.gif");

  ////////////////


  TCanvas *c2 = new TCanvas("c2", "c2",620,620);
  DecorateCanvas(c2, false);

  TH2F *muon_etaphi = new TH2F("muon_etaphi","muon_etaphi",200,-4,4,200,-4,4);
  muon_tree->Draw("muon_innerphi:muon_innereta >> muon_etaphi");
  DecorateHistogram(muon_etaphi, "muon inner #eta", "muon inner #phi");
  muon_etaphi->Draw("colz");

  c2->SaveAs("muon_map.gif");

  /////////////////////

  TCanvas *c3 = new TCanvas("c3", "c3",620,620);
  DecorateCanvas(c3, false);

  TH1F *nHO = new TH1F("nHO","nHO",300,0,300);
  event_tree->Draw("nHO >> nHO");
  DecorateHistogram(nHO, "Number of HO hits", "# events");

  nHO->Draw("");
  c3->SaveAs("nHO.gif");


  /////////////////////

  TCanvas *c_chi2 = new TCanvas("c_chi2", "c_chi2",620,620);
  DecorateCanvas(c_chi2, true);

  TH1F *muon_chi2 = new TH1F("muon_chi2","muon_chi2",200,0,200);
  muon_tree->Draw("muon_normalizedchi2>> muon_chi2");
  DecorateHistogram(muon_chi2, "Normalized #chi^{2}", "# events");

  muon_chi2->Draw("");
  c_chi2->SaveAs("muon_chi2.gif");




  //////////////////////
  // 2D 
  
  TCanvas *c4 = new TCanvas("c4", "c4",620,620);
  DecorateCanvas(c4, false);
  c4->SetRightMargin(0.16);
  
  TH2F *HO_etaphi = new TH2F("HO_etaphi","HO_etaphi",30,-15,15,72,1,73);
  HO_tree->Draw("HO_iphi:HO_ieta >> HO_etaphi");
  DecorateHistogram(HO_etaphi, "HO i#eta", "HO i#phi");
  HO_etaphi->Draw("colz");

  c4->SaveAs("HO_map_nocut.gif");

  ///////////////////////

  TCanvas *c5 = new TCanvas("c5", "c5",620,620);
  DecorateCanvas(c5, false);
  c5->SetRightMargin(0.16);
  
  TH2F *HO_etaphi_ecut = new TH2F("HO_etaphi_ecut","HO_etaphi_ecut",30,-15,15,72,1,73);
  HO_tree->Draw("HO_iphi:HO_ieta >> HO_etaphi_ecut","HO_energy > 0.3");
  DecorateHistogram(HO_etaphi_ecut, "HO i#eta", "HO i#phi");
  HO_etaphi_ecut->Draw("colz");

  c5->SaveAs("HO_map_ecut.gif");


  ////////////////////////

  TCanvas *c6 = new TCanvas("c6", "c6",620,620);
  DecorateCanvas(c6, false);
  c6->SetRightMargin(0.16);
  
  TH2F *HO_map = new TH2F("HO_map","HO_map",30,-800,200,30,-200,300);
  map_tree->Draw("map_muon_X:map_muon_Z >> HO_map","map_HO_ieta==-9 && map_HO_iphi==17 && map_muon_normalizedchi2 < 20","colztext");
  DecorateHistogram(HO_map, "Z (cm)", "X (cm)");
  HO_map->Draw("colztext");

  c6->SaveAs("HO_map_projection.gif");



  TCanvas *c7 = new TCanvas("c7", "c7",620,620);
  DecorateCanvas(c7, false);
  c7->SetRightMargin(0.16);
  
   //  TH2F *HO_energy_map = new TH2F("HO_energy_map","HO_energy_map",30,-800,200,30,-200,300);
  TH3F *HO_energy_map = new TH3F("HO_energy_map","HO_energy_map",30,-800,200,30,-200,300,30,0,10);
  map_tree->Draw("map_HO_energy:map_muon_X:map_muon_Z >> HO_energy_map","map_HO_ieta==-9 && map_HO_iphi==17 && map_muon_normalizedchi2 < 20");
  TH2D *projection = HO_energy_map->Project3DProfile("yx"); 
  DecorateHistogram(projection, "Z (cm)", "X (cm)");
  
  projection->Draw("colz");
  c7->SaveAs("HO_energy_map_projection.gif");



}
