程式流程

def ackley2d(X, X_DIM) {
    res = 0
    a = 20
    b = 0.2
    c = PI * 2
    d = 2

    return (-1) * a * exp((-1) * b * sqrt((pow(X[0], 2) + pow(X[1], 2)) / d)) - exp((cos(c * X[0]) + cos(c * X[1])) / d) + a + exp(1)
}

def updateVelocity(lastV, last_pos, Pbest_pos, Gbest_pos, X_DIM, INERTIA_WEIGHT,  P_LEARNING_FACTOR,  G_LEARNING_FACTOR, V_UPPER_BOUND, V_LOWER_BOUND) {
    init term1[X_DIM]
    init term2[X_DIM]
    init term3[X_DIM]
    for xi in (0:X_DIM):
        term1[xi] = INERTIA_WEIGHT * lastV[xi]
        term2[xi] = rand(0, 1) * P_LEARNING_FACTOR * (Pbest_pos[xi] - last_pos[xi])
        term3[xi] = rand(0, 1) * G_LEARNING_FACTOR * (Gbest_pos[xi] - last_pos[xi])
        lastV[xi] = term1[xi] + term2[xi] + term3[xi]
        lastV[xi] = lastV[xi] > V_UPPER_BOUND ? V_UPPER_BOUND : lastV[xi]
        lastV[xi] = lastV[xi] < V_LOWER_BOUND ? V_LOWER_BOUND : lastV[xi]
}

init ptcsPos[PTC_AMOUNT][X_DIM]
init ptcsV[PTC_AMOUNT][X_DIM]
init ptcsPBestPos[PTC_AMOUNT][X_DIM]
init ptcsPBestFitness[PTC_AMOUNT]
init ptcsGBestPos[X_DIM]
init ptcsGBestFitness

for pi in (0:PTC_AMOUNT):
    for xi in (0:X_DIM):
        ptcsPos[pi][xi] = rand(MAP_LOWER_BOUND, MAP_UPPER_BOUND)
        ptcsPBestPos[pi][xi] = ptcsPos[pi][xi]
        ptcsPBestFitness[pi] = ackley2d(ptcsPBestPos[pi], X_DIM)

        ptcsV[pi][xi] = rand(V_LOWER_BOUND, V_UPPER_BOUND)

best_i = 0
for pi in (1:PTC_AMOUNT):
    best_i = ptcsPBestFitness[best_i] < ptcsPBestFitness[pi] ? best_i : pi
ptcsGBestFitness = ptcsPBestFitness[best_i]

for iter in (0:ITERATION):
    for pi in (0:PTC_AMOUNT):
        for xi in (0:X_DIM):
            ptcsPos[ptc_i][xi] += ptcsV[ptc_i][xi];
            ptcsPos[ptc_i][xi] = ptcsPos[ptc_i][xi] > MAP_UPPER_BOUND ? MAP_UPPER_BOUND : ptcsPos[ptc_i][xi]
            ptcsPos[ptc_i][xi] = ptcsPos[ptc_i][xi] < MAP_LOWER_BOUND ? MAP_LOWER_BOUND : ptcsPos[ptc_i][xi]

    for pi in (0:PTC_AMOUNT):
        updateVelocity(ptcsV[ptc_i], ptcsPos[ptc_i], ptcsPBestPos[ptc_i], ptcsGBestPos, X_DIM, INERTIA_WEIGHT, P_LEARNING_FACTOR, G_LEARNING_FACTOR, V_UPPER_BOUND, V_LOWER_BOUND)

    for pi in (0:PTC_AMOUNT):
        tmp_ack_value = ackley2d(ptcsPos[ptc_i], X_DIM)
        better_checkpoint = 0
        if (tmp_ack_value < ptcsPBestFitness[ptc_i]):
            better_checkpoint = 1

            for (int xi = 0; xi < X_DIM; xi++):
                ptcsPBestPos[ptc_i][xi] = ptcsPos[ptc_i][xi]
            ptcsPBestFitness[ptc_i] = ackley2d(ptcsPBestPos[ptc_i], X_DIM)

        if (better_checkpoint && tmp_ack_value < ptcsGBestFitness)
            for (int xi = 0; xi < X_DIM; xi++):
                ptcsPBestPos[ptc_i][xi] = ptcsPos[ptc_i][xi]
            ptcsGBestFitness = tmp_ack_value

實驗結果
    最佳解: 0.000526707
    平均最佳解: 0.0420514
    結果分析: ackley function 的最佳解在整個解空間的正中間，或許對 PSO 的設計也更加有利