#include <functional>
#include <istream>
#include <iostream>
#include <dlfcn.h>

const inline std::string pathToF1 = "./libf1.so";
const inline std::string pathToF2 = "./libf2.so";

typedef float (*PrimeNumsPointer)(int a);
typedef std::vector<int> (*SortPointer)(std::vector<int> a);

void handlePrimeNumbers(const std::function<int(int A, int B)>& CalcNums, std::istream& is, std::ostream& os) {
    int a, b;

    os << "Enter a and b: ";
    is >> a >> b;

    int result = CalcNums(a, b);
    os << "Result: " << result << std::endl;
}

void handleSort(const std::function<std::vector<int> (std::vector<int>)>& SortingMethod, std::istream& is, std::ostream& os) {
    std::vector<int> numsList;
    size_t size;

    os << "Enter the size of the array: ";
    is >> size;

    os << "Enter the array elements separated by a space: ";
    int val;
    for (auto i = 0; i < size; ++i){
        is >> val;
        numsList.push_back(val);
    }

    auto result = SortingMethod(numsList);
    os << "Result: ";
    for (auto& item: result) os << item << " " << std::endl;
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
