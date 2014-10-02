from ROOT import TFile, gDirectory, TH1F, TLegend, TCanvas, gStyle, TPad, TLine, gROOT, TTree
import math, copy, sys
import dist_config as tool
from array import array

#gROOT.SetBatch(True)

file = TFile('Myroot.root')
#label = ['No_jet_association','Jet_association']
label = ['No_HO_association','HO_association']

col = [2,4,6]
#MAX = 50.
#MIN = 0.
MAX = 2.
MIN = 0.

_can_ = [0 for i in range(1000)]
_pad1_ = [0 for i in range(1000)]
_pad2_ = [0 for i in range(1000)]
_h_ = [0 for i in range(1000)]
_line_ = [0 for i in range(1000)]
_leg_ = [0 for i in range(1000)]


def saveall():
    for a in range(len(_can_)):
        if _can_[a]==0:
            continue


    count = 0
    
    for a in range(len(_can_)):
        if _can_[a]==0:
            continue

#        base = 'figure/fig_' + type + '_' + title + '.pdf'
        base = 'figure_HO.eps'

        if count==0:
            _str_ = base + '('
            _can_[a].SaveAs(_str_)

        else:
            _can_[a].SaveAs(base)
            
        count += 1

    __c__ = TCanvas('c_end')
    _str_ = base + ')'
    __c__.SaveAs(_str_)


def draw(canvas, pad1, pad2, hlist, ref_num, xtitle):
    _leg_.append(tool.legendFactory(0.7770178,0.8019231,0.9863201,0.9038462))
#    if(xtitle.find('eta')!=-1):
#        _leg_.append(tool.legendFactory(0.1751026,0.6057692,0.4254446,0.8865385))
#    else:
#        _leg_.append(tool.legendFactory(0.61,0.59,0.86,0.87))        

#      TLegend *leg = new TLegend(,NULL,"brNDC");
    id_leg = len(_leg_)-1
            
    tool.LegendSettings(_leg_[id_leg])
    gStyle.SetOptTitle(0)
    gStyle.SetOptStat(0)
    tool.CanvasSetting(canvas)

    pad1.Draw()
    pad1.cd()
    pad1.Range(-37.5137,-0.007315414,212.8562,0.05638885)
    tool.PadSetting(pad1)
    pad1.SetLeftMargin(0.1498331)
    pad1.SetRightMargin(0.05134869)
    pad1.SetTopMargin(0.07807864)
    pad1.SetBottomMargin(0.1398986)
    
    for ii in range(len(hlist)):
        hlist[ii].Scale(1/hlist[ii].GetSumOfWeights())

        tool.DecoHist(hlist[ii], col[ii], col[ii])
        _leg_[id_leg].AddEntry(hlist[ii], label[ii],'lp')

        
    for ii in range(len(hlist)):
        if ii==0:
            hlist[ii].SetMinimum(0)
            hlist[ii].SetMaximum(hlist[ii].GetMaximum()*1.3)
            hlist[ii].SetMinimum(0.000001)
            hlist[ii].Draw('')
        else:
            hlist[ii].Draw('same')

    _leg_[id_leg].Draw()

    pad1.Modified()
    canvas.cd()

    pad2.Draw()
    pad2.cd()
    pad2.Range(-37.32877,-6.033058,213.0137,10.82645)
    tool.PadSetting(pad2)
    pad2.SetLeftMargin(0.1477428);
    pad2.SetRightMargin(0.05335154);
    pad2.SetTopMargin(0.04901967);
    pad2.SetBottomMargin(0.3578431);

    flag = False
    for ii in range(len(hlist)):
        if ii == ref_num:
            continue
        else:
            _h_.append(tool.ratioFactory(hlist[ii], hlist[ref_num]))

            id = len(_h_)-1


            tool.DecoRatioHist(_h_[id], xtitle)
            _h_[id].GetYaxis().SetTitle(' ratio ')
            _h_[id].GetYaxis().SetTitleOffset(0.6)
            _h_[id].GetYaxis().SetTitleSize(0.12)
            _h_[id].GetYaxis().SetTitleFont(42)
            _h_[id].SetLineColor(col[ii])
            _h_[id].SetMarkerColor(col[ii])
            _h_[id].SetMaximum(MAX)
            _h_[id].SetMinimum(MIN)
            

            if flag:
                _h_[id].Draw('epsame')
            else:
                _h_[id].Draw("ep")
                flag = True

            for ibin in range(1, _h_[id].GetXaxis().GetNbins()):
                if(xtitle=='Njet'):
                    print xtitle, ibin, (1-_h_[id].GetBinContent(ibin))

    _line_.append(tool.lineFactory(hlist[ref_num].GetXaxis().GetXmin(), 1, hlist[ref_num].GetXaxis().GetXmax(), 1))
    
    id = len(_line_)-1
    _line_[id].SetLineStyle(2)
    _line_[id].SetLineColor(1)
    _line_[id].Draw()

    
    pad2.Modified()
    canvas.cd()
    canvas.Modified()



##################


h_ho_energy= [0 for k in range(len(label))]

for id, exp in enumerate(label):

    hname = 'h_jet_pt_' + label[id]
    hnew = TH1F(hname, hname, 50,0,500)
    hnew.Sumw2()

    #TH1F(hname, hname, 60,0,3000)
#    h_ho_energy[id].Sumw2()

    criteria = 'r_met'
    if id==1:
        criteria += '2'

    criteria += ' >> ' + hname
    condition = 'r_maxjfrac > 0.15'
#    condition = 'r_HO40==1 && r_maxjfrac > 0.1'
    
    file.EventAnalysis.Draw(criteria, condition);
    h_ho_energy[id] = copy.deepcopy(hnew)

ctype = ['ho_energy']
xtitletype = ['missing ET (GeV)']

for ii in range(len(ctype)):

    cname = 'can_' + ctype[ii]
    _can_[ii] = TCanvas(cname, cname, 750,700)

    pname = 'pad1_' + ctype[ii]
    p1 = TPad(pname, pname, 0.006702413,0.2136499,0.9865952,0.9851632)

    pname = 'pad2_' + ctype[ii]
    p2 = TPad(pname, pname, 0.009383378,0.01038576,0.9892761,0.3130564)

    list = []
    if ii == 0:
        list = h_ho_energy
    elif ii == 1:
        list = h_jet_energy

    draw(_can_[ii], p1, p2, list, 0, xtitletype[ii])




saveall()

