// $Id: rootlogon.C,v 1.1 2013/06/09 13:30:16 sixie Exp $
{

  std::cout << "Load rootlogon ..." << std::endl;

  gStyle->SetPalette(1);
  gROOT->SetStyle("Plain");
  gStyle->SetOptStat(111);
  gStyle->SetOptTitle(1);
  gStyle->SetPadBottomMargin(0.1);
  gStyle->SetPadTopMargin(0.1);
  gStyle->SetPadRightMargin(0.10);
  gStyle->SetPadLeftMargin(0.15); //0.15 was default
  gStyle->SetPadTickX(1);
  gStyle->SetPadTickY(1);
  gStyle->SetPadColor(0);
  gStyle->SetFrameBorderMode(0);
  gStyle->SetFrameFillColor(0);
  gStyle->SetPadColor(0);
  gStyle->SetCanvasColor(0);
  gStyle->SetCanvasBorderMode(0);
  gStyle->SetPadBorderMode(1);
  gStyle->SetTitleBorderSize(1);
  gStyle->SetTitleFillColor(0);
  gStyle->SetTitleY(0.99);
  gStyle->SetTitleH(0.08);
  gStyle->SetTitleW(0.75);
  gStyle->SetTitleX(0.15);
  Int_t font=42; // Helvetica
  Double_t tsize=0.05;
  gStyle->SetTextFont(font);
  gStyle->SetTextSize(tsize);
  gStyle->SetLabelFont(font,"x");
  gStyle->SetTitleFont(font,"x");
  gStyle->SetLabelFont(font,"y");
  gStyle->SetTitleFont(font,"y");
  gStyle->SetLabelFont(font,"z");
  gStyle->SetTitleFont(font,"z");
  gStyle->SetLabelSize(tsize,"x");
  gStyle->SetTitleSize(tsize,"x");
  gStyle->SetLabelSize(tsize,"y");
  gStyle->SetTitleSize(tsize,"y");
  gStyle->SetLabelSize(tsize,"z");
  gStyle->SetTitleSize(tsize,"z");

  //gROOT->Macro("Macro.C+");
  gROOT->Macro("MyStyle.C+");
  //  gROOT->Macro("/Users/TakahashiYuta/analysis/YutaMacro/MyStyle+"

}

