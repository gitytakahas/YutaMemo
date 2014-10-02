# copy

xrdcp madgraph_0_ggH_CMS.root root://eoscms//eos/cms/store/cmst3/user/ytakahas/CMG/madgraph_ggH_root/
xrdcp ptsqmin30_${a}_CMS.root root://eoscms//eos/cms/store/cmst3/user/ytakahas/CMG/ptsqmin_ggH_sample/

#for a in $(seq 0 19); do echo $a; xrdcp ptsqmin15_${a}_CMS.root root://eoscms//eos/cms/store/cmst3/user/ytakahas/CMG/ptsqmin_qqH_sample/; done

for a in $(seq 0 9); do echo $a; xrdcp powheg_box_qqH_${a}_ATLAS.root root://eoscms//eos/cms/store/cmst3/user/ytakahas/CMG/pyanaroot_powheg_qqH/; done

# mkdir
xrd eoscms mkdir /eos/cms/store/cmst3/user/ytakahas/CMG/lhe_ptsqmin_qqH

# rmdir
eos rmdir /eos/cms/store/cmst3/user/ytakahas/CMG/lhe_ptsqmin_qqH


# copy directory itself
eos cp -r /afs/cern.ch/user/y/ytakahas/work/job/CMSSW_5_3_9/src/CMGTools/Production/scripts/ggH_powheg_scale/ /eos/cms/store/cmst3/user/ytakahas/CMG/lhe/ggH_powheg_scale/

# mv with incremented numbers
i=0
while [ $i -lt 20 ];do
    ii=`expr $i + 20`
    echo $i $ii
    mv pwgevents_${i}.lhe ptsqmin15_pwgevents_${ii}.lhe
    i=`expr $i + 1`
done