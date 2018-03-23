//
// Created by tianbao on 17-12-3.
//

#ifndef _ENTRY_H
#define _ENTRY_H

template <typename K,typename V>
class Entry {

public:

    Entry<K,V>* next;

    Entry(K k = K(),V v = V()):key(k),value(v),next(nullptr){}
    Entry(const Entry<K,V>& e):key(e.key),value(e.value),next(e.next){}
    bool operator<(const Entry<K,V>& temp) const {return key<temp.key;}
    bool operator>(const Entry<K,V>& temp) const {return key>temp.key;}
    bool operator==(const Entry<K,V>& temp) const {return key==temp.key && value == temp.value;}
    bool operator!=(const Entry<K,V>& temp) const {return !(*this == temp);}
    K getKey() const {return key;}
    V& getValue(){return value;}
    V setValue(V newValue) {V oldValue = value;value = newValue;return oldValue;}

private:

    K key;
    V value;

};
#endif //_ENTRY_H
