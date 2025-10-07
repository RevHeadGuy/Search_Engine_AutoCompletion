# 🔍 Search Engine Auto-Completion

A **Trie + Heap based Auto-Complete System** that suggests the most relevant search queries based on user input prefixes — just like Google or YouTube search boxes.

This project demonstrates efficient prefix-based searching using **Data Structures & Algorithms (DSA)** concepts such as **Trie, DFS, and Max Heap**.

---

## 🚀 Features

- ✅ Suggests the **Top-K most frequent** search completions.
- ✅ Uses a **Trie** for prefix-based lookups.
- ✅ Uses a **Max Heap (priority queue)** for ranking results by frequency.
- ✅ Supports **multi-word queries** (e.g., "how to make pizza").
- ✅ Interactive console-based demo.
- ✅ Easily extendable for real datasets.

---

## 🧠 Data Structures Used

| DSA | Purpose |
|-----|----------|
| **Trie (Prefix Tree)** | Stores all search queries for fast prefix lookup |
| **DFS (Depth-First Search)** | Traverses all completions of a given prefix |
| **Heap / Priority Queue** | Returns top-k highest frequency suggestions efficiently |

---

## 📂 Project Structure

📦 SearchEngineAutoComplete

┣ 📜 autocomplete.cpp # Main source code

┣ 📜 README.md # Project documentation

## ⚙️ How It Works

1. **Insertion Phase:**
2. 
   Each query (like `"how to make pizza"`) is inserted into the Trie.  
   - If it already exists, its frequency is incremented.
   - Otherwise, a new path in the Trie is created.

3. **Search Phase:**
   
   When a user types a prefix (e.g., `"how to m"`), the system:
   - Traverses to the prefix node in the Trie.
   - Performs a **DFS** from that node to collect all words starting with that prefix.
   - Pushes all results into a **max-heap** sorted by:
     - Higher frequency → higher priority  
     - Same frequency → lexicographically smaller first

4. **Result Phase:**
   
   Returns the top-`k` most relevant completions.

---
