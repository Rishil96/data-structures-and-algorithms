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


// 14. Boundary Traversal of a Binary Tree
bool isLeaf(Node* root) {
    if(root->left==NULL && root->right==NULL)
        return true;
    return false;
}

void leftTraversal(Node* root, vector<int>& res) {
    Node* curr = root;
    while(curr != NULL) {
        if (!isLeaf(curr)) res.push_back(curr->data);
        
        if(curr->left)
            curr=curr->left;
        else
            curr=curr->right;
    }
    return;
}

void leafTraversal(Node* root, vector<int>& res) {
    if(root == NULL)
        return ;
    if(isLeaf(root)) res.push_back(root -> data);
    leafTraversal(root -> left, res);
    leafTraversal(root -> right, res);
}

void rightTraversal(Node* root,vector<int>& res) {
    if(root == NULL) return;
    vector<int> temp;
    while(root != NULL)
    {
        if (!isLeaf(root)) temp.push_back(root -> data);
        
        if(root -> right)
            root = root -> right;
        else
            root = root -> left;
    }
    reverse(temp.begin(),temp.end());
    for(auto x : temp)
    res.push_back(x);
}

vector <int> boundary(Node *root) {
    vector<int> res;
    if(!isLeaf(root)) res.push_back(root -> data);
    leftTraversal(root -> left, res);
    leafTraversal(root, res);
    rightTraversal(root -> right, res);
    return res;
}


// 15. Same Tree
bool isSameTree(TreeNode* p, TreeNode* q) {
    // Base Case: Return true when both are null
    if (!p && !q) return true;

    // Ek Case: If p val is not equal to q val or any one does not exist while the other exists return false
    if ((!p || !q) || (p -> val != q -> val)) return false;

    // Recursive Case: Check left and right subtree of p and q
    bool leftAns = isSameTree(p -> left, q -> left);
    bool rightAns = isSameTree(p -> right, q -> right);

    // Only return true if both subtrees are equal
    return leftAns && rightAns;
}



int main() {

    

    return 0;
}