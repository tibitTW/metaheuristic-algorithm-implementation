d_arr=(10,30,50,100)
result_path="./result.csv"

# output csv header
for((i=0; i<4; i++))
do
    printf "${d_arr[i]}" >> ${result_path}
done
printf "\n" >> $result_path

# output experiment result
for((i=0; i<4; i++))
do
    for((fun_num=1; fun_num<=30; fun_num++))
    do
        printf "${d_arr[i]}" >> ${result_path}
    done
done
printf "\n" >> $result_path
