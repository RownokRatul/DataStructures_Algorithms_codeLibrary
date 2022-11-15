#include<iostream>
#include<vector>
using namespace std;

int inf = INT_MAX;
int MAXSIZE = 500000;

template <class T> class Heap {
    vector<T> v;
    int mxSize;
    int heapSize;
    
public:

    Heap(vector<T> vec,int n) {
        heapSize = n;
        mxSize = MAXSIZE;
        for(int i=0;i<n;i++) {
            v.push_back(vec[i]);
        }
    }

    void maxHeapify(int idx) {
        int left = leftChild(idx);
        int right = rightChild(idx);
        int largest;
        largest = (left < v.size() && v[left] > v[idx]) ? left : idx;
        largest = (right < v.size() && v[right] > v[largest]) ? right : largest;
        if(largest != idx) {
            swap(v[idx],v[largest]);
            maxHeapify(largest);
        }
    }
    
    void buildMaxHeap() {
        for(int i=(int)(v.size()/2);i>=0;i--) {
            maxHeapify(i);
        }
    }
    
    int parent(int idx) {
        return ((idx+1)/2)-1;
    }
    
    int leftChild(int idx) {
        return 2*(idx+1)-1;
    }
    
    int rightChild(int idx) {
        return 2*(idx+1);
    }

    void heapIncreaseKey(int idx,int key) {
        if(v[idx] > key) {
            cout<<"Key is already larger."<<endl;
        }
        else {
            v[idx] = key;
            while(idx >= 0 && parent(idx) >= 0 && v[parent(idx)] < v[idx]) {
                swap(v[idx],v[parent(idx)]);
                idx = parent(idx);
            }
        }
    }
    
    T getMax() {
        if(heapSize) {
            return v[0];
        }
        cout<<"Heap Empty"<<endl;
        return NULL;
    }

    void insert(T num) {
        if(heapSize == mxSize) {
            cout<<"Heap Overflow while inserting "<<num<<endl;
        }
        else {
            v.push_back((T)(-inf));
            heapIncreaseKey(heapSize++,num);
        }
    }
    
    void deleteMaxKey() {
        if(heapSize < 0) {
            cout<<"Heap Underflow!"<<endl;
        }
        else {
            swap(v[0],v[heapSize-1]);
            heapSize--;
            v.pop_back();
            maxHeapify(v,0);
        }
    }
    
    int size() {
        return heapSize;
    }
    
    bool empty() {
        return !heapSize;
    }

    vector<T> heapsort() {
        buildMaxHeap();
        vector<T> temp;
        for(int i = (int)(v.size()-1);i>=0;i--) {
            swap(v[i],v[0]);
            temp.push_back(v[i]);
            v.pop_back();
            maxHeapify(0);
        }
        v.clear();
        for(int x:temp) {
            v.push_back(x);
        }
        return v;
    }
};
