#include <random>
#include <vector>

using std::vector;

// solution datatype
typedef vector<double> S;

namespace DE {
void initialization() {
    // TODO : initialization random
}
void crossover();

/*
strategy_id:
0: rand/1
1: rand/2
2: best/1
3: current-to-best/1
*/
void mutation(int strategy_id) {
    switch (strategy_id) {

    // rand/1
    case 0:
        break;

    // rand/2
    case 1:
        break;

    // best/1
    case 2:
        break;

    // current-to-best/1
    case 3:
        break;

    // current-to-pbest/1
    case 4:
        break;

    default:
        break;
    }
}

void selection();

// DE(crossover_rate, scaling_factor, num_of_population)
double DE(const double CR, const double F, const int NP) { initialization(); }
// DE(crossover_rate, scaling_factor, num_of_population)
double SHADE(double) { initialization(); }

} // namespace DE