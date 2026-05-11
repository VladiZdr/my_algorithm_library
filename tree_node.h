enum Color { RED, BLACK };

template<typename K, typename V>
class TreeNode{
private:
    Color color;
    K key;
    V value;
    TreeNode* left;
    TreeNode* right;
    TreeNode* parent;
public:
    // Constructor
    TreeNode() : color(RED), key(K()), value(V()), left(nullptr), right(nullptr), parent(nullptr) {}
    TreeNode(K key, V value) : color(RED), key(key), value(value), left(nullptr), right(nullptr), parent(nullptr) {}
    TreeNode(K key, V value, TreeNode* parent) : color(RED), key(key), value(value), left(nullptr), right(nullptr), parent(parent) {}
    TreeNode(K key, V value, TreeNode* parent, TreeNode* left, TreeNode* right) : color(RED), key(key), value(value), left(left), right(right), parent(parent) {}
    TreeNode(K key, V value, Color color) : color(color), key(key), value(value), left(nullptr), right(nullptr), parent(nullptr) {}

    // operations

    void rotate_left() {
        if (this == nullptr) {
            return;
        }
        
        TreeNode<K, V>* parent = this->get_parent();
        TreeNode<K, V>* right_child = this->get_right();
        if (right_child == nullptr) {
            return;
        }
        
        // fix node's neighbors
        this->set_right(right_child->get_left());
        this->set_parent(right_child);

        // fix former right child's neighbors
        right_child->set_left(this);
        right_child->set_parent(parent);
        if (parent != nullptr) {
            if (parent->get_left() == this) {
                parent->set_left(right_child);
            } else {
                parent->set_right(right_child);
            }
        }
    }

    void rotate_right() {
        if (this == nullptr) {
            return;
        }
        
        TreeNode<K, V>* parent = this->get_parent();
        TreeNode<K, V>* left_child = this->get_left();
        if (left_child == nullptr) {
            return;
        }
        
        // fix node's neighbors
        this->set_left(left_child->get_right());
        this->set_parent(left_child);

        // fix former left child's neighbors
        left_child->set_right(this);
        left_child->set_parent(parent);
        if (parent != nullptr) {
            if (parent->get_left() == this) {
                parent->set_left(left_child);
            } else {
                parent->set_right(left_child);
            }
        }
    }

    // Destructor
    ~TreeNode() {
        if(left != nullptr) delete left;
        if(right != nullptr) delete right;
    }
    
    // Getters
    Color get_color() const { return color; }
    K get_key() const { return key; }
    V get_value() const { return value; }
    TreeNode* get_left() const { return left; }
    TreeNode* get_right() const { return right; }
    TreeNode* get_parent() const { return parent; }
    
    // Setters
    void set_color(Color new_color) { color = new_color; }
    void set_key(K new_key) { key = new_key; }
    void set_value(V new_value) { value = new_value; }
    void set_left(TreeNode* new_left) { left = new_left; }
    void set_right(TreeNode* new_right) { right = new_right; }
    void set_parent(TreeNode* new_parent) { parent = new_parent; }
};
