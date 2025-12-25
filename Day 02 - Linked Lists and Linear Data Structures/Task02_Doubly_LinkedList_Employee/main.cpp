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
private:
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

        // insert at end
        pLast->pNext = newNode;
        newNode->pPrev = pLast;
        pLast = newNode;
    }

    // ================================================================

    Node* searchList(int id)
    {
        Node* current = pStart;
        while (current != nullptr)
        {
            if (current->data.id == id)
                return current;
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

int main()
{
    DDL employees;

    // --- Insert employees ---
    employees.insertNode({1, "Mohamed", 30, 5000});
    employees.insertNode({2, "Thanaa", 25, 4000});
    employees.insertNode({3, "Donia", 28, 4500});
    employees.insertNode({4, "Marzouk", 35, 6000});

    cout << "--- Display all employees ---\n";
    employees.displayAll();

    // --- Search by ID ---
    int searchId = 3;
    if (employees.displayNode(searchId))
        cout << "\nEmployee with ID " << searchId << " found.\n";
    else
        cout << "\nEmployee with ID " << searchId << " not found.\n";

    // --- Search by ID - Not Found ---
    searchId = 5;
    if (employees.displayNode(searchId))
        cout << "\nEmployee with ID " << searchId << " found.\n";
    else
        cout << "\nEmployee with ID " << searchId << " not found.\n";

    // --- Delete a middle employee ---
    int deleteId = 2;
    if (employees.deleteNode(deleteId))
        cout << "\nDeleted employee with ID " << deleteId << ".\n";
    else
        cout << "\nEmployee with ID " << deleteId << " not found.\n";

    employees.displayAll();

    // --- Delete first employee ---
    employees.deleteNode(1);
    cout << "\nAfter deleting first employee:\n";
    employees.displayAll();

    // --- Delete last employee ---
    employees.deleteNode(4);
    cout << "\nAfter deleting last employee:\n";
    employees.displayAll();

    // --- Node count ---
    cout << "\nTotal nodes left: " << employees.nodeNumber() << endl;

    // --- Test operator[] ---
    employees.insertNode({5, "Sameh", 32, 5200});
    Employee* e = employees[0];  // first node
    if (e != nullptr)
        cout << "\nUsing operator[] - First employee: " << e->name << ", Salary: " << e->salary << endl;

    return 0;
}
