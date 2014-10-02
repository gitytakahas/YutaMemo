TString file_7TeV[3] = {"LIMITS/hww-bg/mt/common/htt_mt.input_7TeV.root",
			"LIMITS/hww-bg/et/common/htt_et.input_7TeV.root",
			"LIMITS/hww-bg/em/common/htt_em.input_7TeV.root"};

TString file_8TeV[3] = {"LIMITS/hww-bg/mt/common/htt_mt.input_8TeV.root",
			"LIMITS/hww-bg/et/common/htt_et.input_8TeV.root",
			"LIMITS/hww-bg/em/common/htt_em.input_8TeV.root"};


TString ch_name[3] = {"muTau","eleTau","emu"};
TString tex_name[3] = {"#mu#tau","e#tau","e#mu"};
TString process_name[3] = {"ZTT","ZTT","Ztt"};


void LegendSettings(TLegend *leg){
  leg->SetBorderSize(0);
  leg->SetFillColor(0);
  leg->SetLineColor(0);
  leg->SetFillStyle(0);
  leg->SetTextSize(0.05);
  leg->SetTextFont(42);
}


void plot(TH1F *hist_signal[3], TH1F *hist[3], TString title, TString period){

  TString cname = "can_";
  cname += title;
  //  TCanvas * can = new TCanvas("c_vbf_tight","c_vbf_tight",1000,740);
  TCanvas * can = new TCanvas(cname, cname, 1000,740);
  can->Divide(3,2);

  TGraph *gr[3];
  TGraph *gr_bbb[3];
  TH1F *frame[3];
  TLegend *leg[3];
  TLegend *leg_err[3];

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
    hist[ican]->Draw("hep");

    hist_signal[ican]->SetLineWidth(2);
    hist_signal[ican]->SetLineColor(kBlue);
    for(int ibin=1; ibin <= hist_signal[ican]->GetXaxis()->GetNbins(); ibin++){
      hist_signal[ican]->SetBinError(ibin,0);
    }

    hist_signal[ican]->SetFillStyle(3004);
    hist_signal[ican]->SetFillColor(kBlue);
    hist_signal[ican]->Draw("hsame");

    leg[ican] = new TLegend(0.61,0.55,0.97,0.86);
    LegendSettings(leg[ican]);
    TString catname = title;

    TString legname = tex_name[ican];
    legname += ", ";
    legname += period;

    leg[ican]->AddEntry(hist[ican], catname, "");
    leg[ican]->AddEntry(hist[ican], "Z #rightarrow #tau#tau", "lp");
    leg[ican]->AddEntry(hist_signal[ican], "Signal", "lp");
    leg[ican]->AddEntry(hist_signal[ican], legname, "");
    leg[ican]->Draw();
  }


  ///////////////
  
  for(int ican=0; ican < 3; ican++){
    can->cd(ican+4);
    hist[ican]->SetLineWidth(2);
    hist[ican]->SetLineColor(1);
    
    int counter = 0;
    int counter_sig = 0;

    Float_t x[100];
    Float_t y[100];
    Float_t x_bbb[100];
    Float_t y_bbb[100];

    for(int ii=0; ii<100; ii++){
      x[ii] = 0; y[ii] = 0;
      x_bbb[ii] = 0; y_bbb[ii] = 0;
    }

    for(int ibin=1; ibin <= hist[ican]->GetXaxis()->GetNbins(); ibin++){
      Float_t val = hist[ican]->GetBinContent(ibin);
      Float_t err = hist[ican]->GetBinError(ibin);
      Float_t val_signal = hist_signal[ican]->GetBinContent(ibin);
      
      if(val!=0){
	x[counter] = hist[ican]->GetBinCenter(ibin);	
	y[counter] = val_signal/TMath::Sqrt(val);

	x_bbb[counter] =  hist[ican]->GetBinCenter(ibin);
	y_bbb[counter] = val_signal/TMath::Sqrt(val+err*err);

	//	std::cout << "(bin, x, y, y_bbb) = " << ibin << " " << x[counter] << " " << y[counter] << " " << y_bbb[counter] << " " << val_signal << " " << val << " " << err << std::endl;

	Float_t sig_nobbb = val_signal/TMath::Sqrt(val);
	Float_t sig_bbb = val_signal/TMath::Sqrt(val+err*err);
	
	counter++;
      }
     }

    std::cout << counter << std::endl;
    
    gr[ican] = new TGraph(counter, x, y);
    gr[ican]->SetMarkerStyle(20);

    gr_bbb[ican] = new TGraph(counter, x_bbb, y_bbb);
    gr_bbb[ican]->SetMarkerColor(kBlue);
    gr_bbb[ican]->SetLineColor(kBlue);
    gr_bbb[ican]->SetMarkerStyle(20);

    TString fname = "frame_";
    fname += title;
    fname += "_";
    fname += ican;

    frame[ican] = new TH1F(fname, fname, 1, hist[ican]->GetXaxis()->GetXmin(), hist[ican]->GetXaxis()->GetXmax());
    frame[ican]->Draw();
    frame[ican]->GetXaxis()->SetTitle("m_{#tau#tau} mass (GeV)");

    frame[ican]->GetYaxis()->SetTitle("Significance");

    frame[ican]->GetXaxis()->SetLabelSize(0.05);
    frame[ican]->GetYaxis()->SetLabelSize(0.05);
    frame[ican]->GetXaxis()->SetTitleSize(0.05);
    frame[ican]->GetYaxis()->SetTitleSize(0.05);
    frame[ican]->GetYaxis()->SetTitleOffset(1.4);
    if(title=="VBF" || title=="VBF_loose" || title=="VBF_tight"){
      frame[ican]->SetMaximum(2.5);
    }else{
      frame[ican]->SetMaximum(1.5);
    }
    frame[ican]->Draw();

    TLine * line = new TLine(hist[ican]->GetXaxis()->GetXmin(), 0.1, hist[ican]->GetXaxis()->GetXmax(),0.1);
    line->SetLineStyle(2);
    line->SetLineWidth(2);
    line->SetLineColor(kRed);
    //    line->Draw();
    
    gr[ican]->Draw("lpsame");
    gr_bbb[ican]->Draw("lpsame");


    leg_err[ican] = new TLegend(0.61,0.55,0.97,0.86);
    LegendSettings(leg_err[ican]);
    TString catname = title;

    leg_err[ican]->AddEntry(hist[ican], catname, "");
    leg_err[ican]->AddEntry(gr[ican], "No bbb", "lp");
    leg_err[ican]->AddEntry(gr_bbb[ican], "bbb", "lp");
    leg_err[ican]->Draw();

  }

  TString savename = "Fig_significance_diff_";
  savename += period;
  savename += "_";
  savename += title;
  savename += ".gif";
  can->SaveAs(savename);
}




