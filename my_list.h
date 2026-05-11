#include <stdexcept>
#include "node.h"

template <typename K, typename V>
class MyList{
private:
    Node<K, V>* start;
    Node<K, V>* end;

    std::size_t size;

public:
    //constructors
    MyList(){
        start = nullptr;
        end = nullptr;
        size = 0;
    }

    MyList(Node<K, V>* start_n){
        if(start_n == nullptr) {
            start = nullptr;
            end = nullptr;
            size = 0;
            return;
        }

        this->start = new Node<K, V>(start_n->get_key(), start_n->get_val());
        this->end = this->start;
        size = 1;
    }

    MyList(const MyList<K, V>& other){
        Node<K, V>* tmp2 = other.begin();

        start = nullptr;
        size = other.length();

        if(tmp2 != nullptr){
            start = new Node<K, V>(tmp2->get_key(), tmp2->get_val());
            tmp2 = tmp2->get_next();
        }

        Node<K, V>* tmp1 = start;
        end = start;

        while(tmp2 != nullptr){
            Node<K, V>* next = new Node<K, V>(tmp2->get_key(), tmp2->get_val());
            next->set_prev(tmp1);
            tmp1->set_next(next);

            end = next;
            tmp2 = tmp2->get_next();
            tmp1 = next;
        }
    }

    MyList(MyList<K, V>&& other) noexcept{
        this->start = other.begin();
        this->end = other.tail();
        this->size = other.length();

        other.start = nullptr;
        other.end = nullptr;
        other.size = 0;
    }

    //assigments
    MyList& operator=(MyList<K, V>&& other) noexcept{
        if(this != &other){
            erase();

            this->start = other.begin();
            this->end = other.tail();
            this->size = other.length();

            other.start = nullptr;
            other.end = nullptr;
            other.size = 0;
        }

        return *this;
    }
    
    MyList& operator=(const MyList<K, V>& other){
        if(this != &other){
            erase();

            Node<K, V>* tmp = other.begin();
            if(tmp == nullptr){
                start = nullptr;
                end = nullptr;
                size = 0;
                return *this;
            }

            start = new Node<K, V>(tmp->get_key(), tmp->get_val());
            Node<K, V>* curr = start;
            end = start;
            tmp = tmp->get_next();

            while(tmp != nullptr){
                Node<K, V>* next = new Node<K, V>(tmp->get_key(), tmp->get_val());
                curr->set_next(next);
                next->set_prev(curr);

                end = next;
                curr = next;
                tmp = tmp->get_next();
            }

            size = other.length();
        }

        return *this;
    }

    //operations
    Node<K, V>* begin() const{
        return start;
    }

    Node<K, V>* tail() const{
        return end;
    }

    std::size_t length() const{
        return size;
    }

    //insert without transfering ownership
    Node<K, V>* insert(Node<K, V>* new_node){
        if(new_node == nullptr){
            return nullptr;
        }

        Node<K, V>* el = new Node<K, V>(new_node->get_key(), new_node->get_val());
        
        el->set_prev(nullptr);
        el->set_next(nullptr);

        if(start == nullptr){
            start = el;
            end = el;
            size = 1;
            return el;
        }

        //new head
        if(el->get_key() < start->get_key()){
            el->set_next(start);
            start->set_prev(el);
            start = el;
            size++;
            return el;
        }

        //find insertion point
        Node<K, V>* tmp = start;
        while(tmp->get_next() != nullptr && tmp->get_next()->get_key() <= el->get_key()){
            tmp = tmp->get_next();
        }

        el->set_next(tmp->get_next());
        el->set_prev(tmp);

        if(tmp->get_next() != nullptr){
            tmp->get_next()->set_prev(el);
        }
        else {
            end = el;
        }

        tmp->set_next(el);
        size++;
        return el;
    }

    //remove first node with key k
    bool remove(const K& k){
        Node<K, V>* tmp = get_node(k);
        if (tmp == nullptr) {
            return false;
        }

        if (tmp->get_prev() != nullptr) {
            tmp->get_prev()->set_next(tmp->get_next());
        } else {
            start = tmp->get_next();
        }

        if (tmp->get_next() != nullptr) {
            tmp->get_next()->set_prev(tmp->get_prev());
        }
        else{
            end = tmp->get_prev();
        }

        delete tmp;
        size--;
        if(size == 0) {
            start = nullptr;
            end = nullptr;
        }
        return true;
    }

    //remove node by pointer (suitable only for already found nodes in list)
    bool remove(Node<K, V>* tmp){
        if (tmp == nullptr) {
            return false;
        }

        //if not head
        if (tmp->get_prev() != nullptr) {
            tmp->get_prev()->set_next(tmp->get_next());
        }
        else{
            this->start = tmp->get_next();
        }

        //if not tail
        if (tmp->get_next() != nullptr) {
            tmp->get_next()->set_prev(tmp->get_prev());
        }
        else{
            this->end = tmp->get_prev();
        }

        delete tmp;
        size--;
        if(size == 0) {
            start = nullptr;
            end = nullptr;
        }
        return true;
    }

    //nullptr if not found
    Node<K, V>* get_node(const K& k) const{
        Node<K, V>* tmp = start;
        
        while(tmp != nullptr){
            if(tmp->get_key() == k) return tmp;

            tmp = tmp->get_next();
        }

        return nullptr;
    }
    
