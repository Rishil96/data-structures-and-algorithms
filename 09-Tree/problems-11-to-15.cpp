#include <iostream>
#include <vector>
#include <queue>
#include <map>
using namespace std;


struct Node
{
    int data;
    struct Node* left;
    struct Node* right;
    
    Node(int x){
        data = x;
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


// 11. Left View of Binary Tree
vector<int> leftView(Node *root) {
   // Initialize variables
   queue<pair<int, Node*>> q;
   map<int, int> mp;
   vector<int> ans;
   
   q.push({0, root});
   
   // Level order traversal to get left view    
   while (!q.empty()) {
       auto front = q.front(); q.pop();
       int depth = front.first;
       Node* fNode = front.second;
       
       if (mp.find(depth) == mp.end()) mp[depth] = fNode -> data;
       
       if (fNode -> left) q.push({depth + 1, fNode -> left});
       if (fNode -> right) q.push({depth + 1, fNode -> right});
   }
   
   // Build ans from mp to array
   for (auto it: mp) {
       ans.push_back(it.second);
   }
   
   return ans;
}


// 12. Right View of Binary Tree
vector<int> rightSideView(TreeNode* root) {
        
    vector<int> ans;

    // Empty Tree Case
    if (!root) return ans;
    
    // Init data structures to store right view
    queue<pair<int, TreeNode*>> q;
    map<int, int> mp;

    q.push({0, root});

    // Level order traversal to find right view
    while (!q.empty()) {
        auto front = q.front(); q.pop();
        int depth = front.first;
        TreeNode* fNode = front.second;

        // Enter first value from the right found on current depth
        if (mp.find(depth) == mp.end()) mp[depth] = fNode -> val;

        // Add childrens from right to left
        if (fNode -> right) q.push({depth + 1, fNode -> right});
        if (fNode -> left) q.push({depth + 1, fNode -> left});
    }

    // Build answer
    for (auto it: mp) ans.push_back(it.second);

    return ans;
}


// 13. Diagonal View of Binary Tree
void diagonalHelper(Node* root, map<int, vector<int>>& mp, int diagonal) {
    // Base Case
    if (!root) return ;
    
    // Ek Case: Add current node to the diagonal
    mp[diagonal].push_back(root -> data);
    
    // Traverse using preorder traversal and change diagonal values for left
    diagonalHelper(root -> left, mp, diagonal + 1);
    diagonalHelper(root -> right, mp, diagonal);
}

vector<int> diagonal(Node *root)
{
   // your code here
   map<int, vector<int>> mp;
   vector<int> ans;
   
   // Recursive call
   diagonalHelper(root, mp, 0);
   
   // Build answer
   for (auto it: mp) {
       for (auto node: it.second) ans.push_back(node);
   }
   
   return ans;
}


// 14. 


// 15.



int main() {

    

    return 0;
}