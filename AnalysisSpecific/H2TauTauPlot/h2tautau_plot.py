from ROOT import TFile, gDirectory, TH1F, TLegend, gROOT, TCanvas, gStyle, Double
from optparse import OptionParser, OptionGroup
import shelve, math, copy, ConfigParser, sys

gStyle.SetOptStat(0)
gStyle.SetPadLeftMargin(0.125);
gStyle.SetPadRightMargin(0.07471264);
gStyle.SetPadTopMargin(0.08474576);
gStyle.SetPadBottomMargin(0.1165254);


fmt = '%-60s %-4s %.2f %.2f'

canvas={}
leg={}
histDict={}

def stop():
    sys.stderr.write('Press q to quit : ')
    if raw_input('') in ['q','Q']:
        return -1

def addHistError(h1, h2):
    if h1.GetNbinsX() != h2.GetNbinsX():
        print 'Inconsistent # of bin for histograms'

    for ibin in range(1, h1.GetNbinsX()+1):
        err1 = h1.GetBinContent(ibin)
        err2 = h2.GetBinContent(ibin)
        err = math.sqrt(err1*err1+err2*err2)
        h1.SetBinContent(ibin, err)
    

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
    leg.SetTextSize(0.032)
    leg.SetLineColor(0)
    leg.SetLineStyle(1)
    leg.SetLineWidth(0)
    leg.SetFillColor(0)
    leg.SetFillStyle(0)


def fitResultModule(filename):

#    print filename
    fit_result = {}

    for _line_ in open(filename):
        line = _line_.split()
        if line[0] in ['name','r']:
            continue

        if len(line)!=15:
            print 'Warning > Unexpected line : ', line
            continue
          
        parameter = line[0]
        sbfit_val = line[9].replace('!','')
        sbfit_err = line[11].replace('!','')

        fit_result[parameter] = [sbfit_val, sbfit_err]

    return fit_result



        
def readingModule(file, filename, fitResult, category, ibkg, hist):

    flag_nuisance = False
    
    process = []
    counter_process = False

#    print fitResult

    # First catch the process list
    for _line_ in open(filename):
        line = _line_.split()

        if(len(line)==0):
            continue

        if line[0] == 'bin':
            if line[1] != category:
                print 'Warning !!! Not correct txt file', line[1], category
                return -1

        if line[0] == 'process':
            if counter_process:
                process = line[1:]
            counter_process = True

    if len(process)==0:
        print 'Warning > could not catch processes'



    ListOfHistogram = {}

    # second, check each nuisances
    for _line_ in open(filename):
        line = _line_.split()

        if(len(line)==0):
            continue
        if line[0].find("#")!=-1:
            continue
            
        if line[0].find('lumi')!=-1:
            flag_nuisance = True

        if not flag_nuisance:
            continue
            
        parameter = line[0]
        etype = line[1]
        err = line[2:]

            
        if etype not in ['shape', 'lnN']:
            print 'Warning !!! Unexpected type', etype

        if len(err) != len(process):
            print 'Warning !!! Not correct nuisances', len(err), len(process)

        for iprocess in range(len(process)):
            if process[iprocess] == ibkg and err[iprocess]!='-':

                if not fitResult.has_key(parameter):
                    print 'No key : ', parameter, ibkg, etype, err[iprocess]
                    continue

                if etype=='lnN':

                    scale = 1.+Double(fitResult[parameter][0])
                    hnew = copy.deepcopy(hist)
                    hnew.Scale(scale)

                    for ibin in range(1, hnew.GetNbinsX()+1):
                        newerr = hnew.GetBinContent(ibin)*(1.-math.fabs(Double(err[iprocess])))*Double(fitResult[parameter][1])
                        print parameter, ibin,  hist.GetBinContent(ibin), scale, (Double(err[iprocess])-1.), Double(fitResult[parameter][1]), newerr
                        hnew.SetBinContent(ibin, math.fabs(newerr))
                        hnew.SetBinError(ibin, 0)


                    ListOfHistogram[parameter] = hnew, etype

                elif etype=='shape':
                    # CMS_htt_mt_muTau_vbf_tight_8TeV_W_bin_9 muTau_vbf_tight W    
                    print parameter, category, ibkg

                    if parameter.find('_bin_')!=-1:
                        pass
