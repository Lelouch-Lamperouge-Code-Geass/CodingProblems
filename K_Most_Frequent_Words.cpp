//https://leilater.gitbooks.io/codingpractice/content/binary_search/top_k_frequent_words.html
//http://www.geeksforgeeks.org/find-the-k-most-frequent-words-from-a-file/


#include <iostream>
#include <vector>
#include <stack>
#include <unordered_set>
#include <memory>
#include <string>
#include <unordered_map>
#include <queue>
#include <fstream>
#include <algorithm>

class WordFrequency {
public:
  WordFrequency(const std::string & word, int frequency):m_word(word),m_frequency(frequency){}
  std::string m_word;
  int m_frequency;
};

class WordFrequencyCompare {
public:
  bool operator()(const WordFrequency& left, const WordFrequency& right) {
    return left.m_frequency > right.m_frequency;
  }
};

typedef std::priority_queue<WordFrequency,std::vector<WordFrequency>,WordFrequencyCompare> WordFrequencyPq;


namespace HashTableSolution {
std::vector<std::string> GetKMostFrequentWords(const std::vector<std::string> & words, const int k){
  std::unordered_map<std::string, int> counter;
  for (std::size_t i=0;i<words.size();++i) {
    std::string temp(words[i]);
    std::transform(temp.begin(),temp.end(),temp.begin(),::tolower);
    ++ counter[temp];
  }

  WordFrequencyPq pq;
  for (auto iter=counter.begin();iter!=counter.end();++iter) {
    pq.push(WordFrequency(iter->first,iter->second));
    if (pq.size()>k) pq.pop();
  }

  std::vector<std::string> reval;
  while(!pq.empty()) {
    std::cout << pq.top().m_word << ":" << pq.top().m_frequency << std::endl;
    reval.push_back(pq.top().m_word);
    pq.pop();
  }
  return reval;
}

}

namespace TrieSolution {

  class TrieNode;
  typedef TrieNode* TrieNodePtr;
  class TrieNode {
  public:
    TrieNode() : m_count(0),m_children(26,NULL){}
    ~TrieNode() {for (int i=0;i<26;++i) delete m_children[i];}
    int m_count;
    std::vector<TrieNodePtr> m_children;
  };


  class Trie {
  public:
    Trie():m_root(new TrieNode()){}
    ~Trie() {delete m_root;}
    void AddWord(const std::string & data){
      std::string word(data);
      std::transform(word.begin(), word.end(), word.begin(), ::tolower);
 TrieNodePtr curr(m_root);
      for (std::size_t i=0;i<word.size();++i) {
        if (!curr->m_children[word[i]-'a']) {
          curr->m_children[word[i]-'a'] = new TrieNode();
        }
        curr = curr->m_children[word[i]-'a'];
      }
      ++ curr->m_count;
    }

    std::vector<WordFrequency> GetWordStatistics() {
      std::vector<WordFrequency> reval;
      std::string temp("");
      CheckWithDfs(reval,m_root,temp);
      return reval;
    }
  private:
    void CheckWithDfs(std::vector<WordFrequency> & res,const TrieNodePtr & node, std::string temp) {
      if (!node) return ;
      if (node->m_count>0){res.push_back(WordFrequency(temp,node->m_count)); }
      for (int i=0;i<26;++i) {
        if (node->m_children[i]) {
          std::string new_temp(temp);
          new_temp.push_back('a'+i);
          CheckWithDfs(res,node->m_children[i],new_temp);

        }
      }
    }
    TrieNodePtr m_root;
  };

  std::vector<std::string> GetKMostFrequentWords(const std::vector<std::string> & words, const int k){
    Trie trie;
    for (std::size_t i=0;i<words.size();++i) {
      trie.AddWord(words[i]);
    }

    std::vector<WordFrequency> word_freq = trie.GetWordStatistics();
    WordFrequencyPq pq;
    for (auto iter=word_freq.begin();iter!=word_freq.end();++iter) {
      pq.push(WordFrequency(*iter));
      if (pq.size()>k) pq.pop();
    }

    std::vector<std::string> reval;
    while(!pq.empty()) {
      std::cout << pq.top().m_word << ":" << pq.top().m_frequency << std::endl;
      reval.push_back(pq.top().m_word);
      pq.pop();
    }
    return reval;
  }

}

std::vector<std::string> ReadWordsFromFile(const std::string & file_path) {
  std::ifstream file_reader;
  file_reader.open(file_path);
  std::vector<std::string> reval;
  if (file_reader.is_open()) {
    std::string word("");
    while (file_reader>>word) {
      reval.push_back(word);
    }
  }
  return reval;
}
int main(int argc,char* argv[]) {
  if (argc!=2) {
    std::cout << "usage: "<< argv[0] <<" <filename>\n" << std::endl;
  } else {
    const std::string file_path(argv[1]);
    const std::vector<std::string> & words = ReadWordsFromFile(file_path);
    std::vector<std::string>  res = TrieSolution::GetKMostFrequentWords(words,5);
    std::cout << "*************************************" << std::endl;
    res = HashTableSolution::GetKMostFrequentWords(words,5);
  }

  return 0;
}
