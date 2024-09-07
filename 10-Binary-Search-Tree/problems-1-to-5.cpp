#include <iostream>
#include <stack>
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
	int key;
	struct Node *left;
	struct Node *right;
	
	Node(int x){
	    key = x;
	    left = NULL;
	    right = NULL;
	}
};

// 1. Search in a BST
TreeNode* searchBST(TreeNode* root, int val) {
    // Base Case
    if (!root) return NULL;

    // Ek Case
    if (root -> val == val) return root;

    // Recursive Case
    if (root -> val > val) return searchBST(root -> left, val);
    else return searchBST(root -> right, val);
}


// 2. Inorder Predecessor
void predecessor(Node* root, Node*& pre, int k){
    while (root) {
        // If condition will try to traverse on the left side of key node
        if (root -> key >= k) root = root -> left;
        // Once we are on the left side, mark each node as pre and move as much right as possible
        else{
            pre = root;
            root = root -> right;
        }
    }
}


// 3. Inorder Successor
void successor(Node* root, Node*&suc, int k){
    while (root) {
        // If condition will try to traverse on the right side of the key node
        if (root -> key <= k) root = root -> right;
        // Once we are on the right side, makr each node as suc and move as much left as possible
        else {
            suc = root;
            root = root -> left;
        }
    }
}

void findPreSuc(Node* root, Node*& pre, Node*& suc, int key){
    predecessor(root, pre, key);
    successor(root, suc, key);
}


// 4. Validate BST
bool ivbHelper(TreeNode* root, long lb, long rb) {
    // Base Case
    if (!root) return true;

    // Ek Case: If current root is out of current range then return false
    if (root -> val <= lb || root -> val >= rb) return false;
    // Recursive Case:
    // Set (lb, root -> val) for nodes to the left of root
    // Set (root -> val, rb) for nodes to the right of root
    return ivbHelper(root -> left, lb, root -> val) && ivbHelper(root -> right, root -> val, rb);
}

bool isValidBST(TreeNode* root) {
    return ivbHelper(root,  -2147483649, 2147483648);
}


// 5. Lowest Common Ancestor of BST
TreeNode* lcaHelper(TreeNode* root, TreeNode* &p, TreeNode*& q) {
    // Base Case
    if (!root) return NULL;

    // Ek Case
    // If current root is either p or q return root
    if (root == p || root == q) return root;
    else {
        // If both p and q values are less than current root value then search left
        if (p -> val < root -> val && q -> val < root -> val) return lcaHelper(root -> left, p , q);
        // If both p and q values are greater than current root value then search right
        else if (p -> val > root -> val && q -> val > root -> val) return lcaHelper(root -> right, p, q);
        // If p and q exists on different sides of current root then return root
        else return root;
    }

}

TreeNode* lowestCommonAncestor(TreeNode* root, TreeNode* p, TreeNode* q) {
    return lcaHelper(root, p, q);
}



int main() {

    Node* root = new Node(10);

    root -> left = new Node(2);
    root -> right = new Node(11);
    
    root -> left -> left = new Node(1);
    root -> left -> right = new Node(5);

    root -> left -> right -> left = new Node(3);
    root -> left -> right -> right = new Node(6);

    root -> left -> right -> left -> right = new Node(4);

    Node* pre, *suc;

    findPreSuc(root, pre, suc, 11);

    return 0;
}