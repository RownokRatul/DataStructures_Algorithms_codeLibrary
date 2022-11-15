#include<iostream>
#include<vector>
#include<list>
#include<iterator>
#include<cmath>
using namespace std;

#define INVALID -99999999

int negInf = -9999999;

template<typename T> class node {

    public:

        T value;
        node<T>* parent;
        node<T>* next;
        node<T>* prev;
        list<node<T>*> child;
        int degree;
        bool mark;

        node(T val) {
            value = val;
            parent = nullptr;
            next = nullptr;
            prev = nullptr;
            degree = 0;
            mark = false;
        }
};

template <typename T> class fibonacciHeap {
        node<T>* head;
        node<T>* tail;
        node<T>* minNode;
        int size;

        node<T>* searchByKey(T val) {
            node<T>* cur = head;
            while(cur != nullptr) {
                node<T>* result = searchTree(cur, val);
                if(result != nullptr) {
                    return result;
                }
                cur = head->next;
            }
            return nullptr;
        }

        node<T>* searchTree(node<T>* root, T val) {
            if(root == nullptr || root->value == val) {
                return root;
            }
            typename list<node<T>*>::iterator it = root->child.begin();
            while(it != root->child.end()) {
                node<T>* result = searchTree(*it, val);
                if(result != nullptr) {
                    return result;
                }
                it++;
            }
            return nullptr;
        }

        void fibonacciConsolidateHeap() {
            int n = log(size) + 5;
            node<T>* aux[n];
            for(int i=0;i<n;i++) {
                aux[i] = nullptr;
            }
            node<T>* cur = head;
            while(cur != nullptr) {
                node<T>* x = cur;
                int deg = cur->degree;
                while(aux[deg] != nullptr) {
                    node<T>* y = aux[deg];
                    if(x->value > y->value) {
                        swap(x,y);
                    }
                    fibonacciLink(x,y);
                    aux[deg] = nullptr;
                    deg++;
                }
                aux[deg] = x;
                cur = cur->next;
            }
            minNode = nullptr;
            for(int i=0;i<n;i++) {
                if(aux[i] != nullptr) {
                    if(minNode == nullptr) {
                        head = aux[i];
                        tail = aux[i];
                        tail->next = nullptr;
                        head->prev = nullptr;
                        minNode = head;
                    }
                    else {
                        tail->next = aux[i];
                        tail->next->prev = tail;
                        tail = tail->next;
                        if(aux[i]->value < minNode->value) {
                            minNode = aux[i];
                        }
                    }
                }
            }
        }

        void fibonacciLink(node<T>* c, node<T>* p) {
            if(c->prev != nullptr) {
                c->prev->next = c->next;
            }
            if(c->next != nullptr) {
                c->next->prev = c->prev;
            }
            c->parent = p;
            p->child.push_back(c);
            p->degree++;
            c->mark = false;
        }

        void fibonacciCut(node<T>* x, node<T>* y) {
            y->child.erase(x);
            y->degree--;
            x->parent = nullptr;
            tail->next = x;
            tail->next->prev = x;
            x->mark = false;
        }

        void fibonacciCascadedCut(node<T>* z) {
            node<T>* parent = z->parent;
            if(parent != nullptr) {
                if(z->mark == false) {
                    z->mark = true;
                }
                else {
                    fibonacciCut(z,parent);
                    fibonacciCascadedCut(parent);
                }
            }
        }

    public:

        fibonacciHeap() {
            minNode = nullptr;
            head = nullptr;
            tail = nullptr;
            size = 0;
        }

        void insert(T val) {
            node<T>* t = new node<T> (val);
            if(head == nullptr) {
                head = t;
                minNode = t;
                tail = t;
            }
            else {
                tail->next = t;
                t->prev = tail;
                tail = t;
                minNode = (minNode->value > t->value) ? t : minNode;
            }
            size++;
        }

        T minimum() {
            return minNode == nullptr ? INVALID : minNode->value;
        }

        void unionHeap(fibonacciHeap<T>& f) {
            if(!size) {
                head = f.head;
                tail = f.tail;
                minNode = f.minNode;
            }
            else if(f.size) {
                tail->next = f.head;
                f.head->prev = tail;
                tail = f.tail;
                minNode = (minNode->value > f.minNode->value) ? f.minNode : minNode;
            }
            size += f.size;
        }

        T extractMin() {
            node<T>* prevMin = minNode;
            node<T>* cur = tail;
            if(minNode != nullptr) {
                typename list<node<T>*>::iterator it = minNode->child.begin();
                while(it != minNode->child.end()) {
                    node<T>* t = *it;
                    cur->next = t;
                    t->prev = cur;
                    t->parent = nullptr;
                    cur = t;
                    it++;
                }
                if(minNode->prev != nullptr) {
                    minNode->prev->next = minNode->next;
                }
                if(minNode->next != nullptr) {
                    minNode->next->prev = minNode->prev;
                }
                if(size == 1) {
                    minNode = nullptr;
                    head = nullptr;
                    tail = nullptr;
                }
                else {
                    fibonacciConsolidateHeap();
                }
                size--;
                delete prevMin;
            }
            return INVALID;
        }

        bool decreaseKey(node<T>* t, T newKey) {
            if(t != nullptr && t->value > newKey) {
                cout<<"Invalid key.\n";
                return false;
            }
            t->value = newKey;
            node<T>* parent = t->parent;
            if(parent != nullptr && parent->value > t->value) {
                fibonacciCut(t,parent);
                fibonacciCascadedCut(parent);
            }
            if(t->value < minNode->value) {
                t = minNode;
            }
            return true;
        }

        bool decreaseKey(T oldKey, T newKey) {
            if(oldKey < newKey) {
                cout<<"Invalid key.\n";
                return false;
            }
            node<T>* t = searchByKey(oldKey);
            if(t == nullptr) {
                cout<<"No search Key.\n";
                return false;
            }
            t->value = newKey;
            node<T>* parent = t->parent;
            if(parent != nullptr && parent->value > t->value) {
                fibonacciCut(t,parent);
                fibonacciCascadedCut(parent);
            }
            if(t->value < minNode->value) {
                t = minNode;
            }
            return true;
        }

        bool deleteElement(node<T>* t) {
            if(t == nullptr) {
                cout<<"Null pointer!\n";
                return false;
            }
            decreaseKey(t,negInf);
            extractMin();
            return true;
        }

        bool deleteElement(T val) {
            node<T>* res = searchByKey(val);
            if(res == nullptr) {
                cout<<"No such Value.\n";
                return false;
            }
            decreaseKey(res, negInf);
            extractMin();
            return true;
        }


};

int main() {

}