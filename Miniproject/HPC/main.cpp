#include <iostream>
#include <vector>
#include <ctime>
#include <omp.h>
#include <cstdlib>

void swap(int *a, int *b)
{
    int t = *a;
    *a = *b;
    *b = t;
}
int partition(std::vector<int> &arr, int low, int high)
{
    int pivot = arr[high];
    int i = (low - 1);
    for (int j = low; j <= high - 1; j++)
    {
        if (arr[j] < pivot)
        {
            i++;
            swap(&arr[i], &arr[j]);
        }
    }
    swap(&arr[i + 1], &arr[high]);
    return (i + 1);
}
void quickSortSerial(std::vector<int> &arr, int low, int high)
{
    if (low < high)
    {
        int pi = partition(arr, low, high);
        quickSortSerial(arr, low, pi - 1);
        quickSortSerial(arr,
                        pi + 1, high);
    }
}
void quickSortParallel(std::vector<int> &arr, int low, int high)
{
    if (low < high)
    {
        int pi = partition(arr, low, high);
#pragma omp parallel sections
        {
#pragma omp section quickSortParallel(arr, low, pi - 1);
#pragma omp section quickSortParallel(arr, pi + 1, high);
        }
    }
}
int main()
{
    const int SIZE = 1000000;
    std::vector<int> arrSerial(SIZE), arrParallel(SIZE);
    for (int i = 0; i < SIZE; i++)
    {
        arrSerial[i] = arrParallel[i] = rand() % SIZE;
    }
    clock_t startSerial = clock();
    quickSortSerial(arrSerial, 0, SIZE - 1);
    clock_t endSerial = clock();
    clock_t startParallel = clock();
    quickSortParallel(arrParallel, 0, SIZE - 1);
    clock_t endParallel = clock();
    std::cout << "Time taken by Serial QuickSort: " << (double)(endSerial - startSerial) / CLOCKS_PER_SEC << " seconds" << std::endl;
    std::cout << "Time taken by Parallel QuickSort: " << (double)(endParallel - startParallel) / CLOCKS_PER_SEC << " seconds" << std::endl;
    return 0;
}