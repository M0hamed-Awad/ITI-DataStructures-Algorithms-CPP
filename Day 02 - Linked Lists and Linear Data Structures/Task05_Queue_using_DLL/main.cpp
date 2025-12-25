#include <iostream>

using namespace std;

struct Employee
{
    int id;
    string name;
    int age;
    float salary;
};

class Node
{
public:
    Employee data;
    Node* pNext;
    Node* pPrev;

    Node(const Employee& emp)
        : data(emp), pNext(nullptr), pPrev(nullptr) {}
};

class DDL
{
protected:
    Node* pStart;
    Node* pLast;

public:

    // Constructor
    DDL() : pStart(nullptr), pLast(nullptr) {}

    // Destructor
    ~DDL()
    {
        Node* current = pStart;
        while (current != nullptr)
        {
            Node* temp = current;
            current = current->pNext;
            delete temp;
        }
        pStart = pLast = nullptr;
    }

    // Copy Constructor
    DDL(const DDL& other)
    {
        pStart = nullptr;
        pLast = nullptr;

        Node* current = other.pStart;
        while (current != nullptr)
        {
            insertNode(current->data);
            current = current->pNext;
        }
    }

    // Copy Assignment Operator
    DDL& operator=(const DDL& other)
    {
        if (this == &other) return *this;

        // clear existing list
        this->~DDL();

        pStart = pLast = nullptr;

        Node* current = other.pStart;
        while (current != nullptr)
        {
            insertNode(current->data);
            current = current->pNext;
        }
        return *this;
    }

    // ================================================================

    void insertNode(const Employee& emp)
    {
        Node* newNode = new Node(emp);

        // list empty
        if (pStart == nullptr)
        {
            pStart = pLast = newNode;
            return;
        }
        else
        {
            Node* current = pStart;
            // Traverse to find suitable insertion point, go till the "current id" becomes > "new node id"
            while (current != nullptr && current->data.id < emp.id)
            {
                current = current->pNext;
            }

            // Insert at start -> current node smaller than first node ^^^
            if (current == pStart) // Before start
            {
                newNode->pNext = pStart;
                pStart->pPrev = newNode;
                pStart = newNode;
            }
            // Insert at end
            else if (current == nullptr) // Append
            {
                newNode->pPrev = pLast;
                pLast->pNext = newNode;
                pLast = newNode;
            }
            else // General case (insert in middle - before current)
            {
                newNode->pNext = current;
                newNode->pPrev = current->pPrev;
                current->pPrev->pNext = newNode;
                current->pPrev = newNode;
            }
        }
    }

    // ================================================================

    Node* searchList(int id)
    {
        Node* current = pStart;
        while (current != nullptr)
        {
            if (current->data.id == id)
                return current;
            else if (current->data.id > id)
                return nullptr; // stop early
            current = current->pNext;
        }
        return nullptr;
    }

    // ================================================================

    bool deleteNode(int id)
    {
        Node* target = searchList(id);
        if (target == nullptr) return false;

        // only one node
        if (pStart == pLast)
        {
            delete target;
            pStart = pLast = nullptr;
            return true;
        }

        // delete first
        if (target == pStart)
        {
            pStart = pStart->pNext;
            pStart->pPrev = nullptr;
            delete target;
            return true;
        }

        // delete last
        if (target == pLast)
        {
            pLast = pLast->pPrev;
            pLast->pNext = nullptr;
            delete target;
            return true;
        }

        // delete in middle
        // next of the previous node = next of target
        target->pPrev->pNext = target->pNext;

        // previous of the next node = previous of target
        target->pNext->pPrev = target->pPrev;

        delete target;

        return true;
    }

    // ================================================================

    bool displayNode(int id)
    {
        Node* n = searchList(id);
        if (n == nullptr) return false;

        cout << "\nEmployee Info:\n";
        cout << "ID: " << n->data.id << endl;
        cout << "Name: " << n->data.name << endl;
        cout << "Age: " << n->data.age << endl;
        cout << "Salary: " << n->data.salary << endl;
        return true;
    }

    // ================================================================

    void displayAll()
    {
        Node* current = pStart;
        if (current == nullptr)
        {
            cout << "List is empty.\n";
            return;
        }

        cout << "\n===== Employee List =====\n";
        while (current != nullptr)
        {
            cout << "ID: " << current->data.id
                 << " | Name: " << current->data.name
                 << " | Age: " << current->data.age
                 << " | Salary: " << current->data.salary << endl;
            current = current->pNext;
        }
    }

    // ================================================================

    int nodeNumber()
    {
        int count = 0;
        Node* cur = pStart;
        while (cur != nullptr)
        {
            count++;
            cur = cur->pNext;
        }
        return count;
    }

    // ================================================================

    // "[]" Operator
    Employee* operator[](int index)
    {
        // Invalid index (negative)
        if (index < 0)
            return nullptr;

        Node* current = pStart;
        int pos = 0;

        while (current != nullptr)
        {
            if (pos == index)
                return &(current->data);
            current = current->pNext;
            pos++;
        }

        // Index out of range
        return nullptr;
    }
};


// FIFO (First-In-First-Out)
class QueueDDL  : public DDL
{
    // pStart ---> The front of the Queue
    // pLast ---> The rear of the Queue

public:
    // insert at "rear" -> pLast
    void Enqueue(const Employee& emp)
    {
        Node* newNode = new Node(emp);
        if (!pStart) // empty queue
        {
            pStart = pLast = newNode;
        }
        else
        {
            pLast->pNext = newNode;
            newNode->pPrev = pLast;
            pLast = newNode;
        }
    }

    // remove from "front" --> pStart
    Node* Dequeue()
    {
        if (!pStart) return nullptr; // empty queue

        Node* frontNode = pStart;

        if (pStart == pLast) // only one node
        {
            pStart = pLast = nullptr;
        }
        else
        {
            pStart = pStart->pNext;
            pStart->pPrev = nullptr;
        }

        // Detach node
        frontNode->pNext = frontNode->pPrev = nullptr;
        return frontNode;
    }

    Node* peek()
    {
        return pStart;
    }
};

int main()
{
    QueueDDL queue;

    cout << "--- Enqueue employees ---\n";
    queue.Enqueue({1, "Mohamed", 30, 5000});
    queue.Enqueue({2, "Thanaa", 25, 4000});
    queue.Enqueue({3, "Donia", 28, 4500});

    cout << "\n--- Queue content (front to rear) ---\n";
    queue.displayAll();

    cout << "\n--- Peek front employee ---\n";
    Node* front = queue.peek();
    if (front)
        cout << "Front: " << front->data.name << ", ID: " << front->data.id << endl;

    cout << "\n--- Dequeue front employee ---\n";
    Node* dequeued = queue.Dequeue();
    if (dequeued)
    {
        cout << "Dequeued: " << dequeued->data.name << ", ID: " << dequeued->data.id << endl;
        delete dequeued; // free memory
    }

    cout << "\n--- Queue content after dequeue ---\n";
    queue.displayAll();

    return 0;
}
