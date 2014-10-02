import ROOT, os, numpy
#from officialStyle import officialStyle
from ROOT import TLegend, TCanvas
from CMGTools.RootTools.DataMC.DataMCPlot import DataMCPlot
from CMGTools.H2TauTau.proto.plotter.officialStyle import officialStyle
from ROOT import TColor, kMagenta, kOrange, kRed, kBlue, kGray, kBlack

ROOT.gROOT.SetBatch(True)
officialStyle(ROOT.gStyle)
#ROOT.gStyle.SetOptTitle(1)
#ROOT.gStyle.SetPadLeftMargin(0.18)
#ROOT.gStyle.SetPadBottomMargin(0.15)

col_qcd = TColor.GetColor(250,202,255)
col_tt  = TColor.GetColor(155,152,204)
col_ttv  = TColor.GetColor(155,182,204)
col_ewk = TColor.GetColor(222,90,106)
col_zll = TColor.GetColor(100,182,232)
col_red = TColor.GetColor(248,206,104)

colours = [2, 3, 4, 6, 7, 8]
nbin=20

variables = {
    'bdt_muon_pt': {'nbin':nbin, 'xtitle':'muon pT (GeV)', 'xmin':0, 'xmax':200},
    'bdt_tau_pt': {'nbin':nbin, 'xtitle':'tau pT (GeV)', 'xmin':0, 'xmax':200},
    'bdt_evt_nbjet': {'nbin':5, 'xtitle':'Number of bjet', 'xmin':0, 'xmax':5},
    'bdt_evt_LT': {'nbin':nbin, 'xtitle':'M(#tau, sub leading lepton)', 'xmin':0, 'xmax':400},
    'bdt_evt_njet_or30': {'nbin':10, 'xtitle':'Number of jets (p_{T} > 30GeV)', 'xmin':0, 'xmax':10},
    'bdt_evt_max_jet_eta':{'nbin':10, 'xtitle':'Max. jet #eta', 'xmin':0, 'xmax':5},
    'bdt_evt_sphericity':{'nbin':10, 'xtitle':'Sphericity', 'xmin':0, 'xmax':1},
    'bdt_evt_aplanarity':{'nbin':10, 'xtitle':'Aplanarity', 'xmin':0, 'xmax':0.2}
}

selections = {
#    'VV':{'selection':'bdt_evt_processid<=2', 'col':col_zll, 'order':1},
#    'ttV':{'selection':'bdt_evt_processid>=17 && bdt_evt_processid<=19', 'col':col_tt, 'order':2},
#    'reducible':{'selection':'bdt_evt_processid==20', 'col':kOrange-2, 'order':3},
#    'data':{'selection':'bdt_evt_processid==100', 'col':1, 'order':2999}
    'VV':{'selection':'bdt_evt_processid<=2', 'col':col_zll, 'order':1},
    'ttV':{'selection':'bdt_evt_processid>=17 && bdt_evt_processid<=18', 'col':kOrange-2, 'order':2},
    'ttH':{'selection':'bdt_evt_processid==19', 'col':col_ttv, 'order':3},
    'reducible':{'selection':'bdt_evt_processid==20', 'col':col_qcd, 'order':4},
    'signal':{'selection':'bdt_evt_processid==16', 'col':kRed, 'order':1001},
    'data':{'selection':'bdt_evt_processid==100', 'col':1, 'order':2999}
    }

def ensureDir(directory):
    if not os.path.exists(directory):
        os.makedirs(directory)

def makePlotsVars(tree, isSignal=False):
   
    for ivar, var in variables.items():

        c = TCanvas()
        h_stack = DataMCPlot('hs_' + ivar)
        h_stack.legendBorders = 0.65, 0.6, 0.85, 0.85
        
        for iprocess, process in selections.items():

            if not isSignal and iprocess=='signal':
                continue

            if isSignal and iprocess=='data':
                continue
            
            hist = ROOT.TH1F('h_'+ivar+'_'+iprocess, '', var['nbin'], var['xmin'], var['xmax'])
            hist.GetXaxis().SetTitle(var['xtitle'])
            hist.GetYaxis().SetNdivisions(507)
            hist.Sumw2()

            sel = '(' + process['selection'] + ')*bdt_evt_weight'
#            print hist.GetName(), ivar, sel

            _ivar_ = ivar
            if ivar == 'bdt_evt_max_jet_eta':
                _ivar_ = 'TMath::Abs(' + ivar + ')'
            tree.Project(hist.GetName(), _ivar_, sel)


            if iprocess=='data':
                hist.SetMarkerStyle(20)
            elif iprocess=='signal':
                hist.Scale(10.)
                hist.SetLineWidth(2)
                hist.SetLineColor(process['col'])
                hist.SetMarkerColor(process['col'])
                hist.SetMarkerSize(0)
            else:
                hist.SetFillStyle(1)
                hist.SetLineWidth(2)
                hist.SetFillColor(process['col'])
                hist.SetLineColor(process['col'])
                
            
            h_stack.AddHistogram(hist.GetName(), hist, process['order'])
            h_stack.Hist(hist.GetName()).legendLine = iprocess

            if iprocess=='data' or iprocess=='signal':
                h_stack.Hist(hist.GetName()).stack = False
            if iprocess=='signal':
                h_stack.Hist(hist.GetName()).legendLine = 'signal (x10)'

        print h_stack
#        h_stack.NormalizeToBinWidth()
        h_stack.DrawStack('HIST')
#       h_stack.DrawRatioStack('HIST')
        
        ensureDir('plots')
        cname =  'plots/' + ivar + '.gif'
        if isSignal:
            cname = cname.replace('.gif', '_f12.gif')
        else:
            cname = cname.replace('.gif', '_f3.gif')
            
        print cname
        c.Print(cname)


if __name__ == '__main__':

    tfile = ROOT.TFile('BDT_training_ss_f3.root')
    tree = tfile.Get('Tree')
    makePlotsVars(tree)

    tfile = ROOT.TFile('BDT_training_ss_f12.root')
    tree = tfile.Get('Tree')
    makePlotsVars(tree, True)
