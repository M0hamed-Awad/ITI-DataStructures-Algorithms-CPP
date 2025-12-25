#include <iostream>
#include <vector>
#include <cstdlib>
#include <string>


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
    Node* pLeft;
    Node* pRight;

    Node(const Employee& emp)
        : data(emp), pLeft(nullptr), pRight(nullptr) {}
};

class BST
{
private:
    Node* root;

    bool insertNode(Node*& pCurrentRoot, Node* newNode)
    {
        // Empty (Tree - Subtree)
        if(pCurrentRoot == nullptr)
        {
            pCurrentRoot = newNode;
            return true;
        }

        // Prevent Duplicates
        if( (newNode->data.id) == (pCurrentRoot->data.id) ) return false;

        // Insert Left
        if( (newNode->data.id) < (pCurrentRoot->data.id) ) return insertNode(pCurrentRoot->pLeft, newNode);

        // Insert Right
        else if( (newNode->data.id) > (pCurrentRoot->data.id) ) return insertNode(pCurrentRoot->pRight, newNode);

        else return false;
    }


    void insertNode(Node* parent, Node* current, Node* newNode)
    {
        // Empty Tree
        if (parent == nullptr)
        {
            root = newNode;
            return;
        }

        // ----- Inserting -----
        if (current == nullptr)
        {
            // Insert Left
            if ( (newNode->data.id) < (parent->data.id) ) parent->pLeft = newNode;

            // Insert Right
            else if ( (newNode->data.id) > (parent->data.id) ) parent->pRight = newNode;

            return; // Stop after Insertion
        }

        // Prevent Duplicates
        if ( (newNode->data.id) == (current->data.id) ) return;

        // ----- Movement -----
        // Go Left
        if ( (newNode->data.id) < (current->data.id) ) insertNode(current, current->pLeft, newNode);

        // Go Right
        else insertNode(current, current->pRight, newNode);
    }

    // Inorder (left - root - right)
    void treeTraverse(Node* pCurrentRoot)
    {
        if(pCurrentRoot == nullptr) return;
        treeTraverse(pCurrentRoot->pLeft);
        cout << pCurrentRoot->data.id << " (" << pCurrentRoot->data.name << ")" << endl;
        treeTraverse(pCurrentRoot->pRight);
    }

    int countNodes(Node* pCurrentRoot)
    {
        if(pCurrentRoot == nullptr) return 0;

        else return countNodes(pCurrentRoot->pLeft) + 1 + countNodes(pCurrentRoot->pRight);
    }

    int countLevels(Node* pCurrentRoot)
    {
        if(pCurrentRoot == nullptr) return 0;

        int leftLevels = countLevels(pCurrentRoot->pLeft);
        int rightLevels = countLevels(pCurrentRoot->pRight);

        return 1 + (leftLevels > rightLevels ? leftLevels : rightLevels);
    }

    // search for node to remove
    void Delete(Node*& pCurrentRoot, int value)
    {
        // Empty (Tree - Subtree) || Nothing to Delete
        if (pCurrentRoot == nullptr) return;

        // Go Left
        if(value < pCurrentRoot->data.id) Delete(pCurrentRoot->pLeft, value);

        // Go Right
        else if (value > pCurrentRoot->data.id) Delete(pCurrentRoot->pRight, value);

        // Actual Node Removal
        else removeNode(pCurrentRoot); // value == pCurrentRoot->data.id
    }

    // Get the Maximum Employee by (id) from the Left Subtree
    Employee getMaxValueOnLeftSubTree(Node* pCurrentRoot)
    {
        while(pCurrentRoot->pRight != nullptr) pCurrentRoot = pCurrentRoot->pRight;
        return pCurrentRoot->data;
    }

    // Deleting a Node, handles 3 delete cases
    void removeNode(Node*& pTarget)
    {
        if (pTarget == nullptr) return;

        // 0x1000
        Node* pTemp = pTarget;

        // ------- Delete a Leaf - No Children -------
        if(pTarget->pLeft == nullptr && pTarget->pRight == nullptr)
        {
            delete pTemp;
            pTarget = nullptr;
        }

        // ------- Delete a Root - 1 Child (Left or Right) -------
        // ===> Only Right Child
        else if(pTarget->pLeft == nullptr)
        {
            pTarget = pTarget->pRight;
            pTemp->pRight = nullptr;
            delete pTemp;
        }

        // ===> Only Left Child
        else if(pTarget->pRight == nullptr)
        {
            pTarget = pTarget->pLeft; // From 0x1000 To 0x2000
            pTemp->pLeft = nullptr; // pTemp->pLeft = 0x2000, disconnect left child from the node-to-be-deleted
            delete pTemp; // Now Left and Right children are null
        }

        // ------- Delete a Root - 2 Children -------
        else
        {
            Employee newRootData = getMaxValueOnLeftSubTree(pTarget->pLeft);
            pTarget->data = newRootData;
            // Send the data, but only on the left-subtree, to exculde the current root data from it
            Delete(pTarget->pLeft, newRootData.id);
        }
    }

