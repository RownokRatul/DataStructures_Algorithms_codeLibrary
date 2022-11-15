#include<bits/stdc++.h>
using namespace std;

typedef long long ll;

int null = -1;
int MAX_ITERATION = 1000;

void randomWordGenerator(string words[], int n, int len) {
    map<string,int> mp;
    int count = 0;
    srand(time(0));
    while(count < n) {
        string s = "";
        for(int i=0;i<len;i++) {
            s += (rand()%26) + 'a';
        }
        if(mp.find(s) == mp.end()) {
            count++;
            mp.insert(make_pair(s,count));
            words[count-1] = s;
        }
    }
} 

int mapLetter(char c) {
    return (int) (c-'a'+1);
}

int generateKey(string& s) {
    int k = 0;
    int l = s.length();
    for(int i=0;i<l;i++) {
        k += mapLetter(s[i]);
    }
    return k;
}

int polynomialRollingHash(string s, int l, int m) {
    ll p = 31;
    ll mul = 1;
    ll hash = 0;
    for(int i=0;i<l;i++) {
        hash = (hash + (mapLetter(s[i])*mul)) % m;
        mul *= p;
    }
    return hash;
}

int multiplicativeHash(string s, int l, int m) {
    double A = 0.6180339887;
    int k = generateKey(s);
    double rem = k*1.0*A - (int)(k*1.0*A);
    return (int)(rem*m);
}

int djb2Hash(string s,int l, int m) {
    ll h = 5381;
    for(int i=0;i<l;i++) {
        h = h*33 + mapLetter(s[i]);
    }
    return h%m;
}

int auxHashing1(string s, int l, int m) {
    int k = generateKey(s);
    return k%m + 1;
}

int auxHashing2(string s,int l, int m) {
    int k = generateKey(s);
    int p = 31;
    return p - (k%p);
}

class hashTable {
        int n;
        int c1;
        int c2;
        vector<pair<string,int> > *separateChaining;
        vector<pair<string,int> > doubleHash;
        vector<pair<string,int> > customProbing;

        int (*hash) (string, int, int);
        int (*auxHash) (string, int, int);

    public:

        hashTable(int num, int (*h) (string, int, int), int (*aux) (string, int, int)) {
            n = num;
            c1 = 1;
            c2 = 1;
            hash = h;
            auxHash = aux;
            separateChaining = new vector<pair<string,int> > [n];
            for(int i=0;i<n;i++) {
                separateChaining[i].push_back(make_pair("",null));
                doubleHash.push_back(make_pair("",null));
                customProbing.push_back(make_pair("",null));
            }
        }

        bool insertElementSC(string s, int i, int& colSC) {
            int idx = hash(s, s.length(), n);
            colSC = 0;
            if(separateChaining[idx][0].second != null) {
                colSC++;
                separateChaining[idx].push_back(make_pair(s,i));
            }
            else {
                separateChaining[idx][0] = make_pair(s,i);
            }
            return true;
        }

        bool insertElementDH(string s, int i, int& colDH) {
            int idx = hash(s, s.length(), n);
            int aux = auxHash(s, s.length(), n);
            colDH = 0;
            for(int i=0;i<MAX_ITERATION;i++) {
                int newIDX = (idx + i*aux) % n;
                if(doubleHash[newIDX].second == null) {
                    doubleHash[newIDX] = make_pair(s,i);
                    return true;
                }
                colDH = 1;
            }
            return false;
        }

        bool insertElementCP(string s,int i, int& colCP) {
            int idx = hash(s, s.length(), n);
            int aux = auxHash(s, s.length(), n);
            colCP = 0;
            for(int i=0;i<MAX_ITERATION;i++) {
                int newIDX = (idx + c1*i*aux + c2*i*i) % n;
                if(customProbing[newIDX].second == null) {
                    customProbing[newIDX] = make_pair(s,i);
                    return true;
                }
                colCP = 1;
            }
            return false;
        }

        int searchElementSC(string s, int& count) {
            count = 0;
            int idx = hash(s, s.length(), n);
            for(pair<string,int> t : separateChaining[idx]) {
                count++;
                if(t.first == s) {
                    return t.second;
                }
            }
            return -1;
        }

        int searchElementDH(string s, int& count) {
            count = 0;
            int idx = hash(s, s.length(), n);
            int aux = auxHash(s, s.length(), n);
            for(int i=0;i<MAX_ITERATION;i++) {
                count++;
                int newIDX = (idx + i*aux) % n;
                if(doubleHash[newIDX].first == s) {
                    return doubleHash[newIDX].second;
                }
            }
            return -1;
        }

        int searchElementCP(string s, int& count) {
            count = 0;
            int idx = hash(s, s.length(), n);
            int aux = auxHash(s, s.length(), n);
            for(int i=0;i<MAX_ITERATION;i++) {
                count++;
                int newIDX = (idx + c1*i*aux + c2*i*i) % n;
                if(customProbing[newIDX].first == s) {
                    return customProbing[newIDX].second;
                }
            }
            return -1;
        }

