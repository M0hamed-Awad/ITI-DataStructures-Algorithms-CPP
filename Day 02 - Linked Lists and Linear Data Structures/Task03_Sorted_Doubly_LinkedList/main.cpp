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

int main()
{
    DDL employees;

    // --- Insert employees ---
    cout << "--- Test Case 1: Insert employees (sorted automatically) ---\n";
    employees.insertNode({10, "Mohamed", 30, 5000});
    employees.insertNode({5, "Thanaa", 25, 4000});
    employees.insertNode({15, "Donia", 28, 4500});
    employees.insertNode({12, "Marzouk", 35, 6000});

    cout << "--- Display all employees ---\n";
    employees.displayAll(); // Thanaa -> Mohamed -> Marzouk -> Donia

    cout << "\n--- Test Case 2: Search existing and non-existing IDs ---\n";
    // --- Search by ID ---
    int searchId = 12;
    if (employees.displayNode(searchId))
        cout << "\nEmployee with ID " << searchId << " found.\n";
    else
        cout << "\nEmployee with ID " << searchId << " not found.\n";

    // --- Search by ID - Not Found ---
    searchId = 7;
    if (employees.displayNode(searchId))
        cout << "\nEmployee with ID " << searchId << " found.\n";
    else
        cout << "\nEmployee with ID " << searchId << " not found.\n";

    // --- Delete a middle employee ---
    cout << "\n--- Test Case 3: Delete middle employee (ID 12) ---\n";
    int deleteId = 12;
    if (employees.deleteNode(deleteId))
        cout << "\nDeleted employee with ID " << deleteId << ".\n";
    else
        cout << "\nEmployee with ID " << deleteId << " not found.\n";

    employees.displayAll(); // Thanaa -> Mohamed -> Donia

    // --- Delete first employee ---
    cout << "\n--- Test Case 4: Delete first employee (ID 5) ---\n";
    employees.deleteNode(5);
    cout << "\nAfter deleting first employee:\n";
    employees.displayAll(); // Mohamed -> Donia

    // --- Delete last employee ---
    cout << "\n--- Test Case 5: Delete last employee (ID 15) ---\n";
    employees.deleteNode(15);
    cout << "\nAfter deleting last employee:\n";
    employees.displayAll(); // Mohamed

    cout << "\n--- Test Case 6: Delete non-existing employee (ID 20) ---\n";
    if (!employees.deleteNode(20))
        cout << "Employee with ID 20 not found.\n";

    cout << "\n--- Test Case 7: Insert employee smaller than first (ID 2) ---\n";
    employees.insertNode({2, "Ali", 22, 3500});
    employees.displayAll(); // Ali -> Mohamed

    cout << "\n--- Test Case 8: Insert employee larger than last (ID 20) ---\n";
    employees.insertNode({20, "Sara", 40, 7000});
    employees.displayAll(); // Ali -> Mohamed -> Sara


    // --- Node count ---
    cout << "\n--- Test Case 9: Node count ---\n";
    cout << "Total nodes: " << employees.nodeNumber() << endl; // 3

    // --- Test operator[] ---
    cout << "\n--- Test Case 10: Access using operator[] ---\n";
    Employee* e0 = employees[0];
    Employee* e1 = employees[1];
    Employee* e2 = employees[2];
    if (e0) cout << "Index 0: " << e0->name << endl;
    if (e1) cout << "Index 1: " << e1->name << endl;
    if (e2) cout << "Index 2: " << e2->name << endl;

    return 0;
}
