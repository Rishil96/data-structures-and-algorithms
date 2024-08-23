#include <iostream>
#include <vector>
#include <unordered_map>
#include <map>
#include <queue>
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


// 7. Construct Binary Tree from Inorder and Preorder Traversal
TreeNode* btHelper(vector<int>& preorder, vector<int>& inorder, int &pi, int inStart, int inEnd, unordered_map<int, int> &mapping) {
    // Base Case
    if (pi >= preorder.size() || inStart > inEnd) return NULL;

    // Ek Case
    // Create current node
    TreeNode* root = new TreeNode(preorder[pi]);

    // Find current node in inorder array
    int inIndex = mapping[preorder[pi]];

    pi++;

    // Recursive call for left and right nodes
    root -> left = btHelper(preorder, inorder, pi, inStart, inIndex - 1, mapping);
    root -> right = btHelper(preorder, inorder, pi, inIndex + 1, inEnd, mapping);

    return root;
}

TreeNode* buildTree(vector<int>& preorder, vector<int>& inorder) {
    int preOrderIndex = 0;                      // Index to create nodes in tree using preorder
    // Start and end index for inorder array to check if current element is valid
    int inStart = 0;                            
    int inEnd = inorder.size() - 1;

    // Create mapping of each element to its index in inorder array to save time
    unordered_map<int, int> mapping;
    for (int i=0; i<preorder.size(); i++) {
        mapping[inorder[i]] = i;
    }

    return btHelper(preorder, inorder, preOrderIndex, inStart, inEnd, mapping);
}


// 8. Construct Binary Tree from Inorder and Postorder Traversal
TreeNode* btHelper(vector<int>& inorder, vector<int>& postorder, int &pi, int inStart, int inEnd, unordered_map<int, int> &mapping) {
    // Base Case
    if (pi < 0 || inStart > inEnd) return NULL;

    // Ek Case
    // Create current node
    TreeNode* root = new TreeNode(postorder[pi]);
    int inIndex = mapping[postorder[pi]];

    // Decrement index of postorder denoting one node being created
    pi--;

    // Build left and right subtrees of nodes
    root -> right = btHelper(inorder, postorder, pi, inIndex + 1, inEnd, mapping);
    root -> left = btHelper(inorder, postorder, pi, inStart, inIndex - 1, mapping);

    return root;
}

TreeNode* buildTree(vector<int>& inorder, vector<int>& postorder) {
    // Index variables to keep track of nodes created and the position of next node i.e. left or right
    int pi = postorder.size() - 1;
    int inStart = 0;
    int inEnd = inorder.size() - 1;

    // Mapping of elements to its position in inorder array
    unordered_map<int, int> mapping;
    for (int i=0; i<inorder.size(); i++) mapping[inorder[i]] = i;

    return btHelper(inorder, postorder, pi, inStart, inEnd, mapping);
}


// 9. Top View of Binary Tree
vector<int> topView(Node *root) {
    map<int, int> mp;
    queue<pair<int, Node*>> q;
    vector<int> ans;
    
    // Push root with horizontal level 0
    q.push({0, root});
    
    // Level order traversal to find top view
    while (!q.empty()) {
        // Get front node from queue and pop
        auto front = q.front(); q.pop();
        Node* fNode = front.second;
        int level = front.first;
        
        // Add to map
        if (mp.find(level) == mp.end()) 
            mp[level] = fNode -> data;
        
        // Add children nodes for next level
        if (fNode -> left) q.push({level - 1, fNode -> left});
        if (fNode -> right) q.push({level + 1, fNode -> right});
    }
    
    // Append top view from map to vector
    for (auto it: mp) ans.push_back(it.second);
    
    return ans;
}


// 10. Bottom View of Binary Tree
vector <int> bottomView(Node *root) {
    map<int, int> mp;
    queue<pair<int, Node*>> q;
    vector<int> ans;
    
    q.push({0, root});
    
    // Level order traversal for bottom view
    while (!q.empty()) {
        auto front = q.front(); q.pop();
        int level = front.first;
        Node* fNode = front.second;
        
        // Add to map
        mp[level] = fNode -> data;
        
        // Add children
        if (fNode -> left) q.push({level - 1, fNode -> left});
        if (fNode -> right) q.push({level + 1, fNode -> right});
    }
    
    // Append bottom view from map to vector
    for (auto it: mp) ans.push_back(it.second);
    
    return ans;
}



int main() {

    

    return 0;
}