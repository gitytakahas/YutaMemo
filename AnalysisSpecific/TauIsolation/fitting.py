from ROOT import TFile, gROOT, gStyle, TH1F, TH2F, kBlue, kRed, TCanvas, TLatex, TLegend
import os, numpy, copy
from officialStyle import officialStyle


gROOT.SetBatch(True)
officialStyle(gStyle)
gStyle.SetPadLeftMargin(0.18)
gStyle.SetPadBottomMargin(0.15)

def returnRange(hist):
    
    bin = []
    
    for ibin in range(0, hist.GetNbinsX()+1):
        proj = hist.ProjectionY("ProjY_"+str(ibin), ibin, ibin+1)
        if proj.GetEntries() > 100:
            bin.append(ibin)

    return min(bin), max(bin)



def LegendSettings(leg):
    leg.SetBorderSize(0)
    leg.SetFillColor(10)
    leg.SetLineColor(0)
    leg.SetFillStyle(0)
    leg.SetTextSize(0.035)
    leg.SetTextFont(42)

colours = [2, 3, 4, 6, 7, 8]

process = 'DY'
#process = 'VBF'

directory = 'sample_20140513'

samples = []
if process=='DY':
    samples = ['DY_Standard', 'DY_Timing', 'DY_3DandTiming']
elif process=='VBF':
    samples = ['VBF_Standard125', 'VBF_Timing125', 'VBF_3DandTiming125']


plots = ['tau_iso_neutralPt','tau_iso_neutralPtWeight1','tau_iso_neutralPtWeight2','tau_iso_neutralPtWeight1NQ','tau_iso_neutralPtWeight2NQ']

plotleg = ['#Sigma_{neutral} p_{T} [GeV]', 
           '#Sigma_{neutral, weight1} p_{T} [GeV]',
           '#Sigma_{neutral, weight1 NQ} p_{T} [GeV]',
           '#Sigma_{neutral, weight2} p_{T} [GeV]',
           '#Sigma_{neutral, weight2 NQ} p_{T} [GeV]',
           ]

barrel_endcap = ['all', 'barrel', 'endcap']


hist2d_save = [[[i for i in range(len(samples))] for j in range(len(barrel_endcap))] for k in range(len(plots))]
hist_save = [[[i for i in range(len(samples))] for j in range(len(barrel_endcap))] for k in range(len(plots))]
f1_save = [[[i for i in range(len(samples))] for j in range(len(barrel_endcap))] for k in range(len(plots))]


for iplot, plot in enumerate(plots):
    for ibe, isbarrel in enumerate(barrel_endcap):

        hist = [i for i in range(len(samples))]
        hist2d = [i for i in range(len(samples))]
        f1 = [i for i in range(len(samples))]
        
        cname = 'can_' + plot + '_' + isbarrel
        can = TCanvas(cname, cname)

        for ii, sample in enumerate(samples):

            tfile = TFile('{dir}/{sample}/TauTreeProducer/TauTreeProducer_tree.root'.format(dir=directory, sample=sample))
            tree = tfile.Get('TauTreeProducer')
        
            hname = 'h_' + sample + '_' + isbarrel + '_' + plot
            hist[ii] = TH2F(hname, hname, 80,0,80, 60,0,60)
#            hist[ii].Sumw2()
            
            if isbarrel=='all':
                tree.Draw(plot + ':tau_iso_sumPUPt >> ' + hname, 'TMath::Abs(parton_pdgId)==15 && tau_decayModeFinding==1')
            elif isbarrel=='barrel':
                tree.Draw(plot + ':tau_iso_sumPUPt >> ' + hname, 'TMath::Abs(parton_pdgId)==15 && tau_decayModeFinding==1 && TMath::Abs(tau_eta) < 1.479')
            else:
                tree.Draw(plot + ':tau_iso_sumPUPt >> ' + hname, 'TMath::Abs(parton_pdgId)==15 && tau_decayModeFinding==1 && TMath::Abs(tau_eta) > 1.479')


            fitmin, fitmax = returnRange(hist[ii])
            hist2d[ii] = hist[ii].ProfileX()
            hist2d[ii].Fit("pol1","","",fitmin, fitmax)
            f1[ii] = hist2d[ii].GetFunction("pol1");
            
            hist2d[ii].GetXaxis().SetTitle('#Sigma_{PU} p_{T} [GeV]')
            hist2d[ii].GetYaxis().SetTitle(plotleg[iplot])
            hist2d[ii].SetMaximum(20)
            hist2d[ii].SetMinimum(0)
            hist2d[ii].SetMarkerSize(0.1)
            hist2d[ii].SetMarkerColor(colours[ii])
            hist2d[ii].SetLineColor(colours[ii])
            
            tname = process + ', ' + isbarrel
            hist2d[ii].SetTitle(tname)

            hist_save[iplot][ibe][ii] = copy.deepcopy(hist[ii])
            hist2d_save[iplot][ibe][ii] = copy.deepcopy(hist2d[ii])
            f1_save[iplot][ibe][ii] = copy.deepcopy(f1[ii])


        leg = TLegend(0.2,0.75,0.7,0.9)
        LegendSettings(leg)

        for ii, sample in enumerate(samples):
            if ii==0:
                hist2d_save[iplot][ibe][ii].Draw()
            else:
                hist2d_save[iplot][ibe][ii].Draw('same')
            
            f1_save[iplot][ibe][ii].SetLineColor(colours[ii])
            f1_save[iplot][ibe][ii].SetLineStyle(2)
            f1_save[iplot][ibe][ii].SetRange(hist2d_save[iplot][ibe][ii].GetXaxis().GetXmin(), hist2d_save[iplot][ibe][ii].GetXaxis().GetXmax())
            f1_save[iplot][ibe][ii].Draw('same')

            lname = sample.replace('_', ' ').replace('3DandTiming', '3D & Timing').replace('125','') + ', (' + str("{0:.3f}".format(f1_save[iplot][ibe][ii].GetParameter(1))) + ', ' + str("{0:.1f}".format(round(f1_save[iplot][ibe][ii].GetParameter(0),1))) + ')'
            leg.AddEntry(hist2d_save[iplot][ibe][ii], lname, 'l')

        leg.Draw()

        sname = 'plot/isolation_' + plot + '_' + isbarrel + '_' + process + '_neutral_vs_puiso.gif'
        can.SaveAs(sname)


file = TFile('root/Myroot_' + process + '.root','recreate')

for iplot, plot in enumerate(plots):
    for ibe, isbarrel in enumerate(barrel_endcap):
       for ii, sample in enumerate(samples):
           hist_save[iplot][ibe][ii].Write()
           hist2d_save[iplot][ibe][ii].Write()

        
file.Write()
file.Close()
