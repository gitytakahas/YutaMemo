from ROOT import TLine, TLegend, TCanvas, TH1F, TLatex, gStyle, gROOT
import copy, subprocess, shelve


def returnFile(type, process):

    filelist = []
    flabel = []
    
    if type is 'ptsqmin':
        
        if process=='qqH':
            filelist=['~/work/data/qqH_nominal_cms/all.root',
                      '~/work/data/qqH_ptsqmin5/all.root',
                      '~/work/data/qqH_ptsqmin15/all.root',
                      '~/work/data/qqH_ptsqmin30/all.root',]
            
            flabel=['ptsqmin1','ptsqmin5','ptsqmin15','ptsqmin30']
            
        elif process is 'ggH':
            filelist=['~/work/data/ggH_nominal_cms/Myroot.root',
                      '~/work/data/ggH_ptsqmin0.5/Myroot.root',
                      '~/work/data/ggH_ptsqmin5/Myroot.root',
                      '~/work/data/ggH_ptsqmin15/Myroot.root',
                      '~/work/data/ggH_ptsqmin30/Myroot.root']
            
            
            flabel=['ptsqmin1','ptsqmin0.5','ptsqmin5','ptsqmin15','ptsqmin30']

    elif type is 'scale':

        if process=='qqH':
            filelist=['~/work/data/qqH_nominal_cms/all.root',
                      '~/work/data/qqH_rf_22/all.root',
                      '~/work/data/qqH_rf_HH/all.root',
                      '~/work/data/qqH_rf_1H/all.root',
                      '~/work/data/qqH_rf_H1/all.root',
                      '~/work/data/qqH_rf_12/all.root',
                      '~/work/data/qqH_rf_21/all.root',]
            
        else:
            filelist=['~/work/data/ggH_nominal_cms/Myroot.root',
                      '~/work/data/ggH_rf_22/Myroot.root',
                      '~/work/data/ggH_rf_HH/Myroot.root',
                      '~/work/data/ggH_rf_1H/Myroot.root',
                      '~/work/data/ggH_rf_H1/Myroot.root',
                      '~/work/data/ggH_rf_12/Myroot.root',
                      '~/work/data/ggH_rf_21/Myroot.root',
                      ]

        flabel=['scale_11','scale_22','scale_HH','scale_1H','scale_H1','scale_12','scale_21']

    elif type is 'shower':
        
        if process=='qqH':
            filelist=['~/work/data/qqH_nominal_atlas/all.root',
                      '~/work/data/qqH_nominal_cms/all.root']
            
        elif process=='ggH':
            filelist=['~/work/data/ggH_nominal_atlas/Myroot.root',
                      '~/work/data/ggH_nominal_cms/Myroot.root']
            
        flabel=['ATLAS','CMS']

    elif type is 'pdf_study':
        
        if process=='qqH':
            filelist=['~/work/data/qqH_nominal_cms/all.root']

        elif process=='ggH':
            filelist=['~/work/data/ggH_nominal_cms/Myroot.root']

        flabel=['CMS']

    elif type is 'MC_comparison':

        if process=='ggH':
            filelist=['~/work/data/ggH_nominal_cms/Myroot.root',
                      '~/work/data/125_ggH_minlo/Myroot.root']
            #                  '~/higgs2tautau/CMSSW_5_3_9/src/CMGTools/GenStudies/pyana/ggH/ggH_madgraph/madgraph/madgraph.root']

            #        flabel=['powheg','minlo','madgraph']
            flabel=['powheg','minlo']
        else:
            print 'Not available for qqH'

    else:
        print '!!! Invalid option found !!!', type, process

    return filelist, flabel



