# Interactive python code to produce pre / post fit plots
# Yuta.Takahashi@cern.ch

from ROOT import TFile, gDirectory, TH1F, TLegend
from CMGTools.RootTools.DataMC.DataMCPlot import DataMCPlot
from CMGTools.H2TauTau.proto.plotter.officialStyle import officialStyle
from CMGTools.RootTools.Style import *
from CMGTools.ZJetsTutorial.plotter.rootutils import *
import shelve, config, math, copy, logging

officialStyle(gStyle)
configclass = config.config()

mass = '125'
dic = shelve.open('plot_shelve')
table_7TeV = dic['nuisance_7TeV']
table_8TeV = dic['nuisance_8TeV']
tes = dic['tau_energy_scale']
table_list = [table_7TeV, table_8TeV]

__h__ = {}
__canvas__ = {}
__frame__ = {}

filelist = ['htt_mt.input_7TeV.root',
            'htt_mt.input_8TeV.root']



#QCD, Ztautau, EWK, tt, obs, higgs
h_hist = [[[0 for i in range(len(config.hist_dict))] for j in range(len(config.dirname))] for k in range(len(filelist))]
h_stack = [0 for i in range(len(config.dirname))]
  
####################################################################

def SaveAll():
    for key in __canvas__:
        __canvas__[key].SaveAs('Plots/'+__canvas__[key].GetName()+'.png')


def SaveFile():

    energy = ['7TeV','8TeV']
    _file_ = TFile('Myroot.root', 'recreate')

    for ienergy, file in enumerate(filelist):
        for icategory, catid in config.dirname.items():
            for hid, id in enumerate(config.hist_dict):

                hname = icategory + '_' + h_hist[ienergy][catid][hid].GetName() + '_' + energy[ienergy] + '_' + id
                print hname
                h_hist[ienergy][catid][hid].SetName(hname)
                h_hist[ienergy][catid][hid].Write()
                
    _file_.Write()
    _file_.Close()

def setUncertainty(hist, category, id, ienergy):

#    if(id=='VH' or id=='ggH' or id=='qqH' or id=='data_obs'):
#        pass
   
    err = [0 for i in range(hist.GetXaxis().GetNbins())]
    
    for key, val, in sorted(table_list[ienergy][category].items()):
        if(key=='r'): continue

        flag = val['flag']
        fit_cent = float(val['fit_cent'])
        fit_err = float(val['fit_err'])
        orig_sys = float(val['orig_sys'])
        bbb = int(val['bbb'])

        for iprocess in val['process'].split(','):
            if(iprocess==id):                

                if('scale_t_' in key): # tau energy scale

                    if(flag==True):

                        for ibin in range(1, hist.GetXaxis().GetNbins()+1):
                            bin_val = hist.GetBinContent(ibin)
                            stat_err = hist.GetBinError(ibin)

                            _id_ = id
                            if(id=='VH' or id=='ggH' or id=='qqH'): _id_ = _id_ + mass

                            _orig_sys_ = tes[category][config.energyname[ienergy]][_id_]
#                            print 'process, category, energy, bin, err = ', id, category, config.energyname[ienergy], ibin,  _orig_sys_[ibin-1]

                            hist.SetBinContent(ibin, (1+fit_cent*orig_sys)*bin_val)
                            hist.SetBinError(ibin, (1+fit_cent*orig_sys)*stat_err)
                            err[ibin-1] = err[ibin-1] + pow(bin_val*fit_err*orig_sys,2)                       
                    else:

                        for ibin in range(1, hist.GetXaxis().GetNbins()+1):
                            bin_val = hist.GetBinContent(ibin)
                            err[ibin-1] = err[ibin-1] + pow(bin_val*orig_sys,2)
                        

                else:

                    if(bbb==-1):

                        if(flag==True): hist.Scale(1+fit_cent*orig_sys)

                        for ibin in range(1, hist.GetXaxis().GetNbins()+1):
                            bin_val = hist.GetBinContent(ibin)
                            if(flag==True):
                                err[ibin-1] = err[ibin-1] + pow(bin_val*fit_err*orig_sys,2)
                            else:
                                err[ibin-1] = err[ibin-1] + pow(bin_val*orig_sys,2)
                    else:

                        if(flag==True):
                            # scale only one specific bin
                            bin_val = hist.GetBinContent(bbb)
                            stat_err = hist.GetBinError(bbb)
                            hist.SetBinContent(bbb, (1+fit_cent*orig_sys)*bin_val)
                            hist.SetBinError(bbb, (1+fit_cent*orig_sys)*stat_err)
                            err[bbb-1] = err[bbb-1] + pow(bin_val*fit_err*orig_sys,2)
                        else:
                            bin_val = hist.GetBinContent(bbb)
                            err[bbb-1] = err[bbb-1] + pow(bin_val*orig_sys,2)

                        
                        
    for ibin in range(1, hist.GetXaxis().GetNbins()+1):
        bin_err = hist.GetBinError(ibin)
        final_err = math.sqrt(bin_err*bin_err + err[ibin-1])
        hist.SetBinError(ibin, final_err)



