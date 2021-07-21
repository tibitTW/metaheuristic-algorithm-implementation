檔案內容:

main.cpp : source code
main.exe : mainly executable file 
           usage : use main.exe -h for fully usage explaintion
binary_numeric_result_with_avg.csv / flipbit_result_with_avg.csv : 51 run 結果
flipbit.jpg / binary_numeric.jpg : 結果圖、平均收斂圖

程式流程:

def HC(bit_size, max_iteration, neighbor_type):
    init s    # solution
    init Result[max_iteration]
    f = fitness(s)    # calculate fitness
    Result[0] = f
    for i in (1 ~ max_iteration) do:
        next_s = neighbor(s)
        if fitness(s) > f:
            f = fitness(s)
            Result[i] = f
            s = next_s

    return Result

main:
    read arguments{bit_size, max_iteration, runs, neighbor_type, result_file_path}
    do runs times:
        Result = HC(bit_size, max_iteration, neighbor_type)
        result_file.write(Result)

---------------------------------------------------------------------------------------

程式結果:

    arguments:
        bit size: 100
        max iteration: 200
        run: 51

    transition type:

        binary value (0110 <- 0111 -> 1000):
            best fitness = 61
            avg fitness = 50.76

        randomly flip one bit (0 -> 1 / 1 -> 0):
            best fitness = 97
            avg fitness = 93.62

---------------------------------------------------------------------------------------

分析:
transition by binary value: neighbor 只有兩個方向，且容易卡死在區域最佳解(當 solution 為 "...111...111"，結尾為連續的1時即有可能為區域最佳解)。若要達到全域最佳解，則可能的初始值只有 4 種組合 (111...111, 111...110, 111...101, 111...100)，因此找到全域最佳解的機率為 4/2^100 = 1/2^98
transition by flip one bit randomly: neighbor 的選擇方式為隨機選取一個bit翻轉，因此不容易卡在區域最佳解。在每個 iteration 當中， fitness 增加 1 的機率為 (bit size - 當前的 fitness) / bit size，因此從理論上而言若 iteration 次數足夠，必定能找到全域最佳解
