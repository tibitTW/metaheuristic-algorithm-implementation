#include <cstdio>
#include <ctime>
#include <iostream>
#include <random>
#include <string.h>
#include <vector>

using namespace std;

int main(int argc, char *argv[]) {
    for (int i = 1; i <= argc; i++) {
        cout << argv[i] << endl;
    }
    return 0;
}