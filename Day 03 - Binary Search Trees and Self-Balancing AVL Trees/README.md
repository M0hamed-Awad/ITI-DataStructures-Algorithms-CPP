# 📂 Day 03 - Binary Search Trees & Self-Balancing AVL Trees

### Objectives
- Implement **Binary Search Trees (BST)** for hierarchical data management  
- Master complex node deletion cases (Leaf, Single Child, and Two Children)  
- Solve the **Skewed Tree** problem by maintaining balance  
- Deep dive into **AVL Trees** and automated balancing through rotations  
- Analyze height-based complexity and **Balance Factors**  

---

### Complexity Overview

| Structure | Search (Avg) | Search (Worst) | Space Complexity |
| :--- | :--- | :--- | :--- |
| **Basic BST** | O(log n) | O(n) (Skewed) | O(n) |
| **AVL Tree** | O(log n) | O(log n) | O(n) |

---

### 📝 Tasks Summary

#### 1. BST with Manual Rebalancing
- Addresses "Skewed Trees" where BST can degrade into a linked list causing O(n) performance  
- **Strategy:** Flatten tree into a sorted vector (Inorder traversal), destroy it, and rebuild using **Divide and Conquer** so the median becomes the new root  
- **Core Logic:** Recursive height calculation and early detection of imbalance  

#### 2. AVL Tree (Self-Balancing Engine)
- Maintains **Balance Factor** strictly between -1 and 1 during every insertion/removal  
- **Self-Study Achievement:** Researched and implemented **AVL Rotation Logic**  
- **Rotations Implemented:**  
  - **Single Rotations:** Left-Left (LL) and Right-Right (RR)  
  - **Double Rotations:** Left-Right (LR) and Right-Left (RL)  
- **Metadata:** Each node tracks its own `height` for O(1) balance factor calculation  

---

### 🎥 Visual Learning: AVL Rotations Explained
- Created a **Motion Graphics** video to illustrate complex pointer swapping during rotations for O(log n) performance  
- 👉 **[Watch my AVL Rotations Explainer on LinkedIn](LINK)**  

---

### 💡 Key Technical Insights
- **Case 3 Deletion (Two Children):** Uses **Inorder Predecessor** (max of left subtree) to replace deleted node while maintaining BST properties  
- **"Orphan" Adoption:** Properly reassigns subtrees during AVL rotations to maintain structure  
- **Automated Height Updates:** Every recursive call updates node height ensuring accurate metadata for subsequent operations  

---

### 📁 Structure
- `Task01_BST_Manual_Rebalance`: Manual rebalancing via sorted vector reconstruction  
- `Task02_AVL_Implementation`: Advanced self-balancing tree with 4-way rotation logic  