#pragma once

#include <vector>
#include <iterator>
#include <list>
#include <stdexcept>

template<class KeyType, class ValueType, class Hash = std::hash<KeyType>>
class HashMap {
 public:
    using KeyValuePair = typename std::pair<const KeyType, ValueType>;
    using iterator = typename std::list<KeyValuePair>::iterator;
    using const_iterator = typename std::list<KeyValuePair>::const_iterator;

    HashMap(Hash hasher_ = Hash()) : hasher_(hasher_) {
        table_size_ = startSize_;
        count_elements_ = 0;
        table.resize(table_size_);
    }

    HashMap(const std::initializer_list<KeyValuePair>& init,
            Hash hasher_ = Hash()) : HashMap(hasher_) {
        for (auto const &current_element : init) {
            insert(current_element);
        }
    }

    template <typename Inputit>
    HashMap(Inputit first, Inputit last, Hash hasher_ = Hash())
            : HashMap(hasher_) {
        for (auto current_iter = first; current_iter != last; ++current_iter) {
            insert(*current_iter);
        }
    }

    size_t size() const {
        return count_elements_;
    }

    bool empty() const {
        return count_elements_ == 0;
    }

    void insert(const KeyValuePair& new_element);

    Hash hash_function() const {
        return hasher_;
    }

    void erase(const KeyType& key);

    iterator begin() {
        return all.begin();
    }

    iterator end() {
        return all.end();
    }

    const_iterator begin() const {
        return all.cbegin();
    }

    const_iterator end() const {
        return all.cend();
    }

    void clear();

    iterator find(const KeyType& key);

    const_iterator find(const KeyType& key) const;

    ValueType& operator[](const KeyType& key);

    const ValueType& at(const KeyType& key) const;

    HashMap& operator=(const HashMap& other);

 private:
    size_t table_size_;
    size_t count_elements_;
    const size_t startSize_ = 10;
    const size_t changeSize_ = 2;
    std::list<KeyValuePair> all;
    std::vector<std::list<iterator>> table;
    Hash hasher_;
    void rebuild();
};


template<class KeyType, class ValueType, class Hash>
auto HashMap<KeyType, ValueType, Hash>::find(
        const KeyType& key) -> iterator {
    size_t index = hasher_(key) % table_size_;
    for (auto const &element : table[index]) {
        if (element->first == key) {
            return element;
        }
    }
    return all.end();
}

template<class KeyType, class ValueType, class Hash>
auto HashMap<KeyType, ValueType, Hash>::find(
        const KeyType& key) const -> const_iterator {
    size_t index = hasher_(key) % table_size_;
    for (auto const &element : table[index]) {
        if (element->first == key) {
            return element;
        }
    }
    return all.cend();
}

template<class KeyType, class ValueType, class Hash>
void HashMap<KeyType, ValueType, Hash>::insert(
        const KeyValuePair& new_element) {
    size_t index = hasher_(new_element.first) % table_size_;
    all.push_back(new_element);
    table[index].push_back(std::prev(all.end()));
    count_elements_++;
    if (count_elements_ == table_size_) {
        rebuild();
    }
}

template<class KeyType, class ValueType, class Hash>
void HashMap<KeyType, ValueType, Hash>::erase(const KeyType& key) {
    size_t index = hasher_(key) % table_size_;
    for (auto iter = table[index].begin(); iter != table[index].end();
            ++iter) {
        if ((*iter)->first == key) {
            all.erase(*iter);
            table[index].erase(iter);
            count_elements_--;
            break;
        }
    }
}

template<class KeyType, class ValueType, class Hash>
void HashMap <KeyType, ValueType, Hash>::clear() {
    all.clear();
    table.clear();
    count_elements_ = 0;
    table_size_ = startSize_;
    table.resize(table_size_);
}

template<class KeyType, class ValueType, class Hash>
ValueType& HashMap<KeyType, ValueType, Hash>::operator[](
        const KeyType& key) {
    auto result = find(key);
    if (result == all.end()) {
        insert({key, {}});
        return find(key)->second;
    }
    return result->second;
}

template<class KeyType, class ValueType, class Hash>
const ValueType& HashMap<KeyType, ValueType, Hash>::at(
        const KeyType& key) const {
    const_iterator result = find(key);
    if (result == all.cend()) {
        throw std::out_of_range("");
    }
    return result->second;
}

template<class KeyType, class ValueType, class Hash>
HashMap<KeyType, ValueType, Hash>&
        HashMap<KeyType, ValueType, Hash>::operator=(const HashMap &other) {
    if (this == &other) {
        return *this;
    }
    clear();
    for (auto const &iter : other) {
        insert(iter);
    }
    return *this;
}

template<class KeyType, class ValueType, class Hash>
void HashMap<KeyType, ValueType, Hash>::rebuild() {
    table_size_ *= changeSize_;
    table.clear();
    table.resize(table_size_);
    for (auto iter = all.begin(); iter != all.end(); ++iter) {
        size_t index = hasher_(iter->first) % table_size_;
        table[index].push_back(iter);
    }
}
