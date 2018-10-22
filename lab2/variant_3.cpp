#include <iostream>
#include <chrono>

//using namespace std;
using namespace std::chrono;
size_t srav = 0, pris = 0;

void quickSort(int *arr, int left, int right, int parts = 1) {
    if (right - left + 1 > parts) {
        int i = left, j = right;
        int tmp;
        int pivot = arr[(left + right) / 2];

        while (i <= j) {
            while (arr[i] < pivot) {
                i++;
                srav++;
            }
            while (arr[j] > pivot) {
                j--;
                srav++;
            }
            if (i <= j) {
//                std::cout << arr[i] << " " << arr[j] << std::endl;
                tmp = arr[i];
                arr[i] = arr[j];
                arr[j] = tmp;
                i++;
                j--;
                pris += 2;
            }
        };

        if (left < j)
            quickSort(arr, left, j);
        if (i < right)
            quickSort(arr, i, right);
    }
}

void bubbleSort(int *arr, int left, int right, int repeats = NULL) {
    int size = right - left + 1;
    if (!repeats) {
        repeats = size;
    }
    for (int j(0); j < repeats; ++j) {
        for (int i = 0; i < size - 1; i++) {
            srav++;
            if (arr[i] > arr[i + 1]) {
                std::swap(arr[i], arr[i + 1]);
                pris++;

            }
        }
    }
}

void quick_with_bubble(int *arr, int left, int right) {
    int parts = 3;
    quickSort(arr, left, right, parts);
    bubbleSort(arr, left, right, parts - 1);
}

int main() {
    int n = 100000;
    int *a = new int[n];
    for (int i(0); i < n; ++i) {
        a[i] = 0 + (random() % static_cast<int>(1000 - 0 + 1));
    }

    high_resolution_clock::time_point t1 = high_resolution_clock::now();
//    bubbleSort(a, 0, n - 1);
//    quickSort(a, 0, n - 1);
    quick_with_bubble(a, 0, n - 1);
    high_resolution_clock::time_point t2 = high_resolution_clock::now();
    auto duration = duration_cast<microseconds>(t2 - t1).count();
    std::cout << duration << " " << srav << " " << pris << std::endl;
}


