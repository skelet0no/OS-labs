#include <functional>
#include <istream>
#include <iostream>
#include <dlfcn.h>

const inline std::string pathToF1 = "./libf1.so";
const inline std::string pathToF2 = "./libf2.so";

typedef int (*PrimeNumsPointer)(int(int a, int b));
typedef std::vector<int> (*SortPointer)(std::vector<int> a);

using PrimeNumsFunc = std::function<int(int a, int b)>;
using SorterFunc = std::function<std::vector<int> (std::vector<int>)>;

void handlePrimeNumbers(const PrimeNumsFunc& CalcNums) {
    int a, b;

    std::cout << "Enter a and b: ";
    std::cin >> a >> b;

    int result = CalcNums(a, b);
    std::cout << "Result: " << result << std::endl;
}

void handleSort(const SorterFunc& SortingMethod) {
    std::vector<int> numsList;
    size_t size;

    std::cout << "Enter the size of the array: ";
    std::cin >> size;

    std::cout << "Enter the array elements separated by a space: ";
    int val;
    for (auto i = 0; i < size; ++i){
        std::cin >> val;
        numsList.push_back(val);
    }

    auto result = SortingMethod(numsList);
    std::cout << "Result: ";
    for (auto& item: result) std::cout << item << " ";
    std::cout << std::endl;
}

void handlePrimeNumbersDynamic(void* libHandle, const std::string& funcName) {
    auto pi = reinterpret_cast<PrimeNumsPointer>(dlsym(libHandle, funcName.c_str()));

    if (!pi) {
        std::cout << "Error while loading library: Can't use function " << funcName << std::endl;
        return;
    }

    handlePrimeNumbers(pi);
    dlclose(libHandle);
}

void handleSortDynamic(void* libHandle, const std::string& funcName) {
    auto pi = reinterpret_cast<SortPointer>(dlsym(libHandle, funcName.c_str()));

    if (!pi) {
        std::cout << "Error while loading library: Can't use function " << funcName << std::endl;
        return;
    }

    handleSort(pi);
    dlclose(libHandle);
}

void* loadLib(const std::string& path){
    void* libHandle = dlopen(path.c_str(), RTLD_LAZY);
    if (!libHandle) {
        std::cout << "Error while loading library: " << dlerror() << std::endl;
        return nullptr;
    }
    return libHandle;
}

int main(){
    auto command = 0;

    auto libHandle = dlopen(pathToF1.c_str(), RTLD_LAZY);
    auto isF1 = true;

    while (command != 5) {
        std::cout << "Enter command: ";
        std::cin >> command;

        switch (command) {
            case 0:
                if (isF1) {
                    libHandle = loadLib(pathToF2);
                    isF1 = false;
                }
                else {
                    libHandle = loadLib(pathToF1);
                    isF1 = true;
                }
                break;
            case 1:
                handlePrimeNumbersDynamic(libHandle, isF1 ? "SimplePrimeNumbers" : "HardPrimeNumbers");
                break;
            case 2:
                handleSortDynamic(libHandle, isF1 ? "BubbleSort" : "HoarSort");
                break;
            default:
                break;
        }

        if (command == 3) return 0;
    }
}
