#include <iostream>
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


// 19. 


// 20.



int main() {

    

    return 0;
}