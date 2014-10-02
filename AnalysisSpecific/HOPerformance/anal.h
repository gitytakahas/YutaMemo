//////////////////////////////////////////////////////////
// This class has been automatically generated on
// Fri Sep 20 12:37:42 2013 by ROOT version 5.32/00
// from TTree Events/Events
// found on file: /afs/cern.ch/user/y/ytakahas/work/MET_performance/CMSSW_5_3_2_patch4/src/analysis/Ntuple.root
//////////////////////////////////////////////////////////

#ifndef anal_h
#define anal_h

#include <TROOT.h>
#include <TChain.h>
#include <TFile.h>
#include <TMath.h>
#include <string>
#include <iostream>
#include <vector>
#include <TH1F.h>
#include <TH2F.h>
#include <TGraph.h>
#include <TLegend.h>



// Header file for the classes stored in the TTree if any.
#include <TClonesArray.h>

// Fixed size dimensions of array or collections stored in the TTree if any.
const Int_t kMaxGenParticle = 464;
const Int_t kMaxMuon = 51;
const Int_t kMaxElectron = 8;
const Int_t kMaxPFJet = 60;
const Int_t kMaxHO = 15;
const Int_t kMaxGenJet = 16;
const Int_t kMaxMuon2 = 47;
const Int_t kMaxElectron2 = 7;
const Int_t kMaxPFJet2 = 59;

class anal {
public :
   TTree          *fChain;   //!pointer to the analyzed TTree or TChain
   Int_t           fCurrent; //!current Tree number in a TChain

