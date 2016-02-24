base_dir='job_30_30'
ls_result=($(ls $base_dir))
for dir in ${ls_result[@]}
do
    cd ${base_dir}/$dir
    cd -
done