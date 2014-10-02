##############################################
#
# date : 2014.4.16
# goal : simple analysis for the AGR data, produce simple tree
# author : Yuta Takahashi
# mail : Yuta.Takahashi@cern.ch
#
##############################################


import numpy as num
import math
from DataFormats.FWLite import Events, Handle
from ROOT import TFile, TTree, TChain
import returnPosition as tool

#import pdb; pdb.set_trace()

# file to be read
# change here depending on your environment
#aChain = TChain('Events')
#aChain.Add('/data1/ytakahas/*.root')
#events = Events(aChain)

#events = Events(['/data1/ytakahas/522D7B2B-67C4-E311-81D3-0025904B2C7E.root', '/data1/ytakahas/BAB53DB2-50C4-E311-87C9-02163E00E7F7.root'])

events = Events('/data1/ytakahas/522D7B2B-67C4-E311-81D3-0025904B2C7E.root')

#events = Events('root://eoscms//store/data/Commissioning2014/Cosmics/AOD/PromptReco-v1/000/220/845/00000/00D0197D-89C5-E311-A04C-02163E00F416.root')

handle_muon  = Handle ('vector<reco::Track>')
label_muon = ('cosmicMuons')

handle_HO  = Handle ('edm::SortedCollection<HORecHit,edm::StrictWeakOrdering<HORecHit>>')
label_HO = ('horeco')


#handle_digi = Handle ('edm::SortedCollection<ZDCDataFrame,edm::StrictWeakOrdering<ZDCDataFrame> >')
#label_digi = ('hcalDigis')

def returnEta(ieta):
    if ieta > 0:
        return 0.08727*(ieta-1)
    else:
        return 0.08727*ieta
   

def returnPhi(iphi):
    if iphi < 36:
        return 0.08727*iphi
    else:
        return -2*math.pi + 0.08727*iphi    


def returndR(eta1,phi1,eta2,phi2):
    dr2 = (eta1-eta2)*(eta1-eta2) + (phi1-phi2)*(phi1-phi2)
    return math.sqrt(dr2)

            


file = TFile('Myroot.root','recreate')

#####################################
# event by event variables
#####################################
nmuon = num.zeros(1, dtype=int)
nHO = num.zeros(1, dtype=int)
nHO_thres = num.zeros(1, dtype=int)
eId = num.zeros(1, dtype=int)
run = num.zeros(1, dtype=int)
lumi = num.zeros(1, dtype=int)

t_event = TTree('event_tree','event_tree')
t_event.Branch('eId',eId,'eId/I')
t_event.Branch('run',run,'run/I')
t_event.Branch('lumi',lumi,'lumi/I')
t_event.Branch('nmuon',nmuon,'nmuon/I')
t_event.Branch('nHO',nHO,'nHO/I')
t_event.Branch('nHO_thres',nHO_thres,'nHO_thres/I')



#####################################
# muon
#####################################
muon_pt = num.zeros(1, dtype=num.float)
muon_eta = num.zeros(1, dtype=num.float)
muon_phi = num.zeros(1, dtype=num.float)
muon_innereta = num.zeros(1, dtype=num.float)
muon_innerphi = num.zeros(1, dtype=num.float)
muon_closest_HO_energy = num.zeros(1, dtype=num.float)
muon_closest_HO_dR = num.zeros(1, dtype=num.float)
muon_normalizedchi2 = num.zeros(1, dtype=num.float)
muon_tight = num.zeros(1, dtype=num.float)

t_muon = TTree('muon_tree','muon_tree')
t_muon.Branch('muon_pt',muon_pt,'muon_pt/D')
t_muon.Branch('muon_eta',muon_eta,'muon_eta/D')
t_muon.Branch('muon_phi',muon_phi,'muon_phi/D')
t_muon.Branch('muon_normalizedchi2',muon_normalizedchi2,'muon_normalizedchi2/D')
t_muon.Branch('muon_tight',muon_tight,'muon_tight/D')
t_muon.Branch('muon_innereta',muon_innereta,'muon_innereta/D')
t_muon.Branch('muon_innerphi',muon_innerphi,'muon_innerphi/D')
t_muon.Branch('muon_closest_HO_energy',muon_closest_HO_energy,'muon_closest_HO_energy/D')
t_muon.Branch('muon_closest_HO_dR',muon_closest_HO_dR,'muon_closest_HO_dR/D')