   // Declaration of leaf types
   Int_t           GenParticle_;
   Float_t         GenParticle_pt[kMaxGenParticle];   //[GenParticle_]
   Float_t         GenParticle_eta[kMaxGenParticle];   //[GenParticle_]
   Float_t         GenParticle_phi[kMaxGenParticle];   //[GenParticle_]
   Float_t         GenParticle_mass[kMaxGenParticle];   //[GenParticle_]
   Int_t           GenParticle_pdgid[kMaxGenParticle];   //[GenParticle_]
   Int_t           GenParticle_status[kMaxGenParticle];   //[GenParticle_]
   Int_t           GenParticle_motherPdgID[kMaxGenParticle];   //[GenParticle_]
   Int_t           Muon_;
   Float_t         Muon_pt[kMaxMuon];   //[Muon_]
   Float_t         Muon_eta[kMaxMuon];   //[Muon_]
   Float_t         Muon_phi[kMaxMuon];   //[Muon_]
   Float_t         Muon_pterr[kMaxMuon];   //[Muon_]
   Int_t           Muon_q[kMaxMuon];   //[Muon_]
   UInt_t          Muon_typeBits[kMaxMuon];   //[Muon_]
   UInt_t          Muon_qualityBits[kMaxMuon];   //[Muon_]
   Int_t           Muon_nValidHits[kMaxMuon];   //[Muon_]
   UInt_t          Muon_nTkHits[kMaxMuon];   //[Muon_]
   UInt_t          Muon_nPixHits[kMaxMuon];   //[Muon_]
   UInt_t          Muon_nMatch[kMaxMuon];   //[Muon_]
   UInt_t          Muon_trkLayers[kMaxMuon];   //[Muon_]
   Float_t         Muon_tkNchi2[kMaxMuon];   //[Muon_]
   Float_t         Muon_muNchi2[kMaxMuon];   //[Muon_]
   ULong_t         Muon_hltMatchBits[kMaxMuon];   //[Muon_]
   Int_t           Muon_isMCReal[kMaxMuon];   //[Muon_]
   Float_t         Muon_trkIso03[kMaxMuon];   //[Muon_]
   Float_t         Muon_emIso03[kMaxMuon];   //[Muon_]
   Float_t         Muon_hadIso03[kMaxMuon];   //[Muon_]
   Float_t         Muon_hoIso03[kMaxMuon];   //[Muon_]
   Float_t         Muon_pfIso04ChargedHadron[kMaxMuon];   //[Muon_]
   Float_t         Muon_pfIso04ChargedParticle[kMaxMuon];   //[Muon_]
   Float_t         Muon_pfIso04NeutralHadron[kMaxMuon];   //[Muon_]
   Float_t         Muon_pfIso04Photon[kMaxMuon];   //[Muon_]
   Float_t         Muon_pfIso04NeutralHadronHighThreshold[kMaxMuon];   //[Muon_]
   Float_t         Muon_pfIso04PhotonHighThreshold[kMaxMuon];   //[Muon_]
   Float_t         Muon_pfIso04PU[kMaxMuon];   //[Muon_]
   Float_t         Muon_d0[kMaxMuon];   //[Muon_]
   Float_t         Muon_dz[kMaxMuon];   //[Muon_]
   Float_t         Muon_ip3d[kMaxMuon];   //[Muon_]
   Float_t         Muon_ip3dSig[kMaxMuon];   //[Muon_]
   Float_t         Muon_ip3dBS[kMaxMuon];   //[Muon_]
   Float_t         Muon_ip3dSigBS[kMaxMuon];   //[Muon_]
   UInt_t          Muon_NMatchedPFCandidates[kMaxMuon];   //[Muon_]
   UInt_t          Muon_MatchedPFCandidateIndex[kMaxMuon][10];   //[Muon_]
   Int_t           Electron_;
   Float_t         Electron_pt[kMaxElectron];   //[Electron_]
   Float_t         Electron_eta[kMaxElectron];   //[Electron_]
   Float_t         Electron_phi[kMaxElectron];   //[Electron_]
   Float_t         Electron_p[kMaxElectron];   //[Electron_]
   Float_t         Electron_scEt[kMaxElectron];   //[Electron_]
   Float_t         Electron_scEta[kMaxElectron];   //[Electron_]
   Float_t         Electron_scPhi[kMaxElectron];   //[Electron_]
   Int_t           Electron_q[kMaxElectron];   //[Electron_]
   Bool_t          Electron_isEcalDriven[kMaxElectron];   //[Electron_]
   Bool_t          Electron_isTrackerDriven[kMaxElectron];   //[Electron_]
   Bool_t          Electron_isEB[kMaxElectron];   //[Electron_]
   Bool_t          Electron_isEE[kMaxElectron];   //[Electron_]
   Int_t           Electron_Classification[kMaxElectron];   //[Electron_]
   Int_t           Electron_isMCReal[kMaxElectron];   //[Electron_]
   ULong_t         Electron_hltMatchBits[kMaxElectron];   //[Electron_]
   UInt_t          Electron_l1TriggerMatchBits[kMaxElectron];   //[Electron_]
   Float_t         Electron_TrackMomentumError[kMaxElectron];   //[Electron_]
   Int_t           Electron_nBrem[kMaxElectron];   //[Electron_]
   Float_t         Electron_fBrem[kMaxElectron];   //[Electron_]
   Float_t         Electron_EOverP[kMaxElectron];   //[Electron_]
   Float_t         Electron_pIn[kMaxElectron];   //[Electron_]
   Float_t         Electron_ESeedClusterOverPIn[kMaxElectron];   //[Electron_]
   Float_t         Electron_ESeedClusterOverPout[kMaxElectron];   //[Electron_]
   Float_t         Electron_EEleClusterOverPout[kMaxElectron];   //[Electron_]
   Float_t         Electron_EcalEnergy[kMaxElectron];   //[Electron_]
   Float_t         Electron_EcalEnergyError[kMaxElectron];   //[Electron_]
   Float_t         Electron_deltaEtaIn[kMaxElectron];   //[Electron_]
   Float_t         Electron_deltaPhiIn[kMaxElectron];   //[Electron_]
   Float_t         Electron_dEtaCalo[kMaxElectron];   //[Electron_]
   Float_t         Electron_dPhiCalo[kMaxElectron];   //[Electron_]
   Float_t         Electron_sigiEtaiEta[kMaxElectron];   //[Electron_]
   Float_t         Electron_sigiPhiiPhi[kMaxElectron];   //[Electron_]
   Float_t         Electron_sigiEtaiPhi[kMaxElectron];   //[Electron_]
   Float_t         Electron_SCEtaWidth[kMaxElectron];   //[Electron_]
   Float_t         Electron_SCPhiWidth[kMaxElectron];   //[Electron_]
   Float_t         Electron_R9[kMaxElectron];   //[Electron_]
   Float_t         Electron_PreShowerOverRaw[kMaxElectron];   //[Electron_]
   Float_t         Electron_HoverE[kMaxElectron];   //[Electron_]
   Float_t         Electron_HoverESingleTower[kMaxElectron];   //[Electron_]
   Float_t         Electron_GsfTrackChi2OverNdof[kMaxElectron];   //[Electron_]
   Float_t         Electron_KFTrackChi2OverNdof[kMaxElectron];   //[Electron_]
   Float_t         Electron_KFTrackNHits[kMaxElectron];   //[Electron_]
   Float_t         Electron_KFTrackNLayersWithMeasurement[kMaxElectron];   //[Electron_]
   Float_t         Electron_SeedE1x5OverE5x5[kMaxElectron];   //[Electron_]
   Bool_t          Electron_isConv[kMaxElectron];   //[Electron_]
   Float_t         Electron_nExpHitsInner[kMaxElectron];   //[Electron_]
   Float_t         Electron_partnerDeltaCot[kMaxElectron];   //[Electron_]
   Float_t         Electron_partnerDist[kMaxElectron];   //[Electron_]
   Float_t         Electron_partnerRadius[kMaxElectron];   //[Electron_]
   Float_t         Electron_d0[kMaxElectron];   //[Electron_]
   Float_t         Electron_d0Err[kMaxElectron];   //[Electron_]
   Float_t         Electron_dz[kMaxElectron];   //[Electron_]
   Float_t         Electron_ip3d[kMaxElectron];   //[Electron_]
   Float_t         Electron_ip3dSig[kMaxElectron];   //[Electron_]
   Float_t         Electron_ip3dBS[kMaxElectron];   //[Electron_]
   Float_t         Electron_ip3dSigBS[kMaxElectron];   //[Electron_]
   Float_t         Electron_trkIso03[kMaxElectron];   //[Electron_]
   Float_t         Electron_emIso03[kMaxElectron];   //[Electron_]
   Float_t         Electron_hadIso03[kMaxElectron];   //[Electron_]
   Float_t         Electron_trkIso04[kMaxElectron];   //[Electron_]
   Float_t         Electron_emIso04[kMaxElectron];   //[Electron_]
   Float_t         Electron_hadIso04[kMaxElectron];   //[Electron_]
   Float_t         Electron_pfIso04ChargedHadron[kMaxElectron];   //[Electron_]
   Float_t         Electron_pfIso04ChargedParticle[kMaxElectron];   //[Electron_]
   Float_t         Electron_pfIso04NeutralHadron[kMaxElectron];   //[Electron_]
   Float_t         Electron_pfIso04Photon[kMaxElectron];   //[Electron_]
   Float_t         Electron_pfIso04NeutralHadronHighThreshold[kMaxElectron];   //[Electron_]
   Float_t         Electron_pfIso04PhotonHighThreshold[kMaxElectron];   //[Electron_]
   Float_t         Electron_pfIso04PU[kMaxElectron];   //[Electron_]
   Float_t         Electron_SCRawEnergy[kMaxElectron];   //[Electron_]
   Float_t         Electron_E5x5[kMaxElectron];   //[Electron_]
   Float_t         Electron_EtaSeed[kMaxElectron];   //[Electron_]
   Float_t         Electron_PhiSeed[kMaxElectron];   //[Electron_]
   Float_t         Electron_ESeed[kMaxElectron];   //[Electron_]
   Float_t         Electron_E3x3Seed[kMaxElectron];   //[Electron_]
   Float_t         Electron_E5x5Seed[kMaxElectron];   //[Electron_]
   Float_t         Electron_EMaxSeed[kMaxElectron];   //[Electron_]
   Float_t         Electron_E2ndSeed[kMaxElectron];   //[Electron_]
   Float_t         Electron_ETopSeed[kMaxElectron];   //[Electron_]
   Float_t         Electron_EBottomSeed[kMaxElectron];   //[Electron_]
   Float_t         Electron_ELeftSeed[kMaxElectron];   //[Electron_]
   Float_t         Electron_ERightSeed[kMaxElectron];   //[Electron_]
   Float_t         Electron_E2x5MaxSeed[kMaxElectron];   //[Electron_]
   Float_t         Electron_E2x5TopSeed[kMaxElectron];   //[Electron_]
   Float_t         Electron_E2x5BottomSeed[kMaxElectron];   //[Electron_]
   Float_t         Electron_E2x5LeftSeed[kMaxElectron];   //[Electron_]
   Float_t         Electron_E2x5RightSeed[kMaxElectron];   //[Electron_]
   Float_t         Electron_IEtaSeed[kMaxElectron];   //[Electron_]
   Float_t         Electron_IPhiSeed[kMaxElectron];   //[Electron_]
   Float_t         Electron_EtaCrySeed[kMaxElectron];   //[Electron_]
   Float_t         Electron_PhiCrySeed[kMaxElectron];   //[Electron_]
   UInt_t          Electron_NSCMatchedPFCandidates[kMaxElectron];   //[Electron_]
   UInt_t          Electron_SCMatchedPFCandidateIndex[kMaxElectron][10];   //[Electron_]
   UInt_t          Electron_NGsfTrackMatchedPFCandidates[kMaxElectron];   //[Electron_]
   UInt_t          Electron_GsfTrackMatchedPFCandidateIndex[kMaxElectron][10];   //[Electron_]
   Int_t           PFJet_;
   Float_t         PFJet_pt[kMaxPFJet];   //[PFJet_]
   Float_t         PFJet_eta[kMaxPFJet];   //[PFJet_]
   Float_t         PFJet_phi[kMaxPFJet];   //[PFJet_]
   Float_t         PFJet_mass[kMaxPFJet];   //[PFJet_]
   Float_t         PFJet_rawPt[kMaxPFJet];   //[PFJet_]
   Float_t         PFJet_L1JECScale[kMaxPFJet];   //[PFJet_]
   Float_t         PFJet_L2JECScale[kMaxPFJet];   //[PFJet_]
   Float_t         PFJet_L3JECScale[kMaxPFJet];   //[PFJet_]
   ULong_t         PFJet_hltMatchBits[kMaxPFJet];   //[PFJet_]
   UInt_t          PFJet_NConstituents[kMaxPFJet];   //[PFJet_]
   Float_t         PFJet_NeutralHadronFraction[kMaxPFJet];   //[PFJet_]
   Float_t         PFJet_NeutralEMFraction[kMaxPFJet];   //[PFJet_]
   Float_t         PFJet_ChargedHadronFraction[kMaxPFJet];   //[PFJet_]
   Float_t         PFJet_ChargedEMFraction[kMaxPFJet];   //[PFJet_]
   Float_t         PFJet_TrackCountingHighEffBJetTagsDisc[kMaxPFJet];   //[PFJet_]
   Float_t         PFJet_TrackCountingHighPurBJetTagsDisc[kMaxPFJet];   //[PFJet_]
   Float_t         PFJet_SoftElectronByPtBJetTagsDisc[kMaxPFJet];   //[PFJet_]
   Float_t         PFJet_SoftElectronByIP3dBJetTagsDisc[kMaxPFJet];   //[PFJet_]
   Float_t         PFJet_SoftMuonByPtBJetTagsDisc[kMaxPFJet];   //[PFJet_]
   Float_t         PFJet_SoftMuonByIP3dBJetTagsDisc[kMaxPFJet];   //[PFJet_]
   Float_t         PFJet_SoftMuonBJetTagsDisc[kMaxPFJet];   //[PFJet_]
   Float_t         PFJet_SimpleSecondaryVertexHighPurBJetTagsDisc[kMaxPFJet];   //[PFJet_]
   Float_t         PFJet_SimpleSecondaryVertexHighEffBJetTagsDisc[kMaxPFJet];   //[PFJet_]
   Float_t         PFJet_CombinedSecondaryVertexBJetTagsDisc[kMaxPFJet];   //[PFJet_]
   Float_t         PFJet_CombinedSecondaryVertexMVABJetTagsDisc[kMaxPFJet];   //[PFJet_]
   Float_t         PFJet_JetProbabilityBJetTagsDisc[kMaxPFJet];   //[PFJet_]
   Float_t         PFJet_JetBProbabilityBJetTagsDisc[kMaxPFJet];   //[PFJet_]
   Float_t         PFJet_JetArea[kMaxPFJet];   //[PFJet_]
   Int_t           PFJet_matchedPdgId[kMaxPFJet];   //[PFJet_]
   Int_t           HO_;
   Float_t         HO_pt[kMaxHO];   //[HO_]
   Float_t         HO_eta[kMaxHO];   //[HO_]
   Float_t         HO_phi[kMaxHO];   //[HO_]
   Float_t         HO_theta[kMaxHO];   //[HO_]
   Int_t           HO_charge[kMaxHO];   //[HO_]
   Int_t           GenJet_;
   Float_t         GenJet_pt[kMaxGenJet];   //[GenJet_]
   Float_t         GenJet_eta[kMaxGenJet];   //[GenJet_]
   Float_t         GenJet_phi[kMaxGenJet];   //[GenJet_]
   Float_t         GenJet_mass[kMaxGenJet];   //[GenJet_]
   Int_t           GenJet_matchedPdgId[kMaxGenJet];   //[GenJet_]
   Int_t           Muon2_;
   Float_t         Muon2_pt[kMaxMuon2];   //[Muon2_]
   Float_t         Muon2_eta[kMaxMuon2];   //[Muon2_]
   Float_t         Muon2_phi[kMaxMuon2];   //[Muon2_]
   Float_t         Muon2_pterr[kMaxMuon2];   //[Muon2_]
   Int_t           Muon2_q[kMaxMuon2];   //[Muon2_]
   UInt_t          Muon2_typeBits[kMaxMuon2];   //[Muon2_]
   UInt_t          Muon2_qualityBits[kMaxMuon2];   //[Muon2_]
   Int_t           Muon2_nValidHits[kMaxMuon2];   //[Muon2_]
   UInt_t          Muon2_nTkHits[kMaxMuon2];   //[Muon2_]
   UInt_t          Muon2_nPixHits[kMaxMuon2];   //[Muon2_]
   UInt_t          Muon2_nMatch[kMaxMuon2];   //[Muon2_]
   UInt_t          Muon2_trkLayers[kMaxMuon2];   //[Muon2_]
   Float_t         Muon2_tkNchi2[kMaxMuon2];   //[Muon2_]
   Float_t         Muon2_muNchi2[kMaxMuon2];   //[Muon2_]
   ULong_t         Muon2_hltMatchBits[kMaxMuon2];   //[Muon2_]
   Int_t           Muon2_isMCReal[kMaxMuon2];   //[Muon2_]
   Float_t         Muon2_trkIso03[kMaxMuon2];   //[Muon2_]
   Float_t         Muon2_emIso03[kMaxMuon2];   //[Muon2_]
   Float_t         Muon2_hadIso03[kMaxMuon2];   //[Muon2_]
   Float_t         Muon2_hoIso03[kMaxMuon2];   //[Muon2_]
   Float_t         Muon2_pfIso04ChargedHadron[kMaxMuon2];   //[Muon2_]
   Float_t         Muon2_pfIso04ChargedParticle[kMaxMuon2];   //[Muon2_]
   Float_t         Muon2_pfIso04NeutralHadron[kMaxMuon2];   //[Muon2_]
   Float_t         Muon2_pfIso04Photon[kMaxMuon2];   //[Muon2_]
   Float_t         Muon2_pfIso04NeutralHadronHighThreshold[kMaxMuon2];   //[Muon2_]
   Float_t         Muon2_pfIso04PhotonHighThreshold[kMaxMuon2];   //[Muon2_]
   Float_t         Muon2_pfIso04PU[kMaxMuon2];   //[Muon2_]
   Float_t         Muon2_d0[kMaxMuon2];   //[Muon2_]
   Float_t         Muon2_dz[kMaxMuon2];   //[Muon2_]
   Float_t         Muon2_ip3d[kMaxMuon2];   //[Muon2_]
   Float_t         Muon2_ip3dSig[kMaxMuon2];   //[Muon2_]
   Float_t         Muon2_ip3dBS[kMaxMuon2];   //[Muon2_]
   Float_t         Muon2_ip3dSigBS[kMaxMuon2];   //[Muon2_]
   UInt_t          Muon2_NMatchedPFCandidates[kMaxMuon2];   //[Muon2_]
   UInt_t          Muon2_MatchedPFCandidateIndex[kMaxMuon2][10];   //[Muon2_]
   Int_t           Electron2_;
   Float_t         Electron2_pt[kMaxElectron2];   //[Electron2_]
   Float_t         Electron2_eta[kMaxElectron2];   //[Electron2_]
   Float_t         Electron2_phi[kMaxElectron2];   //[Electron2_]
   Float_t         Electron2_p[kMaxElectron2];   //[Electron2_]
   Float_t         Electron2_scEt[kMaxElectron2];   //[Electron2_]
   Float_t         Electron2_scEta[kMaxElectron2];   //[Electron2_]
   Float_t         Electron2_scPhi[kMaxElectron2];   //[Electron2_]
   Int_t           Electron2_q[kMaxElectron2];   //[Electron2_]
   Bool_t          Electron2_isEcalDriven[kMaxElectron2];   //[Electron2_]
   Bool_t          Electron2_isTrackerDriven[kMaxElectron2];   //[Electron2_]
   Bool_t          Electron2_isEB[kMaxElectron2];   //[Electron2_]
   Bool_t          Electron2_isEE[kMaxElectron2];   //[Electron2_]
   Int_t           Electron2_Classification[kMaxElectron2];   //[Electron2_]
   Int_t           Electron2_isMCReal[kMaxElectron2];   //[Electron2_]
   ULong_t         Electron2_hltMatchBits[kMaxElectron2];   //[Electron2_]
   UInt_t          Electron2_l1TriggerMatchBits[kMaxElectron2];   //[Electron2_]
   Float_t         Electron2_TrackMomentumError[kMaxElectron2];   //[Electron2_]
   Int_t           Electron2_nBrem[kMaxElectron2];   //[Electron2_]
   Float_t         Electron2_fBrem[kMaxElectron2];   //[Electron2_]
   Float_t         Electron2_EOverP[kMaxElectron2];   //[Electron2_]
   Float_t         Electron2_pIn[kMaxElectron2];   //[Electron2_]
   Float_t         Electron2_ESeedClusterOverPIn[kMaxElectron2];   //[Electron2_]
   Float_t         Electron2_ESeedClusterOverPout[kMaxElectron2];   //[Electron2_]
   Float_t         Electron2_EEleClusterOverPout[kMaxElectron2];   //[Electron2_]
   Float_t         Electron2_EcalEnergy[kMaxElectron2];   //[Electron2_]
   Float_t         Electron2_EcalEnergyError[kMaxElectron2];   //[Electron2_]
   Float_t         Electron2_deltaEtaIn[kMaxElectron2];   //[Electron2_]
   Float_t         Electron2_deltaPhiIn[kMaxElectron2];   //[Electron2_]
   Float_t         Electron2_dEtaCalo[kMaxElectron2];   //[Electron2_]
   Float_t         Electron2_dPhiCalo[kMaxElectron2];   //[Electron2_]
   Float_t         Electron2_sigiEtaiEta[kMaxElectron2];   //[Electron2_]
   Float_t         Electron2_sigiPhiiPhi[kMaxElectron2];   //[Electron2_]
   Float_t         Electron2_sigiEtaiPhi[kMaxElectron2];   //[Electron2_]
   Float_t         Electron2_SCEtaWidth[kMaxElectron2];   //[Electron2_]
   Float_t         Electron2_SCPhiWidth[kMaxElectron2];   //[Electron2_]
   Float_t         Electron2_R9[kMaxElectron2];   //[Electron2_]
   Float_t         Electron2_PreShowerOverRaw[kMaxElectron2];   //[Electron2_]
   Float_t         Electron2_HoverE[kMaxElectron2];   //[Electron2_]
   Float_t         Electron2_HoverESingleTower[kMaxElectron2];   //[Electron2_]
   Float_t         Electron2_GsfTrackChi2OverNdof[kMaxElectron2];   //[Electron2_]
   Float_t         Electron2_KFTrackChi2OverNdof[kMaxElectron2];   //[Electron2_]
   Float_t         Electron2_KFTrackNHits[kMaxElectron2];   //[Electron2_]
   Float_t         Electron2_KFTrackNLayersWithMeasurement[kMaxElectron2];   //[Electron2_]
   Float_t         Electron2_SeedE1x5OverE5x5[kMaxElectron2];   //[Electron2_]
   Bool_t          Electron2_isConv[kMaxElectron2];   //[Electron2_]
   Float_t         Electron2_nExpHitsInner[kMaxElectron2];   //[Electron2_]
   Float_t         Electron2_partnerDeltaCot[kMaxElectron2];   //[Electron2_]
   Float_t         Electron2_partnerDist[kMaxElectron2];   //[Electron2_]
   Float_t         Electron2_partnerRadius[kMaxElectron2];   //[Electron2_]
   Float_t         Electron2_d0[kMaxElectron2];   //[Electron2_]
   Float_t         Electron2_d0Err[kMaxElectron2];   //[Electron2_]
   Float_t         Electron2_dz[kMaxElectron2];   //[Electron2_]
   Float_t         Electron2_ip3d[kMaxElectron2];   //[Electron2_]
   Float_t         Electron2_ip3dSig[kMaxElectron2];   //[Electron2_]
   Float_t         Electron2_ip3dBS[kMaxElectron2];   //[Electron2_]
   Float_t         Electron2_ip3dSigBS[kMaxElectron2];   //[Electron2_]
   Float_t         Electron2_trkIso03[kMaxElectron2];   //[Electron2_]
   Float_t         Electron2_emIso03[kMaxElectron2];   //[Electron2_]
   Float_t         Electron2_hadIso03[kMaxElectron2];   //[Electron2_]
   Float_t         Electron2_trkIso04[kMaxElectron2];   //[Electron2_]
   Float_t         Electron2_emIso04[kMaxElectron2];   //[Electron2_]
   Float_t         Electron2_hadIso04[kMaxElectron2];   //[Electron2_]
   Float_t         Electron2_pfIso04ChargedHadron[kMaxElectron2];   //[Electron2_]
   Float_t         Electron2_pfIso04ChargedParticle[kMaxElectron2];   //[Electron2_]
   Float_t         Electron2_pfIso04NeutralHadron[kMaxElectron2];   //[Electron2_]
   Float_t         Electron2_pfIso04Photon[kMaxElectron2];   //[Electron2_]
   Float_t         Electron2_pfIso04NeutralHadronHighThreshold[kMaxElectron2];   //[Electron2_]
   Float_t         Electron2_pfIso04PhotonHighThreshold[kMaxElectron2];   //[Electron2_]
   Float_t         Electron2_pfIso04PU[kMaxElectron2];   //[Electron2_]
   Float_t         Electron2_SCRawEnergy[kMaxElectron2];   //[Electron2_]
   Float_t         Electron2_E5x5[kMaxElectron2];   //[Electron2_]
   Float_t         Electron2_EtaSeed[kMaxElectron2];   //[Electron2_]
   Float_t         Electron2_PhiSeed[kMaxElectron2];   //[Electron2_]
   Float_t         Electron2_ESeed[kMaxElectron2];   //[Electron2_]
   Float_t         Electron2_E3x3Seed[kMaxElectron2];   //[Electron2_]
   Float_t         Electron2_E5x5Seed[kMaxElectron2];   //[Electron2_]
   Float_t         Electron2_EMaxSeed[kMaxElectron2];   //[Electron2_]
   Float_t         Electron2_E2ndSeed[kMaxElectron2];   //[Electron2_]
   Float_t         Electron2_ETopSeed[kMaxElectron2];   //[Electron2_]
   Float_t         Electron2_EBottomSeed[kMaxElectron2];   //[Electron2_]
   Float_t         Electron2_ELeftSeed[kMaxElectron2];   //[Electron2_]
   Float_t         Electron2_ERightSeed[kMaxElectron2];   //[Electron2_]
   Float_t         Electron2_E2x5MaxSeed[kMaxElectron2];   //[Electron2_]
   Float_t         Electron2_E2x5TopSeed[kMaxElectron2];   //[Electron2_]
   Float_t         Electron2_E2x5BottomSeed[kMaxElectron2];   //[Electron2_]
   Float_t         Electron2_E2x5LeftSeed[kMaxElectron2];   //[Electron2_]
   Float_t         Electron2_E2x5RightSeed[kMaxElectron2];   //[Electron2_]
   Float_t         Electron2_IEtaSeed[kMaxElectron2];   //[Electron2_]
   Float_t         Electron2_IPhiSeed[kMaxElectron2];   //[Electron2_]
   Float_t         Electron2_EtaCrySeed[kMaxElectron2];   //[Electron2_]
   Float_t         Electron2_PhiCrySeed[kMaxElectron2];   //[Electron2_]
   UInt_t          Electron2_NSCMatchedPFCandidates[kMaxElectron2];   //[Electron2_]
   UInt_t          Electron2_SCMatchedPFCandidateIndex[kMaxElectron2][10];   //[Electron2_]
   UInt_t          Electron2_NGsfTrackMatchedPFCandidates[kMaxElectron2];   //[Electron2_]
   UInt_t          Electron2_GsfTrackMatchedPFCandidateIndex[kMaxElectron2][10];   //[Electron2_]
   Int_t           PFJet2_;
   Float_t         PFJet2_pt[kMaxPFJet2];   //[PFJet2_]
   Float_t         PFJet2_eta[kMaxPFJet2];   //[PFJet2_]
   Float_t         PFJet2_phi[kMaxPFJet2];   //[PFJet2_]
   Float_t         PFJet2_mass[kMaxPFJet2];   //[PFJet2_]
   Float_t         PFJet2_rawPt[kMaxPFJet2];   //[PFJet2_]
   Float_t         PFJet2_L1JECScale[kMaxPFJet2];   //[PFJet2_]
   Float_t         PFJet2_L2JECScale[kMaxPFJet2];   //[PFJet2_]
   Float_t         PFJet2_L3JECScale[kMaxPFJet2];   //[PFJet2_]
   ULong_t         PFJet2_hltMatchBits[kMaxPFJet2];   //[PFJet2_]
   UInt_t          PFJet2_NConstituents[kMaxPFJet2];   //[PFJet2_]
   Float_t         PFJet2_NeutralHadronFraction[kMaxPFJet2];   //[PFJet2_]
   Float_t         PFJet2_NeutralEMFraction[kMaxPFJet2];   //[PFJet2_]
   Float_t         PFJet2_ChargedHadronFraction[kMaxPFJet2];   //[PFJet2_]
   Float_t         PFJet2_ChargedEMFraction[kMaxPFJet2];   //[PFJet2_]
   Float_t         PFJet2_TrackCountingHighEffBJetTagsDisc[kMaxPFJet2];   //[PFJet2_]
   Float_t         PFJet2_TrackCountingHighPurBJetTagsDisc[kMaxPFJet2];   //[PFJet2_]
   Float_t         PFJet2_SoftElectronByPtBJetTagsDisc[kMaxPFJet2];   //[PFJet2_]
   Float_t         PFJet2_SoftElectronByIP3dBJetTagsDisc[kMaxPFJet2];   //[PFJet2_]
   Float_t         PFJet2_SoftMuonByPtBJetTagsDisc[kMaxPFJet2];   //[PFJet2_]
   Float_t         PFJet2_SoftMuonByIP3dBJetTagsDisc[kMaxPFJet2];   //[PFJet2_]
   Float_t         PFJet2_SoftMuonBJetTagsDisc[kMaxPFJet2];   //[PFJet2_]
   Float_t         PFJet2_SimpleSecondaryVertexHighPurBJetTagsDisc[kMaxPFJet2];   //[PFJet2_]
   Float_t         PFJet2_SimpleSecondaryVertexHighEffBJetTagsDisc[kMaxPFJet2];   //[PFJet2_]
   Float_t         PFJet2_CombinedSecondaryVertexBJetTagsDisc[kMaxPFJet2];   //[PFJet2_]
   Float_t         PFJet2_CombinedSecondaryVertexMVABJetTagsDisc[kMaxPFJet2];   //[PFJet2_]
   Float_t         PFJet2_JetProbabilityBJetTagsDisc[kMaxPFJet2];   //[PFJet2_]
   Float_t         PFJet2_JetBProbabilityBJetTagsDisc[kMaxPFJet2];   //[PFJet2_]
   Float_t         PFJet2_JetArea[kMaxPFJet2];   //[PFJet2_]
   Int_t           PFJet2_matchedPdgId[kMaxPFJet2];   //[PFJet2_]
   Float_t         MET;
   Float_t         MET2;
   Int_t           run_num;
   Int_t           event_num;

