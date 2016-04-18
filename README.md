YutaMemo
========


------------------------------------------
ROOT commands :
------------------------------------------

tree.Scan("run:lumi:event","","colsize=20")

Events->Draw("recoGenParticles_genParticles__RECO.obj.vertex_.fCoordinates.fZ","recoGenParticles_genParticles__RECO.obj.pdgId_==-15")

Events->Draw("recoBeamSpot_offlineBeamSpot__RECO.obj.position_.fCoordinates.fZ")

Events->Scan("recoPFClusters_particleFlowClusterECAL__RECO.obj.energy_","EventAuxiliary.id_.event_==40")

gStyle.SetPaintTextFormat("2.2f")

------------------------------------------
git push to the remote repository :
------------------------------------------

git push <repository> <branch>

git push https://github.com/gitytakahas/cmg-cmssw Yuta_develop_20140211

git remote add Jan https://github.com/steggema/cmg-cmssw/

git remote -v

git fetch Jan

git lt Jan/HTauTauMiniAOD

git cherry-pick e57e210

git diff CMGTools/H2TauTau/python/proto/analyzers/H2TauTauTreeProducerTauMu.py

git diff H2TauTauTreeProducerTauMu.py

git reset --merge

git cms-addpkg GeneratorInterface/TauolaInterface ...

------------------------------------------

Similar example:

cd test/

cmsrel CMSSW_7_2_3

cd CMSSW_7_2_3/src/

cmsenv

git init

git remote add Yuta https://github.com/gitytakahas/cmg-cmssw

git fetch Yuta

git config core.sparsecheckout true

cp /afs/cern.ch/user/y/ytakahas/public/forEmmanuelle/sparse-checkout .git/info/sparse-checkout

git checkout -b CMGTools-from-CMSSW_7_2_3_TauIsolation Yuta/CMGTools-from-CMSSW_7_2_3

scram b -j8


------------------------------------------
edmIntegrityCheck
------------------------------------------

edmIntegrityCheck.py -u htautau_group -p -w *.root /TTJets_FullLeptMGDecays_8TeV-madgraph-tauola/Summer12_DR53X-PU_S10_START53_V7C-v2/AODSIM/V5_B/PAT_CMG_V5_16_0/EMuTau_Yuta_Feb12

------------------------------------------
getInfo
------------------------------------------

getInfo.py -s "select file_owner, path_name from dataset_details where path_name like '%EMuTau_Yuta_Feb12%' order by path_name"

------------------------------------------
Access to the eos root file
------------------------------------------

root://eoscms//eos/cms/store/cmst3/group/cmgtools/CMG/GluGluToHToTauTau_M-120_8TeV-powheg-pythia6/Summer12_DR53X-PU_S10_START53_V7A-v1/AODSIM/V5_B/PAT_CMG_V5_14_0/cmgTuple_1.root

------------------------------------------
Produce event list
------------------------------------------

eventList.py test/HiggsVBF125/H2TauTauSyncTreeMuEle/H2TauTauSyncTreeMuEle_tree.root --tree H2TauTauSyncTreeMuEle

------------------------------------------
Produce different event list
------------------------------------------
diffEventList.py test1 test2

------------------------------------------
Check CPU info
------------------------------------------

cat /proc/cpuinfo

------------------------------------------
Loop in the bash
------------------------------------------

for a in $(seq 1 5)

do

echo $a

done

------------------------------------------
Check job status
------------------------------------------

bpeek <ID>

------------------------------------------
 Submit job
------------------------------------------

crab -cfg HOMET.cfg -create -submit

------------------------------------------
 Check status
------------------------------------------

crab -c crab_0_130901_143856 -status

------------------------------------------
 Collect your job
------------------------------------------

crab -c crab_0_130720_081427 -getoutput

Tree->Draw("bdt_evt_L2T >> h(10,0,200)","(bdt_evt_isSignal==1)*bdt_evt_weight")


------------------------------------------
jobreport
------------------------------------------

jobreport.py /MuEG/Run2012A-22Jan2013-v1/AOD/PAT_CMG_V5_15_0/EMuTau_Yuta_Feb21 . -u htautau_group -w 'muEle_fullsel_tree_CMG*root' 
=> be carefule about XXX*root 

