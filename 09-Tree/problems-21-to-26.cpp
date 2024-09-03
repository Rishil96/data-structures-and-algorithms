#include <iostream>
using namespace std;

struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode() : val(0), left(nullptr), right(nullptr) {}
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
    TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
};

struct Node
{
    int data;
    Node* left;
    Node* right;
};


// 21. Flatten Binary Tree to Linked List
void flatten(TreeNode* root) {
    // Use temp variable
    TreeNode* currentNode = root;
    // Loop to flatten tree
    while (currentNode) {
        // If curr node has a left node, find inorder predecessor and connect it to current's right node
        if (currentNode -> left) {
            // Get predecessor of current node
            TreeNode* predecessor = currentNode -> left;
            while (predecessor -> right) predecessor = predecessor -> right;

            // Connect predecessor's right to current node's right
            predecessor -> right = currentNode -> right;

            // Set current node's left to current node's right and then remove link from left
            currentNode -> right = currentNode -> left;
            currentNode -> left = NULL;
        }
        currentNode = currentNode -> right;
    }
}


// 22. Find maximum sum of non-adjacent values in tree
pair<int, int> gmsHelper(Node* root) {
    // Base Case
    if (!root) return {0, 0};
    
    // Recursive Case: Traverse the tree
    auto leftAns = gmsHelper(root -> left);
    auto rightAns = gmsHelper(root -> right);

    // Ek Case: Build both answers 
    /* 
        1. Include current node in answer (second of left and right ans is taken as they represent excluded answers)
        Here excluded answer must be taken as we are including current node value so children's node values should not be considered
    */
    int includesAns = root -> data + leftAns.second + rightAns.second;
    
    /*
        2. Exclude current node in answer
        Since we are not considering current node value, it doesn't matter if we consider including the children node value
        so we get the max answer from both left and right children and add them to current node answer irrespective of 
        children node being included or excluded
    */ 
    int excludesAns = max(leftAns.first, leftAns.second) + max(rightAns.first, rightAns.second);
    
    return {includesAns, excludesAns};
}

//Function to return the maximum sum of non-adjacent nodes.
int getMaxSum(Node *root) {   
    // Helper will return pair of int, where {includes current node, excludes current node} 
    auto ans = gmsHelper(root);
    return max(ans.first, ans.second);
}


// 23.


// 24.


// 25.


// 26.



int main() {

    

    return 0;
}