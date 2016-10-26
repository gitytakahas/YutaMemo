from ROOT import TFile

class config(object):

    def __init__(self, basedir, lumi):
        
        self.basedir = basedir
        self.lumi = lumi

        self.process = {

            'TT':{'name':'TT', 
                  'file':self.basedir + '/TT/TauTauAnalysis.TT_TuneCUETP8M1_ICHEP.root',
                  'cross-section':831.76,
                  'isSignal':0, 
                  'order':1},

            'DY10to50':{'name':'DY10to50', 
                        'file':self.basedir + '/DY/TauTauAnalysis.DYJetsToLL_M-10to50_TuneCUETP8M1_ICHEP.root', 
                        'cross-section':18610.0,
                        'isSignal':0, 
                        'order':2},

            'DY50':{'name':'DY50', 
                    'file':self.basedir + '/DY/TauTauAnalysis.DYJetsToLL_M-50_TuneCUETP8M1_ICHEP.root',
                    'cross-section':5765.4,
                    'isSignal':0, 
                    'order':3},
            
            'WWTo1L1Nu2Q':{'name':'WWTo1L1Nu2Q', 
                           'file':self.basedir + '/WW/TauTauAnalysis.WWTo1L1Nu2Q_ICHEP.root',
                           'cross-section':1.212,
                           'isSignal':0, 
                           'order':4},
            
            #    'WWTo4Q':{'name':'WWTo4Q', 
            #              'file':self.basedir + '/WW/TauTauAnalysis.WWTo4Q_4f_ICHEP.root', 
            #              'cross-section':22.82,
            #              'isSignal':0, 
            #              'order':5},
            
            'WZ':{'name':'WZ', 
                  'file':self.basedir + '/WZ/TauTauAnalysis.WZ_TuneCUETP8M1_ICHEP.root', 
                  'cross-section':10.71,
                  'isSignal':0, 
                  'order':6},
            
            'ZZ':{'name':'ZZ', 
                  'file':self.basedir + '/ZZ/TauTauAnalysis.ZZ_TuneCUETP8M1_ICHEP.root', 
                  'cross-section':3.22,
                  'isSignal':0, 
                  'order':7},
            
            'WJets':{'name':'WJets', 
                     'file':self.basedir + 'WJ/TauTauAnalysis.WJetsToLNu_TuneCUETP8M1_ICHEP.root', 
                     'cross-section':61526.7,
                     'isSignal':0, 
                     'order':8},
    
            'ST_t_top':{'name':'ST_t_top', 
                        'file':self.basedir + 'ST/TauTauAnalysis.ST_t-channel_top_4f_leptonDecays_ICHEP.root', 
                        'cross-section':136.02,
                        'isSignal':0, 
                        'order':9},
            
            
            'ST_t_antitop':{'name':'ST_t_antitop', 
                            'file':self.basedir + 'ST/TauTauAnalysis.ST_t-channel_antitop_4f_leptonDecays_ICHEP.root', 
                            'cross-section':80.95,
                            'isSignal':0, 
                            'order':10},
            
            
            'ST_tw_top':{'name':'ST_tw_top', 
                         'file':self.basedir + 'ST/TauTauAnalysis.ST_tW_top_5f_inclusiveDecays_ICHEP.root', 
                         'cross-section':35.60,
                         'isSignal':0, 
                         'order':11},
            
            'ST_tw_antitop':{'name':'ST_tw_antitop', 
                             'file':self.basedir + 'ST/TauTauAnalysis.ST_tW_antitop_5f_inclusiveDecays_ICHEP.root', 
                             'cross-section':35.60,
                             'isSignal':0, 
                             'order':12},
            
            #    'Signal':{'name':'Signal', 
            #              'file':self.basedir + 'signal/TauTauAnalysis.LowMass_30GeV_DiTauResonance_ICHEP.root', 
            #              'cross-section':1.,
            #              'isSignal':1, 
            #              'order':3000},
            
            'data_obs':{'name':'data_obs', 
                        'file':self.basedir + 'SingleMuon/TauTauAnalysis.SingleMuon_Run2016_ICHEP.root',
                        'cross-section':1.,
                        'isSignal':0, 
                        'order':2999},

            'QCD':{'name':'QCD', 
                   'file':None,
                   'cross-section':None,
                   'isSignal':0, 
                   'order':0},

            }



        print 'Retrieve normalization'

        for processname, val in self.process.iteritems():
            if processname=='QCD': continue
            print processname,

            file = TFile(val['file'])            
            ntot = file.Get("histogram_mutau/cutflow_mutau").GetBinContent(1)
            self.process[processname]['ntot'] = ntot
            self.process[processname]['file'] = file

            print '... Register : ', self.process[processname]['ntot'], 'SF = ', self.process[processname]['cross-section']*self.lumi*1000/self.process[processname]['ntot']

