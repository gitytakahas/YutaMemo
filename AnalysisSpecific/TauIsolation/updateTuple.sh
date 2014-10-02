# update each ntuple by adding QCD fake weight and the MVA for ttbar rejection

basedir="/afs/cern.ch/work/y/ytakahas/Tau/CMSSW_7_1_0_pre6/src/CMGTools/RootTools/python/configs"

tag="sample_20140513"

for file in DY_Timing #VBF_Timing125
  do
    ifile="${basedir}/${tag}/${file}/TauTreeProducer/TauTreeProducer_tree.root";
    output="${basedir}/${tag}/${file}/TauTreeProducer/";
    ofile="/tmp/ytakahas/TauTreeProducer_tree_mod.root";
    param="${basedir}/root/IsolationParameters_DY";

    root -l -q -b 'evaluate.C("'${ifile}'", "'${ofile}'", "'${param}'")'
  
    cp $ofile $output

done
