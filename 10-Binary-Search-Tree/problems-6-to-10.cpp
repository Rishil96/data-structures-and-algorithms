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


// 6. Kth smallest node of a BST
int kthSmallest(TreeNode* root, int &k) {
    // Base Case
    if (!root) return -1;

    // Ek Case: Inorder Traversal (as this traversal of BST returns nodes in sorted form)
    // Go left first
    int leftAns = kthSmallest(root -> left, k);
    // For current node reduce k and if k == 0 it means we are at kth smallest node
    k--;
    if (k == 0) return root -> val;
    // Go right
    int rightAns = kthSmallest(root -> right, k);

    return leftAns != -1 ? leftAns : rightAns;
}


// 7.


// 8.


// 9.


// 10.



int main() {

    

    return 0;
}