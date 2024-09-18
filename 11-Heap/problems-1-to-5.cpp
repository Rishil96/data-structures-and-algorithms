#include <iostream>
#include <vector>
#include <queue>
using namespace std;

struct Node {
    int data;
    Node *left;
    Node *right;

    Node(int val) {
        data = val;
        left = right = NULL;
    }
};

struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode() : val(0), left(nullptr), right(nullptr) {}
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
    TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
};


// 1. Kth largest element in the array
int findKthLargest(vector<int>& nums, int k) {
    // Create a MinHeap
    priority_queue<int, vector<int>, greater<int>> minHeap;
    // Add first k elements in heap
    for (int i=0; i<k; i++) minHeap.push(nums[i]);

    // For every remaining item, if current element is greater than top of heap, remove top and add curr
    for (int i=k; i<nums.size(); i++) {
        if (nums[i] > minHeap.top()) {
            minHeap.pop();
            minHeap.push(nums[i]);
        }
    }
    
    // Running the above loop will contain k largest elements in minHeap which means the smallest of them will be at the top i.e. the kth largest
    return minHeap.top();
}


// 2. Kth smallest element in the array
int kthSmallest(vector<int> &arr, int k) {
    
    // Create a maxHeap
    priority_queue<int> maxHeap;
    
    // Add first k elements in heap
    for (int i=0; i<k; i++) maxHeap.push(arr[i]);
    
    /* 
    For every remaining elements, if current element is smaller than top
    remove top element and add current element
    */
    for (int i=k; i<arr.size(); i++) {
        if (arr[i] < maxHeap.top()) {
            maxHeap.pop();
            maxHeap.push(arr[i]);
        }
    }
    
    return maxHeap.top();
}


// 3. Check if Binary Tree is a valid heap
bool isCompleteTree(Node* root) {
    // Check tree is complete BST using level order traversal
    queue<Node*> q;
    q.push(root);
    bool nullFound = false;

    while (!q.empty()) {
        Node* front = q.front(); q.pop();
        
        // Mark null found if front node is null
        if (front == NULL) {
            nullFound = true;
        }
        else {
            /* 
            Below condition means if we are on a non-null node 
            but a NULL node was already found, it means the tree 
            is not a complete Binary Tree
            */
            if (nullFound) {
                return false;
            }
            q.push(front -> left);
            q.push(front -> right);
        }
    }

    return true;
}

bool heapProperty(Node* tree) {
    // Base Case: if current root is NULL or a leaf node, it is a valid heap
    if (tree == NULL) return true;
    if (tree -> left == NULL && tree -> right == NULL) return true;
    
    // Recursive Case: Check if both subtrees are valid heap
    bool left = isHeap(tree -> left);
    bool right = isHeap(tree -> right);
    
    if (!left || !right) return false;
    
    // If left or right child is greater than current node, return false
    if (tree -> left && tree -> data < tree -> left -> data) return false;
    if (tree -> right && tree -> data < tree -> right -> data) return false;
    
    return true;
}

bool isHeap(struct Node* tree) {
    return heapProperty(tree) && isCompleteTree(tree);
}


// 4. Is Binary Tree a Complete Binary Tree
bool isCompleteTree2(TreeNode* root) {
    
    // Level order traversal using queue
    queue<TreeNode*> q;
    q.push(root);
    // Variable to keep track if null found
    bool nullFound = false;

    while (!q.empty()) {
        TreeNode* frontNode = q.front(); q.pop();
        // If null node found then mark true
        if (!frontNode) {
            nullFound = true;
        }
        // Else not null node case
        else {
            // If a null node was already found before current node it means its not a complete tree, return false
            if (nullFound) return false;
            // Push both children in queue
            q.push(frontNode -> left);
            q.push(frontNode -> right);
        }
    }
    // If no valid nodes are found after a null node it means the tree is a complete BT
    return true;
}

// 5. 



int main() {

    

    return 0;
}