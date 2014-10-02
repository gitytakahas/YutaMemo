# 
# simple python macro to generate offset, RMS term
# starting from the histogram
# 
# 13 May 2014
# contact : Yuta Takahashi
#

import sys, ConfigParser, copy
from optparse import OptionParser, OptionGroup
from ROOT import gROOT, TFile, Double, TH1F

gROOT.SetBatch(True)

def returnRange(hist):
    
    bin = []
    
    for ibin in range(0, hist.GetNbinsX()+1):
        proj = hist.ProjectionY("ProjY_"+str(ibin), ibin, ibin+1)
#        print hist.GetName(), ibin, proj.GetEntries()
        if proj.GetEntries() > 100:
            bin.append(ibin)

    return min(bin), max(bin)


def returnVal(hist):

    # check overflow / underflow to make the fit result reliable
    # only allow if the outlier is less than 1%

    outlier = Double((hist.GetEntries() - hist.GetEffectiveEntries())/hist.GetEntries())
#    print '[INFO] outlier = ', outlier, ' effective / total = ', hist.GetEffectiveEntries(), '/', hist.GetEntries()
    
    if outlier > 0.01:
        print '[WARNING] There are more than 1% outlier : ' + outlier + '. Need to rearrange the axis'
        print '[WARNING] The fitting result might not reliable'


    fitmin, fitmax = returnRange(hist)
    hist_profile = hist.ProfileX()
    hist_profile.Fit("pol1", "", "", fitmin, fitmax)

    func = hist_profile.GetFunction("pol1");
    slope = func.GetParameter(1)
    offset = func.GetParameter(0)

    return slope, offset


def returnRMShistogram(hist, name):
    ''' retrieve 2D histogram and return 1D histogram with RMS value as a Y-axis '''
    
    hname = 'hist_RMS' + hist.GetName()
    hist_RMS = TH1F(hname, hname, 
                    hist.GetNbinsX(),
                    hist.GetXaxis().GetXmin(),
                    hist.GetXaxis().GetXmax())

    num = 0
    den = 0

    for ibin in range(0, hist.GetNbinsX()+1):
        proj = hist.ProjectionY("ProjY_"+str(ibin), ibin, ibin)
        if proj.GetEntries() > 100:
            RMS = proj.GetRMS()
            RMSerror = proj.GetRMSError()

            hist_RMS.SetBinContent(ibin, RMS)
            hist_RMS.SetBinError(ibin, RMSerror)
            
            weight = 1/(RMSerror*RMSerror)
      
            num += RMS*weight
            den += weight
      
    weighted_RMS = num/den

    hist_RMS.Fit('pol1','q')
    func = hist_RMS.GetFunction("pol1");
    
    func.SetName(name)
    func.SetTitle(name)
           
    return hist_RMS, func, weighted_RMS



def returnSimplehistogram(a, b, name):
    
    hname_dbeta  = 'dbeta_' + name
    hname_offset = 'offset_' + name

    hist_dbeta = TH1F(hname_dbeta, hname_dbeta, 100,-10,10)
    hist_offset = TH1F(hname_offset, hname_offset, 100,-10,10)
    
    hist_dbeta.Fill(a)
    hist_offset.Fill(b)
    
    return hist_dbeta, hist_offset


def returnSimpleRMShistogram(a, name):
    
    hname_wrms  = 'wrms_' + name

    hist_wrms = TH1F(hname_wrms, hname_wrms, 100,-10,10)
    hist_wrms.Fill(a)
    
    return hist_wrms


