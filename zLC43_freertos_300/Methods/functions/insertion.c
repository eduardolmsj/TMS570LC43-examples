#include "teste.h"
#include "HL_sys_common.h"

#include <stdio.h>
#include <stdlib.h>

void insertionSort(int arr[], int n) {
    int i, key, j;
    for (i = 1; i < n; i++) {
        key = arr[i];
        j = i - 1;

        // Move elements of arr[0..i-1] that are greater than key to one position ahead of their current position
        while (j >= 0 && arr[j] > key) {
            arr[j + 1] = arr[j];
            j = j - 1;
        }
        arr[j + 1] = key;
    }
}

void insertion_rotine(int n, int arr[]) {
    uint32 idx;
    for (idx = 0; idx < n; idx++) {
            arr[idx] = n - idx;
        }

        // Perform insertion sort
        insertionSort(arr, n);
    return;
}
