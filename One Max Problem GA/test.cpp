#include "ga.h"
#include <iostream>
#include <vector>

using namespace std;

int main() {
    vector<int> res;
    ga::ga(10, 10, 10, 0.8, 0.1, res);
    cout << res.size();
    return 0;
}