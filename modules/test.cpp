#include <ctime>
#include <iostream>
#include <random>

using namespace std;

int main() {
    random_device rd;
    default_random_engine generator(rd());
    uniform_real_distribution<float> unif(-10.0, 10.0);

    float x;
    for (int i = 0; i < 1000; i++) {
        x = unif(generator);
        cout << x << endl;
    }
}