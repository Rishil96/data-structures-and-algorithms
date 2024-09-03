#include <iostream>
#include <vector>
#include <queue>
#include <map>
using namespace std;

struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode() : val(0), left(nullptr), right(nullptr) {}
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
    TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
};



// 16. Symmetric Tree
bool symHelper(TreeNode* p, TreeNode* q) {
    // Base Case: Returns true if both nodes are null
    if (!p && !q) return true;

    // Ek Case: Return false if any one of the node doesn't exist or they don't have equal values
    if ((!p || !q) || (p -> val != q -> val)) return false;

    // Recursive Case: Check in mirroring directions
    bool leftAns = symHelper(p -> left, q -> right);
    bool rightAns = symHelper(p -> right, q -> left);

    return leftAns && rightAns;
}

bool isSymmetric(TreeNode* root) {
    return symHelper(root -> left, root -> right);
}


// 17. Invert Binary Tree
TreeNode* invertTree(TreeNode* &root) {
    // Base Case: Return NULL if not a valid node
    if (!root) return NULL;

    // Ek Case: Traverse to the left and right subtrees
    TreeNode* leftTree = invertTree(root -> left);
    TreeNode* rightTree = invertTree(root -> right);

    // Update right subtree to the left of root
    root -> left = rightTree;
    // Update left subtree to the right of root
    root -> right = leftTree;

    // Return root
    return root;
}


// 18. ZigZag Level Order Traversal
vector<vector<int>> zigzagLevelOrder(TreeNode* root) {

    vector<vector<int>> ans;        // Answer container
    if (!root) return ans;          // Edge case of empty tree
    queue<TreeNode*> q;             // Queue for Level Order Traversal
    q.push(root);                   // Add root in queue
    bool flag = true;               // Flag that directs left to right or vice versa in a level

    while (!q.empty()) {
        // Vector to store current level
        int currSize = q.size();
        vector<int> temp(currSize);

        // Add all elements of current level from left to right in temp
        if (flag) {
            for (int i=0; i<currSize; i++) {
                TreeNode* fNode = q.front(); q.pop();
                temp[i] = fNode -> val;

                if (fNode -> left) q.push(fNode -> left);
                if (fNode -> right) q.push(fNode -> right);
            }
        }
        // Add all elements of current level from right to left in temp
        else {
            for (int i=currSize - 1; i>=0; i--) {
                TreeNode* fNode = q.front(); q.pop();
                temp[i] = fNode -> val;

                if (fNode -> left) q.push(fNode -> left);
                if (fNode -> right) q.push(fNode -> right);
            }
        }

        // Switch flag direction and push current level answer in ans container
        flag = !flag;
        ans.push_back(temp);
    }

    return ans;
}


// 19. Vertical Order Traversal
static bool cmp(pair<int, int> &a, pair<int, int> &b) {
    // If both elements are on the same row then smaller one should be kept first in Vertical order traversal
    if (a.first == b.first) return a.second < b.second;
    // If both elements are on different rows then smaller row element will come first in VOT
    else return a.first < b.first;
}

void pot(TreeNode* root, int row, int col, map<int, vector<pair<int, int>>> &mp) {
    // Base Case
    if (!root) return ;

    // Ek Case
    // Push node and its row, col details in map
    mp[col].push_back({row, root -> val});

    // Baaki Recursion: Preorder traversal
    pot(root -> left, row + 1, col - 1, mp);
    pot(root -> right, row + 1, col + 1, mp);
}

vector<vector<int>> verticalTraversal(TreeNode* root) {
    //  col              row  val
    map<int, vector<pair<int, int>>> mp;
    pot(root, 0, 0, mp);            // Preorder traversal to add all nodes in map as per col and row
    vector<vector<int>> ans;

    // Loop through the map
    for (auto nodeItem : mp) {
        int col = nodeItem.first;                               // Column of current node list
        vector<pair<int, int>> nodes = nodeItem.second;         // Node array of {row, node Value}
        sort(nodes.begin(), nodes.end(), cmp);                  // Sort nodes

        // Add all node values to separate array to store it in final answer
        vector<int> currColNodes;
        for (int i=0; i<nodes.size(); i++) currColNodes.push_back(nodes[i].second);

        ans.push_back(currColNodes);
    }

    return ans;
}


// 20. K Sum Paths
int paths = 0;

void psHelper(TreeNode* root, long long targetSum, int &paths) {
    // Base Case
    if (!root) return ;

    // Ek Case: Check if subtracting current node value gets us the targetSum and update ans accordingly
    if (targetSum - root -> val == 0) paths++;

    // Left and Right traversal after subtracting current node value from targetSum
    psHelper(root -> left, targetSum - root -> val, paths);
    psHelper(root -> right, targetSum - root -> val, paths);

    return ;
}

int pathSum(TreeNode* root, int targetSum) {
    /*
    We need 3 recursive calls
        1. Find path starting from current node
        2. Recursive call to do the same starting from left child
        3. Recursive call to do the same starting from right child
    */
    // Find paths from current node
    psHelper(root, targetSum, paths);
    // Start fresh paths from both children and consider tham roots
    if (root) {
        pathSum(root -> left, targetSum);
        pathSum(root -> right, targetSum);
    }

    return paths;
}



int main() {

    

    return 0;
}