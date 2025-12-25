#include <iostream>
#include <vector>
#include <cstdlib>

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
    int height;

    Node(const Employee& emp)
        : data(emp), pLeft(nullptr), pRight(nullptr), height(1) {}
};

class AVL
{
private:
    Node* root;

    // ============ Balancing Helpers ============
    // Get the height of a node
    int getHeight(Node* pCurrentNode);

    // Detect if node is unbalanced
    int getBalanceFactor(Node* pCurrentNode);

    // ============ Rotation ============
    Node* rotateRight(Node* pCurrentRoot);
    Node* rotateLeft(Node* pCurrentRoot);

    // ============ Insertion & Removal ============
    Node* insertNode(Node*& pCurrentRoot, Node* pNewNode);
    Node* removeNode(Node* pCurrentRoot, int id);

    // ============ Insertion & Removal Helpers ============
    // Get the Maximum Employee by (id) from the Left Subtree
    Employee getMaxValueOnLeftSubTree(Node* pCurrentRoot);

    // ============ Traversal ============
    // Inorder (left - root - right)
    void inorder(Node* pCurrentRoot);

    // ============ Delete the Whole Tree ============
    void deleteTree(Node*& pCurrentRoot);

public:
    // Just makes an empty tree
    AVL() : root(nullptr) {}

    ~AVL()
    {
        deleteTree(root); // deletes all nodes safely
    }

    Node* getRoot()
    {
        return root;
    }

    // ============ Tree Helpers ============
    int countNodes(Node* pCurrentRoot);
    int countLevels(Node* pCurrentRoot);

    // ============ Wrappers ============
    void insert(const Employee& newEmp);
    void remove(int empId);
    void traverse();
};

void AVL::insert(const Employee& newEmp)
{
    root = insertNode(root, new Node(newEmp));
}

void AVL::remove(int empId)
{
    root = removeNode(root, empId);
}

void AVL::traverse()
{
    inorder(root);
    cout << endl;
}

int AVL::getHeight(Node* pCurrentNode)
{
    return (pCurrentNode != nullptr) ? pCurrentNode->height : 0;
}

int AVL::getBalanceFactor(Node* pCurrentNode)
{
    // BF = {Height(Left Subtree)} - {Height(Right Subtree)}
    // BF in {-1, 0, 1\}:   Safe Zone       ===> The node is balanced.
    // BF > 1 (e.g., 2):    Left Heavy      ===> The left side is dragging us down.
    // BF < -1 (e.g., -2):  Right Heavy     ===> The right side is dragging us down.
    return (pCurrentNode != nullptr) ?
           getHeight(pCurrentNode->pLeft) - getHeight(pCurrentNode->pRight) : 0;
}

Node* AVL::rotateRight(Node* pCurrentRoot)
{
    Node* pNewRoot = pCurrentRoot->pLeft;
    Node* rst = pNewRoot->pRight; // The one getting adopted  (the orphan)

    // ------ Rotation ------

    // Left Child (the New Root) rises up, and the Current Root becomes its Right Child
    pNewRoot->pRight = pCurrentRoot;
    // Current Root adopts Right Subtree of the New Root (the orphan) as its new Left Child
    pCurrentRoot->pLeft = rst;

    // Update Heights ---> Because the Current Root moved down and the New Root moved up
    // So, Their heights changed
    // Update Current Root first (the child) because New Root depends on Current Root's height now

    // Current Root's new height = 1 + Max of its NEW children
    pCurrentRoot->height = 1 + max(getHeight(pCurrentRoot->pLeft), getHeight(pCurrentRoot->pRight));

    // New Root's new height = 1 + Max of its NEW children
    pNewRoot->height = 1 + max(getHeight(pNewRoot->pLeft), getHeight(pNewRoot->pRight));

    cout << "Rotate Right at Node ID: " << pCurrentRoot->data.id << endl;

    return pNewRoot;
}

Node* AVL::rotateLeft(Node* pCurrentRoot)
{
    Node* pNewRoot = pCurrentRoot->pRight;
    Node* lst = pNewRoot->pLeft; // the orphan

    // ------ Rotation ------

    pNewRoot->pLeft = pCurrentRoot;
    pCurrentRoot->pRight = lst;

    pCurrentRoot->height = 1 + max(getHeight(pCurrentRoot->pLeft), getHeight(pCurrentRoot->pRight));
    pNewRoot->height = 1 + max(getHeight(pNewRoot->pLeft), getHeight(pNewRoot->pRight));

    cout << "Rotate Left at Node ID: " << pCurrentRoot->data.id << endl;

    return pNewRoot;
}

