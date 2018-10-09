//
// Created by Антон Донской on 06/09/2018.
//

#include <iostream>

void quickSort(int *arr, int left, int right) {
    if (right - left + 1 > 3) {
        int i = left, j = right;
        int tmp;
        int pivot = arr[(left + right) / 2];

        /* partition */
        while (i <= j) {
            while (arr[i] < pivot)
                i++;
            while (arr[j] > pivot)
                j--;
            if (i <= j) {
                tmp = arr[i];
                arr[i] = arr[j];
                arr[j] = tmp;
                i++;
                j--;
            }
        };

        /* recursion */
        if (left < j)
            quickSort(arr, left, j);
        if (i < right)
            quickSort(arr, i, right);
    }
}


int main() {

    int n;
    std::cin >> n;
    int *a = new int[n];
    for (int i(0); i < n; ++i) {
        std::cin >> a[i];
    }

    quickSort(a, 0, n - 1);

    for (int i(0); i < n; ++i) {
        std::cout << a[i] << " ";
        if ((i + 1) % 3 == 0) {
            std::cout << "| ";
        }
    }
    std::cout << std::endl;
    std::cout << std::endl;

    for (int j(0); j < 2; ++j) {
        for (int i = 0; i < n - 1; i++) {
            if (a[i] > a[i + 1]) {
                std::swap(a[i], a[i + 1]);
            }

        }
        for (int i(0); i < n; ++i) {
            std::cout << a[i] << " ";
            if ((i + 1) % 3 == 0) {
                std::cout << "| ";
            }
        }
        std::cout << std::endl;
    }


}


