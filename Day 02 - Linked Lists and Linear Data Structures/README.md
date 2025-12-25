# 📂 Day 02 - Linked Lists & Linear Data Structures

### Objectives
- Implement **Singly Linked Lists (SLL)** for dynamic linear storage  
- Master **Doubly Linked Lists (DLL)** for bi-directional traversal  
- Apply **Inheritance** to build specialized structures (**Stacks & Queues**) over linked lists  
- Implement **Sorted Insertion** logic to maintain data integrity  
- Understand the trade-offs between different linear data structures in terms of **Time Complexity**  

---

### Time Complexity Comparison

| Operation       | Singly Linked List | Doubly Linked List | Array (Static) |
|-----------------|-----------------|------------------|----------------|
| Insert Front    | O(1)            | O(1)             | O(n)           |
| Insert End      | O(n) (without tail) | O(1) (with pLast) | O(1)       |
| Search          | O(n)            | O(n)             | O(n) / O(log n)|
| Delete Front    | O(1)            | O(1)             | O(n)           |
| Delete Middle   | O(n)            | O(n)             | O(n)           |

---

### 📝 Tasks Summary

#### 1. Singly Linked List (SLL)
- Dynamic structure where each node contains data and a pointer to the next node  
- **Operations:** Comprehensive CRUD including insertion and deletion by position, value, or at the boundaries  
- **Logic:** Efficient forward traversal and manual memory cleanup  

#### 2. Doubly Linked List (DLL) - Employee Management
- Nodes point both to the next and previous elements  
- **Resource Safety:** Implements the Rule of Three (Destructor, Copy Constructor, Copy Assignment) for deep copies of dynamic nodes  
- **Operator Overloading:** Overloaded the subscript operator `[]` for intuitive array-like access to employee data  

#### 3. Sorted Doubly Linked List
- Maintains elements in ascending order based on ID  
- **Strategy:** Traverse the list during insertion until the correct position is found, ensuring **O(n)** sorted insertion without a separate sorting step  

#### 4. Stack Implementation (LIFO)
- Last-In-First-Out structure built by inheriting from the DLL class  
- **Mechanism:** All operations (push, pop, peek) target the `pLast` pointer of the Doubly Linked List for **O(1)** performance  

#### 5. Queue Implementation (FIFO)
- First-In-First-Out structure built by inheriting from the DLL class  
- **Mechanism:** Elements are added at the rear (`pLast`) and removed from the front (`pStart`) for efficient flow  

---

### 💡 Key Technical Highlights
- **Memory Management:** Every class implements a robust destructor to traverse the list and delete nodes individually, preventing memory leaks in a dynamic heap environment  
- **Pointer Manipulation:** Direct manipulation of `pNext` and `pPrev` pointers, especially in "Middle Deletion" logic, to bypass nodes and re-link the structure seamlessly  
- **Code Reusability:** Leveraging **Inheritance** to create Stacks and Queues demonstrates how basic data structures can serve as the foundation for more complex ones  