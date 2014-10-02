for a in $(seq 0 4810)
do
    cd Job_${a}

    if ls *.root > /dev/null 2>&1
    then
	echo "ok for Job_${a}"
    else
	echo "not exists for Job_${a}"
	bsub -q 2nd batchScript.sh
	sleep 0.1
    fi
    cd - > /dev/null 2>&1
done
