#include <iostream>
#include <vector>
#include <unordered_map>
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


// 7. Construct Special BST using Inorder
void inOrderTraversal(TreeNode* root) {
    if (!root) return ;
    inOrderTraversal(root -> left);
    cout << root -> val << " ";
    inOrderTraversal(root -> right);
}

void preOrderTraversal(TreeNode* root) {
    if (!root) return ;
    cout << root -> val << " ";
    preOrderTraversal(root -> left);
    preOrderTraversal(root -> right);
}

int getMaxIndex(vector<int>& inorder, int &leftIndex, int &rightIndex) {
    int index = 0;
    for (int i=leftIndex; i<=rightIndex; i++) {
        index = inorder[i] > inorder[index] ? i : index;
    } 
    return index;
}

TreeNode* bstHelper(vector<int>& inorder, int leftIndex, int rightIndex) {
    // Base Case
    if (leftIndex > rightIndex) return NULL;
    
    // Ek Case
    int maxIndex = getMaxIndex(inorder, leftIndex, rightIndex);
    TreeNode* root = new TreeNode(inorder[maxIndex]);

    root -> left = bstHelper(inorder, leftIndex, maxIndex - 1);
    root -> right = bstHelper(inorder, maxIndex + 1, rightIndex);

    return root;
}

TreeNode* constructBST(vector<int> inorder) {
    return bstHelper(inorder, 0, inorder.size()-1);
}


// 8. Two Sum in BST
bool ftHelper(TreeNode* root, int &k, unordered_map<int, bool> &mp) {
    // Base Case
    if (!root) return false;

    // Ek Case: Add every node value in mp
    if (mp[k - root -> val]) return true;
    mp[root -> val] = 1;

    // Recursive Case: Traverse the tree
    bool left = ftHelper(root -> left, k, mp);
    bool right = ftHelper(root -> right, k, mp);

    return left || right; 
}

bool findTarget(TreeNode* root, int k) {
    unordered_map<int, bool> mp;
    return ftHelper(root, k, mp);
}


// 9. 


// 10.



int main() {

    vector<int> inorder{5, 10, 40, 30, 28};
    
    TreeNode* root = constructBST(inorder);
    
    cout << "Inorder Traversal: ";
    inOrderTraversal(root);
    cout << endl;

    cout << "Preorder Traversal: ";
    preOrderTraversal(root);
    cout << endl;

    return 0;
}