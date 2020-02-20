#include <bits/stdc++.h>

using namespace std;

template < class KeyType, class ValueType, class Hash = hash < KeyType > >

class HashMap{
private:
    int m, n;
    list < pair < const KeyType, ValueType> > all;
    vector < list < typename list < pair < const KeyType, ValueType> > :: iterator > > table;
    Hash hasher;
public:
    using iterator = typename list < pair < const KeyType, ValueType > > :: iterator;
    using const_iterator = typename list < pair < const KeyType, ValueType > > :: const_iterator;
    HashMap(Hash hasher = Hash()) : hasher(hasher){
        m = 10;
        n = 0;
        table.resize(m);
    }
    HashMap(const initializer_list < pair < const KeyType, ValueType > > &l, Hash hasher = Hash()) : HashMap(hasher){
        for (auto it : l){
            insert(it);
        }
    }
    template < typename iter >
    HashMap(iter l, iter r, Hash hasher = Hash()) : HashMap(hasher){
        for (auto it = l; it != r; ++it){
            insert(*it);
        }
    }
    const int size() const{
        return n;
    }
    const bool empty() const{
        return n == 0;
    }
    void insert(pair < const KeyType, ValueType > el){
        int cur = hasher(el.first) % m;
        all.push_back(el);
        iterator it = all.end();
        it--;
        table[cur].push_back(it);
        n++;
        if (n == m){
            rebuild();
        }
    }
    void print(){
        for (int i = 0; i < m; i++){
            cout << i << endl;
            for (auto cur : table[i]){
                cout << (*cur).first << " " << (*cur).second << endl;
            }
            cout << endl;
        }
    }
    const Hash hash_function() const{
        return hasher;
    }
    void erase(const KeyType key){
        int cur = hasher(key) % m;
        for (auto it = table[cur].begin(); it != table[cur].end(); it++){
            if ((*(*it)).first == key){
                all.erase(*it);
                table[cur].erase(it);
                n--;
                break;
            }
        }
    }
    iterator begin(){
        return all.begin();
    }
    iterator end(){
        return all.end();
    }
    const_iterator begin() const{
        return all.begin();
    }
    const_iterator end() const{
        return all.end();
    }
    void clear(){
        all.clear();
        table.clear();
        n = 0;
        m = 10;
        table.resize(10);
    }
    void rebuild(){
        m *= 2;
        table.clear();
        table.resize(m);
        for (auto cur = all.begin(); cur != all.end(); cur++){
            table[hasher((*cur).first) % m].push_back(cur);
        }
    }
    iterator find(const KeyType key){
        int cur = hasher(key) % m;
        for (auto tec : table[cur]){
            if ((*tec).first == key){
                return tec;
            }
        }
        return all.end();
    }
    const_iterator find(const KeyType key) const{
        int cur = hasher(key) % m;
        for (auto tec : table[cur]){
            if ((*tec).first == key){
                return tec;
            }
        }
        return all.end();
    }
    ValueType &operator[](const KeyType key){
        auto cur = find(key);
        if (cur == all.end()){
            insert({key, {}});
            return (*find(key)).second;
        }
        return (*cur).second;
    }
    const ValueType &at(const KeyType key) const{
        auto cur = find(key);
        if (cur == all.end()){
            throw out_of_range("");
        }
        return (*cur).second;
    }
    HashMap &operator= (const HashMap &other) {
        if (this == &other) {
            return *this;
        }
        clear();
        for (auto it : other){
            insert(it);
        }
        return *this;
    }
};

