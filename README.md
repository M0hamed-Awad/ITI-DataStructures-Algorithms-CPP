# Data Structures & Algorithms (DSA) | ITI

[![Language](https://img.shields.io/badge/Language-C%2B%2B-blue.svg)](https://isocpp.org/)
[![Topic](https://img.shields.io/badge/Topic-Algorithms-orange.svg)]()
[![Standard](https://img.shields.io/badge/Standard-C%2B%2B20-green.svg)]()

This repository documents my intensive journey through **Data Structures and Algorithms** at the **Information Technology Institute (ITI)**. It features low-level implementations of fundamental and advanced structures, focusing on memory efficiency, generic programming with templates, and rigorous complexity analysis.

---

## Table of Contents
* [Curriculum Roadmap](#curriculum-roadmap)
* [Key Algorithm Complexity](#key-algorithm-complexity)
* [Featured Implementations](#featured-implementations)
* [Core Competencies](#core-competencies)
* [Repository Structure](#repository-structure)
* [How to Run](#how-to-run)

---

## Curriculum Roadmap

| Module | Focus Area | Key Implementations |
| :--- | :--- | :--- |
| **Day 01** | **Search & Sort** | Binary Search, Quick Sort, Merge Sort, and Heap Sort. |
| **Day 02** | **Linked Lists** | Singly & Doubly Linked Lists, LIFO Stack, and FIFO Queue. |
| **Day 03** | **Hierarchical Trees** | Binary Search Tree (BST) and Self-Balancing AVL Trees. |
| **Day 04** | **Dynamic Containers** | Generic Dynamic Array (Vector) and Min-Heap (Priority Queue). |
| **Day 05** | **Hashing & Graphs** | Chained Hash Tables with Rehashing, Dijkstra’s Algorithm, BFS/DFS. |

---

## Key Algorithm Complexity

Understanding the trade-offs between Time and Space complexity is at the heart of this repository.

| Algorithm | Average Time | Space Complexity | Paradigm |
| :--- | :--- | :--- | :--- |
| Quick Sort | O(n log n) | O(log n) | Divide & Conquer |
| Merge Sort | O(n log n) | O(n) | External/Stable Sort |
| Binary Search | O(log n) | O(1) | Decrease & Conquer |
| AVL Search | O(log n) | O(n) | Self-Balancing Tree |
| Hash Lookup | O(1) | O(n) | Hashing / Chaining |
| Dijkstra | O(V^2) | O(V) | Greedy / Pathfinding |

---

## Featured Implementations

### 1. Self-Balancing AVL Trees
Beyond the basic BST requirements, I implemented a full **AVL Tree** to guarantee O(log n) search performance even in worst-case scenarios.

* **Mechanism:** Handles 4 types of rotations (LL, RR, LR, RL) triggered by Balance Factor changes.
* **Visual Aid:** I created a custom Motion Graphics video to explain these rotations visually.
* 🎥 **[Watch the AVL Explainer Video on LinkedIn](Link)**

### 2. Dynamic Hash Table with Rehashing
A generic `HashTable` implementation using **Separate Chaining** to handle collisions effectively.

* **Load Factor Optimization:** To maintain O(1) efficiency, the table automatically triggers a **Rehash** (doubling capacity and re-distributing keys) once the load factor exceeds 0.75.

### 3. Graph Theory & Pathfinding
Implementation of a directed, weighted graph using an **Adjacency Matrix**.

* **Dijkstra’s Algorithm:** Utilizes a Min-Priority Queue to find the shortest path—a logic used in modern OSPF networking protocols and GPS systems.
* **Traversals:** Full implementation of Breadth-First Search (BFS) and Depth-First Search (DFS).

---

## Core Competencies

* **Advanced Pointers:** Manual heap management and pointer manipulation for non-linear structures.
* **Template Meta-programming:** Building generic containers capable of storing any data type (integers, strings, or custom structs).
* **Software Architecture:** Applying OOP principles (Inheritance, Operator Overloading) to build data structures from scratch.

---

## Repository Structure

```text
📂 ITI-Data-Structures-Algorithms
 ┣ 📂 Day_01_Searching_Sorting
 ┣ 📂 Day_02_Linked_Structures
 ┣ 📂 Day_03_Trees_and_Balancing
 ┣ 📂 Day_04_Dynamic_Structures
 ┗ 📂 Day_05_Hashing_and_Graphs
```

 ---

## 🚀 How to Run

1. **Clone the repository**:

```bash
git clone https://github.com/M0hamed-Awad/ITI-DataStructures-Algorithms-CPP.git
```

2. **Compile (Using MinGW/GCC recommended):**
```bash
g++ -std=c++20 main.cpp -o app
```

3. **Run**: Execute the generated file in a terminal that supports ANSI codes for the best UI experience.