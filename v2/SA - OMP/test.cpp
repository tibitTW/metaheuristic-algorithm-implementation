// #include "onemax.h"
#include "sa.h"
#include <fstream>
#include <iostream>
#include <math.h>
#include <stdio.h>

using namespace std;

int main() {
    double temp = 1000;
    while (temp > 20) {
        printf("temp: %lf, P: %lf\n", temp, P(80, 70, temp));
        temp *= .995;
    }
    return 0;
}