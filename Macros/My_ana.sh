#tree="crab_0_150120_133904/res/ntuple.root"
#tree="/afs/cern.ch/user/y/ytakahas/work/TauReconstruction_PFnoPU/CMSSW_7_1_0_pre6/src/RecoTauTag/TauTagTools/isolation_run2/VBF_run2_performance_20150124/all.root"
tree="~/work/TauReconstruction_PFnoPU/CMSSW_7_1_0_pre6/src/RecoTauTag/TauTagTools/isolation_run2/VBFHToTauTau_run2/ntuple.root"

root -l -b <<EOF

TChain ch("isoTuple");
ch.Add("$tree");


gROOT->ProcessLine(".L ./anal.C+g");
anal * t = new anal();

t->StartLoop();

t->SetTree(&ch);
t->Loop(false);
//t->Loop(true);

t->EndLoop();

.q
EOF

