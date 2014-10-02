# Interactive python code to produce pre / post fit plots
# Yuta.Takahashi@cern.ch

from ROOT import TFile, gDirectory, TH1F, TLegend, gROOT, TCanvas, gStyle
from optparse import OptionParser, OptionGroup
#from CMGTools.RootTools.DataMC.DataMCPlot import DataMCPlot
#from CMGTools.H2TauTau.proto.plotter.officialStyle import officialStyle
#from CMGTools.RootTools.Style import *
#from CMGTools.ZJetsTutorial.plotter.rootutils import *
import shelve, math, copy, ConfigParser, sys

gStyle.SetOptStat(0)

fmt = '%-60s %-4s %.2f %.2f'

#officialStyle(gStyle)
#configclass = config.config()

#dic = shelve.open('plot_shelve')
#table_7TeV = dic['nuisance_7TeV']
#table_8TeV = dic['nuisance_8TeV']
#tes = dic['tau_energy_scale']
#table_list = [table_7TeV, table_8TeV]

canvas = {}
leg = {}
histDict = {}

def stop():
        sys.stderr.write('[Read]\tstop.\tPress "q" to quit >')
        ans = raw_input('> ')

        if ans in ['q', 'Q']:
		return -1
        elif ans in ['.', '.q', 'Q']:
		return -1


def separateModule(init, channel, name):
	
	dict = {}

	for ii in init.get(channel, name).split():
		_ii_ = ii.split(':')
		processname = _ii_[0]
		process = _ii_[1].split('_')
		dict[processname] = process

	return dict




def tFileCopy(tfile, histName):
	
	hist = tfile.Get(histName)
	if not hist:
		msg = '{histName} not found in {tfile}'.format(histName=histName, tfile=tfile)
		raise RuntimeError(msg)

	histNew = copy.deepcopy(hist)
	histNew.SetName(histName)
	return histNew

def LegendSettings(leg):
	leg.SetBorderSize(0)
	leg.SetLineColor(0)
	leg.SetLineStyle(1)
	leg.SetLineWidth(0)
	leg.SetFillColor(0)
	leg.SetFillStyle(0)



def main():

	parser = OptionParser(usage='usage: %prog [options] ARGs',
			      description='Pre-/Post-fit plots Maker')

	parser.add_option('-c', '--channel', dest='channel', default='mt', action='store',
			  help='channels to be considered for the plot.')

	parser.add_option('-a', '--analysis', dest='analysis', default='sm', action='store',
			  help='Analysis flag for SM or MSSM analysis')

	parser.add_option('-p', '--period', dest='period', default='8TeV', action='store',
			  help='period used for the S/B plots. Default : 7TeV 8TeV')

	parser.add_option('-m', '--mass', dest='mass', default='125', action='store',
			  help='Target Higgs mass. Default : 125')

	parser.add_option("-b", "--batch", dest='batch', action="store_true", default=False,
			  help='Set Batch mode. Default : False')

	(options, args) = parser.parse_args()


	if(options.batch==True):
		gROOT.SetBatch(True)


	init = ConfigParser.SafeConfigParser()
	if options.analysis=='sm':
		init.read('config.ini')
	else:
		init.read('config_mssm.ini')

			
	for ichn in options.channel.split():        
		for iperiod in options.period.split():

			list_category = init.get(ichn, 'category_'+iperiod).split()
			list_bkg = separateModule(init, ichn, 'bkg')
			list_sig = separateModule(init, ichn, 'signal')
			filename = 'htt_' + str(ichn) + '.input_' + iperiod + '.root'
			
			for icategory in list_category:

				categoryname = init.get(ichn, 'prefix') + '_' + icategory
				uname = categoryname + '_' + iperiod

				print uname, '----------------------------------------------------'
				print '\t InputFile = ', filename, ', Category = ', categoryname
				print '\t Background = ', list_bkg
				print '\t Signal = ', list_sig
				
				file = TFile(filename)
				
				h_bkg = {}
						
				for ikey, content in sorted(list_bkg.items()):
					for ibkg in content:
						
						key = uname + '_' + ikey
						
						if h_bkg.has_key(key):
							h_bkg[key].Add(tFileCopy(file, categoryname+'/'+ibkg))
						else:
							h_bkg[key] = tFileCopy(file, categoryname+'/'+ibkg)
							h_bkg[key].SetName(ikey)
							
							
				histDict[uname] = h_bkg
				
#	print histDict


	for ikey, content in sorted(histDict.items()):
		# content is a dictionary !

		canvas[ikey] = TCanvas(ikey, '', 600,600)
		counter_hist = 0

		leg[ikey] = TLegend(0.68,0.63,0.9,0.87)
		LegendSettings(leg[ikey])

		for keyname, hist in sorted(content.items()):			

			hist.SetTitle(ikey)
			hist.SetLineColor(counter_hist+1)
			hist.SetLineWidth(2)
			hist.GetXaxis().SetTitle('M_{#tau#tau} (GeV)')
			hist.GetYaxis().SetTitle('Uncertainty')

			for ibin in range(1,hist.GetNbinsX()+1):
				hist.SetBinContent(ibin, hist.GetBinError(ibin))
				hist.SetBinError(ibin, 0)
