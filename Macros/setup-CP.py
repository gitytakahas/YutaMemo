#!/usr/bin/env python

import CombineHarvester.CombineTools.ch as ch
import os

cb = ch.CombineHarvester()

auxiliaries  = os.environ['CMSSW_BASE'] + '/src/auxiliaries/'
aux_shapes   = auxiliaries +'shapes/'

procs = {
  'sig'  : ['ggH', 'qqH', 'VH'],
  'sim'  : ['VV','TT', 'ZTT','ZJ','ZL'],
  'bkg'  : ['QCD','TT','VV','W','ZTT','ZJ','ZL']
}

cats = [(1, 'muTau_inclusive')]

masses = ['125']

cb.AddObservations(   ['*'], ['htt'], ["8TeV"], ['mt'],               cats         )
cb.AddProcesses(      ['*'], ['htt'], ["8TeV"], ['mt'], procs['bkg'], cats, False  )
cb.AddProcesses(     masses, ['htt'], ["8TeV"], ['mt'], procs['sig'], cats, True   )

print '>> Adding systematic uncertainties...'

cb.cp().process(procs['sig']).AddSyst(
    cb, 'lumi_$ERA', 'lnN', ch.SystMap()(1.026))

cb.cp().process(['ggH']).AddSyst(cb, 'QCDscale_ggH2in', 'lnN', ch.SystMap()(0.772))
cb.cp().process(['qqH']).AddSyst(cb, 'QCDscale_qqH', 'lnN', ch.SystMap()(1.018))
cb.cp().process(['VH']).AddSyst(cb, 'QCDscale_VH', 'lnN', ch.SystMap()(1.04))

cb.cp().AddSyst(
    cb, 'pdf_qqbar', 'lnN', ch.SystMap('process')
      (['qqH'], 1.036)(['VH'], 1.04))

cb.cp().AddSyst(
    cb, 'pdf_gg', 'lnN', ch.SystMap('process')
      (['ggH'], 1.097))

cb.cp().AddSyst(
    cb, 'UEPS', 'lnN', ch.SystMap('process')
      (['qqH', 'VH'], 0.988))

cb.cp().process(['ggH']).AddSyst(cb, 'UEPS', 'lnN', ch.SystMap()(0.893))


cb.cp().process(procs['sig'] + procs['sim']).AddSyst(
    cb, 'CMS_eff_m', 'lnN', ch.SystMap()(1.02))


cb.cp().AddSyst(
    cb, 'CMS_eff_t_mutau_$ERA', 'lnN', ch.SystMap('process')
      (procs['sig'],           1.08)
      (['ZTT', 'TT', 'VV'],  1.08))

cb.cp().AddSyst(
    cb, 'CMS_eff_t_mutau_medium_$ERA', 'lnN', ch.SystMap('process')
      (procs['sig'],           1.01)
      (['ZTT', 'TT', 'VV'],  1.01))

cb.cp().AddSyst(
    cb, 'CMS_eff_t_mutau_medium_high_$ERA', 'lnN', ch.SystMap('process')
      (procs['sig'],           1.012)
      (['ZTT', 'TT', 'VV'],  1.012))

cb.cp().process(['ggH']).AddSyst(cb, 'CMS_scale_j_8TeV', 'lnN', ch.SystMap()(1.1))
cb.cp().process(['qqH']).AddSyst(cb, 'CMS_scale_j_8TeV', 'lnN', ch.SystMap()(1.04))
cb.cp().process(['VH']).AddSyst(cb, 'CMS_scale_j_8TeV', 'lnN', ch.SystMap()(1.15))
cb.cp().process(['ZL']).AddSyst(cb, 'CMS_scale_j_8TeV', 'lnN', ch.SystMap()(1.05))
cb.cp().process(['ZJ']).AddSyst(cb, 'CMS_scale_j_8TeV', 'lnN', ch.SystMap()(1.1))
cb.cp().process(['TT']).AddSyst(cb, 'CMS_scale_j_8TeV', 'lnN', ch.SystMap()(1.05))
cb.cp().process(['VV']).AddSyst(cb, 'CMS_scale_j_8TeV', 'lnN', ch.SystMap()(1.08))

