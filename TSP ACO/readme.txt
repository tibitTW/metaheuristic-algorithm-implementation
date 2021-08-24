程式流程

    def calculateExceptedValue(tau, eta, PHERO_CTRL_FACTOR, DISTANCE_CTRL_FACTOR):
        return pow(tau, PHERO_CTRL_FACTOR) * pow(eta, DISTANCE_CTRL_FACTOR)

    init ant_path_length_acc[ANT_POP] = {0}
    init ants_current_city[ANT_POP]
    init ant_visited_city[ANT_POP][CITY_DIM] = {0}
    init ants_visited_city_order[ANT_POP][CITY_DIM]
    init excepted_value_table[CITY_DIM][3]
    init phero_RM[CITY_DIM]CITY_DIM]
    init city_distances[CITY_DIM][CITY_DIM]

    shortest_path <- 10000
    during iteration:
        for ai in (0:ANT_POP):
            ants_current_city[ai] = random_city()
            ant_visited_city[ai][ants_current_city[ai]] = 1

        for ai in (0:ANT_POP):
            for city_cnt in (1:CITY_DIM):
                exp_val_sum <- 0
                p_sum <- 0

                for ci in (0:CITY_DIM):
                    if ant_visited_city[ai][ci] == 1:
                        excepted_value_table[ci][0] = -1
                
                    else:
                        exp_val = calculateExceptedValue(phero_RM[ants_current_city[ai]][ci], 1.0 / city_distances[ants_current_city[ai]][ci], PHERO_CTRL_FACTOR, DISTANCE_CTRL_FACTOR)

                        excepted_value_table[ci][0] = exp_val
                        exp_val_sum += exp_val

                for ci in (0:CITY_DIM):
                    if excepted_value_table[ci][0] == -1:
                        excepted_value_table[ci][1] = -1
                        excepted_value_table[ci][2] = -1
                    
                    else:
                        excepted_value_table[ci][1] = excepted_value_table[ci][0] / exp_val_sum
                        p_sum ++ excepted_value_table[ci][1]
                        excepted_value_table[ci][2] = p_sum

                rdn = rand(0, 1)

                next_ci = 0
                while (next_ci < CITY_DIM):
                    if (excepted_value_table[next_ci][2] > rdn):
                        ant_path_length_acc[ai] += city_distances[ants_current_city[ai]][next_ci]
                        ants_current_city[ai] = next_ci
                        ant_visited_city[ai][next_ci] = 1
                        ants_visited_city_order[ai][city_cnt] = next_ci
                        break

                    next_ci += 1

            ant_path_length_acc[ai] ++ city_distances[ants_current_city[CITY_DIM-1]][0]

            for ci in (0:CITY_DIM):
                for cj in (0:CITY_DIM):
                    if (ci != cj):
                        phero_RM[ci][cj] += (1-EVAPORATION_FACTOR)
                        phero_RM[ci][cj] = (phero_RM[ci][cj] > MIN_PHERO_AMOUNT ? phero_RM[ci][cj] : MIN_PHERO_AMOUNT)

            for ai in (0:ANT_POP):
                avg_phero = PHERO_ANT_CARRIED / CITY_DIM
                for ci in (0:CITY_DIM-1):
                    phero_RM[ants_visited_city_order[ai][ci]][ants_visited_city_order[ai][ci + 1]] += avg_phero / city_distances[ants_visited_city_order[ai][ci]][ants_visited_city_order[ai][ci + 1]]
                    phero_RM[ants_visited_city_order[ai][ci + 1]][ants_visited_city_order[ai][ci]] = phero_RM[ants_visited_city_order[ai][ci]][ants_visited_city_order[ai][ci + 1]]

                phero_RM[ants_visited_city_order[ai][CITY_DIM - 1]][ants_visited_city_order[ai][0]] += avg_phero / city_distances[ants_visited_city_order[ai][CITY_DIM - 1]][ants_visited_city_order[ai][0]]
                phero_RM[ants_visited_city_order[ai][CITY_DIM - 1]][ants_visited_city_order[ai][0]] = phero_RM[ants_visited_city_order[ai][0]][ants_visited_city_order[ai][CITY_DIM - 1]]

            for ai in (0:ANT_POP):
                shortest_path = shortest_path < ant_path_length_acc[ai] ? shortest_path : ant_path_length_acc[ai]

實驗結果
    最佳解: 404.305
    平均最佳解: 425.461
    結果分析: 或許是螞蟻數設100，數量較多的原因，iteration平均在100以內都能將找到的最佳解收斂到500以下。有些解答找到比原本最佳解還好的結果，不確定是哪個部分有寫錯(待釐清)