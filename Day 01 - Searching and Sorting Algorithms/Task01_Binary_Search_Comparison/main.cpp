#include <iostream>

using namespace std;

int binarySearchRecursive(const int *arr, int low, int high, int key)
{
    if(low <= high)
    {
        int mid = (high + low) / 2;

        if (key == arr[mid]) // found
            return mid;

        if (key < arr[mid]) // right half
            return binarySearchRecursive(arr, low, mid - 1, key);

        else // left half
            return binarySearchRecursive(arr, mid + 1,  high, key);
    }
    return -1;
}

int binarySearchIterative(const int *arr, int size, int key)
{
    int low = 0;
    int high = size - 1;

    while (low <= high)
    {
        int mid = (high + low) / 2;
        if (arr[mid] == key) return mid; // found

        else if (arr[mid] < key)
        {
            low = mid + 1;               // right half
        }
        else
        {
            high = mid - 1;              // left half
        }
    }
    return -1;
}


int main()
{
    int arr[] = {1, 3, 5, 7, 9, 11};
    int size = 6;

    // Test 1: Key exists (recursive)
    int key1 = 5;
    int index1 = binarySearchRecursive(arr, 0, size - 1, key1);
    cout << "Recursive Search: Key " << key1 << " found at index " << index1 << endl;

    // Test 2: Key exists (iterative)
    int key2 = 9;
    int index2 = binarySearchIterative(arr, size, key2);
    cout << "Iterative Search: Key " << key2 << " found at index " << index2 << endl;

    // Test 3: Key does not exist (recursive)
    int key3 = 6;
    int index3 = binarySearchRecursive(arr, 0, size - 1, key3);
    cout << "Recursive Search: Key " << key3 << " found at index " << index3 << " (not found)\n";

    // Test 4: Key does not exist (iterative)
    int key4 = 12;
    int index4 = binarySearchIterative(arr, size, key4);
    cout << "Iterative Search: Key " << key4 << " found at index " << index4 << " (not found)\n";
    return 0;
}