def returnHist(option=None):

    __hist__ = [[[0 for i in range(len(config.hist_dict))] for j in range(len(config.dirname))] for k in range(len(filelist))]

    for ienergy, file in enumerate(filelist):
        if(option==None): _Myroot_ = TFile(file)
        for icategory, catid in config.dirname.items():
            if(option==None): _Myroot_.cd(icategory)
            for id in config.hist_dict:

                hnew = 0
                hid = config.hist_dict[id]['hid']
                
                if(option==None):
                    name = configclass.returnName(id, mass)
                    _h_ = gDirectory.Get(name)

#                    if(_h_ == None): logging.error('No histogram for ', id)

                    hnew = copy.deepcopy(_h_)
                    h_hist[ienergy][catid][hid] = copy.deepcopy(_h_)

                else:
                    hnew = copy.deepcopy(h_hist[ienergy][catid][hid])
                    
                configclass.DecoHist(id, hnew, icategory)
                __hist__[ienergy][catid][hid] = hnew
                __hist__[ienergy][catid][hid].SetName("h_" + str(ienergy) + "_" + icategory + "_" + id)
                
                setUncertainty(__hist__[ienergy][catid][hid], icategory, id, ienergy)

    return __hist__




def returnHistStack(hist, option=None):

    __stack__ = [0 for i in range(len(config.dirname))]

    for icategory, catid in config.dirname.items():

        if(option!=None):
            if(option!=catid): continue

        hname = 'h_'+icategory
        __stack__[catid] = DataMCPlot(hname)

        for id in config.hist_dict:
            hid = config.hist_dict[id]['hid']
            for ienergy in range(len(filelist)):

                __stack__[catid].AddHistogram(hist[ienergy][catid][hid].GetName(),
                                              hist[ienergy][catid][hid],
                                              config.hist_dict[id]['layer'])

        for ikey, ival in config.legname.items():

            group = []
            for iprocess in ival['group']:
                _hid_ = config.hist_dict[iprocess]['hid']
                for ienergy in range(len(filelist)):
                    group.append(hist[ienergy][catid][_hid_].GetName())

            __stack__[catid].Group(ikey, group)
            __stack__[catid].Hist(ikey).legendLine = configclass.returnLegendName(config.legname[ikey]['legname'], mass)
            __stack__[catid].Hist(ikey).NormalizeToBinWidth()
            __stack__[catid].Hist(ikey).Show(icategory, ikey)

            if(ikey == 'observed'): __stack__[catid].Hist(ikey).stack = False

    if(option==None):
        return __stack__
    else:
        return __stack__[option]


def AllTurnOff():
    for _table_list_ in table_list:
        for _key_, _val_ in sorted(_table_list_.items()):
            for key, val, in sorted(_val_.items()):
                if(key=='r'): continue
                val['flag'] = False


def TurnOn(nuisance_list, str):
    for icategory, ikey in nuisance_list:
        for _table_list_ in table_list:
            if(_table_list_[str].has_key(ikey)==True):
                _table_list_[str][ikey]['flag'] = True                    


def PrintList(thres = 0.5, cond = None):
    fmtstring = '%-20s %-40s %-30s %-15s %-15s %-10s %5s %5s'

    print '------------------------------------------------'
    print 'Shows nuisance parameters with large deviation (threshold > %s)' % thres
    print '------------------------------------------------'

    print fmtstring % ('category', 'nuisance parameter', 'affected_process', 'pull_center', 'pull_err', 'orig_unc', 'flag', 'bbb')
    print '---------------------------------------------------------------------------------------------------------------------------'
    
    counter = 0
    _name_list_ = []

    for _table_list_ in table_list:
        for _key_, _val_ in sorted(_table_list_.items()):
            for key, val, in sorted(_val_.items()):
                if(key=='r'): continue

                if(cond != None):
                    if(cond in _key_): pass
                    else: continue
            
                scale_cent = float(val['fit_cent'])
                scale_err = float(val['fit_err'])

                if(math.fabs(scale_cent) > thres):
                    print fmtstring % (_key_, key, val['process'], scale_cent, scale_err, val['orig_sys'], val['flag'], val['bbb'])
                    counter = counter+1
                    _name_list_.append([_key_, key])

    print '------------------------------------------------'
    print 'In total, there are %s indecies' % counter
    print '------------------------------------------------'

    return _name_list_



def Draw(channel, category, plotname=None, criteria=None):

    channel = config.channelname[channel]
    phase = config.phasespace[category]
    str = channel + "_" + phase
    cname = 'canvas_' + str

    AllTurnOff()

    if(criteria!=None):
        cname = cname + '_' + plotname
        nuisance_list = []

        if(isinstance(criteria, basestring)==True):
            nuisance_list.append([str, criteria])
        else:
            nuisance_list = criteria

        TurnOn(nuisance_list, str)

    __canvas__[cname] = buildCanvasOfficial(cname)
    index = config.dirname[str] 

    if(criteria!=None):
        __h__[cname] = returnHistStack(returnHist('2nd'), index)
        __h__[cname].DrawStack('HIST')
        return __h__[cname]
    else:
        h_stack[index].DrawStack('HIST')
        return h_stack[index]




h_stack = returnHistStack(returnHist())
#configclass.help()
