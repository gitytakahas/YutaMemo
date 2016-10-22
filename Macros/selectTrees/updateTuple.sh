# update each ntuple by adding QCD fake weight and the MVA for ttbar rejection

basedir="/mnt/t3nfs01/data01/shome/ytakahas/work/TauTau/SFrameAnalysis/AnalysisOutput/signal_VBF/"
ifile="${basedir}/TauTauAnalysis.VBFHToTauTau_M125_13TeV_powheg_pythia8.root"

echo "input : $ifile"

for channel in tree_mutau tree_eletau
#for channel in tree_mutau
do
    ofile="${basedir}/TauTauAnalysis.VBFHToTauTau_M125_13TeV_powheg_pythia8_${channel}.root"
    echo $ofile

    root -l -q -b 'addvariable.C("'${ifile}'", "'${ofile}'", "'${channel}'")'
done