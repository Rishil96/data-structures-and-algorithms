#include <iostream>
#include <vector>
#include <stack>
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

class BSTNodeInfo {
    public:
        int sum;
        bool isValid;
        int min;
        int max;

        BSTNodeInfo() {
            this -> sum = 0;
            this -> isValid = true;
            this -> min = INT_MAX;
            this -> max = INT_MIN; 
        }
};


// 21. Merge 2 BSTs
vector<int> merge(Node *root1, Node *root2) {
    vector<int> ans;
    
    stack<Node*> s1, s2;
    Node* a = root1;
    Node* b = root2;
    
    while (true) {
        // Inorder Traversal of root1's left
        while (a) {
            s1.push(a);
            a = a -> left;
        }
        // Inorder Traversal of root2's left
        while (b) {
            s2.push(b);
            b = b -> left;
        }
        
        // If both stacks are empty it means both traversal is complete
        if (s1.empty() && s2.empty()) break;
        
        // Get top nodes of both stacks
        Node* atop = (!s1.empty()) ? s1.top() : NULL;
        Node* btop = (!s2.empty()) ? s2.top() : NULL;
        
        // If s1 stack was empty, add top element of s2
        if (!atop) {
            ans.push_back(btop -> data);
            s2.pop();
            b = btop -> right;
        }
        // If s2 stack was empty, add top element of s1
        else if (!btop) {
            ans.push_back(atop -> data);
            s1.pop();
            a = atop -> right;
        }
        // If s1's top is less than equal to s2's top node, add s1 top in ans
        else if (atop -> data <= btop -> data) {
            ans.push_back(atop -> data);
            s1.pop();
            a = atop -> right;
        }
        // Else add s2's top in ans
        else if (btop -> data < atop -> data) {
            ans.push_back(btop -> data);
            s2.pop();
            b = btop -> right;
        }
    }
    
    return ans;
}


// 22. Maximum Sum BST in a Binary Tree
BSTNodeInfo* msHelper(TreeNode* root, int &maxSum) {
    // Base Case
    if (!root) return new BSTNodeInfo();

    // Recursive Case: Get left and right subtree answers
    BSTNodeInfo* leftSubTree = msHelper(root -> left, maxSum);
    BSTNodeInfo* rightSubTree = msHelper(root -> right, maxSum);

    // Ek Case
    BSTNodeInfo * currAns = new BSTNodeInfo();  

    // If left and right subtrees are both valid and using current node is also valid BST
    if (leftSubTree -> isValid && 
        rightSubTree -> isValid && 
        ((root -> val > leftSubTree -> max) && root -> val < rightSubTree -> min)) {
            // Current sum will be sum of left tree, right tree and current val
            currAns -> sum = leftSubTree -> sum + rightSubTree -> sum + root -> val;
            currAns -> isValid = true;
            // Min will be min value between current node and min of left tree
            currAns -> min = min(leftSubTree -> min, root -> val);
            // Max will be max value between current node and max of right tree
            currAns -> max = max(rightSubTree -> max, root -> val);
    }
    // Current BST is not valid
    else {
        // Push the larger sum between the left and right tree above
        currAns -> sum = max(leftSubTree -> sum, rightSubTree -> sum);
        // Mark BST as not valid
        currAns -> isValid = false;
        // Min and max will follow the same logic as in valid BST scenario
        currAns -> min = min(leftSubTree -> min, root -> val);
        currAns -> max = max(rightSubTree -> max, root -> val);
    }

    maxSum = max(currAns -> sum, maxSum);

    return currAns;
}

int maxSumBST(TreeNode* root) {
    int maxSum = 0;
    msHelper(root, maxSum);
    return maxSum;        
}



int main() {

    

    return 0;
}