   // List of branches
   TBranch        *b_GenParticle_;   //!
   TBranch        *b_GenParticle_pt;   //!
   TBranch        *b_GenParticle_eta;   //!
   TBranch        *b_GenParticle_phi;   //!
   TBranch        *b_GenParticle_mass;   //!
   TBranch        *b_GenParticle_pdgid;   //!
   TBranch        *b_GenParticle_status;   //!
   TBranch        *b_GenParticle_motherPdgID;   //!
   TBranch        *b_Muon_;   //!
   TBranch        *b_Muon_pt;   //!
   TBranch        *b_Muon_eta;   //!
   TBranch        *b_Muon_phi;   //!
   TBranch        *b_Muon_pterr;   //!
   TBranch        *b_Muon_q;   //!
   TBranch        *b_Muon_typeBits;   //!
   TBranch        *b_Muon_qualityBits;   //!
   TBranch        *b_Muon_nValidHits;   //!
   TBranch        *b_Muon_nTkHits;   //!
   TBranch        *b_Muon_nPixHits;   //!
   TBranch        *b_Muon_nMatch;   //!
   TBranch        *b_Muon_trkLayers;   //!
   TBranch        *b_Muon_tkNchi2;   //!
   TBranch        *b_Muon_muNchi2;   //!
   TBranch        *b_Muon_hltMatchBits;   //!
   TBranch        *b_Muon_isMCReal;   //!
   TBranch        *b_Muon_trkIso03;   //!
   TBranch        *b_Muon_emIso03;   //!
   TBranch        *b_Muon_hadIso03;   //!
   TBranch        *b_Muon_hoIso03;   //!
   TBranch        *b_Muon_pfIso04ChargedHadron;   //!
   TBranch        *b_Muon_pfIso04ChargedParticle;   //!
   TBranch        *b_Muon_pfIso04NeutralHadron;   //!
   TBranch        *b_Muon_pfIso04Photon;   //!
   TBranch        *b_Muon_pfIso04NeutralHadronHighThreshold;   //!
   TBranch        *b_Muon_pfIso04PhotonHighThreshold;   //!
   TBranch        *b_Muon_pfIso04PU;   //!
   TBranch        *b_Muon_d0;   //!
   TBranch        *b_Muon_dz;   //!
   TBranch        *b_Muon_ip3d;   //!
   TBranch        *b_Muon_ip3dSig;   //!
   TBranch        *b_Muon_ip3dBS;   //!
   TBranch        *b_Muon_ip3dSigBS;   //!
   TBranch        *b_Muon_NMatchedPFCandidates;   //!
   TBranch        *b_Muon_MatchedPFCandidateIndex;   //!
   TBranch        *b_Electron_;   //!
   TBranch        *b_Electron_pt;   //!
   TBranch        *b_Electron_eta;   //!
   TBranch        *b_Electron_phi;   //!
   TBranch        *b_Electron_p;   //!
   TBranch        *b_Electron_scEt;   //!
   TBranch        *b_Electron_scEta;   //!
   TBranch        *b_Electron_scPhi;   //!
   TBranch        *b_Electron_q;   //!
   TBranch        *b_Electron_isEcalDriven;   //!
   TBranch        *b_Electron_isTrackerDriven;   //!
   TBranch        *b_Electron_isEB;   //!
   TBranch        *b_Electron_isEE;   //!
   TBranch        *b_Electron_Classification;   //!
   TBranch        *b_Electron_isMCReal;   //!
   TBranch        *b_Electron_hltMatchBits;   //!
   TBranch        *b_Electron_l1TriggerMatchBits;   //!
   TBranch        *b_Electron_TrackMomentumError;   //!
   TBranch        *b_Electron_nBrem;   //!
   TBranch        *b_Electron_fBrem;   //!
   TBranch        *b_Electron_EOverP;   //!
   TBranch        *b_Electron_pIn;   //!
   TBranch        *b_Electron_ESeedClusterOverPIn;   //!
   TBranch        *b_Electron_ESeedClusterOverPout;   //!
   TBranch        *b_Electron_EEleClusterOverPout;   //!
   TBranch        *b_Electron_EcalEnergy;   //!
   TBranch        *b_Electron_EcalEnergyError;   //!
   TBranch        *b_Electron_deltaEtaIn;   //!
   TBranch        *b_Electron_deltaPhiIn;   //!
   TBranch        *b_Electron_dEtaCalo;   //!
   TBranch        *b_Electron_dPhiCalo;   //!
   TBranch        *b_Electron_sigiEtaiEta;   //!
   TBranch        *b_Electron_sigiPhiiPhi;   //!
   TBranch        *b_Electron_sigiEtaiPhi;   //!
   TBranch        *b_Electron_SCEtaWidth;   //!
   TBranch        *b_Electron_SCPhiWidth;   //!
   TBranch        *b_Electron_R9;   //!
   TBranch        *b_Electron_PreShowerOverRaw;   //!
   TBranch        *b_Electron_HoverE;   //!
   TBranch        *b_Electron_HoverESingleTower;   //!
   TBranch        *b_Electron_GsfTrackChi2OverNdof;   //!
   TBranch        *b_Electron_KFTrackChi2OverNdof;   //!
   TBranch        *b_Electron_KFTrackNHits;   //!
   TBranch        *b_Electron_KFTrackNLayersWithMeasurement;   //!
   TBranch        *b_Electron_SeedE1x5OverE5x5;   //!
   TBranch        *b_Electron_isConv;   //!
   TBranch        *b_Electron_nExpHitsInner;   //!
   TBranch        *b_Electron_partnerDeltaCot;   //!
   TBranch        *b_Electron_partnerDist;   //!
   TBranch        *b_Electron_partnerRadius;   //!
   TBranch        *b_Electron_d0;   //!
   TBranch        *b_Electron_d0Err;   //!
   TBranch        *b_Electron_dz;   //!
   TBranch        *b_Electron_ip3d;   //!
   TBranch        *b_Electron_ip3dSig;   //!
   TBranch        *b_Electron_ip3dBS;   //!
   TBranch        *b_Electron_ip3dSigBS;   //!
   TBranch        *b_Electron_trkIso03;   //!
   TBranch        *b_Electron_emIso03;   //!
   TBranch        *b_Electron_hadIso03;   //!
   TBranch        *b_Electron_trkIso04;   //!
   TBranch        *b_Electron_emIso04;   //!
   TBranch        *b_Electron_hadIso04;   //!
   TBranch        *b_Electron_pfIso04ChargedHadron;   //!
   TBranch        *b_Electron_pfIso04ChargedParticle;   //!
   TBranch        *b_Electron_pfIso04NeutralHadron;   //!
   TBranch        *b_Electron_pfIso04Photon;   //!
   TBranch        *b_Electron_pfIso04NeutralHadronHighThreshold;   //!
   TBranch        *b_Electron_pfIso04PhotonHighThreshold;   //!
   TBranch        *b_Electron_pfIso04PU;   //!
   TBranch        *b_Electron_SCRawEnergy;   //!
   TBranch        *b_Electron_E5x5;   //!
   TBranch        *b_Electron_EtaSeed;   //!
   TBranch        *b_Electron_PhiSeed;   //!
   TBranch        *b_Electron_ESeed;   //!
   TBranch        *b_Electron_E3x3Seed;   //!
   TBranch        *b_Electron_E5x5Seed;   //!
   TBranch        *b_Electron_EMaxSeed;   //!
   TBranch        *b_Electron_E2ndSeed;   //!
   TBranch        *b_Electron_ETopSeed;   //!
   TBranch        *b_Electron_EBottomSeed;   //!
   TBranch        *b_Electron_ELeftSeed;   //!
   TBranch        *b_Electron_ERightSeed;   //!
   TBranch        *b_Electron_E2x5MaxSeed;   //!
   TBranch        *b_Electron_E2x5TopSeed;   //!
   TBranch        *b_Electron_E2x5BottomSeed;   //!
   TBranch        *b_Electron_E2x5LeftSeed;   //!
   TBranch        *b_Electron_E2x5RightSeed;   //!
   TBranch        *b_Electron_IEtaSeed;   //!
   TBranch        *b_Electron_IPhiSeed;   //!
   TBranch        *b_Electron_EtaCrySeed;   //!
   TBranch        *b_Electron_PhiCrySeed;   //!
   TBranch        *b_Electron_NSCMatchedPFCandidates;   //!
   TBranch        *b_Electron_SCMatchedPFCandidateIndex;   //!
   TBranch        *b_Electron_NGsfTrackMatchedPFCandidates;   //!
   TBranch        *b_Electron_GsfTrackMatchedPFCandidateIndex;   //!
   TBranch        *b_PFJet_;   //!
   TBranch        *b_PFJet_pt;   //!
   TBranch        *b_PFJet_eta;   //!
   TBranch        *b_PFJet_phi;   //!
   TBranch        *b_PFJet_mass;   //!
   TBranch        *b_PFJet_rawPt;   //!
   TBranch        *b_PFJet_L1JECScale;   //!
   TBranch        *b_PFJet_L2JECScale;   //!
   TBranch        *b_PFJet_L3JECScale;   //!
   TBranch        *b_PFJet_hltMatchBits;   //!
   TBranch        *b_PFJet_NConstituents;   //!
   TBranch        *b_PFJet_NeutralHadronFraction;   //!
   TBranch        *b_PFJet_NeutralEMFraction;   //!
   TBranch        *b_PFJet_ChargedHadronFraction;   //!
   TBranch        *b_PFJet_ChargedEMFraction;   //!
   TBranch        *b_PFJet_TrackCountingHighEffBJetTagsDisc;   //!
   TBranch        *b_PFJet_TrackCountingHighPurBJetTagsDisc;   //!
   TBranch        *b_PFJet_SoftElectronByPtBJetTagsDisc;   //!
   TBranch        *b_PFJet_SoftElectronByIP3dBJetTagsDisc;   //!
   TBranch        *b_PFJet_SoftMuonByPtBJetTagsDisc;   //!
   TBranch        *b_PFJet_SoftMuonByIP3dBJetTagsDisc;   //!
   TBranch        *b_PFJet_SoftMuonBJetTagsDisc;   //!
   TBranch        *b_PFJet_SimpleSecondaryVertexHighPurBJetTagsDisc;   //!
   TBranch        *b_PFJet_SimpleSecondaryVertexHighEffBJetTagsDisc;   //!
   TBranch        *b_PFJet_CombinedSecondaryVertexBJetTagsDisc;   //!
   TBranch        *b_PFJet_CombinedSecondaryVertexMVABJetTagsDisc;   //!
   TBranch        *b_PFJet_JetProbabilityBJetTagsDisc;   //!
   TBranch        *b_PFJet_JetBProbabilityBJetTagsDisc;   //!
   TBranch        *b_PFJet_JetArea;   //!
   TBranch        *b_PFJet_matchedPdgId;   //!
   TBranch        *b_HO_;   //!
   TBranch        *b_HO_pt;   //!
   TBranch        *b_HO_eta;   //!
   TBranch        *b_HO_phi;   //!
   TBranch        *b_HO_theta;   //!
   TBranch        *b_HO_charge;   //!
   TBranch        *b_GenJet_;   //!
   TBranch        *b_GenJet_pt;   //!
   TBranch        *b_GenJet_eta;   //!
   TBranch        *b_GenJet_phi;   //!
   TBranch        *b_GenJet_mass;   //!
   TBranch        *b_GenJet_matchedPdgId;   //!
   TBranch        *b_Muon2_;   //!
   TBranch        *b_Muon2_pt;   //!
   TBranch        *b_Muon2_eta;   //!
   TBranch        *b_Muon2_phi;   //!
   TBranch        *b_Muon2_pterr;   //!
   TBranch        *b_Muon2_q;   //!
   TBranch        *b_Muon2_typeBits;   //!
   TBranch        *b_Muon2_qualityBits;   //!
   TBranch        *b_Muon2_nValidHits;   //!
   TBranch        *b_Muon2_nTkHits;   //!
   TBranch        *b_Muon2_nPixHits;   //!
   TBranch        *b_Muon2_nMatch;   //!
   TBranch        *b_Muon2_trkLayers;   //!
   TBranch        *b_Muon2_tkNchi2;   //!
   TBranch        *b_Muon2_muNchi2;   //!
   TBranch        *b_Muon2_hltMatchBits;   //!
   TBranch        *b_Muon2_isMCReal;   //!
   TBranch        *b_Muon2_trkIso03;   //!
   TBranch        *b_Muon2_emIso03;   //!
   TBranch        *b_Muon2_hadIso03;   //!
   TBranch        *b_Muon2_hoIso03;   //!
   TBranch        *b_Muon2_pfIso04ChargedHadron;   //!
   TBranch        *b_Muon2_pfIso04ChargedParticle;   //!
   TBranch        *b_Muon2_pfIso04NeutralHadron;   //!
   TBranch        *b_Muon2_pfIso04Photon;   //!
   TBranch        *b_Muon2_pfIso04NeutralHadronHighThreshold;   //!
   TBranch        *b_Muon2_pfIso04PhotonHighThreshold;   //!
   TBranch        *b_Muon2_pfIso04PU;   //!
   TBranch        *b_Muon2_d0;   //!
   TBranch        *b_Muon2_dz;   //!
   TBranch        *b_Muon2_ip3d;   //!
   TBranch        *b_Muon2_ip3dSig;   //!
   TBranch        *b_Muon2_ip3dBS;   //!
   TBranch        *b_Muon2_ip3dSigBS;   //!
   TBranch        *b_Muon2_NMatchedPFCandidates;   //!
   TBranch        *b_Muon2_MatchedPFCandidateIndex;   //!
   TBranch        *b_Electron2_;   //!
   TBranch        *b_Electron2_pt;   //!
   TBranch        *b_Electron2_eta;   //!
   TBranch        *b_Electron2_phi;   //!
   TBranch        *b_Electron2_p;   //!
   TBranch        *b_Electron2_scEt;   //!
   TBranch        *b_Electron2_scEta;   //!
   TBranch        *b_Electron2_scPhi;   //!
   TBranch        *b_Electron2_q;   //!
   TBranch        *b_Electron2_isEcalDriven;   //!
   TBranch        *b_Electron2_isTrackerDriven;   //!
   TBranch        *b_Electron2_isEB;   //!
   TBranch        *b_Electron2_isEE;   //!
   TBranch        *b_Electron2_Classification;   //!
   TBranch        *b_Electron2_isMCReal;   //!
   TBranch        *b_Electron2_hltMatchBits;   //!
   TBranch        *b_Electron2_l1TriggerMatchBits;   //!
   TBranch        *b_Electron2_TrackMomentumError;   //!
   TBranch        *b_Electron2_nBrem;   //!
   TBranch        *b_Electron2_fBrem;   //!
   TBranch        *b_Electron2_EOverP;   //!
   TBranch        *b_Electron2_pIn;   //!
   TBranch        *b_Electron2_ESeedClusterOverPIn;   //!
   TBranch        *b_Electron2_ESeedClusterOverPout;   //!
   TBranch        *b_Electron2_EEleClusterOverPout;   //!
   TBranch        *b_Electron2_EcalEnergy;   //!
   TBranch        *b_Electron2_EcalEnergyError;   //!
   TBranch        *b_Electron2_deltaEtaIn;   //!
   TBranch        *b_Electron2_deltaPhiIn;   //!
   TBranch        *b_Electron2_dEtaCalo;   //!
   TBranch        *b_Electron2_dPhiCalo;   //!
   TBranch        *b_Electron2_sigiEtaiEta;   //!
   TBranch        *b_Electron2_sigiPhiiPhi;   //!
   TBranch        *b_Electron2_sigiEtaiPhi;   //!
   TBranch        *b_Electron2_SCEtaWidth;   //!
   TBranch        *b_Electron2_SCPhiWidth;   //!
   TBranch        *b_Electron2_R9;   //!
   TBranch        *b_Electron2_PreShowerOverRaw;   //!
   TBranch        *b_Electron2_HoverE;   //!
   TBranch        *b_Electron2_HoverESingleTower;   //!
   TBranch        *b_Electron2_GsfTrackChi2OverNdof;   //!
   TBranch        *b_Electron2_KFTrackChi2OverNdof;   //!
   TBranch        *b_Electron2_KFTrackNHits;   //!
   TBranch        *b_Electron2_KFTrackNLayersWithMeasurement;   //!
   TBranch        *b_Electron2_SeedE1x5OverE5x5;   //!
   TBranch        *b_Electron2_isConv;   //!
   TBranch        *b_Electron2_nExpHitsInner;   //!
   TBranch        *b_Electron2_partnerDeltaCot;   //!
   TBranch        *b_Electron2_partnerDist;   //!
   TBranch        *b_Electron2_partnerRadius;   //!
   TBranch        *b_Electron2_d0;   //!
   TBranch        *b_Electron2_d0Err;   //!
   TBranch        *b_Electron2_dz;   //!
   TBranch        *b_Electron2_ip3d;   //!
   TBranch        *b_Electron2_ip3dSig;   //!
   TBranch        *b_Electron2_ip3dBS;   //!
   TBranch        *b_Electron2_ip3dSigBS;   //!
   TBranch        *b_Electron2_trkIso03;   //!
   TBranch        *b_Electron2_emIso03;   //!
   TBranch        *b_Electron2_hadIso03;   //!
   TBranch        *b_Electron2_trkIso04;   //!
   TBranch        *b_Electron2_emIso04;   //!
   TBranch        *b_Electron2_hadIso04;   //!
   TBranch        *b_Electron2_pfIso04ChargedHadron;   //!
   TBranch        *b_Electron2_pfIso04ChargedParticle;   //!
   TBranch        *b_Electron2_pfIso04NeutralHadron;   //!
   TBranch        *b_Electron2_pfIso04Photon;   //!
   TBranch        *b_Electron2_pfIso04NeutralHadronHighThreshold;   //!
   TBranch        *b_Electron2_pfIso04PhotonHighThreshold;   //!
   TBranch        *b_Electron2_pfIso04PU;   //!
   TBranch        *b_Electron2_SCRawEnergy;   //!
   TBranch        *b_Electron2_E5x5;   //!
   TBranch        *b_Electron2_EtaSeed;   //!
   TBranch        *b_Electron2_PhiSeed;   //!
   TBranch        *b_Electron2_ESeed;   //!
   TBranch        *b_Electron2_E3x3Seed;   //!
   TBranch        *b_Electron2_E5x5Seed;   //!
   TBranch        *b_Electron2_EMaxSeed;   //!
   TBranch        *b_Electron2_E2ndSeed;   //!
   TBranch        *b_Electron2_ETopSeed;   //!
   TBranch        *b_Electron2_EBottomSeed;   //!
   TBranch        *b_Electron2_ELeftSeed;   //!
   TBranch        *b_Electron2_ERightSeed;   //!
   TBranch        *b_Electron2_E2x5MaxSeed;   //!
   TBranch        *b_Electron2_E2x5TopSeed;   //!
   TBranch        *b_Electron2_E2x5BottomSeed;   //!
   TBranch        *b_Electron2_E2x5LeftSeed;   //!
   TBranch        *b_Electron2_E2x5RightSeed;   //!
   TBranch        *b_Electron2_IEtaSeed;   //!
   TBranch        *b_Electron2_IPhiSeed;   //!
   TBranch        *b_Electron2_EtaCrySeed;   //!
   TBranch        *b_Electron2_PhiCrySeed;   //!
   TBranch        *b_Electron2_NSCMatchedPFCandidates;   //!
   TBranch        *b_Electron2_SCMatchedPFCandidateIndex;   //!
   TBranch        *b_Electron2_NGsfTrackMatchedPFCandidates;   //!
   TBranch        *b_Electron2_GsfTrackMatchedPFCandidateIndex;   //!
   TBranch        *b_PFJet2_;   //!
   TBranch        *b_PFJet2_pt;   //!
   TBranch        *b_PFJet2_eta;   //!
   TBranch        *b_PFJet2_phi;   //!
   TBranch        *b_PFJet2_mass;   //!
   TBranch        *b_PFJet2_rawPt;   //!
   TBranch        *b_PFJet2_L1JECScale;   //!
   TBranch        *b_PFJet2_L2JECScale;   //!
   TBranch        *b_PFJet2_L3JECScale;   //!
   TBranch        *b_PFJet2_hltMatchBits;   //!
   TBranch        *b_PFJet2_NConstituents;   //!
   TBranch        *b_PFJet2_NeutralHadronFraction;   //!
   TBranch        *b_PFJet2_NeutralEMFraction;   //!
   TBranch        *b_PFJet2_ChargedHadronFraction;   //!
   TBranch        *b_PFJet2_ChargedEMFraction;   //!
   TBranch        *b_PFJet2_TrackCountingHighEffBJetTagsDisc;   //!
   TBranch        *b_PFJet2_TrackCountingHighPurBJetTagsDisc;   //!
   TBranch        *b_PFJet2_SoftElectronByPtBJetTagsDisc;   //!
   TBranch        *b_PFJet2_SoftElectronByIP3dBJetTagsDisc;   //!
   TBranch        *b_PFJet2_SoftMuonByPtBJetTagsDisc;   //!
   TBranch        *b_PFJet2_SoftMuonByIP3dBJetTagsDisc;   //!
   TBranch        *b_PFJet2_SoftMuonBJetTagsDisc;   //!
   TBranch        *b_PFJet2_SimpleSecondaryVertexHighPurBJetTagsDisc;   //!
   TBranch        *b_PFJet2_SimpleSecondaryVertexHighEffBJetTagsDisc;   //!
   TBranch        *b_PFJet2_CombinedSecondaryVertexBJetTagsDisc;   //!
   TBranch        *b_PFJet2_CombinedSecondaryVertexMVABJetTagsDisc;   //!
   TBranch        *b_PFJet2_JetProbabilityBJetTagsDisc;   //!
   TBranch        *b_PFJet2_JetBProbabilityBJetTagsDisc;   //!
   TBranch        *b_PFJet2_JetArea;   //!
   TBranch        *b_PFJet2_matchedPdgId;   //!
   TBranch        *b_MET;   //!
   TBranch        *b_MET2;   //!
   TBranch        *b_run_num;   //!
   TBranch        *b_event_num;   //!