if __name__ == '__main__':

    parser = OptionParser(usage='usage: %prog [options] ARGs',
                          description='Tau isolation macro, producing relevant parameters (k-factor, offset and RMS)')
    parser.add_option('--file', dest='file', default='root/Myroot_DY.root', action='store',
                      help='specify ROOT file including the histogram')

    parser.add_option('--output', dest='output', default='IsolationParameters.root', action='store',
                      help='specify output ROOT file name')

    parser.add_option('--hist_barrel', dest='hist_barrel', default='h_neutralvscharged_DY_Timing_barrel', action='store',
                      help='specify input Histogram for neutral Pt vs pileup Pt')

    parser.add_option('--hist_endcap', dest='hist_endcap', default='h_neutralvscharged_DY_Timing_endcap', action='store',
                      help='specify input Histogram for neutral Pt vs pileup Pt')

    parser.add_option('--hist_all', dest='hist_all', default='h_neutralvscharged_DY_Timing_all', action='store',
                      help='specify input Histogram for neutral Pt vs pileup Pt')

    (options, args) = parser.parse_args()

    file = TFile(options.file)

    print '-'*80
    print 'Input ROOT file : ', options.file
    print 'Input Histogram (neutral vs PU, barrel) : ', options.hist_barrel
    print 'Input Histogram (neutral vs PU, endcap) : ', options.hist_endcap
    print 'Input Histogram (neutral vs PU) : ', options.hist_all
    print '-'*80
    print 

    #####################################
        
    hist_neutralvspu_barrel = file.Get(options.hist_barrel)
    e = returnVal(hist_neutralvspu_barrel)


    hist_RMS_barrel, func_barrel, wrms1 = returnRMShistogram(hist_neutralvspu_barrel, 'barrel_PUiso')
    hist_dbeta_barrel, hist_offset_barrel = returnSimplehistogram(e[0], e[1], 'barrel_PUiso')
    hist_wrms_barrel = returnSimpleRMShistogram(wrms1, 'barrel_PUiso')

    print ''
    print 'barrel delta beta = (Neutral iso / PU iso) = ', Double(e[0])
    print 'barrel Neutral offset term = ', e[1]
    print 'barrel weighted RMS = ', wrms1
    print 

    #####################################
        
    hist_neutralvspu_endcap = file.Get(options.hist_endcap)
    f = returnVal(hist_neutralvspu_endcap)


    hist_RMS_endcap, func_endcap, wrms2 = returnRMShistogram(hist_neutralvspu_endcap, 'endcap_PUiso')
    hist_dbeta_endcap, hist_offset_endcap = returnSimplehistogram(f[0], f[1], 'endcap_PUiso')        
    hist_wrms_endcap = returnSimpleRMShistogram(wrms2, 'endcap_PUiso')

    print ''
    print 'endcap delta beta = (Neutral iso / PU iso) = ', Double(f[0])
    print 'endcap Neutral offset term = ', f[1]
    print 'endcap weighted RMS = ', wrms2
    print 


    #####################################
        
    hist_neutralvspu_all = file.Get(options.hist_all)
    g = returnVal(hist_neutralvspu_all)

    hist_RMS_all, func_all, wrms3 = returnRMShistogram(hist_neutralvspu_all, 'all_PUiso')
    hist_dbeta_all, hist_offset_all = returnSimplehistogram(g[0], g[1], 'all_PUiso')
    hist_wrms_all = returnSimpleRMShistogram(wrms3, 'all_PUiso')

    print ''
    print 'all delta beta = (Neutral iso / PU iso) = ', Double(g[0])
    print 'all Neutral offset term = ', g[1]
    print 'all weighted RMS = ', wrms3
    print 


    print
    print 'sum', ('%.3f' % e[0]), '&', ('%.3f' % f[0]), '&', ('%.3f' % g[0]), '&', ('%.3f' % e[1]), '&', ('%.3f' % f[1]), '&', ('%.3f' % g[1]), '&', ('%.3f' % wrms1), '&', ('%.3f' % wrms2), '&', ('%.3f' % wrms3), '\\\\'
    print 

    ofile = TFile(options.output,'recreate')

    hist_RMS_barrel.Write()
    hist_RMS_endcap.Write()
    hist_RMS_all.Write()

    func_barrel.Write()
    func_endcap.Write()
    func_all.Write()

    hist_dbeta_barrel.Write()
    hist_dbeta_endcap.Write()
    hist_dbeta_all.Write()

    hist_offset_barrel.Write()
    hist_offset_endcap.Write()
    hist_offset_all.Write()

    hist_wrms_barrel.Write()
    hist_wrms_endcap.Write()
    hist_wrms_all.Write()

    ofile.Write()
    ofile.Close()
