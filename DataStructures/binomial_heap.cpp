#include<iostream>
#include<cstdio>
#include<list>
#include<vector>
#include<algorithm>
#include<queue>
#include<string>
using namespace std;

int inf = 99999999;
int negInf = -99999999;
int mxSize = 100;

class node {

    public:
    
        int value;
        int degree;
        node* parent;
        node* child;
        node* sibling;
        bool vis;

        node() {

        }

        node(int val) {
            value = val;
            degree = 0;
            parent = nullptr;
            child = nullptr;
            sibling = nullptr;
            vis = false;
        }

};

class binomialHeap {
        vector<node*> rootlist;
        int size;

        void binomial_heap_link(node* c, node* p) {
            c->parent = p;
            c->sibling = p->child;
            p->child = c;
            p->degree++;
        }

        vector<node*> binomial_heap_merge(binomialHeap& h) {
            vector<node*> temp;
            vector<node*>::iterator it1,it2;
            it1 = rootlist.begin();
            it2 = h.rootlist.begin();
            while(it1 != rootlist.end() && it2 != h.rootlist.end()) {
                if((*it1)->degree < (*it2)->degree) {
                    temp.push_back(*it1);
                    it1++;
                }
                else {
                    temp.push_back(*it2);
                    it2++;
                }
            }
            if(it1 != rootlist.end()) {
                while(it1 != rootlist.end()) {
                    temp.push_back(*it1);
                    it1++;
                }
            }
            else {
                while(it2 != h.rootlist.end()) {
                    temp.push_back(*it2);
                    it2++;
                }
            }
            return temp;
        }

        pair<node*,int> binomial_heap_maximum() {
            if(!size) {
                return make_pair(nullptr,-1);
            }
            int idx = 0;
            int mx = rootlist[0]->value;
            int len = rootlist.size();
            for(int i=0;i<len;i++) {
                if(mx < rootlist[i]->value) {
                    mx = rootlist[i]->value;
                    idx = i;
                }
            }
            return make_pair(rootlist[idx],idx);
        }

        void binomial_heap_union(binomialHeap& h) {
            this->rootlist = binomial_heap_merge(h);
            int len = rootlist.size();
            vector<node*>::iterator it = rootlist.begin();
            int cur = 0;
            while(cur+1 < len) {
                if((rootlist[cur]->degree != rootlist[cur+1]->degree) || 
                        (cur+2 < len && rootlist[cur+2]->degree == rootlist[cur]->degree)) {
                    cur++;
                    it++;
                }
                else {
                    if(rootlist[cur]->value > rootlist[cur+1]->value) {
                        binomial_heap_link(rootlist[cur+1], rootlist[cur]);
                        it++;
                        it = rootlist.erase(it);
                        it--;
                    }
                    else {
                        binomial_heap_link(rootlist[cur], rootlist[cur+1]);
                        it = rootlist.erase(it);
                    }
                    len--;
                }
            }
        }

        node* search_value(int val) {
            node* t;
            t = nullptr;
            for(node* root : rootlist) {
                t = recursive_search_tree(root, val);
                if(t != nullptr) {
                    break;
                }
            }
            return t;
        }       
    
        node* recursive_search_tree(node* cur, int val) {
            if(cur == nullptr) {
                return nullptr;
            }
            if(cur->value == val) {
                return cur;
            }
            node* t ;
            t = recursive_search_tree(cur->sibling, val);
            if(t == nullptr) {
                t = recursive_search_tree(cur->child, val);
            }
            return t;
        }

        void undoVisited(node* root) {
            if(root != nullptr) {
                root->vis = false;
                undoVisited(root->sibling);
                undoVisited(root->child);
            }
        }

        void levelOrder_tree_print(node* root) {
            int level = -1;
            queue<pair<node*,int> > q;
            vector<int> v[mxSize];
            q.push(make_pair(root,0));
            while(!q.empty()) {
                pair<node*, int> p = q.front();
                node* cur = p.first;
                cur->vis = true;
                int curLevel = p.second;
                q.pop();

                v[curLevel].push_back(cur->value);
                while(cur->sibling != nullptr) {
                    cur = cur->sibling;
                    if(!cur->vis) {
                        q.push(make_pair(cur,curLevel));
                        cur->vis = true;
                    }
                }
                if(p.first->child != nullptr && !p.first->child->vis) {
                    q.push(make_pair(p.first->child, curLevel+1));
                }
            }
            undoVisited(root);
            for(int i=0;i<mxSize;i++) {
                if(!v[i].size()) {
                    break;
                }
                cout<<"Level "<<i<<" : ";
                for(int e:v[i]) {
                    cout<<e<<" ";
                }
                cout<<'\n';
            }
        }