   anal();
   virtual ~anal();
   virtual void     SetTree(TTree *tree=0);
   virtual Int_t    Cut(Long64_t entry);
   virtual Int_t    GetEntry(Long64_t entry);
   virtual Long64_t LoadTree(Long64_t entry);
   virtual void     Init(TTree *tree);
   virtual void     Loop();
   virtual void     StartLoop();
   virtual void     EndLoop();
   virtual Bool_t   Notify();
   virtual void     Show(Long64_t entry = -1);

 private:

   TFile *file;
   TTree *HO_tree;
   TTree *Event_tree;
   TTree *Jet_tree;
   TTree *Muon_tree;
   
   Int_t isMatch;
   Float_t r_muon_pt;
   Float_t r_muon_eta;
   Float_t r_muon_phi;

   Float_t r_HO_energy;
   Float_t r_HO_efrac;
   Float_t r_HO_eta;
   Float_t r_HO_phi;
   Int_t r_HO_iphi;
   Int_t r_HO_ieta;
   Int_t r_HO_abs_ieta;
   Int_t r_HO_isSignal;
   Int_t r_HO_isUse;
   Float_t r_HO_jetenergy;

   Int_t r_HO20;
   Int_t r_HO30;
   Int_t r_HO40;
   Int_t r_HO50;
   Int_t r_HO70;
   Float_t r_maxjfrac;
   Float_t r_maxHO;
   Float_t r_met;
   Float_t r_met2;
   Int_t r_nHO;
   Int_t r_njet;
   Int_t r_nHO_isSignal;
   Int_t r_nmuon;
   Int_t r_nelectron;

