import os, numpy, math, copy, math, sys, collections
from array import array
from ROOT import gStyle, TCanvas, TLegend, TH1F
from officialStyle import officialStyle
from DisplayManager import DisplayManager
from DataMCPlot import *

import MultiDraw

gROOT.SetBatch(True)
#gROOT.SetBatch(False)
officialStyle(gStyle)
gStyle.SetOptTitle(0)

def comparisonPlots(hist, pname='sync.pdf', isRatio=True):

    display = DisplayManager(pname, isRatio, 0.42, 0.65)
    display.Draw(hist)


def ensureDir(directory):
    if not os.path.exists(directory):
        os.makedirs(directory)

#lumi=24.5
lumi=12.9

evaluateQCDfromdata = True
normalizeWusinghighMT = True
WsidebandMTvalue = 80.

basedir = '/mnt/t3nfs01/data01/shome/ytakahas/work/TauTau/SFrameAnalysis/AnalysisOutput/'

process = {

    'TT':{'name':'TT', 
          'file':basedir + '/TT/TauTauAnalysis.TT_TuneCUETP8M1.root',
          'cross-section':831.76,
          'isSignal':0, 
          'order':1},

    'DY10to50':{'name':'DY10to50', 
                'file':basedir + '/DY/TauTauAnalysis.DYJetsToLL_M-10to50_TuneCUETP8M1.root', 
                'cross-section':18610.0,
                'isSignal':0, 
                'order':2},

    'DY50':{'name':'DY50', 
            'file':basedir + '/DY/TauTauAnalysis.DYJetsToLL_M-50_TuneCUETP8M1.root',
            'cross-section':5765.4,
            'isSignal':0, 
            'order':3},

    'WWTo1L1Nu2Q':{'name':'WWTo1L1Nu2Q', 
                   'file':basedir + '/WW/TauTauAnalysis.WWTo1L1Nu2Q.root',
                   'cross-section':1.212,
                   'isSignal':0, 
                   'order':4},

#    'WWTo4Q':{'name':'WWTo4Q', 
#              'file':basedir + '/WW/TauTauAnalysis.WWTo4Q_4f.root', 
#              'cross-section':22.82,
#              'isSignal':0, 
#              'order':5},

   'WZ':{'name':'WZ', 
         'file':basedir + '/WZ/TauTauAnalysis.WZ_TuneCUETP8M1.root', 
         'cross-section':10.71,
         'isSignal':0, 
         'order':6},

   'ZZ':{'name':'ZZ', 
         'file':basedir + '/ZZ/TauTauAnalysis.ZZ_TuneCUETP8M1.root', 
         'cross-section':3.22,
         'isSignal':0, 
         'order':7},

    'WJets':{'name':'WJets', 
             'file':basedir + 'WJ/TauTauAnalysis.WJetsToLNu_TuneCUETP8M1.root', 
             'cross-section':61526.7,
             'isSignal':0, 
             'order':8},

#    'Signal':{'name':'Signal', 
#              'file':basedir + 'signal/TauTauAnalysis.LowMass_30GeV_DiTauResonance.root', 
#              'cross-section':1.,
#              'isSignal':1, 
#              'order':3000},

    'data':{'name':'data_obs', 
            'file':basedir + 'SingleMuon/TauTauAnalysis.SingleMuon_Run2016.root',
            'cross-section':1.,
            'isSignal':0, 
            'order':2999},

}

vardir = {
    'm_vis':{'drawname':'m_vis', 'nbins':30, 'min':0, 'max':120, 'label':'visible mass (GeV)'},
    'mt_1':{'drawname':'mt_1', 'nbins':40, 'min':0, 'max':200, 'label':'Transverse mass (GeV)'},
    'met':{'drawname':'met', 'nbins':30, 'min':0, 'max':200, 'label':'missing E_{T} (GeV)'},
    'dR_ll':{'drawname':'dR_ll', 'nbins':30, 'min':0, 'max':math.pi, 'label':'#Delta R (l, #tau)'},
    'pt_1':{'drawname':'pt_1', 'nbins':30, 'min':0, 'max':200, 'label':'muon pT (GeV)'},
    'pt_2':{'drawname':'pt_2', 'nbins':30, 'min':0, 'max':200, 'label':'tau pT (GeV)'}
    }


# currently, for mu-tau channel only
categories = collections.OrderedDict()
categories['nominal_ss'] = {'sel':'dilepton_veto == 0 && extraelec_veto == 0 && extramuon_veto == 0 && againstElectronVLooseMVA6_2 == 1 && againstMuonTight3_2 == 1 && iso_1 < 0.15 && iso_2 == 1 && channel==1 && q_1*q_2>0 && channel==1'}
categories['nominal_os'] = {'sel':'dilepton_veto == 0 && extraelec_veto == 0 && extramuon_veto == 0 && againstElectronVLooseMVA6_2 == 1 && againstMuonTight3_2 == 1 && iso_1 < 0.15 && iso_2 == 1 && channel==1 && q_1*q_2<0 && channel==1'}


