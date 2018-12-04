//
//  Dictionary.h
//
//  Created by Eiji Adachi Medeiros Barbosa
//

#ifndef Dictionary_h
#define Dictionary_h

#include <unordered_map>

template <typename K, typename V>
class Dictionary {
private:
    std::unordered_map<K, V> data;
    
public:
    Dictionary();
    
    ~Dictionary();
    
    V get(const K key);
    
    bool contains(const K key);
    
    bool put(const K key, const V value);
    
    bool remove(const K key);
    
    int getQuantity();
    
    bool isEmpty();
    
    void print();
};

template <typename K, typename V>
Dictionary<K, V>::Dictionary()
{
}

template <typename K, typename V>
Dictionary<K, V>::~Dictionary()
{
}

template <typename K, typename V>
V Dictionary<K, V>::get(const K key)
{
    return (V)data.at(key); 
}

template <typename K, typename V>
bool Dictionary<K, V>::contains(const K key)
{
    return data.find(key) != data.end();
}

template <typename K, typename V>
bool Dictionary<K, V>::put(const K key, const V value)
{
    auto f = data.find(key);
    if( f != data.end() )
    {
        f->second = value;
    }
    else
    {
        data.insert( {key, value} );
    }
    
    return true;
}

template <typename K, typename V>
bool Dictionary<K, V>::remove(const K key)
{
    if( !this->contains(key) )
    {
        return false;
    }
    
    data.erase( key );
    return true;
}

template <typename K, typename V>
int Dictionary<K, V>::getQuantity()
{
    return data.size();
}

template <typename K, typename V>
bool Dictionary<K, V>::isEmpty()
{
    return data.empty();
}

template <typename K, typename V>
void Dictionary<K, V>::print()
{
    std::cout << "{";
    for ( auto it = data.begin(); it != data.end(); ++it )
    {
        std::cout << " " << it->first << ":" << it->second;
    }
    std::cout << " }\n";
}

#endif /* Dictionary_h */
