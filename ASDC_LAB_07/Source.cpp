#include <iostream>
#include <vector>
#include <span>
#include <chrono>

using namespace std;

struct Data {
    int key;
    string value;
};

bool compare(const Data& a, const Data& b) {
    return a.key < b.key;
}

void bubbleSort(span<Data> arr, int& comparisons, int& swaps) {
    int n = arr.size();
    comparisons = 0;
    swaps = 0;

    auto start = chrono::steady_clock::now();

    for (int i = 0; i < n - 1; ++i) {
        for (int j = 0; j < n - i - 1; ++j) {
            ++comparisons;
            if (compare(arr[j + 1], arr[j])) {
                swap(arr[j], arr[j + 1]);
                ++swaps;
            }
        }
    }

    auto end = chrono::steady_clock::now();
    chrono::duration<double> elapsed_seconds = end - start;
    cout << "Bubble Sort: Time taken: " << elapsed_seconds.count() << " seconds\n";
}

void insertionSort(span<Data> arr, int& comparisons, int& swaps) {
    int n = arr.size();
    comparisons = 0;
    swaps = 0;

    auto start = chrono::steady_clock::now();

    for (int i = 1; i < n; ++i) {
        Data key = arr[i];
        int j = i - 1;
        while (j >= 0 && compare(key, arr[j])) {
            ++comparisons;
            arr[j + 1] = arr[j];
            ++swaps;
            j = j - 1;
        }
        arr[j + 1] = key;
    }

    auto end = chrono::steady_clock::now();
    chrono::duration<double> elapsed_seconds = end - start;
    cout << "Insertion Sort: Time taken: " << elapsed_seconds.count() << " seconds\n";
}

void selectionSort(span<Data> arr, int& comparisons, int& swaps) {
    int n = arr.size();
    comparisons = 0;
    swaps = 0;

    auto start = chrono::steady_clock::now();

    for (int i = 0; i < n - 1; ++i) {
        int min_idx = i;
        for (int j = i + 1; j < n; ++j) {
            ++comparisons;
            if (compare(arr[j], arr[min_idx])) {
                min_idx = j;
            }
        }
        swap(arr[min_idx], arr[i]);
        ++swaps;
    }

    auto end = chrono::steady_clock::now();
    chrono::duration<double> elapsed_seconds = end - start;
    cout << "Selection Sort: Time taken: " << elapsed_seconds.count() << " seconds\n";
}

void shellSort(span<Data> arr, int& comparisons, int& swaps) {
    int n = arr.size();
    comparisons = 0;
    swaps = 0;

    auto start = chrono::steady_clock::now();

    for (int gap = n / 2; gap > 0; gap /= 2) {
        for (int i = gap; i < n; ++i) {
            Data temp = arr[i];
            int j;
            for (j = i; j >= gap && compare(arr[j - gap], temp); j -= gap) {
                ++comparisons;
                arr[j] = arr[j - gap];
                ++swaps;
            }
            arr[j] = temp;
        }
    }

    auto end = chrono::steady_clock::now();
    chrono::duration<double> elapsed_seconds = end - start;
    cout << "Shell Sort: Time taken: " << elapsed_seconds.count() << " seconds\n";
}

int main() {
    vector<Data> data = { {5, "five"}, {2, "two"}, {9, "nine"}, {1, "one"}, {5, "five"}, {6, "six"} };
    int comparisons, swaps;

    bubbleSort(data, comparisons, swaps);
    cout << "Comparisons: " << comparisons << ", Swaps: " << swaps << "\n\n";

    constexpr int num_runs = 5;
    double total_time = 0;

    for (int i = 0; i < num_runs; ++i) {
        vector<Data> data_copy = data;
        bubbleSort(data_copy, comparisons, swaps);
        total_time += elapsed_seconds.count();
    }

    cout << "Total time for Bubble Sort: " << total_time << " seconds\n";
    cout << "Average time for Bubble Sort: " << total_time / num_runs << " seconds\n";

    return 0;
}
