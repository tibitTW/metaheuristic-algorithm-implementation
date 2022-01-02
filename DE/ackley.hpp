#include <math.h>
#include <vector>

using std::vector;

double ackley(vector<double> x, double a = 20, double b = 0.2, double c = 3);

double ackley(vector<double> x, double a, double b, double c) {
    double term1 = 0, term2 = 0;
    for (double xn : x) {
        term1 += xn * xn;
        term2 += cos(c * xn);
    }
    term1 = (-1) * a * exp((-1) * b * term1 / x.size());
    term2 = (-1) * exp(term2 / x.size());

    return term1 + term2 + a + exp(1);
}