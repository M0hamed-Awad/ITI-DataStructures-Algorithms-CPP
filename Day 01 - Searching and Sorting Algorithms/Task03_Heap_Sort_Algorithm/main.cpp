#include <iostream>

using namespace std;

void swap(int &x, int &y)
{
    int temp = x;
    x = y;
    y = temp;
}

// n: heap size, i: location of the element we want to fix (parent)
void heapify(int *arr, int size, int i) {
    int largest = i;
    int left = 2 * i + 1;
    int right = 2 * i + 2;

    // If the Left exists and is bigger than the current parent
    if (left < size && arr[left] > arr[largest])
        largest = left;

    // If the Right wing exists and is bigger than the current parent
    if (right < size && arr[right] > arr[largest])
        largest = right;

    // Swap on If we discover that the parent is not the largest
    // ONLY IF --> the "largest" value changed
    if (largest != i) {
        // Re-Order
        swap(arr[i], arr[largest]);

        //Fix the rest.
        heapify(arr, size, largest);
    }
}


void buildHeap(int *arr, int size){
    // We start from the middle of the matrix and work backwards (because these are the parents who have children)
    // Turn it to Mas Heap
    for (int i = size / 2 - 1; i >= 0; i--)
        heapify(arr, size, i);
}

void heapSort(int *arr, int size) {
    buildHeap(arr, size);
    for (int i = size - 1; i > 0; i--) {
        // Take the parent (the one at the beginning) and put it at the end, largest to the end
        swap(arr[0], arr[i]);

        // Fix the remaining heap
        heapify(arr, i, 0);
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
    // Test Case 1: Random numbers
    int arr1[] = {5, 3, 8, 4, 2};
    int size = 5;
    cout << "Test 1 - Random numbers: ";
    printArray(arr1, size);
    heapSort(arr1, size);
    cout << " => Sorted: ";
    printArray(arr1, size);
    cout << endl;

    // Test Case 2: Already sorted
    int arr2[] = {1, 2, 3, 4, 5};
    cout << "Test 2 - Already sorted: ";
    printArray(arr2, size);
    heapSort(arr2, size);
    cout << " => Sorted: ";
    printArray(arr2, size);
    cout << endl;

    // Test Case 3: Reverse sorted
    int arr3[] = {9, 7, 5, 3, 1};
    cout << "Test 3 - Reverse sorted: ";
    printArray(arr3, size);
    heapSort(arr3, size);
    cout << " => Sorted: ";
    printArray(arr3, size);
    cout << endl;

    return 0;
}
