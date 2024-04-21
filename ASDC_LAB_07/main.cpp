#include <iostream>
#include <vector>
#include <span>

// Пример структуры из второй лабораторной работы
struct MyStruct {
    int value;
    // Другие поля, методы и т.д.
};

// Функция сравнения элементов для сортировки
bool compare(const MyStruct& a, const MyStruct& b) {
    return a.value < b.value;
}

// Bubble Sort
template<typename T>
void bubbleSort(std::span<T> arr) {
    int n = arr.size();
    for (int i = 0; i < n - 1; ++i) {
        for (int j = 0; j < n - i - 1; ++j) {
            if (arr[j] > arr[j + 1]) {
                std::swap(arr[j], arr[j + 1]);
            }
        }
    }
}

// Insertion Sort
template<typename T>
void insertionSort(std::span<T> arr) {
    int n = arr.size();
    for (int i = 1; i < n; ++i) {
        T key = arr[i];
        int j = i - 1;
        while (j >= 0 && arr[j] > key) {
            arr[j + 1] = arr[j];
            --j;
        }
        arr[j + 1] = key;
    }
}

// Selection Sort
template<typename T>
void selectionSort(std::span<T> arr) {
    int n = arr.size();
    for (int i = 0; i < n - 1; ++i) {
        int min_index = i;
        for (int j = i + 1; j < n; ++j) {
            if (arr[j] < arr[min_index]) {
                min_index = j;
            }
        }
        if (min_index != i) {
            std::swap(arr[i], arr[min_index]);
        }
    }
}

// Shell Sort
template<typename T>
void shellSort(std::span<T> arr) {
    int n = arr.size();
    for (int gap = n / 2; gap > 0; gap /= 2) {
        for (int i = gap; i < n; ++i) {
            T temp = arr[i];
            int j;
            for (j = i; j >= gap && arr[j - gap] > temp; j -= gap) {
                arr[j] = arr[j - gap];
            }
            arr[j] = temp;
        }
    }
}

// Heap Sort
template<typename T>
void heapify(std::vector<T>& arr, int n, int i) {
    int largest = i;
    int left = 2 * i + 1;
    int right = 2 * i + 2;
    if (left < n && arr[left] > arr[largest]) {
        largest = left;
    }
    if (right < n && arr[right] > arr[largest]) {
        largest = right;
    }
    if (largest != i) {
        std::swap(arr[i], arr[largest]);
        heapify(arr, n, largest);
    }
}

template<typename T>
void heapSort(std::span<T> arr) {
    int n = arr.size();
    std::vector<T> temp(arr.begin(), arr.end());
    for (int i = n / 2 - 1; i >= 0; --i) {
        heapify(temp, n, i);
    }
    for (int i = n - 1; i > 0; --i) {
        std::swap(temp[0], temp[i]);
        heapify(temp, i, 0);
    }
    std::copy(temp.begin(), temp.end(), arr.begin());
}

// Merge Sort
template<typename T>
void merge(std::span<T> arr, int l, int m, int r) {
    int n1 = m - l + 1;
    int n2 = r - m;
    std::vector<T> L(n1), R(n2);
    for (int i = 0; i < n1; ++i) {
        L[i] = arr[l + i];
    }
    for (int j = 0; j < n2; ++j) {
        R[j] = arr[m + 1 + j];
    }
    int i = 0, j = 0, k = l;
    while (i < n1 && j < n2) {
        if (L[i] <= R[j]) {
            arr[k] = L[i];
            ++i;
        }
        else {
            arr[k] = R[j];
            ++j;
        }
        ++k;
    }
    while (i < n1) {
        arr[k] = L[i];
        ++i;
        ++k;
    }
    while (j < n2) {
        arr[k] = R[j];
        ++j;
        ++k;
    }
}

template<typename T>
void mergeSort(std::span<T> arr, int l, int r) {
    if (l < r) {
        int m = l + (r - l) / 2;
        mergeSort(arr, l, m);
        mergeSort(arr, m + 1, r);
        merge(arr, l, m, r);
    }
}

template<typename T>
void mergeSort(std::span<T> arr) {
    mergeSort(arr, 0, arr.size() - 1);
}

// Quick Sort
template<typename T>
int partition(std::span<T> arr, int low, int high) {
    T pivot = arr[high];
    int i = low - 1;
    for (int j = low; j <= high - 1; ++j) {
        if (arr[j] < pivot) {
            ++i;
            std::swap(arr[i], arr[j]);
        }
    }
    std::swap(arr[i + 1], arr[high]);
    return i + 1;
}

template<typename T>
void quickSort(std::span<T> arr, int low, int high) {
    if (low < high) {
        int pi = partition(arr, low, high);
        quickSort(arr, low, pi - 1);
        quickSort(arr, pi + 1, high);
    }
}

template<typename T>
void quickSort(std::span<T> arr) {
    quickSort(arr, 0, arr.size() - 1);
}

// Radix Sort
template<typename T>
void countingSort(std::span<T> arr, int exp) {
    int n = arr.size();
    std::vector<T> output(n);
    int count[10] = { 0 };

    for (int i = 0; i < n; ++i) {
        count[(arr[i] / exp) % 10]++;
    }
    for (int i = 1; i < 10; ++i) {
        count[i] += count[i - 1];
    }
    for (int i = n - 1; i >= 0; --i) {
        output[count[(arr[i] / exp) % 10] - 1] = arr[i];
        count[(arr[i] / exp) % 10]--;
    }
    for (int i = 0; i < n; ++i) {
        arr[i] = output[i];
    }
}

template<typename T>
void radixSort(std::span<T> arr) {
    int max = *std::max_element(arr.begin(), arr.end());
    for (int exp = 1; max / exp > 0; exp *= 10) {
        countingSort(arr, exp);
    }
}

int main() {
    std::vector<MyStruct> arr = { {5}, {1}, {8}, {3}, {9}, {2}, {7} };

    // Пример вызова функций сортировки
    bubbleSort(arr);
    insertionSort(arr);
    selectionSort(arr);
    shellSort(arr);
    heapSort(arr);
    mergeSort(arr);
    quickSort(arr);
    radixSort(arr);

    // Вывод отсортированного массива
    for (const auto& elem : arr) {
        std::cout << elem.value << " ";
    }
    std::cout << std::endl;

    return 0;
}
