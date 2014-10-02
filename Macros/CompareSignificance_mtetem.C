TString returnVal(float val){

  char _val_[10];
  sprintf(_val_, "%.3f",val);
  TString name = _val_;

  return name;
}

TString file[4] = {"~/work/H2TauTau_nobbb/CMSSW_6_1_1/src/LIMITS/hww-bg/mt/125/higgsCombineSIG-exp.ProfileLikelihood.mH125.root",
		   "~/work/H2TauTau_nobbb/CMSSW_6_1_1/src/LIMITS/hww-bg/et/125/higgsCombineSIG-exp.ProfileLikelihood.mH125.root",
		   "~/work/H2TauTau_nobbb/CMSSW_6_1_1/src/LIMITS/hww-bg/em/125/higgsCombineSIG-exp.ProfileLikelihood.mH125.root",
		   "~/work/H2TauTau_nobbb/CMSSW_6_1_1/src/LIMITS/hww-bg/cmb/125/higgsCombineSIG-exp.ProfileLikelihood.mH125.root"};


TString file_bbb[4] = {"~/work/H2TauTau_bbb/CMSSW_6_1_1/src/LIMITS/hww-bg/mt/125/higgsCombineSIG-exp.ProfileLikelihood.mH125.root",
		       "~/work/H2TauTau_bbb/CMSSW_6_1_1/src/LIMITS/hww-bg/et/125/higgsCombineSIG-exp.ProfileLikelihood.mH125.root",
		       "~/work/H2TauTau_bbb/CMSSW_6_1_1/src/LIMITS/hww-bg/em/125/higgsCombineSIG-exp.ProfileLikelihood.mH125.root",
		       //		       "~/work/H2TauTau_bbb/CMSSW_6_1_1/src/LIMITS/hww-bg/em/125/higgsCombineSIG-exp.ProfileLikelihood.mH125.root"};
		       "~/work/H2TauTau_bbb/CMSSW_6_1_1/src/LIMITS/hww-bg/cmb/125/higgsCombineSIG-exp.ProfileLikelihood.mH125.root"};

TString channelname[4] = {"mt","et","em","cmb"};

void CompareSignificance_mtetem(){

  TFile *myfile;
  TH1F *h_sig[4];

  Float_t sig_nobbb[4];
  Float_t sig_bbb[4];

  for(int ii=0; ii<4; ii++){
    sig_nobbb[ii] = 0;
    sig_bbb[ii] = 0;
  }

  for(int ichannel=0; ichannel < 4; ichannel++){
     
    TString fname = file[ichannel];
    myfile = new TFile(fname);

    TString hname = "h_sig_";
    hname += channelname[ichannel];
    h_sig[ichannel] = new TH1F(hname, hname, 100,0,5);

    TString criteria = "limit >> ";
    criteria += hname;
    limit->Draw(criteria);

    //    std::cout << "No_bbb : " << channelname[ichannel] << " " <<  h_sig[ichannel]->GetMean() << std::endl;
	
    sig_nobbb[ichannel] = h_sig[ichannel]->GetMean();
  }

  //////////////////////////////////

  TFile *myfile_bbb;
  TH1F *h_sig_bbb[4];

  for(int ichannel=0; ichannel < 4; ichannel++){
     
    TString fname = file_bbb[ichannel];
    myfile_bbb = new TFile(fname);

    TString hname = "h_sig_bbb_";
    hname += channelname[ichannel];
    h_sig_bbb[ichannel] = new TH1F(hname, hname, 100,0,5);

    TString criteria = "limit >> ";
    criteria += hname;
    limit->Draw(criteria);

    //    std::cout << "bbb : " << channelname[ichannel] << " " <<  h_sig_bbb[ichannel]->GetMean() << std::endl;
    sig_bbb[ichannel] = h_sig_bbb[ichannel]->GetMean();
  }

  for(int ichannel=0; ichannel < 4; ichannel++){
    Float_t diff = (float)((sig_nobbb[ichannel] - sig_bbb[ichannel])/sig_nobbb[ichannel]);
    std::cout << channelname[ichannel] << " (no_bbb, bbb, diff) = " 
	      << returnVal(sig_nobbb[ichannel]) << " " 
	      << returnVal(sig_bbb[ichannel]) << " " << returnVal(100*diff) << "%" << std::endl;
  }
  

}
