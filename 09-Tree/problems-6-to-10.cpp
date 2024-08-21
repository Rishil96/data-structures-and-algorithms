#include <iostream>
using namespace std;


struct Node
{
	int data;
	struct Node *left, *right;
};


// 6. Kth ancestor of a node
bool kthAncestorHelper(Node* root, int node, int &k, int &ans) {
    // Base Case
    if (root == NULL) return false;
    if (root -> data == node) return true;
    
    // Ek Case
    // Search left and right of root node
    bool leftAns = kthAncestorHelper(root -> left, node, k, ans);
    bool rightAns = kthAncestorHelper(root -> right, node, k, ans);
    
    // If answer if found, decrement k to find ancestor
    if (leftAns || rightAns) {
        k--;
    }
    
    // If ancestor is found write it in ans variable
    if (k == 0) {
        ans = root -> data;
        k = -1;
    }

    return leftAns || rightAns;
}

int kthAncestor(Node *root, int k, int node)
{
    // Code here
    int ans = -1;
    bool op = kthAncestorHelper(root, node, k, ans);
    
    return ans;
}


// 7.
// 8.
// 9.
// 10.

int main() {

    

    return 0;
}