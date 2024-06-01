#include <iostream>
#include <queue>
using namespace std;

class TreeNode
{
    public:
    int val;
    TreeNode *left, *right;
    TreeNode(int _val) : val(_val), left(NULL), right(NULL) {}
};


TreeNode* buildTree() {
    int data;
    cout << "Enter value for current root: ";
    cin >> data;
    // Base Case
    if (data == -1) return NULL;

    // Ek Case
    TreeNode* root = new TreeNode(data);

    // Baaki Recursion
    cout << "\nGoing left of " << data << " node" << endl;
    root -> left = buildTree();

    cout << "\nGoing right of " << data << " node" << endl;
    root -> right = buildTree();

    return root;
}

// Preorder
void inorder(TreeNode* root) {
    if (!root) return ;
    inorder(root -> left);
    cout << root -> val << " ";
    inorder(root -> right);
}

// Inorder
void preorder(TreeNode* root) {
    if (!root) return ;
    cout << root -> val << " ";
    preorder(root -> left);
    preorder(root -> right);
}

// Postorder
void postorder(TreeNode* root) {
    if (!root) return ;
    postorder(root -> left);
    postorder(root -> right);
    cout << root -> val << " ";
}

// Levelorder
void levelorder(TreeNode* root) {
    // Source ko queue me daal 
    queue<TreeNode*> q;
    q.push(root);

    while (!q.empty()) {
        // Traverse current element
        TreeNode* front = q.front(); q.pop();
        cout << front -> val << " ";

        // Add children in queue
        if (front -> left) q.push(front -> left);
        if (front -> right) q.push(front -> right);
    }
}
 

int main() {

    TreeNode* root = buildTree();

    cout << "Preorder: ";
    preorder(root);
    cout << endl;

    cout << "Inorder: ";
    inorder(root);
    cout << endl;

    cout << "Postorder: ";
    postorder(root);
    cout << endl;

    cout << "Levelorder: ";
    levelorder(root);
    cout << endl;

    return 0;
}