#include<bits/stdc++.h>
using namespace std;

#define null nullptr

class node {
    public: 
        int key;
        node* parent;
        node* left;
        node* right;
        int h;

        node(int val) {
            key = val;
            parent = null;
            left = null;
            right = null;
            h = 1;
        }
};

class avlTree {
        node* root;
        int sz;

        int height(node* n) {
            return n==null ? 0 : n->h;
        }

        void leftRotate(node* y, node* z) {
            z->right = y->left;
            if(y->left != null) {
                y->left->parent = z;
            }
            if(root == z) {
                root = y;
                root->parent = null;
            }
            else {
                y->parent = z->parent;
                if(z->parent->left == z) {
                    z->parent->left = y;
                }
                else {
                    z->parent->right = y;
                }
            }
            z->parent = y;
            y->left = z;
            z->h = max(height(z->left), height(z->right))+1;
            y->h = max(height(y->left), height(y->right))+1;
        }

        void rightRotate(node* y, node* z) {
            z->left = y->right;
            if(y->right != null) {
                y->right->parent = z;
            }
            if(root == z) {
                root = y;
                root->parent = null;
            }
            else {
                y->parent = z->parent;
                if(z->parent->left == z) {
                    y->parent->left = y;
                }
                else {
                    y->parent->right = y;
                }
            }
            z->parent = y;
            y->right = z;
            z->h = max(height(z->left), height(z->right))+1;
            y->h = max(height(y->left), height(y->right))+1;
        }

        bool recursiveFind(int val, node* cur) {
            if(cur == null) {
                return false;
            }
            if(cur->key == val) {
                return true;
            } 
            return val < cur->key ? recursiveFind(val, cur->left) : recursiveFind(val, cur->right);
        }

        int balanceFactor (int leftH,int rightH) {
            return leftH - rightH;
        }

        void printHeightViolated() {
            cout<<"Height Invariant Violated!\n";
        }

        node* biggerNode(node* a, node* b) {
            if(a == null) {
                return b;
            }
            else if(b == null) {
                return a;
            }
            else {
                return a->h >= b->h ? a : b;
            }
        }


    public:

        avlTree() {
            root = null;
            sz = 0;
        }

        void parenthesisStructure(node* cur) {
            if(cur == null) {
                return;
            }
            cout<<cur->key;
            if(cur->left == null && cur->right == null) {
                return;
            }
            cout<<"(";
            parenthesisStructure(cur->left);
            cout<<")";
            cout<<"(";
            parenthesisStructure(cur->right);
            cout<<")";
        }

        int getSize() {
            return sz;
        }

        bool insert(int val) {
            node* cur = root;
            //if(cur) cout<<cur->key<<endl;
            node* p = null;
            while(true) {
                if(cur == null) {
                    //if(p) cout<<p->key<<endl;
                    node* newNode = new node(val);
                    if(p == null) {
                        root = newNode;
                    }
                    else {
                        newNode->parent = p;
                        //cout<<newNode->key<<endl;
                        if(val < p->key) {
                            p->left = newNode;
                        }
                        else {
                            //cout<<"hehe"<<p->key<<endl;
                            //cout<<newNode->parent->key<<endl;
                            p->right = newNode;
                        }
                    }
                    //if(p != null) cout<<p->key<<endl;
                    cur = p;
                    //if(cur != null) cout<<cur->key<<endl;
                    p = newNode;
                    //if(p != null) cout<<p->key<<endl;
                    sz++;
                    break;
                }
                if(val < cur->key) {
                    p = cur;
                    cur = cur->left;
                }
                else if(val > cur->key) {
                    p = cur;
                    cur = cur->right;
                }
                else {
                    cout<<"Duplicate keys to Insert!";
                    return false;
                }
            }

            node* child = p;
            //if(cur != null) cout<<cur->key<<endl;
            node* grandChild = null;
            int violated = 0;
            while(cur != null) {
                //cout<<cur->key<<endl;
                int factor = balanceFactor(height(cur->left), height(cur->right));
                if(factor > 1) {
                    //rightRotate or leftRight
                    violated = 1;
                    if(child->left == grandChild) {
                        rightRotate(child, cur);
                        cur = cur->parent;
                        child = grandChild;
                    }
                    else {
                        leftRotate(grandChild, child);
                        rightRotate(grandChild, cur);
                        cur = cur->parent;
                    }
                }
                else if(factor < -1) {
                    //cout<<"at "<<cur->key<<" "<<factor<<endl;
                    //left or rightLeft
                    violated = 1;
                    if(child->right == grandChild) {
                        //cout<<"left"<<endl;
                        leftRotate(child, cur);
                        cur = cur->parent;
                        child = grandChild;
                    }
                    else {
                        //cout<<"rightLeft"<<endl;
                        rightRotate(grandChild, child);
                        leftRotate(grandChild, cur);
                        cur = cur->parent;
                    }
                }

                else {
                    cur->h = 1 + max(height(cur->left), height(cur->right));
                    //cout<<"h:"<<cur->h<<endl;
                }
                grandChild = child;
                child = cur;
                cur = cur->parent;
            }
            if(violated) {
                printHeightViolated();
                cout<<"After Rebalancing: ";
            }
            parenthesisStructure(root);
            cout<<endl;
            return true;
        }

