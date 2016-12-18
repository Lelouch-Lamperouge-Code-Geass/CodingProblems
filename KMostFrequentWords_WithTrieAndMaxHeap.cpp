#include <iostream>
#include <vector>
#include <memory>
#include <queue>
#include <string>
#include <fstream>
#include <algorithm> // std::transform
#include <cctype> // to lower

/*
You can use HashMap to record the word and count, and eventually iterate the HashMap
and push word and count item into a MaxHeap. This is the most intuitive solution.
But the downside is that if you use the whole word as Key, then HashMap will cost more
memory than a trie.
For example, suppose input is ["a","ab","ac","abc","abd"], let's say one char cost one byte
(which is actually true in most scenarios), the HashMap will cost 11 bytes at least(why at least?
don't forget load factor of HashMap),while trie will only cost 5 bytes. 
*/

namespace {
  const int MAX_CHAR(26);
}
class TrieNode {
public:
  TrieNode():m_children(MAX_CHAR,nullptr),m_count(0){ }
private:
  friend class Trie;
  std::vector< TrieNode* > m_children;
  int m_count; // count the words on this node
};
typedef  TrieNode* TrieNodePtr;

class WordCounter {
public:
  WordCounter(const std::string & w,int c):m_word(w),m_count(c){}
  std::string m_word;
  int m_count;
};

class WordCounterCompare {
public:
  bool operator()(const WordCounter & left, const WordCounter & right) {
    return left.m_count < right.m_count;
  }
};

class Trie {
public:
  Trie(){
    m_root = new TrieNode();
  }
  void AddWord(const std::string & word) {
    TrieNodePtr curr(m_root);
    for (char c : word) {
      if(!curr->m_children[c-'a'])
        curr->m_children[c-'a'] = new TrieNode();
      curr = curr->m_children[c-'a'];
    }
    ++ curr->m_count;
  }
  std::vector<WordCounter> GetWordCount() {
    std::vector<WordCounter> reval;
    TrieNodePtr curr(m_root);
    std::string temp("");
    CheckWithDfs(reval,curr,temp);
    return reval;
  }
private:
  void CheckWithDfs(std::vector<WordCounter> & reval,const TrieNodePtr & curr,std::string & temp) {
    if (!curr) return;
    if (curr->m_count>0) { // has word here
      reval.push_back(WordCounter(temp,curr->m_count));
    }
    for (int i=0;i<MAX_CHAR;++i) {
      temp.push_back('a'+i);
      CheckWithDfs(reval,curr->m_children[i],temp);
      temp.pop_back();
    }
  }
  TrieNodePtr m_root;
};

std::vector<WordCounter> MostFrequentWords(const std::vector<std::string> & words,int k) {
  Trie trie;
  for (const std::string & word : words) {
    trie.AddWord(word);
  }
  std::vector<WordCounter> word_count = trie.GetWordCount();
  std::priority_queue<WordCounter,std::vector<WordCounter>,WordCounterCompare> max_heap(word_count.begin(),word_count.end());
  std::vector<WordCounter> reval;
  for (int i=0;i<k && !max_heap.empty();++i) {
    reval.push_back(max_heap.top());
    max_heap.pop();
  }
  return reval;
}


int main(int argc, char* argv[]) {
  if (argc != 2) {
    std::cout << "usage: "<< argv[0] <<" <filename>\n" << std::endl;
  } else {
    std::ifstream my_file;
    my_file.open(argv[1]);
    if (my_file.is_open()) {
      std::vector<std::string> words;
      std::string word;
      while (my_file>>word) {
        std::transform(word.begin(), word.end(), word.begin(), ::tolower);
        words.push_back(word);
      }
      std::vector<WordCounter> res =  MostFrequentWords(words,5);
      for (const WordCounter & wc : res) {
        std::cout << wc.m_word << " : " << wc.m_count << std::endl;
      }
    } else {
      std::cout << "Can't open file : " << argv[1] << std::endl;
    }
  }
  return 0;
}