    public: 

        binomialHeap() {
            size = 0;
        }

        int findMax() {
            pair<node*,int> t = binomial_heap_maximum();
            return t.first==nullptr ? negInf : t.first->value;
        }

        bool insert(int val) {
            node* t = new node(val);
            binomialHeap h;
            h.size = 1;
            h.rootlist.push_back(t);
            size++;
            binomial_heap_union(h);
            return true;
        }

        int extractMax() {
            pair<node*,int> t = binomial_heap_maximum();
            if(t.first == nullptr) {
                cout<<"Heap is Empty!\n";
                return negInf;
            }
            vector<node*>::iterator it = rootlist.begin();
            for(int i=0;i<t.second;i++) {
                it++;
            }
            rootlist.erase(it);
            binomialHeap h;
            node* child = t.first->child;
            while(child != nullptr) {
                h.rootlist.push_back(child);
                child->parent = nullptr;
                node* temp = child;
                child = child->sibling;
                temp->sibling = nullptr;
            }

            reverse(h.rootlist.begin(),h.rootlist.end());
            h.size = h.rootlist.size();
            binomial_heap_union(h);
            size--;
            int mx = t.first->value;
            delete t.first;
            return mx;
        }

        bool increaseKey(int ki, int kf) {
            if(ki > kf) {
                //cout<<"Invalid key!\n";
                return false;
            }
            node* t = search_value(ki);
            if(t == nullptr) {
                //cout<<"No such key found to increase!\n";
                return false;
            }
            t->value = kf;
            node* p = t->parent;
            while(p != nullptr && p->value < t->value) {
                int temp = p->value;
                p->value = t->value;
                t->value = temp;
                t = p;
                p = t->parent;
            } 
            return true;
        }

        bool increaseKey(node* cur, int k) {
            if(cur->value > k) {
                //cout<<"Invalid key!\n";
                return false;
            }
            cur->value = k;
            node* t = cur;
            node* p = t->parent;
            while(p != nullptr && p->value < t->value) {
                int temp = p->value;
                p->value = t->value;
                t->value = temp;
                t = p;
                p = t->parent;
            } 
            return true;
        }

        bool deleteKey(int k) {
            node* t = search_value(k);
            if(t == nullptr) {
                //cout<<"No such key found to delete!\n";
                return false;
            }
            increaseKey(t,inf);
            extractMax();
            size--;
            return true;
        }

        void print() {
            cout<<"Printing Binomial Heap...\n-----------------------\n";
            int len = rootlist.size();
            for(int i=0;i<len;i++) {
                cout<<"Binomial Tree, B"<<i+1<<": \n";
                levelOrder_tree_print(rootlist[i]);
                cout<<"-----------------------\n";
            }
        }

        int getSize() {
            return size;
        }

};

int main() {
    binomialHeap h;
    freopen("input.txt","r",stdin);
    string s;
    while(cin>>s) {
        if(s == "FIN") {
            cout<<"FindMax returned "<<h.findMax()<<'\n';
        }
        else if(s == "EXT") {
            cout<<"ExtractMax returned "<<h.extractMax()<<'\n';
        }
        else if(s == "INS") {
            int t;
            cin>>t;
            h.insert(t);
            cout<<"Inserted "<<t<<'\n';
        }
        else if(s == "PRI") {
            h.print();
        } 
        else if(s == "INC") {
            int x,y;
            cin>>x>>y;
            bool f = h.increaseKey(x,y);
            if(f) {
                cout<<"Increased "<<x<<". The updated value is "<<y<<'\n';
            }
            else {
                cout<<"Unsuccessful Increase key!\n";
            }
        }
        else {
            cout<<"Invalid Command.";
        }
    }
    return 0;
}