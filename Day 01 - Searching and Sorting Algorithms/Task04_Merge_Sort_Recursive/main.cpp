#include <iostream>

using namespace std;

void merge(int* arr, int start, int end, int mid)
{
    int size = end - start + 1;
    int* tempArr = new int[size];

    // "i" is pointer to the first line, "j" is pointer to the second line.
    int i = start;
    int j = mid + 1;
    // pointer to the temp array
    int k = 0;

    // The Game: Which one of you have the Smallest Value?
    while(i <= mid && j <= end)
    {
        if(arr[i] <= arr[j])
        {
            tempArr[k] = arr[i];
            i++;
        }
        else
        {
            tempArr[k] = arr[j];
            j++;
        }
        k++;
    }

    // If Left side has leftovers
    while(i <= mid)
    {
        tempArr[k] = arr[i];
        i++;
        k++;
    }

    // If Right side has leftovers
    while(j <= end)
    {
        tempArr[k] = arr[j];
        j++;
        k++;
    }

    // Copy Back to Original Array
    for(int x = 0; x < size; x++)
    {   // (start + x) =====> The Offset
        arr[start + x] = tempArr[x];
    }

    delete[] tempArr;
}

void mergeSort(int *arr, int start, int end)
{
    if(start < end)
    {
        int mid = (start + end) / 2;
        // Recursive: Left half
        mergeSort(arr, start, mid);
        // Recursive: Right half
        mergeSort(arr, mid + 1, end);
        // Merge the sorted halves
        merge(arr, start, end, mid);
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
    mergeSort(arr1, 0, arrSize - 1);
    cout << " => Sorted: ";
    printArray(arr1, arrSize);
    cout << endl;

    // Test Case 2: Already sorted
    int arr2[] = {1, 2, 3, 4, 5};
    cout << "Test 2 - Already sorted: ";
    printArray(arr1, arrSize);
    mergeSort(arr2, 0, arrSize - 1);
    cout << " => Sorted: ";
    printArray(arr1, arrSize);
    cout << endl;

    // Test Case 3: Reverse sorted
    int arr3[] = {9, 7, 5, 3, 1};
    cout << "Test 3 - Reverse sorted: ";
    printArray(arr1, arrSize);
    mergeSort(arr3, 0, arrSize - 1);
    cout << " => Sorted: ";
    printArray(arr1, arrSize);
    cout << endl;
    return 0;
}
