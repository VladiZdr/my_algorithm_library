#include "tree_node.h"

template<typename K, typename V>
class MyRedBlackTree {
private:
    TreeNode<K, V>* root;
    size_t height;

    //helper functions
    bool check_children_colors(TreeNode<K, V>* node) const {
        if (node == nullptr) {
            return true;
        }
        
        if (node->get_left() != nullptr && node->get_left()->get_color() == RED) {
            return false;
        }
        
        if (node->get_right() != nullptr && node->get_right()->get_color() == RED) {
            return false;
        }
        
        return check_children_colors(node->get_left()) && check_children_colors(node->get_right());
    }

    bool check_properties() const{
        if (root == nullptr) {
            return true;
        }

        if (root->get_color() != BLACK) {
            return false;
        }
        return check_children_colors(root);
    }

    void recalculate_height() {
        TreeNode<K, V>* current = root;
        height = 0;
        while (current != nullptr) {
            if(current->get_color() == BLACK) height++;
            current = current->get_left();
        }
    }

    void fix_tree_colors(TreeNode<K, V>* current) {
        TreeNode<K, V>* parent = current->get_parent();
        if(parent == nullptr || parent == root || parent->get_color() == BLACK) return;
        
        TreeNode<K, V>* grandparent = parent->get_parent();
        TreeNode<K, V>* uncle = grandparent->get_left() == parent ? grandparent->get_right() : grandparent->get_left();
        
        //case 1: uncle is red, parent is red, grandparent is black
        if(uncle != nullptr && uncle->get_color() == RED){
            parent->set_color(BLACK);
            uncle->set_color(BLACK);
            grandparent->set_color(RED);

            //recursively fix colors
            fix_tree_colors(grandparent);
            root->set_color(BLACK);
        }

        //case 2: uncle black or nullptr
        else if(uncle == nullptr || uncle->get_color() == BLACK){

            // if parent is left child
            if(grandparent->get_left() == parent){
                // left-parent left-child case
                if(parent->get_left() == current){
                    parent->set_color(BLACK);
                    grandparent->set_color(RED);
                    grandparent->rotate_right();
                }
                // left-parent right-child case
                else{
                    parent->rotate_left();
                }
            }

            // if parent is right child
            else{
                // right-parent right-child case
                if(parent->get_right() == current){
                    parent->set_color(BLACK);
                    grandparent->set_color(RED);
                    grandparent->rotate_left();
                }
                // right-parent left-child case
                else{
                    parent->rotate_right();
                }
            }
        }

        
    }
    
public:
    MyRedBlackTree() : root(nullptr), height(0) {}

    // find node with given key
    // if key not found, returns last node visited
    // if tree empty, returns nullptr
    TreeNode<K, V>* find(K key) const{
        TreeNode<K, V>* current = root;
        while (current != nullptr) {
            //go left
            if (key < current->get_key()) {
                if(current->get_left() != nullptr) current = current->get_left();
                else return current;
            } 
            //go right
            else if (key > current->get_key()) {
                if(current->get_right() != nullptr) current = current->get_right();
                else return current;
            } 
            //found
            else {
                return current;
            }
        }
        return nullptr;
    }

    // insert key-value pair into tree and return inserted node
    // if key already exists, returns existing node
    // if tree is empty, creates root node
    TreeNode<K, V>* insert(K key, V value) {

        TreeNode<K, V>* parent = find(key);
        //if tree is empty
        if (parent == nullptr) {
            root = new TreeNode<K, V>(key, value, BLACK);
            height = 1;
            return root;
        }
        
        TreeNode<K, V>* new_node = new TreeNode<K, V>(key, value, RED);
        //1. insert as in BST
        if (key < parent->get_key()) {
            parent->set_left(new_node);
            new_node->set_parent(parent);
        } else {
            parent->set_right(new_node);
            new_node->set_parent(parent);
        }
        
        //2. fix the tree properties
        fix_tree_colors(new_node);
        
        recalculate_height();
        
        return new_node;    
    }

    ~MyRedBlackTree() {
        delete root;
    }

    //getters
    TreeNode<K, V>* get_root() const { return root; }
    size_t get_height() const { return height; }

    //setters
    void set_root(TreeNode<K, V>* new_root) { 
        delete root;
        root = new_root;
        if(root == nullptr){
            height = 0;
            return;
        } 
        if (!check_properties()) {
            throw std::invalid_argument("Invalid tree properties after setting root");
        }
    }
};
