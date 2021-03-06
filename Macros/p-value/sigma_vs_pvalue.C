void sigma_vs_pvalue(){
  
  TH1F *h = new TH1F("h","h",51,0,5);

  for(int ii=0; ii<=50; ii++){
    float i = ii/10.0;
    float pval = TMath::Erfc(i/TMath::Sqrt(2))/2;
    //float pval = TMath::Erfc(i)/2;
    std::cout << i << " " << pval << std::endl;
    h->SetBinContent(ii+1, pval);
  }

  TCanvas *c = new TCanvas("c");
  c->SetGridx();
  c->SetGridy();

  h->SetLineWidth(2);
  h->GetXaxis()->SetTitle("Sigma");
  h->GetYaxis()->SetTitle("P-value");

  h->Draw("lp");


  TCanvas *c2 = new TCanvas("c2");
  c2->SetGridx();
  c2->SetGridy();
  c2->SetLogy();

  h->Draw("lp");
}
