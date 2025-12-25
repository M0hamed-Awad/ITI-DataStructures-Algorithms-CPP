# 📂 Day 04 - Dynamic Structures & Priority Queues

### Objectives
- Implement a Generic Dynamic Array (Vector) from scratch  
- Understand Amortized Analysis and the doubling strategy for array growth  
- Build a Binary Min-Heap for efficient priority management  
- Master Percolation Algorithms (Up and Down) to maintain heap invariants  
- Use Templates to create type-independent, reusable data structures  

---

### Performance Analysis

| Structure | Operation | Time Complexity | Notes |
| :--- | :--- | :--- | :--- |
| Dynamic Array | Add (End) | O(1) | Amortized (Doubles when full) |
| Dynamic Array | Remove (Index) | O(n) | Due to element shifting |
| Min-Heap | Insert | O(log n) | Percolate Up logic |
| Min-Heap | Delete Min | O(log n) | Percolate Down logic |
| Min-Heap | Get Min | O(1) | Accessing the root |

---

### 📝 Tasks Summary

#### 1. Custom Dynamic Array (Generic Vector)
- Re-implementation of a dynamic-size array that manages its own memory buffer on the heap  
- **Doubling Strategy:** Doubles capacity when full to achieve Amortized O(1) addition  
- **Safe Access:** Overloaded `[]` with bounds checking; returns static dummy element if out-of-range  
- **Memory Management:** Provides `resize()` and `trim()` functions to manage capacity  

#### 2. Binary Min-Heap (Priority Queue)
- Complete binary tree stored in array format where every parent node ≤ children  
- **Array-to-Tree Mapping:**  
  - Parent: `(i - 1) / 2`  
  - Left Child: `2i + 1`  
  - Right Child: `2i + 2`  
- **Balance Mechanism:**  
  - **Percolate Up:** Moves new element up to restore heap property  
  - **Percolate Down:** After deleting root, moves last element down to correct position  

---

### 💡 Technical Insights
- **Amortized Cost:** Doubling capacity ensures expensive copying occurs infrequently, giving average O(1) addition  
- **Heap vs. Sorted Array:** Sorted array gives O(1) min access but O(n) insertion; Min-Heap allows O(log n) insertion/deletion  
- **Template Power:** Structures are implemented as template classes to support int, double, std::string, or custom objects (e.g., Employee struct)  

---

### 📁 Repository Structure
- `Task01_Dynamic_Array`: Manual memory management and array growth logic  
- `Task02_Min_Heap`: Implementation of the binary heap using `std::vector` as the underlying container 