   TH1F *h_ho[72][21];
   TH1F *h_ho_signal[10];
   TH1F *h_ho_noise[10];

   TH1F *h_ho_muon_signal[10];
   TH1F *h_ho_muon_noise[10];
   
   TH1F *h_jet_resolution[2][20];

   Float_t r_jet_pt;
   Float_t r_jet_eta;
   Float_t r_jet_phi;
   Float_t r_jet_pt_wHO;
   Float_t r_gjet_pt;
   Float_t r_gjet_eta;
   Float_t r_gjet_phi;
   Float_t r_jet_dr;
   Int_t r_jet_HO_match;
   Float_t r_jet_HOenergy;
   
};

#endif

#ifdef anal_cxx

anal::anal(){}

void anal::SetTree(TTree *tree){

   if (tree == 0) {
     std::cout << "No input files" << std::endl;
   }
   Init(tree);

}

anal::~anal()
{
   if (!fChain) return;
   delete fChain->GetCurrentFile();
}


Int_t anal::GetEntry(Long64_t entry)
{
// Read contents of entry.
   if (!fChain) return 0;
   return fChain->GetEntry(entry);
}
Long64_t anal::LoadTree(Long64_t entry)
{
// Set the environment to read one entry
   if (!fChain) return -5;
   Long64_t centry = fChain->LoadTree(entry);
   if (centry < 0) return centry;
   if (fChain->GetTreeNumber() != fCurrent) {
      fCurrent = fChain->GetTreeNumber();
      Notify();
   }
   return centry;
}