def setenv():

    gStyle.SetPalette(1);
    gROOT.SetStyle("Plain");
    gStyle.SetOptStat(0);
    gStyle.SetOptTitle(0);
    gStyle.SetPadBottomMargin(0.13);
    gStyle.SetPadTopMargin(0.1);
    gStyle.SetPadRightMargin(0.10);
    gStyle.SetPadLeftMargin(0.15);# //0.15 was default
    gStyle.SetPadTickX(1);
    gStyle.SetPadTickY(1);
    gStyle.SetPadColor(0);
    gStyle.SetFrameBorderMode(0);
    gStyle.SetFrameFillColor(0);
    gStyle.SetPadColor(0);
    gStyle.SetCanvasColor(0);
    gStyle.SetCanvasBorderMode(0);
    gStyle.SetPadBorderMode(1);
    gStyle.SetTitleBorderSize(1);
    gStyle.SetTitleFillColor(0);
    gStyle.SetTitleY(0.99);
    gStyle.SetTitleH(0.08);
    gStyle.SetTitleW(0.75);
    gStyle.SetTitleX(0.15);
    font=42;# // Helvetica
    tsize=0.05;
    gStyle.SetTextFont(font);
    gStyle.SetTextSize(tsize);
    gStyle.SetLabelFont(font,"x");
    gStyle.SetTitleFont(font,"x");
    gStyle.SetLabelFont(font,"y");
    gStyle.SetTitleFont(font,"y");
    gStyle.SetLabelFont(font,"z");
    gStyle.SetTitleFont(font,"z");
    gStyle.SetLabelSize(tsize,"x");
    gStyle.SetTitleSize(tsize,"x");
    gStyle.SetLabelSize(tsize,"y");
    gStyle.SetTitleSize(tsize,"y");
    gStyle.SetLabelSize(tsize,"z");
    gStyle.SetTitleSize(tsize,"z");



def returnDict(mass, process, sys):
    table = 0

    dictname = 'result_' + str(mass) + '/sys_' + process + '_' + sys + '.shelve'
    dict = shelve.open(dictname)
    table = dict['dict']
    dict.close()

    if table==0:
        print 'No dictionary found'

    return table


def returnchannelname(channel):

    _chan_ = ''

    if(channel=='eemm'):
        _chan_ = channel.replace('eemm','$ee, \\mu\\mu$')
    elif(channel=='tautau'):
        _chan_ = channel.replace('tautau','$\\tau\\tau$')
    elif(channel=='emu'):
        _chan_ = channel.replace('emu','e$\\mu$')
    elif(channel=='etau'):
        _chan_ = channel.replace('etau','e$\\tau$')
    elif(channel=='mutau'):
        _chan_ = channel.replace('mutau','$\\mu\\tau$')

    return _chan_



def returnlabel(channel):
    
    _chan_ = ''
    
    if(channel=='eemm'):
        _chan_ = channel.replace('eemm','ee, #mu#mu')
    elif(channel=='tautau'):
        _chan_ = channel.replace('tautau','#tau#tau')
    elif(channel=='emu'):
        _chan_ = channel.replace('emu','e#mu')
    elif(channel=='etau'):
        _chan_ = channel.replace('etau','e#tau')
    elif(channel=='mutau'):
        _chan_ = channel.replace('mutau','#mu#tau')

    return _chan_


def returnChannel(decay):
    if decay in [0]:
        return 0
    elif decay in [1,2]:
        return 1
    elif decay in [3,4]:
        return 2
    elif decay in [5,7]:
        return 3
    elif decay in [6,8]:
        return 4
    else:
        print 'Invalid decaymode'
        return -1
    
def ratioFactory(h1,h2):
    _h_ = copy.deepcopy(h1)
#    _h_.Sumw2()
    _h_.Divide(h2)

    return _h_


def legendFactory(x1,y1,x2,y2):

    _leg_ = TLegend(x1,y1,x2,y2)

    return _leg_

def texFactory(x,y,name):

    _tex_ = TLatex(x, y, name)

    return _tex_

def frameFactory(hname, xmax, ymax):

    _frame_ = TH1F(hname, hname, xmax,0,xmax)

    return _frame_

def lineFactory(x_min, y_min, x_max, y_max):

    _line_ = TLine(x_min, y_min, x_max, y_max)
    return _line_

def returnfname(title, base):
    fname = 'figure_' + title + '/' + base + '.gif'
    return fname


def directory(title):
    dname = 'figure_' + title
    cmd = 'mkdir '+dname+' 2>/dev/null'
    subprocess.call(cmd, shell=True)
    

