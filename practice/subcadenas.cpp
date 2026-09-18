#include <bits/stdc++.h>

// Used: https://github.com/Ghasttley/Algoritmos-y-Estructuras-de-Datos-2026-2-EC3-material/blob/main/own_hash.cpp

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
        const size_t hashfunct(kt key) const { //return std::hash<kt>{}(key) % static_cast<size_t>(n);
            return key%n; // char
        }

    public:
        explicit hashtab(int n): n(n), table(n, nullptr){ }
        hashtab(const hashtab&) = delete; hashtab& operator=(const hashtab&) = delete;

        vt* search(const kt& key){
            size_t idx = hashfunct(key); // "hashing the key"
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

// cadena s: input
//  determinar la longitud de la subcadena 
// contigua más larga de s sin un caracter repetido, 
//considerando que son distintos entre sí

// n >= 128, ya que hay 94 chars posibles: 94 caracteres ASCII imprimibles, n grande

int main(){
    std::string s; std::cin >> s; hashtab<char, int> last(300);

    int l = 0, best = 0;
    for (int r = 0; r < (int)s.size(); ++r) {
        int* prev = last.search(s[r]);
        if (prev != nullptr && *prev >= l) {
            l = *prev + 1;
        } last.insert(s[r], r); best = std::max(best, r - l + 1);
    } std::cout << best << "\n";
    return 0;
}