void compare_Mtt_distribution_fitting(){

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
     
    TString fname = file_8TeV[ichannel];
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



  plot(h_vbf_tight_signal, h_vbf_tight, "VBF_tight","8TeV");
  plot(h_vbf_loose_signal, h_vbf_loose, "VBF_loose","8TeV");
  plot(h_1jet_signal, h_1jet, "1jet_high","8TeV");


  /////////////////// 7 TeV ////////////////////////////

  TH1F* hh_vbf[3];
  TH1F* hh_1jet[3];
  TH1F* hh_vbf_signal[3];
  TH1F* hh_1jet_signal[3];


  /*
   * VBF tight category for 8TeV
   */

  for(int ichannel=0; ichannel < 3; ichannel++){
     
    TString fname = file_7TeV[ichannel];
    file = new TFile(fname);
    
    TString getname = ch_name[ichannel];
    if(ichannel==2) getname += "_vbf_loose/";
    else getname += "_vbf/";

    TString name = getname + process_name[ichannel];
    hh_vbf[ichannel] = (TH1F*) file->Get(name);

    // signal 

    TString sname = getname;
    sname += "ggH125";
    hh_vbf_signal[ichannel] = (TH1F*) file->Get(sname);

    sname = getname;
    sname += "qqH125";
    hh_vbf_signal[ichannel]->Add((TH1F*) file->Get(sname));
    
    sname = getname;
    sname += "VH125";
    hh_vbf_signal[ichannel]->Add((TH1F*) file->Get(sname));


    //////////////////////////


    getname = ch_name[ichannel];
    if(ichannel==2) getname += "_1jet_high/";
    else getname += "_1jet_high_mediumhiggs/";

    TString name = getname + process_name[ichannel];
    hh_1jet[ichannel] = (TH1F*) file->Get(name);

    
    // signal

    sname = getname;
    sname += "ggH125";
    hh_1jet_signal[ichannel] = (TH1F*) file->Get(sname);

    sname = getname;
    sname += "qqH125";
    hh_1jet_signal[ichannel]->Add((TH1F*) file->Get(sname));
    
    sname = getname;
    sname += "VH125";
    hh_1jet_signal[ichannel]->Add((TH1F*) file->Get(sname));
				
  }



  plot(hh_vbf_signal, hh_vbf, "VBF","7TeV");
  plot(hh_1jet_signal, hh_1jet, "1jet","7TeV");


}