Node* AVL::insertNode(Node*& pCurrentRoot, Node* pNewNode)
{
    // -------- Normal BST Flow --------

    // Empty (Tree - Subtree)
    if(pCurrentRoot == nullptr) return pNewNode;

    // Insert Left
    if( (pNewNode->data.id) < (pCurrentRoot->data.id) )
        pCurrentRoot->pLeft = insertNode(pCurrentRoot->pLeft, pNewNode);

    // Insert Right
    else if( (pNewNode->data.id) > (pCurrentRoot->data.id) )
        pCurrentRoot->pRight = insertNode(pCurrentRoot->pRight, pNewNode);

    // Prevent Duplicates
    else return pCurrentRoot;

    // -------- Maintaining Balance --------

    // Update the Height
    pCurrentRoot->height = 1 + max(getHeight(pCurrentRoot->pLeft), getHeight(pCurrentRoot->pRight));

    // Calculate the Balance Factor
    int balanceFactor = getBalanceFactor(pCurrentRoot);

    // LL (Left Left Imbalance) - Right Rotation
    if( (balanceFactor > 1) && (pNewNode->data.id < pCurrentRoot->pLeft->data.id) )
        return rotateRight(pCurrentRoot);


    // LR (Left Right Imbalance) - Left Rotation then Right Rotation
    if( (balanceFactor > 1) && (pNewNode->data.id > pCurrentRoot->pLeft->data.id) )
    {
        pCurrentRoot->pLeft = rotateLeft(pCurrentRoot->pLeft);
        return rotateRight(pCurrentRoot);
    }

    // RR (Right Right Imbalance) - Left Rotation
    if( (balanceFactor < -1) && (pNewNode->data.id > pCurrentRoot->pRight->data.id) )
        return rotateLeft(pCurrentRoot);


    // RL (Right Left Imbalance) - Right Rotation then Left Rotation
    if( (balanceFactor < -1) && (pNewNode->data.id < pCurrentRoot->pRight->data.id) )
    {
        pCurrentRoot->pRight = rotateRight(pCurrentRoot->pRight);
        return rotateLeft(pCurrentRoot);
    }

    // If already Balanced
    return pCurrentRoot;
}

Node* AVL::removeNode(Node* pCurrentRoot, int id)
{
    if (pCurrentRoot == nullptr) return pCurrentRoot;

    // Go Left
    if(id < pCurrentRoot->data.id)
        pCurrentRoot->pLeft = removeNode(pCurrentRoot->pLeft, id);

    // Go Right
    else if (id > pCurrentRoot->data.id)
        pCurrentRoot->pRight = removeNode(pCurrentRoot->pRight, id);

    // Node Found --->  ( pTargetNode->data.id == pCurrentRoot->data.id )
    else
    {
        // ------- Delete a Leaf - No Children -------
        if(pCurrentRoot->pLeft == nullptr && pCurrentRoot->pRight == nullptr)
        {
            delete pCurrentRoot;
            return nullptr; // return the new subtree root
        }

        // ------- Delete a Root - 1 Child (Left or Right) -------
        // ===> Only Right Child
        else if(pCurrentRoot->pLeft == nullptr)
        {
            Node* temp = pCurrentRoot->pRight;
            delete pCurrentRoot;
            return temp;   // return the new subtree root
        }

        // ===> Only Left Child
        else if(pCurrentRoot->pRight == nullptr)
        {
            Node* temp = pCurrentRoot->pLeft;
            delete pCurrentRoot;
            return temp;   // return the new subtree root
        }

        // ------- Delete a Root - 2 Children -------
        else
        {
            Employee maxLeft  = getMaxValueOnLeftSubTree(pCurrentRoot->pLeft);
            pCurrentRoot->data = maxLeft ;
            // Send the data, but only on the left-subtree, to exclude the root data from it
            pCurrentRoot->pLeft = removeNode(pCurrentRoot->pLeft, maxLeft .id);
        }
    }

    // -------- Maintaining Balance --------

    // Update the Height
    pCurrentRoot->height = 1 + max(getHeight(pCurrentRoot->pLeft), getHeight(pCurrentRoot->pRight));

    // Calculate the Balance Factor
    int balanceFactor = getBalanceFactor(pCurrentRoot);

    // LL (Left Left Imbalance) - Right Rotation
    if( (balanceFactor > 1) && (getBalanceFactor(pCurrentRoot->pLeft) >= 0) )
        return rotateRight(pCurrentRoot);


    // LR (Left Right Imbalance) - Left Rotation then Right Rotation
    if( (balanceFactor > 1) && (getBalanceFactor(pCurrentRoot->pLeft) < 0) )
    {
        pCurrentRoot->pLeft = rotateLeft(pCurrentRoot->pLeft);
        return rotateRight(pCurrentRoot);
    }

    // RR (Right Right Imbalance) - Left Rotation
    if( (balanceFactor < -1) && (getBalanceFactor(pCurrentRoot->pRight) <= 0) )
        return rotateLeft(pCurrentRoot);


    // RL (Right Left Imbalance) - Right Rotation then Left Rotation
    if( (balanceFactor < -1) && (getBalanceFactor(pCurrentRoot->pRight) > 0) )
    {
        pCurrentRoot->pRight = rotateRight(pCurrentRoot->pRight);
        return rotateLeft(pCurrentRoot);
    }

    // If already Balanced
    return pCurrentRoot;
}

