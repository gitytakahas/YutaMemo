TString file_tau[3] = {"~/work/H2TauTau_nobbb_pT30/CMSSW_6_1_1/src/LIMITS/hww-bg/mt/common/htt_mt.input_8TeV.root",
		       "~/work/H2TauTau_nobbb_pT30/CMSSW_6_1_1/src/LIMITS/hww-bg/et/common/htt_et.input_8TeV.root",
		       "~/work/H2TauTau_nobbb_pT30/CMSSW_6_1_1/src/LIMITS/hww-bg/em/common/htt_em.input_8TeV.root"};

TString file_notau[3] = {"~/work/H2TauTau_nobbb/CMSSW_6_1_1/src/LIMITS/hww-bg/mt/common/htt_mt.input_8TeV.root",
		       "~/work/H2TauTau_nobbb/CMSSW_6_1_1/src/LIMITS/hww-bg/et/common/htt_et.input_8TeV.root",
		       "~/work/H2TauTau_nobbb/CMSSW_6_1_1/src/LIMITS/hww-bg/em/common/htt_em.input_8TeV.root"};


TString ch_name[3] = {"muTau","eleTau","emu"};
TString tex_name[3] = {"#mu#tau","e#tau","e#mu"};
TString process_name[3] = {"ZTT","ZTT","Ztt"};


void LegendSettings(TLegend *leg){
  leg->SetBorderSize(0);
  leg->SetFillColor(0);
  leg->SetLineColor(0);
  leg->SetFillStyle(0);
  leg->SetTextSize(0.04);
  leg->SetTextFont(42);
}


void plot(TH1F *hist_signal[3], TH1F *hist[3], TH1F* hist_tau_signal[3], TH1F *hist_tau[3], TString title, TString period){

  TString cname = "can_";
  cname += title;
  TCanvas * can = new TCanvas(cname, cname, 1500,600);
  can->Divide(3,1);

  TLegend *leg[3];

  for(int ican=0; ican < 3; ican++){
    can->cd(ican+1);
    
    hist[ican]->SetLineWidth(2);
    hist[ican]->GetXaxis()->SetTitle("m_{#tau#tau} mass (GeV)");
    hist[ican]->GetYaxis()->SetTitleOffset(1.4);
    hist[ican]->GetYaxis()->SetTitle("Events");
    hist[ican]->GetXaxis()->SetLabelSize(0.05);
    hist[ican]->GetYaxis()->SetLabelSize(0.05);
    hist[ican]->GetXaxis()->SetTitleSize(0.05);
    hist[ican]->GetYaxis()->SetTitleSize(0.05);
    hist[ican]->SetMinimum(0);
    hist[ican]->SetLineColor(kBlack);
    hist[ican]->SetLineStyle(2);
    hist[ican]->Draw("h");

    hist_signal[ican]->SetLineWidth(2);
    hist_signal[ican]->SetLineColor(kBlue);
    for(int ibin=1; ibin <= hist_signal[ican]->GetXaxis()->GetNbins(); ibin++){
      hist[ican]->SetBinError(ibin,0);
      hist_signal[ican]->SetBinError(ibin,0);
    }

    hist_signal[ican]->SetFillStyle(3004);
    hist_signal[ican]->SetFillColor(kBlue);
    hist_signal[ican]->SetLineStyle(2);
    hist_signal[ican]->Draw("hsame");


    /////////////////////////////

    hist_tau[ican]->SetLineWidth(2);
    hist_tau[ican]->GetXaxis()->SetTitle("m_{#tau#tau} mass (GeV)");
    hist_tau[ican]->GetYaxis()->SetTitleOffset(1.4);
    hist_tau[ican]->GetYaxis()->SetTitle("Events");
    hist_tau[ican]->GetXaxis()->SetLabelSize(0.05);
    hist_tau[ican]->GetYaxis()->SetLabelSize(0.05);
    hist_tau[ican]->GetXaxis()->SetTitleSize(0.05);
    hist_tau[ican]->GetYaxis()->SetTitleSize(0.05);
    hist_tau[ican]->SetLineColor(kBlack);
    hist_tau[ican]->SetMinimum(0);
    hist_tau[ican]->Draw("hsame");

    hist_tau_signal[ican]->SetLineWidth(2);
    hist_tau_signal[ican]->SetLineColor(kBlue);
    for(int ibin=1; ibin <= hist_tau_signal[ican]->GetXaxis()->GetNbins(); ibin++){
      hist_tau[ican]->SetBinError(ibin,0);
      hist_tau_signal[ican]->SetBinError(ibin,0);
    }

    hist_tau_signal[ican]->SetFillStyle(3004);
    hist_tau_signal[ican]->SetFillColor(kBlue);
    hist_tau_signal[ican]->Draw("hsame");

    leg[ican] = new TLegend(0.45,0.55,0.97,0.86);
    LegendSettings(leg[ican]);
    TString catname = title;

    TString legname = tex_name[ican];
    legname += ", ";
    legname += period;

    leg[ican]->AddEntry(hist[ican], catname, "");
    leg[ican]->AddEntry(hist[ican], "Z #rightarrow #tau#tau", "lp");
    leg[ican]->AddEntry(hist_signal[ican], "Signal", "lp");
    leg[ican]->AddEntry(hist_tau[ican], "Z #rightarrow #tau#tau (p_{T}^{#tau} > 30 GeV)", "lp");
    leg[ican]->AddEntry(hist_tau_signal[ican], "Signal (p_{T}^{#tau} > 30 GeV)", "lp");
    leg[ican]->AddEntry(hist_signal[ican], legname, "");
    leg[ican]->Draw();

  }


  TString savename = "Fig_compare_diff_";
  savename += period;
  savename += "_";
  savename += title;
  savename += ".gif";
  can->SaveAs(savename);
}




