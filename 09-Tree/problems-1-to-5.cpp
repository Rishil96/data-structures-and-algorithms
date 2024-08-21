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
    Node* left, * right;
};


// 1. Depth of a tree
int maxDepth(TreeNode* root) {
    // Base Case
    if (!root) return 0;

    // Base Case
    int leftTree = 1 + maxDepth(root -> left);
    int rightTree = 1 + maxDepth(root -> right);

    return max(leftTree, rightTree);
}


// 2. Diameter of Binary Tree
int dobtHelper(TreeNode* root, int &diameter) {
    // Base Case: root node is NULL
    if (!root) return 0;

    // EK Case
    // Calculate height of left and right subtree 
    int leftST = dobtHelper(root -> left, diameter);
    int rightST = dobtHelper(root -> right, diameter);

    // Diameter of current node is the sum of depths of its left and right subtree, update max diameter
    diameter = max(diameter, leftST + rightST);

    // Return depth of current node
    return max(leftST, rightST) + 1;
}

int diameterOfBinaryTree(TreeNode* root) {
    // Store max diameter found while traversing the tree to get depth
    int diameter = 0;
    // Function call to calculate the height of tree
    dobtHelper(root, diameter);
    return diameter;
}


// 3. Balanced Binary Tree
int ibHelper(TreeNode* root, bool &b) {
    // Base Case
    if (!root) return 0;

    // Ek Case
    if (b) {
        // Get heights of left and right subtree
        int lt = 1 + ibHelper(root -> left, b);
        int rt = 1 + ibHelper(root -> right, b);
        // If difference between height of left and right subtree is > 1 it is not balanced
        if (abs(lt - rt) > 1) b = false;
        return max(lt, rt);
    }

    return 0;
}

bool isBalanced(TreeNode* root) {
    bool b = true;
    ibHelper(root, b);
    return b;
}


// 4. Convert to sum tree
int tstHelper(Node* &node) {
    // Base Case
    // return 0 in case of not a valid node
    if (!node) return 0;
    // for leaf node, set the node val to 0 and return the actual node val
    if (!node -> left && !node -> right) {
        int nodeVal = node -> data;
        node -> data = 0;
        return nodeVal;
    }
    
    // Ek Case
    // Get sum of left and right subtrees
    int lstSum = tstHelper(node -> left);
    int rstSum = tstHelper(node -> right);
    
    // Save current node value, update curr node value to sum of lst and rst
    // and return the total of (lst, rst, current node val) to parent node
    int currVal = node -> data;
    node -> data = lstSum + rstSum;
    return lstSum + rstSum + currVal;
}

// Convert a given tree to a tree where every node contains sum of values of
// nodes in left and right subtrees in the original tree
void toSumTree(Node *node)
{
    // Your code here
    tstHelper(node);
}


// 5. Lowest Common Ancestor of a Binary Tree
TreeNode* lcaHelper(TreeNode* root, TreeNode* &p, TreeNode* &q) {
    // Base Case
    if (!root) return NULL;

    // Ek Case
    // If current node is either p or q, return the current node
    if (root == p || root == q) return root;
    // Else process
    else {
        // Find p and q from left and right subtrees
        TreeNode* lst = lcaHelper(root -> left, p, q);
        TreeNode* rst = lcaHelper(root -> right, p, q);
        // If right subtree reached NULL, it means p and q is on left subtree of current root
        if (!rst) return lst;
        // If left subtree reached NULL, it means p and q is on right subtree of current root
        else if (!lst) return rst;
        // If both are not NULL, it means we find p and q on both subtrees each
        return root;
    }
}

TreeNode* lowestCommonAncestor(TreeNode* root, TreeNode* p, TreeNode* q) {
    return lcaHelper(root, p, q);
}



int main() {

    

    return 0;
}