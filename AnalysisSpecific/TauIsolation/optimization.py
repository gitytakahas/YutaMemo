from ROOT import TFile, gROOT, gStyle, TH1F, TH2F, kBlue, kRed, TCanvas, TLatex, TLegend, Double, TGraph
import os, numpy, copy
from officialStyle import officialStyle


gROOT.SetBatch(True)
officialStyle(gStyle)
gStyle.SetOptTitle(0)
gStyle.SetPadLeftMargin(0.2)
gStyle.SetTitleX(0.5)

#file = TFile('RejectionMap.root')
file = TFile('RejectionMap_combine.root')

colours = [1, 2, 3, 4, 6]

def LegendSettings(leg):
    leg.SetBorderSize(0)
    leg.SetFillColor(10)
    leg.SetLineColor(0)
    leg.SetFillStyle(0)
    leg.SetTextSize(0.035)
    leg.SetTextFont(42)


def draw(hist, fname):
    c = TCanvas()
    hist.GetYaxis().SetTitle("bkg efficiency")
    hist.GetXaxis().SetTitle("k")
    hist.GetXaxis().SetNdivisions(507)
    hist.GetYaxis().SetNdivisions(507)
    hist.GetYaxis().SetTitleOffset(1.7)
    hist.Draw('APl')
    c.SaveAs(fname + '_cmb.gif')

    min = 1000.

    for ipoint in range(hist.GetN()):
        x = Double(0)
        y = Double(0)

        hist.GetPoint(ipoint, x, y)

        if min > y:
            min = y
            
    return min



def draws(hist, fname):
    c = TCanvas()

    min = 1000
    max = -1000

    min2 = 1000

    for ii, ihist in enumerate(hist):
#        print ihist.GetName()

        for ipoint in range(ihist.GetN()):
            x = Double(0)
            y = Double(0)
            
            ihist.GetPoint(ipoint, x, y)

            if min > y:
                min = y
            if max < y:
                max = y

            if ihist.GetName().find('Weight2NQ')!=-1:
                if min2 > y:
                    min2 = y


    y_start = 0.6
    if fname.find('40')!=-1:
        y_start = 0.2

    leg = TLegend(0.23, y_start, 0.6, y_start + 0.3)
    LegendSettings(leg)
    
    lname = ['Nominal #Delta#beta', 'Weight1', 'Weight1, NQ', 'Weight2', 'Weight2, NQ']

    for ii, ihist in enumerate(hist):
        ihist.GetYaxis().SetTitle("bkg efficiency")
        ihist.GetXaxis().SetTitle("k")
        ihist.GetXaxis().SetNdivisions(507)
        ihist.GetYaxis().SetNdivisions(507)
        ihist.GetYaxis().SetTitleOffset(1.7)
        ihist.SetMinimum(min*0.8)
        ihist.SetMaximum(max*1.2)
        ihist.SetLineColor(colours[ii])
        ihist.SetMarkerColor(colours[ii])

        leg.AddEntry(ihist, lname[ii], 'lp')

        if ii == 0:
            ihist.Draw('APl')
        else:
            ihist.Draw('Plsame')

        leg.Draw()

    c.SaveAs(fname + '_cmb.gif')
    
    return min2


old = TGraph()
dbeta_nominal = TGraph()
dbeta_tuning = TGraph()
pu_nominal = TGraph()
pu_tuning = TGraph()


for ii, ieff in enumerate(["40", "60", "80"]):
    
    print ii, ieff

    hist = file.Get('Graph_from_h_rejmap_db_'+ieff)
    min_db = draw(hist, 'db_' + ieff)

    hist1 = file.Get('Graph_from_h_rejmap_weight_Weight1_'+ieff)
    hist2 = file.Get('Graph_from_h_rejmap_weight_Weight1NQ_'+ieff)
    hist3 = file.Get('Graph_from_h_rejmap_weight_Weight2_'+ieff)
    hist4 = file.Get('Graph_from_h_rejmap_weight_Weight2NQ_'+ieff)
    hist_weight = [hist, hist1, hist2, hist3, hist4]
    
    min_pu = draws(hist_weight, 'all_db_' + ieff)

    _hist_ = file.Get('h_old_noecal_' + ieff)
    old.SetPoint(ii, int(ieff)*0.01, _hist_.GetMean())

    _hist2_ = file.Get('h_old_' + ieff)
    dbeta_nominal.SetPoint(ii, int(ieff)*0.01, _hist2_.GetMean())

    _hist3_ = file.Get('h_puweight_Weight2NQ_' + ieff)

    value = Double(_hist3_.GetMean())
    pu_nominal.SetPoint(ii, int(ieff)*0.01, value)

    dbeta_tuning.SetPoint(ii, int(ieff)*0.01, min_db)
    pu_tuning.SetPoint(ii, int(ieff)*0.01, min_pu)



combine = TCanvas()

graphs = [old, dbeta_nominal, dbeta_tuning, pu_nominal, pu_tuning]
legname = ['#Delta#beta, No ECAL timing cut',
           '#Delta#beta, ECAL',
           '#Delta#beta, tuning, ECAL',
           'PU weight, ECAL',
           'PU weight, tuning, ECAL'
           ]

leg_cmb = TLegend(0.25, 0.6, 0.72, 0.9)
LegendSettings(leg_cmb)

for ig, graph in enumerate(graphs):
    
    graph.GetXaxis().SetTitle('Signal efficiency')
    graph.GetYaxis().SetTitle('Background efficiency')

    graph.SetMinimum(0)
    graph.SetMaximum(0.2)
    graph.GetYaxis().SetNdivisions(507)

    graph.SetLineColor(colours[ig])
    graph.SetMarkerColor(colours[ig])



old.Draw('APL')
dbeta_nominal.Draw('PLsame')
dbeta_tuning.Draw('PLsame')
pu_nominal.Draw('PLsame')
pu_tuning.Draw('PLsame')

leg_cmb.AddEntry(old, legname[0], 'lp')
leg_cmb.AddEntry(dbeta_nominal, legname[1], 'lp')
leg_cmb.AddEntry(dbeta_tuning, legname[2], 'lp')
leg_cmb.AddEntry(pu_nominal, legname[3], 'lp')
leg_cmb.AddEntry(pu_tuning, legname[4], 'lp')

leg_cmb.Draw()

combine.SaveAs('roc_cmb.gif')
