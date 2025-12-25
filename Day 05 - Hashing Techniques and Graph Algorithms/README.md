# 📂 Day 05 - Hashing & Graph Theory

### Objectives
- Implement a Generic Hash Table with Separate Chaining for collision resolution  
- Master the Rehashing process to maintain constant time complexity O(1)  
- Model complex networks using Directed Weighted Graphs  
- Implement fundamental graph traversals: Breadth-First Search (BFS) and Depth-First Search (DFS)  
- Solve the shortest path problem using Dijkstra's Algorithm  

---

### Complexity & Performance Analysis

| Structure / Algorithm | Operation | Time Complexity | Notes |
| :--- | :--- | :--- | :--- |
| Hash Table | Search / Insert | O(1) Average | Degrades to O(n) without rehashing |
| Graph (Matrix) | Add Edge | O(1) | Immediate access via indices |
| BFS / DFS | Traversal | O(V²) | Due to adjacency matrix traversal |
| Dijkstra | Shortest Path | O(V²) | Can be O(E log V) with adjacency list |

---

### 📝 Tasks Summary

#### 1. Advanced Hash Table (Rehashing & Chaining)
- High-performance Key-Value data structure for O(1) lookups  
- **Collision Handling:** Separate Chaining using a vector of doubly linked lists  
- **Dynamic Resizing (Rehash):** Triggers when Load Factor > 0.75; doubles table size and redistributes elements  
- **Generic Implementation:** Template-based to support any data type (e.g., Employee objects)  

#### 2. Directed Weighted Graph System
- **Representation:** Adjacency Matrix for directed edges with weights  
- **Traversals:**  
  - **BFS:** Level-order exploration with a queue for shortest paths in unweighted graphs  
  - **DFS:** Depth-first exploration with a stack for path discovery and connectivity testing  
- **Shortest Path (Dijkstra's Algorithm):**  
  - Greedy approach for minimum distances from source vertex  
  - Uses Min-Priority Queue (Min-Heap) for efficient vertex selection  

---

### 💡 Key Technical Insights
- **Load Factor Balance:** Standard factor 0.75 balances memory usage and search speed  
- **Dijkstra in Real World:** Core algorithm for OSPF networking protocols and GPS navigation  
- **Adjacency Matrix Trade-offs:** O(V²) space, but allows O(1) edge lookup; ideal for dense graphs  

---

### 📁 Repository Structure
- `Task01_Hash_Table`: Implementation of chaining and automated rehashing  
- `Task02_Graph_Algorithms`: Directed graph with BFS, DFS, and Dijkstra implementations  