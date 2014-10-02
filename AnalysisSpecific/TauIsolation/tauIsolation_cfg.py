import CMGTools.RootTools.fwlite.Config as cfg
from CMGTools.RootTools.fwlite.Config import printComps
from CMGTools.RootTools.RootTools import * 



vertexAna = cfg.Analyzer(
    'VertexAnalyzer',
    goodVertices = 'goodPVFilter',
    vertexWeight = None,
    fixedWeight = 1,
    verbose = False,
    )


pileUpAna = cfg.Analyzer(
    'PileUpAnalyzer',
    true = True
    )


muonAna = cfg.Analyzer(
    'MuonAnalyzer',
    genSrc = 'genParticles',
    absGenIds = [13, 5],
    muonSrc = 'muons',
    minPt = 20.,
    maxEta = 2.4,
    matchDeltaR = 0.3,
    )

electronAna = cfg.Analyzer(
    'ElectronAnalyzer',
    genSrc = 'genParticles',
    absGenIds = [11, 5],
    electronSrc = 'gedGsfElectrons',
    minPt = 20.,
    maxEta = 2.4,
    matchDeltaR = 0.3,
    )

tauAna = cfg.Analyzer(
    'TauAnalyzer',
    genSrc = 'genParticles',
    absGenIds = [15, 13, 11, 5, 4, 3, 2, 1], # all jets from top may fake a tau
    tauSrc = 'hpsPFTauProducer',
    minPt = 20.,
    maxEta = 2.4,
    matchDeltaR = 0.5,
    )

genMetAna = cfg.Analyzer(
    'GenMetAnalyzer',
    genSrc = 'genParticles',
    metSrc = 'pfMet'
    )


jetAna = cfg.Analyzer(
    'PFJetAnalyzer',
    # jetCol = 'ak5PFJets',
    jetCol = 'ak5PFJetsCHS',
    jetPt = 30.,
    jetEta = 3.0,
    btagSFseed = 123456,
    relaxJetId = False, 
    jerCorr = False,
    #jesCorr = 1.,
    )

treeProducer = cfg.Analyzer(
    'H2TauTauTreeProducerPFStudies'
    )

metTreeProducer = cfg.Analyzer(
    'METTreeProducer'
    )
jetTreeProducer = cfg.Analyzer(
    'JetTreeProducer'
    )
electronTreeProducer = cfg.Analyzer(
    'ElectronTreeProducer'
    )
muonTreeProducer = cfg.Analyzer(
    'MuonTreeProducer'
    )
partonTreeProducer = cfg.Analyzer(
    'PartonTreeProducer'
    )
tauTreeProducer = cfg.Analyzer(
    'TauTreeProducer'
    )
#########################################################################################

#from CMGTools.RootTools.pf_samples import allsamples
from CMGTools.RootTools.pf_samples import *

#########################################################################################


sequence = cfg.Sequence( [
    vertexAna, 
    tauAna,
    partonTreeProducer,
    tauTreeProducer
   ] )


selectedComponents = allsamples
selectedComponents = [VBF_Timing]

for comp in selectedComponents:
    comp.splitFactor = 1
#    comp.splitFactor = 100

config = cfg.Config( components = selectedComponents,
                     sequence = sequence )

printComps(config.components, True)