void anal::Init(TTree *tree)
{
   // The Init() function is called when the selector needs to initialize
   // a new tree or chain. Typically here the branch addresses and branch
   // pointers of the tree will be set.
   // It is normally not necessary to make changes to the generated
   // code, but the routine can be extended by the user if needed.
   // Init() will be called many times when running on PROOF
   // (once per file to be processed).

   // Set branch addresses and branch pointers
   if (!tree) return;
   fChain = tree;
   fCurrent = -1;
   fChain->SetMakeClass(1);

   fChain->SetBranchAddress("GenParticle", &GenParticle_, &b_GenParticle_);
   fChain->SetBranchAddress("GenParticle.pt", GenParticle_pt, &b_GenParticle_pt);
   fChain->SetBranchAddress("GenParticle.eta", GenParticle_eta, &b_GenParticle_eta);
   fChain->SetBranchAddress("GenParticle.phi", GenParticle_phi, &b_GenParticle_phi);
   fChain->SetBranchAddress("GenParticle.mass", GenParticle_mass, &b_GenParticle_mass);
   fChain->SetBranchAddress("GenParticle.pdgid", GenParticle_pdgid, &b_GenParticle_pdgid);
   fChain->SetBranchAddress("GenParticle.status", GenParticle_status, &b_GenParticle_status);
   fChain->SetBranchAddress("GenParticle.motherPdgID", GenParticle_motherPdgID, &b_GenParticle_motherPdgID);
   fChain->SetBranchAddress("Muon", &Muon_, &b_Muon_);
   fChain->SetBranchAddress("Muon.pt", Muon_pt, &b_Muon_pt);
   fChain->SetBranchAddress("Muon.eta", Muon_eta, &b_Muon_eta);
   fChain->SetBranchAddress("Muon.phi", Muon_phi, &b_Muon_phi);
   fChain->SetBranchAddress("Muon.pterr", Muon_pterr, &b_Muon_pterr);
   fChain->SetBranchAddress("Muon.q", Muon_q, &b_Muon_q);
   fChain->SetBranchAddress("Muon.typeBits", Muon_typeBits, &b_Muon_typeBits);
   fChain->SetBranchAddress("Muon.qualityBits", Muon_qualityBits, &b_Muon_qualityBits);
   fChain->SetBranchAddress("Muon.nValidHits", Muon_nValidHits, &b_Muon_nValidHits);
   fChain->SetBranchAddress("Muon.nTkHits", Muon_nTkHits, &b_Muon_nTkHits);
   fChain->SetBranchAddress("Muon.nPixHits", Muon_nPixHits, &b_Muon_nPixHits);
   fChain->SetBranchAddress("Muon.nMatch", Muon_nMatch, &b_Muon_nMatch);
   fChain->SetBranchAddress("Muon.trkLayers", Muon_trkLayers, &b_Muon_trkLayers);
   fChain->SetBranchAddress("Muon.tkNchi2", Muon_tkNchi2, &b_Muon_tkNchi2);
   fChain->SetBranchAddress("Muon.muNchi2", Muon_muNchi2, &b_Muon_muNchi2);
   fChain->SetBranchAddress("Muon.hltMatchBits", Muon_hltMatchBits, &b_Muon_hltMatchBits);
   fChain->SetBranchAddress("Muon.isMCReal", Muon_isMCReal, &b_Muon_isMCReal);
   fChain->SetBranchAddress("Muon.trkIso03", Muon_trkIso03, &b_Muon_trkIso03);
   fChain->SetBranchAddress("Muon.emIso03", Muon_emIso03, &b_Muon_emIso03);
   fChain->SetBranchAddress("Muon.hadIso03", Muon_hadIso03, &b_Muon_hadIso03);
   fChain->SetBranchAddress("Muon.hoIso03", Muon_hoIso03, &b_Muon_hoIso03);
   fChain->SetBranchAddress("Muon.pfIso04ChargedHadron", Muon_pfIso04ChargedHadron, &b_Muon_pfIso04ChargedHadron);
   fChain->SetBranchAddress("Muon.pfIso04ChargedParticle", Muon_pfIso04ChargedParticle, &b_Muon_pfIso04ChargedParticle);
   fChain->SetBranchAddress("Muon.pfIso04NeutralHadron", Muon_pfIso04NeutralHadron, &b_Muon_pfIso04NeutralHadron);
   fChain->SetBranchAddress("Muon.pfIso04Photon", Muon_pfIso04Photon, &b_Muon_pfIso04Photon);
   fChain->SetBranchAddress("Muon.pfIso04NeutralHadronHighThreshold", Muon_pfIso04NeutralHadronHighThreshold, &b_Muon_pfIso04NeutralHadronHighThreshold);
   fChain->SetBranchAddress("Muon.pfIso04PhotonHighThreshold", Muon_pfIso04PhotonHighThreshold, &b_Muon_pfIso04PhotonHighThreshold);
   fChain->SetBranchAddress("Muon.pfIso04PU", Muon_pfIso04PU, &b_Muon_pfIso04PU);
   fChain->SetBranchAddress("Muon.d0", Muon_d0, &b_Muon_d0);
   fChain->SetBranchAddress("Muon.dz", Muon_dz, &b_Muon_dz);
   fChain->SetBranchAddress("Muon.ip3d", Muon_ip3d, &b_Muon_ip3d);
   fChain->SetBranchAddress("Muon.ip3dSig", Muon_ip3dSig, &b_Muon_ip3dSig);
   fChain->SetBranchAddress("Muon.ip3dBS", Muon_ip3dBS, &b_Muon_ip3dBS);
   fChain->SetBranchAddress("Muon.ip3dSigBS", Muon_ip3dSigBS, &b_Muon_ip3dSigBS);
   fChain->SetBranchAddress("Muon.NMatchedPFCandidates", Muon_NMatchedPFCandidates, &b_Muon_NMatchedPFCandidates);
   fChain->SetBranchAddress("Muon.MatchedPFCandidateIndex[10]", Muon_MatchedPFCandidateIndex, &b_Muon_MatchedPFCandidateIndex);
   fChain->SetBranchAddress("Electron", &Electron_, &b_Electron_);
   fChain->SetBranchAddress("Electron.pt", Electron_pt, &b_Electron_pt);
   fChain->SetBranchAddress("Electron.eta", Electron_eta, &b_Electron_eta);
   fChain->SetBranchAddress("Electron.phi", Electron_phi, &b_Electron_phi);
   fChain->SetBranchAddress("Electron.p", Electron_p, &b_Electron_p);
   fChain->SetBranchAddress("Electron.scEt", Electron_scEt, &b_Electron_scEt);
   fChain->SetBranchAddress("Electron.scEta", Electron_scEta, &b_Electron_scEta);
   fChain->SetBranchAddress("Electron.scPhi", Electron_scPhi, &b_Electron_scPhi);
   fChain->SetBranchAddress("Electron.q", Electron_q, &b_Electron_q);
   fChain->SetBranchAddress("Electron.isEcalDriven", Electron_isEcalDriven, &b_Electron_isEcalDriven);
   fChain->SetBranchAddress("Electron.isTrackerDriven", Electron_isTrackerDriven, &b_Electron_isTrackerDriven);
   fChain->SetBranchAddress("Electron.isEB", Electron_isEB, &b_Electron_isEB);
   fChain->SetBranchAddress("Electron.isEE", Electron_isEE, &b_Electron_isEE);
   fChain->SetBranchAddress("Electron.Classification", Electron_Classification, &b_Electron_Classification);
   fChain->SetBranchAddress("Electron.isMCReal", Electron_isMCReal, &b_Electron_isMCReal);
   fChain->SetBranchAddress("Electron.hltMatchBits", Electron_hltMatchBits, &b_Electron_hltMatchBits);
   fChain->SetBranchAddress("Electron.l1TriggerMatchBits", Electron_l1TriggerMatchBits, &b_Electron_l1TriggerMatchBits);
   fChain->SetBranchAddress("Electron.TrackMomentumError", Electron_TrackMomentumError, &b_Electron_TrackMomentumError);
   fChain->SetBranchAddress("Electron.nBrem", Electron_nBrem, &b_Electron_nBrem);
   fChain->SetBranchAddress("Electron.fBrem", Electron_fBrem, &b_Electron_fBrem);
   fChain->SetBranchAddress("Electron.EOverP", Electron_EOverP, &b_Electron_EOverP);
   fChain->SetBranchAddress("Electron.pIn", Electron_pIn, &b_Electron_pIn);
   fChain->SetBranchAddress("Electron.ESeedClusterOverPIn", Electron_ESeedClusterOverPIn, &b_Electron_ESeedClusterOverPIn);
   fChain->SetBranchAddress("Electron.ESeedClusterOverPout", Electron_ESeedClusterOverPout, &b_Electron_ESeedClusterOverPout);
   fChain->SetBranchAddress("Electron.EEleClusterOverPout", Electron_EEleClusterOverPout, &b_Electron_EEleClusterOverPout);
   fChain->SetBranchAddress("Electron.EcalEnergy", Electron_EcalEnergy, &b_Electron_EcalEnergy);
   fChain->SetBranchAddress("Electron.EcalEnergyError", Electron_EcalEnergyError, &b_Electron_EcalEnergyError);
   fChain->SetBranchAddress("Electron.deltaEtaIn", Electron_deltaEtaIn, &b_Electron_deltaEtaIn);
   fChain->SetBranchAddress("Electron.deltaPhiIn", Electron_deltaPhiIn, &b_Electron_deltaPhiIn);
   fChain->SetBranchAddress("Electron.dEtaCalo", Electron_dEtaCalo, &b_Electron_dEtaCalo);
   fChain->SetBranchAddress("Electron.dPhiCalo", Electron_dPhiCalo, &b_Electron_dPhiCalo);
   fChain->SetBranchAddress("Electron.sigiEtaiEta", Electron_sigiEtaiEta, &b_Electron_sigiEtaiEta);
   fChain->SetBranchAddress("Electron.sigiPhiiPhi", Electron_sigiPhiiPhi, &b_Electron_sigiPhiiPhi);
   fChain->SetBranchAddress("Electron.sigiEtaiPhi", Electron_sigiEtaiPhi, &b_Electron_sigiEtaiPhi);
   fChain->SetBranchAddress("Electron.SCEtaWidth", Electron_SCEtaWidth, &b_Electron_SCEtaWidth);
   fChain->SetBranchAddress("Electron.SCPhiWidth", Electron_SCPhiWidth, &b_Electron_SCPhiWidth);
   fChain->SetBranchAddress("Electron.R9", Electron_R9, &b_Electron_R9);
   fChain->SetBranchAddress("Electron.PreShowerOverRaw", Electron_PreShowerOverRaw, &b_Electron_PreShowerOverRaw);
   fChain->SetBranchAddress("Electron.HoverE", Electron_HoverE, &b_Electron_HoverE);
   fChain->SetBranchAddress("Electron.HoverESingleTower", Electron_HoverESingleTower, &b_Electron_HoverESingleTower);
   fChain->SetBranchAddress("Electron.GsfTrackChi2OverNdof", Electron_GsfTrackChi2OverNdof, &b_Electron_GsfTrackChi2OverNdof);
   fChain->SetBranchAddress("Electron.KFTrackChi2OverNdof", Electron_KFTrackChi2OverNdof, &b_Electron_KFTrackChi2OverNdof);
   fChain->SetBranchAddress("Electron.KFTrackNHits", Electron_KFTrackNHits, &b_Electron_KFTrackNHits);
   fChain->SetBranchAddress("Electron.KFTrackNLayersWithMeasurement", Electron_KFTrackNLayersWithMeasurement, &b_Electron_KFTrackNLayersWithMeasurement);
   fChain->SetBranchAddress("Electron.SeedE1x5OverE5x5", Electron_SeedE1x5OverE5x5, &b_Electron_SeedE1x5OverE5x5);
   fChain->SetBranchAddress("Electron.isConv", Electron_isConv, &b_Electron_isConv);
   fChain->SetBranchAddress("Electron.nExpHitsInner", Electron_nExpHitsInner, &b_Electron_nExpHitsInner);
   fChain->SetBranchAddress("Electron.partnerDeltaCot", Electron_partnerDeltaCot, &b_Electron_partnerDeltaCot);
   fChain->SetBranchAddress("Electron.partnerDist", Electron_partnerDist, &b_Electron_partnerDist);
   fChain->SetBranchAddress("Electron.partnerRadius", Electron_partnerRadius, &b_Electron_partnerRadius);
   fChain->SetBranchAddress("Electron.d0", Electron_d0, &b_Electron_d0);
   fChain->SetBranchAddress("Electron.d0Err", Electron_d0Err, &b_Electron_d0Err);
   fChain->SetBranchAddress("Electron.dz", Electron_dz, &b_Electron_dz);
   fChain->SetBranchAddress("Electron.ip3d", Electron_ip3d, &b_Electron_ip3d);
   fChain->SetBranchAddress("Electron.ip3dSig", Electron_ip3dSig, &b_Electron_ip3dSig);
   fChain->SetBranchAddress("Electron.ip3dBS", Electron_ip3dBS, &b_Electron_ip3dBS);
   fChain->SetBranchAddress("Electron.ip3dSigBS", Electron_ip3dSigBS, &b_Electron_ip3dSigBS);
   fChain->SetBranchAddress("Electron.trkIso03", Electron_trkIso03, &b_Electron_trkIso03);
   fChain->SetBranchAddress("Electron.emIso03", Electron_emIso03, &b_Electron_emIso03);
   fChain->SetBranchAddress("Electron.hadIso03", Electron_hadIso03, &b_Electron_hadIso03);
   fChain->SetBranchAddress("Electron.trkIso04", Electron_trkIso04, &b_Electron_trkIso04);
   fChain->SetBranchAddress("Electron.emIso04", Electron_emIso04, &b_Electron_emIso04);
   fChain->SetBranchAddress("Electron.hadIso04", Electron_hadIso04, &b_Electron_hadIso04);
   fChain->SetBranchAddress("Electron.pfIso04ChargedHadron", Electron_pfIso04ChargedHadron, &b_Electron_pfIso04ChargedHadron);
   fChain->SetBranchAddress("Electron.pfIso04ChargedParticle", Electron_pfIso04ChargedParticle, &b_Electron_pfIso04ChargedParticle);
   fChain->SetBranchAddress("Electron.pfIso04NeutralHadron", Electron_pfIso04NeutralHadron, &b_Electron_pfIso04NeutralHadron);
   fChain->SetBranchAddress("Electron.pfIso04Photon", Electron_pfIso04Photon, &b_Electron_pfIso04Photon);
   fChain->SetBranchAddress("Electron.pfIso04NeutralHadronHighThreshold", Electron_pfIso04NeutralHadronHighThreshold, &b_Electron_pfIso04NeutralHadronHighThreshold);
   fChain->SetBranchAddress("Electron.pfIso04PhotonHighThreshold", Electron_pfIso04PhotonHighThreshold, &b_Electron_pfIso04PhotonHighThreshold);
   fChain->SetBranchAddress("Electron.pfIso04PU", Electron_pfIso04PU, &b_Electron_pfIso04PU);
   fChain->SetBranchAddress("Electron.SCRawEnergy", Electron_SCRawEnergy, &b_Electron_SCRawEnergy);
   fChain->SetBranchAddress("Electron.E5x5", Electron_E5x5, &b_Electron_E5x5);
   fChain->SetBranchAddress("Electron.EtaSeed", Electron_EtaSeed, &b_Electron_EtaSeed);
   fChain->SetBranchAddress("Electron.PhiSeed", Electron_PhiSeed, &b_Electron_PhiSeed);
   fChain->SetBranchAddress("Electron.ESeed", Electron_ESeed, &b_Electron_ESeed);
   fChain->SetBranchAddress("Electron.E3x3Seed", Electron_E3x3Seed, &b_Electron_E3x3Seed);
   fChain->SetBranchAddress("Electron.E5x5Seed", Electron_E5x5Seed, &b_Electron_E5x5Seed);
   fChain->SetBranchAddress("Electron.EMaxSeed", Electron_EMaxSeed, &b_Electron_EMaxSeed);
   fChain->SetBranchAddress("Electron.E2ndSeed", Electron_E2ndSeed, &b_Electron_E2ndSeed);
   fChain->SetBranchAddress("Electron.ETopSeed", Electron_ETopSeed, &b_Electron_ETopSeed);
   fChain->SetBranchAddress("Electron.EBottomSeed", Electron_EBottomSeed, &b_Electron_EBottomSeed);
   fChain->SetBranchAddress("Electron.ELeftSeed", Electron_ELeftSeed, &b_Electron_ELeftSeed);
   fChain->SetBranchAddress("Electron.ERightSeed", Electron_ERightSeed, &b_Electron_ERightSeed);
   fChain->SetBranchAddress("Electron.E2x5MaxSeed", Electron_E2x5MaxSeed, &b_Electron_E2x5MaxSeed);
   fChain->SetBranchAddress("Electron.E2x5TopSeed", Electron_E2x5TopSeed, &b_Electron_E2x5TopSeed);
   fChain->SetBranchAddress("Electron.E2x5BottomSeed", Electron_E2x5BottomSeed, &b_Electron_E2x5BottomSeed);
   fChain->SetBranchAddress("Electron.E2x5LeftSeed", Electron_E2x5LeftSeed, &b_Electron_E2x5LeftSeed);
   fChain->SetBranchAddress("Electron.E2x5RightSeed", Electron_E2x5RightSeed, &b_Electron_E2x5RightSeed);
   fChain->SetBranchAddress("Electron.IEtaSeed", Electron_IEtaSeed, &b_Electron_IEtaSeed);
   fChain->SetBranchAddress("Electron.IPhiSeed", Electron_IPhiSeed, &b_Electron_IPhiSeed);
   fChain->SetBranchAddress("Electron.EtaCrySeed", Electron_EtaCrySeed, &b_Electron_EtaCrySeed);
   fChain->SetBranchAddress("Electron.PhiCrySeed", Electron_PhiCrySeed, &b_Electron_PhiCrySeed);
   fChain->SetBranchAddress("Electron.NSCMatchedPFCandidates", Electron_NSCMatchedPFCandidates, &b_Electron_NSCMatchedPFCandidates);
   fChain->SetBranchAddress("Electron.SCMatchedPFCandidateIndex[10]", Electron_SCMatchedPFCandidateIndex, &b_Electron_SCMatchedPFCandidateIndex);
   fChain->SetBranchAddress("Electron.NGsfTrackMatchedPFCandidates", Electron_NGsfTrackMatchedPFCandidates, &b_Electron_NGsfTrackMatchedPFCandidates);
   fChain->SetBranchAddress("Electron.GsfTrackMatchedPFCandidateIndex[10]", Electron_GsfTrackMatchedPFCandidateIndex, &b_Electron_GsfTrackMatchedPFCandidateIndex);
   fChain->SetBranchAddress("PFJet", &PFJet_, &b_PFJet_);
   fChain->SetBranchAddress("PFJet.pt", PFJet_pt, &b_PFJet_pt);
   fChain->SetBranchAddress("PFJet.eta", PFJet_eta, &b_PFJet_eta);
   fChain->SetBranchAddress("PFJet.phi", PFJet_phi, &b_PFJet_phi);
   fChain->SetBranchAddress("PFJet.mass", PFJet_mass, &b_PFJet_mass);
   fChain->SetBranchAddress("PFJet.rawPt", PFJet_rawPt, &b_PFJet_rawPt);
   fChain->SetBranchAddress("PFJet.L1JECScale", PFJet_L1JECScale, &b_PFJet_L1JECScale);
   fChain->SetBranchAddress("PFJet.L2JECScale", PFJet_L2JECScale, &b_PFJet_L2JECScale);
   fChain->SetBranchAddress("PFJet.L3JECScale", PFJet_L3JECScale, &b_PFJet_L3JECScale);
   fChain->SetBranchAddress("PFJet.hltMatchBits", PFJet_hltMatchBits, &b_PFJet_hltMatchBits);
   fChain->SetBranchAddress("PFJet.NConstituents", PFJet_NConstituents, &b_PFJet_NConstituents);
   fChain->SetBranchAddress("PFJet.NeutralHadronFraction", PFJet_NeutralHadronFraction, &b_PFJet_NeutralHadronFraction);
   fChain->SetBranchAddress("PFJet.NeutralEMFraction", PFJet_NeutralEMFraction, &b_PFJet_NeutralEMFraction);
   fChain->SetBranchAddress("PFJet.ChargedHadronFraction", PFJet_ChargedHadronFraction, &b_PFJet_ChargedHadronFraction);
   fChain->SetBranchAddress("PFJet.ChargedEMFraction", PFJet_ChargedEMFraction, &b_PFJet_ChargedEMFraction);
   fChain->SetBranchAddress("PFJet.TrackCountingHighEffBJetTagsDisc", PFJet_TrackCountingHighEffBJetTagsDisc, &b_PFJet_TrackCountingHighEffBJetTagsDisc);
   fChain->SetBranchAddress("PFJet.TrackCountingHighPurBJetTagsDisc", PFJet_TrackCountingHighPurBJetTagsDisc, &b_PFJet_TrackCountingHighPurBJetTagsDisc);
   fChain->SetBranchAddress("PFJet.SoftElectronByPtBJetTagsDisc", PFJet_SoftElectronByPtBJetTagsDisc, &b_PFJet_SoftElectronByPtBJetTagsDisc);
   fChain->SetBranchAddress("PFJet.SoftElectronByIP3dBJetTagsDisc", PFJet_SoftElectronByIP3dBJetTagsDisc, &b_PFJet_SoftElectronByIP3dBJetTagsDisc);
   fChain->SetBranchAddress("PFJet.SoftMuonByPtBJetTagsDisc", PFJet_SoftMuonByPtBJetTagsDisc, &b_PFJet_SoftMuonByPtBJetTagsDisc);
   fChain->SetBranchAddress("PFJet.SoftMuonByIP3dBJetTagsDisc", PFJet_SoftMuonByIP3dBJetTagsDisc, &b_PFJet_SoftMuonByIP3dBJetTagsDisc);
   fChain->SetBranchAddress("PFJet.SoftMuonBJetTagsDisc", PFJet_SoftMuonBJetTagsDisc, &b_PFJet_SoftMuonBJetTagsDisc);
   fChain->SetBranchAddress("PFJet.SimpleSecondaryVertexHighPurBJetTagsDisc", PFJet_SimpleSecondaryVertexHighPurBJetTagsDisc, &b_PFJet_SimpleSecondaryVertexHighPurBJetTagsDisc);
   fChain->SetBranchAddress("PFJet.SimpleSecondaryVertexHighEffBJetTagsDisc", PFJet_SimpleSecondaryVertexHighEffBJetTagsDisc, &b_PFJet_SimpleSecondaryVertexHighEffBJetTagsDisc);
   fChain->SetBranchAddress("PFJet.CombinedSecondaryVertexBJetTagsDisc", PFJet_CombinedSecondaryVertexBJetTagsDisc, &b_PFJet_CombinedSecondaryVertexBJetTagsDisc);
   fChain->SetBranchAddress("PFJet.CombinedSecondaryVertexMVABJetTagsDisc", PFJet_CombinedSecondaryVertexMVABJetTagsDisc, &b_PFJet_CombinedSecondaryVertexMVABJetTagsDisc);
   fChain->SetBranchAddress("PFJet.JetProbabilityBJetTagsDisc", PFJet_JetProbabilityBJetTagsDisc, &b_PFJet_JetProbabilityBJetTagsDisc);
   fChain->SetBranchAddress("PFJet.JetBProbabilityBJetTagsDisc", PFJet_JetBProbabilityBJetTagsDisc, &b_PFJet_JetBProbabilityBJetTagsDisc);
   fChain->SetBranchAddress("PFJet.JetArea", PFJet_JetArea, &b_PFJet_JetArea);
   fChain->SetBranchAddress("PFJet.matchedPdgId", PFJet_matchedPdgId, &b_PFJet_matchedPdgId);
   fChain->SetBranchAddress("HO", &HO_, &b_HO_);
   fChain->SetBranchAddress("HO.pt", HO_pt, &b_HO_pt);
   fChain->SetBranchAddress("HO.eta", HO_eta, &b_HO_eta);
   fChain->SetBranchAddress("HO.phi", HO_phi, &b_HO_phi);
   fChain->SetBranchAddress("HO.theta", HO_theta, &b_HO_theta);
   fChain->SetBranchAddress("HO.charge", HO_charge, &b_HO_charge);
   fChain->SetBranchAddress("GenJet", &GenJet_, &b_GenJet_);
   fChain->SetBranchAddress("GenJet.pt", GenJet_pt, &b_GenJet_pt);
   fChain->SetBranchAddress("GenJet.eta", GenJet_eta, &b_GenJet_eta);
   fChain->SetBranchAddress("GenJet.phi", GenJet_phi, &b_GenJet_phi);
   fChain->SetBranchAddress("GenJet.mass", GenJet_mass, &b_GenJet_mass);
   fChain->SetBranchAddress("GenJet.matchedPdgId", GenJet_matchedPdgId, &b_GenJet_matchedPdgId);
   fChain->SetBranchAddress("Muon2", &Muon2_, &b_Muon2_);
   fChain->SetBranchAddress("Muon2.pt", Muon2_pt, &b_Muon2_pt);
   fChain->SetBranchAddress("Muon2.eta", Muon2_eta, &b_Muon2_eta);
   fChain->SetBranchAddress("Muon2.phi", Muon2_phi, &b_Muon2_phi);
   fChain->SetBranchAddress("Muon2.pterr", Muon2_pterr, &b_Muon2_pterr);
   fChain->SetBranchAddress("Muon2.q", Muon2_q, &b_Muon2_q);
   fChain->SetBranchAddress("Muon2.typeBits", Muon2_typeBits, &b_Muon2_typeBits);
   fChain->SetBranchAddress("Muon2.qualityBits", Muon2_qualityBits, &b_Muon2_qualityBits);
   fChain->SetBranchAddress("Muon2.nValidHits", Muon2_nValidHits, &b_Muon2_nValidHits);
   fChain->SetBranchAddress("Muon2.nTkHits", Muon2_nTkHits, &b_Muon2_nTkHits);
   fChain->SetBranchAddress("Muon2.nPixHits", Muon2_nPixHits, &b_Muon2_nPixHits);
   fChain->SetBranchAddress("Muon2.nMatch", Muon2_nMatch, &b_Muon2_nMatch);
   fChain->SetBranchAddress("Muon2.trkLayers", Muon2_trkLayers, &b_Muon2_trkLayers);
   fChain->SetBranchAddress("Muon2.tkNchi2", Muon2_tkNchi2, &b_Muon2_tkNchi2);
   fChain->SetBranchAddress("Muon2.muNchi2", Muon2_muNchi2, &b_Muon2_muNchi2);
   fChain->SetBranchAddress("Muon2.hltMatchBits", Muon2_hltMatchBits, &b_Muon2_hltMatchBits);
   fChain->SetBranchAddress("Muon2.isMCReal", Muon2_isMCReal, &b_Muon2_isMCReal);
   fChain->SetBranchAddress("Muon2.trkIso03", Muon2_trkIso03, &b_Muon2_trkIso03);
   fChain->SetBranchAddress("Muon2.emIso03", Muon2_emIso03, &b_Muon2_emIso03);
   fChain->SetBranchAddress("Muon2.hadIso03", Muon2_hadIso03, &b_Muon2_hadIso03);
   fChain->SetBranchAddress("Muon2.hoIso03", Muon2_hoIso03, &b_Muon2_hoIso03);
   fChain->SetBranchAddress("Muon2.pfIso04ChargedHadron", Muon2_pfIso04ChargedHadron, &b_Muon2_pfIso04ChargedHadron);
   fChain->SetBranchAddress("Muon2.pfIso04ChargedParticle", Muon2_pfIso04ChargedParticle, &b_Muon2_pfIso04ChargedParticle);
   fChain->SetBranchAddress("Muon2.pfIso04NeutralHadron", Muon2_pfIso04NeutralHadron, &b_Muon2_pfIso04NeutralHadron);
   fChain->SetBranchAddress("Muon2.pfIso04Photon", Muon2_pfIso04Photon, &b_Muon2_pfIso04Photon);
   fChain->SetBranchAddress("Muon2.pfIso04NeutralHadronHighThreshold", Muon2_pfIso04NeutralHadronHighThreshold, &b_Muon2_pfIso04NeutralHadronHighThreshold);
   fChain->SetBranchAddress("Muon2.pfIso04PhotonHighThreshold", Muon2_pfIso04PhotonHighThreshold, &b_Muon2_pfIso04PhotonHighThreshold);
   fChain->SetBranchAddress("Muon2.pfIso04PU", Muon2_pfIso04PU, &b_Muon2_pfIso04PU);
   fChain->SetBranchAddress("Muon2.d0", Muon2_d0, &b_Muon2_d0);
   fChain->SetBranchAddress("Muon2.dz", Muon2_dz, &b_Muon2_dz);
   fChain->SetBranchAddress("Muon2.ip3d", Muon2_ip3d, &b_Muon2_ip3d);
   fChain->SetBranchAddress("Muon2.ip3dSig", Muon2_ip3dSig, &b_Muon2_ip3dSig);
   fChain->SetBranchAddress("Muon2.ip3dBS", Muon2_ip3dBS, &b_Muon2_ip3dBS);
   fChain->SetBranchAddress("Muon2.ip3dSigBS", Muon2_ip3dSigBS, &b_Muon2_ip3dSigBS);
   fChain->SetBranchAddress("Muon2.NMatchedPFCandidates", Muon2_NMatchedPFCandidates, &b_Muon2_NMatchedPFCandidates);
   fChain->SetBranchAddress("Muon2.MatchedPFCandidateIndex[10]", Muon2_MatchedPFCandidateIndex, &b_Muon2_MatchedPFCandidateIndex);
   fChain->SetBranchAddress("Electron2", &Electron2_, &b_Electron2_);
   fChain->SetBranchAddress("Electron2.pt", Electron2_pt, &b_Electron2_pt);
   fChain->SetBranchAddress("Electron2.eta", Electron2_eta, &b_Electron2_eta);
   fChain->SetBranchAddress("Electron2.phi", Electron2_phi, &b_Electron2_phi);
   fChain->SetBranchAddress("Electron2.p", Electron2_p, &b_Electron2_p);
   fChain->SetBranchAddress("Electron2.scEt", Electron2_scEt, &b_Electron2_scEt);
   fChain->SetBranchAddress("Electron2.scEta", Electron2_scEta, &b_Electron2_scEta);
   fChain->SetBranchAddress("Electron2.scPhi", Electron2_scPhi, &b_Electron2_scPhi);
   fChain->SetBranchAddress("Electron2.q", Electron2_q, &b_Electron2_q);
   fChain->SetBranchAddress("Electron2.isEcalDriven", Electron2_isEcalDriven, &b_Electron2_isEcalDriven);
   fChain->SetBranchAddress("Electron2.isTrackerDriven", Electron2_isTrackerDriven, &b_Electron2_isTrackerDriven);
   fChain->SetBranchAddress("Electron2.isEB", Electron2_isEB, &b_Electron2_isEB);
   fChain->SetBranchAddress("Electron2.isEE", Electron2_isEE, &b_Electron2_isEE);
   fChain->SetBranchAddress("Electron2.Classification", Electron2_Classification, &b_Electron2_Classification);
   fChain->SetBranchAddress("Electron2.isMCReal", Electron2_isMCReal, &b_Electron2_isMCReal);
   fChain->SetBranchAddress("Electron2.hltMatchBits", Electron2_hltMatchBits, &b_Electron2_hltMatchBits);
   fChain->SetBranchAddress("Electron2.l1TriggerMatchBits", Electron2_l1TriggerMatchBits, &b_Electron2_l1TriggerMatchBits);
   fChain->SetBranchAddress("Electron2.TrackMomentumError", Electron2_TrackMomentumError, &b_Electron2_TrackMomentumError);
   fChain->SetBranchAddress("Electron2.nBrem", Electron2_nBrem, &b_Electron2_nBrem);
   fChain->SetBranchAddress("Electron2.fBrem", Electron2_fBrem, &b_Electron2_fBrem);
   fChain->SetBranchAddress("Electron2.EOverP", Electron2_EOverP, &b_Electron2_EOverP);
   fChain->SetBranchAddress("Electron2.pIn", Electron2_pIn, &b_Electron2_pIn);
   fChain->SetBranchAddress("Electron2.ESeedClusterOverPIn", Electron2_ESeedClusterOverPIn, &b_Electron2_ESeedClusterOverPIn);
   fChain->SetBranchAddress("Electron2.ESeedClusterOverPout", Electron2_ESeedClusterOverPout, &b_Electron2_ESeedClusterOverPout);
   fChain->SetBranchAddress("Electron2.EEleClusterOverPout", Electron2_EEleClusterOverPout, &b_Electron2_EEleClusterOverPout);
   fChain->SetBranchAddress("Electron2.EcalEnergy", Electron2_EcalEnergy, &b_Electron2_EcalEnergy);
   fChain->SetBranchAddress("Electron2.EcalEnergyError", Electron2_EcalEnergyError, &b_Electron2_EcalEnergyError);
   fChain->SetBranchAddress("Electron2.deltaEtaIn", Electron2_deltaEtaIn, &b_Electron2_deltaEtaIn);
   fChain->SetBranchAddress("Electron2.deltaPhiIn", Electron2_deltaPhiIn, &b_Electron2_deltaPhiIn);
   fChain->SetBranchAddress("Electron2.dEtaCalo", Electron2_dEtaCalo, &b_Electron2_dEtaCalo);
   fChain->SetBranchAddress("Electron2.dPhiCalo", Electron2_dPhiCalo, &b_Electron2_dPhiCalo);
   fChain->SetBranchAddress("Electron2.sigiEtaiEta", Electron2_sigiEtaiEta, &b_Electron2_sigiEtaiEta);
   fChain->SetBranchAddress("Electron2.sigiPhiiPhi", Electron2_sigiPhiiPhi, &b_Electron2_sigiPhiiPhi);
   fChain->SetBranchAddress("Electron2.sigiEtaiPhi", Electron2_sigiEtaiPhi, &b_Electron2_sigiEtaiPhi);
   fChain->SetBranchAddress("Electron2.SCEtaWidth", Electron2_SCEtaWidth, &b_Electron2_SCEtaWidth);
   fChain->SetBranchAddress("Electron2.SCPhiWidth", Electron2_SCPhiWidth, &b_Electron2_SCPhiWidth);
   fChain->SetBranchAddress("Electron2.R9", Electron2_R9, &b_Electron2_R9);
   fChain->SetBranchAddress("Electron2.PreShowerOverRaw", Electron2_PreShowerOverRaw, &b_Electron2_PreShowerOverRaw);
   fChain->SetBranchAddress("Electron2.HoverE", Electron2_HoverE, &b_Electron2_HoverE);
   fChain->SetBranchAddress("Electron2.HoverESingleTower", Electron2_HoverESingleTower, &b_Electron2_HoverESingleTower);
   fChain->SetBranchAddress("Electron2.GsfTrackChi2OverNdof", Electron2_GsfTrackChi2OverNdof, &b_Electron2_GsfTrackChi2OverNdof);
   fChain->SetBranchAddress("Electron2.KFTrackChi2OverNdof", Electron2_KFTrackChi2OverNdof, &b_Electron2_KFTrackChi2OverNdof);
   fChain->SetBranchAddress("Electron2.KFTrackNHits", Electron2_KFTrackNHits, &b_Electron2_KFTrackNHits);
   fChain->SetBranchAddress("Electron2.KFTrackNLayersWithMeasurement", Electron2_KFTrackNLayersWithMeasurement, &b_Electron2_KFTrackNLayersWithMeasurement);
   fChain->SetBranchAddress("Electron2.SeedE1x5OverE5x5", Electron2_SeedE1x5OverE5x5, &b_Electron2_SeedE1x5OverE5x5);
   fChain->SetBranchAddress("Electron2.isConv", Electron2_isConv, &b_Electron2_isConv);
   fChain->SetBranchAddress("Electron2.nExpHitsInner", Electron2_nExpHitsInner, &b_Electron2_nExpHitsInner);
   fChain->SetBranchAddress("Electron2.partnerDeltaCot", Electron2_partnerDeltaCot, &b_Electron2_partnerDeltaCot);
   fChain->SetBranchAddress("Electron2.partnerDist", Electron2_partnerDist, &b_Electron2_partnerDist);
   fChain->SetBranchAddress("Electron2.partnerRadius", Electron2_partnerRadius, &b_Electron2_partnerRadius);
   fChain->SetBranchAddress("Electron2.d0", Electron2_d0, &b_Electron2_d0);
   fChain->SetBranchAddress("Electron2.d0Err", Electron2_d0Err, &b_Electron2_d0Err);
   fChain->SetBranchAddress("Electron2.dz", Electron2_dz, &b_Electron2_dz);
   fChain->SetBranchAddress("Electron2.ip3d", Electron2_ip3d, &b_Electron2_ip3d);
   fChain->SetBranchAddress("Electron2.ip3dSig", Electron2_ip3dSig, &b_Electron2_ip3dSig);
   fChain->SetBranchAddress("Electron2.ip3dBS", Electron2_ip3dBS, &b_Electron2_ip3dBS);
   fChain->SetBranchAddress("Electron2.ip3dSigBS", Electron2_ip3dSigBS, &b_Electron2_ip3dSigBS);
   fChain->SetBranchAddress("Electron2.trkIso03", Electron2_trkIso03, &b_Electron2_trkIso03);
   fChain->SetBranchAddress("Electron2.emIso03", Electron2_emIso03, &b_Electron2_emIso03);
   fChain->SetBranchAddress("Electron2.hadIso03", Electron2_hadIso03, &b_Electron2_hadIso03);
   fChain->SetBranchAddress("Electron2.trkIso04", Electron2_trkIso04, &b_Electron2_trkIso04);
   fChain->SetBranchAddress("Electron2.emIso04", Electron2_emIso04, &b_Electron2_emIso04);
   fChain->SetBranchAddress("Electron2.hadIso04", Electron2_hadIso04, &b_Electron2_hadIso04);
   fChain->SetBranchAddress("Electron2.pfIso04ChargedHadron", Electron2_pfIso04ChargedHadron, &b_Electron2_pfIso04ChargedHadron);
   fChain->SetBranchAddress("Electron2.pfIso04ChargedParticle", Electron2_pfIso04ChargedParticle, &b_Electron2_pfIso04ChargedParticle);
   fChain->SetBranchAddress("Electron2.pfIso04NeutralHadron", Electron2_pfIso04NeutralHadron, &b_Electron2_pfIso04NeutralHadron);
   fChain->SetBranchAddress("Electron2.pfIso04Photon", Electron2_pfIso04Photon, &b_Electron2_pfIso04Photon);
   fChain->SetBranchAddress("Electron2.pfIso04NeutralHadronHighThreshold", Electron2_pfIso04NeutralHadronHighThreshold, &b_Electron2_pfIso04NeutralHadronHighThreshold);
   fChain->SetBranchAddress("Electron2.pfIso04PhotonHighThreshold", Electron2_pfIso04PhotonHighThreshold, &b_Electron2_pfIso04PhotonHighThreshold);
   fChain->SetBranchAddress("Electron2.pfIso04PU", Electron2_pfIso04PU, &b_Electron2_pfIso04PU);
   fChain->SetBranchAddress("Electron2.SCRawEnergy", Electron2_SCRawEnergy, &b_Electron2_SCRawEnergy);
   fChain->SetBranchAddress("Electron2.E5x5", Electron2_E5x5, &b_Electron2_E5x5);
   fChain->SetBranchAddress("Electron2.EtaSeed", Electron2_EtaSeed, &b_Electron2_EtaSeed);
   fChain->SetBranchAddress("Electron2.PhiSeed", Electron2_PhiSeed, &b_Electron2_PhiSeed);
   fChain->SetBranchAddress("Electron2.ESeed", Electron2_ESeed, &b_Electron2_ESeed);
   fChain->SetBranchAddress("Electron2.E3x3Seed", Electron2_E3x3Seed, &b_Electron2_E3x3Seed);
   fChain->SetBranchAddress("Electron2.E5x5Seed", Electron2_E5x5Seed, &b_Electron2_E5x5Seed);
   fChain->SetBranchAddress("Electron2.EMaxSeed", Electron2_EMaxSeed, &b_Electron2_EMaxSeed);
   fChain->SetBranchAddress("Electron2.E2ndSeed", Electron2_E2ndSeed, &b_Electron2_E2ndSeed);
   fChain->SetBranchAddress("Electron2.ETopSeed", Electron2_ETopSeed, &b_Electron2_ETopSeed);
   fChain->SetBranchAddress("Electron2.EBottomSeed", Electron2_EBottomSeed, &b_Electron2_EBottomSeed);
   fChain->SetBranchAddress("Electron2.ELeftSeed", Electron2_ELeftSeed, &b_Electron2_ELeftSeed);
   fChain->SetBranchAddress("Electron2.ERightSeed", Electron2_ERightSeed, &b_Electron2_ERightSeed);
   fChain->SetBranchAddress("Electron2.E2x5MaxSeed", Electron2_E2x5MaxSeed, &b_Electron2_E2x5MaxSeed);
   fChain->SetBranchAddress("Electron2.E2x5TopSeed", Electron2_E2x5TopSeed, &b_Electron2_E2x5TopSeed);
   fChain->SetBranchAddress("Electron2.E2x5BottomSeed", Electron2_E2x5BottomSeed, &b_Electron2_E2x5BottomSeed);
   fChain->SetBranchAddress("Electron2.E2x5LeftSeed", Electron2_E2x5LeftSeed, &b_Electron2_E2x5LeftSeed);
   fChain->SetBranchAddress("Electron2.E2x5RightSeed", Electron2_E2x5RightSeed, &b_Electron2_E2x5RightSeed);
   fChain->SetBranchAddress("Electron2.IEtaSeed", Electron2_IEtaSeed, &b_Electron2_IEtaSeed);
   fChain->SetBranchAddress("Electron2.IPhiSeed", Electron2_IPhiSeed, &b_Electron2_IPhiSeed);
   fChain->SetBranchAddress("Electron2.EtaCrySeed", Electron2_EtaCrySeed, &b_Electron2_EtaCrySeed);
   fChain->SetBranchAddress("Electron2.PhiCrySeed", Electron2_PhiCrySeed, &b_Electron2_PhiCrySeed);
   fChain->SetBranchAddress("Electron2.NSCMatchedPFCandidates", Electron2_NSCMatchedPFCandidates, &b_Electron2_NSCMatchedPFCandidates);
   fChain->SetBranchAddress("Electron2.SCMatchedPFCandidateIndex[10]", Electron2_SCMatchedPFCandidateIndex, &b_Electron2_SCMatchedPFCandidateIndex);
   fChain->SetBranchAddress("Electron2.NGsfTrackMatchedPFCandidates", Electron2_NGsfTrackMatchedPFCandidates, &b_Electron2_NGsfTrackMatchedPFCandidates);
   fChain->SetBranchAddress("Electron2.GsfTrackMatchedPFCandidateIndex[10]", Electron2_GsfTrackMatchedPFCandidateIndex, &b_Electron2_GsfTrackMatchedPFCandidateIndex);
   fChain->SetBranchAddress("PFJet2", &PFJet2_, &b_PFJet2_);
   fChain->SetBranchAddress("PFJet2.pt", PFJet2_pt, &b_PFJet2_pt);
   fChain->SetBranchAddress("PFJet2.eta", PFJet2_eta, &b_PFJet2_eta);
   fChain->SetBranchAddress("PFJet2.phi", PFJet2_phi, &b_PFJet2_phi);
   fChain->SetBranchAddress("PFJet2.mass", PFJet2_mass, &b_PFJet2_mass);
   fChain->SetBranchAddress("PFJet2.rawPt", PFJet2_rawPt, &b_PFJet2_rawPt);
   fChain->SetBranchAddress("PFJet2.L1JECScale", PFJet2_L1JECScale, &b_PFJet2_L1JECScale);
   fChain->SetBranchAddress("PFJet2.L2JECScale", PFJet2_L2JECScale, &b_PFJet2_L2JECScale);
   fChain->SetBranchAddress("PFJet2.L3JECScale", PFJet2_L3JECScale, &b_PFJet2_L3JECScale);
   fChain->SetBranchAddress("PFJet2.hltMatchBits", PFJet2_hltMatchBits, &b_PFJet2_hltMatchBits);
   fChain->SetBranchAddress("PFJet2.NConstituents", PFJet2_NConstituents, &b_PFJet2_NConstituents);
   fChain->SetBranchAddress("PFJet2.NeutralHadronFraction", PFJet2_NeutralHadronFraction, &b_PFJet2_NeutralHadronFraction);
   fChain->SetBranchAddress("PFJet2.NeutralEMFraction", PFJet2_NeutralEMFraction, &b_PFJet2_NeutralEMFraction);
   fChain->SetBranchAddress("PFJet2.ChargedHadronFraction", PFJet2_ChargedHadronFraction, &b_PFJet2_ChargedHadronFraction);
   fChain->SetBranchAddress("PFJet2.ChargedEMFraction", PFJet2_ChargedEMFraction, &b_PFJet2_ChargedEMFraction);
   fChain->SetBranchAddress("PFJet2.TrackCountingHighEffBJetTagsDisc", PFJet2_TrackCountingHighEffBJetTagsDisc, &b_PFJet2_TrackCountingHighEffBJetTagsDisc);
   fChain->SetBranchAddress("PFJet2.TrackCountingHighPurBJetTagsDisc", PFJet2_TrackCountingHighPurBJetTagsDisc, &b_PFJet2_TrackCountingHighPurBJetTagsDisc);
   fChain->SetBranchAddress("PFJet2.SoftElectronByPtBJetTagsDisc", PFJet2_SoftElectronByPtBJetTagsDisc, &b_PFJet2_SoftElectronByPtBJetTagsDisc);
   fChain->SetBranchAddress("PFJet2.SoftElectronByIP3dBJetTagsDisc", PFJet2_SoftElectronByIP3dBJetTagsDisc, &b_PFJet2_SoftElectronByIP3dBJetTagsDisc);
   fChain->SetBranchAddress("PFJet2.SoftMuonByPtBJetTagsDisc", PFJet2_SoftMuonByPtBJetTagsDisc, &b_PFJet2_SoftMuonByPtBJetTagsDisc);
   fChain->SetBranchAddress("PFJet2.SoftMuonByIP3dBJetTagsDisc", PFJet2_SoftMuonByIP3dBJetTagsDisc, &b_PFJet2_SoftMuonByIP3dBJetTagsDisc);
   fChain->SetBranchAddress("PFJet2.SoftMuonBJetTagsDisc", PFJet2_SoftMuonBJetTagsDisc, &b_PFJet2_SoftMuonBJetTagsDisc);
   fChain->SetBranchAddress("PFJet2.SimpleSecondaryVertexHighPurBJetTagsDisc", PFJet2_SimpleSecondaryVertexHighPurBJetTagsDisc, &b_PFJet2_SimpleSecondaryVertexHighPurBJetTagsDisc);
   fChain->SetBranchAddress("PFJet2.SimpleSecondaryVertexHighEffBJetTagsDisc", PFJet2_SimpleSecondaryVertexHighEffBJetTagsDisc, &b_PFJet2_SimpleSecondaryVertexHighEffBJetTagsDisc);
   fChain->SetBranchAddress("PFJet2.CombinedSecondaryVertexBJetTagsDisc", PFJet2_CombinedSecondaryVertexBJetTagsDisc, &b_PFJet2_CombinedSecondaryVertexBJetTagsDisc);
   fChain->SetBranchAddress("PFJet2.CombinedSecondaryVertexMVABJetTagsDisc", PFJet2_CombinedSecondaryVertexMVABJetTagsDisc, &b_PFJet2_CombinedSecondaryVertexMVABJetTagsDisc);
   fChain->SetBranchAddress("PFJet2.JetProbabilityBJetTagsDisc", PFJet2_JetProbabilityBJetTagsDisc, &b_PFJet2_JetProbabilityBJetTagsDisc);
   fChain->SetBranchAddress("PFJet2.JetBProbabilityBJetTagsDisc", PFJet2_JetBProbabilityBJetTagsDisc, &b_PFJet2_JetBProbabilityBJetTagsDisc);
   fChain->SetBranchAddress("PFJet2.JetArea", PFJet2_JetArea, &b_PFJet2_JetArea);
   fChain->SetBranchAddress("PFJet2.matchedPdgId", PFJet2_matchedPdgId, &b_PFJet2_matchedPdgId);
   fChain->SetBranchAddress("MET", &MET, &b_MET);
   fChain->SetBranchAddress("MET2", &MET2, &b_MET2);
   fChain->SetBranchAddress("run_num", &run_num, &b_run_num);
   fChain->SetBranchAddress("event_num", &event_num, &b_event_num);
   Notify();
}

Bool_t anal::Notify()
{
   // The Notify() function is called when a new file is opened. This
   // can be either for a new TTree in a TChain or when when a new TTree
   // is started when using PROOF. It is normally not necessary to make changes
   // to the generated code, but the routine can be extended by the
   // user if needed. The return value is currently not used.

   return kTRUE;
}

void anal::Show(Long64_t entry)
{
// Print contents of entry.
// If entry is not specified, print current entry
   if (!fChain) return;
   fChain->Show(entry);
}
Int_t anal::Cut(Long64_t entry)
{
// This function may be called from Loop.
// returns  1 if entry is accepted.
// returns -1 otherwise.
   return 1;
}
#endif // #ifdef anal_cxx
