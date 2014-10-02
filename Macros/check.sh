for a in DY2Jets DY1Jets W4Jets W2Jets W3Jets TTZ TTW WZJetsTo3LNu ZZJetsTo4L WJets HiggsTTH125 TTJetsSemiLept DY3Jets TTJetsHadronic WWJetsTo2L2Nu TTJetsFullLept data_Run2012D data_Run2012B data_Run2012C W1Jets data_Run2012A DYJets DY4Jets
  do
  echo $a, "before"
  root -l $a/H2TauTauTreeProducerEMT2/H2TauTauTreeProducerEMT2_tree.root <<EOF
H2TauTauTreeProducerEMT2->GetEntries()
EOF

  echo $a, "after"
  root -l ../../process/emt_20140811/$a/H2TauTauTreeProducerEMT2/H2TauTauTreeProducerEMT2_tree.root <<EOF
H2TauTauTreeProducerEMT2->GetEntries()
EOF


  echo "============================================================"
done