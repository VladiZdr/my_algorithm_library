template <typename T>
class Node{
private:
    Node<T> next;
    Node<T> prev;
    T key;
    T val;
public:

    //constructors
    Node(){
        next = nullptr;
        prev = nullptr;
        key = -1;
        val = -1;
    }

    Node(Node<T> next, Node<T> prev, T key, T val){
        this.next = next;
        this.prev = prev;
        this.key = key;
        this.val = val;
    }

    Node(const Node<T>& other){
        this.next = other.next;
        this.prev = other.prev;
        this.key = other.key;
        this.val = other.val;
    }
    
    Node(const Node<T>&& other) noexcept{
        if(this == other) return;

        this.next = other.next;
        this.prev = other.prev;
        this.key = other.key;
        this.val = other.val;

        other.next = nullptr;
        other.prev = nullptr;
        other.key = -1;
        other.val = -1;
    }

    Node& operator=(const Node& other){
        if(this != other){
            this.next = other.next;
            this.prev = other.prev;
            this.key = other.key;
            this.val = other.val;
        }

        return *this;
    }

    //getters
    Node<T> next() const{
        return next;
    }

    Node<T> prev() const{
        return prev;
    }

    T key() const{
        return key;
    }
    
    T val() const{
        return val;
    }

    //setter
    void set_next(Node<T> new_next){
        next = new_next;
    }

    void set_prev(Node<T> new_prev){
        prev = new_prev;
    }
    
    void set_key(Node<T> new_key){
        key = new_key;
    }

    void set_val(Node<T> new_val){
        val = new_val;
    }
};