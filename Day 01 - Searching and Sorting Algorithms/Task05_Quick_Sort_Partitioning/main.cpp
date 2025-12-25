#include <iostream>

using namespace std;

void swap(int &x, int &y)
{
    int temp = x;
    x = y;
    y = temp;
}

int partition(int *arr, int start, int end, int pivot)
{
    // Pointers to Array Elements
    int l = start;
    int r = end;

    // They did not cross each other
    while (l <= r)
    {
        // Move "i" right as long as the number is {less than} to the pivot
        while (l <= end && arr[l] < pivot) l++;

        // Move "r" left as long as the number is {greater than} the pivot
        while (r >= start && arr[r] > pivot) r--;

        // If pointers haven't crossed, swap and move
        // as if (l < r), then arr[l] > arr[r] so we need to switch them
        if (l <= r)
        {
            swap(arr[l], arr[r]);
            // Move pointers past the swapped elements
            l++;
            r--;
        }
    }

    // At this point, 'l' is the first number of the "Large" group
    // and 'r' is the last number of the "Small" group
    // return pivot position, 'r' is now the index of the last element in the left partition
    return r;
}

void quickSort(int* arr, int start, int end)
{
    // Base case
    if (start >= end) return;

    // Pick the Pivot
    int mid = start + (end - start) / 2;
    int pivot = arr[mid];

    // get pivot position (Split Point)
    int pivotIndex = partition(arr, start, end, pivot);
    // cout << "\nPivot Index is:" <<pivotIndex << endl;

    // FIX: If the split point ran off the left edge (rare edge case),
    // force the split to be at 'start' to ensure we make progress.
    if (pivotIndex < start) pivotIndex = start;

    // Left: From Start to "r" (pivot index)
    quickSort(arr, start, pivotIndex);

    // Right: From "r + 1" to End
    quickSort(arr, pivotIndex + 1, end);
}

void printArray(int *arr, int size)
{
    for (int i = 0; i < size; i++)
        cout << arr[i] << " ";
    cout << endl;
}

int main()
{
    int size = 5;
    // Test Case 1: Random numbers
    int arr1[] = {5, 3, 8, 4, 2};
    cout << "Test 1 - Random numbers: ";
    printArray(arr1, size);
    quickSort(arr1, 0, size - 1);
    cout << " => Sorted: ";
    printArray(arr1, size);

    // Test Case 2: Already sorted
    int arr2[] = {1, 2, 3, 4, 5};
    cout << "Test 2 - Already sorted: ";
    printArray(arr2, size);
    quickSort(arr2, 0, size - 1);
    cout << " => Sorted: ";
    printArray(arr2, size);

    // Test Case 3: Reverse sorted
    int arr3[] = {9, 7, 5, 3, 1};
    cout << "Test 3 - Reverse sorted: ";
    printArray(arr3, size);
    quickSort(arr3, 0, size - 1);
    cout << " => Sorted: ";
    printArray(arr3, size);

    return 0;
}
