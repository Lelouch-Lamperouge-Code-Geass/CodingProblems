//https://leilater.gitbooks.io/codingpractice/content/binary_search/top_k_frequent_words.html
//http://www.geeksforgeeks.org/find-the-k-most-frequent-words-from-a-file/

#include <string>
#include <vector>
#include <queue>
#include <unordered_map>
#include <iostream>

namespace Solution1 {
  typedef std::pair<std::string,int> Item;
  class WordCompare { // Functor to define comparison
  public:
    bool operator() (const Item & left, const Item & right) {
      if (left.second != right.second) {
        return left.second < right.second;
      } else {
        // left="b" && right=="a" ==> "ba" > "ab"  
        return left.first+right.first > right.first+left.first;
      }
    }
  };
  std::vector<std::string> topKFrequentWords(std::vector<std::string>& words, int k) {
    std::unordered_map<std::string,int> counter;
    for (const std::string & word : words) {
      ++ counter[word];
    }
    std::priority_queue<Item,std::vector<Item>,WordCompare> max_heap;// highest frequence at the end of vector
    for (const Item & item : counter) {
      max_heap.push(item);
    }
    std::vector<std::string> reval;
    while (!max_heap.empty() && k) {
      reval.push_back(max_heap.top().first);
      max_heap.pop();
      --k;
    }
    return reval;
  }
}

namespace Solution2 {
  class TrieNode {
  public:
    TrieNode() : m_children(26,nullptr),m_count(0) {}
  private:
    friend class Trie;
    // Its size depends on char case-sensitive or not, lets assume all lowercase here.
    // Can use hashmap here as well.
    std::vector< TrieNodePtr > m_children;
    int m_count; // how many words end here
  };
  typedef std::shared_ptr<TrieNode> TrieNodePtr;
  
  class Trie {
  public:
    Trie():m_root(new TrieNode()) {}
    void AddWord(const std::string & word) {
      TrieNodePtr curr = m_root;
      for (const char c : word) {
        int cix = c - 'a';
        if (!curr->m_children[cix]) curr->m_children[cix] = new TrieNode();
        curr = curr->m_children[cix];
      }
      ++ curr->m_count;
    }

  private:
    TrieNodePtr m_root;
  };

  std::vector<std::string> topKFrequentWords(std::vector<std::string>& words, int k) {
    Tire word_trie;
    for (const std::string & word : words) {
      word_trie.AddWord(word);
    }
    std::priority_queue<Item,std::vector<Item>,WordCompare> max_heap;// highest frequence at the end of vector
    for (const std::string : counter) {
      max_heap.push(item);
    }
    std::vector<std::string> reval;
    while (!max_heap.empty() && k) {
      reval.push_back(max_heap.top().first);
      max_heap.pop();
      --k;
    }
    return reval;
  }
  
}
int main() {
  std::string arr[] = {"ab","ba","ae","c","d","ab","ba","d","d"};
  std::vector<std::string> words(std::begin(arr),std::end(arr));
  std::vector<std::string> wl1 = Solution1::topKFrequentWords(words,3);
  for (const std::string & w : wl1) {
    std::cout << w << std::endl;
  }
  return 0;
}