#####################################
# HO
#####################################
#HO_energy = num.zeros(1, dtype=num.float)
#HO_ieta = num.zeros(1, dtype=num.int)
#HO_iphi = num.zeros(1, dtype=num.int)
#HO_eta = num.zeros(1, dtype=num.float)
#HO_phi = num.zeros(1, dtype=num.float)
#HO_xl = num.zeros(1, dtype=num.float)
#HO_xh = num.zeros(1, dtype=num.float)
#HO_yl = num.zeros(1, dtype=num.float)
#HO_yh = num.zeros(1, dtype=num.float)
#HO_zl = num.zeros(1, dtype=num.float)
#HO_zh = num.zeros(1, dtype=num.float)
#
#t_HO = TTree('HO_tree','HO_tree')
#t_HO.Branch('HO_energy',HO_energy,'HO_energy/D')
#t_HO.Branch('HO_ieta',HO_ieta,'HO_ieta/I')
#t_HO.Branch('HO_iphi',HO_iphi,'HO_iphi/I')
#t_HO.Branch('HO_eta',HO_eta,'HO_eta/D')
#t_HO.Branch('HO_phi',HO_phi,'HO_phi/D')
#t_HO.Branch('HO_xl',HO_xl,'HO_xl/D')
#t_HO.Branch('HO_xh',HO_xh,'HO_xh/D')
#t_HO.Branch('HO_yl',HO_yl,'HO_yl/D')
#t_HO.Branch('HO_yh',HO_yh,'HO_yh/D')
#t_HO.Branch('HO_zl',HO_zl,'HO_zl/D')
#t_HO.Branch('HO_zh',HO_zh,'HO_zh/D')


#####################################
# mapping 
#####################################
map_HO_energy = num.zeros(1, dtype=num.float)
map_HO_ieta = num.zeros(1, dtype=num.int)
map_HO_iphi = num.zeros(1, dtype=num.int)
map_HO_ichannel = num.zeros(1, dtype=num.int)

map_HO_xl = num.zeros(1, dtype=num.float)
map_HO_xh = num.zeros(1, dtype=num.float)
map_HO_yl = num.zeros(1, dtype=num.float)
map_HO_yh = num.zeros(1, dtype=num.float)
map_HO_zl = num.zeros(1, dtype=num.float)
map_HO_zh = num.zeros(1, dtype=num.float)


map_muon_pt = num.zeros(1, dtype=num.float)
map_muon_eta = num.zeros(1, dtype=num.float)
map_muon_phi = num.zeros(1, dtype=num.float)
map_muon_normalizedchi2 = num.zeros(1, dtype=num.float)
map_muon_tight = num.zeros(1, dtype=num.float)
map_muon_X = num.zeros(1, dtype=num.float)
map_muon_Y = num.zeros(1, dtype=num.float)
map_muon_Z = num.zeros(1, dtype=num.float)

map_tree = TTree('map_tree','map_tree')
map_tree.Branch('map_HO_energy',map_HO_energy,'map_HO_energy/D')
map_tree.Branch('map_HO_ieta',map_HO_ieta,'map_HO_ieta/I')
map_tree.Branch('map_HO_iphi',map_HO_iphi,'map_HO_iphi/I')
map_tree.Branch('map_HO_ichannel',map_HO_ichannel,'map_HO_ichannel/I')
map_tree.Branch('map_HO_xl',map_HO_xl,'map_HO_xl/D')
map_tree.Branch('map_HO_xh',map_HO_xh,'map_HO_xh/D')
map_tree.Branch('map_HO_yl',map_HO_yl,'map_HO_yl/D')
map_tree.Branch('map_HO_yh',map_HO_yh,'map_HO_yh/D')
map_tree.Branch('map_HO_zl',map_HO_zl,'map_HO_zl/D')
map_tree.Branch('map_HO_zh',map_HO_zh,'map_HO_zh/D')


