#include<bits/stdc++.h>
using namespace std;

#define NIL sentinel

int RED = 0;
int BLACK = 1;

class node {
    public:

        int key;
        node* left;
        node* right;
        node* parent;
        int color;

        node() {
            key = 0;
            color = RED;
        }

        node(int key) {
            this->key = key;
            color = RED;
        }
};

class redBlackTree {

        node* root;
        int sz;
        node* sentinel;
        
        node* leftRotate(node* x, node* y) {
            y->parent = x->parent;
            if(x->parent != NIL) {
                if(x->parent->left == x) {
                    x->parent->left = y;
                }
                else {
                    x->parent->right = y;
                }
            }
            else {
                root = y;
            }
            x->right = y->left;
            if(y->left != NIL) {
                y->left->parent = x;   
            }
            y->left = x;
            x->parent = y;
            return y;
        }

        node* rightRotate(node* x, node* y) {
            y->parent = x->parent;
            if(x->parent != NIL) {
                if(x->parent->left == x) {
                    x->parent->left = y;
                }
                else {
                    y->parent->right = y;
                }
            }
            else {
                root = y;
            }
            x->left = y->right;
            if(y->right != NIL) {
                y->right->parent = x;
            }
            y->right = x;
            x->parent = y;
            return y;
        }

        node* searchNode(node* cur, int key) {
            if(cur == NIL || cur->key == key) {
                return cur;
            }
            if(cur->key > key) {
                return searchNode(cur->left, key);
            }
            else {
                return searchNode(cur->right, key);
            }
        }

        void initializeNode(node* temp) {
            temp->left = NIL;
            temp->parent = NIL;
            temp->right = NIL;
        }

        void resetSentinel() {
            sentinel->color = BLACK;
            sentinel->parent = sentinel;
            sentinel->left = sentinel;
            sentinel->right = sentinel;
            sentinel->key = 0;
        }

        void printSenInfo() {
            cout<<"Sen INFO: \n";
            cout<<sentinel->key<<" "<<sentinel->parent->key<<" "<<sentinel->left->key<<" "<<sentinel->right->key<<" "<<sentinel->color<<endl;
            cout<<"info of Sen ends!\n";
        }

        void insertFixup(node* z) {
            while(z->parent->color == RED) {
                // case: left grandchild
                if(z->parent == z->parent->parent->left) {
                    //case 1: uncle is RED
                    node* uncle = z->parent->parent->right;
                    if(uncle->color == RED) {
                        z->parent->color = BLACK;
                        uncle->color = BLACK;
                        z->parent->parent->color = RED;
                        z = z->parent->parent;
                    }
                    //case 2: uncle is BLACK and z is right child
                    else {
                        if(z == z->parent->right) {
                            z = z->parent;
                            leftRotate(z, z->right);
                        }
                        //case 3: uncle is BLACK and z is left child
                        z->parent->color = BLACK;
                        z->parent->parent->color = RED;
                        rightRotate(z->parent->parent, z->parent);
                    }
                }
                // case: right grandchild symmetric with left right exchaned
                else {
                    node* uncle = z->parent->parent->left;
                    if(uncle->color == RED) {
                        z->parent->color = BLACK;
                        uncle->color = BLACK;
                        z->parent->parent->color = RED;
                        z = z->parent ->parent;
                    }
                    else {
                        if(z == z->parent->left) {
                            z = z->parent;
                            rightRotate(z, z->left);
                        }
                        z->parent->color = BLACK;
                        z->parent->parent->color = RED;
                        leftRotate(z->parent->parent, z->parent);
                    }
                }
            }
            root->color = BLACK;
            resetSentinel();
        }

        void nodeTransplant(node* prev, node* cur) {
            if(prev->parent == NIL) {
                root = cur;
            }
            else if(prev->parent->left == prev) {
                prev->parent->left = cur;
            } 
            else {
                prev->parent->right = cur;
            }
            cur->parent = prev->parent;
        }

        node* successor(node* t) {
            node* suc = t;
            node* temp = t->right;
            while(temp != NIL) {
                suc = temp;
                temp = temp->left;
            }
            return suc;
        }

