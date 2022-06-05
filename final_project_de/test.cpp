#include "test_function.hpp"

#include <iostream>
#include <vector>

typedef vector<double> d1d;

using namespace std;

int main() {
    d1d a = {-2.715690, 1.822122};
    cout << ackley(a) << endl;

    return 0;
}