        bool deleteElementSC(string s) {
            int idx = hash(s,s.length(),n);
            vector<pair<string,int> >::iterator it = separateChaining[idx].begin();
            while(it != separateChaining[idx].end()) {
                if(it->first == s) {
                    separateChaining[idx].erase(it);
                    if(!separateChaining[idx].size()) {
                        separateChaining[idx].push_back(make_pair("",null));
                    }
                    return true;
                }
            }
            return false;
        }

        bool deleteElementDH(string s) {
            int idx = hash(s, s.length(), n);
            int aux = auxHash(s, s.length(), n);
            for(int i=0;i<MAX_ITERATION;i++) {
                int newIDX = (idx + i*aux) % n;
                if(doubleHash[newIDX].first == s) {
                    doubleHash[newIDX] = make_pair("",null);
                    return true;
                }
            }
            return false;
        }

        bool deleteElementCP(string s) {
            int idx = hash(s, s.length(), n);
            int aux = auxHash(s, s.length(), n);
            for(int i=0;i<MAX_ITERATION;i++) {
                int newIDX = (idx + c1*i*aux + c2*i*i);
                if(customProbing[newIDX].first == s) {
                    customProbing[newIDX] = make_pair("",null);
                    return true;
                }
            }
            return false;
        }

        void show(int f) {
            cout<<"SC: \n";
            for(int i=0;i<f;i++) {
                for(pair<string,int> t : separateChaining[i]) {
                    cout<<t.first<<" "<<t.second<<'\n';
                }
            }
            cout<<"DH: \n";
            for(int i=0;i<f;i++) {
                cout<<doubleHash[i].first<<" "<<doubleHash[i].second<<'\n';
            }
            cout<<"CP: \n";
            for(int i=0;i<f;i++) {
                cout<<customProbing[i].first<<" "<<customProbing[i].second<<'\n';
            }
        }

};


int main() {
    int n;
    cin>>n;
    string words[10005];
    randomWordGenerator(words, 10000, 7);
    hashTable table1(n, polynomialRollingHash, auxHashing1);
    hashTable table2(n,djb2Hash,auxHashing1);

    int collision;
    int colHash1[3];
    int colHash2[3];
    for(int i=0;i<3;i++) {
        colHash1[i] = 0;
        colHash2[i] = 0;
    }

    //insert all words.
    for(int i=0;i<10000;i++) {
        table1.insertElementSC(words[i],i,collision);
        colHash1[0] += collision;
        table1.insertElementDH(words[i],i,collision);
        colHash1[1] += collision;
        table1.insertElementCP(words[i],i,collision);
        colHash1[2] += collision;

        table2.insertElementSC(words[i],i,collision);
        colHash2[0] += collision;
        table2.insertElementDH(words[i],i,collision);
        colHash2[1] += collision;
        table2.insertElementCP(words[i],i,collision);
        colHash2[2] += collision;
    }

    //random 1000 words search
    int taken[10000];
    double searchHash1[3];
    double searchHash2[3];
    for(int i=0;i<3;i++) {
        searchHash1[i] = 0;
        searchHash2[i] = 0;
    }
    fill(taken,taken+10000,0);
    int count = 0;
    srand(time(0));
    while(count < 1000) {
        int idx = rand() % 10000;
        if(!taken[idx]) {
            count++;
            int probe;
            table1.searchElementSC(words[idx], probe);
            searchHash1[0] += probe*1.0;
            table1.searchElementDH(words[idx], probe);
            searchHash1[1] += probe*1.0;
            table1.searchElementCP(words[idx], probe);
            searchHash1[2] += probe*1.0;

            table2.searchElementSC(words[idx], probe);
            searchHash2[0] += probe*1.0;
            table2.searchElementDH(words[idx], probe);
            searchHash2[1] += probe*1.0;
            table2.searchElementCP(words[idx], probe);
            searchHash2[2] += probe*1.0;
        }
    }
    for(int i=0;i<3;i++) {
        searchHash1[i] /= 1000.0;
        searchHash2[i] /= 1000.0;
    }

    cout<<"\n";
    cout<<"***Generated Result are respectively: Separate Chaining, Double Hashing, Custom Probing.***\n";
    cout<<"For Polynomial Rolling Hash: "<<endl;
    cout<<"Number of Collisions:\t"<<"Average Probes: \n";
    for(int i=0;i<3;i++) {
        cout<<colHash1[i]<<"\t\t\t\t"<<searchHash1[i]<<'\n';
    }
    cout<<"For DJB2 Hash: "<<endl;
    cout<<"Number of Collisions:\t"<<"Average Probes: \n";
    for(int i=0;i<3;i++) {
        cout<<colHash2[i]<<"\t\t\t\t"<<searchHash2[i]<<'\n';
    }
    cout<<"\n";
    return 0;
}