map_tree.Branch('map_muon_pt',map_muon_pt,'map_muon_pt/D')
map_tree.Branch('map_muon_eta',map_muon_eta,'map_muon_eta/D')
map_tree.Branch('map_muon_phi',map_muon_phi,'map_muon_phi/D')
map_tree.Branch('map_muon_normalizedchi2',map_muon_normalizedchi2,'map_muon_normalizedchi2/D')
map_tree.Branch('map_muon_X',map_muon_X,'map_muon_X/D')
map_tree.Branch('map_muon_Y',map_muon_Y,'map_muon_Y/D')
map_tree.Branch('map_muon_Z',map_muon_Z,'map_muon_Z/D')
map_tree.Branch('map_muon_tight',map_muon_tight,'map_muon_tight/D')

db = tool.findEtaPhi()


for iev, ev in enumerate(events):
    
    ev.getByLabel(label_muon, handle_muon)

    ### Event information
    runnum = ev.eventAuxiliary().id().run()
    luminosity = ev.eventAuxiliary().id().luminosityBlock()
    eventId = ev.eventAuxiliary().id().event()

    if iev%1000==0:
        print runnum, iev

    ### Muon
    muon = handle_muon.product()

    if len(muon) == 0:
        continue

    ### HO
    ev.getByLabel(label_HO, handle_HO)
    ho = handle_HO.product()

    nmuon[0] = len(muon)
    nHO[0] = len(ho)
    nHO_thres[0] = len([iho for iho in ho if iho.energy() > 0.3])
    eId[0] = eventId
    run[0] = runnum
    lumi[0] = luminosity

    t_event.Fill()

    for imuon in muon:

        muon_pt[0] = imuon.pt()
        muon_eta[0] = imuon.eta()
        muon_phi[0] = imuon.phi()
        muon_normalizedchi2[0] = imuon.normalizedChi2()
        muon_tight[0] = imuon.tight
        muon_innereta[0] = imuon.innerPosition().eta()
        muon_innerphi[0] = imuon.innerPosition().phi()

        ho_min_dR = 100
        ho_energy = -1
        
        for iho in ho:
            eta   = returnEta(iho.id().ieta())
            phi   = returnPhi(iho.id().iphi())
            energy = iho.energy()

            if energy > 0.3:
                map_HO_energy[0] = energy
                map_HO_ieta[0] = iho.id().ieta()
                map_HO_iphi[0] = iho.id().iphi()
                map_HO_ichannel[0] = iho.id().det()

                xl,xh,yl,yh,zl,zh = db.returnXY(iho.id().ieta(), iho.id().iphi(), iho.id().zside())
                
                map_HO_xl[0] = xl
                map_HO_xh[0] = xh
                map_HO_yl[0] = yl
                map_HO_yh[0] = yh
                map_HO_zl[0] = zl
                map_HO_zh[0] = zh


                map_muon_pt[0] = imuon.pt()
                map_muon_eta[0] = imuon.eta()
                map_muon_phi[0] = imuon.phi()
                map_muon_X[0] = imuon.innerPosition().x()
                map_muon_Y[0] = imuon.innerPosition().y()
                map_muon_Z[0] = imuon.innerPosition().z()
                map_muon_normalizedchi2[0] = imuon.normalizedChi2()
                map_muon_tight[0] = imuon.tight
                map_tree.Fill()


            dr = returndR(imuon.innerPosition().eta(), imuon.innerPosition().phi(), eta, phi)
            if dr < ho_min_dR:
                ho_min_dR = dr
                ho_energy = energy
                
        muon_closest_HO_energy[0] = ho_energy
        muon_closest_HO_dR[0] = ho_min_dR
        


        t_muon.Fill()



#    for iho in ho:
#        HO_ieta[0]   = iho.id().ieta()
#        HO_iphi[0]   = iho.id().iphi()
#        HO_eta[0]   = returnEta(iho.id().ieta())
#        HO_phi[0]   = returnPhi(iho.id().iphi())
#        HO_energy[0] = iho.energy()
#
#
#        t_HO.Fill()
        

    

#    print 'check'

file.Write()
file.Close()
