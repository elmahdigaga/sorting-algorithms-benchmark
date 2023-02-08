#ifndef SORT_H
#define SORT_H

#include <iostream>

class Sort {
   private:
    __int64 i = 0, j = 0;

    void swap(int* a, int* b) {
        int temp = *a;
        *a = *b;
        *b = temp;
    }
    void merged(int arr[], __int64 p, __int64 q, __int64 r) {
        __int64 n1 = q - p + 1;
        __int64 n2 = r - q;
        int L[n1], M[n2];

        for (i = 0; i < n1; i++)
            L[i] = arr[p + i];
        for (j = 0; j < n2; j++)
            M[j] = arr[q + 1 + j];

        i = 0;
        j = 0;
        __int64 k = p;

        while (i < n1 && j < n2) {
            if (L[i] <= M[j]) {
                arr[k] = L[i];
                i++;
            } else {
                arr[k] = M[j];
                j++;
            }
            k++;
        }

        while (i < n1) {
            arr[k] = L[i];
            i++;
            k++;
        }
        while (j < n2) {
            arr[k] = M[j];
            j++;
            k++;
        }
    }
    __int64 partition(int array[], __int64 low, __int64 high) {
        int pivot = array[high];
        __int64 i = (low - 1);

        for (__int64 j = low; j < high; j++) {
            if (array[j] <= pivot) {
                i++;
                swap(&array[i], &array[j]);
            }
        }

        swap(&array[i + 1], &array[high]);

        return (i + 1);
    }

   public:
    void display(int arr[], __int64 size) {
        for (i = 0; i < size; i++) {
            std::cout << arr[i] << std::endl;
        }
    }
    void copy(int a[], int b[], __int64 size) {
        for (i = 0; i < size; i++) {
            b[i] = a[i];
        }
    }

    void bubble(int arr[], __int64 size) {
        for (i = 0; i < size; ++i) {
            for (j = 0; j < size; ++j) {
                if (arr[j] > arr[j + 1]) {
                    swap(&arr[j], &arr[j + 1]);
                }
            }
        }
    }

    void selection(int arr[], __int64 size) {
        __int64 min = 0;
        for (i = 0; i < size; ++i) {
            min = i;
            for (j = i + 1; j < size; ++j) {
                if (arr[min] > arr[j])
                    min = j;
            }
            if (min != i) {
                swap(&arr[i], &arr[min]);
            }
        }
    }

    void insertion(int arr[], __int64 size) {
        for (i = 1; i < size; ++i) {
            int key = arr[i];
            j = i - 1;
            while (j >= 0 && key < arr[j]) {
                arr[j + 1] = arr[j];
                --j;
            }
            arr[j + 1] = key;
        }
    }

    void merge(int arr[], __int64 l, __int64 r) {
        if (l < r) {
            __int64 m = l + (r - l) / 2;
            merge(arr, l, m);
            merge(arr, m + 1, r);
            merged(arr, l, m, r);
        }
    }

    void quick(int arr[], __int64 l, __int64 r) {
        if (l < r) {
            __int64 pi = partition(arr, l, r);
            quick(arr, l, pi - 1);
            quick(arr, pi + 1, r);
        }
    }
};

#endif