#!/bin/bash

#export SCRAM_ARCH=slc5_amd64_gcc472
#cmsrel CMSSW_6_1_1
#cd CMSSW_6_1_1/src/
#cmsenv
#git clone https://github.com/cms-analysis/HiggsAnalysis-CombinedLimit.git HiggsAnalysis/CombinedLimit
#git clone https://github.com/cms-analysis/HiggsAnalysis-HiggsToTauTau.git HiggsAnalysis/HiggsToTauTau
#git clone https://github.com/roger-wolf/HiggsAnalysis-HiggsToTauTau-auxiliaries.git auxiliaries

#pushd HiggsAnalysis/HiggsToTauTau
#git checkout HiggsAnalysis-HiggsToTauTau-V01-01-12
#popd
#pushd HiggsAnalysis/CombinedLimit
#git checkout HiggsAnalysis-CombinedLimit-V03-04-02
#popd
#pushd auxiliaries
#git checkout HiggsAnalysis-HiggsToTauTau-auxiliaries-V01-01-12
#popd


#eval `scramv1 runtime -sh`
#scram b j4

# change configuration file !!

#python HiggsAnalysis/HiggsToTauTau/scripts/doSM.py --update-all 125


# To calculate the significance, This is enough
for chn in cmb et mt em
  do
  submit.py --significance-frequentist --options "--expectedOnly" LIMITS/hww-bg/$chn/*
done




## Setting up the LIMITS folder
## The following is done in the "src" directory of the CMSSW folder

#mkdir -p LIMITS/hww-bg
#cvs2local.py -i auxiliaries/datacards/ -o LIMITS/hww-bg/ee -p "8TeV 7TeV" -c "ee" --sm-categories-ee "0 1 2 3 4" 110-145:5
#cvs2local.py -i auxiliaries/datacards/ -o LIMITS/hww-bg/mm -p "8TeV 7TeV" -c "mm" --sm-categories-mm "0 1 2 3 4" 110-145:5
#cvs2local.py -i auxiliaries/datacards/ -o LIMITS/hww-bg/em -p "7TeV" -c "em" --sm-categories-em "0 1 2 3 4" 110-145:5
#cvs2local.py -i auxiliaries/datacards/ -o LIMITS/hww-bg/em -p "8TeV" -c "em" --sm-categories-em "0 1 2 3 4 5" 110-145:5
#cvs2local.py -i auxiliaries/datacards/ -o LIMITS/hww-bg/et -p 7TeV -c "et" --sm-categories-et "0 1 2 3 5 6" 110-145:5
#cvs2local.py -i auxiliaries/datacards/ -o LIMITS/hww-bg/et -p 8TeV -c "et" --sm-categories-et "0 1 2 3 5 6 7" 110-145:5
#cvs2local.py -i auxiliaries/datacards/ -o LIMITS/hww-bg/mt -p 7TeV -c "mt" --sm-categories-mt "0 1 2 3 4 5 6" 110-145:5
#cvs2local.py -i auxiliaries/datacards/ -o LIMITS/hww-bg/mt -p 8TeV -c "mt" --sm-categories-mt "0 1 2 3 4 5 6 7" 110-145:5
#cvs2local.py -i auxiliaries/datacards/ -o LIMITS/hww-bg/tt -p 8TeV -c "tt" --sm-categories-tt "0 1 2" 110-145:5
#cvs2local.py -i auxiliaries/datacards/ -o LIMITS/hww-bg/cmb -p 7TeV -c "ee mm mt et em" --sm-categories-ee "0 1 2 3 4" --sm-categories-mm "0 1 2 3 4" --sm-categories-em "0 1 2 3 4" --sm-categories-mt "0 1 2 3 4 5 6" --sm-categories-et "0 1 2 3 5 6" 110-145:5
#cvs2local.py -i auxiliaries/datacards/ -o LIMITS/hww-bg/cmb -p 8TeV -c "ee mm mt tt et em" --sm-categories-ee "0 1 2 3 4" --sm-categories-mm "0 1 2 3 4" --sm-categories-em "0 1 2 3 4 5" --sm-categories-mt "0 1 2 3 4 5 6 7" --sm-categories-et "0 1 2 3 5 6 7" --sm-categories-tt "0 1 2" 110-145:5


## run the mlfit
#for chn in cmb et mt em mm ee tt
for chn in cmb et mt em
do
    submit.py --max-likelihood LIMITS/hww-bg/$chn/125
done

## wait for all jobs to finish
#while true
#do
#    if [ ! "$(bjobs 2>/dev/null)" ]
#    then
#        break
#    fi
#    sleep 30
#done

## include an absolute path and produce postfits
## first addapt the inlcude to the corresponding absolute path
sed -i "1s,.*,#include \"$CMSSW_BASE/src/HiggsAnalysis/HiggsToTauTau/interface/HttStyles.h\"," HiggsAnalysis/HiggsToTauTau/src/HttStyles.cc
pushd HiggsAnalysis/HiggsToTauTau/test
## The following is done in the "test" directory of the HiggsToTauTau repository. The previous line changes the folder
#for chn in cmb et mt em mm ee tt
for chn in cmb et mt em
do
    python mlfit_and_copy.py -s $CMSSW_BASE/src/LIMITS/hww-bg/$chn/125
    python produce_macros.py -c ../data/limits.config-sm-${chn}-only --hww-background
    python run_macros.py -c ../data/limits.config-sm-${chn}-only
done
python summary_plots.py -c ../data/limits.config-sm-130902 --hww-background
popd

## run asymptotic and significance
## The following is done in the "src" directory of the CMSSW folder
## if jobs fail due to computing time issues, use "-q '-q 1nd' " as an additional option

#for chn in cmb et mt em mm ee tt
for chn in cmb et mt em
do
    submit.py --asymptotic --options "--expectedOnly" LIMITS/hww-bg/$chn/*
done


## produce the plots for asymptotic and significance
## first change the configuration for the plotting to expected only
sed -i '33s/.*/\ \ \ \ expectedOnly = cms.bool(True),/' HiggsAnalysis/HiggsToTauTau/python/layouts/limit-sm.py
#for chn in cmb et mt em mm ee tt
for chn in cmb et mt em
do
    plot --asymptotic HiggsAnalysis/HiggsToTauTau/python/layouts/limit-sm.py LIMITS/hww-bg/$chn
    plot --significance-frequentist HiggsAnalysis/HiggsToTauTau/python/layouts/significance-sm.py LIMITS/hww-bg/$chn
done
