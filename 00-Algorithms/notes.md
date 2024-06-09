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
| 29 | [Topological Sort DFS](#29) |
| 30 | [Topological Sort BFS](#30) |
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

- Description
    - Selection Sort is an algorithm where we place the smallest kth element to its correct place in kth pass.
    - Initially we consider 0th position as sorted list and compare rest of the elements with 0th element.
    - Once we find the smallest element, we swap the smallest with 0th element thus placing the smallest element at 0th position.
- Algorithm
    1. Run outer loop determining the latest index of sorted portion of the array. (0 to n - 2).
    2. Run inner loop starting from outer loop index + 1 and going till last element of array.
    3. Find the index of the smallest element in the inner loop.
    4. After completion of inner loop, we will have the smallest index for that pass so swap the elements of smallest index to the outer loop index.
    5. Repeat this n - 2 times in outer loop.

---

<h3 id="4">Insertion Sort</h3>

- Description
    - is a stable sorting algorithm meaning the relative position of equal elements do not change.
    - In Insertion sort we initially consider 1st element as sorted and as we go on we increasing that number till we reach last element.

- Algorithm
    1. Run outer loop from 1 to last index of array (i).
    2. Initialize key = element at i and j = i - 1
    3. Now inner loop is a while loop that checks if element at j is greater than key, if yes then we insert the element at j to position j + 1 i.e. arr[j+1] = arr[j] and decrement j.
    4. This inner loop runs till either j >= 0 and the above condition is true.
    5. Once inner loop is done running, we simply insert the key at j + 1 position i.e. arr[j + 1] = key.
    6. The array will be sorted once outer loop finishes execution. So simply speaking we push element at j to postion j + 1 till element at j is greater than key.

---

<h3 id="5">Merge Sort</h3>

- Description
    - is a divide and conquer algorithm that uses recursion to split the array into 2 and merge them back in sorted order later.
    - consists of 2 functions:-
        1. mergeSort() that uses start and end indexes of the array and splits it into two using mid index.
        2. merge() that merges the left and right sub arrays back to one.

- Algorithm
    1. Call the mergeSort function which will recursively call itself and split the arrays in 2.
    2. This splitting will keep on till there are only 1 element left on each left and right subarrays for that recurisive call.
    3. Now merge function will be called after mergeSort to merge the left and right subarrays in sorted form using the Merge 2 sorted arrays algorithm.
    - Can be understood better in code.

---

<h3 id="6">Quick Sort</h3>

- Description
    - also a divide and conquer algorithm.
    - here we choose a pivot element and place it to its correct position and let recursion place the elements in sorted order for left and right subarray.

- Algorithm
    1. Base case will be returned if start is greater than or equal to end meaning 1 or no element in array.
    2. Firstly, get the pivot element by choosing any one element from the array (could be first, last, random any element).
    3. Now place the pivot element to its correct position by any logic (e.g. count the elements smaller than pivot and place it to the next index).
    4. After placing the pivot to its correct position, move all the elements smaller than pivot to its left side and elements larger than pivot to its right side.
    5. Return the pivot index after performing the above steps.
    6. Now call quick sort recursively for left subarray of pivot and right subarray of pivot.

---

<h3 id="7">Linked List</h3>

- Linked List is a linear data structure that stores the data as nodes where each node carries data and the address to the next node.
- The common functionalities of Linked List are :- insert, delete, size, search, reverse.

---

<h3 id="8">Floyd's Cycle Detection</h3>

- Floyd's Cycle Detection is an algorithm to detect a cycle in Linked LIst.
- Use 2 pointers slow and fast, slow pointer moves once and fast pointers move twice in each iteration.
- If slow and fast pointer meet, it means a cycle is present and if fast pointer reaches end of List, it means no cycle is present.

---

<h3 id="9">Stack</h3>

- Stack is a data structure that stores data in Last In First Out (LIFO) approach.
- only the top element can be accessed in the Stack.
- common functions of stack are push, pop, peek/top, size and is empty.

---

<h3 id="10">N Stacks in an array</h3>

- Given an array implement N Stacks in an array.
- N => Number of stacks.
- S => Size of array.
- Requirements:-
- **Top array** => an array that stores top element of each stack. Size of top array is N. Initialize with -1 denoting empty stacks.
- **Next array** => 
    - points to next element after top element.
    - points to the next free space.
- this is for each index. It is an array of size S.
- Initialize with next freespot, for 0 next freespot is 1, for 1 it is 2 and so on with last index has no next free space so -1.
- **freeSpot** => shows the current free spot in array.

- **Push Element**
    1. Find index i.e. a free spot.
    2. Update free spot to the next one using next array.
    3. Insert element in main array.
    4. Update next array but getting the previous top element of ith stack using top array.
    5. Update top array to index of top element in main array.

- **Pop Element**
    1. Get index of top element which is going to be popped.
    2. Update top array with the current next element index.
    3. Remove element from main array.
    4. Update next array with freeSpot.
    5. Update freeSpot with index from where the element was popped.
---

<h3 id="11">Queue</h3>

- Queue is a data structure that stores data in FIFO (First In First Out) manner.
- Two pointers front and rear are used, new items are added from rear and deleted from front.

---

<h3 id="12">K Queues in an array</h3>

- Given an array of size n, implement k queues in this array.
- Requirements:-
    - **front array** => size k that shows front index of kth queue.
    - **rear array** => size k that stores rear index of kth queue.
    - **next array** => size n stores indexes of next item for all items in array.
    - **freeSpot** => current available free spot in main array.

- **Push Algorithm**
    1. Check overflow (freespot = -1 is overflow)
    2. Find first free index.
    3. Update free spot.
    4. If first element of ith queue i.e. front of kth queue is -1 then update front of kth queue to new index.
    5. If not first element, then link the previous rear element of kth queue with this new element which will become the new rear.
    6. Update next of index to -1.
    7. Update rear to new element index.
    8. Insert element in main array.

- **Pop Algorithm**
    1. Check Underflow (front[kth queue] is -1)
    2. Find index to pop which is front of kth queue.
    3. Update front to its next element using next of index.
    4. Manage freespot variable by updating next of index to freespot as that index will be free after front is popped.
    5. Set free spot to current index from which element was popped.
    
---

<h3 id="13">Build Generic Binary Tree</h3>

- A binary tree is a non-linear data structure that stores data in the form of nodes as parents and children.
- Each node can have 0, 1 or 2 children that is connected to them using pointers left and right.

---

<h3 id="14">Inorder Traversal</h3>

- a way to traverse a Binary Tree where we traverse the left subtree first, followed by node and then followed by right subtree.

---

<h3 id="15">Preorder Traversal</h3>

- a way to traverse a Binary Tree where we traverse the node first, followed by left subtree and then followed by right subtree.

---

<h3 id="16">Postorder Traversal</h3>

- a way to traverse a Binary Tree where we traverse the left subtree first, followed by right subtree and then followed by the node.

---

<h3 id="17">Levelorder Traversal</h3>

- a way to traverse a Binary Tree where we traverse the tree from root to the leaf nodes as levels/depth.

---

<h3 id="18">Morris Traversal</h3>
   
- this traversal is basically inorder traversal but here we do it in O(1) Space Complexity but not using Recursion.
- **Algorithm**
1. Create variable curr set to root to use in traversal.
2. Start while loop using curr and it will run till curr is a valid node and not NULL.
3. IF 
    - curr has no left node, visit the curr node and go right.
4. ELSE
    - Find Inorder Predecessor of curr node (go left once then keep going right till we find NULL or we find curr node).
    - IF right of predecessor is NULL, then make connection from predecessor to curr node using right pointer (pred -> right = curr) and then move curr to its left.
    - ELSE it means predecessor is pointing to the current node means it has been visited once. First remove connection of pred with curr node (pred -> right = NULL). Then visit the curr node and move curr to its right.
    - PTR : while getting the predecessor of any node, it is possible to get stuck in infinite loop as we are pointing the predecessor to that node to return back, so we also have to check if the predecessor node is pointing to the current node and break loop if it is.

---

<h3 id="19">Binary Search Tree</h3>

- this data structure is the same as Binary Tree but with one condition.
- The elements smaller than the root will be placed to its left and the elements larger than the root will be placed to its right. 
- This condition is followed for every node in the tree.

---

<h3 id="20">Delete a node from BST</h3>

- Deleting a node can be done recursively.
- If root is empty return NULL.
- Use recursion to traverse left / right if the key is smaller or larger than the current root.
- When the key is equal to the current node, we start our deletion process.
- There are 4 possible cases:-
    1. Leaf Node: if the node to delete is a leaf node, delete the node and return NULL.
    2. Only left tree: if the node to delete has only left subtree, save the left subtree in a variable, delete the current node and return the left subtree.
    3. Only right tree: if the node to delete has only right subtree, save the right subtree in a variable, delete the current node and return the right subtree.
    4. Both trees: if the node to delete has both sub trees, first get the inorder predecessor of the node to delete. Copy the value of the predecessor to the current node that we want to delete, then call the delete node function to go and delete the predecessor. 
    - This way we simply replace the node to delete with predecessor node and then delete the predecessor.
- Finally return the root node.

---

<h3 id="21">Heap</h3>

- Heap is a Data Structure that exists in a Complete Binary Tree form and holds a heap property.

- Created as an array but visualized as a tree.

- Complete BT: all levels are completely filled except last one. Node filling happens from left to right.

- Heap Property:
    - Max property: parent is greater than both of its child. called as MaxHeap.
    - Min property: parent is lesser than both of its child. called as MinHeap.

- Indexes (Parent to Child):
    - Starting index is 1 of array
    - Parent: i
    - LeftChild: 2i
    - RightChild: 2i+1

- Starting index is 0 of array
    - Parent: i
    - LeftChild: 2i+1
    - RightChild: 2i+2

- Child to Parent:
    - Of any child i/2 will be its parent index.

- Insertion:-
    1. Add node to the end of array
    2. Place it to the correct place as per Heap Property and Complete Binary Tree property.
    Compare with parent using index and replace as per Heap Property.
    - TC: O(logn)

- Deletion:-

    - Only the root node is allowed to be deleted in a heap.
    1. Replace last value with root and delete last node.
    2. Place root to its correct position.

---

<h3 id="22">Heapify an array</h3>

- heapify is a function that places the element at index to its correct position in terms of Heap.
- Algorithm:-
    - Input :- array, n (last index of array), i (index of element to heapify)
    1. i is considered as parent, get left and right child indexes.
    2. Use variable largest and store the largest element index among the children in this variable.
    3. If largest is not equal to the initial index of the element, then swap the index with the largest child and call heapify on the child where we swapped.

---

<h3 id="23">Heap Sort</h3>

- Sort an array that follows the heap rule.
- Algorithm:-
    1. Save last index of array in variable index.
    2. Run while loop on index till index is greater than 1.
    3. Swap first element with the last element as first element is the largest in max heap.
    4. Reduce the array size by 1 as we already sorted the last element and call heapify on first element to place the largest element back on 1st position.
---

<h3 id="24">Trie</h3>

- is a tree like data structure also known as prefix tree.
- used to efficiently store string type data.
- a known usecase is searching in browsers.
- each node contains a single character as data and has multiple children pointers which points to the next character in the stored string.
- 3 functions are : insert, delete and search.

---

<h3 id="25">Graph</h3>

- a graph is a data structure that stores in the form of nodes and each nodes may be linked to another node through edges.
- e.g. social media where each account can act as a node and their friends list will be edges.

- Breadth First Search
    1. Create a queue to hold the nodes that are not visited and insert the source node in the queue and mark it as visited.
    2. Run while loop till queue has atleast one node.
    3. In the while loop, pop the front node from the queue, and visit the node.
    4. Go through the neighbours of the front node and add them to the queue if they are not already visited and mark them as visited.

- Depth First Search
    1. Visit the source node and mark it as visited.
    2. For all the neighbour nodes of source, if they are not visited, mark them as visited and call dfs recursively for the neighbour nodes which will be the new source.

---

<h3 id="26">Undirected Graph Cycle Detection BFS</h3>

- **Algorithm**

    1. Cycle Detection using BFS for Undirected Graph will accept 3 inputs: source node, visited map (stores if current node is visited) and parent map (stores the parent node of current node).
    2. Initialize queue and add the source node in the queue, mark source node as visited and mark parent of source node as -1 (dummy value as source is root and doesn't have parent).
    3. Run while loop till we find a cycle or till there are nodes left in queue to be visited.
    4. Inside while loop, pop out the front node from queue.
    5. Loop through the neighbours of the front node.

        - **IF** current neighbour in loop is not visited, mark it visited, set parent of current neighbour to front node and add neighbour in queue.
        - **ELSE** check if parent of front node is the current neighbour, if it is the case then we are fine but if current neighbour is not the parent of front node, it means neighbour was already visited before by some another node, this tells us that cycle is present, return true.
    6. Once the queue has no nodes left, return false as we visited all nodes but couldn't find any cycle.
---

<h3 id="27">Undirected Graph Cycle Detection DFS</h3>

- **Algorithm**

    1. Cycle Detection using DFS for undirected graph will accept 3 inputs: source node, visited map and parent node of source.
    2. Visited the source node by marking true in visited map.
    3. Loop through the neighbours of current source node.

        - **IF** current neighbour is not visited, mark it as visited and call function recursively for current neighbour and send parent as source node for current neighbour.
        - **ELSE** current neighbour is already visited, if the current neighbour is not the parent of current source node, it means cycle is present as current neighbour was already visited before by some other parent. return true.

    4. Once all recursive functions are called, return false as no cycle found.

---

<h3 id="28">Directed Graph Cycle Detection DFS</h3>

- Cycle Detection in DFS for Directed Graph is different from undirected graph.
- For 3 nodes A, B, C, undirected graph will form cycle no matter what if all three are connected as edge is bidirectional.
- But for directed graph, suppose A -> B and A -> C and B -> C, although all nodes are connected, it is unidirectional, as we can't come back to A from C so its not a valid cycle.
- To beat this, we use Recursive Call Stack.
- When we call DFS on a node, we basically go downwards till we find the end node similar to going down from root to leaf of a tree.
- Suppose A is the root and we go down to B, C and we again reached A while we had called DFS from A, it means we reached A again through a cycle.
- So in code, we will keep track of recursive calls and mark it false when we exit from the Recursive call for a specific node.

- **Algorithm**

    1. Function accepts 3 inputs, source node, visited map and dfsVisited map (track recursive calls in this)
    2. First we visit the source node by marking it as visited.
    3. Then we loop through all the neighbours of source node.
    4. For each neighbour, if it is not visited, we mark it visited in both visited and dfsVisited maps.
    5. Then we call dfs on that neighbour node and save it in variable.
    6. If the recursion ans of dfs is true it means cycle was found and we return true else we mark dfsVisited as false for current neighbour as we came out of dfs calls for it.
    7. If the neighbour was already visited, we check dfsVisited and if it is also true in dfsVisited, we return true as cycle is present when a node is present in both visited and dfsVisited.
    8. At the end we simply return false if cycle was not found.

---

<h3 id="29">Topological Sort DFS</h3>

- Topological Sort is a way of sorting graph nodes in a way such that the most independent node will come first.

- **Algorithm**

    1. Visit the source node.
    2. Visit all the neighbours of the source node.
    3. After all the neighbour nodes are visited, add the source node in Stack.
    4. This will store the sorted nodes in reverse order in stack for all nodes.

---

<h3 id="30">Topological Sort BFS</h3>

- **Algorithm**

    1. Create indegree map, which contains how many nodes are directed towards current node. *E.g. Suppose there are no nodes directed to A, it means A is independent node and it can be added first in our topological sorted ans.*
    2. Add all nodes with 0 indegree in a queue.
    3. Run BFS Logic, means while loop till queue is not empty.
    4. Pop out front node from queue, nodes in queue are independent so we add them in our answer.
    5. Traverse to all the neighbours of front node and decrement their indegree by 1 as we traversed the front node so that dependency can be removed.
    6. While decrementing indegrees of neighbours, if a neighbour's indegree becomes 0, add it to the queue or else ignore it.
    7. This will run till all nodes are traversed by removing their dependencies.

---

<h3 id="31">Shortest Path using BFS</h3>

- Shortest Path in BFS for non-weighted graph can be found out easily. From the path where we reach the destination node first, that path itself is the shortest path.

- **Algorithm**

    1. Initialize variables: path (storing shortest path), q (BFS Traversal), vis (keep track of visited nodes) & parent (to store parent of visiting node which later will be used to backtrack and get the path)
    2. Add source node in queue, mark parent as -1 and mark it visited.
    3. Start BFS till we find the destination node first.
    4. While BFS traversal mark every non-visited node as visited and set their parents correctly.
    5. Once we reach the destination node for the first time, we break out due to the rule we stated in explanation.

---

<h3 id="32">Shortest Path using DFS</h3>

- In DFS, we find the shortest path for weighted graph.
- We use topological sort to find the shortest distance from all nodes to the destination node.

- **Algorithm**
    1. Initialize distance vector of size n where n is no. of nodes.
    2. Use top element of stack we get from topological sort as source and set its distance as 0.
    3. Set distance of all neighbours of source node with respect to the source node in distance array.
    4. Run while loop to do the same for all nodes left in topological ordering.
    5. For all nodes, set the distance from current node to neighbour node but only if the distance in distance array is greater than the current distance we found.
    6. Once while loop is run to completion, we get the distance array and we will get the shortest distance from source to destination.

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