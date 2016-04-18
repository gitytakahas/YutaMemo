from DataFormats.FWLite import Events, Handle
from ROOT import TFile, TH1F, TTree, gStyle, TH2F
import sys, math
import numpy as num
#from DeltaR import *

argvs = sys.argv
argc = len(argvs)

#rfile=[
#    'root://eoscms//eos/cms/store/mc/RunIIFall15MiniAODv2/WJetsToLNu_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/MINIAODSIM/PU25nsData2015v1_76X_mcRun2_asymptotic_v12-v1/00000/0C765598-8BD1-E511-BF63-20CF3027A566.root',
#    'root://eoscms//eos/cms/store/mc/RunIIFall15MiniAODv2/WJetsToLNu_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/MINIAODSIM/PU25nsData2015v1_76X_mcRun2_asymptotic_v12-v1/00000/16CE1558-77D1-E511-A977-44A8423DE2C0.root',
#    'root://eoscms//eos/cms/store/mc/RunIIFall15MiniAODv2/WJetsToLNu_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/MINIAODSIM/PU25nsData2015v1_76X_mcRun2_asymptotic_v12-v1/00000/32788050-8FD1-E511-A9B1-20CF3027A566.root',
#    'root://eoscms//eos/cms/store/mc/RunIIFall15MiniAODv2/WJetsToLNu_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/MINIAODSIM/PU25nsData2015v1_76X_mcRun2_asymptotic_v12-v1/00000/4E0AB48C-8AD1-E511-B409-20CF3027A566.root',
#    'root://eoscms//eos/cms/store/mc/RunIIFall15MiniAODv2/WJetsToLNu_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/MINIAODSIM/PU25nsData2015v1_76X_mcRun2_asymptotic_v12-v1/00000/5CC6ED1B-8ED1-E511-91E6-20CF3027A566.root',
#    'root://eoscms//eos/cms/store/mc/RunIIFall15MiniAODv2/WJetsToLNu_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/MINIAODSIM/PU25nsData2015v1_76X_mcRun2_asymptotic_v12-v1/00000/6064E9B7-90D1-E511-9A65-20CF3027A566.root',
#    'root://eoscms//eos/cms/store/mc/RunIIFall15MiniAODv2/WJetsToLNu_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/MINIAODSIM/PU25nsData2015v1_76X_mcRun2_asymptotic_v12-v1/00000/727C8C9E-8CD1-E511-8307-20CF3027A566.root',
#    'root://eoscms//eos/cms/store/mc/RunIIFall15MiniAODv2/WJetsToLNu_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/MINIAODSIM/PU25nsData2015v1_76X_mcRun2_asymptotic_v12-v1/00000/B018CFCA-75D1-E511-AE04-44A8423DE2C0.root',
#    'root://eoscms//eos/cms/store/mc/RunIIFall15MiniAODv2/WJetsToLNu_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/MINIAODSIM/PU25nsData2015v1_76X_mcRun2_asymptotic_v12-v1/00000/BA99658A-76D1-E511-833A-44A8423DE2C0.root',
#    'root://eoscms//eos/cms/store/mc/RunIIFall15MiniAODv2/WJetsToLNu_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/MINIAODSIM/PU25nsData2015v1_76X_mcRun2_asymptotic_v12-v1/00000/F26A37F7-74D1-E511-B232-44A8423DE2C0.root',
#    'root://eoscms//eos/cms/store/mc/RunIIFall15MiniAODv2/WJetsToLNu_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/MINIAODSIM/PU25nsData2015v1_76X_mcRun2_asymptotic_v12-v1/10000/00731810-79D1-E511-84ED-549F358EB7A3.root',
#    'root://eoscms//eos/cms/store/mc/RunIIFall15MiniAODv2/WJetsToLNu_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/MINIAODSIM/PU25nsData2015v1_76X_mcRun2_asymptotic_v12-v1/10000/00B2358B-97D1-E511-A993-02163E0176B1.root',
#    'root://eoscms//eos/cms/store/mc/RunIIFall15MiniAODv2/WJetsToLNu_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/MINIAODSIM/PU25nsData2015v1_76X_mcRun2_asymptotic_v12-v1/10000/00C21449-9AD1-E511-9EEF-008CFA197CE0.root',
#    'root://eoscms//eos/cms/store/mc/RunIIFall15MiniAODv2/WJetsToLNu_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/MINIAODSIM/PU25nsData2015v1_76X_mcRun2_asymptotic_v12-v1/10000/00FAD487-95D1-E511-BBE2-02163E01679D.root',
#    'root://eoscms//eos/cms/store/mc/RunIIFall15MiniAODv2/WJetsToLNu_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/MINIAODSIM/PU25nsData2015v1_76X_mcRun2_asymptotic_v12-v1/10000/023C370C-61D1-E511-83D4-A0000420FE80.root',
#    'root://eoscms//eos/cms/store/mc/RunIIFall15MiniAODv2/WJetsToLNu_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/MINIAODSIM/PU25nsData2015v1_76X_mcRun2_asymptotic_v12-v1/10000/02D080B1-8DD1-E511-B9D2-001E67DDC2CC.root',
#    'root://eoscms//eos/cms/store/mc/RunIIFall15MiniAODv2/WJetsToLNu_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/MINIAODSIM/PU25nsData2015v1_76X_mcRun2_asymptotic_v12-v1/10000/02D580AC-8DD1-E511-88D7-5065F381B2D1.root',
#    'root://eoscms//eos/cms/store/mc/RunIIFall15MiniAODv2/WJetsToLNu_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/MINIAODSIM/PU25nsData2015v1_76X_mcRun2_asymptotic_v12-v1/10000/04051510-B9D1-E511-8B83-02163E013F56.root',
#    'root://eoscms//eos/cms/store/mc/RunIIFall15MiniAODv2/WJetsToLNu_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/MINIAODSIM/PU25nsData2015v1_76X_mcRun2_asymptotic_v12-v1/10000/043FC30F-86D1-E511-9C05-A0000420FE80.root',
#    'root://eoscms//eos/cms/store/mc/RunIIFall15MiniAODv2/WJetsToLNu_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/MINIAODSIM/PU25nsData2015v1_76X_mcRun2_asymptotic_v12-v1/10000/04774AF9-7DD1-E511-B8AE-002590A82B8E.root',
#    'root://eoscms//eos/cms/store/mc/RunIIFall15MiniAODv2/WJetsToLNu_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/MINIAODSIM/PU25nsData2015v1_76X_mcRun2_asymptotic_v12-v1/10000/04C76083-97D1-E511-8391-001E675A622F.root',
#    'root://eoscms//eos/cms/store/mc/RunIIFall15MiniAODv2/WJetsToLNu_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/MINIAODSIM/PU25nsData2015v1_76X_mcRun2_asymptotic_v12-v1/10000/065ACBE9-95D1-E511-9D5C-5065F381B271.root']
#


