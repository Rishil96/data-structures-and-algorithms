#include <iostream>
#include <vector>
using namespace std;

class TreeNode
{
    public:
    int val;
    TreeNode *left, *right;
    TreeNode(int _val) : val(_val), left(NULL), right(NULL) {}
};


// Morris Traversal
vector<int> morrisTraversal(TreeNode* root) {
    vector<int> ans;
    TreeNode* curr = root;

    while (curr) {
        // If left node is NULL, visit current node and go right
        if (curr -> left == NULL) {
            ans.push_back(curr -> val);
            curr = curr -> right;
        }   
        else {
            // Find inorder predecessor
            TreeNode* pred = curr -> left;
            while (pred -> right != curr && pred -> right) {
                pred = pred -> right;
            }

            // If right of predecessor is Null establish a connection
            if (pred -> right == NULL) {
                pred -> right = curr;
                curr = curr -> left;
            }
            // Left is already visited, go right after visiting current node and removing link
            else {
                pred -> right = NULL;
                ans.push_back(curr -> val);
                curr = curr -> right;
            }
        }
    }

    return ans;
}

int main() {

    

    return 0;
}