void compare_taupTcut(){

  gStyle->SetOptStat(0);
  gStyle->SetOptTitle(0);
  gStyle->SetPadRightMargin(0.03);
  gStyle->SetPadLeftMargin(0.16);


  TFile *file;
  TH1F* h_vbf_tight[3];
  TH1F* h_vbf_loose[3];
  TH1F* h_1jet[3];
  TH1F* h_vbf_tight_signal[3];
  TH1F* h_vbf_loose_signal[3];
  TH1F* h_1jet_signal[3];


  /*
   * VBF tight category for 8TeV
   */

  for(int ichannel=0; ichannel < 3; ichannel++){
     
    TString fname = file_notau[ichannel];
    file = new TFile(fname);
    
    TString getname = ch_name[ichannel];
    getname += "_vbf_tight/";
    TString name = getname + process_name[ichannel];
    h_vbf_tight[ichannel] = (TH1F*) file->Get(name);

    // signal 

    TString sname = getname;
    sname += "ggH125";
    h_vbf_tight_signal[ichannel] = (TH1F*) file->Get(sname);

    sname = getname;
    sname += "qqH125";
    h_vbf_tight_signal[ichannel]->Add((TH1F*) file->Get(sname));
    
    sname = getname;
    sname += "VH125";
    h_vbf_tight_signal[ichannel]->Add((TH1F*) file->Get(sname));


    //////////////////////////

    getname = ch_name[ichannel];
    getname += "_vbf_loose/";
    TString name = getname + process_name[ichannel];
    h_vbf_loose[ichannel] = (TH1F*) file->Get(name);

    // signal

    sname = getname;
    sname += "ggH125";
    h_vbf_loose_signal[ichannel] = (TH1F*) file->Get(sname);

    sname = getname;
    sname += "qqH125";
    h_vbf_loose_signal[ichannel]->Add((TH1F*) file->Get(sname));
    
    sname = getname;
    sname += "VH125";
    h_vbf_loose_signal[ichannel]->Add((TH1F*) file->Get(sname));
				

    /////////////////////////


    getname = ch_name[ichannel];
    if(ichannel==2) getname += "_1jet_high/";
    else getname += "_1jet_high_mediumhiggs/";

    TString name = getname + process_name[ichannel];
    h_1jet[ichannel] = (TH1F*) file->Get(name);

    
    // signal

    sname = getname;
    sname += "ggH125";
    h_1jet_signal[ichannel] = (TH1F*) file->Get(sname);

    sname = getname;
    sname += "qqH125";
    h_1jet_signal[ichannel]->Add((TH1F*) file->Get(sname));
    
    sname = getname;
    sname += "VH125";
    h_1jet_signal[ichannel]->Add((TH1F*) file->Get(sname));
				
  }


  ////////////////////////////////

  TH1F* h_vbf_tight_tau[3];
  TH1F* h_vbf_loose_tau[3];
  TH1F* h_1jet_tau[3];
  TH1F* h_vbf_tight_tau_signal[3];
  TH1F* h_vbf_loose_tau_signal[3];
  TH1F* h_1jet_tau_signal[3];


  /*
   * VBF tight category for 8TeV
   */

  for(int ichannel=0; ichannel < 3; ichannel++){
     
    TString fname = file_tau[ichannel];
    file = new TFile(fname);
    
    TString getname = ch_name[ichannel];
    getname += "_vbf_tight/";
    TString name = getname + process_name[ichannel];
    h_vbf_tight_tau[ichannel] = (TH1F*) file->Get(name);

    // signal 

    TString sname = getname;
    sname += "ggH125";
    h_vbf_tight_tau_signal[ichannel] = (TH1F*) file->Get(sname);

    sname = getname;
    sname += "qqH125";
    h_vbf_tight_tau_signal[ichannel]->Add((TH1F*) file->Get(sname));
    
    sname = getname;
    sname += "VH125";
    h_vbf_tight_tau_signal[ichannel]->Add((TH1F*) file->Get(sname));


    //////////////////////////

    getname = ch_name[ichannel];
    getname += "_vbf_loose/";
    TString name = getname + process_name[ichannel];
    h_vbf_loose_tau[ichannel] = (TH1F*) file->Get(name);

    // signal

    sname = getname;
    sname += "ggH125";
    h_vbf_loose_tau_signal[ichannel] = (TH1F*) file->Get(sname);

    sname = getname;
    sname += "qqH125";
    h_vbf_loose_tau_signal[ichannel]->Add((TH1F*) file->Get(sname));
    
    sname = getname;
    sname += "VH125";
    h_vbf_loose_tau_signal[ichannel]->Add((TH1F*) file->Get(sname));
				

    /////////////////////////


    getname = ch_name[ichannel];
    if(ichannel==2) getname += "_1jet_high/";
    else getname += "_1jet_high_mediumhiggs/";

    TString name = getname + process_name[ichannel];
    h_1jet_tau[ichannel] = (TH1F*) file->Get(name);

    
    // signal

    sname = getname;
    sname += "ggH125";
    h_1jet_tau_signal[ichannel] = (TH1F*) file->Get(sname);

    sname = getname;
    sname += "qqH125";
    h_1jet_tau_signal[ichannel]->Add((TH1F*) file->Get(sname));
    
    sname = getname;
    sname += "VH125";
    h_1jet_tau_signal[ichannel]->Add((TH1F*) file->Get(sname));
				
  }


  plot(h_vbf_tight_signal, h_vbf_tight, h_vbf_tight_tau_signal, h_vbf_tight_tau, "VBF_tight", "8TeV");
  plot(h_vbf_loose_signal, h_vbf_loose, h_vbf_loose_tau_signal, h_vbf_loose_tau, "VBF_loose", "8TeV");
  plot(h_1jet_signal, h_1jet, h_1jet_tau_signal, h_1jet_tau, "1jet", "8TeV");



}
