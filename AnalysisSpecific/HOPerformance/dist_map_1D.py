from ROOT import TFile, gDirectory, TH1F, TLegend, TCanvas, gStyle, TPad, TLine, gROOT, TTree, TH2F, kRed, kBlue
import math, copy, sys
import dist_config as tool
from array import array

file = TFile('Myroot.root')

gStyle.SetOptTitle(0)
gStyle.SetOptStat(0)

gStyle.SetPadLeftMargin(0.142132);
gStyle.SetPadRightMargin(0.06598984);
gStyle.SetPadTopMargin(0.04761905);
gStyle.SetPadBottomMargin(0.1798942);


h_ho_noise = [0 for ii in range(10)]
h_ho_signal = [0 for ii in range(10)]
#c_ho = [0 for ii in range(20)]

c_ho = TCanvas('c_map','',1080,660)
c_ho.Divide(5,2)
counter = 0

gStyle.SetOptStat(0)

leg = [0 for ii in range(10)]

for ieta in range(10):
    hname = 'h_ho_signal_eta' + str(ieta)
    h_ho_signal[ieta] = file.Get(hname)
            
    hname = 'h_ho_noise_eta' + str(ieta)
    h_ho_noise[ieta] = file.Get(hname)

    
    if h_ho_signal[ieta].GetEntries()==0 or h_ho_noise[ieta].GetEntries()==0:
        print 'No entry !'
        pass
    else:

        c_ho.cd(counter+1)
        c_ho.cd(counter+1).SetLogy()

        print h_ho_signal[ieta].GetEntries(), h_ho_noise[ieta].GetEntries()

        h_ho_signal[ieta].SetLineColor(kRed)
        h_ho_noise[ieta].SetFillStyle(3004)
        h_ho_noise[ieta].SetFillColor(1)
        h_ho_noise[ieta].SetLineColor(1)
        h_ho_signal[ieta].SetLineWidth(2)
        h_ho_noise[ieta].SetLineWidth(2)
        h_ho_noise[ieta].GetXaxis().SetTitle('HO cluster energy (GeV)')
        h_ho_noise[ieta].GetXaxis().SetNdivisions(509);
        h_ho_noise[ieta].GetXaxis().SetLabelSize(0.07);
        h_ho_noise[ieta].GetYaxis().SetLabelSize(0.07);
        h_ho_noise[ieta].GetXaxis().SetTitleSize(0.06);

#        h_ho_noise[ieta].SetMinimum(0.1)
        h_ho_noise[ieta].DrawNormalized()
        h_ho_signal[ieta].DrawNormalized('same')
        counter += 1

        leg[ieta] = TLegend(0.51,0.6,0.99,0.93);
        tool.LegendSettings(leg[ieta])
        leg[ieta].SetTextSize(0.08)

        legtitle = '|#eta| = ' + str(ieta+1)
        leg[ieta].AddEntry(h_ho_signal[ieta],legtitle,'')

        if ieta==0:
            leg[ieta].AddEntry(h_ho_signal[ieta]," Signal","l")
            leg[ieta].AddEntry(h_ho_noise[ieta]," Noise","f")

        leg[ieta].Draw()


c_ho.SaveAs('HO_energy.gif')