    // Returns node with largest key <= k
    // or start if all keys in list are > k
    Node<K, V>* find(const K& k) const{
        Node<K, V>* tmp = start;
        if(tmp == nullptr){
            return nullptr;
        }

        while(tmp->get_next() != nullptr){
            if(tmp->get_key() == k) return tmp;
            if(tmp->get_key() > k) return tmp->get_prev() == nullptr ? start : tmp->get_prev();

            tmp = tmp->get_next();
        }

        if(tmp->get_key() == k) return tmp;
        if(tmp->get_key() > k) return tmp->get_prev() == nullptr ? start : tmp->get_prev();
        return tmp;
    }

    // Starting search from start_node
    // returns node with largest key <= k
    // or start_node if all keys in list are > k
    Node<K, V>* find_from(Node<K, V>* start_node, const K& k) const{
        if(start_node == nullptr){
            return find(k);
        }
        
        Node<K, V>* tmp = start_node;
        if(tmp == nullptr){
            return nullptr;
        }

        while(tmp->get_next() != nullptr){
            if(tmp->get_key() == k) return tmp;
            if(tmp->get_key() > k) return tmp->get_prev() == nullptr ? start_node : tmp->get_prev();

            tmp = tmp->get_next();
        }

        if(tmp->get_key() == k) return tmp;
        if(tmp->get_key() > k) return tmp->get_prev() == nullptr ? start_node : tmp->get_prev();
        return tmp;
    }

    //lower/upper_bound -> nullptr if not found
    Node<K, V>* lower_bound(const K& k) const{
        Node<K, V>* tmp = start;
        if(tmp == nullptr){
            return nullptr;
        }
        while(tmp->get_key() < k){
            if(tmp->get_next() == nullptr){
                return nullptr;
            }
            tmp = tmp->get_next();
        }

        return tmp;
    }

    
    Node<K, V>* upper_bound(const K& k) const{
        Node<K, V>* tmp = start;
        if(tmp == nullptr){
            return nullptr;
        }

        while(tmp->get_key() <= k){
            if(tmp->get_next() == nullptr){
                return nullptr;
            }
            tmp = tmp->get_next();
        }

        return tmp;
    }
    
    //successor/predeccessor
    Node<K, V>* successor(const K& k) const{
        Node<K, V>* tmp = get_node(k);

        return (tmp == nullptr) ? tmp : tmp->get_next();
    }
    
    Node<K, V>* predeccessor(const K& k) const{
        Node<K, V>* tmp = get_node(k);

        return tmp == nullptr ? tmp : tmp->get_prev();
    }
    
    // update first node with key k to value v
    bool update(const K& k, const V& v){
        Node<K, V>* tmp = get_node(k);

        if(tmp == nullptr) return false;

        tmp->set_val(v);

        return true;
    }

    // rank(x): how many elements in list with key < k
    std::size_t rank(const K& k) const{
        Node<K, V>* tmp = start;
        
        std::size_t r = 0;
        while(tmp != nullptr){
            if(tmp->get_key() >= k) return r;

            tmp = tmp->get_next();
            r++;
        }

        return r;
    }
    
    //deep copy from other and destry other
    void merge(MyList<K, V>& other){
        if(this == &other){
            return;
        }
        //move other to this
        if(start==nullptr){
            *this = other;
            other.erase();
            return;
        }

        Node<K, V>* curr1 = start;
        Node<K, V>* curr2 = other.begin();

        while(curr1->get_next() != nullptr){
            if(curr2 == nullptr){
                break;
            }
            
            //find first node in L1 with key > curr2.key
            while(curr1->get_key() < curr2->get_key()){
                if(curr1->get_next() == nullptr){
                    break;
                }
                curr1 = curr1->get_next();
            }
            if(curr1->get_next() == nullptr){
                break;
            }

            //insert el from L2 in L1
            Node<K, V>* to_add = new Node<K, V>(curr2->get_key(), curr2->get_val());
            if(curr1->get_prev() != nullptr){
                Node<K, V>* tmp = curr1->get_prev();

                tmp->set_next(to_add);
                to_add->set_prev(tmp);
            }
            //if curr1 = start
            else{
                start = to_add;
            }
            curr1->set_prev(to_add);
            to_add->set_next(curr1);

            curr2 = curr2->get_next();
        }

        if(curr1->get_next() == nullptr){
            end = curr1;
        }

        //insert any left elements from L2 infront
        while(curr2 != nullptr && curr1->get_key() > curr2->get_key()){
            Node<K, V>* to_add = new Node<K, V>(curr2->get_key(), curr2->get_val());
            
            if(curr1->get_prev() != nullptr){
                Node<K, V>* tmp = curr1->get_prev();

                tmp->set_next(to_add);
                to_add->set_prev(tmp);
            }
            else{
                start = to_add;
            }
            curr1->set_prev(to_add);
            to_add->set_next(curr1);
            
            end = curr2;
            curr2 = curr2->get_next();
        }
        
        //insert any left elements from L2 at the end
        while(curr2 != nullptr){
            Node<K, V>* to_add = new Node<K, V>(curr2->get_key(), curr2->get_val());

            to_add->set_prev(curr1);
            curr1->set_next(to_add);
            to_add->set_next(nullptr);

            curr1 = curr1->get_next();
            end = curr1;
            curr2 = curr2->get_next();
        }

        size+=other.length();
        other.erase();
    }

    //cleanup
    void erase(){
        Node<K,V>* tmp = start;
        while(tmp != nullptr){
            Node<K, V>* next = tmp->get_next();
            delete tmp;
            tmp = next;
        }
        size = 0;
        start = nullptr;
        end = nullptr;
    }
    
    ~MyList(){
        erase();
    }
};



