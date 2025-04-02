#include <iostream>
#include <algorithm>
using namespace std;

// AVL Tree node structure
struct Node {
    int key;
    Node *left;
    Node *right;
    int height;
    
    Node(int k) : key(k), left(nullptr), right(nullptr), height(1) {}
};

// Utility function to get height of a node
int height(Node *N) {
    return (N == nullptr) ? 0 : N->height;
}

// Utility function to get balance factor of node N
int getBalance(Node *N) {
    return (N == nullptr) ? 0 : height(N->left) - height(N->right);
}

// Right rotate subtree rooted with y
Node* rightRotate(Node *y) {
    Node *x = y->left;
    Node *T2 = x->right;
    
    // Perform rotation
    x->right = y;
    y->left = T2;
    
    // Update heights
    y->height = max(height(y->left), height(y->right)) + 1;
    x->height = max(height(x->left), height(x->right)) + 1;
    
    // Return new root
    return x;
}

// Left rotate subtree rooted with x
Node* leftRotate(Node *x) {
    Node *y = x->right;
    Node *T2 = y->left;
    
    // Perform rotation
    y->left = x;
    x->right = T2;
    
    // Update heights
    x->height = max(height(x->left), height(x->right)) + 1;
    y->height = max(height(y->left), height(y->right)) + 1;
    
    // Return new root
    return y;
}

// Insert a key into the subtree rooted with node and returns the new root
Node* insert(Node* node, int key) {
    // 1. Perform normal BST insertion
    if (node == nullptr)
        return new Node(key);
    
    if (key < node->key)
        node->left = insert(node->left, key);
    else if (key > node->key)
        node->right = insert(node->right, key);
    else  // Duplicate keys are not allowed in AVL tree
        return node;
    
    // 2. Update height of this ancestor node
    node->height = 1 + max(height(node->left), height(node->right));
    
    // 3. Get the balance factor to check whether this node became unbalanced
    int balance = getBalance(node);
    
    // If unbalanced, then there are 4 cases:
    
    // Left Left Case
    if (balance > 1 && key < node->left->key)
        return rightRotate(node);
    
    // Right Right Case
    if (balance < -1 && key > node->right->key)
        return leftRotate(node);
    
    // Left Right Case
    if (balance > 1 && key > node->left->key) {
        node->left = leftRotate(node->left);
        return rightRotate(node);
    }
    
    // Right Left Case
    if (balance < -1 && key < node->right->key) {
        node->right = rightRotate(node->right);
        return leftRotate(node);
    }
    
    // Return the (unchanged) node pointer
    return node;
}

// A utility function to print preorder traversal of the tree.
void preOrder(Node *root) {
    if(root != nullptr) {
        cout << root->key << " ";
        preOrder(root->left);
        preOrder(root->right);
    }
}

int main() {
    Node *root = nullptr;
    
    
    root = insert(root, 30);
    root = insert(root, 20);
    root = insert(root, 40);
    root = insert(root, 10);
    root = insert(root, 25);
    root = insert(root, 50);
    
    cout << "Preorder traversal of the constructed AVL tree is \n";
    preOrder(root);
    
    return 0;
}
