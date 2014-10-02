import sys
from ROOT import gStyle, gROOT
from ROOT import TColor,kViolet, kMagenta, kOrange, kRed, kBlue, kGray, kBlack
from CMGTools.RootTools.Style import *
from CMGTools.ZJetsTutorial.plotter.rootutils import *

dirname = {
    'muTau_0jet_low' : 0,
    'muTau_0jet_high' : 1,
    'muTau_boost_low' : 2,
    'muTau_boost_high' : 3,
    'muTau_vbf' : 4
    }

channelname = {
    'mt':"muTau",
    'tm':"muTau",
    'et':"eTau",
    'te':"eTau",
    'tt':"tauTau",
    'mm':"muMu",
    'me':"eMu",
    'em':"eMu"}

phasespace = {
    '0jh':'0jet_high',
    '0jl':'0jet_low',
    'bh':'boost_high',
    'bl' : 'boost_low',
    'vbf':'vbf'
    }

energyname = ['7TeV', '8TeV']

# key : id, color_id, color, fill style

#hist_dict ={
#    'QCD' : {'hid':0, 'color':kMagenta-10, 'fill':1, 'lstyle':1, 'lcolor':1, 'layer':0},
#    'ZTT' : {'hid':1,'color': kOrange-2, 'fill':1, 'lstyle':1, 'lcolor':1, 'layer':3},
#    'ZLL' : {'hid':2,'color': kRed+2, 'fill':1, 'lstyle':1, 'lcolor':1, 'layer':1},
#    'ZL' : {'hid':3,'color': kRed+2, 'fill':1, 'lstyle':1, 'lcolor':1, 'layer':1},
#    'ZJ' : {'hid':4,'color': kRed+2, 'fill':1, 'lstyle':1, 'lcolor':1, 'layer':1},
#    'VV' : {'hid':5,'color': kRed+2, 'fill':1, 'lstyle':1, 'lcolor':1, 'layer':1},
#    'W' : {'hid':6,'color': kRed+2, 'fill':1, 'lstyle':1, 'lcolor':1, 'layer':1},
#    'TT' : {'hid':7,'color': kBlue-8, 'fill':1, 'lstyle':1, 'lcolor':1, 'layer':2},
#    'VH' : {'hid':8, 'color':kBlue, 'fill':-1, 'lstyle':2, 'lcolor':kBlue, 'layer':1001},
#    'ggH' : {'hid':9,'color': kBlue, 'fill':-1, 'lstyle':2, 'lcolor':kBlue, 'layer':1001},
#    'qqH' : {'hid':10,'color': kBlue, 'fill':-1, 'lstyle':2, 'lcolor':kBlue, 'layer':1001},
#    'data_obs' : {'hid':11, 'color':kBlack, 'fill':0, 'lstyle':1, 'lcolor':1, 'layer':2999}
#    }


hist_dict ={
    'QCD' : {'hid':0, 'color':kMagenta-10, 'fill':1, 'lstyle':1, 'lcolor':1, 'layer':0},
    'ZTT' : {'hid':1,'color': kOrange-2, 'fill':1, 'lstyle':1, 'lcolor':1, 'layer':3},
    'ZL' : {'hid':2,'color': kRed+2, 'fill':1, 'lstyle':1, 'lcolor':1, 'layer':1},
    'ZJ' : {'hid':3,'color': kRed+2, 'fill':1, 'lstyle':1, 'lcolor':1, 'layer':1},
    'VV' : {'hid':4,'color': kRed+2, 'fill':1, 'lstyle':1, 'lcolor':1, 'layer':1},
    'W' : {'hid':5,'color': kRed+2, 'fill':1, 'lstyle':1, 'lcolor':1, 'layer':1},
    'TT' : {'hid':6,'color': kBlue-8, 'fill':1, 'lstyle':1, 'lcolor':1, 'layer':2},
    'VH' : {'hid':7, 'color':kBlue, 'fill':-1, 'lstyle':2, 'lcolor':kBlue, 'layer':1001},
    'ggH' : {'hid':8,'color': kBlue, 'fill':-1, 'lstyle':2, 'lcolor':kBlue, 'layer':1001},
    'qqH' : {'hid':9,'color': kBlue, 'fill':-1, 'lstyle':2, 'lcolor':kBlue, 'layer':1001},
    'data_obs' : {'hid':10, 'color':kBlack, 'fill':0, 'lstyle':1, 'lcolor':1, 'layer':2999}
    }


legname = {'QCD' : {'legname' : 'QCD', 'hid':0, 'layer':0, 'group':['QCD']},
           'ZTT' : {'legname' : 'Z #rightarrow #tau#tau', 'hid':1, 'layer':3, 'group':['ZTT']},
#           'EWK' : {'legname' : 'electroweak', 'hid':2, 'layer':1, 'group':['ZLL','ZL','ZJ','VV','W']},
           'EWK' : {'legname' : 'electroweak', 'hid':2, 'layer':1, 'group':['ZL','ZJ','VV','W']},
           'TT' : {'legname' : 't#bar{t}', 'hid':3, 'layer':2, 'group':['TT']},
           'H' : {'legname' : 'H', 'hid':4, 'layer':1001, 'group':['VH','ggH','qqH']},
           'observed' : {'legname' : 'observed', 'hid':5, 'layer':2999, 'group':['data_obs']}}


