
import ROOT, os, numpy, copy
from officialStyle import officialStyle
from ROOT import TH2F, Double, TGraph, TH1F, gROOT, gStyle, TFile, TCanvas

gROOT.SetBatch(True)
officialStyle(gStyle)
gStyle.SetOptTitle(1)
gStyle.SetPadLeftMargin(0.18)
gStyle.SetPadBottomMargin(0.15)

directory = 'sample_20140513'
process='DY'
#process='VBF'

samples = []
esamples = []
if process=='VBF':
    samples = ['VBF_Timing125']
    esamples = ['VBF_Standard125']
elif process=='DY':
    samples = ['DY_Timing']
    esamples = ['DY_Standard']
else:
    print 'process is wrong !'

setupsROC = {
    'tau':{
    'tree':'TauTreeProducer/TauTreeProducer_tree_mod.root',
    'treename':'TauTreeProducer',
    }
}


selections = {}
selections['tau'] = {
    'signal':'abs(parton_pdgId)==15 && tau_decayModeFinding==1',
    'background':'abs(parton_pdgId)<=5 && tau_decayModeFinding==1',
}



def rocCurve(hS, hB):
  ''' Create a ROC TGraph from two input histograms.
  '''
  maxBin = hS.GetNbinsX()

  if hS.Integral() == 0.:
    print 'ROC curve creator, hist', hS.GetName(), 'has zero entries'
    return

  effsS = [hS.Integral(0, nBin)/hS.Integral(0, maxBin+1) for nBin in range(0, maxBin + 1) ]
  rejB = [1. - hB.Integral(0, nBin)/hB.Integral(0, maxBin+1) for nBin in range(0, maxBin + 1) ]
#  rejB = [hB.Integral(0, nBin)/hB.Integral(0, maxBin+1) for nBin in range(0, maxBin + 1) ]

  rocCurve = TGraph(maxBin, numpy.asarray(effsS), numpy.asarray(rejB))

  bkgeff40 = 1.-rocCurve.Eval(0.4)
  bkgeff60 = 1.-rocCurve.Eval(0.6)
  bkgeff80 = 1.-rocCurve.Eval(0.8)



  return bkgeff40, bkgeff60, bkgeff80



