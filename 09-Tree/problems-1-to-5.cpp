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


// 4. 


// 5.



int main() {

    

    return 0;
}