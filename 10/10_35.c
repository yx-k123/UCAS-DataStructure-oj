#include <stdio.h>

void heapify(int arr[], int n, int i) {
    int largest = i; 
    int l = 3 * i + 1; 
    int m = 3 * i + 2;
    int r = 3 * i + 3; 

    if (l < n && arr[l] > arr[largest])
        largest = l;
    if (m < n && arr[m] > arr[largest])
        largest = m;
    if (r < n && arr[r] > arr[largest])
        largest = r;

    if (largest != i) {
        int temp = arr[i];
        arr[i] = arr[largest];
        arr[largest] = temp;
        heapify(arr, n, largest);
    }
}

void heapSort(int arr[], int n) {
    for (int i = (n - 2) / 3; i >= 0; i--)
        heapify(arr, n, i);

    for (int i = n - 1; i > 0; i--) {
        int temp = arr[0];
        arr[0] = arr[i];
        arr[i] = temp;
        heapify(arr, i, 0);
    }
}

int main()
{
    int arr[1000] = {0};
    int i = 0;
    while (scanf("%d", &arr[i++]) != EOF){}

    heapSort(arr, i - 1);

    for (int j = 0; j < i - 1; j++)
        printf("%d ", arr[j]);
    printf("\n");

    return 0;
}