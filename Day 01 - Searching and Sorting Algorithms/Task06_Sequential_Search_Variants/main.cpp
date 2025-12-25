#include <iostream>

using namespace std;

int sequentialSearchForSortedElements(const int *arr, int size, int key)
{
    for (int i = 0; i < size; ++i)
    {
        if (arr[i] == key) return i;
        if (arr[i] > key) return -1; // exit — as the array is sorted ascending, so the left element MUST be less than the Right one
    }
    return -1;
}

int sequentialSearchForUnsortedElements(const int *arr, int size, int key)
{
    for (int i = 0; i < size; ++i)
        if (arr[i] == key) return i;

    return -1;
}


int main()
{
    int sortedArr[] = {1, 3, 5, 7, 9};
    int unsortedArr[] = {7, 2, 9, 1, 5};
    int size = 5;

    // Test 1: Sequential search in sorted array (key exists)
    int key1 = 5;
    int index1 = sequentialSearchForSortedElements(sortedArr, size, key1);
    cout << "Sorted array search: Key " << key1 << " found at index " << index1 << endl;

    // Test 2: Sequential search in sorted array (key does not exist)
    int key2 = 6;
    int index2 = sequentialSearchForSortedElements(sortedArr, size, key2);
    cout << "Sorted array search: Key " << key2 << " found at index " << index2 << " (not found)\n";

    // Test 3: Sequential search in unsorted array (key exists)
    int key3 = 9;
    int index3 = sequentialSearchForUnsortedElements(unsortedArr, size, key3);
    cout << "Unsorted array search: Key " << key3 << " found at index " << index3 << endl;

    // Test 4: Sequential search in unsorted array (key does not exist)
    int key4 = 4;
    int index4 = sequentialSearchForUnsortedElements(unsortedArr, size, key4);
    cout << "Unsorted array search: Key " << key4 << " found at index " << index4 << " (not found)\n";
    return 0;
}
