#include <vector>
#include "lib2.h"

int HardPrimeNumbers(int A, int B) {
    int max = std::max(A, B);
    std::vector<bool> isPrime(max + 1, true);
    isPrime[0] = isPrime[1] = false;
    for (int i = 2; i * i <= max; ++i) {
        if (isPrime[i]) {
            for (int j = i * i; j <= max; j += i) {
                isPrime[j] = false;
            }
        }
    }

    int count = 0;
    for (int i = A; i <= B; ++i) {
        if (isPrime[i]) {
            count++;
        }
    }

    return count;
}

std::vector<int> HoarSort(std::vector<int> array) {
    if (array.size() < 2)
        return array;
    int pivotIndex = array.size() / 2;
    int pivot = array[pivotIndex];
    std::vector<int> result, greater;
    for (int i = 0; i < array.size(); ++i) {
        if (i == pivotIndex) continue;
        if (array[i] < pivot) result.push_back(array[i]);
        else greater.push_back(array[i]);
    }
    result = HoarSort(result);
    greater = HoarSort(greater);
    result.push_back(pivot);
    result.insert(result.end(), greater.begin(), greater.end());
    return result;
}
