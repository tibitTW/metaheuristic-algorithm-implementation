#include <cmath>
#include <vector>

#define PI 3.141592653589793

using std::vector;

typedef vector<double> d1d;

// x limits : [-32.768, 32.768]
double ackley(d1d x, int a = 20, double b = 0.2, double c = 2 * PI) {
    double term1 = 0, term2 = 0;
    for (int i = 0; i < x.size(); i++) {
        term1 += x.at(i) * x.at(i);
        term2 += cos(c * x.at(i));
    }
    term1 /= x.size();
    term2 /= x.size();

    return (-1) * a * exp((-1) * b * sqrt(term1)) - exp(term2) + a + exp(1);
}

// x limits : [-600, 600]
double griewank(d1d x) {
    double term1 = 0, term2 = 1;
    for (int i = 0; i < x.size(); i++) {
        term1 += x.at(i) * x.at(i) / 4000;
        term2 *= cos(x.at(i) / sqrt(i + 1));
    }

    return term1 - term2 + 1;
}

// x limits : [-5.12, 5.12]
double rastrigin(d1d x) {
    double term2 = 0;
    for (int i = 0; i < x.size(); i++)
        term2 += x.at(i) * x.at(i) - 10 * cos(2 * PI * x.at(i));

    return 10 * x.size() + term2;
}

// x limits : [-500, 500]
double schwefel(d1d x) {
    double term2 = 0;
    for (int i = 0; i < x.size(); i++)
        term2 += x.at(i) * sin(sqrt(abs(x.at(i))));

    return 418.9829 * x.size() - term2;
}

// x limits : [-5.12, 5.12]
double sphere(d1d x) {
    double res = 0;
    for (int i = 0; i < x.size(); i++)
        res += x.at(i) * x.at(i);

    return res;
}

// x limits : [-5.12, 5.12]
double sum_squares(d1d x) {
    double res = 0;
    for (int i = 0; i < x.size(); i++)
        res += (i + 1) * x.at(i) * x.at(i);

    return res;
}

// x limits : [-5, 10]
double zakharov(d1d x) {
    double term1 = 0, term2 = 0, term3 = 0;
    for (int i = 0; i < x.size(); i++) {
        term1 += x.at(i) * x.at(i);
        term2 += 0.5 * (i + 1) * x.at(i);
        term3 += 0.5 * (i + 1) * x.at(i);
    }

    return term1 + pow(term2, 2) + pow(term3, 4);
}

// x limits : [-5, 10]
double rosenbrock(d1d x) {
    double res = 0;
    for (int i = 0; i < x.size() - 1; i++)
        res += 100 * (x.at(i + 1) - x.at(i) * x.at(i)) + (x.at(i) - 1) * (x.at(i) - 1);

    return res;
}

// x limits : [0, pi]
double michalewicz(d1d x, double m = 10) {
    double res = 0;
    for (int i = 0; i < x.size(); i++)
        res += sin(x.at(i)) * pow(sin((i + 1) * x.at(i) * x.at(i) / PI), 2 * m);

    return (-1) * res;
}

// x limits : [-4, 5]
double powell(d1d x) {
    double res = 0;

    for (int i = 0; i < x.size() / 4; i++) {
        res += pow(x.at(4 * i) + x.at(4 * i + 2) * 10, 2) +
               pow(x.at(4 * i + 2) - x.at(4 * i), 2) * 5 +
               pow(x.at(4 * i + 1) - x.at(4 * i + 3) * 2, 4) +
               pow(x.at(4 * i) + x.at(4 * i + 3), 4) * 10;
    }

    return res;
}

double test_func(d1d x, const int TEST_FUNC_ID) {
    switch (TEST_FUNC_ID) {

    case 0:
        return ackley(x);

    case 1:
        return griewank(x);

    case 2:
        return rastrigin(x);

    case 3:
        return schwefel(x);

    case 4:
        return sphere(x);

    case 5:
        return sum_squares(x);

    case 6:
        return zakharov(x);

    case 7:
        return rosenbrock(x);

    case 8:
        return michalewicz(x);

    case 9:
        return powell(x);

    default:
        break;
    }

    return 0;
}