#                        continue

                    scale = 1.+Double(fitResult[parameter][0])
                    hnew = copy.deepcopy(hist)
                    hnew.Scale(scale)

                    hnew_up = copy.deepcopy(tFileCopy(file, category+'/'+ibkg+'_'+parameter+'Up'))
                    hnew_down = copy.deepcopy(tFileCopy(file, category+'/'+ibkg+'_'+parameter+'Down'))

                    for ibin in range(1, hnew.GetNbinsX()+1):
                        iup = hnew_up.GetBinContent(ibin)
                        idown = hnew_down.GetBinContent(ibin)

                        err_half = 0

                        if not (iup==0 and idown==0):
                            err_half = math.fabs((iup - idown)/(iup + idown))
                            
#                        print ibin, math.fabs(err_half)

#                        newerr = hist.GetBinContent(ibin)*scale*err_half*Double(fitResult[parameter][1])
                        newerr = hnew.GetBinContent(ibin)*err_half*Double(fitResult[parameter][1])
                        hnew.SetBinContent(ibin, math.fabs(newerr))
                        hnew.SetBinError(ibin, 0)
                    

                    ListOfHistogram[parameter] = hnew, etype
                    


    return ListOfHistogram



def main():

    parser = OptionParser(usage='usage: %prog [options] ARGs',
                          description='Pre-/Post-fit plots Maker')
    
    parser.add_option('-c', '--channel', dest='channel', default='mt', action='store',
                      help='channels to be considered for the plot.')
    
    parser.add_option('-a', '--analysis', dest='analysis', default='sm', action='store',
                      help='Analysis flag for SM or MSSM analysis')
    
    parser.add_option('-p', '--period', dest='period', default='7TeV 8TeV', action='store',
                      help='period used for the S/B plots. Default : 7TeV 8TeV')
    
    parser.add_option('-m', '--mass', dest='mass', default='125', action='store',
                      help='Target Higgs mass. Default : 125')
    
    parser.add_option("-b", "--batch", dest='batch', action="store_true", default=False,
                      help='Set Batch mode. Default : False')

    parser.add_option('-t', '--threshold', dest='threshold', default='0.3', action='store',
                      help='threshold for drawing.')
    
    (options, args) = parser.parse_args()
    

    if(options.batch==True):
        gROOT.SetBatch(True)
        

    init = ConfigParser.SafeConfigParser()
    if options.analysis=='sm':
        init.read('config.ini')
    else:
        init.read('config_mssm.ini')

			
    for ichn in options.channel.split():        

        # fitting result file
        ffile = 'LIMITS/hww-bg/' + ichn + '/' + options.mass + '/out/mlfit.txt'
        fitResult = fitResultModule(ffile)

        for iperiod in options.period.split():

            list_category = init.get(ichn, 'category_'+iperiod).split()
            dict_bkg = separateModule(init, ichn, 'bkg')
            dict_sig = separateModule(init, ichn, 'signal')

            filename = 'LIMITS/hww-bg/' + ichn + '/common/htt_' + str(ichn) + '.input_' + iperiod + '.root'
            file = TFile(filename)
                
            for icategory in list_category:

                categoryname = init.get(ichn, 'prefix') + '_' + icategory.split(':')[0]

                # nuisance list file
                pfile = 'LIMITS/hww-bg/' + ichn + '/' + options.mass + '/htt_' + ichn + '_' + icategory.split(':')[1] + '_' + iperiod + '.txt'

                uname = categoryname + '_' + iperiod
                
				
                print uname, '----------------------------------------------------'
                print '\t InputFile = ', filename, ', Category = ', categoryname
                print '\t ParameterFile = ', pfile
                print '\t Background = ', dict_bkg
                print '\t Signal = ', dict_sig


                h_bkg = {}
						
                for ikey, content in sorted(dict_bkg.items()):
                    for ibkg in content:

                        print '\t process = ', ibkg
                        key = uname + '_' + ikey

                        histogram = tFileCopy(file, categoryname+'/'+ibkg)
                        h_bkg[ibkg] = readingModule(file, pfile, fitResult, categoryname, ibkg, histogram)

                histDict[uname] = h_bkg

                print '------------------------------------------------------------'