#processid = {
#    'QCD': ['QCD',0,0],
#    'ZTT': ['ZTT',1,1],
#    'ZLL': ['EWK',2,2],
#    'ZL': ['EWK',3,2],
#    'ZJ': ['EWK',4,2],
#    'VV': ['EWK',5,2],
#    'W': ['EWK',6,2],
#    'TT': ['TT',7,3],
#    'VH': ['H',8,4],
#    'ggH': ['H',9,4],
#    'qqH': ['H',10,4]
#    }

processid = {
    'QCD': ['QCD',0,0],
    'ZTT': ['ZTT',1,1],
    'ZL': ['EWK',2,2],
    'ZJ': ['EWK',3,2],
    'VV': ['EWK',4,2],
    'W': ['EWK',5,2],
    'TT': ['TT',6,3],
    'VH': ['H',7,4],
    'ggH': ['H',8,4],
    'qqH': ['H',9,4]
    }

masspoint = [110,115,120,125,130,135,140,145]






class config:

    def __init__(self):
        print ""

    def close(self):
        sys.stderr.write('stop press "q" to quite > ')
        ans = raw_input('>' )
        if ans in ['q', 'Q']:
            sys.exit(-1)
        else:
            return -1

    def Message(sev,str):
        print '['+sev+'] : '+str


    def DecoHist(self, id, h, title):
        h.GetXaxis().SetTitle(xtitles['svfitMass'])
        h.GetYaxis().SetTitle('dN/dm_{#tau#tau} [1/GeV]')
        h.GetXaxis().SetTitleSize(0.05)
        h.GetYaxis().SetTitleSize(0.05)
        h.SetTitle(title)
        
#        h.GetYaxis().SetTitleOffset(1.3)
#        h.GetYaxis().SetTitle('# of events')
        h.SetLineWidth(2)
        h.SetLineColor(hist_dict[id]['lcolor'])
        if(id=='data_obs'):
            h.SetMarkerStyle(20)

        if(id =='data_obs' or
           id == 'VH' or id == 'ggH' or id == 'qqH'):
            h.SetFillStyle(hist_dict[id]['fill'])

        h.SetFillColor(hist_dict[id]['color'])
        h.SetLineStyle(hist_dict[id]['lstyle'])
        h.SetLineWidth(2)

    def DecoNuiColorHist(self, h, style, size, col):
        h.SetMarkerStyle(style)
        h.SetMarkerSize(size)

        if(col>=4):
            col = col+2
        h.SetMarkerColor(col)
        h.SetLineColor(col)



    def DecoNuiHist(self, h, title, max):
        h.SetTitle(title)
        h.GetXaxis().SetTitle(xtitles['svfitMass'])
        h.GetYaxis().SetTitle('Uncertainty')
        h.GetYaxis().SetTitleOffset(1.3)
        h.SetMarkerStyle(20)
        h.SetMarkerSize(1)
        h.SetMaximum(max)
        h.SetMinimum(0)


    def addList(self, list1, list2):

        list = [0 for i in range(len(list1))]
        
        if(len(list1) != len(list2)):
            print 'Not same indicies ', len(list1), len(list2)
            return list
        else:
            for i, data in enumerate(list1):
                val = list1[i] + list[i]
                list[i] = val

            return list
                

    def help(self):

        print 'Usage :'
        print ''
#        print 'AllTurnOn() : Modify all the histograms according to the fitting results'
#        print 'AllTurnOff() : Modify all the histograms not to reflect fitting results'
#        print 'TurnOn(nuisance_str) : Turn on specific histogram to reflect fitting results'
#        print 'TurnOff(nuisance_str) : Turn on specific histogram not to the fitting results'    
        print 'PrintList(thres=0.5) : Print list of nuisance parameters with abs(pull_center) > threshold'
        print '                       Return value is a list'
        print '                       eg) list = PrintList(0.5)'
        print ''
        print 'Draw(channel, category, plotname=None, nuisance_parameter=None) : Draw histogram'
        print '                       [channel] mt, et, tt, em, mm'
        print '                       [category] 0jl, 0jh, bl, bh, vbf'
        print '                       [plotname] whatever you like'
        print '                       [nuisance_parameter] input a list of nuisance parameter you would like to reflect to the histogram'
        print '                       eg) Draw(\"mt\",\"vbf\",\"plot2\",list), where list = PrintList(0.5)'
        print ''
        print 'DrawNuisance(channel, category, plotname, threshold, nuisance_parameter=None) : Draw Nuisance'
        print '                       [channel] mt, et, tt, em, mm'
        print '                       [category] 0jl, 0jh, bl, bh, vbf'
        print '                       [plotname] whatever you like'
        print '                       [nuisance_parameter] input a list of nuisance parameter you would like to reflect to the histogram'
        print '                       eg) Draw(\"mt\",\"vbf\",\"plot2\",list), where list = PrintList(0.5)'
        print '\n'

        
#        print 'PrintLargeDeviation(val) : Show a list of nuisance parameter with large deviation (threshold > val)'
#        print 'RePaint() : Re-draw the histograms with modified scales'
#        print 'Draw(channel, category, plotname=None, criteria) : Draw the histograms (mt/et/tt/em/mm), (0jh,0jl,bh,bl,vbf)'


    def returnName(self, id, mass):
        name = ''
        if(id=='VH' or id=='ggH' or id=='qqH'):
            name = id + mass
        else:
            name = id
        return name

    def returnLegendName(self, id, mass):
        name = id
        if(id=='H'):
            name = id + "(" + mass + "GeV) #rightarrow #tau#tau"
        return name

    def LegendSettings(self, leg):
        leg.SetBorderSize(0)
        leg.SetFillColor(0)
        leg.SetLineColor(0)
        leg.SetFillStyle(0)
#        leg.SetTextSize(0.05)
