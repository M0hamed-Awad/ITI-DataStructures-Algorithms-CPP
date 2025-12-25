#include <iostream>

using namespace std;

class Node
{
public:
    int data;
    Node* next;

    Node(int value)
    {
        data = value;
        next = nullptr;
    }
};

class LinkedList
{
private:
    Node* head;

public:
    LinkedList()
    {
        head = nullptr;
    }

    void insertFront(int value)
    {
        Node* newNode = new Node(value);
        newNode->next = head;
        head = newNode;
    }

    void insertEnd(int value)
    {
        Node* newNode = new Node(value);
        // Insert at front
        if (head == nullptr)
        {
            head = newNode;
            return;
        }

        Node* temp = head;

        // go through all elements
        while (temp->next != nullptr)
        {
            temp = temp->next;
        }

        temp->next = newNode;
    }

    void insertAtPosition(int position, int value)
    {
        // Position invalid
        if (position < 1)
        {
            cout << "Invalid position!\n";
            return;
        }

        // insert at front
        if (position == 1)
        {
            insertFront(value);
            return;
        }

        // go to the node before the position
        Node* current = head;
        int count = 1; // head is position 1

        while (current != nullptr && count < position - 1)
        {
            current = current->next;
            count++;
        }

        // Check if position is beyond list length
        if (current == nullptr)
        {
            cout << "Position is > list size!\n";
            return;
        }

        Node* newNode = new Node(value);
        newNode->next = current->next;
        current->next = newNode;
    }

    void deleteFront()
    {
        if (head == nullptr) return; // Empty List

        Node* temp = head;
        head = head->next;
        delete temp;
    }

    void deleteLast()
    {
        if (head == nullptr) return; // Empty List

        if (head->next == nullptr)   // Only 1 Element
        {
            delete head;
            head = nullptr;
            return;
        }

        // Multiple Elements
        Node* current = head;
        while (current->next->next != nullptr)
        {
            current = current->next;
        }

        Node* temp = current->next; // Last Node
        current->next = nullptr;
        delete temp;
    }

    void deleteAtPosition(int position)
    {
        if (position < 1 || head == nullptr) return; // invalid position or Empty List

        // If it's the (Head)
        if (position == 1)
        {
            deleteFront();
            return;
        }

        Node* current = head;
        int count = 1;

        while (current->next != nullptr && count < position - 1)
        {
            current = current->next;
            count++;
        }

        // Position > List Size
        if (current->next == nullptr)
        {
            cout << "Position is beyond list size!\n";
            return;
        }

        Node* temp = current->next;
        current->next = temp->next;
        delete temp;
    }


    // Delete first occurrence of value
    void deleteValue(int value)
    {
        // List is empty
        if (head == nullptr) return;

        // If head is the node to delete
        if (head->data == value)
        {
            Node* temp = head;
            head = head->next;
            delete temp;
            return;
        }

        Node* current = head;
        // Search for node BEFORE the target
        while (current->next != nullptr && current->next->data != value)
        {
            current = current->next;
        }

        // Value not found
        if (current->next == nullptr) return;

        // Delete node
        Node* temp = current->next;
        current->next = temp->next;
        delete temp;
    }

    bool search(int value)
    {
        Node* temp = head;
        while (temp != nullptr)
        {
            if (temp->data == value)
                return true;
            temp = temp->next;
        }
        return false;
    }

    void printList()
    {
        Node* temp = head;
        while (temp != nullptr)
        {
            cout << temp->data << " -> ";
            temp = temp->next;
        }
        cout << "NULL\n";
    }
};

int main()
{
    LinkedList list;

    cout << "--- Inserting elements ---\n";
    list.insertFront(33);          // 33
    list.insertEnd(65);            // 33 -> 65
    list.insertEnd(98);            // 33 -> 65 -> 98
    list.insertFront(7);           // 7 -> 33 -> 65 -> 98
    list.insertAtPosition(3, 50);  // 7 -> 33 -> 50 -> 65 -> 98
    list.printList();

    cout << "\n--- Searching for 20 ---\n";
    cout << "Search 20: " << (list.search(20) ? "Found" : "Not Found") << endl;
    cout << "Search 50: " << (list.search(50) ? "Found" : "Not Found") << endl;

    cout << "\n--- Deleting first occurrence of value 98 ---\n";
    list.deleteValue(98);
    list.printList(); // 7 -> 33 -> 50 -> 65 -> NULL

    cout << "\n--- Deleting front ---\n";
    list.deleteFront();
    list.printList(); // 33 -> 50 -> 65 -> NULL

    cout << "\n--- Deleting last ---\n";
    list.deleteLast();
    list.printList(); // 33 -> 50 -> NULL

    cout << "\n--- Deleting at position 2 ---\n";
    list.deleteAtPosition(2);
    list.printList(); // 33 -> NULL

    cout << "\n--- Deleting at position 5 (invalid) ---\n";
    list.deleteAtPosition(5);      // Position beyond list size
    list.printList();               // 33 -> NULL

    return 0;
}
