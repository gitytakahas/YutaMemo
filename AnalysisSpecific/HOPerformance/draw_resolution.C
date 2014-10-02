void draw_resolution(){

  /*
   * Jet energy resolution
   */

  TFile *file = new TFile("Myroot.root");
  
  TH1F *h_jet_resolution[2][20];
  TGraph *gr_resolution[2];

  for(int iho=0; iho<2; iho++){

    Int_t counter = 0;
    Float_t x[20];
    Float_t y[20];

    

    for(int ijet=0; ijet<20; ijet++){
      TString hname = (iho==0) ? "h_noho_jet_" : "h_ho_jet";
      hname += ijet;

      h_jet_resolution[iho][ijet] = (TH1F*) gROOT->FindObject(hname);
      std::cout << iho << " " << ijet << " " << h_jet_resolution[iho][ijet]->GetRMS()/h_jet_resolution[iho][ijet]->GetMean() << std::endl;
      x[counter] = h_jet_resolution[iho][ijet]->GetMean();
      y[counter] = h_jet_resolution[iho][ijet]->GetRMS()/h_jet_resolution[iho][ijet]->GetMean();
      counter ++;
    }

    gr_resolution[iho] = new TGraph(counter, x, y);
    gr_resolution[iho]->SetLineColor(2-iho);
    gr_resolution[iho]->SetMarkerColor(2-iho);
    gr_resolution[iho]->SetMarkerSize(1);
    gr_resolution[iho]->SetMarkerStyle(20);
  }


  MakeCanvas("c_resolution");

  gr_resolution[0]->Draw("aep");
  gr_resolution[1]->Draw("pesame");

}
