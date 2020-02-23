#include <bits/stdc++.h>

template < class KeyType, class ValueType, class Hash = std :: hash < KeyType > >


class HashMap{
public:
    using iterator = typename std :: list < std :: pair < const KeyType, ValueType > > :: iterator;
    using const_iterator = typename std :: list < std :: pair < const KeyType, ValueType > > :: const_iterator;
    HashMap(Hash hasher = Hash()) : hasher(hasher){
        table_size_ = 10;
        count_elements_ = 0;
        table.resize(table_size_);
    }
    HashMap(const std :: initializer_list < std :: pair < const KeyType, ValueType > > &l, Hash hasher = Hash()) : HashMap(hasher){
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
    int size() const{
        return count_elements_;
    }
    bool empty() const{
        return count_elements_ == 0;
    }
    void insert(std :: pair < const KeyType, ValueType > el);
    Hash hash_function() const{
        return hasher;
    }
    void erase(const KeyType key);
    iterator begin(){
        return all.begin();
    }
    iterator end(){
        return all.end();
    }
    const_iterator begin() const{
        return all.cbegin();
    }
    const_iterator end() const{
        return all.cend();
    }
    void clear();
    iterator find(const KeyType key);

    const_iterator find(const KeyType key) const;

    ValueType &operator[](const KeyType key);

    const ValueType &at(const KeyType key) const;

    HashMap &operator= (const HashMap &other);
private:
    int table_size_, count_elements_;
    std :: list < std :: pair < const KeyType, ValueType> > all;
    std :: vector < std :: list < typename std :: list < std :: pair < const KeyType, ValueType> > :: iterator > > table;
    Hash hasher;
    void rebuild(){
        table_size_ *= 2;
        table.clear();
        table.resize(table_size_);
        for (auto cur = all.begin(); cur != all.end(); cur++){
            table[hasher((*cur).first) % table_size_].push_back(cur);
        }
    }

};


template < class KeyType, class ValueType, class Hash >
typename std :: list < std :: pair < const KeyType, ValueType > > :: iterator HashMap < KeyType, ValueType, Hash > :: find(const KeyType key){
    int cur = hasher(key) % table_size_;
    for (auto tec : table[cur]){
        if ((*tec).first == key){
            return tec;
        }
    }
    return all.end();
}

template < class KeyType, class ValueType, class Hash >
typename std :: list < std :: pair < const KeyType, ValueType > > :: const_iterator HashMap < KeyType, ValueType, Hash > :: find(const KeyType key) const{
    int cur = hasher(key) % table_size_;
    for (auto tec : table[cur]){
        if ((*tec).first == key){
            return tec;
        }
    }
    return all.cend();
}

template < class KeyType, class ValueType, class Hash >
void HashMap < KeyType, ValueType, Hash > :: insert(std :: pair < const KeyType, ValueType > el){
    int cur = hasher(el.first) % table_size_;
    all.push_back(el);
    iterator it = all.end();
    it--;
    table[cur].push_back(it);
    count_elements_++;
    if (count_elements_ == table_size_){
        rebuild();
    }
}

template < class KeyType, class ValueType, class Hash >
void HashMap < KeyType, ValueType, Hash > :: erase(const KeyType key){
    int cur = hasher(key) % table_size_;
    for (auto it = table[cur].begin(); it != table[cur].end(); it++){
        if ((*(*it)).first == key){
            all.erase(*it);
            table[cur].erase(it);
            count_elements_--;
            break;
        }
    }
}

template < class KeyType, class ValueType, class Hash >
void HashMap < KeyType, ValueType, Hash > :: clear(){
    all.clear();
    table.clear();
    count_elements_ = 0;
    table_size_ = 10;
    table.resize(table_size_);
}

template < class KeyType, class ValueType, class Hash >
ValueType& HashMap < KeyType, ValueType, Hash > :: operator[](const KeyType key){
    auto cur = find(key);
    if (cur == all.end()){
        insert({key, {}});
        return (*find(key)).second;
    }
    return (*cur).second;
}

template < class KeyType, class ValueType, class Hash >
const ValueType& HashMap < KeyType, ValueType, Hash > :: at(const KeyType key) const{
    const_iterator cur = find(key);
    if (cur == all.cend()){
        throw std :: out_of_range("");
    }
    return (*cur).second;
}

template < class KeyType, class ValueType, class Hash >
HashMap < KeyType, ValueType, Hash >& HashMap < KeyType, ValueType, Hash > :: operator= (const HashMap &other){
    if (this == &other) {
        return *this;
    }
    clear();
    for (auto it : other){
        insert(it);
    }
    return *this;
}


