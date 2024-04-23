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
	size_t n = arr.size();
	for (int i = 0; i < n - 1; ++i) {
		for (int j = 0; j < n - i - 1; ++j) {
			if (compare(arr[j], arr[j + 1])) {
				std::swap(arr[j], arr[j + 1]);
			}
		}
	}
}

// Insertion Sort
template<typename T>
void insertionSort(std::span<T> arr) {
	size_t n = arr.size();
	for (int i = 1; i < n; ++i) {
		T key = std::move(arr[i]);
		int j = i - 1;
		while (j >= 0 && compare(key, arr[j])) {
			arr[j + 1] = arr[j];
			--j;
		}
		arr[j + 1] = key;
	}
}

// Selection Sort
template<typename T>
void selectionSort(std::span<T> arr) {
	size_t n = arr.size();
	for (int i = 0; i < n - 1; ++i) {
		int min_index = i;
		for (int j = i + 1; j < n; ++j) {
			if (compare(arr[j], arr[min_index])) {
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
	int n = static_cast<int>(arr.size());
	for (int gap = n / 2; gap > 0; gap /= 2) {
		for (int i = gap; i < n; ++i) {
			T temp = std::move(arr[i]);
			int j;
			for (j = i; j >= gap && compare(temp, arr[j - gap]); j -= gap) {
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
	if (left < n && compare(arr[largest], arr[left])) {
		largest = left;
	}
	if (right < n&& compare(arr[largest], arr[right])) {
		largest = right;
	}
	if (largest != i) {
		std::swap(arr[i], arr[largest]);
		heapify(arr, n, largest);
	}
}

template<typename T>
void heapSort(std::span<T> arr) {
	int n = static_cast<int>(arr.size());
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


// Quick Sort

template<typename T>
void qsort(std::span<T> arr) {
	int low = 0;
	int high = static_cast<int>(arr.size()) - 1;
	qsortImpl(arr, low, high);
}

template<typename T>
void qsortImpl(std::span<T> arr, int b, int e) {
	int l = b, r = e;
	auto piv = arr[(l + r) / 2];

	while (l <= r) {
		while (compare(arr[l],piv))
			l++;
		while (compare(piv,arr[r]))
			r--;
		if (l <= r) {
			std::swap(arr[l], arr[r]);
			l++;
			r--;
		}
	}
	if (b < r)
		qsortImpl(arr, b, r);
	if (e > l)
		qsortImpl(arr, l, e);
}





int main() {
	std::vector<MyStruct> numberArr = { {5}, {1}, {8}, {3}, {9}, {2}, {7} };
	std::span<MyStruct> arr{ numberArr };

	// Пример вызова функций сортировки
	bubbleSort(arr);
	insertionSort(arr);
	selectionSort(arr);
	shellSort(arr);
	heapSort(arr);
	qsort(arr);

	// Вывод отсортированного массива
	for (const auto& elem : arr) {
		std::cout << elem.value << " ";
	}
	std::cout << std::endl;

	return 0;
}
