root -l -b <<EOF

gROOT->ProcessLine(".L ./parselhe.C+g");
parselhe("pwgevents.lhe", "Myroot.root")

.q
EOF

