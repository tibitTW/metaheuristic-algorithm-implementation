#include <cstdlib>
#include <iostream>
#include <math.h>
#include <set>
#include <time.h>
#include <vector>

#define CITY_DIM 10

using namespace std;
typedef vector<int> Chromo;

int main() {
    srand(time(NULL));
    Chromo c1{1, 2, 3, 4, 5, 6, 7, 8, 9}, c2{5, 4, 6, 9, 2, 1, 7, 8, 3};

    for (int c : c1)
        cout << c << " ";
    cout << endl;

    for (int c : c2)
        cout << c << " ";
    cout << endl;

    return 0;
}