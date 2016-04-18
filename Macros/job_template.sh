dir='/afs/cern.ch/user/y/ytakahas/work/genproductions/bin/MadGraph5_aMCatNLO/test3/CMSSW_7_1_20_patch3/src'
cd ${dir}
currDir=`pwd`
echo 'Now working in '${currDir}
eval `scramv1 runtime -sh`
./runcmsgrid.sh 100000 1234 6
