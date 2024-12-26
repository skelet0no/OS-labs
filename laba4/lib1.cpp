#include "lib1.h"

bool isPrime(int num) {
    if (num <= 1) {
        return false;
    } for (int i = 2; i * i <= num; ++i) {
        if (num % i == 0) {
            return false;
        }
    }
    return true;
}

int SimplePrimeNumbers(int A, int B) {
    int count = 0;
    for (int i = A; i <= B; ++i) {
        if (isPrime(i)) {
            count++;
        }
    } return count;
}

std::vector<int> BubbleSort(std::vector<int> arr) {
    bool swapped = true;
    int n = arr.size();
    while (swapped) {
        swapped = false;
        for (int i = 0; i < n - 1; ++i) {
            if (arr[i] > arr[i + 1]) {
                std::swap(arr[i], arr[i + 1]);
                swapped = true;
            }
        }
    } return arr;
}
