from ROOT import TFile, gROOT, gStyle, TH1F, TH2F, kBlue, kRed, TCanvas, TLatex, TLegend, TVirtualFitter, TMatrixD
import os, numpy, copy, math
from officialStyle import officialStyle

gROOT.SetBatch(True)
officialStyle(gStyle)
#gStyle.SetOptTitle(0)
gStyle.SetPadLeftMargin(0.18)
gStyle.SetPadBottomMargin(0.15)

def returnRange(hist):
    
    bin = []
    
    for ibin in range(0, hist.GetNbinsX()+1):
        proj = hist.ProjectionY("ProjY_"+str(ibin), ibin, ibin+1)
#        print hist.GetName(), ibin, proj.GetEntries()
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

colours = [2, 4, 6, 7, 8]

directory = 'sample_20140513'
directory2 = 'sample_20140514_PU20x25ns'

samples = ['VBF_Timing125', 'VBF_Timing125']

plots = ['tau_iso_neutralPt']
plotleg = ['#Sigma_{neutral} p_{T} [GeV]']

barrel_endcap = ['barrel', 'endcap']

hist2d_save = [[[i for i in range(len(samples))] for j in range(len(barrel_endcap))] for k in range(len(plots))]
hist_save = [[[i for i in range(len(samples))] for j in range(len(barrel_endcap))] for k in range(len(plots))]
f1_save = [[[i for i in range(len(samples))] for j in range(len(barrel_endcap))] for k in range(len(plots))]


for iplot, plot in enumerate(plots):
    for ibe, isbarrel in enumerate(barrel_endcap):

        hist = [i for i in range(len(samples))]
        hist2d = [i for i in range(len(samples))]
        f1 = [i for i in range(len(samples))]
        
        cname = 'can_' + plot
        can = TCanvas(cname, cname)

        for ii, sample in enumerate(samples):
            
            if ii==0:
                tfile = TFile('{dir}/{sample}/TauTreeProducer/TauTreeProducer_tree.root'.format(dir=directory, sample=sample))
            elif ii==1:
                tfile = TFile('{dir}/{sample}/TauTreeProducer/TauTreeProducer_tree.root'.format(dir=directory2, sample=sample))
            tree = tfile.Get('TauTreeProducer')
        
            hname = 'h_' + sample + '_' + isbarrel + '_' + plot
            hist[ii] = TH2F(hname, hname, 80,0,80, 100,0,100)
            
            if isbarrel=='barrel':
                tree.Draw(plot + ':nVert_cur >> ' + hname, 'TMath::Abs(parton_pdgId)==15 && tau_decayModeFinding==1 && TMath::Abs(tau_eta) < 1.479')
            else:
                tree.Draw(plot + ':nVert_cur >> ' + hname, 'TMath::Abs(parton_pdgId)==15 && tau_decayModeFinding==1 && TMath::Abs(tau_eta) > 1.479')

            hist2d[ii] = hist[ii].ProfileX()

            fitmin, fitmax = returnRange(hist[ii])

            hist2d[ii].Fit("pol1", "", "", fitmin, fitmax)
            f1[ii] = hist2d[ii].GetFunction("pol1");

            fitter = TVirtualFitter.GetFitter()
            matrix = TMatrixD(2,2,fitter.GetCovarianceMatrix())
            matrix.Print()
            errorFirstPar = math.sqrt(fitter.GetCovarianceMatrixElement(0,0));
            errorSecondPar = math.sqrt(fitter.GetCovarianceMatrixElement(1,1));
            
            print 'error (first, second) = ', errorFirstPar, errorSecondPar

            
            hist2d[ii].GetXaxis().SetTitle('Number of vertex')
            hist2d[ii].GetYaxis().SetTitle(plotleg[iplot])
            
#            if plot.find('tau_iso_neutralPt')!=-1:
#                hist2d[ii].SetMaximum(20)
#            elif plot.find('tau_iso_chargedPt')!=-1:
#                hist2d[ii].SetMaximum(5)
#            elif plot.find('tau_iso_sumPUPt')!=-1:
#                hist2d[ii].SetMaximum(60)

            hist2d[ii].SetMaximum(15)
            hist2d[ii].SetMinimum(0)
            hist2d[ii].GetXaxis().SetRangeUser(0,60)
            hist2d[ii].SetMarkerSize(0.1)
            hist2d[ii].SetMarkerColor(colours[ii])
            hist2d[ii].SetLineColor(colours[ii])
            
            tname = 'VBF, ' + isbarrel
            hist2d[ii].SetTitle(tname)

            hist_save[iplot][ibe][ii] = copy.deepcopy(hist[ii])
            hist2d_save[iplot][ibe][ii] = copy.deepcopy(hist2d[ii])
            f1_save[iplot][ibe][ii] = copy.deepcopy(f1[ii])


        leg = TLegend(0.2,0.75,0.6,0.9)
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

            lname = sample.replace('_', ' ').replace('3DandTiming', '3D & Timing').replace('125','')
            if ii==0:
                lname += ' (PU40x25ns)'
            elif ii==1:
                lname += ' (PU20x25ns)'

            lname += ', (' + str("{0:.3f}".format(f1_save[iplot][ibe][ii].GetParameter(1))) + ', ' + str("{0:.1f}".format(round(f1_save[iplot][ibe][ii].GetParameter(0),1))) + ')'
            leg.AddEntry(hist2d_save[iplot][ibe][ii], lname, 'l')

        leg.Draw()

        sname = 'offset_isolation_' + plot + '_' + isbarrel + '_nvert_cur.gif'
        can.SaveAs(sname)




