run=51
d_array=(2 10 30)
for d in "${d_array[@]}"; do
    res_path="./output/ackley/lshade_ackley_${d}d_${run}r.txt"
    (time ./main.out LSHADE $run 0 $d -32.768 32.768 >$res_path) 2>>$res_path
    res_path="./output/griewank/lshade_griewank_${d}d_${run}r.txt"
    (time ./main.out LSHADE $run 1 $d -600 600 >$res_path) 2>>$res_path
    res_path="./output/rastrigin/lshade_rastrigin_${d}d_${run}r.txt"
    (time ./main.out LSHADE $run 2 $d -5.12 5.12 >$res_path) 2>>$res_path
    res_path="./output/schwefel/lshade_schwefel_${d}d_${run}r.txt"
    (time ./main.out LSHADE $run 3 $d -500 500 >$res_path) 2>>$res_path
    res_path="./output/sphere/lshade_sphere_${d}d_${run}r.txt"
    (time ./main.out LSHADE $run 4 $d -5.12 5.12 >$res_path) 2>>$res_path
    res_path="./output/sum_squares/lshade_sum_squares_${d}d_${run}r.txt"
    (time ./main.out LSHADE $run 5 $d -5.12 5.12 >$res_path) 2>>$res_path
    res_path="./output/zakharov/lshade_zakharov_${d}d_${run}r.txt"
    (time ./main.out LSHADE $run 6 $d -5 10 >$res_path) 2>>$res_path
    res_path="./output/rosenbrock/lshade_rosenbrock_${d}d_${run}r.txt"
    (time ./main.out LSHADE $run 7 $d -5 10 >$res_path) 2>>$res_path
    res_path="./output/michalewicz/lshade_michalewicz_${d}d_${run}r.txt"
    (time ./main.out LSHADE $run 8 $d 0 3.141592653589793 >$res_path) 2>>$res_path
    res_path="./output/powell/lshade_powell_${d}d_${run}r.txt"
    (time ./main.out LSHADE $run 9 $d -4 5 >$res_path) 2>>$res_path

done
