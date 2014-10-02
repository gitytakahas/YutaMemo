in1="~/work/MET_performance/CMSSW_5_3_2_patch4/src/analysis/Ntuple.root";

root -l -b <<EOF

TChain ch1("Events");
ch1.Add("$in1");

gROOT->ProcessLine(".L ./anal.C+g");
anal * t = new anal();

t->StartLoop();

t->SetTree(&ch1);
t->Loop();

t->EndLoop();

.q
EOF