        bool deleteNode(int val) {
            bool found = false;
            node* cur = root;
            node* child = null;
            node* grandchild = null;
            while(cur != null) {
                if(cur->key == val) {
                    found = true;
                    node* temp = cur;
                    if(cur->left == null && cur->right == null) {
                        //no child case
                        if(cur->parent == null) {
                            root = null;
                        }
                        else {
                            cur->parent->left = cur->parent->left == cur ? null : cur->parent->left;
                            cur->parent->right = cur->parent->right == cur ? null : cur->parent->right;
                        }
                        cur = cur->parent;
                    }
                    else if(cur->left == null || cur->right == null) {
                        //one child case
                        if(cur->left != null) {
                            cur->key = cur->left->key;
                            temp = cur->left;
                            cur->left = null;
                        }
                        else {
                            cur->key = cur->right->key;
                            temp = cur->right;
                            cur->right = null;
                        }
                        cur = cur->parent;
                    }
                    else {
                        //two child case
                        node* toSwap = cur->right;
                        while(toSwap->left != null) {
                            toSwap = toSwap->left;
                        }
                        cout<<toSwap->key<<endl;
                        cur->key = toSwap->key;
                        temp = toSwap;
                        if(toSwap->parent == cur) {
                            cur->right = toSwap->right;
                            if(toSwap->right != null) {
                                toSwap->right->parent = cur;
                            }
                        }
                        else {
                            toSwap->parent->left = toSwap->right;
                            if(toSwap->right != null) {
                                toSwap->right->parent = toSwap->parent;
                            }
                        }
                        cur = toSwap->parent;
                    }
                    sz--;
                    delete temp;
                    break;
                }
                else {
                    cur = val < cur->key? cur->left : cur->right; 
                }
            }
            //re-balancing
            int violated = 0;

            while(cur != null) {
                int factor = balanceFactor(height(cur->left), height(cur->right));
                if(factor > 1) {
                    violated = 1;
                    child = biggerNode(cur->left, cur->right);
                    grandchild = biggerNode(child->left, child->right);
                    if(child->left == grandchild) {
                        //right
                        rightRotate(child, cur);
                        cur = cur->parent;
                    }
                    else {
                        //leftRight
                        leftRotate(grandchild, child);
                        rightRotate(grandchild, cur);
                        cur = cur->parent;
                    }
                }
                else if(factor < -1) {
                    violated = 1;
                    child = biggerNode(cur->left, cur->right);
                    grandchild = biggerNode(child->left, child->right);
                    if(child->right == grandchild) {
                        //left
                        leftRotate(child, cur);
                        cur = cur->parent;
                    }
                    else {
                        //rightLeft
                        rightRotate(grandchild, child);
                        leftRotate(grandchild, cur);
                        cur = cur->parent;
                    }
                }
                cur = cur->parent;
            }
            if(violated) {
                printHeightViolated();
                cout<<"After Rebalancing: ";
            }
            parenthesisStructure(root);
            cout<<endl;
            return found;
        }
        
        bool find(int val) {
            return recursiveFind(val, root);
        }

};


int main() {
    freopen("input.txt","r",stdin);
    avlTree t;
    char c;
    int temp;
    while(cin>>c>>temp) { 
        if(c == 'I') {
            t.insert(temp);
        }
        else if(c == 'D') {
            t.deleteNode(temp);
        }
        else if(c == 'F') {
            int f = t.find(temp);
            if(f) {
                cout<<"True"<<endl;
            }
            else {
                cout<<"False"<<endl;
            }
        }
    }
}