cb.cp().process(['ggH', 'qqH', 'VH', 'ZTT']).AddSyst(cb, 'CMS_scale_t_mutau_$ERA', 'shape', ch.SystMap()(1.0))
#cb.cp().process(['QCD']).AddSyst(cb, 'CMS_htt_QCDShape_mutau_$BIN_$ERA', 'shape', ch.SystMap()(1.0))
cb.cp().process(['ZL']).AddSyst(cb, 'CMS_htt_ZLScale_mutau_$ERA', 'shape', ch.SystMap()(1.0))


cb.cp().AddSyst(
    cb, 'CMS_htt_scale_met_$ERA', 'lnN', ch.SystMap('process')
      (procs['sig'],           0.99)
      (['W', 'TT'],  1.04)
      (['ZL', 'ZJ'],  1.03)    
    )

cb.cp().AddSyst(
    cb, 'CMS_eff_b_$ERA', 'lnN', ch.SystMap('process')
      (['TT'],  0.94))

cb.cp().AddSyst(
    cb, 'CMS_htt_ZttNorm_$ERA', 'lnN', ch.SystMap('process')
      (['ZTT', 'ZL', 'ZJ'],  1.03))

cb.cp().process(['TT']).AddSyst(cb, 'CMS_htt_ttbarNorm_8TeV', 'lnN', ch.SystMap()(1.08))
cb.cp().process(['TT']).AddSyst(cb, 'CMS_htt_ttbarNorm_mutau_inclusive_8TeV', 'lnN', ch.SystMap()(1.33))
cb.cp().process(['VV']).AddSyst(cb, 'CMS_htt_DiBosonNorm_8TeV', 'lnN', ch.SystMap()(1.15))
cb.cp().process(['VV']).AddSyst(cb, 'CMS_htt_DiBosonNorm_mutau_inclusive_8TeV', 'lnN', ch.SystMap()(1.5))
cb.cp().process(['W']).AddSyst(cb, 'CMS_htt_WNorm_mutau_inclusive_8TeV', 'lnN', ch.SystMap()(1.21))
cb.cp().process(['ZTT']).AddSyst(cb, 'CMS_htt_extrap_ztt_mutau_inclusive_8TeV', 'lnN', ch.SystMap()(1.1))
cb.cp().process(['QCD']).AddSyst(cb, 'CMS_htt_QCDSyst_mutau_inclusive_8TeV', 'lnN', ch.SystMap()(1.3))
cb.cp().process(['ZL']).AddSyst(cb, 'CMS_htt_ZLeptonFakeTau_mutau_8TeV', 'lnN', ch.SystMap()(1.3))
cb.cp().process(['ZL']).AddSyst(cb, 'CMS_htt_ZLeptonFakeTau_mutau_inclusive_8TeV', 'lnN', ch.SystMap()(1.7))
cb.cp().process(['ZJ']).AddSyst(cb, 'CMS_htt_ZJetFakeTau_mutau_inclusive_8TeV', 'lnN', ch.SystMap()(1.3))




print '>> Extracting histograms from input root files...'
file = aux_shapes + 'CERN/muTau_inclusive.root'
cb.cp().backgrounds().ExtractShapes(
    file, '$BIN/$PROCESS', '$BIN/$PROCESS_$SYSTEMATIC')
cb.cp().signals().ExtractShapes(
    file, '$BIN/$PROCESS$MASS', '$BIN/$PROCESS$MASS_$SYSTEMATIC')


print '>> Generating bbb uncertainties...'
bbb = ch.BinByBinFactory()
bbb.SetAddThreshold(0.1).SetFixNorm(True)
bbb.AddBinByBin(cb.cp().process(['W']), cb)


print '>> Setting standardised bin names...'
ch.SetStandardBinNames(cb)
cb.PrintAll()

writer = ch.CardWriter('$TAG/$MASS/$ANALYSIS_$CHANNEL_$BINID_$ERA.txt',
                       '$TAG/common/$ANALYSIS_$CHANNEL.input.root')
writer.SetVerbosity(1)
writer.WriteCards('output/sm_cards/LIMITS', cb)

print '>> Done!'
