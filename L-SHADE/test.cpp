#include "cec17_test_func.h"

#include <cstdio>
#include <ctime>
#include <iostream>
#include <random>
#include <string.h>
#include <vector>

using namespace std;

int main() {
    char c1[] = "abcde";
    char *c2 = (char *)malloc(5 * sizeof(char));
    strcpy(c2, c1);
    printf("%s\n", c1);
    printf("%s\n", c2);

    return 0;
}