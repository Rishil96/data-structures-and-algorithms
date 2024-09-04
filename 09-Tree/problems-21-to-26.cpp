#include <iostream>
#include <queue>
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

struct Node
{
    int data;
    Node* left;
    Node* right;
};


// 21. Flatten Binary Tree to Linked List
void flatten(TreeNode* root) {
    // Use temp variable
    TreeNode* currentNode = root;
    // Loop to flatten tree
    while (currentNode) {
        // If curr node has a left node, find inorder predecessor and connect it to current's right node
        if (currentNode -> left) {
            // Get predecessor of current node
            TreeNode* predecessor = currentNode -> left;
            while (predecessor -> right) predecessor = predecessor -> right;

            // Connect predecessor's right to current node's right
            predecessor -> right = currentNode -> right;

            // Set current node's left to current node's right and then remove link from left
            currentNode -> right = currentNode -> left;
            currentNode -> left = NULL;
        }
        currentNode = currentNode -> right;
    }
}


// 22. Find maximum sum of non-adjacent values in tree
pair<int, int> gmsHelper(Node* root) {
    // Base Case
    if (!root) return {0, 0};
    
    // Recursive Case: Traverse the tree
    auto leftAns = gmsHelper(root -> left);
    auto rightAns = gmsHelper(root -> right);

    // Ek Case: Build both answers 
    /* 
        1. Include current node in answer (second of left and right ans is taken as they represent excluded answers)
        Here excluded answer must be taken as we are including current node value so children's node values should not be considered
    */
    int includesAns = root -> data + leftAns.second + rightAns.second;
    
    /*
        2. Exclude current node in answer
        Since we are not considering current node value, it doesn't matter if we consider including the children node value
        so we get the max answer from both left and right children and add them to current node answer irrespective of 
        children node being included or excluded
    */ 
    int excludesAns = max(leftAns.first, leftAns.second) + max(rightAns.first, rightAns.second);
    
    return {includesAns, excludesAns};
}

//Function to return the maximum sum of non-adjacent nodes.
int getMaxSum(Node *root) {   
    // Helper will return pair of int, where {includes current node, excludes current node} 
    auto ans = gmsHelper(root);
    return max(ans.first, ans.second);
}


// 23. Sum of nodes on the longest path from root to leaf of a tree
//                                      depth, sum
pair<int, int> sopHelper(Node* root, pair<int, int> info) {
    // Base Case
    if (!root) return info;
    
    // Recursive Case: Get longest depth and its sum from left and right subtrees
    auto leftPath = sopHelper(root -> left, {info.first + 1, info.second + root -> data});
    auto rightPath = sopHelper(root -> right, {info.first + 1, info.second + root -> data});
    
    // If left path is longer then leftPath will be returned
    if (leftPath.first > rightPath.first) 
        return leftPath;
    // If left and right path are of equal length and leftSum is greater than leftPath will be considered
    else if (leftPath.first == rightPath.first && leftPath.second > rightPath.second)
        return leftPath;
    // Else right path will be considered
    else 
        return rightPath;
    
}    
        

int sumOfLongRootToLeafPath(Node *root) {
    //code here
    return sopHelper(root, {0, 0}).second;
}


// 24. Burning Tree
void buildParentMap(Node* cNode, Node* pNode, unordered_map<Node*, Node*> &parent, int &target, Node* &startNode) {
    // Base Case
    if (!cNode) return ;
    
    // Ek Case: Add parent entry of current node
    parent[cNode] = pNode;
    
    // Secondary Task: Find the starting node to burn the tree
    if (cNode -> data == target) startNode = cNode;
    
    // Recursive Case: Traverse rest of the tree
    buildParentMap(cNode -> left, cNode, parent, target, startNode);
    buildParentMap(cNode -> right, cNode, parent, target, startNode);
}

int minTime(Node* root, int target) {
    // Variable to hold starting node to burn the tree
    Node* startNode = NULL;
    
    // Get parents of each node in the tree
    unordered_map<Node*, Node*> parent;
    buildParentMap(root, NULL, parent, target, startNode);
    
    // Use a queue to burn the tree
    //      second, node burnt at second
    queue<pair<int, Node*>> q;
    int minSecond = 0;
    
    // Burn the start node at 0th second
    q.push({0, startNode});
    // Keep track of nodes that were burnt
    unordered_map<Node*, bool> isBurnt;
    
    // Burn the rest of the tree by spreading the fire on parent, left and right child
    while (!q.empty()) {
        // Remove burnt item out of the tree
        auto burntItem = q.front(); q.pop();
        int currSecond = burntItem.first;
        Node* currNode = burntItem.second;
        
        // Mark popped node as burnt
        isBurnt[currNode] = 1;
        // Update the latest seconds taken
        minSecond = currSecond;
        
        // Burn parent
        if (parent[currNode] && !isBurnt[parent[currNode]]) q.push({currSecond + 1, parent[currNode]});
        // Burn left and right children
        if (currNode -> left && !isBurnt[currNode -> left]) q.push({currSecond + 1, currNode -> left});
        if (currNode -> right && !isBurnt[currNode -> right]) q.push({currSecond + 1, currNode -> right});
    }
    
    return minSecond;
}


// 25.


// 26.



int main() {

    

    return 0;
}