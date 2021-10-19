#include <ctime>
#include <iostream>
#include <random>
#include <vector>

using namespace std;

int main() {
    vector<int> V;
    V.resize(10);
    for (auto a : V)
        cout << a << "-";
    cout << endl;

    return 0;
}