[ytakahas@lxplus415 ~/work/htautau_2014_analysis/CMSSW_5_3_14/src/CMGTools/H2TauTau/skimming/MuEG/Run2012A-22Jan2013-v1/AOD/PAT_CMG_V5_15_0_1393840295/EMuTau_Yuta_Feb21_Jobs]$ jobreport.py /MuEG/Run2012A-22Jan2013-v1/AOD/PAT_CMG_V5_15_0/EMuTau_Yuta_Feb21 . -u htautau_group -s -b 'bsub -q 2nd < batchScript.sh'

=> Need to be in the directory where you can see the JobX/ directories 



------------------------------------------
change directory structure
------------------------------------------

scramv1 b ProjectRename


------------------------------------------
change preselection criteria
------------------------------------------

$CMSSW_BASE/src/CMGTools/H2TauTau/python/objects


------------------------------------------
LXR
------------------------------------------

When searching for python files, then 

Files named : .*py

Containing : PoolSourse


------------------------------------------
H2TauTau memo
------------------------------------------

for detecting leptonleg for the MET recoil correction

CMGTools/H2TauTau/python/tools

CMGTools/H2TauTau/python/objects


------------------------------------------
scram
------------------------------------------

scramv1 b ProjectRename

scram list CMSSW


------------------------------------------
Add afs user
------------------------------------------

/usr/sbin/addusercern steggema


------------------------------------------
kill firefox
------------------------------------------

.mozilla/firefox/y5agqdie.default/.parentlock


------------------------------------------
check file
------------------------------------------

fs setacl -dir . -acl system:anyuser rl

fs listacl /afs/cern.ch/user/y/ytakahas/public/WH_emt_3S_root/


------------------------------------------
Run crab job 
------------------------------------------

voms-proxy-init -voms cms -valid 192:00


------------------------------------------
pybatch
------------------------------------------

pybatch.py -o 20140329_nominal tauMu_2012_cfg.py -b 'bsub -q 8nh -J 20140329_nominal < batchScript.sh'


------------------------------------------
grid help
------------------------------------------

https://twiki.cern.ch/twiki/bin/view/CMSPublic/SWGuideCrab#Getting_Support

------------------------------------------
pick event
------------------------------------------

https://twiki.cern.ch/twiki/bin/view/CMSPublic/WorkBookPickEvents

------------------------------------------
cmsShow
------------------------------------------

cmsShow root://eoscms//eos/cms/store/cmst3/user/ytakahas/CMG/HO/522D7B2B-67C4-E311-81D3-0025904B2C7E.root

------------------------------------------
eos
------------------------------------------

eos quota

eos ls /eos/cms/store/lhe/MCMDBID

execute cmsStage after "cmsenv"

------------------------------------------
AN, DN setup
------------------------------------------

> svn co -N svn+ssh://svn.cern.ch/reps/tdr2 myDir

> cd myDir

> svn update utils

> svn update -N notes

> svn update notes/DN-14-019

> eval `./notes/tdr runtime -csh` # for tcsh. use -sh for bash.

> cd notes/DN-14-019/trunk

# (edit the template, then to build the document)

> tdr --style=dn b DN-14-019
 
You can commit your changes with

> svn add NewFileNames

before they can be committed.

> svn commit –m "commit message"

New files will first need to be added with


------------------------------------------
Recovery of the old files
------------------------------------------

afs_admin recover /afs/cern.ch/user/y/ytakahas/.mozilla/firefox/y5agqdie.default/

------------------------------------------
kill some commands
------------------------------------------

pgrep python | xargs kill

------------------------------------------
python
------------------------------------------

'{0:.1f}'.format()


------------------------------------------
bkill
------------------------------------------
bkill -s9 <jobid>


------------------------------------------
find command
------------------------------------------
find . -name "param_card.dat"


------------------------------------------
public settings
------------------------------------------
find . -type d -exec fs setacl {} system:anyuser rl \;
fs setacl -dir . -acl system:anyuser rl