# Retrieve the # of generated events for the normalization
for processname, val in process.iteritems():

    file = TFile(val['file'])

    ntot = file.Get("histogram_mutau/cutflow_mutau").GetBinContent(1)
    process[processname]['ntot'] = ntot
    process[processname]['file'] = file

    print 'Register : ', processname, process[processname]['ntot']



hists = {}

for catname, cat in categories.iteritems():

    print '-'*80
    print '[INFO] Categories = ', catname
    print '[INFO] ', cat['sel']
    print '-'*80

    for processname, val in process.iteritems():

        tree = val['file'].Get('tree_mutau')

        print        
        print '[INFO] : Process = ', processname
        
        var_tuples = []

        for varname, var in vardir.iteritems():        
            hname = 'hist_' + catname + '_' + processname + '_' + varname

            hist_register = TH1F(hname, hname, var['nbins'], var['min'], var['max'])
            hist_register.GetXaxis().SetTitle(var['label'])
            hist_register.Sumw2()
            hist_register.GetXaxis().SetLabelSize(0)
            
            if val['name'] in ['data_obs']:
                hist_register.SetMarkerStyle(20)
                hist_register.SetMarkerSize(0.5)


            hists[hname] = hist_register

            var_tuples.append('{var} >> {hist}'.format(var=var['drawname'], hist=hname))

        cut = '({c}) * {we}'.format(c=cat['sel'], we='weight')
        tree.MultiDraw(var_tuples, cut)


SFforW = 1.

if normalizeWusinghighMT:

    data = 0
    totalmc = 0
    wyield = 0

    for processname, val in process.iteritems():
        hname = 'hist_nominal_os_' + processname + '_mt_1'
        bin_min = hists[hname].GetXaxis().FindBin(WsidebandMTvalue)
        bin_max = hists[hname].GetXaxis().FindBin(hists[hname].GetXaxis().GetXmax())

        pname = val['name']
        scale = val['cross-section']*lumi*1000/val['ntot']

        if pname == 'WJets':
            wyield = hists[hname].Integral(bin_min, bin_max)*scale
        elif pname == 'data_obs':
            data = hists[hname].Integral(bin_min, bin_max)
        else:
            totalmc += hists[hname].Integral(bin_min, bin_max)*scale


    if wyield!=0:
        SFforW = (data - totalmc)/wyield
        print 'W normalization summary : data ', data, ', other MC : ', totalmc, ', Wyield : ', wyield, ', SF = ', SFforW


for catname, cat in categories.iteritems():

    ensureDir('fig_' + catname)

    for varname, var in vardir.iteritems():        

        stackname = 'stackhist_' + catname + '_' + varname
        hist = DataMCPlot(stackname)
        hist.legendBorders = 0.55, 0.55, 0.88, 0.88

        for processname, val in process.iteritems():

            hname = 'hist_' + catname + '_' + processname + '_' + varname
            pname = val['name']
               
            if not pname in ['data_obs']:
                SF = val['cross-section']*lumi*1000/val['ntot']
                hists[hname].Scale(SF)
            #                print '[INFO] : ', val['name'], ', sigma =', val['cross-section'], 'SF = ', SF

            if pname == 'WJets':
                hists[hname].Scale(SFforW)
                print 'additionally normalize W by ', SFforW



            hist.AddHistogram(pname, hists[hname], val['order'])

            if pname in ['data_obs']:
                hist.Hist(pname).stack = False


        if evaluateQCDfromdata and catname.find('os')!=-1:
            h_QCD = None

            for processname, val in process.iteritems():

                hname = 'hist_' + catname.replace('os', 'ss') + '_' + processname + '_' + varname

                addfactor = -1
                if val['name'] == 'data_obs':
                    addfactor = 1.

                if h_QCD == None:
                    h_QCD = copy.deepcopy(hists[hname])
                else:
                    h_QCD.Add(hists[hname], addfactor)

            hist.AddHistogram('QCD', h_QCD, 0)
            

        hist.Group('electroweak', ['WJets', 'WZ', 'ZZ', 'WWTo1L1Nu2Q'])
#        hist.Group('electroweak', ['WZ', 'ZZ', 'WWTo1L1Nu2Q'])

        print hist
    
        comparisonPlots(hist, 'fig_' + catname + '/' + stackname + '.pdf')

