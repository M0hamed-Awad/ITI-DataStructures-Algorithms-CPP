#include <iostream>

using namespace std;

void swap(int &x, int &y)
{
    int temp = x;
    x = y;
    y = temp;
}


void bubbleSort(int *arr, int size)
{
    bool isSorted = false;

    for (int i = 0; (i < size - 1) && (!isSorted); i++)
    {
        isSorted = true;

        for (int j = 0; j < size - i - 1; j++)
        {
            if (arr[j] > arr[j+1])
            {
                swap(arr[j], arr[j+1]);
                isSorted = false;
            }
        }
    }
}

void printArray(int *arr, int size)
{
    for (int i = 0; i < size; i++)
        cout << arr[i] << " ";
    cout << endl;
}


int main()
{

    int arrSize = 5;
    // Test Case 1: Random numbers
    int arr1[] = {5, 3, 8, 4, 2};
    cout << "Test 1 - Random numbers: ";
    printArray(arr1, arrSize);
    bubbleSort(arr1, arrSize);
    cout << " => Sorted: ";
    printArray(arr1, arrSize);
    cout << endl;

    // Test Case 2: Already sorted
    int arr2[] = {1, 2, 3, 4, 5};
    cout << "Test 2 - Already sorted: ";
    printArray(arr2, arrSize);
    bubbleSort(arr2, arrSize);
    cout << " => Sorted: ";
    printArray(arr2, arrSize);
    cout << endl;

    // Test Case 3: Reverse sorted
    int arr3[] = {9, 7, 5, 3, 1};
    cout << "Test 3 - Reverse sorted: ";
    printArray(arr3, arrSize);
    bubbleSort(arr3, arrSize);
    cout << " => Sorted: ";
    printArray(arr3, arrSize);
    cout << endl;
    return 0;
}
