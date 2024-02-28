#include <iostream>
#include <ctime>
#include <cstdlib>

template <typename T>
void printArray(T arr[], int size) {
    for (int i = 0; i < size; ++i) {
        std::cout << arr[i] << " ";
    }
    std::cout << std::endl;
}

template <typename T>
void bubbleSort(T arr[], int size) {
    for (int i = 0; i < size - 1; ++i) {
        for (int j = 0; j < size - i - 1; ++j) {
            if (arr[j] > arr[j + 1]) {
                std::swap(arr[j], arr[j + 1]);
            }
        }
    }
}

template <typename T>
int partition(T arr[], int low, int high) {
    int pivot = arr[high];
    int i = low - 1;
    for (int j = low; j < high; ++j) {
        if (arr[j] < pivot) {
            ++i;
            std::swap(arr[i], arr[j]);
        }
    }
    std::swap(arr[i + 1], arr[high]);
    return i + 1;
}

template <typename T>
int randomPartition(T arr[], int low, int high) {
    int randomIndex = low + rand() % (high - low + 1);
    std::swap(arr[randomIndex], arr[high]);
    return partition(arr, low, high);
}

template <typename T>
void quickSort(T arr[], int low, int high) {
    if (low < high) {
        int pivotIndex = randomPartition(arr, low, high);
        quickSort(arr, low, pivotIndex - 1);
        quickSort(arr, pivotIndex + 1, high);
    }
}

template <typename T>
void countingSort(T arr[], int size) {
    T maxElement = *std::max_element(arr, arr + size);
    T minElement = *std::min_element(arr, arr + size);
    int range = maxElement - minElement + 1;

    T* count = new T[range]();
    T* output = new T[size];

    for (int i = 0; i < size; ++i) {
        count[arr[i] - minElement]++;
    }

    for (int i = 1; i < range; ++i) {
        count[i] += count[i - 1];
    }

    for (int i = size - 1; i >= 0; --i) {
        output[count[arr[i] - minElement] - 1] = arr[i];
        count[arr[i] - minElement]--;
    }

    for (int i = 0; i < size; ++i) {
        arr[i] = output[i];
    }

    delete[] count;
    delete[] output;
}

int main() {
    const int size = 10;

    int* arr = new int[size];
    for (int i = 0; i < size; ++i) {
        arr[i] = rand() % 1000;
    }

    // Измерение времени выполнения Bubble Sort
    clock_t start_time = clock();
    bubbleSort(arr, size);
    clock_t end_time = clock();
    std::cout << "Bubble Sort time: " << (end_time - start_time) / static_cast<double>(CLOCKS_PER_SEC) << " seconds" << std::endl;

    // Измерение времени выполнения Quick Sort
    start_time = clock();
    quickSort(arr, 0, size - 1);
    end_time = clock();
    std::cout << "Quick Sort time: " << (end_time - start_time) / static_cast<double>(CLOCKS_PER_SEC) << " seconds" << std::endl;

    // Измерение времени выполнения Counting Sort
    start_time = clock();
    countingSort(arr, size);
    end_time = clock();
    std::cout << "Counting Sort time: " << (end_time - start_time) / static_cast<double>(CLOCKS_PER_SEC) << " seconds" << std::endl;

    printArray(arr, size);

    // Освобождение динамически выделенной памяти
    delete[] arr;

    return 0;
}