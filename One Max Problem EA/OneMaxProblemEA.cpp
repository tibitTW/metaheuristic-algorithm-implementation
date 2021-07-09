#include <iomanip>
#include <iostream>
#include <time.h>

#define BIT_SIZE 100
#define TIME_LIMIT_IN_SEC 1800.0

using namespace std;

int main() {
    clock_t begin = clock();

    unsigned sum, max_of_sum = 0;
    unsigned long long n = 0, n_2 = 0, tmp, tmp2;

    while (1) {
        tmp = n;
        tmp2 = n_2;
        sum = 0;
        for (int i = 0; i < sizeof(unsigned long long) * 8; i++) {
            sum += tmp & 1;
            tmp >>= 1;
        }
        for (int i = 0; i < BIT_SIZE - (sizeof(unsigned long long) * 8); i++) {
            sum += tmp2 & 1;
            tmp2 >>= 1;
        }

        if (sum >= max_of_sum) {
            max_of_sum = sum;
            tmp = n;
            tmp2 = n_2;
            for (int i = 0; i < sizeof(unsigned long long) * 8; i++) {
                cout << (tmp & 1);
                tmp >>= 1;
            }
            for (int i = 0; i < BIT_SIZE - (sizeof(unsigned long long) * 8); i++) {
                cout << (tmp2 & 1);
                tmp2 >>= 1;
            }
            cout << " : score = " << setfill(' ') << setw(2) << max_of_sum << endl;
        }

        // calculate time
        clock_t t = clock();
        double current_time = (double)(t - begin) / CLOCKS_PER_SEC;
        if (current_time > TIME_LIMIT_IN_SEC) {
            cout << "time spent : " << current_time << " s\n";
            break;
        }
        n++;
        if (n == 0)
            n_2++;
    }

    cout << "best fitness : " << max_of_sum << endl;
    return 0;
}
