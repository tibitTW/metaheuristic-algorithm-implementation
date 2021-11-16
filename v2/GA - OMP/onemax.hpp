#include <functional>
#include <random>
#include <stdlib.h>
#include <vector>

using std::vector;

namespace onemax {

typedef vector<bool> solution;

std::random_device rd;
std::mt19937 generator(rd());
std::uniform_int_distribution<int> distribution(0, 1);
auto bool_dice = std::bind(distribution, generator);

void init(onemax::solution &sol) {
    for (int si = 0; si < sol.size(); si++) {
        sol.at(si) = bool_dice();
    }
}

int fitness(const onemax::solution sol) {
    int f = 0;
    for (int si = 0; si < sol.size(); si++)
        f += sol.at(si);
    return f;
}

} // namespace onemax