        void deleteFixup(node* z) {
            while(root != z && z->color == BLACK) {
                if(z->parent->left == z) {
                    node* w = z->parent->right;
                    if(w->color == RED) {
                        w->color = BLACK;
                        z->parent->color = RED;
                        leftRotate(z->parent, w);
                        w = z->parent->right;
                    }
                    if(w->left->color == BLACK && w->right->color == BLACK) {
                        w->color = RED;
                        z = z->parent;
                    }
                    else {
                        if(w->right->color == BLACK) {
                            w->left->color = BLACK;
                            w->color = RED;
                            rightRotate(w, w->left);
                            w = z->parent->right;
                        }
                        w->color = z->parent->color;
                        z->parent->color = BLACK;
                        w->right->color = BLACK;
                        leftRotate(z->parent,w);
                        z = root;
                    }
                }
                else {
                    node* w = z->parent->left;
                    if(w->color == RED) {
                        w->color = BLACK;
                        z->parent->color = RED;
                        rightRotate(z->parent, w);
                        w = z->parent->left;
                    }
                    if(w->right->color == BLACK && w->left->color == BLACK) {
                        w->color = RED;
                        z = z->parent;
                    }
                    else {
                        if(w->left->color == BLACK) {
                            w->right->color = BLACK;
                            w->color = RED;
                            leftRotate(w, w->right);
                            w = z->parent->left;
                        }
                        w->color = z->parent->color;
                        z->parent->color = BLACK;
                        w->left->color = BLACK;
                        rightRotate(z->parent,w);
                        z = root;
                    }
                }
            }
            z->color = BLACK;
            resetSentinel();
            //printSenInfo();
        }

        void preOrderTraverse(node* x) {
            if(x == NIL) {
                return;
            }
            cout<<x->key<<"("<<x->color<<")"<<" ";
            preOrderTraverse(x->left);
            preOrderTraverse(x->right);
        }
    
    public: 

        redBlackTree() {
            sz = 0;
            sentinel = new node();
            sentinel->key = 0;
            sentinel->parent = sentinel;
            sentinel->left = sentinel;
            sentinel->right = sentinel;
            sentinel->color = BLACK;
            root = NIL;
        }

        bool insertNode(int k) {
            node* newNode = new node(k);
            initializeNode(newNode);
            node* p = NIL;
            node* cur = root;
            while(cur != NIL) {
                if(cur->key == k) {
                    return false;
                }
                p = cur;
                if(cur->key < k) {
                    cur = cur->right;
                }
                else {
                    cur = cur->left;
                }
            }
            newNode->parent = p;
            if(p == NIL) {
                root = newNode;
            }
            else if(p->key < k) {
                p->right = newNode;
            }
            else {
                p->left = newNode;
            }
            newNode->color = RED;
            insertFixup(newNode);
            sz++;
            return true;
        }

        bool deleteNode(int key) {
            node* z = searchNode(root, key);
            if(z != NIL) {
                node* x;
                int originColor = z->color;
                if(z->left == NIL) {
                    x = z->right;
                    nodeTransplant(z,x);
                }
                else if(z->right == NIL) {
                    x = z->left;
                    nodeTransplant(z,x);
                }
                else {
                    node* y = successor(z);
                    originColor = y->color;
                    x = y->right;
                    if(y->parent != z) {
                        nodeTransplant(y,x);
                        y->right = z->right;
                        y->right->parent = y;
                    }
                    nodeTransplant(z,y);
                    y->left = z->left;
                    z->left->parent = y;
                    y->color = z->color;
                }
                if(originColor == BLACK) {
                    deleteFixup(x);
                }
                delete z;
                return true;
            }
            return false;
        }

        bool search(int key) {
            return searchNode(root, key) == NIL ? false : true; 
        }

        void preOrderPrint() {
            cout<<"Tree: \n";
            preOrderTraverse(root);
            cout<<'\n';
        }

        int getSize() {
            return sz;
        }

};

int main() {
    redBlackTree rb;
    //rb.preOrderPrint();
    rb.insertNode(1);
    rb.insertNode(2);
    rb.insertNode(3);
    rb.insertNode(4);
    rb.insertNode(5);
    rb.deleteNode(2);
    rb.insertNode(6);
    rb.deleteNode(3);
    rb.insertNode(7);
    rb.insertNode(8);
    rb.insertNode(9);
    rb.deleteNode(9);
    
    rb.preOrderPrint();
}