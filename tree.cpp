#include <iostream>
#include <string>
using namespace std;

template <class DS>
class BST {
private:
    struct Node {
        DS data;
        Node* left;
        Node* right;

        Node(const string& val) {
            data = val;
            left = right = nullptr;
        }
    };

    Node* root;

    Node* insert(Node* node, const string& data) {
        // If the tree is empty, return a new node
        if (node == nullptr) {
            return new Node(data);
        }

        // Otherwise, recur down the tree
        if (data < node->data) {
            node->left = insert(node->left, data);
        } else if (data > node->data) {
            node->right = insert(node->right, data);
        }

        // Return the (unchanged) node pointer
        return node;
    }

    bool search(Node* node, const string& data) {
        // Base case: root is null or key is present at root
        if (node == nullptr) {
            return false;
        }
        if (node->data == data) {
            return true;
        }

        // Key is greater than root's key
        if (node->data < data) {
            return search(node->right, data);
        }

        // Key is smaller than root's key
        return search(node->left, data);
    }

    void inorder(Node* node) {
        if (node != nullptr) {
            inorder(node->left);
            cout << node->data << " ";
            inorder(node->right);
        }
    }

public:
    BST() {
        root = nullptr;
    }

    void insert(const string& data) {
        root = insert(root, data);
    }

    bool search(const string& data) {
        return search(root, data);
    }

    void inorder() {
        inorder(root);
        cout << endl;
    }
};

int main() {
    BST <string> tree;
    tree.insert("kushal");
    tree.insert("danush");
    tree.insert("Charlie");
    tree.insert("Sudarshan");
    tree.insert("Kushal ");
    tree.insert("Frank");
    tree.insert("jam");

    cout << "Inorder traversal of the given tree: ";
    tree.inorder();

    string key = "jam";
    if (tree.search(key)) {
        cout << "Element " << key << " found in the BST." << endl;
    } else {
        cout << "Element " << key << " not found in the BST." << endl;
    }

    return 0;
}