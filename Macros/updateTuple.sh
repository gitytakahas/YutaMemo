# update each ntuple by adding QCD fake weight and the MVA for ttbar rejection

basedir="/afs/cern.ch/work/m/manzoni/public/diTau_17Sep_newPU/nom"
yutadir="/afs/cern.ch/work/y/ytakahas/TauTrigger_tautau/CMSSW_5_3_14/src/CMGTools/H2TauTau/TauTau/sample/nom"


ptval=35

for file in data_Run2012A_22Jan2013_v1 Tbar_tW WZJetsTo3LNu data_Run2012B_22Jan2013_v1 TTJetsFullLept ZZJetsTo2L2Nu data_Run2012C_22Jan2013_v1 TTJetsFullLept_bug ZZJetsTo2L2Q data_Run2012D_22Jan2013_v1 TTJetsHadronic ZZJetsTo4L DY1Jets TTJetsSemiLept DY2Jets HiggsGGH125 T_tW DY3Jets W1Jets DY4Jets W2Jets W3Jets embed_Run2012A_22Jan2013_v1 nonSplitVH W4Jets embed_Run2012B_22Jan2013_v1 HiggsVBF125 embed_Run2012C_22Jan2013_v1 WWJetsTo2L2Nu embed_Run2012D_22Jan2013_v1 HiggsVH125 WZJetsTo2L2Q

#for file in HiggsGGH125
  do
  ifile="${basedir}/${file}/H2TauTauTreeProducerTauTau/H2TauTauTreeProducerTauTau_tree.root";
  outdir="${yutadir}/${file}/H2TauTauTreeProducerTauTau";
  mkdir -p $outdir

  ofile="${yutadir}/${file}/H2TauTauTreeProducerTauTau/H2TauTauTreeProducerTauTau_tree.root";

  cd EmuMVA;
  root -l -q -b 'addvariable.C("'${ifile}'", "'${ofile}'", "'${ptval}'")'
  cd -;

done
