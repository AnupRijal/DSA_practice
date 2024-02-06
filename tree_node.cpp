#include <iostream>
using namespace std;

// Definition of a tree node
struct TreeNode {
    int val;
    TreeNode* left;
    TreeNode* right;

    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
};

// Binary Search Tree class
class BST {
private:
    TreeNode* root;

    // Helper function for inserting a value into the BST
    TreeNode* insertHelper(TreeNode* node, int val) {
        if (node == nullptr) {
            return new TreeNode(val);
        }

        if (val < node->val) {
            node->left = insertHelper(node->left, val);
        } else if (val > node->val) {
            node->right = insertHelper(node->right, val);
        }

        return node;
    }

    // Helper function for inorder traversal
    void inorderHelper(TreeNode* node) {
        if (node == nullptr) return;

        inorderHelper(node->left);
        cout << node->val << " ";
        inorderHelper(node->right);
    }

    // Helper function for preorder traversal
    void preorderHelper(TreeNode* node) {
        if (node == nullptr) return;

        cout << node->val << " ";
        preorderHelper(node->left);
        preorderHelper(node->right);
    }

    // Helper function for postorder traversal
    void postorderHelper(TreeNode* node) {
        if (node == nullptr) return;

        postorderHelper(node->left);
        postorderHelper(node->right);
        cout << node->val << " ";
    }

    // Helper function to find the minimum value node in a subtree
    TreeNode* findMin(TreeNode* node) {
        while (node->left != nullptr) {
            node = node->left;
        }
        return node;
    }

    // Helper function to delete a node with a given value from the BST
    TreeNode* deleteNodeHelper(TreeNode* node, int val) {
        if (node == nullptr) return node;

        if (val < node->val) {
            node->left = deleteNodeHelper(node->left, val);
        } else if (val > node->val) {
            node->right = deleteNodeHelper(node->right, val);
        } else {
            // Node to be deleted found
            if (node->left == nullptr) {
                TreeNode* temp = node->right;
                delete node;
                return temp;
            } else if (node->right == nullptr) {
                TreeNode* temp = node->left;
                delete node;
                return temp;
            }

            // Node with two children: Get the inorder successor (smallest
            // in the right subtree)
            TreeNode* temp = findMin(node->right);

            // Copy the inorder successor's content to this node
            node->val = temp->val;

            // Delete the inorder successor
            node->right = deleteNodeHelper(node->right, temp->val);
        }
        return node;
    }

public:
    // Constructor
    BST() : root(nullptr) {}

    // Insertion operation
    void insert(int val) {
        root = insertHelper(root, val);
    }

    // Inorder traversal
    void inorderTraversal() {
        inorderHelper(root);
        cout << endl;
    }

    // Preorder traversal
    void preorderTraversal() {
        preorderHelper(root);
        cout << endl;
    }

    // Postorder traversal
    void postorderTraversal() {
        postorderHelper(root);
        cout << endl;
    }

    // Deletion operation
    void deleteNode(int val) {
        root = deleteNodeHelper(root, val);
    }
};

int main() {
    BST bst;

    // Insert some values
    bst.insert(50);
    bst.insert(30);
    bst.insert(20);
    bst.insert(40);
    bst.insert(70);
    bst.insert(60);
    bst.insert(80);

    // Print inorder traversal
    cout << "Inorder traversal: ";
    bst.inorderTraversal();

    // Print preorder traversal
    cout << "Preorder traversal: ";
    bst.preorderTraversal();

    // Print postorder traversal
    cout << "Postorder traversal: ";
    bst.postorderTraversal();

    // Delete node with value 30
    bst.deleteNode(30);

    // Print inorder traversal after deletion
    cout << "Inorder traversal after deletion: ";
    bst.inorderTraversal();

    return 0;
}
