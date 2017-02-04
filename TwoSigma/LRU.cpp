#include <string>
#include <list>
#include <unordered_map>
#include <cassert>
#include <iostream>

template<typename KeyType,typename ValueType>
class LRUCache {
  typedef typename std::pair<KeyType,ValueType> ListItem;
public:
  LRUCache(const std::size_t capacity) : m_capacity(capacity){    }
  
  ValueType Get(const KeyType & key_type);
  void Put(const KeyType & key_type, const ValueType & value_type);
private:
  // Touch an item in the list at the front of the list,
  // and update m_mapper for this Key.
  // If key not exist, do nothing.
  void Touch(const KeyType & key_type);
  std::size_t m_capacity;
  std::list<ListItem> m_list;
  typedef typename std::list<ListItem>::iterator ListItemPosition;
  std::unordered_map<KeyType,ListItemPosition> m_mapper;
};


template<typename KeyType,typename ValueType>
void LRUCache<KeyType,ValueType>::Touch(const KeyType & key_type) {
  if (m_mapper.count(key_type)==0) {
    return ;
  } else {
    ListItemPosition list_pos = m_mapper[key_type];
    m_list.push_front(*list_pos);
    m_list.erase(list_pos);
    m_mapper[key_type] = m_list.begin();
  }
}

template<typename KeyType,typename ValueType>
ValueType LRUCache<KeyType,ValueType>::Get(const KeyType & key_type) {
  if (m_mapper.count(key_type)==0) {
    return ValueType();
  } else {
    Touch(key_type);
    return m_list.front().second;
  }
}



template<typename KeyType,typename ValueType>
void LRUCache<KeyType,ValueType>::Put(const KeyType & key_type, const ValueType & value_type) {
  if (m_mapper.count(key_type)!=0) {
    Touch(key_type);
    m_list.front().second = value_type;
  } else {
    if (m_list.size()==m_capacity) {
      m_mapper.erase(m_list.back().first);
      m_list.pop_back();
    }
    m_list.push_front(ListItem(key_type,value_type));
    m_mapper[key_type] = m_list.begin();
  }
}


void UnitTest() {
  LRUCache<int,std::string> cache(3);
  cache.Put(1,"1"); // 1
  cache.Put(2,"2"); // 2,1
  cache.Put(3,"3"); // 3,2,1
  cache.Put(4,"4"); // 4,3,2
  
  assert(cache.Get(1) == ""); // 4,3,2
  assert(cache.Get(2) == "2"); // 2,4,3
  cache.Put(5,"5"); // 5,2,4
  assert(cache.Get(3) == ""); // 5,2,4
  assert(cache.Get(4) == "4"); // 4,5,2
  cache.Put(2,"II");
  assert(cache.Get(2) == "II"); // II,4,5
}

int main() {
  UnitTest();
  return 0;
}
