#include <iostream>
#include <vector>
#include <queue>
using namespace std;

class BSTNode
{
    public:
    int val;
    BSTNode* left;
    BSTNode* right;
    BSTNode(int _val): val(_val), left(NULL), right(NULL) {}
};


class BST 
{
    public:
    BSTNode* root;
    BST(int val) {
        root = new BSTNode(val);
    }
    BST() {
        root = NULL;
    }

    void insertNode(int val) {
        // 1. Create new node
        BSTNode* newNode = new BSTNode(val);

        // 2. Empty BST Case
        if (!root) {
            root = newNode;
            return ;
        }

        // 3. Normal Case
        BSTNode* temp = root;
        while (temp) {
            if (newNode -> val < temp -> val) {
                if (temp -> left) temp = temp -> left;
                else {
                    temp -> left = newNode;
                    return ;
                }
            }
            else {
                if (temp -> right) temp = temp -> right;
                else {
                    temp -> right = newNode;
                    return ;
                }
            }
        }
    }

};

void inorder(BSTNode* root) {
    if (!root) return ;
    inorder(root -> left);
    cout << root -> val << " ";
    inorder(root -> right);
}

// Inorder
void preorder(BSTNode* root) {
    if (!root) return ;
    cout << root -> val << " ";
    preorder(root -> left);
    preorder(root -> right);
}

// Postorder
void postorder(BSTNode* root) {
    if (!root) return ;
    postorder(root -> left);
    postorder(root -> right);
    cout << root -> val << " ";
}

// Levelorder
void levelorder(BSTNode* root) {
    // Source ko queue me daal 
    queue<BSTNode*> q;
    q.push(root);

    while (!q.empty()) {
        // Traverse current element
        BSTNode* front = q.front(); q.pop();
        cout << front -> val << " ";

        // Add children in queue
        if (front -> left) q.push(front -> left);
        if (front -> right) q.push(front -> right);
    }
}


// Delete node from BST
BSTNode* deleteNode(BSTNode* &root, int key) {
    // Base Case
    if (!root) return NULL;

    // Ek Case
    if (root -> val == key) {
        // 1. Leaf Node 
        if (root -> left == NULL && root -> right == NULL) {
            delete root;
            return NULL;
        }
        // 2. Only left subtree
        else if (root -> left && root -> right == NULL) {
            BSTNode* child = root -> left;
            delete root;
            return child;
        }
        // 3. Only right subtree
        else if (root -> right && root -> left == NULL) {
            BSTNode* child = root -> right;
            delete root;
            return child;
        }
        // 4. Both subtree
        else {
            // Find Inorder Predecessor
            BSTNode* pred = root -> left;
            while (pred -> right) pred = pred -> right;
            root -> val = pred -> val;
            root -> left = deleteNode(root -> left, pred -> val);
        }
    }
    // Baaki Recursion 
    else if (key < root -> val) {
        root -> left = deleteNode(root -> left, key);
    }
    else {
        root -> right = deleteNode(root -> right, key);
    }

    return root;
}

int main() {

    BST* bst = new BST();

    bst -> insertNode(50);
    bst -> insertNode(10);
    bst -> insertNode(90);
    bst -> insertNode(40);
    bst -> insertNode(60);
    bst -> insertNode(30);
    bst -> insertNode(70);
    bst -> insertNode(20);
    bst -> insertNode(80);


    cout << "Preorder: ";
    preorder(bst -> root);
    cout << endl;

    cout << "Inorder: ";
    inorder(bst -> root);
    cout << endl;

    cout << "Postorder: ";
    postorder(bst -> root);
    cout << endl;

    cout << "Levelorder: ";
    levelorder(bst -> root);
    cout << endl;

    bst -> root = deleteNode(bst -> root, 50);
    bst -> root = deleteNode(bst -> root, 20);

    cout << "**********";
    cout << "\nPreorder: ";
    preorder(bst -> root);
    cout << endl;

    cout << "Inorder: ";
    inorder(bst -> root);
    cout << endl;

    cout << "Postorder: ";
    postorder(bst -> root);
    cout << endl;

    cout << "Levelorder: ";
    levelorder(bst -> root);
    cout << endl;

    return 0;
}