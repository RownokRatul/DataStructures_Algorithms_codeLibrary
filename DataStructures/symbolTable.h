#include<iostream>
#include<vector>
#include<string>
using namespace std;

#define NIL nullptr
#define ROOT_ID "1"
#define DEFAULT_SIZE 13

class symbolInfo {

        string name;
        string type;
        symbolInfo* next;

    public:

        symbolInfo(string nm, string tp) {
            name = nm;
            type = tp;
            next = NIL;
        }

        string getName() {
            return name;
        }

        string getType() {
            return type;
        }

        void setNameType(string nm, string tp) {
            name = nm;
            type = tp;
        }

        void setNext(symbolInfo* nxt) {
            next = nxt;
        }

        symbolInfo* getNext() {
            return next;
        }

        ~symbolInfo() {

        }

};

class scopeTable {

        int bucketSize;
        scopeTable* parentScope;
        vector<symbolInfo*> hashTable;
        string scopeID;
        int childScopeCount;

        unsigned int hash_sdbm(string s) {
            int len = s.length();
            unsigned int hash = 0;
            for(int i=0;i<len;i++) {
                //hash = (int)s[i] + hash*65599 + hash;
                hash = s[i] + (hash << 6) + (hash << 16) - hash;
            }
            return hash % bucketSize;
        }

        void generateScopeID() {
            if(parentScope == NIL) {
                scopeID = ROOT_ID;
            }
            else {
                if(parentScope->getChildScopeCount()) {
                    scopeID = parentScope->getScopeID() + ".";
                    scopeID += (char)(parentScope->getChildScopeCount() + 48);
                }
                else {
                    scopeID = parentScope->getScopeID() + ".1";
                }
                cout<<"New ScopeTable with ID# "<<scopeID<<" created.\n";
            }
        }

    public: 

        scopeTable(int size) {
            bucketSize = size;
            parentScope = NIL;
            hashTable.resize(bucketSize);
            childScopeCount = 0;
            generateScopeID();
        }

        scopeTable(int size, scopeTable* parent) {
            bucketSize = size;
            parentScope = parent;
            hashTable.resize(bucketSize);
            childScopeCount = 0;
            generateScopeID();
        }

        scopeTable* getParentScope() {
            return parentScope;
        }

        void setParentScope(scopeTable* t) {
            parentScope = t;
        }


        int getChildScopeCount() {
            return childScopeCount;
        }

        void incrementChildScopeCount() {
            childScopeCount++;
        }

        string getScopeID() {
            return scopeID; 
        }

        bool insert(string name, string type) {
            int hash = hash_sdbm(name);
            symbolInfo* cur = hashTable[hash];
            symbolInfo* prev = NIL;
            int i = 0;
            while(cur != NIL) {
                if(cur->getName() == name) {
                    // print message
                    cout<<"< "<<name<<" , "<<type<<" > already exists in Current ScopeTable.\n";
                    return false;
                }
                i++;
                prev = cur;
                cur = cur->getNext();
            }
            symbolInfo* toInsert = new symbolInfo(name, type);
            if(prev == NIL) {
                hashTable[hash] = toInsert;
            }
            else {
                prev->setNext(toInsert);
            }
            // print message
            cout<<"Inserted in ScopeTable# "<<scopeID<<" at position "<<hash<<", "<<i<<"\n";
            return true;
        }

        symbolInfo* lookup(string name) {
            int hash = hash_sdbm(name);
            symbolInfo* cur = hashTable[hash];
            int i = 0;
            while(cur != NIL) {
                if(cur->getName() == name) {
                    // print message
                    cout<<"Found in ScopeTable# "<<scopeID<<" in position "<<hash<<", "<<i<<"\n";
                    return cur;
                }
                i++;
                cur = cur->getNext();
            }
            return NIL;
        }

        bool deleteSymbol(string name) {
            int hash = hash_sdbm(name);
            symbolInfo* cur = hashTable[hash];
            symbolInfo* prev = NIL;
            int i = 0;
            while(cur != NIL) {
                if(cur->getName() == name) {
                    break;
                }
                i++;
                prev = cur;
                cur = cur->getNext();
            }
            if(cur == NIL) {
                // print message
                cout<<"Not Found\n";
                return false;
            }
            else {
                if(prev != NIL) {
                    cout<<"NOT  NIL\n";
                    prev->setNext(cur->getNext());
                }
                else {
                    cout<<"NIL\n";
                    hashTable[hash] = cur->getNext();
                }
                // print message
                cout<<"Found in ScopeTable# "<<scopeID<<" in position "<<hash<<", "<<i<<"\n";
                delete cur;
                cout<<"Deleted Entry "<<hash<<", "<<i<<" from Current Scope Table.\n";
            }
            return true;
        }

        void printHashTable() {
            cout<<"ScopeTable # "<<scopeID<<" :\n";
            for(int i=0;i<bucketSize;i++) {
                cout<<i<<"--> ";
                symbolInfo* cur = hashTable[i];
                while(cur != NIL) {
                    cout<<"< "<<cur->getName()<<" , "<<cur->getType()<<" > ";
                    cur = cur->getNext();
                }
                cout<<'\n';
            }
        }

        ~scopeTable() {

        }

};

class symbolTable {

        int bucketSize;
        scopeTable* currentScope;

    public:

        symbolTable(int size = DEFAULT_SIZE) {
            bucketSize = size;
            currentScope = new scopeTable(bucketSize);
        }

        void enterScope() {
            if(currentScope == NIL) {
                currentScope = new scopeTable(bucketSize);
            }
            else {
                currentScope->incrementChildScopeCount();
                scopeTable* nextScope = new scopeTable(bucketSize, currentScope);
                nextScope->setParentScope(currentScope);
                currentScope = nextScope;
            }
            
        }

        void exitScope() {
            if(currentScope == NIL) {
                cout<<"No Scope Exists.\n";
            }
            else {
                scopeTable* prevScope = currentScope->getParentScope();
                cout<<"Scope Table with ID# "<<currentScope->getScopeID()<<" removed.\n";
                delete currentScope;
                currentScope = prevScope;
            }
        }

        bool insert(string name, string type) {
            if(currentScope != NIL) {
                return currentScope->insert(name, type);
            }
            else {
                cout<<"No Scope Table.\n";
                return false;
            }
            
        }

        bool remove(string name) {
            if(currentScope != NIL) {
                cout<<"yessir"<<endl;
                return currentScope->deleteSymbol(name);
                cout<<"yessir"<<endl;
            }
            else {
                cout<<"No Scope Table.\n";
                return false;
            }
        }

        string getCurrentScopeID() {
            return currentScope->getScopeID();
        }

        symbolInfo* lookup(string name) {
            scopeTable* cur = currentScope;
            while(cur != NIL) {
                symbolInfo* result = cur->lookup(name);
                if(result != NIL) {
                    return result;
                }
                cur = cur->getParentScope();
            }
            // print message
            cout<<"Not Found.\n";
            return NIL;
        }

        void printCurrentScopeTable() {
            if(currentScope != NIL) {
                currentScope->printHashTable();
            }
        }

        void printAllScopeTable() {
            scopeTable* cur = currentScope;
            while(cur != NIL) {
                cur->printHashTable();
                cur = cur->getParentScope();
            }
        }

        ~symbolTable() {
            delete currentScope;
        }

};