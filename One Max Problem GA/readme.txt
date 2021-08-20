files:
    ga.h : ga library
    onemax.h : onemax problem library

    main.cpp : 主程式(source code)
    main.exe
    Makefile
    plot.py : 收斂圖畫圖script
    result.csv : 紀錄每個run中每個iteration的best fitness
    result.jpg : 51run收斂圖

程式流程:

    ### initialization ###
    init P[population], P_next[population]
    best_fitness <- 0
    init Fitness[population] 
    init wheel_selection_table[population]

    during iteration:
        ### evaluation ###
        for i in (0:population):
            Fitness[i] <- fitness(P[i])
            if Fitness[i] > best_fitness:
                best_fitness <- Fitness[i]

        ### selection ###
        f_sum <- sum(Fitness[])
        wheel_selection_table[0] <- Fitness[0] / f_sum
        for i in (1:population):
            wheel_selection_table[i] <- Fitness[i] / f_sum + wheel_selection_table[i-1]

        for i in (0:population):
            s_flag <- rand(0, 1)
            for si in (0:population):
                if wheel_selection_table[si] > s_flag:
                    P_next[i] = P[si]
                    break

        ### crossover ###
        for i in (0:population, step = 2):
            if rand(0, 1) < crossover_p:
                crossover(P_next[i], P_next[i+1])

        ### mutation ###
        for i in (0:population):
            if rand(0, 1) < mutation_p:
                mutation(P_next[i])

        ### determination ###
        P = P_next
    
    ### evaluation (for the population of last iteration) ###
    for i in (0:population):
    Fitness[i] <- fitness(P[i])
    if Fitness[i] > best_fitness:
        best_fitness <- Fitness[i]

result:
最佳解: 97
平均最佳解: 93.4118
原因分析(推測): ga演算法的優點是進行多點搜索，因此找到的解會散布在整個解空間，能較快速的找到更好的解，也不容易卡在local optimum(有crossover跟mutation機制)。但對於onemax problem而言，ga不會針對特定的bit去改變解，因此ga很難找到global optimum