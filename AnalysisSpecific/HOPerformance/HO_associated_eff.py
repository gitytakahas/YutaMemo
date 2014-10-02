from ROOT import TFile, gDirectory, TH1F, TLegend, TCanvas, gStyle, TPad, TLine, gROOT, TTree, TH2F, TGraphAsymmErrors, kRed
import math, copy, sys
import dist_config as tool
from array import array

#gROOT.SetBatch(True)
gStyle.SetOptTitle(0)
gStyle.SetOptStat(0)

#gStyle.SetPadLeftMargin(0.16);
#gStyle.SetPadTopMargin(0.06);

tool.setenv()
file = TFile('Myroot.root')
hist = [0 for ii in range(2)]

leg = TLegend(0.57,0.64,0.85,0.87)
legname = ['All','Associated HO hit']
tool.LegendSettings(leg)
leg.SetTextSize(0.04)
        
for ii in range(2):
    hname = 'h_jet_pt_' + str(ii)
    hnew = TH1F(hname, hname, 50,0,5000)
#    hnew.Sumw2()


    criteria = 'r_jet_pt >> ' + hname

    condition = ''
    if ii==1:
        condition = 'r_jet_HO_match == 1'

    file.JetAnalysis.Draw(criteria, condition);
    hist[ii] = copy.deepcopy(hnew)

    leg.AddEntry(hist[ii],legname[ii],'le')



c = TCanvas('c')
hist[0].GetXaxis().SetTitle('Jet energy (GeV)')
hist[0].GetYaxis().SetTitle('# events')
hist[0].SetLineWidth(2)
hist[1].SetLineWidth(2)
hist[0].SetLineColor(kRed)
hist[1].SetLineColor(1)
hist[1].SetFillStyle(3004)
hist[1].SetFillColor(1)

hist[0].GetXaxis().SetNdivisions(508)
hist[0].GetYaxis().SetNdivisions(509)
hist[0].Draw()
hist[1].Draw('same')

leg.Draw()

c.SaveAs('JetEnergy.gif')
c.SetLogy()
c.SaveAs('JetEnergy_log.gif')

c2 = TCanvas('c2')
gr = TGraphAsymmErrors()
gr.BayesDivide(hist[1],hist[0],'b')

gr.SetMarkerStyle(20)
gr.GetXaxis().SetTitle('Jet energy (GeV)')
gr.GetYaxis().SetTitle('HO associated efficiency')
gStyle.SetEndErrorSize(0)
gr.Draw("AP")


c2.SaveAs('Jet_HOassociated_eff.gif')
