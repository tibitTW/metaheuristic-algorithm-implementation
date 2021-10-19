#include <ctime>
#include <iostream>
#include <random>
#include <vector>

using namespace std;

typedef vector<int> V;
int main() {
    vector<V> P(4, V(4, 0));
    for (auto v : P) {
        cout << v.size() << endl;
        for (auto c : v)
            cout << c << "_";
        cout << endl;
    }

    return 0;
}