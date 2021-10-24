#include <bitset>
#include <iostream>
#include <time.h>

#define BIT_SIZE 100
using namespace std;

#define TIME_LIMIT CLOCKS_PER_SEC * 1800

bitset<BIT_SIZE> bs2;
bitset<BIT_SIZE> next(bitset<BIT_SIZE> bs) {
    bool hold = 1;
    bitset<BIT_SIZE> bs2;
    for (int i = 0; i < BIT_SIZE; i++) {
        bs2[i] = (bs[i] == hold) ? 0 : 1;
        hold = (bs[i] && hold) ? 1 : 0;
    }

    return bs2;
}
int fitness(bitset<BIT_SIZE> bs) { return bs.count(); }

int main() {
    bitset<BIT_SIZE> sol, best_sol;
    int f, best_f = 0;
    clock_t clock_b;
    clock_b = clock();
    while ((double)(clock() - clock_b) < TIME_LIMIT) {
        f = fitness(sol);
        if (f > best_f) {
            best_f = f;
            best_sol = sol;
        }
        sol = next(sol);
    }

    cout << "best sol: " << best_sol << ": " << best_f << endl;
}