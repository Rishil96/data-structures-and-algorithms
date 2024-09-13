#include <iostream>
#include <vector>
#include <limits.h>
#include <unordered_map>
using namespace std;

struct Node {
    int data;
    Node *left;
    Node *right;

    Node(int val) {
        data = val;
        left = right = NULL;
    }
};

struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode() : val(0), left(nullptr), right(nullptr) {}
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
    TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
};


// 11. Largest BST in a Binary Tree
vector<int> solve(Node * root)
{
    // Base Case
    if(root == NULL) return {INT_MAX , INT_MIN , 0};
    
    if(!root->left && !root->right) {
        // Set min and max as current value
        return {root->data , root->data , 1};
    }
    
    // Ek Case
    vector<int>left = solve(root->left);
    vector<int>right = solve(root->right);
    vector<int> ans(3);
    
    if(root->data > left[1] && root->data < right[0])
    {
        ans[0] = min(root->data , left[0]);         // First element contains min value
        ans[1] = max(root->data , right[1]);        // Second element contains max value
        ans[2] = left[2] + right[2] + 1;            // Third element contains count of valid BST nodes
        return ans;
    }
    
    ans[0] = INT_MIN;
    ans[1] = INT_MAX;
    ans[2] = max(left[2], right[2]);
    
    return ans;
}

int largestBst(Node *root) {
return solve(root)[2];
}


struct ValidBST {
    int size;
    bool isValid;
    int maxVal;
    int minVal;
};

ValidBST* lbHelper(Node* root) {
    // Base Case
    if (!root) {
        ValidBST* currAns = new ValidBST();
        currAns -> size = 0;
        currAns -> isValid = true;
        currAns -> maxVal = INT_MIN;
        currAns -> minVal = INT_MAX;
        return currAns;
    }

    // Recursive Case
    ValidBST* leftAns = lbHelper(root -> left);
    ValidBST* rightAns = lbHelper(root -> right);

    // Current Case
    ValidBST* currAns = new ValidBST();
    
    // Both left and right subtrees are valid BST and current root has value greater than max of left and lesser than min of right tree
    if (leftAns -> isValid && rightAns -> isValid && root -> data > leftAns -> maxVal && root -> data < rightAns -> minVal) {
        currAns -> size = 1 + leftAns -> size + rightAns -> size;       // Include current node in size of valid BST
        currAns -> isValid = true;                                      // True as including current root still is valid BST
        currAns -> maxVal = max(root -> data, rightAns -> maxVal);      // Push max value between current and right subtree
        currAns -> minVal = min(root -> data, leftAns -> minVal);       // Push min value between current and left subtree
    }
    // If including the current root is not a valid BST
    else {
        currAns -> size = max(leftAns -> size, rightAns -> size);       // Just push the max valid BST size upwards
        currAns -> isValid = false;                                     // False as its not a valid BST
        currAns -> maxVal = max(root -> data, rightAns -> maxVal);      // Push max value between current and right subtree
        currAns -> minVal = min(root -> data, leftAns -> minVal);       // Push min value between current and left subtree
    }
    
    return currAns;
}

int largestBst2(Node* root) {
    return lbHelper(root) -> size;
}


// 12. Construct Binary Search Tree from Preorder Traversal
TreeNode* bstFromPreorderItr(vector<int>& preorder) {
    // Create root node using 1st node of preorder
    TreeNode* root = new TreeNode(preorder[0]);

    // Add remaining nodes in BST as per BST condition
    for (int i=1; i<preorder.size(); i++) {
        TreeNode* temp = root;
        TreeNode* newNode = new TreeNode(preorder[i]);

        while (temp) {
            if (newNode -> val < temp -> val) {
                if (!temp -> left) {
                    temp -> left = newNode;
                    break;
                }
                else temp = temp -> left;
            }
            else {
                if (!temp -> right) {
                    temp -> right = newNode;
                    break;
                }
                else temp = temp -> right;
            }
        }
    }
    return root;
}

TreeNode* bstHelper(vector<int>& preorder, int &preIndex, int &minBoundary, int &maxBoundary) {
    // Base Case
    if (preIndex >= preorder.size()) return NULL;

    // Ek Case: Create current node if current value fits in the min and max boundary
    TreeNode* root = NULL;
    int currVal = preorder[preIndex];
    
    // Baaki Recursion Sambhaal lega
    if (minBoundary < currVal && currVal < maxBoundary) {
        root = new TreeNode(currVal);
        preIndex++;
        root -> left = bstHelper(preorder, preIndex, minBoundary, currVal);
        root -> right = bstHelper(preorder, preIndex, currVal, maxBoundary);
    }

    return root;
}

TreeNode* bstFromPreorderRec(vector<int>& preorder) {
    int minBoundary = INT_MIN;
    int maxBoundary = INT_MAX;
    int preIndex = 0;

    return bstHelper(preorder, preIndex, minBoundary, maxBoundary);
}


// 13. Brothers from different roots
void traverse(Node* root, unordered_map<int, int> &mp, bool mode, int &ans, int &x) {
    // Base Case
    if (!root) return ;
    // Ek Case
    // If mode is true, means we are mapping root1 nodes
    if (mode) {
        mp[root -> data]++;
    }
    /* If mode is false, means we are searching for pair 
    of int for root2 if it exists in root1 such that their sum is x*/
    else {
        if (mp[x - root -> data] >= 1) ans++;
    }
    traverse(root -> left, mp, mode, ans, x);
    traverse(root -> right, mp, mode, ans, x);
}

int countPairs(Node* root1, Node* root2, int x)
{
    int ans = 0;
    unordered_map<int, int> treeMp;
    traverse(root1, treeMp, true, ans, x);
    traverse(root2, treeMp, false, ans, x);
    return ans;
}


// 14. Convert BST into Balanced BST
void getInorder(TreeNode* root, vector<int>& inorder) {
    if (!root) return ;
    getInorder(root -> left, inorder);
    inorder.push_back(root -> val);
    getInorder(root -> right, inorder);
}

TreeNode* balancedBSTHelper(vector<int>& inorder, int &i, int n) {
    /*
        i => index of current root
        n => no. of nodes in tree
    */
    // Base Case
    if (i >= inorder.size() || n <= 0) return NULL;
    // Ek Case
    // Build left subtree
    TreeNode* leftSubtree = balancedBSTHelper(inorder, i, n/2);
    // Build root node
    TreeNode* root = new TreeNode(inorder[i++]);
    root -> left = leftSubtree;
    // Build right subtree
    root -> right = balancedBSTHelper(inorder, i, n - n/2 - 1);

    return root; 
}

TreeNode* balanceBST(TreeNode* root) {
    // 1. Get inorder traversal of BST
    vector<int> inorder;
    getInorder(root, inorder);

    // 2. Reconstruct BST using inorder
    int i = 0;
    int n = inorder.size();
    return balancedBSTHelper(inorder, i, n);
}


// 15. Median of a BST
void traverse(struct Node *root, vector<int> &inorder) {
    // Base Case
    if (!root) return ;
    // Ek Case
    traverse(root -> left, inorder);
    inorder.push_back(root -> data);
    traverse(root -> right, inorder);
}

float findMedian(struct Node *root) {
    vector<int> inorder;
    traverse(root, inorder);
    
    float ans;
    int size = inorder.size() - 1;
    if (size + 1 & 1) {
        ans = inorder[size/2];
    }
    else {
        ans = (float(inorder[size/2]) + float(inorder[size/2 + 1])) / 2;
    }
    
    return ans;
}


int main() {

    

    return 0;
}