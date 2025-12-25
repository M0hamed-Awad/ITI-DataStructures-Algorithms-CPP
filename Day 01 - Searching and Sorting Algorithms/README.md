# 📂 Day 01 - Searching and Sorting Algorithms

### Objectives
- Master fundamental Searching techniques (**Linear vs. Binary**)  
- Implement various Sorting algorithms and analyze their **Time & Space complexities**  
- Understand the **Divide and Conquer** paradigm through Merge and Quick Sort  
- Implement Tree-based sorting using Heap Sort  

---

### Algorithms Complexity Analysis

| Algorithm         | Best Case    | Average Case | Worst Case   | Space Complexity |
|------------------|-------------|--------------|-------------|----------------|
| Sequential Search | O(1)        | O(n)         | O(n)        | O(1)           |
| Binary Search     | O(1)        | O(log n)     | O(log n)    | O(1) / O(log n)|
| Bubble Sort       | O(n)        | O(n²)        | O(n²)       | O(1)           |
| Heap Sort         | O(n log n)  | O(n log n)   | O(n log n)  | O(1)           |
| Merge Sort        | O(n log n)  | O(n log n)   | O(n log n)  | O(n)           |
| Quick Sort        | O(n log n)  | O(n log n)   | O(n²)       | O(log n)       |

---

### 📝 Tasks Summary

#### 1. Binary Search (Iterative & Recursive)
- Implementation of the Binary Search algorithm on a **sorted array**  
- **Recursive Approach:** Utilizes the system stack for the divide-and-conquer logic  
- **Iterative Approach:** Uses a while loop, more memory-efficient by avoiding recursion overhead  

#### 2. Optimized Bubble Sort
- Comparison-based sorting algorithm  
- **Feature:** Includes an `isSorted` flag optimization, terminating early if the array becomes sorted before all passes, achieving **O(n)** in the best case  

#### 3. Heap Sort
- Efficient sorting algorithm based on the **Binary Heap** data structure  
- **Logic:** Build a Max-Heap and repeatedly extract the maximum element  
- **Key Functions:** `heapify()` and `buildHeap()`  

#### 4. Merge Sort
- Classic **Divide and Conquer** algorithm  
- **Strategy:** Recursively split the array into halves, sort them, and merge the sorted halves  
- **Space Note:** Requires O(n) auxiliary space for the temporary merging array  

#### 5. Quick Sort
- Another Divide and Conquer algorithm, typically faster in practice than Merge Sort  
- **Strategy:** Pick a Pivot element and partition the array such that elements smaller than the pivot are on the left and larger ones on the right  
- **Partitioning:** Uses a two-pointer approach to sort elements around the pivot in-place  

#### 6. Sequential Search Variants
- **Unsorted:** Simple linear traversal  
- **Sorted:** Optimized traversal that exits early if the current element exceeds the target key, reducing unnecessary comparisons  

---

### 💡 Key Learnings
- **Stability:** Merge Sort is stable (preserves order of duplicates), while Quick Sort and Heap Sort are not  
- **In-place vs. Out-of-place:** Merge Sort requires extra memory, whereas Quick Sort and Heap Sort work within the original array (in-place)  
- **Recursion vs. Iteration:** Balancing code elegance with stack memory efficiency  