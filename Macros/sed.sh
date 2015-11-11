for a in DY1Jets_madgraph_5f_LO DY2Jets_madgraph_5f_LO DY3Jets_madgraph_5f_LO DY4Jets_madgraph_5f_LO
do
    cd ${a}
    mv DYJets_HT-incl_proc_card.dat ${a}_proc_card.dat
    mv DYJets_HT-incl_run_card.dat ${a}_run_card.dat
    sed -i -e "s/output DYJets_HT-incl/output "${a}"/" ${a}_proc_card.dat
    cd -
done
