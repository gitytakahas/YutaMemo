from DataFormats.FWLite import Events, Handle
from ROOT import TLorentzVector

rfile='root://xrootd.unl.edu//store/mc/RunIIFall15MiniAODv2/DY4JetsToLL_M-50_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/MINIAODSIM/PU25nsData2015v1_76X_mcRun2_asymptotic_v12-v1/10000/04C213A4-C3B8-E511-8695-3417EBE64B4F.root'

events = Events(rfile)
handle_lhe = Handle('LHEEventProduct')
label_lhe = ('externalLHEProducer')

for ev in events:

    ev.getByLabel(label_lhe, handle_lhe)
    lhe = handle_lhe.product()

    outgoing = []
    invmass = []

    for status, pdg, moth, mom in zip(lhe.hepeup().ISTUP, lhe.hepeup().IDUP, lhe.hepeup().MOTHUP, lhe.hepeup().PUP):

        if status==1 and abs(pdg) in [21, 1,2,3,4,5]:            
            outgoing.append(pdg)

        if status==1 and abs(pdg) in [11, 13, 15]:
            l = TLorentzVector(mom.x[0], mom.x[1], mom.x[2], mom.x[3])
            invmass.append(l)


    print '# outgoing partons = ', len(outgoing),
    if len(invmass)==2:
        print ', m(ll) = ', (invmass[0] + invmass[1]).M()
    else:
        print 'Wrong counting !!!!!!!!!!!!!'

