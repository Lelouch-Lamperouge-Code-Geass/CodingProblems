
```cpp
#include <list>
#include <iostream>
#include <cassert>



class ModFiveIterator {
public:
  typedef std::list<int>::iterator ListIterator;
  ModFiveIterator(const ListIterator & begin, const ListIterator & end)
    : m_pos(begin), m_end(end), m_peeked(false) {
  }

  bool HasNext() {
    TryPeek();
    return m_peeked;
  }

  int Next() {
    TryPeek();
    m_peeked = false;
    return m_peeked_val;
  }

  void Remove() {
    Next();
  }
private:
  void TryPeek() {
    // if m_peeked == true, do nothing
    while (!m_peeked && m_pos < m_end) {
        if ( (*m_pos) % 5 == 0) {
          m_peeked = true;
          m_peeked_val = *m_pos;
        }
        ++ m_pos;
    }
  }
  bool m_peeked;
  int m_peeked_val;
  ListIterator m_pos;
  ListIterator m_end;
};

void TestNextAndHasNext() {
  std::list<int> values ;

  for (int i = 0; i <= 20; ++i) {
    values.push_back(i);
  }

  ModFiveIterator iter(values.begin(), values.end());

  assert(iter.HasNext() == true);
  assert(iter.Next() == 0);

  assert(iter.HasNext() == true);
  assert(iter.Next() == 5);

  assert(iter.HasNext() == true);
  assert(iter.Next() == 10);

  assert(iter.HasNext() == true);
  assert(iter.Next() == 15);

  assert(iter.HasNext() == true);
  assert(iter.Next() == 20);

  assert(iter.HasNext() == false);

}
void TestRemove() {
  std::list<int> values ;

  for (int i = 0; i <= 20; ++i) {
    values.push_back(i);
  }

  ModFiveIterator iter(values.begin(), values.end());

  assert(iter.HasNext() == true);
  assert(iter.Next() == 0);

  assert(iter.HasNext() == true);
  assert(iter.Next() == 5);

  iter.Remove();

  iter.Remove();

  assert(iter.HasNext() == true);
  assert(iter.Next() == 20);

  assert(iter.HasNext() == false);

}


int main() {
  TestNextAndHasNext();
  TestRemove();
  return 0;
}
```