def DecoHist(hist, lcolor, mcolor):
    hist.SetLineWidth(2)
    hist.SetLineColor(lcolor)
    hist.SetMarkerColor(mcolor)
#    hist.GetXaxis().SetTitle(xtitle)
    hist.SetFillColor(2)
    hist.SetFillStyle(0)
    hist.SetLineStyle(0)
    hist.SetLineWidth(2)
    hist.SetMarkerStyle(20)
    hist.SetMarkerSize(1.)
    hist.GetYaxis().SetTitle("Normalized")
    hist.GetXaxis().SetNdivisions(505)
    hist.GetXaxis().SetLabelFont(42)
    hist.GetXaxis().SetLabelSize(0.05)
    hist.GetXaxis().SetTitleSize(0.055)
    hist.GetXaxis().SetTitleOffset(1.2)
    hist.GetXaxis().SetTitleFont(42)
    hist.GetYaxis().SetLabelFont(42)
    hist.GetYaxis().SetLabelOffset(0.01)
    hist.GetYaxis().SetLabelSize(0.05)
    hist.GetYaxis().SetTitleSize(0.055)
    hist.GetYaxis().SetTitleOffset(1.4)
    hist.GetYaxis().SetTitleFont(42)

def CanvasSetting(canvas):
    canvas.SetHighLightColor(2)
    canvas.Range(0,0,1,1)
    canvas.SetFillColor(0)
    canvas.SetBorderMode(0)
    canvas.SetBorderSize(10)
    canvas.SetTickx(1)
    canvas.SetTicky(1)
    canvas.SetLeftMargin(0.15)
    canvas.SetRightMargin(0.05)
    canvas.SetTopMargin(0.08)
    canvas.SetBottomMargin(0.13)
    canvas.SetFrameFillStyle(0)
    canvas.SetFrameLineStyle(0)
    canvas.SetFrameLineWidth(2)
    canvas.SetFrameBorderMode(0)
    canvas.SetFrameBorderSize(10)
    
def PadSetting(pad):
    pad.SetFillColor(0)
    pad.SetBorderMode(0)
    pad.SetBorderSize(10)
    pad.SetTickx(1)
    pad.SetTicky(1)
    pad.SetFrameFillStyle(0)
    pad.SetFrameLineStyle(0)
    pad.SetFrameLineWidth(2)
    pad.SetFrameBorderMode(0)
    pad.SetFrameBorderSize(10)
    pad.SetFrameFillStyle(0)
    pad.SetFrameLineStyle(0)
    pad.SetFrameLineWidth(2)
    pad.SetFrameBorderMode(0)
    pad.SetFrameBorderSize(10)


def DecoRatioHist(hist, xtitle):
#    hist.SetMinimum(0.9)
#    hist.SetMaximum(1.1)
    hist.SetFillColor(2)
    hist.SetFillStyle(0)
    hist.SetLineStyle(0)
    hist.SetLineColor(1)
    hist.SetMarkerColor(1)
    hist.SetLineWidth(2)
    hist.SetMarkerStyle(20)
    hist.SetMarkerSize(1.)
    hist.GetXaxis().SetTitle(xtitle)
    hist.GetXaxis().SetNdivisions(505)
    hist.GetXaxis().SetLabelFont(42)
    hist.GetXaxis().SetLabelSize(0.12)
    hist.GetXaxis().SetTitleSize(0.14)
    hist.GetXaxis().SetTitleOffset(1.23)
    hist.GetXaxis().SetTitleFont(42)
    hist.GetYaxis().SetNdivisions(503)
    hist.GetYaxis().SetLabelFont(42)
    hist.GetYaxis().SetLabelOffset(0.01)
    hist.GetYaxis().SetLabelSize(0.13)
    hist.GetYaxis().SetTitleSize(0.07)
    hist.GetYaxis().SetTitleOffset(1.6)
    hist.GetYaxis().SetTitleFont(42)


def LegendSettings(leg):
    leg.SetBorderSize(0)
    leg.SetFillColor(0)
    leg.SetLineColor(0)
    leg.SetFillStyle(0)
    leg.SetTextSize(0.04)
    leg.SetTextFont(42)
