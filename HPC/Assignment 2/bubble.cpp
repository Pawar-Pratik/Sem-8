#include <iostream>
#include <vector>
#include <omp.h>

using namespace std;

void bubble_sort(vector<int>& arr) {
    int n = arr.size();
    bool swapped;
    for (int i = 0; i < n - 1; ++i) {
        swapped = false;
#pragma omp parallel for shared(arr, swapped)
        for (int j = 0; j < n - i - 1; ++j) {
            if (arr[j] > arr[j + 1]) {
                swap(arr[j], arr[j + 1]);
                swapped = true;
            }
        }
        // If no two elements were swapped in the inner loop, the array is already sorted
        if (!swapped) {
            break;
        }
    }
}

int main() {
    int n;
    cout << "Enter the number of elements: ";
    cin >> n;
    vector<int> arr(n);
    cout << "Enter " << n << " elements: ";
    for (int i = 0; i < n; ++i) {
        cin >> arr[i];
    }

    double start, end;

    // Measure performance of sequential bubble sort
    start = omp_get_wtime();
    bubble_sort(arr);
    end = omp_get_wtime();
    cout << "Sequential bubble sort time: " << (end - start) * 1000 << " milliseconds" << endl;

    // Show sorted numbers
    cout << "Sorted numbers: ";
    for (size_t i = 0; i < arr.size(); ++i) {
        cout << arr[i] << " ";
    }
    cout << endl;

    return 0;
}

