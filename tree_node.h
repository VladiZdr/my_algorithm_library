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

    // Destructor
    ~TreeNode() {
        delete left;
        delete right;
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
