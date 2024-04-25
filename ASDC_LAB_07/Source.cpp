#include <iostream>
#include <vector>
#include <span>
#include <chrono>
#include <functional>

using namespace std;

struct Data {
    int key;
    string value;
};

bool compare(const Data& a, const Data& b) {
    return a.key < b.key;
}

template<typename Func>
double measureTime(Func& func, span<Data> arr, int& comparisons, int& swaps) {
    int n = arr.size();
    comparisons = 0;
    swaps = 0;

    auto start = chrono::steady_clock::now();

    func(arr, comparisons, swaps);

    auto end = chrono::steady_clock::now();
    chrono::duration<double> elapsed_seconds = end - start;

    return elapsed_seconds.count();
}

void bubbleSort(span<Data> arr, int& comparisons, int& swaps) {
    int n = arr.size();

    for (int i = 0; i < n - 1; ++i) {
        for (int j = 0; j < n - i - 1; ++j) {
            ++comparisons;
            if (compare(arr[j + 1], arr[j])) {
                swap(arr[j], arr[j + 1]);
                ++swaps;
            }
        }
    }
}

void insertionSort(span<Data> arr, int& comparisons, int& swaps) {
    int n = arr.size();

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
}

void selectionSort(span<Data> arr, int& comparisons, int& swaps) {
    int n = arr.size();

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
}

void shellSort(span<Data> arr, int& comparisons, int& swaps) {
    int n = arr.size();

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
}

void heapify(span<Data> arr, int n, int i, int& comparisons, int& swaps) {
    int largest = i;
    int left = 2 * i + 1;
    int right = 2 * i + 2;

    if (left < n && compare(arr[left], arr[largest]))
        largest = left;

    if (right < n&& compare(arr[right], arr[largest]))
        largest = right;

    if (largest != i) {
        swap(arr[i], arr[largest]);
        ++swaps;
        heapify(arr, n, largest, comparisons, swaps);
    }
}

void heapSort(span<Data> arr, int& comparisons, int& swaps) {
    int n = arr.size();

    for (int i = n / 2 - 1; i >= 0; --i)
        heapify(arr, n, i, comparisons, swaps);

    for (int i = n - 1; i > 0; --i) {
        swap(arr[0], arr[i]);
        ++swaps;
        heapify(arr, i, 0, comparisons, swaps);
    }
}

int main() {
    vector<Data> data = { {5, "five"}, {2, "two"}, {9, "nine"}, {1, "one"}, {5, "five"}, {6, "six"} };
    int comparisons, swaps;

    double time_taken = measureTime(bubbleSort, data, comparisons, swaps);
    cout << "Bubble Sort: Time taken: " << time_taken << " seconds\n";

    time_taken = measureTime(insertionSort, data, comparisons, swaps);
    cout << "Insertion Sort: Time taken: " << time_taken << " seconds\n";

    time_taken = measureTime(selectionSort, data, comparisons, swaps);
    cout << "Selection Sort: Time taken: " << time_taken << " seconds\n";

    time_taken = measureTime(shellSort, data, comparisons, swaps);
    cout << "Shell Sort: Time taken: " << time_taken << " seconds\n";

    time_taken = measureTime(heapSort, data, comparisons, swaps);
    cout << "Heap Sort: Time taken: " << time_taken << " seconds\n";

    return 0;
}
