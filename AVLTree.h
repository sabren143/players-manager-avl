#ifndef AVLTree_h
#define AVLTree_h

#include <cstdlib>
#include <cstdio>
#include <iostream>

using namespace std;

/**
 * Node<T> - A single node in the AVL Tree
 */
template <class T>
class Node {
public:
    T* data;
    int height;
    Node<T>* parent;
    Node<T>* right;
    Node<T>* left;

    explicit Node(T* data, int height = 0, Node<T>* parent = nullptr, Node<T>* right = nullptr, Node<T>* left = nullptr)
        : data(data), height(height), parent(parent), right(right), left(left) {}

    int getBalance() const {
        int left_height = left ? left->height : 0;
        int right_height = right ? right->height : 0;
        return left_height - right_height;
    }

    Node<T>* findNext() {
        Node<T>* current = right;
        while (current && current->left) {
            current = current->left;
        }
        if (current) return current;

        current = this;
        Node<T>* ancestor = current->parent;
        while (ancestor && ancestor->right == current) {
            current = ancestor;
            ancestor = ancestor->parent;
        }
        return ancestor;
    }

    Node(const Node<T>& other) {
        height = other.height;
        parent = other.parent;
        right = other.right;
        left = other.left;
        data = other.data;
    }

    ~Node() {
        delete data;
    }
};

/**
 * AVLTree<T> - Self-balancing Binary Search Tree
 */
template <class T>
class AVLTree {
public:
    Node<T>* root;
    int node_count;
    Node<T>* smallest;

    AVLTree() : root(nullptr), node_count(0), smallest(nullptr) {}

    ~AVLTree() {
        clear(root);
        root = nullptr;
    }

    AVLTree(const AVLTree<T>& other) {
        node_count = other.node_count;
        root = clone(other.root);
        smallest = findMin(root);
    }

    AVLTree<T>& operator=(const AVLTree<T>& other) {
        if (this != &other) {
            clear(root);
            root = clone(other.root);
            node_count = other.node_count;
            smallest = findMin(root);
        }
        return *this;
    }

    bool isEmpty() const {
        return root == nullptr && node_count == 0;
    }

    void insert(T* data) {
        if (!root) {
            root = new Node<T>(data, 1);
            smallest = root;
            node_count++;
            return;
        }

        Node<T>* current = root;
        Node<T>* parent = nullptr;

        while (current) {
            parent = current;
            if (*data < *(current->data))
                current = current->left;
            else
                current = current->right;
        }

        Node<T>* new_node = new Node<T>(data, 1, parent);
        if (*data < *(parent->data))
            parent->left = new_node;
        else
            parent->right = new_node;

        updateHeights(parent);
        rebalance(parent);
        node_count++;
    }

    void remove(T* data) {
        Node<T>* node = findNode(data);
        if (!node) return;

        if (node->left && node->right) {
            Node<T>* successor = findMin(node->right);
            swap(node->data, successor->data);
            node = successor;
        }

        Node<T>* child = node->left ? node->left : node->right;
        linkParent(node, child);
        updateHeights(node->parent);
        rebalance(node->parent);
        delete node;
        node_count--;
    }

    Node<T>* findNode(T* data) {
        Node<T>* current = root;
        while (current) {
            if (*data == *(current->data)) return current;
            if (*data < *(current->data)) current = current->left;
            else current = current->right;
        }
        return nullptr;
    }

private:
    void clear(Node<T>* node) {
        if (!node) return;
        clear(node->left);
        clear(node->right);
        delete node;
    }

    Node<T>* clone(Node<T>* node) {
        if (!node) return nullptr;
        Node<T>* left_clone = clone(node->left);
        Node<T>* right_clone = clone(node->right);
        Node<T>* new_node = new Node<T>(node->data, node->height, nullptr, right_clone, left_clone);
        if (left_clone) left_clone->parent = new_node;
        if (right_clone) right_clone->parent = new_node;
        return new_node;
    }

    void updateHeights(Node<T>* node) {
        while (node) {
            int left_height = (node->left) ? node->left->height : 0;
            int right_height = (node->right) ? node->right->height : 0;
            node->height = max(left_height, right_height) + 1;
            node = node->parent;
        }
    }

    void updateSmallest() {
        smallest = findMin(root);
    }

    void linkParent(Node<T>* from, Node<T>* to) {
        if (!from->parent)
            root = to;
        else if (from->parent->left == from)
            from->parent->left = to;
        else
            from->parent->right = to;

        if (to) to->parent = from->parent;
    }

    Node<T>* findMin(Node<T>* node) const {
        if (!node) return nullptr;
        while (node->left) node = node->left;
        return node;
    }

    void rotateLL(Node<T>* node) {
        Node<T>* l_child = node->left;
        linkParent(node, l_child);
        node->left = l_child->right;
        if (l_child->right) l_child->right->parent = node;
        l_child->right = node;
        node->parent = l_child;
        updateHeights(node);
    }

    void rotateRR(Node<T>* node) {
        Node<T>* r_child = node->right;
        linkParent(node, r_child);
        node->right = r_child->left;
        if (r_child->left) r_child->left->parent = node;
        r_child->left = node;
        node->parent = r_child;
        updateHeights(node);
    }

    void rotateLR(Node<T>* node) {
        rotateRR(node->left);
        rotateLL(node);
    }

    void rotateRL(Node<T>* node) {
        rotateLL(node->right);
        rotateRR(node);
    }

    void rebalance(Node<T>* node) {
        if (!node) return;
        int balance_factor = node->getBalance();

        if (balance_factor > 1) {
            if (node->left->getBalance() >= 0) rotateLL(node);
            else rotateLR(node);
        } else if (balance_factor < -1) {
            if (node->right->getBalance() <= 0) rotateRR(node);
            else rotateRL(node);
        }

        if (node->parent)
            rebalance(node->parent);
        else
            smallest = findMin(root);
    }
};

#endif // AVLTree_h
