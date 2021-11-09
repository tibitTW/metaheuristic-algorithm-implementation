d_arr=(10 30 50 100)
result_path="./result.csv"

rm $result_path

# output csv header
printf "f_num,10d,30d,50d,100d\n" >>$result_path

# output experiment result
for ((f_num = 1; f_num <= 30; f_num++)); do
    printf "${f_num}," >>$result_path
    for ((i = 0; i < 4; i++)); do
        # main.exe x_dim     x_min x_max fun_num run output_file
        ./main.exe $d_arr[i] -100 100 $f_num 51 ./result/result_${d_arr[i]}D_f${f_num}.txt >>${result_path}
        # ./main.exe $d_arr[i] -100 100 $f_num 1 result_${i}D_f${f_num}.txt >>${result_path}
<<<<<<< Updated upstream

        if [ "$i" -ne 3 ]; then
            printf "," >>$result_path
        fi
=======
        # ./main.exe $d_arr[i] -100 100 $f_num 1 "" >>${result_path}
        printf $d_arr[i]
        # printf "," >>$result_path
>>>>>>> Stashed changes
    done
    printf "\n" >>$result_path
done
