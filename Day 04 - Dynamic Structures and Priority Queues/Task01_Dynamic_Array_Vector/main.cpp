#include <iostream>

using namespace std;


template <typename T>
class DynamicArray
{
private:
    T* elements;
    int numElements;
    int capacity;

    // ================= Main Resize Function ================= //
    void resize(int newCapacity)
    {
        // 1- Resize with the new Capacity - Default behavior ==> Trim
        if (newCapacity < numElements)
            newCapacity = numElements; // Can't shrink below current size

        // 2- Allocate with the new Capacity
        T* newArr = new T[newCapacity];

        // 3- Move all elements from the Old array to the New one
        for (int i = 0; i < numElements; i++)
            newArr[i] = elements[i];

        delete[] elements;
        elements = newArr;
        capacity = newCapacity;
    }

public:
    // ---------- Constructor ---------- //
    explicit DynamicArray(int initialCapacity = 4)
    {
        if (initialCapacity <= 0) initialCapacity = 4;

        elements = new T[initialCapacity];

        numElements = 0;
        capacity = initialCapacity;
    }

    // ---------- Destructor ---------- //
    ~DynamicArray()
    {
        delete[] elements;
    }

    // ---------- Copy Constructor ---------- //
    DynamicArray(const DynamicArray& other)
    {
        numElements = other.numElements;
        capacity = other.capacity;

        elements = new T[capacity];

        for (int i = 0; i < numElements; i++)
            elements[i] = other.elements[i];
    }

    // ---------- Copy Assignment Operator ---------- //
    DynamicArray& operator=(const DynamicArray& other)
    {
        if (this == &other) return *this; // Prevent Self-assignment

        delete[] elements;

        numElements = other.numElements;
        capacity = other.capacity;

        elements = new T[capacity];

        for (int i = 0; i < numElements; i++)
            elements[i] = other.elements[i];

        return *this;
    }

    // ============ Basic Helpers ============
    int size() const
    {
        return numElements;
    }

    int getCapacity() const
    {
        return capacity;
    }

    // ============ Standartd Functions ============

    // ---------- Add element at the end ---------- //
    void add(const T& value)
    {
        // Array is Full ==> Need to Resize
        if (numElements == capacity) resize(capacity * 2); // double the capacity

        elements[numElements++] = value;
    }

    // ---------- Remove element at index ---------- //
    void removeAt(int index)
    {
        if (index < 0 || index >= numElements) return; // Invalid Index

        // Shifting the rest of the elements after the specified index, and erase the element at that index
        for (int x = index; x < numElements - 1; x++)
            elements[x] = elements[x + 1];

        numElements--;
    }

    // ---------- Remove {first occurrence} of value ---------- //
    void remove(const T& value)
    {
        for (int i = 0; i < numElements; i++)
        {
            if (elements[i] == value)
            {
                removeAt(i);
                return;
            }
        }
    }

    // ---------- Remove Empty Slots or places ---------- //
    void trim()
    {
        resize(numElements);
    }

    // ---------- Overloading the "[]" Operator ==> Get & Update ONLY ---------- //
    T& operator[](int index)
    {
        static T dummy{}; // Safe Return

        if (index < 0 || index >= numElements)
        {
            std::cout << "Warning: Index " << index << " out of bounds! Returning dummy value.\n";
            return dummy;
        }

        return elements[index];
    }

    // ---------- View current array ---------- //
    void view() const
    {
        for (int i = 0; i < numElements; i++)
            cout << elements[i] << " ";
        cout << endl;
    }
};


int main()
{
    DynamicArray<int> arr;

    arr.add(10);
    arr.add(20);
    arr.add(30);
    cout << "\nArray Elements: \n" << endl;
    arr.view(); // 10 20 30

    cout << "\n============================================================\n" << endl;

    cout << "\nRemove element at index (1) ..." << endl;
    arr.removeAt(1);
    cout << "\nArray Elements: \n" << endl;
    arr.view(); // 10 30

    cout << "\n============================================================\n" << endl;

    cout << "\nAdd element 40 and 50 ..." << endl;
    arr.add(40);
    arr.add(50);
    cout << "\nArray Elements: \n" << endl;
    arr.view(); // 10 30 40 50

    cout << "\n============================================================\n" << endl;
    cout << "\nRemove the element 30 ..." << endl;
    arr.remove(30);
    cout << "\nArray Elements: \n" << endl;
    arr.view(); // 10 40 50

    cout << "\n============================================================\n" << endl;

    cout << "\nBefore trim - \tSize: " << arr.size() << ", Capacity: " << arr.getCapacity() << endl;

    arr.trim();
    cout << "After trim - "<< "\tSize: " << arr.size() << ", Capacity: " << arr.getCapacity() << endl;

    cout << "\n============================================================\n" << endl;

    cout << "\nTest accessing array with invalid index (99) ..." << endl;
    arr[99];

    cout << "\n============================================================\n" << endl;

    DynamicArray<string> strArr;

    strArr.add("Hello");
    strArr.add("World");
    strArr.add("Dynamic");
    strArr.add("Array");

    cout << "\nArray Elements:\n";
    strArr.view();

    cout << "\n============================================================\n";

    cout << "\nRemove element at index 2 ..." << endl;
    strArr.removeAt(2);
    strArr.view();

    cout << "\n============================================================\n";

    cout << "\nRemove the element 'World' ..." << endl;
    strArr.remove("World");
    strArr.view();

    cout << "\n============================================================\n";

    cout << "\nBefore trim - Size: " << strArr.size() << ", Capacity: " << strArr.getCapacity() << endl;
    strArr.trim();
    cout << "After trim -  Size: " << strArr.size() << ", Capacity: " << strArr.getCapacity() << endl;

    cout << "\n============================================================\n";

    cout << "\nAccessing invalid index 5 ..." << endl;
    string& invalid = strArr[5];
    cout << "Returned dummy value: '" << invalid << "'\n";

    return 0;
}
