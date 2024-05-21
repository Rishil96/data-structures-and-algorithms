# Algorithms

| Sr. No. | Topic |
|:---:|:---:|
| 1 | [Binary Search](#1) |
| 2 | [Bubble Sort](#2) |
| 3 | [Selection Sort](#3) |
| 4 | [Insertion Sort](#4) |
| 5 | [Merge Sort](#5) |
| 6 | [Quick Sort](#6) |
| 7 | [Linked List](#7) |
| 8 | [Floyd's Cycle Detection](#8) |
| 9 | [Stack](#9) |
| 10 | [N Stacks in an array](#10) |
| 11 | [Queue](#11) |
| 12 | [K Queues in an array](#12) |
| 13 | [Build Generic Binary Tree](#13) |
| 14 | [Inorder Traversal](#14) |
| 15 | [Preorder Traversal](#15) |
| 16 | [Postorder Traversal](#16) |
| 17 | [Levelorder Traversal](#17) |
| 18 | [Morris Traversal](#18) |
| 19 | [Binary Search Tree](#19) |
| 20 | [Delete node from BST](#20) |
| 21 | [Heap](#21) |
| 22 | [Heapify an array](#22) |
| 23 | [Heap Sort](#23) |
| 24 | [Trie](#24) |
| 25 | [Graph](#25) |
| 26 | [Undirected Graph Cycle Detection BFS](#26) |
| 27 | [Undirected Graph Cycle Detection DFS](#27) |
| 28 | [Directed Graph Cycle Detection DFS](#28) |
| 29 | [Topological Sort BFS](#29) |
| 30 | [Topological Sort DFS](#30) |
| 31 | [Shortest Path using BFS](#31) |
| 32 | [Shortest Path using DFS](#32) |
| 33 | [Dijkstra's Algorithm](#33) |
| 34 | [Bellman-Ford Algorithm](#34) |
| 35 | [Floyd-Warshall Algorithm](#35) |
| 36 | [KosaRaju Algorithm](#36) |
| 37 | [Tarjans Algorithm](#37) |
| 38 | [Prims Algorithm](#38) |
| 39 | [Kruskals Algorithm](#39) |


---

<h3 id="1">Binary Search</h3>

- Description
    - an searching algorithm that searches an element in a sorted array in log(n) Time Complexity.
- Algorithm
    1. Create two index variables denoting the **start** and **end** index of the array.
    2. While **start** index is less than or equal to **end** index we run while loop.
    3. Calculate **mid** index using start and end index.
    4. If **target** is at **mid** index return the mid index.
    5. If **target** is greater than element at **mid** index, check the right subarray in next iteration by moving **start** index to **mid + 1**.
    6. If target is lesser than element at mid index, check the left subarray in next iteration by moving **end** index to **mid - 1**.
    7. If target is not found and start becomes greater than end, then return -1.
---

<h3 id="2">Bubble Sort</h3>

- Description
    - Bubble Sort is a sorting algorithm that sorts an array in n - 1 passes.
    - In Bubble Sort, in every kth pass the kth largest element is placed in its correct position.
    - Simply putting, in first pass the largest element will be placed at the last index, then in second pass the second largest element will be placed at the second last index and so on.
- Algorithm
    1. Run outer for loop with iterator index **i** that goes from 0 to second last index of array.
    2. Run inner for loop with iterator index **j** that goes from **0** to **n - i - 1** (means the kth last index).
    3. Now keep comparing **jth** element with **(j+1)** element and swap them if **jth** element is greater than **(j + 1)** element
    4. Repeat this step for **n - 1** passes and the array will be sorted.

---

<h3 id="3">Selection Sort</h3>

---

<h3 id="4">Insertion Sort</h3>

---

<h3 id="5">Merge Sort</h3>

---

<h3 id="6">Quick Sort</h3>

---

<h3 id="7">Linked List</h3>

---

<h3 id="8">Floyd's Cycle Detection</h3>

---

<h3 id="9">Stack</h3>

---

<h3 id="10">N Stacks in an array</h3>

---

<h3 id="11">Queue</h3>

---

<h3 id="12">K Queues in an array</h3>

---

<h3 id="13">Build Generic Binary Tree</h3>

---

<h3 id="14">Inorder Traversal</h3>

---

<h3 id="15">Preorder Traversal</h3>

---

<h3 id="16">Postorder Traversal</h3>

---

<h3 id="17">Levelorder Traversal</h3>

---

<h3 id="18">Morris Traversal</h3>

---

<h3 id="19">Binary Search Tree</h3>

---

<h3 id="20">Delete a node from BST</h3>

---

<h3 id="21">Heap</h3>

---

<h3 id="22">Heapify an array</h3>

---

<h3 id="23">Heap Sort</h3>

---

<h3 id="24">Trie</h3>

---

<h3 id="25">Graph</h3>

---

<h3 id="26">Undirected Graph Cycle Detection BFS</h3>

---

<h3 id="27">Undirected Graph Cycle Detection DFS</h3>

---

<h3 id="28">Directed Graph Cycle Detection DFS</h3>

---


---

<h3 id="29">Topological Sort BFS</h3>

---

<h3 id="30">Topological Sort DFS</h3>

---

<h3 id="31">Shortest Path using BFS</h3>

---

<h3 id="32">Shortest Path using DFS</h3>

---

<h3 id="33">Dijkstra's Algorithm</h3>

---

<h3 id="34">Bellman-Ford Algorithm</h3>

---

<h3 id="35">Floyd-Warshall Algorithm</h3>

---

<h3 id="36">KosaRaju Algorithm</h3>

---

<h3 id="37">Tarjans Algorithm</h3>

---

<h3 id="38">Prims Algorithm</h3>

---

<h3 id="39">Kruskals Algorithm</h3>

---