if __name__ == '__main__':

    setup = 'tau'
    setupDict = setupsROC[setup]
    tfileNames = []
    for sample in samples:
        tfileNames.append('{dir}/{sample}/{treeLoc}'.format(dir=directory, sample=sample, treeLoc=setupDict['tree']))

    tfiles = [TFile(tfileName) for tfileName in tfileNames]    
    trees = [tfile.Get(setupDict['treename']) for tfile in tfiles]


    efileNames = []
    for sample in esamples:
        efileNames.append('{dir}/{sample}/{treeLoc}'.format(dir=directory, sample=sample, treeLoc='TauTreeProducer/TauTreeProducer_tree.root'))

    efiles = [TFile(efileName) for efileName in efileNames]    
    etrees = [efile.Get(setupDict['treename']) for efile in efiles]

    

    ################################################################################
    print 'calculating old isolation definition before ecal timing cut'
    
    h_old_noecal = [i for i in range(3)]

    h_old_noecal[0] = TH1F('h_old_noecal_40','',100,0,1)
    h_old_noecal[1] = TH1F('h_old_noecal_60','',100,0,1)
    h_old_noecal[2] = TH1F('h_old_noecal_80','',100,0,1)


    for iTree, tree in enumerate(etrees):

        var = '(tau_iso_chargedPt + TMath::Max(0., tau_iso_neutralPt - 0.4576*tau_iso_sumPUPt))'
        histS = TH1F('h_old_noecal_S_'+str(iTree), '', 200,0,100)
        tree.Project(histS.GetName(), var, selections[setup]['signal'])
            
        histB= TH1F('h_old_noecal_B_'+str(iTree), '', 200,0,100)
        tree.Project(histB.GetName(), var, selections[setup]['background'])
            
        bkg40, bkg60, bkg80 = rocCurve(histS, histB)

        h_old_noecal[0].Fill(bkg40)
        h_old_noecal[1].Fill(bkg60)
        h_old_noecal[2].Fill(bkg80)

        print bkg40, bkg60, bkg80



    print 'calculating old isolation definition'
    
    h_old = [i for i in range(3)]

    h_old[0] = TH1F('h_old_40','',100,0,1)
    h_old[1] = TH1F('h_old_60','',100,0,1)
    h_old[2] = TH1F('h_old_80','',100,0,1)


    for iTree, tree in enumerate(trees):


        var = '(tau_iso_chargedPt + TMath::Max(0., tau_iso_neutralPt - 0.4576*tau_iso_sumPUPt))'
        histS = TH1F('h_old_S_'+str(iTree), '', 200,0,100)
        tree.Project(histS.GetName(), var, selections[setup]['signal'])
            
        histB= TH1F('h_old_B_'+str(iTree), '', 200,0,100)
        tree.Project(histB.GetName(), var, selections[setup]['background'])
            
        bkg40, bkg60, bkg80 = rocCurve(histS, histB)

        h_old[0].Fill(bkg40)
        h_old[1].Fill(bkg60)
        h_old[2].Fill(bkg80)

        print bkg40, bkg60, bkg80

    ################################################################################

    print 'calculating puweight isolation definition'    

    pulabel = ['Weight1', 'Weight1NQ', 'Weight2', 'Weight2NQ']
    h_puweight = [[i for i in range(3)] for j in range(len(pulabel))]
    

    for ilabel, label in enumerate(pulabel):
        for iTree, tree in enumerate(trees):

            h_puweight[ilabel][0] = TH1F('h_puweight_' + label + '_40','',100,0,1)
            h_puweight[ilabel][1] = TH1F('h_puweight_' + label + '_60','',100,0,1)
            h_puweight[ilabel][2] = TH1F('h_puweight_' + label + '_80','',100,0,1)

            var = '(tau_iso_chargedPt + tau_iso_neutralPt' + pulabel[ilabel] + ')'

            histS = TH1F('h_puweight_S_'+str(iTree) + '_' + label, '', 200,0,100)
            tree.Project(histS.GetName(), var, selections[setup]['signal'])
            
            histB= TH1F('h_puweight_B_'+str(iTree) + '_' + label, '', 200,0,100)
            tree.Project(histB.GetName(), var, selections[setup]['background'])
            
            bkg40, bkg60, bkg80 = rocCurve(histS, histB)
            
            h_puweight[ilabel][0].Fill(bkg40);
            h_puweight[ilabel][1].Fill(bkg60);
            h_puweight[ilabel][2].Fill(bkg80);


            print label, bkg40, bkg60, bkg80


    ################################################################################

    print 'scanning db corrected isolation'

    # k = 0 - 2
    Nbin_k = 30
    k_min = -15.
    k_max = 15.

    h_rejmap_db = [i for i in range(3)]

    for iTree, tree in enumerate(trees):

        h_rejmap_db[0] = TH1F('h_rejmap_db_40','',Nbin_k, k_min, k_max)
        h_rejmap_db[1] = TH1F('h_rejmap_db_60','',Nbin_k, k_min, k_max)
        h_rejmap_db[2] = TH1F('h_rejmap_db_80','',Nbin_k, k_min, k_max)

        for ibin in range(Nbin_k):
            
            dk = k_min + Double(ibin*(k_max - k_min)/Nbin_k)

            var = '(tau_iso_chargedPt + TMath::Max(0., tau_iso_neutralPt - tau_iso_cmb_dbeta*tau_iso_sumPUPt - tau_iso_cmb_offset + ' + str(dk) + '*tau_iso_cmb_wrms))'
            histS = TH1F('h_rejmap_db_S_'+str(iTree) + '_' + str(ibin), '', 200,0,100)
            tree.Project(histS.GetName(), var, selections[setup]['signal'])
            
            histB= TH1F('h_rejmap_db_B_'+str(iTree) + '' + str(ibin), '', 200,0,100)
            tree.Project(histB.GetName(), var, selections[setup]['background'])

            bkg40, bkg60, bkg80 = rocCurve(histS, histB)

            h_rejmap_db[0].SetBinContent(ibin+1, bkg40)
            h_rejmap_db[1].SetBinContent(ibin+1, bkg60)
            h_rejmap_db[2].SetBinContent(ibin+1, bkg80)

        
        print 'best_bkg_eff @ 40', h_rejmap_db[0].GetMinimum(), 'k = ', k_min + (h_rejmap_db[0].GetMinimumBin()-1)*(k_max - k_min)/Nbin_k
        print 'best_bkg_eff @ 60', h_rejmap_db[1].GetMinimum(), 'k = ', k_min + (h_rejmap_db[1].GetMinimumBin()-1)*(k_max - k_min)/Nbin_k
        print 'best_bkg_eff @ 80', h_rejmap_db[2].GetMinimum(), 'k = ', k_min + (h_rejmap_db[2].GetMinimumBin()-1)*(k_max - k_min)/Nbin_k



    h_rejmap_weight = [[i for i in range(3)] for j in range(len(pulabel))]        

    for ilabel, label in enumerate(pulabel):
        for iTree, tree in enumerate(trees):


            h_rejmap_weight[ilabel][0] = TH1F('h_rejmap_weight_' + label + '_40','',Nbin_k, k_min, k_max)
            h_rejmap_weight[ilabel][1] = TH1F('h_rejmap_weight_' + label + '_60','',Nbin_k, k_min, k_max)
            h_rejmap_weight[ilabel][2] = TH1F('h_rejmap_weight_' + label + '_80','',Nbin_k, k_min, k_max)

            for ibin in range(Nbin_k):
            
                dk = k_min + Double(ibin*(k_max - k_min)/Nbin_k)

                var = '(tau_iso_chargedPt + TMath::Max(0., tau_iso_neutralPt' + label + ' - tau_iso_cmb_offset' + label + '+' + str(dk) + '*tau_iso_cmb_wrms' + label + '))'
                histS = TH1F('h_rejmap_weight_S_'+str(iTree) + '_' + str(ibin) + '_' + label, '', 200,0,100)
                tree.Project(histS.GetName(), var, selections[setup]['signal'])
                
                histB= TH1F('h_rejmap_weight_B_'+str(iTree) + '' + str(ibin) + '_' + label, '', 200,0,100)
                tree.Project(histB.GetName(), var, selections[setup]['background'])
                
                bkg40, bkg60, bkg80 = rocCurve(histS, histB)
                
                h_rejmap_weight[ilabel][0].SetBinContent(ibin+1, bkg40), 'k = ', k_min + (h_rejmap_weight[ilabel][0].GetMinimumBin()-1)*(k_max - k_min)/Nbin_k
                h_rejmap_weight[ilabel][1].SetBinContent(ibin+1, bkg60), 'k = ', k_min + (h_rejmap_weight[ilabel][1].GetMinimumBin()-1)*(k_max - k_min)/Nbin_k
                h_rejmap_weight[ilabel][2].SetBinContent(ibin+1, bkg80), 'k = ', k_min + (h_rejmap_weight[ilabel][2].GetMinimumBin()-1)*(k_max - k_min)/Nbin_k


            print 'best_bkg_eff @ 40', label, h_rejmap_weight[ilabel][0].GetMinimum(), 'k = ', k_min + (h_rejmap_weight[ilabel][0].GetMinimumBin()-1)*(k_max - k_min)/Nbin_k
            print 'best_bkg_eff @ 60', label, h_rejmap_weight[ilabel][1].GetMinimum(), 'k = ', k_min + (h_rejmap_weight[ilabel][1].GetMinimumBin()-1)*(k_max - k_min)/Nbin_k
            print 'best_bkg_eff @ 80', label, h_rejmap_weight[ilabel][2].GetMinimum(), 'k = ', k_min + (h_rejmap_weight[ilabel][2].GetMinimumBin()-1)*(k_max - k_min)/Nbin_k




    file = TFile('RejectionMap_combine.root','recreate')

    for ieff in range(3):
        h_old_noecal[ieff].Write()
        h_old[ieff].Write()
        TGraph(h_rejmap_db[ieff]).Write()
        for ilabel, label in enumerate(pulabel):
            h_puweight[ilabel][ieff].Write()
            TGraph(h_rejmap_weight[ilabel][ieff]).Write()

    file.Write()
    file.Close()