    // For EVERY node: [ height(left subtree) – height(right subtree) ] <= 1
    bool isBalanced(Node* pCurrentRoot)
    {
        if (pCurrentRoot == nullptr) return true;

        int leftHeight = countLevels(pCurrentRoot->pLeft);
        int rightHeight = countLevels(pCurrentRoot->pRight);

        if(abs(leftHeight - rightHeight) > 1) return false;

        return isBalanced(pCurrentRoot->pLeft) && isBalanced(pCurrentRoot->pRight);
    }

    void storeNodesSorted(Node* pCurrentRoot, std::vector<Employee>& emps)
    {
        if (pCurrentRoot == nullptr) return;

        storeNodesSorted(pCurrentRoot->pLeft, emps);  // left
        emps.push_back(pCurrentRoot->data);           // store current node
        storeNodesSorted(pCurrentRoot->pRight, emps); // right
    }

    void deleteTree(Node*& pCurrentRoot)
    {
        if (pCurrentRoot == nullptr) return;

        deleteTree(pCurrentRoot->pLeft);  // delete left subtree
        deleteTree(pCurrentRoot->pRight); // delete right subtree

        delete pCurrentRoot;              // delete current node
        pCurrentRoot = nullptr;           // set pointer to nullptr
    }

    Node* buildBalancedBST(const std::vector<Employee>& emps, int start, int end)
    {
        if (start > end) return nullptr; // base case

        // the middle node as the new root for the tree/subtree
        int mid = start + (end - start) / 2;
        Node* pCurrentRoot = new Node(emps[mid]);

        pCurrentRoot->pLeft  = buildBalancedBST(emps, start, mid - 1); // left subtree
        pCurrentRoot->pRight = buildBalancedBST(emps, mid + 1, end);   // right subtree

        return pCurrentRoot;
    }

    // convert to sorted array → build balanced tree
    void reBalance(Node*& pCurrentRoot)
    {
        // collect all nodes in sorted order
        std::vector<Employee> nodes;
        storeNodesSorted(pCurrentRoot, nodes);

        // delete old tree
        deleteTree(pCurrentRoot);

        // rebuild balanced tree
        pCurrentRoot = buildBalancedBST(nodes, 0, nodes.size() - 1);
    }


public:
    // Just makes an empty tree
    BST() : root(nullptr) {}

    ~BST()
    {
        deleteTree(root); // deletes all nodes safely
    }

    Node* getRoot()
    {
        return root;
    }


    // ====== Just Wrappers ======
    void insertNode(const Employee& e)
    {
        Node* newNode = new Node(e);
        if (!insertNode(root, newNode))
            delete newNode;

        // 2 Pointers Insert (Current & Leaf)
//        if (root == nullptr)
//            root = newNode;
//        else
//            insertNode(root, root, newNode);

        if (!isBalanced(root))
            reBalance(root);
    }

    int countNodes()
    {
        return countNodes(root);
    }

    int countLevels()
    {
        return countLevels(root);
    }

    void Delete(int value)
    {
        Delete(root, value);

        if (!isBalanced(root))
            reBalance(root);
    }

    bool checkBalanced()
    {
        return isBalanced(root);
    }

    void traverse()
    {
        treeTraverse(root);
        cout << endl;
    }
};


int main()
{
    BST tree;

    // ===== Insert nodes =====
    tree.insertNode({10, "Alice", 30, 5000});
    tree.insertNode({20, "Bob", 25, 4000});
    tree.insertNode({5, "Charlie", 28, 4500});
    tree.insertNode({8, "Diana", 35, 6000});
    tree.insertNode({15, "Eve", 32, 5500});
    tree.insertNode({25, "Frank", 29, 4800});

    string isBalanced = tree.checkBalanced() ? "Balanced" : "Unbalanced";

    cout << isBalanced << endl;

    cout << "Traversal (before deletion):\n";
    tree.traverse();  // Should print IDs in order: 5, 8, 10, 15, 20, 25

    cout << "Total Nodes: " << tree.countNodes() << endl;
    cout << "Levels (height): " << tree.countLevels() << endl;

    // ===== Delete a node =====
    tree.Delete(10);  // Delete root
    cout << "\nAfter deleting 10:\n";
    tree.traverse();
    cout << "Total Nodes: " << tree.countNodes() << endl;
    cout << "Levels (height): " << tree.countLevels() << endl;

    isBalanced = tree.checkBalanced() ? "Balanced" : "Unbalanced";
    cout << "\n" << isBalanced << endl;

    tree.Delete(8);

    cout << "\nAfter deleting Employee with ID = 8" << endl;
    isBalanced = tree.checkBalanced() ? "Balanced" : "Unbalanced";
    cout << "\n" << isBalanced << endl;

    return 0;
}
