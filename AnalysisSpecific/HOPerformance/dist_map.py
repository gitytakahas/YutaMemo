from ROOT import TFile, gDirectory, TH1F, TLegend, TCanvas, gStyle, TPad, TLine, gROOT, TTree, TH2F
import math, copy, sys
import dist_config as tool
from array import array

#gROOT.SetBatch(True)
gStyle.SetOptTitle(0)
gStyle.SetOptStat(0)

gStyle.SetPadLeftMargin(0.16);
gStyle.SetPadTopMargin(0.06);


file = TFile('Myroot.root')

#    hname = 'h_higgspt_' + label[id]
#    hnew = gDirectory.Get(hname)
#    h_higgspt[id] = copy.deepcopy(hnew)


h_ho = [[0 for ii in range(21)] for jj in range(72)]


h_map_mean = TH2F('h_map_mean','h_map_mean',21,-10,11,72,0,72)
h_map_rms = TH2F('h_map_rms','h_map_rms',21,-10,11,72,0,72)

for iphi in range(72):
    for ieta in range(21):
        hname = 'h_ho_phi' + str(iphi) + '_eta' + str(ieta)
        h_ho[iphi][ieta] = file.Get(hname)
        print iphi, ieta, '->', h_ho[iphi][ieta].GetEntries(), h_ho[iphi][ieta].GetMean(), h_ho[iphi][ieta].GetRMS()

        if h_ho[iphi][ieta].GetEntries() is not 0:
            h_map_mean.SetBinContent(ieta+1, iphi+1, h_ho[iphi][ieta].GetMean())
            h_map_rms.SetBinContent(ieta+1, iphi+1, h_ho[iphi][ieta].GetRMS())
            h_map_mean.GetYaxis().SetTitleOffset(1.4)
            h_map_rms.GetYaxis().SetTitleOffset(1.4)

            h_map_mean.GetYaxis().SetTitle('#phi')
            h_map_mean.GetXaxis().SetTitle('#eta')
            h_map_rms.GetYaxis().SetTitle('#phi')
            h_map_rms.GetXaxis().SetTitle('#eta')
#            h_map_mean.GetZaxis().SetTitle('HO energy')
#            h_map_rms.GetZaxis().SetTitle('HO energy')
            

c = TCanvas('c','',615,870)
h_map_mean.Draw('colz')

#c2 = TCanvas('c2','',615,870)
#h_map_rms.Draw('colz')

c.SaveAs('HO_energy_map.gif')
