#!/usr/bin/env python

import CombineHarvester.CombineTools.ch as ch
import CombineHarvester.CombinePdfs.morphing as morphing
from CombineHarvester.CombinePdfs.morphing import BuildRooMorphing
from ROOT import RooWorkspace, TFile, RooRealVar
import ROOT
import os, sys



cb = ch.CombineHarvester()

aux_shapes   = '/mnt/t3nfs01/data01/shome/ytakahas/work/Combination/CMSSW_7_4_7/src/auxiliaries/shapes/UZH/'

procs = {
  'sig'  : ['ZTT'],
  'bkg'  : ['VV','TT','QCD','W','ZJ','ZL']
}

cats = [(1, 'mt_signal')]


tess = []

for tes in range(-30,31):
    tes = 1 + tes*0.001
#    print tes, 'is added'
    
    addname = str(tes)

#    if addname=='1.0':
#        addname = '1'

    tess.append(addname)

cb.AddObservations(  ['*'], ['ztt'], ["13TeV"], ['mt'],               cats         )
cb.AddProcesses(     ['*'], ['ztt'], ["13TeV"], ['mt'], procs['bkg'], cats, False  )
#cb.AddProcesses(     [''], ['ztt'], ["13TeV"], ['mt'], procs['sig'], cats, True   )
cb.AddProcesses(     tess, ['ztt'], ["13TeV"], ['mt'], procs['sig'], cats, True   )

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




tes = RooRealVar('tes', 'tes', 0.97, 1.03);
tes.setConstant(True)

f_debug = TFile('morph_debug.root', 'RECREATE')

ws = RooWorkspace('htt', 'htt')
bins = cb.bin_set()
for bin in bins:
    for proc in procs['sig']:
        BuildRooMorphing(ws, cb, bin, proc, tes, "norm", True, True, False, f_debug)

f_debug.Close()
cb.AddWorkspace(ws, False)
cb.cp().process(procs['sig']).ExtractPdfs(cb, "htt", "$BIN_$PROCESS_morph", "")



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
writer.SetWildcardMasses([])
writer.WriteCards('output/sm_cards/LIMITS', cb)

print '>> Done!'
