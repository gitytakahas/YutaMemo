from ROOT import TFile, gDirectory, gROOT, TH1F, TLegend
from CMGTools.RootTools.DataMC.DataMCPlot import DataMCPlot
from CMGTools.H2TauTau.proto.plotter.officialStyle import officialStyle
from CMGTools.RootTools.Style import *
from CMGTools.ZJetsTutorial.plotter.rootutils import *
import shelve, config, math, copy

officialStyle(gStyle)
configclass = config.config()

mass = '125'
dic = shelve.open('/data/ytakahas/plot_shelve')
table_7TeV = dic['nuisance_7TeV']
table_8TeV = dic['nuisance_8TeV']
table_list = [table_7TeV, table_8TeV]

__h__ = {}
__canvas__ = {}
__frame__ = {}
__nuisance__ = {}
__leg__ = {}

filelist = ['/data/ytakahas/htt_mt.input_7TeV.root',
            '/data/ytakahas/htt_mt.input_8TeV.root']


#QCD, Ztautau, EWK, tt, obs, higgs
h_hist = [[[0 for i in range(len(config.hist_dict))] for j in range(len(config.dirname))] for k in range(len(filelist))]
h_stack = [0 for i in range(len(config.dirname))]
  
####################################################################

def SaveAll():
    for key in __canvas__:
#        print __canvas__[key]
        __canvas__[key].SaveAs('Plots/'+__canvas__[key].GetName()+'.png')

def setUncertainty(hist, category, id, ienergy):

    if(id=='VH' or id=='ggH' or id=='qqH' or id=='data_obs'):
        return 'No need to set uncertainty'
   
    err = [0 for i in range(hist.GetXaxis().GetNbins())]
    
    for key, val, in sorted(table_list[ienergy][category].items()):
        if(key=='r'): continue

        flag = val['flag']
        fit_cent = float(val['fit_cent'])
        fit_err = float(val['fit_err'])
        orig_sys = float(val['orig_sys'])

        for iprocess in val['process'].split(','):
            if(iprocess==id):                

                if(flag==True): hist.Scale(1+fit_cent*orig_sys)
                    
                for ibin in range(1, hist.GetXaxis().GetNbins()+1):
                    bin_val = hist.GetBinContent(ibin)
                    if(flag==True):
                        err[ibin-1] = err[ibin-1] + pow(bin_val*fit_err*orig_sys,2)
                    else:
                        err[ibin-1] = err[ibin-1] + pow(bin_val*orig_sys,2)

                        
    for ibin in range(1, hist.GetXaxis().GetNbins()+1):
        bin_err = hist.GetBinError(ibin)
        final_err = math.sqrt(bin_err*bin_err + err[ibin-1])
        hist.SetBinError(ibin, final_err)



def returnHist(option=None):

    __hist__ = [[[0 for i in range(len(config.hist_dict))] for j in range(len(config.dirname))] for k in range(len(filelist))]

    for ienergy, file in enumerate(filelist):
        if(option==None): Myroot = TFile(file)
        for icategory, catid in config.dirname.items():
            if(option==None): Myroot.cd(icategory)
            for id in config.hist_dict:

                hnew = 0
                hid = config.hist_dict[id]['hid']
                
                if(option==None):
                    name = configclass.returnName(id, mass)
                    _h_ = gDirectory.Get(name)

                    if(_h_ == None): print 'ERROR : No histogram for ', id

                    hnew = copy.deepcopy(_h_)
                    h_hist[ienergy][catid][hid] = copy.deepcopy(_h_)

                else:
                    hnew = copy.deepcopy(h_hist[ienergy][catid][hid])
                    
#                configclass.DecoHist(id, hnew)

                __hist__[ienergy][catid][hid] = hnew
                __hist__[ienergy][catid][hid].SetTitle(icategory)
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
                group.append(hist[0][catid][_hid_].GetName())
                group.append(hist[1][catid][_hid_].GetName())

            __stack__[catid].Group(ikey, group)
            __stack__[catid].Hist(ikey).legendLine = configclass.returnLegendName(config.legname[ikey]['legname'], mass)
            __stack__[catid].Hist(ikey).NormalizeToBinWidth()

            if(ikey == 'observed'): __stack__[catid].Hist(ikey).stack = False

    if(option==None):
        return __stack__
    else:
        return __stack__[option]


def returnNuisance(str, plotname, dict, err_total):

    list_7TeV = [0 for i in range(len(dict['7TeV']))]
    list_8TeV = [0 for i in range(len(dict['8TeV']))]
        
    h_nuisance = [list_7TeV, list_8TeV]

    for ienergy, energy in enumerate(['7TeV','8TeV']):
        counter = 0
        for key, bin_err in sorted(dict[energy].items()):

            hname = str + plotname + energy + "_" + key

            title = key.replace('CMS_','')
            title = title.replace('_7TeV', ' (7TeV)')
            title = title.replace('_8TeV', ' (8TeV)')
            
            h_nuisance[ienergy][counter] = TH1F(hname, title,
                                                len(bin_err),
                                                0,
                                                h_hist[0][config.dirname[str]][0].GetXaxis().GetXmax())

            for ibin in range(1, len(bin_err)+1):

