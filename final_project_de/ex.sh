run=51
d_array=(2 10 30)
for d in "${d_array[@]}"; do
    res_path="./output/ackley/de_ackley_${d}d_${run}r.txt"
    (time ./main.out DE $run 0 $d -32.768 32.768 50 0.9 0.6 $((d * 10000)) >$res_path) 2>>$res_path
    res_path="./output/griewank/de_griewank_${d}d_${run}r.txt"
    (time ./main.out DE $run 1 $d -600 600 50 0.9 0.6 $((d * 10000)) >$res_path) 2>>$res_path
    res_path="./output/rastrigin/de_rastrigin_${d}d_${run}r.txt"
    (time ./main.out DE $run 2 $d -5.12 5.12 50 0.9 0.6 $((d * 10000)) >$res_path) 2>>$res_path
    res_path="./output/schwefel/de_schwefel_${d}d_${run}r.txt"
    (time ./main.out DE $run 3 $d -500 500 50 0.9 0.6 $((d * 10000)) >$res_path) 2>>$res_path
    res_path="./output/sphere/de_sphere_${d}d_${run}r.txt"
    (time ./main.out DE $run 4 $d -5.12 5.12 50 0.9 0.6 $((d * 10000)) >$res_path) 2>>$res_path
    res_path="./output/sum_squares/de_sum_squares_${d}d_${run}r.txt"
    (time ./main.out DE $run 5 $d -5.12 5.12 50 0.9 0.6 $((d * 10000)) >$res_path) 2>>$res_path
    res_path="./output/zakharov/de_zakharov_${d}d_${run}r.txt"
    (time ./main.out DE $run 6 $d -5 10 50 0.9 0.6 $((d * 10000)) >$res_path) 2>>$res_path
    res_path="./output/rosenbrock/de_rosenbrock_${d}d_${run}r.txt"
    (time ./main.out DE $run 7 $d -5 10 50 0.9 0.6 $((d * 10000)) >$res_path) 2>>$res_path
    res_path="./output/michalewicz/de_michalewicz_${d}d_${run}r.txt"
    (time ./main.out DE $run 8 $d 0 3.141592653589793 50 0.9 0.6 $((d * 10000)) >$res_path) 2>>$res_path
    res_path="./output/powell/de_powell_${d}d_${run}r.txt"
    (time ./main.out DE $run 9 $d -4 5 50 0.9 0.6 $((d * 10000)) >$res_path) 2>>$res_path

done