Employee AVL::getMaxValueOnLeftSubTree(Node* pCurrentRoot)
{
    while(pCurrentRoot->pRight != nullptr) pCurrentRoot = pCurrentRoot->pRight;
    return pCurrentRoot->data;
}

void AVL::inorder(Node* pCurrentRoot)
{
    if(pCurrentRoot == nullptr) return;
    inorder(pCurrentRoot->pLeft);
    cout << pCurrentRoot->data.id << " (" << pCurrentRoot->data.name << ")" << endl;
    inorder(pCurrentRoot->pRight);
}

int AVL::countNodes(Node* pCurrentRoot)
{
    if(pCurrentRoot == nullptr) return 0;

    else return countNodes(pCurrentRoot->pLeft) + 1 + countNodes(pCurrentRoot->pRight);
}

int AVL::countLevels(Node* pCurrentRoot)
{
    if(pCurrentRoot == nullptr) return 0;

    int leftLevels = countLevels(pCurrentRoot->pLeft);
    int rightLevels = countLevels(pCurrentRoot->pRight);

    return 1 + (leftLevels > rightLevels ? leftLevels : rightLevels);
}

void AVL::deleteTree(Node*& pCurrentRoot)
{
    if (pCurrentRoot == nullptr) return;

    deleteTree(pCurrentRoot->pLeft);  // delete left subtree
    deleteTree(pCurrentRoot->pRight); // delete right subtree

    delete pCurrentRoot;              // delete current node
    pCurrentRoot = nullptr;           // set pointer to nullptr
}

int main()
{
    AVL tree;

    // ======= Insert Employees =======
    tree.insert({10, "Alice", 30, 5000});
    tree.insert({20, "Bob", 25, 4500});
    tree.insert({5,  "Charlie", 40, 5500});
    tree.insert({4,  "David", 28, 4700});
    tree.insert({8,  "Eve", 35, 6000});
    tree.insert({15, "Frank", 32, 5200});
    tree.insert({25, "Grace", 29, 4800});

    cout << "Inorder Traversal after Insertions:" << endl;
    tree.traverse();
    // Expected Output (sorted IDs): 4 5 8 10 15 20 25

    // ======= Remove Leaf Node =======
    cout << "\nRemove Leaf Node (ID = 4):" << endl;
    tree.remove(4);
    tree.traverse();
    // Expected Output: 5 8 10 15 20 25

    // ======= Remove Node with One Child =======
    cout << "\nRemove Node with One Child (ID = 25):" << endl;
    tree.remove(25);
    tree.traverse();
    // Expected Output: 5 8 10 15 20

    // ======= Remove Node with Two Children =======
    cout << "\nRemove Node with Two Children (ID = 10):" << endl;
    tree.remove(10);
    tree.traverse();
    // Expected Output: 5 8 15 20

    // ======= Remove Root Node =======
    cout << "\nRemove Root Node (ID = 15):" << endl;
    tree.remove(15);
    tree.traverse();
    // Expected Output: 5 8 20

    // ======= Count Nodes and Levels =======
    cout << "\nTotal Nodes: " << tree.countNodes(tree.getRoot()) << endl;
    cout << "Total Levels: " << tree.countLevels(tree.getRoot()) << endl;

    return 0;
}