#                fraction = float(bin_err[ibin-1])
                fraction = math.sqrt(bin_err[ibin-1])
                if(err_total[ibin-1]!=0):
                    #fraction = float(bin_err[ibin-1]/err_total[ibin-1])
#                    fraction = math.sqrt(bin_err[ibin-1])
                    fraction = math.sqrt(bin_err[ibin-1])

                h_nuisance[ienergy][counter].SetBinContent(ibin, fraction)

            counter = counter + 1

    return h_nuisance





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
    fmtstring = '%-20s %-40s %-30s %-15s %-15s %-10s %5s'

    print '------------------------------------------------'
    print 'Shows nuisance parameters with large deviation (threshold > %s)' % thres
    print '------------------------------------------------'

    print fmtstring % ('category', 'nuisance parameter', 'affected_process', 'pull_center', 'pull_err', 'orig_unc', 'flag')
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
                    print fmtstring % (_key_, key, val['process'], scale_cent, scale_err, val['orig_sys'], val['flag'])
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




def DrawNuisance(channel, category, plotname, thres, criteria=None):

    channel = config.channelname[channel]
    phase = config.phasespace[category]
    str = channel + "_" + phase
    catid = config.dirname[str]

    AllTurnOff()

    if(criteria!=None):

        nuisance_list = []

        if(isinstance(criteria, basestring)==True):
            nuisance_list.append([str, criteria])
        else:
            nuisance_list = criteria

        TurnOn(nuisance_list, str)


    dict = {}
    err_total = [0 for ii in range(h_hist[0][catid][0].GetXaxis().GetNbins())]
    
    for ienergy, _table_list_ in enumerate(table_list):

        _dict_ = {}
    
        for key, val in sorted(_table_list_[str].items()):
            if(key=='r'): continue

            err = [0 for ii in range(h_hist[ienergy][catid][0].GetXaxis().GetNbins())]

            flag = val['flag']
            fit_cent = float(val['fit_cent'])
            fit_err = float(val['fit_err'])
            orig_sys = float(val['orig_sys'])

            for iprocess in val['process'].split(','):

                id = config.hist_dict[iprocess]['hid']
                
                if(iprocess=='VH' or iprocess=='ggH' or iprocess=='qqH' or iprocess=='data_obs'): continue
                for ibin in range(1, h_hist[ienergy][catid][id].GetXaxis().GetNbins()+1):

                    bin_val = h_hist[ienergy][catid][id].GetBinContent(ibin)
                    if(flag==True):
                        sf = 1+fit_cent*orig_sys
                        if(bin_val==0):
                            pass
                        else:
                            err[ibin-1] = err[ibin-1] + pow(sf*bin_val*fit_err*orig_sys,2)/pow(sf*bin_val,2)
                            err_total[ibin-1] = err_total[ibin-1] + pow(sf*bin_val*fit_err*orig_sys,2)/pow(sf*bin_val,2)
                    else:
                        if(bin_val==0):
                            pass
                        else:
                            err[ibin-1] = err[ibin-1] + pow(bin_val*orig_sys,2)/pow(bin_val,2)
                            err_total[ibin-1] = err_total[ibin-1] + pow(bin_val*orig_sys,2)/pow(bin_val,2)

            _dict_[key] = err

        if(ienergy==0): dict['7TeV'] = _dict_
        elif(ienergy==1): dict['8TeV'] = _dict_


    cname = 'nuisance_canvas_' + str + '_' + plotname
    
    __canvas__[cname] = buildCanvasOfficial(cname)
    _hname_ = 'frame' + cname

    __frame__[_hname_] = TH1F(_hname_, _hname_,
                              h_hist[0][catid][0].GetXaxis().GetNbins(),
                              0,
                              h_hist[0][catid][0].GetXaxis().GetXmax())

    for ibin in range(1, h_hist[0][catid][0].GetXaxis().GetNbins()+1):
        __frame__[_hname_].SetBinContent(ibin, math.sqrt(err_total[ibin-1]))
                    

    configclass.DecoNuiHist(__frame__[_hname_], str, __frame__[_hname_].GetMaximum()*1.2)
    __frame__[_hname_].Draw("pl")
    __nuisance__[cname] = returnNuisance(str, plotname, dict, err_total)

    counter = 0

    __leg__[cname] = TLegend(0.45,0.6,0.89,0.88);
    __leg__[cname].AddEntry(__frame__[_hname_], 'Total','l')
    configclass.LegendSettings(__leg__[cname])

    for ienergy, energy in enumerate(['7TeV','8TeV']):
        for ikey in range(len(__nuisance__[cname][ienergy])):

            if(__nuisance__[cname][ienergy][ikey].GetMaximum() > thres):
                configclass.DecoNuiColorHist(__nuisance__[cname][ienergy][ikey], 20, 1, counter+2)
                __nuisance__[cname][ienergy][ikey].Draw("plsame")
                counter = counter+1

                __leg__[cname].AddEntry(__nuisance__[cname][ienergy][ikey], __nuisance__[cname][ienergy][ikey].GetTitle(), 'l')

    __leg__[cname].Draw()


h_stack = returnHistStack(returnHist())
configclass.help()