rfile = [
    'root://eoscms//eos/cms/store/mc/RunIIFall15MiniAODv2/WJetsToLNu_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/MINIAODSIM/PU25nsData2015v1_76X_mcRun2_asymptotic_v12-v1/10000/081E3DF4-D5D1-E511-AD8D-0CC47A009148.root',
'root://eoscms//eos/cms/store/mc/RunIIFall15MiniAODv2/WJetsToLNu_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/MINIAODSIM/PU25nsData2015v1_76X_mcRun2_asymptotic_v12-v1/10000/0A055716-8ED1-E511-B4A1-02163E0168A7.root',
'root://eoscms//eos/cms/store/mc/RunIIFall15MiniAODv2/WJetsToLNu_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/MINIAODSIM/PU25nsData2015v1_76X_mcRun2_asymptotic_v12-v1/10000/0AAC7ED0-96D1-E511-B9A9-02163E01772D.root',
'root://eoscms//eos/cms/store/mc/RunIIFall15MiniAODv2/WJetsToLNu_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/MINIAODSIM/PU25nsData2015v1_76X_mcRun2_asymptotic_v12-v1/10000/0AC6A4AD-8DD1-E511-9473-001E67A404B0.root',
'root://eoscms//eos/cms/store/mc/RunIIFall15MiniAODv2/WJetsToLNu_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/MINIAODSIM/PU25nsData2015v1_76X_mcRun2_asymptotic_v12-v1/10000/0C376330-A2D1-E511-9B13-02163E016860.root',
'root://eoscms//eos/cms/store/mc/RunIIFall15MiniAODv2/WJetsToLNu_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/MINIAODSIM/PU25nsData2015v1_76X_mcRun2_asymptotic_v12-v1/10000/0C7A9202-8BD1-E511-B696-008CFA1C6564.root',
'root://eoscms//eos/cms/store/mc/RunIIFall15MiniAODv2/WJetsToLNu_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/MINIAODSIM/PU25nsData2015v1_76X_mcRun2_asymptotic_v12-v1/10000/0E7E7AAD-8DD1-E511-8E31-0CC47A13CC7E.root',
'root://eoscms//eos/cms/store/mc/RunIIFall15MiniAODv2/WJetsToLNu_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/MINIAODSIM/PU25nsData2015v1_76X_mcRun2_asymptotic_v12-v1/10000/0E860431-A0D1-E511-897E-0025907277FE.root',
'root://eoscms//eos/cms/store/mc/RunIIFall15MiniAODv2/WJetsToLNu_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/MINIAODSIM/PU25nsData2015v1_76X_mcRun2_asymptotic_v12-v1/10000/0E88745B-72D1-E511-9A1B-001E67396E1E.root',
'root://eoscms//eos/cms/store/mc/RunIIFall15MiniAODv2/WJetsToLNu_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/MINIAODSIM/PU25nsData2015v1_76X_mcRun2_asymptotic_v12-v1/10000/0EE2C591-72D1-E511-AD74-0002C94D5614.root',
'root://eoscms//eos/cms/store/mc/RunIIFall15MiniAODv2/WJetsToLNu_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/MINIAODSIM/PU25nsData2015v1_76X_mcRun2_asymptotic_v12-v1/10000/0EEC8896-82D1-E511-AE4B-001E67A404B5.root',
'root://eoscms//eos/cms/store/mc/RunIIFall15MiniAODv2/WJetsToLNu_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/MINIAODSIM/PU25nsData2015v1_76X_mcRun2_asymptotic_v12-v1/10000/1093D92A-9AD1-E511-95C1-90B11C05037D.root',
'root://eoscms//eos/cms/store/mc/RunIIFall15MiniAODv2/WJetsToLNu_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/MINIAODSIM/PU25nsData2015v1_76X_mcRun2_asymptotic_v12-v1/10000/12326493-79D1-E511-9F7F-549F35AF4524.root',
'root://eoscms//eos/cms/store/mc/RunIIFall15MiniAODv2/WJetsToLNu_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/MINIAODSIM/PU25nsData2015v1_76X_mcRun2_asymptotic_v12-v1/10000/125F9B9E-96D1-E511-9728-002590D8C7BE.root',
'root://eoscms//eos/cms/store/mc/RunIIFall15MiniAODv2/WJetsToLNu_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/MINIAODSIM/PU25nsData2015v1_76X_mcRun2_asymptotic_v12-v1/10000/1288D2D4-82D1-E511-82B5-A0369F7FE960.root',
'root://eoscms//eos/cms/store/mc/RunIIFall15MiniAODv2/WJetsToLNu_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/MINIAODSIM/PU25nsData2015v1_76X_mcRun2_asymptotic_v12-v1/10000/12DDA306-9ED1-E511-9BE4-02163E012E1E.root',
'root://eoscms//eos/cms/store/mc/RunIIFall15MiniAODv2/WJetsToLNu_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/MINIAODSIM/PU25nsData2015v1_76X_mcRun2_asymptotic_v12-v1/10000/12E4D5CB-90D1-E511-8754-B083FED0FFCF.root'
]


events = Events(rfile)
outfile = TFile('ValidationTest_W.root', 'recreate')

event_tree = TTree('per_event','per_event')
event_njet = num.zeros(1, dtype=int)

event_tree.Branch('event_njet', event_njet, 'event_njet/I')

handle_lhe = Handle('LHEEventProduct')
label_lhe = ('externalLHEProducer')


evtid = 0

for ev in events:

    evtid += 1

    ev.getByLabel(label_lhe, handle_lhe)
    lhe = handle_lhe.product()

    outgoing = []

#    import pdb; pdb.set_trace()

    for status, pdg, moth, mom in zip(lhe.hepeup().ISTUP, lhe.hepeup().IDUP, lhe.hepeup().MOTHUP, lhe.hepeup().PUP):
        if status==1 and abs(pdg) in [21, 1,2,3,4,5]:

#            print math.sqrt(mom.x[0]**2 + mom.x[1]**2)
#            sumpt += math.sqrt(mom.x[0]**2 + mom.x[1]**2)
            
            outgoing.append(pdg)

#    print '=========>', len(outgoing)
    event_njet[0] = len(outgoing)
    event_tree.Fill()

print evtid, 'events processed'

outfile.Write()
outfile.Close()