#                        if h_bkg.has_key(key):
#                            for ibin in range()
#                            h_bkg[key]
#                            h_bkg[key].Add(histogram)
#                        else:
#                            h_bkg[key] = histogram
#                            h_bkg[key].SetName(ikey)
						
#                histDict[uname] = h_bkg
				

#    print histDict

    for ikey, content in sorted(histDict.items()):

#        canvas[ikey] = TCanvas(ikey, '', 600,600)
        canvas[ikey] = TCanvas(ikey)
        counter_hist = 0
        counter_all = 0

#   TLegend *leg = new TLegend(0.4295977,0.3707627,0.875,0.8792373,NULL,"brNDC");
        leg[ikey] = TLegend(0.43,0.37,0.88,0.88)
        LegendSettings(leg[ikey])

        list_max = [-100 for i in range(1000)]
        max = -100

        h_all = 0

        for iprocess, ivar in sorted(content.items()):
            for nuisance, [ibkg, itype] in sorted(ivar.items()):                

                if counter_all==0:
                    h_all = copy.deepcopy(ibkg)
                else:
                    addHistError(h_all, copy.deepcopy(ibkg))

                h_all.SetTitle(ikey)
                counter_all += 1

                for ibin in range(1,ibkg.GetNbinsX()+1):
                    if ibkg.GetBinContent(ibin) > list_max[ibin-1]:
                        list_max[ibin-1] = ibkg.GetBinContent(ibin)

        h_all.SetLineColor(1)
        h_all.SetLineWidth(2)

        h_all.GetXaxis().SetLabelSize(0.05);
        h_all.GetXaxis().SetTitleSize(0.05);
        h_all.GetYaxis().SetLabelSize(0.05);
        h_all.GetYaxis().SetTitleSize(0.05);
        
        h_all.GetXaxis().SetTitle('M_{#tau#tau} (GeV)')
        h_all.GetYaxis().SetTitle('Absolute Uncertainty')

        h_all.Draw()
        leg[ikey].AddEntry(h_all, "Total", 'lep')


        for iprocess, ivar in sorted(content.items()):
            for nuisance, [ibkg,itype] in sorted(ivar.items()):

                flag_draw = False
                
                for ibin in range(1,ibkg.GetNbinsX()+1):
                    if ibkg.GetBinContent(ibin) > list_max[ibin-1]*Double(options.threshold):
                        flag_draw = True

                print ikey, iprocess, nuisance, itype, ' => ', flag_draw

                if not flag_draw:
                    continue


                col = counter_hist+2
                if col >= 10:
                    col += 20 + counter_hist

                ibkg.SetLineColor(col)
                ibkg.SetMarkerColor(col)
                ibkg.SetLineWidth(2)
                
                lname = nuisance.replace('CMS_', '').replace('htt_','') + ' ('+itype+')'
                leg[ikey].AddEntry(ibkg, lname, 'lep')
		
#                if counter_hist==0:
 #                   ibkg.SetMaximum(max*1.3)
 #                   ibkg.Draw("h")
 #               else:
 #                   ibkg.Draw("hsame")
		
                ibkg.Draw("hsame")
                counter_hist += 1


        leg[ikey].Draw()

        canvas[ikey].Modified()
        canvas[ikey].Update()
        canvas[ikey].SaveAs(ikey+'.png')



if __name__ == '__main__':
    main()
    stop()
