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

struct Sort {
    int comparisons = 0;
    int swaps = 0;
};



bool compare(const Data& a, const Data& b) {
    return a.key < b.key;
}

template<typename Func>
double measureTime(Func& func, span<Data> arr, Sort& sort) {
    int n = arr.size();
    sort = {};

    auto start = chrono::steady_clock::now();

    func(arr, sort);

    auto end = chrono::steady_clock::now();
    chrono::duration<double> elapsed_seconds = end - start;

    return elapsed_seconds.count();
}

void bubbleSort(span<Data> arr, Sort& sort) {
    int n = arr.size();

    for (int i = 0; i < n - 1; ++i) {
        for (int j = 0; j < n - i - 1; ++j) {
            ++sort.comparisons;
            if (compare(arr[j + 1], arr[j])) {
                swap(arr[j], arr[j + 1]);
                ++sort.swaps;
            }
        }
    }
}

void insertionSort(span<Data> arr, Sort& sort) {
    int n = arr.size();

    for (int i = 1; i < n; ++i) {
        Data key = arr[i];
        int j = i - 1;
        while (j >= 0 && compare(key, arr[j])) {
            ++sort.comparisons;
            arr[j + 1] = arr[j];
            ++sort.swaps;
            j = j - 1;
        }
        arr[j + 1] = key;
    }
}

void selectionSort(span<Data> arr, Sort& sort) {
    int n = arr.size();

    for (int i = 0; i < n - 1; ++i) {
        int min_idx = i;
        for (int j = i + 1; j < n; ++j) {
            ++sort.comparisons;
            if (compare(arr[j], arr[min_idx])) {
                min_idx = j;
            }
        }
        swap(arr[min_idx], arr[i]);
        ++sort.swaps;
    }
}

void shellSort(span<Data> arr, Sort& sort) {
    int n = arr.size();

    for (int gap = n / 2; gap > 0; gap /= 2) {
        for (int i = gap; i < n; ++i) {
            Data temp = arr[i];
            int j;
            for (j = i; j >= gap && compare(arr[j - gap], temp); j -= gap) {
                ++sort.comparisons;
                arr[j] = arr[j - gap];
                ++sort.swaps;
            }
            arr[j] = temp;
        }
    }
}

void heapify(span<Data> arr, int n, int i, Sort& sort) {
    int largest = i;
    int left = 2 * i + 1;
    int right = 2 * i + 2;

    if (left < n && compare(arr[left], arr[largest]))
        largest = left;

    if (right < n&& compare(arr[right], arr[largest]))
        largest = right;

    if (largest != i) {
        swap(arr[i], arr[largest]);
        ++sort.swaps;
        heapify(arr, n, largest, sort);
    }
}

void heapSort(span<Data> arr, Sort& sort) {
    int n = arr.size();

    for (int i = n / 2 - 1; i >= 0; --i)
        heapify(arr, n, i, sort);

    for (int i = n - 1; i > 0; --i) {
        swap(arr[0], arr[i]);
        ++sort.swaps;
        heapify(arr, i, 0, sort);
    }
}

int main() {
    vector<Data> data = { {5, "five"}, {2, "two"}, {9, "nine"}, {1, "one"}, {5, "five"}, {6, "six"} };
    Sort sort;

    double time_taken = measureTime(bubbleSort, data, sort);
    cout << "Bubble Sort: Time taken: " << time_taken << " seconds\n";
    cout << "Comparisons: " << sort.comparisons << "\n";
    cout << "Swaps: " << sort.swaps << "\n";

    time_taken = measureTime(insertionSort, data, sort);
    cout << "Insertion Sort: Time taken: " << time_taken << " seconds\n";
    cout << "Comparisons: " << sort.comparisons << "\n";
    cout << "Swaps: " << sort.swaps << "\n";

    time_taken = measureTime(selectionSort, data, sort);
    cout << "Selection Sort: Time taken: " << time_taken << " seconds\n";
    cout << "Comparisons: " << sort.comparisons << "\n";
    cout << "Swaps: " << sort.swaps << "\n";

    time_taken = measureTime(shellSort, data, sort);
    cout << "Shell Sort: Time taken: " << time_taken << " seconds\n";
    cout << "Comparisons: " << sort.comparisons << "\n";
    cout << "Swaps: " << sort.swaps << "\n";

    time_taken = measureTime(heapSort, data, sort);
    cout << "Heap Sort: Time taken: " << time_taken << " seconds\n";
    cout << "Comparisons: " << sort.comparisons << "\n";
    cout << "Swaps: " << sort.swaps << "\n";

    return 0;
}
