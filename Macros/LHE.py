from DataFormats.FWLite import Events, Handle
from ROOT import TFile, TH1F, TTree, gStyle, TH2F, TLorentzVector
import sys, math
import numpy as num
from DeltaR import *

argvs = sys.argv
argc = len(argvs)

rfile = 'root://eoscms//eos/cms/store/mc/RunIIFall15MiniAODv2/DYJetsToLL_M-150_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/MINIAODSIM/PU25nsData2015v1_76X_mcRun2_asymptotic_v12-v1/00000/00A45F10-FFD2-E511-A819-00266CFFC9EC.root'

events = Events(rfile)
outfile = TFile('ValidationTest_DY.root', 'recreate')

event_tree = TTree('per_event','per_event')
event_mass = num.zeros(1, dtype=float)

event_tree.Branch('event_mass', event_mass, 'event_mass/D')


handle_weight = Handle('GenEventInfoProduct')
label_weight = ("generator")

handle_lhe = Handle('LHEEventProduct')
label_lhe = ('externalLHEProducer')


evtid = 0

for ev in events:

    if evtid >= 10000:
        break

    evtid += 1

    ev.getByLabel(label_weight, handle_weight)
    gweight = handle_weight.product()
    weight = gweight.weight()

    ev.getByLabel(label_lhe, handle_lhe)
    lhe = handle_lhe.product()

    outgoing = []
    sumpt = 0

    for status, pdg, moth, mom in zip(lhe.hepeup().ISTUP, lhe.hepeup().IDUP, lhe.hepeup().MOTHUP, lhe.hepeup().PUP):
        if status==1 and abs(pdg) in [11, 13, 15]:

            l = TLorentzVector(mom.x[0], mom.x[1], mom.x[2], mom.x[3])

            outgoing.append(l)



#    import pdb; pdb.set_trace()
    print '=========>', len(outgoing)

    if len(outgoing)!=2:
        print '!!!!!!!!'
    else:
        print (outgoing[0] + outgoing[1]).M()  
        event_mass[0] =(outgoing[0] + outgoing[1]).M()


        event_tree.Fill()



print evtid, 'events processed'

outfile.Write()
outfile.Close()
