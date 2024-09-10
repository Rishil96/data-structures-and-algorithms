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


// 9. Convert Binary Tree into sorted Doubly Linked List
void convertBSTintoSortedDLL(TreeNode* root, TreeNode* &head) {
    /*
        Basic idea is to convert the right subtree first then connect the right head with the current root like in a DLL
        Then update the head to be the current root for the left subtree
        Then convert the left subtree to DLL which will then use the current root as the head and connect all nodes recursively
    */
    // Base Case: In Case of no root do nothing
    if (!root) return ;

    // Ek Case: Build Linked List from the right subtree first
    convertBSTintoSortedDLL(root -> right, head);

    // Attach root to the right head and vice versa
    root -> right = head;
    if (head) head -> left = root;

    // Update head to the current root for our left subtree
    head = root;

    // Convert left subtree into Sorted DLL
    convertBSTintoSortedDLL(root -> left, head);
}


// 10. Convert Sorted Doubly Linked List into BST
TreeNode* convertSortedDLLintoBST(TreeNode* head, int n) {
    /*
        Here, using Recursion we are dividing the List into 3 parts, e.g. List has 8 nodes {1, 2, 3, 4, 5, 6, 7, 8}
        Left Subtree will have n - 1 - n / 2 = n/2 - 1 = 3 nodes in above e.g. i.e. 1 to 3
        Root will be the 4th node i.e. 4
        Right subtree will have n/2 nodes i.e 4 nodes which is 5 to 8
        After processing each head we move it to right
    */

    // Base Case
    if (n <= 0 || head == NULL) return NULL;

    // Ek Case
  
    // Get left subtree by reducing the size of DLL to just before center node
    TreeNode* leftSubtree = convertSortedDLLintoBST(head, n - 1 - n / 2);

    // Process root node
    TreeNode* root = head;
    root -> left = leftSubtree;

    // Move head right to process the next node
    head = head -> right;

    // Get right subtree
    TreeNode* rightSubtree = convertSortedDLLintoBST(head, n / 2);
    return root;
}


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