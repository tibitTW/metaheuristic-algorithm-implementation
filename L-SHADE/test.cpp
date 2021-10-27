#include "de.hpp"

#include <cstdio>
#include <ctime>
#include <iostream>
#include <random>
#include <vector>

using namespace std;

void swap(int &a, int &b) {
    int tmp = a;
    a = b;
    b = tmp;
}
int Partition(vector<int> &arr, int front, int end) {
    int pivot = arr[end];
    int i = front - 1;
    for (int j = front; j < end; j++) {
        if (arr[j] < pivot) {
            i++;
            swap(arr[i], arr[j]);
        }
    }
    i++;
    swap(arr[i], arr[end]);
    return i;
}
void QuickSort(vector<int> &arr, int front, int end) {
    if (front < end) {
        int pivot = Partition(arr, front, end);
        QuickSort(arr, front, pivot - 1);
        QuickSort(arr, pivot + 1, end);
    }
}

int main() {
    vector<int> v1 = {19, 10, 8, 5, 6, 15, 12, 9, 3, 16, 11, 17, 2, 18, 4, 1, 13, 20, 7, 14};
    QuickSort(v1, 0, v1.size() - 1);

    for (auto i : v1)
        cout << i << " ";

    // DE de(100, 1000, 10, -30.0, 30.0);
    // de.test();
    // de.run();

    return 0;
}