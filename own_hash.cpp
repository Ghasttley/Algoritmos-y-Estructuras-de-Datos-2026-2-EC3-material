#include <bits/stdc++.h>
// reference to: https://www.youtube.com/watch?v=Wbdw5ucmHic, so sorry for not understanding el de la clase

// Node 
template<typename kt, typename vt>
struct Node{
    kt key; vt value; Node* next;

    Node(kt key, vt value): key(key), value(value), next(nullptr) {}
};

// Hash table
template<typename kt, typename vt>
class hashtab{
    int n; // n: buckets
        std::vector<Node<kt, vt>*> table;
        const size_t hashfunct(kt key) const { return std::hash<kt>{}(key) % static_cast<size_t>(n);
            //return key%n; // for strings up one...
        }

    public:
        explicit hashtab(int n): n(n), table(n, nullptr){ }
        hashtab(const hashtab&) = delete; hashtab& operator=(const hashtab&) = delete;

        vt* search(const kt& key){
            int idx = hashfunct(key); // "hashing the key"
                for (Node<kt, vt>* current = table[idx]; current; current = current -> next)
                    { if (current -> key == key) { return &current -> value; } }
            return nullptr; 
        }   

        const vt* search(const kt& key) const {
            size_t idx = hashfunct(key); // "hashing the key"
                for (Node<kt, vt>* current = table[idx]; current; current = current -> next)
                    { if (current -> key == key) { return &current -> value; } }
            return nullptr; 
        }   

        void insert(const kt& key, const vt& value){
            size_t idx = hashfunct(key); // "hashing the key"
                Node<kt, vt>* head = table[idx]; Node<kt, vt>* current = head;

                for(Node<kt, vt>* current = table[idx]; current; current = current -> next){
                    if(current -> key == key){
                        current -> value = value;
                    return; }
                } Node<kt, vt>* nnode = new Node<kt, vt>(key, value); 
                    nnode -> next = head; table[idx] = nnode; 
        }

        void remove(const kt& key){
            size_t idx = hashfunct(key); // "hashing the key"
                Node<kt, vt>* current = table[idx]; Node<kt, vt>* prev = nullptr;
                
                while(current!=nullptr){
                    if(current -> key == key){
                        if(prev==nullptr){
                            table[idx] = current -> next; // ! next ptr will be head node
                        } else {
                            prev -> next = current -> next; // done for before and after values
                        } delete current;
                    return; } prev = current; 
                        current = current -> next;
                }
        }

    void print() const {
        for (int i=0; i<n; i++) {
            std::cout << "[" << i << "]: ";
                Node<kt, vt>* current = table[i];
            
            while (current != nullptr) {
                std::cout << "(" << current -> key << ": " << current -> value << ")";
            if (current -> next) std::cout << " -> ";
                current = current -> next;
            } std::cout << "\n";
        }
    }

        ~hashtab(){
            for(auto current: table){
                while(current){
                    Node<kt, vt>* temp = current; 
                        current = current -> next;
                        delete temp;
                }
            }
        }
};

int main(){
    // Use cases
    hashtab<int, std::string> tab(10);
        tab.insert(1, "star"); tab.insert(105, "solbyte"); tab.insert(7, "meow"); 
            tab.insert(207, "patrick star"); tab.insert(11, "toxtricity");
                tab.insert(5, "smaller"); tab.insert(2, "powpow"); tab.insert(6, "fishbones");
            if(auto* i = tab.search(1)) 
                std::cout << *i << std::endl; // *tab.search(100) -> nullptr

                std::cout << "\nBefore deletion: " << *tab.search(105) << "\nAfter deletion: ";
                
                    tab.remove(105); auto s = tab.search(105);
                        if (s) {
                            std::cout << *s << "\n";
                        } else {
                            std::cout << "nullptr\n";
                        } std::cout << "\n\n"; tab.print();
    return 0;
}
