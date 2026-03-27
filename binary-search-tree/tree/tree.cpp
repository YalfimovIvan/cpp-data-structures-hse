#include "tree.h"
#include <memory> // Для std::unique_ptr и std::move

// Реализация метода insert
tree_node* tree::insert(int val) {
    if (!root) {
        root = std::make_unique<tree_node>(val);
        return root.get();
    }
    
    tree_node* current = root.get();
    while (true) {
        if (val < current->value) {
            if (!current->left) {
                current->left = std::make_unique<tree_node>(val);
                return current->left.get();
            }
            current = current->left.get();
        } else if (val > current->value) {
            if (!current->right) {
                current->right = std::make_unique<tree_node>(val);
                return current->right.get();
            }
            current = current->right.get();
        } else {
            return current;
        }
    }
}

// Реализация метода remove
bool tree::remove(int val) {
    tree_node* parent = nullptr;
    tree_node* current = root.get();
    
    // Поиск удаляемого узла
    while (current && current->value != val) {
        parent = current;
        current = (val < current->value) ? 
            current->left.get() : current->right.get();
    }
    
    if (!current) return false;

    // Случай 1: у узла 0 или 1 потомок
    if (!current->left || !current->right) {
        auto& child = (parent ? 
            (parent->left.get() == current ? parent->left : parent->right) 
            : root);
        
        if (current->left) {
            child = std::move(current->left);
        } else {
            child = std::move(current->right);
        }
    }
    // Случай 2: два потомка
    else {
        tree_node* minParent = current;
        tree_node* minNode = current->right.get();
        
        while (minNode->left) {
            minParent = minNode;
            minNode = minNode->left.get();
        }
        
        current->value = minNode->value;
        
        if (minParent == current) {
            minParent->right = std::move(minNode->right);
        } else {
            minParent->left = std::move(minNode->right);
        }
    }
    
    return true;
}