#				print fmt % (keyname, ibin, hist.GetBinContent(ibin), hist.GetBinError(ibin))


			lname = keyname.replace(ikey+'_', '')
			print lname
			leg[ikey].AddEntry(hist, lname, 'lep')
		
			if counter_hist==0:
				hist.Draw("h")
			else:
				hist.Draw("hsame")
		
			counter_hist += 1
		leg[ikey].Draw()
		canvas[ikey].Modified()
		canvas[ikey].Update()
							

												


#QCD, Ztautau, EWK, tt, obs, higgs
#h_hist = [[[0 for i in range(len(config.hist_dict))] for j in range(len(config.dirname))] for k in range(len(filelist))]
#h_stack = [0 for i in range(len(config.dirname))]
#  
#
#def returnHist(option=None):
#
#    __hist__ = [[[0 for i in range(len(config.hist_dict))] for j in range(len(config.dirname))] for k in range(len(filelist))]
#
#    for ienergy, file in enumerate(filelist):
#        if(option==None): _Myroot_ = TFile(file)
#        for icategory, catid in config.dirname.items():
#            if(option==None): _Myroot_.cd(icategory)
#            for id in config.hist_dict:
#
#                hnew = 0
#                hid = config.hist_dict[id]['hid']
#                
#                if(option==None):
#                    name = configclass.returnName(id, mass)
#                    _h_ = gDirectory.Get(name)
#
#
#                    hnew = copy.deepcopy(_h_)
#                    h_hist[ienergy][catid][hid] = copy.deepcopy(_h_)
#
#                else:
#                    hnew = copy.deepcopy(h_hist[ienergy][catid][hid])
#                    
#                configclass.DecoHist(id, hnew, icategory)
#                __hist__[ienergy][catid][hid] = hnew
#                __hist__[ienergy][catid][hid].SetName("h_" + str(ienergy) + "_" + icategory + "_" + id)
#                
#                setUncertainty(__hist__[ienergy][catid][hid], icategory, id, ienergy)
#
#    return __hist__
#
#
#
#
#def returnHistStack(hist, option=None):
#
#    __stack__ = [0 for i in range(len(config.dirname))]
#
#    for icategory, catid in config.dirname.items():
#
#        if(option!=None):
#            if(option!=catid): continue
#
#        hname = 'h_'+icategory
#        __stack__[catid] = DataMCPlot(hname)
#
#        for id in config.hist_dict:
#            hid = config.hist_dict[id]['hid']
#            for ienergy in range(len(filelist)):
#
#                __stack__[catid].AddHistogram(hist[ienergy][catid][hid].GetName(),
#                                              hist[ienergy][catid][hid],
#                                              config.hist_dict[id]['layer'])
#
#        for ikey, ival in config.legname.items():
#
#            group = []
#            for iprocess in ival['group']:
#                _hid_ = config.hist_dict[iprocess]['hid']
#                for ienergy in range(len(filelist)):
#                    group.append(hist[ienergy][catid][_hid_].GetName())
#
#            __stack__[catid].Group(ikey, group)
#            __stack__[catid].Hist(ikey).legendLine = configclass.returnLegendName(config.legname[ikey]['legname'], mass)
#            __stack__[catid].Hist(ikey).NormalizeToBinWidth()
#            __stack__[catid].Hist(ikey).Show(icategory, ikey)
#
#            if(ikey == 'observed'): __stack__[catid].Hist(ikey).stack = False
#
#    if(option==None):
#        return __stack__
#    else:
#        return __stack__[option]
#
#
#def AllTurnOff():
#    for _table_list_ in table_list:
#        for _key_, _val_ in sorted(_table_list_.items()):
#            for key, val, in sorted(_val_.items()):
#                if(key=='r'): continue
#                val['flag'] = False
#
#
#def TurnOn(nuisance_list, str):
#    for icategory, ikey in nuisance_list:
#        for _table_list_ in table_list:
#            if(_table_list_[str].has_key(ikey)==True):
#                _table_list_[str][ikey]['flag'] = True                    
#
#
#def PrintList(thres = 0.5, cond = None):
#    fmtstring = '%-20s %-40s %-30s %-15s %-15s %-10s %5s %5s'
#
#    print '------------------------------------------------'
#    print 'Shows nuisance parameters with large deviation (threshold > %s)' % thres
#    print '------------------------------------------------'
#
#    print fmtstring % ('category', 'nuisance parameter', 'affected_process', 'pull_center', 'pull_err', 'orig_unc', 'flag', 'bbb')
#    print '---------------------------------------------------------------------------------------------------------------------------'
#    
#    counter = 0
#    _name_list_ = []
#
#    for _table_list_ in table_list:
#        for _key_, _val_ in sorted(_table_list_.items()):
#            for key, val, in sorted(_val_.items()):
#                if(key=='r'): continue
#
#                if(cond != None):
#                    if(cond in _key_): pass
#                    else: continue
#            
#                scale_cent = float(val['fit_cent'])
#                scale_err = float(val['fit_err'])
#
#                if(math.fabs(scale_cent) > thres):
#                    print fmtstring % (_key_, key, val['process'], scale_cent, scale_err, val['orig_sys'], val['flag'], val['bbb'])
#                    counter = counter+1



if __name__ == '__main__':
	main()
	stop()
