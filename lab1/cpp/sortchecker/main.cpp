#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <sstream>
#include <chrono>
#include <filesystem>
#include <random>
#include <algorithm>
#include <map>
#include <thread>
namespace fs = std::filesystem;

// Тип сортировки
template<typename T>
using SortMethod = void(*)(std::vector<T>&);

// Проверка времени выполнения
using TimeVerifier = bool(*)(long long, long long);

void generateTestArrays() {
    fs::create_directory("TestArrays");

    auto generateRandomArray = [](int size, int min, int max) {
        std::vector<int> array(size);
        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_int_distribution<> dis(min, max);
        for (int& x : array) {
            x = dis(gen);
        }
        return array;
    };

    auto generateAlmostSortedArray = [](int size, int swaps) {
        std::vector<int> array(size);
        for (int i = 0; i < size; ++i) array[i] = i;

        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_int_distribution<> dis(0, size - 1);

        for (int i = 0; i < swaps; ++i) {
            int idx1 = dis(gen), idx2 = dis(gen);
            std::swap(array[idx1], array[idx2]);
        }
        return array;
    };

    auto generateReverseSortedArray = [](int size) {
        std::vector<int> array(size);
        for (int i = 0; i < size; ++i) array[i] = size - i - 1;
        return array;
    };

    auto saveArray = [](const std::string& filename, const std::vector<int>& array) {
        std::ofstream file(filename);
        for (int i = 0; i < array.size(); ++i) {
            file << array[i];
            if (i != array.size() - 1) file << " ";
        }
    };

    saveArray("TestArrays/small_arr.txt", generateRandomArray(20, 0, 100));
    saveArray("TestArrays/mid_rand.txt", generateRandomArray(500, 0, 1000));
    saveArray("TestArrays/rand_nums.txt", generateRandomArray(5000, 0, 10000));
    saveArray("TestArrays/almost_sorted.txt", generateAlmostSortedArray(1000, 10));
    saveArray("TestArrays/reversed_arr.txt", generateReverseSortedArray(1000));
}

std::map<std::string, std::vector<int>> readTestArrays() {
    std::map<std::string, std::vector<int>> arrays;
    for (const auto& entry : fs::directory_iterator("TestArrays")) {
        std::ifstream file(entry.path());
        std::string content;
        std::getline(file, content);

        std::vector<int> array;
        std::stringstream ss(content);
        int number;
        while (ss >> number) {
            array.push_back(number);
        }
        arrays[entry.path().stem().string()] = array;
    }
    return arrays;
}

template<typename T>
void selectionSortEtalon(std::vector<T>& array) {
    for (int i = 0; i < array.size() - 1; ++i) {
        int minIndex = i;
        for (int j = i + 1; j < array.size(); ++j) {
            if (array[j] < array[minIndex])
                minIndex = j;
        }
        std::swap(array[i], array[minIndex]);
    }
}

template<typename T>
void shakerSortEtalon(std::vector<T>& array) {
    int left = 0, right = array.size() - 1;
    while (left < right) {
        for (int i = left; i < right; ++i) {
            if (array[i] > array[i + 1])
                std::swap(array[i], array[i + 1]);
        }
        --right;
        for (int i = right; i > left; --i) {
            if (array[i] < array[i - 1])
                std::swap(array[i], array[i - 1]);
        }
        ++left;
    }
}

template<typename T>
void selectionSortStudent(std::vector<T>& array) {
    for (int i = 0; i < array.size() - 1; ++i) {
        int minIndex = i;
        for (int j = i + 1; j < array.size(); ++j) {
            if (array[j] < array[minIndex])
                minIndex = j;
        }
        std::swap(array[i], array[minIndex]);
    }
    std::this_thread::sleep_for(std::chrono::milliseconds(4)); 
}

template<typename T>
void shakerSortStudent(std::vector<T>& array) {
    int left = 0, right = array.size() - 1;
    while (left < right) {
        for (int i = left; i < right; ++i) {
            if (array[i] < array[i + 1]) 
                std::swap(array[i], array[i + 1]);
        }
        --right;
        for (int i = right; i > left; --i) {
            if (array[i] > array[i - 1])
                std::swap(array[i], array[i - 1]);
        }
        ++left;
    }
}

bool isTimeAcceptable(long long etalonTime, long long studentTime) {
    return studentTime < etalonTime * 1.5;
}

template<typename T>
long long measureSortingTime(SortMethod<T> sortMethod, const std::vector<T>& array) {
    auto arrayCopy = array;
    auto start = std::chrono::steady_clock::now();
    try {
        sortMethod(arrayCopy);
    } catch (...) {
        return -1;
    }
    auto end = std::chrono::steady_clock::now();
    return std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();
}

template<typename T>
bool areArraysEqual(const std::vector<T>& a1, const std::vector<T>& a2) {
    return a1 == a2;
}

template<typename T>
std::vector<T> performSorting(SortMethod<T> sortMethod, const std::vector<T>& array) {
    auto copy = array;
    try {
        sortMethod(copy);
    } catch (...) {
        return {};
    }
    return copy;
}

template<typename T>
void verifySorting(SortMethod<T> etalonMethod, SortMethod<T> studentMethod,
                   const std::map<std::string, std::vector<T>>& testArrays,
                   TimeVerifier timeVerifier) {
    for (const auto& [name, array] : testArrays) {
        std::cout << "\nDATASET: " << name << "\n";

        long long etalonTime = measureSortingTime(etalonMethod, array);
        if (etalonTime == -1) {
            std::cout << "Runtime Error in standart sort. Test skipped.\n";
            continue;
        }

        long long studentTime = measureSortingTime(studentMethod, array);
        if (studentTime == -1) {
            std::cout << "Result: Runtime error\n";
            continue;
        }

        auto etalonResult = performSorting(etalonMethod, array);
        auto studentResult = performSorting(studentMethod, array);

        bool resultsMatch = areArraysEqual(etalonResult, studentResult);
        bool timeAcceptable = timeVerifier(etalonTime, studentTime);

        std::cout << "Standard sort time: " << etalonTime << " ms\n";
        std::cout << "Student sort time: " << studentTime << " ms\n";

        std::string result = "Accepted";
        if (!resultsMatch)
            result = "Wrong answer";
        else if (!timeAcceptable)
            result = "Time limit exceeded";

        std::cout << "Result: " << result << "\n";
    }
}

int main() {
    generateTestArrays();
    auto testArrays = readTestArrays();

    std::cout << "\nSELECTION SORT:\n";
    verifySorting<int>(selectionSortEtalon, selectionSortStudent, testArrays, isTimeAcceptable);

    std::cout << "\nSHAKER SORT:\n";
    verifySorting<int>(shakerSortEtalon, shakerSortStudent, testArrays, isTimeAcceptable);

    return 0;
}
