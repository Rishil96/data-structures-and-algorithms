#include <iostream>
#include <vector>
using namespace std;

struct Node {
    int data;
    Node * right, * left;
};

struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode() : val(0), left(nullptr), right(nullptr) {}
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
    TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
};


// 16. Check whether BST contains deadend
bool deHelper(Node* root, int lower, int upper) {
    // Base Case
    if (!root) return false;
    
    // Ek Case: If node is leaf node and its min and max boundary has only difference of 1 then it is a deadend
    if (!root -> left && !root -> right && lower + 1 == root -> data && upper - 1 == root -> data) {
        return true;
    } 
    
    // Baaki Recursion Sambhal lega
    bool leftAns = deHelper(root -> left, lower, root -> data);
    bool rightAns = deHelper(root -> right, root -> data, upper);
    
    return leftAns || rightAns;
}

bool isDeadEnd(Node *root) {
    return deHelper(root, 0, INT_MAX);
}


// 17. Count BST Nodes that lie in a given range
void gcHelper(Node* root, int &l, int &h, int &ans) {
    // Base Case
    if (!root) return ;
    
    // Ek Case: If current node is in range increase counter
    if (root -> data >= l && root -> data <= h) {
        ans++;
    }
    // If current node is greater than lower bound, search nodes in left
    if (root -> data > l) gcHelper(root -> left, l, h, ans);
    // If current node is lesser than upper bound, search nodes in right
    if (root -> data < h) gcHelper(root -> right, l, h, ans);
    
    return ;
}

int getCount(Node *root, int l, int h) {
    int ans = 0;
    gcHelper(root, l, h, ans);
    return ans;
}


// 18. Flatten Binary Tree into Linked List
void flatten(TreeNode* root) {
    // Use temp variable
    TreeNode* currNode = root;

    // Flatten till currNode is not NULL
    while (currNode) {
        // If currNode's left exists, then find inorder predecessor and connect it to right of currNode
        if (currNode -> left) {
            // Find predecessor node
            TreeNode* predNode = currNode -> left;
            while (predNode -> right) predNode = predNode -> right;
        
            // Connect predecessor node to right of current node
            predNode -> right = currNode -> right;

            // Move left of current node to its right
            currNode -> right = currNode -> left;

            // Point left of current node to null
            currNode -> left = NULL;
        }

        // Move currNode to its right child once
        currNode = currNode -> right;
    }
}


// 19. Replace every element with the least greater element on its right
void insertNode(struct Node* root, int &val, int &currSuccessor) {
    // Base Case
    if (!root) return ;
    
    // Ek Case
    // If current root is greater than val, it could be successor so mark it
    if (root -> data > val) {
        currSuccessor = root -> data;
        if (root -> left) insertNode(root -> left, val, currSuccessor);
        else {
            Node* newNode = new Node();
            newNode -> data = val;
            root -> left = newNode;
        }
    }
    // Else if current node is less than val, it cannot be successor
    else {
        if (root -> right) insertNode(root -> right, val, currSuccessor);
        else {
            Node* newNode = new Node();
            newNode -> data = val;
            root -> right = newNode;
        }
    }
}

vector<int> findLeastGreater(vector<int>& arr, int n) {
    // Answer array
    vector<int> ans(arr.size(), 0);
    // Create root node of last element in array and add answer as -1
    Node* root = new Node();
    root -> data = arr[n-1]; 
    ans[n-1] = -1;  // Because no nodes to the right of element at n-1
    
    /* 
    Loop through remaining elements from right to left and find inorder
    successor of each node as its the least greater element of current node
    */
    for (int i=n-2; i>=0; i--) {
        int currSuccessor = -1;
        insertNode(root, arr[i], currSuccessor);
        ans[i] = currSuccessor;
    }
    
    return ans;
}


// 20. Check if preorder traversal is a valid BST preorder
void build(int arr[], int &i, int &N, int &min, int &max) {
    // Base Case
    if (i >= N) return ;
    
    // Ek Case: Mimic building a BST using preorder traversal
    if (i < N && arr[i] > min && arr[i] < max) {
        int root = arr[i];
        i++;
        build(arr, i, N, min, root);
        build(arr, i, N, root, max);
    }
    
    return ;
}

int canRepresentBST(int arr[], int N) {
    // code here
    int min = INT_MIN;
    int max = INT_MAX;
    int i = 0;
    
    // If i goes beyond arr index it means whole BST was created using preorder so preorder is valid else not valid
    build(arr, i, N, min, max);
    
    return i >= N;
}



int main() {

    

    return 0;
}