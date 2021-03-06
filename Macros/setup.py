#!/usr/bin/env python

import CombineHarvester.CombineTools.ch as ch
import CombineHarvester.CombinePdfs.morphing as morphing
import ROOT
import os



cb = ch.CombineHarvester()

aux_shapes   = '/mnt/t3nfs01/data01/shome/ytakahas/work/Combination/CMSSW_7_4_7/src/auxiliaries/shapes/UZH/'

procs = {
  'sig'  : ['ZTT'],
  'bkg'  : ['VV','TT','QCD','W','ZJ','ZL']
}

cats = [(1, 'mt_signal')]

cb.AddObservations(  ['*'], ['ztt'], ["13TeV"], ['mt'],               cats         )
cb.AddProcesses(     ['*'], ['ztt'], ["13TeV"], ['mt'], procs['bkg'], cats, False  )
cb.AddProcesses(     [''], ['ztt'], ["13TeV"], ['mt'], procs['sig'], cats, True   )

print '>> Adding systematic uncertainties...'

cb.cp().process(procs['sig'] + ['ZJ', 'ZL', 'TT', 'VV']).AddSyst(
    cb, 'CMS_eff_m', 'lnN', ch.SystMap()(1.02))

cb.cp().process(procs['sig'] + ['ZJ', 'ZL', 'TT', 'VV']).AddSyst(
    cb, 'CMS_lumi', 'lnN', ch.SystMap()(1.062))

cb.cp().AddSyst(
    cb, 'CMS_eff_t', 'lnN', ch.SystMap('channel', 'process')
    (['mt'], procs['sig'] + ['TT'], 1.1))

cb.cp().process(['QCD']).AddSyst(
    cb, 'CMS_$ANALYSIS_qcdSyst_$CHANNEL_$ERA', 'lnN', ch.SystMap('channel')
        (['mt'],      1.2))  # From Tyler's studies

cb.cp().process(['TT']).AddSyst(
    cb, 'CMS_$ANALYSIS_ttjXsec_$ERA', 'lnN', ch.SystMap('channel')
        (['mt'],  1.1))

cb.cp().process(['VV']).AddSyst(
    cb, 'CMS_$ANALYSIS_vvXsec_$ERA', 'lnN', ch.SystMap('channel')
        (['mt'],  1.1))

cb.cp().process(procs['sig'] + ['ZJ', 'ZJ']).AddSyst(
    cb, 'CMS_$ANALYSIS_zjXsec_$ERA', 'lnN', ch.SystMap('channel')
        (['mt'],  1.1))

cb.cp().process(procs['sig']).AddSyst(
    cb, 'CMS_$ANALYSIS_pdf_scale_$ERA', 'lnN', ch.SystMap('channel')
        (['mt'],  1.015))

cb.cp().process(procs['sig']).AddSyst(
    cb, 'CMS_$ANALYSIS_qcd_scale_$ERA', 'lnN', ch.SystMap('channel')
        (['mt'],  1.005))

cb.cp().process(['ZL']).AddSyst(
    cb, 'CMS_$ANALYSIS_rate_mFakeTau_$ERA', 'lnN', ch.SystMap('channel')
        (['mt'],  2.0))

cb.cp().process(['ZJ']).AddSyst(
    cb, 'CMS_$ANALYSIS_zjFakeTau_$ERA', 'lnN', ch.SystMap('channel')
        (['mt'],  1.30))


print '>> Extracting histograms from input root files...'
file = aux_shapes + 'datacard.root'
#file = aux_shapes + 'datacard_combine_1p.root'

cb.cp().backgrounds().ExtractShapes(
    file, '$BIN/$PROCESS', '$BIN/$PROCESS_$SYSTEMATIC')

cb.cp().signals().ExtractShapes(
    file, '$BIN/$PROCESS$MASS', '$BIN/$PROCESS$MASS_$SYSTEMATIC')



#w = ROOT.RooWorkspace('morph', 'morph')
#tes = ROOT.RooRealVar("tes","", 1.0, 0.97, 1.03)
#morphing.BuildRooMorphing(w, cb, 'mt_signal', 'ZTT', tes, 'norm', True, True)


print '>> Generating bbb uncertainties...'
bbb = ch.BinByBinFactory()
bbb.SetAddThreshold(0.0)
#.SetFixNorm(False)
bbb.AddBinByBin(cb.cp().process(procs['sig'] + ['W', 'QCD', 'ZJ', 'ZL']), cb)
#bbb.MergeBinErrors(cb.cp().process(procs['sig'] + ['W', 'QCD', 'ZJ', 'ZL']))
#bbb.SetMergeThreshold(0.0)

print '>> Setting standardised bin names...'
ch.SetStandardBinNames(cb)
cb.PrintAll()

writer = ch.CardWriter('$TAG/$ANALYSIS_$CHANNEL_$BINID_$ERA.txt',
                       '$TAG/common/$ANALYSIS_$CHANNEL.input.root')
writer.SetVerbosity(1)
writer.WriteCards('output/sm_cards/LIMITS', cb)

print '>> Done!'
