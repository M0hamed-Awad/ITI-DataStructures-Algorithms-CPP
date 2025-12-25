#include <iostream>
#include <vector>
#include <utility>

using namespace std;

template <typename P>
void swap(P &x, P &y)
{
    P temp = x;
    x = y;
    y = temp;
}
// Parent = (i - 1) / 2
// Left   = 2*i + 1
// Right  = 2*i + 2

template <typename T>
class Heap
{
private:
    vector<T> elements;
    int currentSize = 0;

    // ============ Index Helpers ============
    int parent(int i)
    {
        return (i - 1) / 2;
    }

    int left(int i)
    {
        return 2 * i + 1;
    }

    int right(int i)
    {
        return 2 * i + 2;
    }

    // ============ Standard Methods ============

    // ---------- Percolate Up ---------- //
    void percolateUp(int hole)
    {
        while (hole > 0 && elements[hole] < elements[parent(hole)])
        {
            std::swap(elements[hole], elements[parent(hole)]);
            hole = parent(hole);
        }
    }

    // ---------- Percolate Down ----------
    void percolateDown(int hole)
    {
        T temp = elements[hole];

        int smallest = hole; // smallest value among parent and children
        int leftChild = left(hole);
        int rightChild = right(hole);

        // If there is a left child && this left child is smaller than the current node
        if (leftChild < currentSize && elements[leftChild] < elements[smallest])
            smallest = leftChild; // the smallest value got updated with the left child value

        if (rightChild < currentSize && elements[rightChild] < elements[smallest])
            smallest = rightChild; // the smallest value got updated with the right child value

        // If the current node is not the smallest among itself and its children
        if (smallest != hole)
        {
            std::swap(elements[hole], elements[smallest]); // Swap current node with the Smallest value
            percolateDown(smallest); // continue moving down
        }
    }


public:
    // ---------- Constructor ---------- //
    explicit Heap(int capacity = 10)
        : elements(capacity), currentSize(0) {}

    // ============ Basic Helpers ============
    bool isEmpty() const
    {
        return currentSize == 0;
    }

    int size()  const
    {
        return currentSize;
    }

    // ============ Standard Methods ============

    // ---------- Insert ---------- //
    void insert(const T& value)
    {
        // Full
        if (currentSize == elements.size())
            elements.resize(elements.size() * 2);

        elements[currentSize] = value;
        percolateUp(currentSize);
        currentSize++;
    }

    // ---------- Get Min ---------- //
    bool getMin(T& out) const
    {
        if (isEmpty()) return false;

        out = elements[0];
        return true;
    }

    // ---------- Delete Min ---------- //
    bool deleteMin()
    {
        if (isEmpty()) return false;

        elements[0] = elements[currentSize - 1];
        currentSize--;

        if (!isEmpty()) percolateDown(0);

        return true;
    }

    // ---------- View Heap ----------
    void View() const
    {
        cout << "Heap state: ";
        for (int i = 0; i < currentSize; i++)
            cout << elements[i] << " ";
        cout << endl;
    }

    // ---------- Operator [] ----------
    T& operator[](int index)
    {
        return elements[index];
    }
};


int main()
{
    Heap<int> heap;

    // Insert some numbers
    heap.insert(20);
    heap.insert(5);
    heap.insert(15);
    heap.insert(10);
    heap.insert(30);

    cout << "After inserts: ";
    heap.View();

    cout << "\n============================================================\n" << endl;

    // Get min
    int minVal;
    if (heap.getMin(minVal))
        cout << "Current min: " << minVal << endl;

    cout << "\n============================================================\n" << endl;

    // Delete min
    heap.deleteMin();
    cout << "After deleteMin: ";
    heap.View();

cout << "\n============================================================\n" << endl;

    // Insert another number
    heap.insert(2);
    cout << "After inserting 2: ";
    heap.View();

    cout << "\n============================================================\n" << endl;

    // Delete min again
    heap.deleteMin();
    cout << "After another deleteMin: ";
    heap.View();

    cout << "\n============================================================\n" << endl;

    return 0;
}
