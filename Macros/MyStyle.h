#include <TCanvas.h>
#include <TH1.h>
#include <TH2.h>
#include <TLegend.h>
#include <TPad.h>

void MyStyle();

void SetStyle();

void LegendSettings(TLegend *leg);

TCanvas* MakeCanvas(const char* name, int dX = 500, int dY = 500);

void InitHist(TH1 *hist, const char *xtit, const char *ytit  = "Number of Entries",
	      EColor color = kBlack);

void InitHist(TH2 *hist, const char *xtit, const char *ytit  = "Number of Entries",
	      EColor color = kBlack);

TString returnVal(Float_t val, Int_t fig);

void addLegend(TH1F *h, TLegend *leg, TString base, Int_t merit, Int_t isflag=0);
void addLegend(TH1D *h, TLegend *leg, TString base, Int_t merit, Int_t isflag=0);
