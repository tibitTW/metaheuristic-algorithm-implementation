#include <iomanip>
#include <iostream>

using namespace std;

int main() {

    double a = 123.456789;
    cout << fixed << setprecision(3) << a << endl;
    return 0;
}