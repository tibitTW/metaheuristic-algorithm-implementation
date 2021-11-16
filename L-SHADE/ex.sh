result_path="./result.csv"

rm ${result_path}

# output csv header
printf "f_num,10d,30d,50d,100d\n" >>$result_path

# output experiment result
for ((f_num = 1; f_num <= 30; f_num++)); do
    printf "${f_num}," >>$result_path
    ./main.exe 10 -100 100 $f_num 51 ./result/result_10D_f${f_num}.txt >>${result_path}
    printf "," >>$result_path
    ./main.exe 30 -100 100 $f_num 51 ./result/result_30D_f${f_num}.txt >>${result_path}
    printf "," >>$result_path
    ./main.exe 50 -100 100 $f_num 51 ./result/result_50D_f${f_num}.txt >>${result_path}
    printf "," >>$result_path
    ./main.exe 100 -100 100 $f_num 51 ./result/result_100D_f${f_num}.txt >>${result_path}
    printf "\n" >>$result_path
done
