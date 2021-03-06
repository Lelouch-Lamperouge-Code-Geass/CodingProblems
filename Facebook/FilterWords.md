```
Given a list of words and a blacklist, filter all the words based on blacklist.
Word should be filtered if :
1. It is contains in blacklist
2. If it has one edit distance to any words in blacklist. 
    One edit distance means up to 1 Add/Change/Delete.
3. If any substring in the word satisfy 1 or 2.

Example:  
words = [facebook, facebok, facebo0k, faceboook, imgood, fffffacebokwithtail]    
blacklist = [facebook, admin]    
output = [imgood]    
```

# Solution

Below solution is not correct，since longest common string is not guarenteed to be a substring.
Substring is consecutive.

The correct solution should come from here. https://github.com/YangLiuNYU/LeetCode/blob/master/cplusplus/161_One_Edit_Distance.md

```cpp
#include <vector>
#include <iostream>
#include <sstream>
#include <cmath>
#include <cassert>


std::size_t LongestCommonString(const std::string & left, const std::string & right) {
  const std::size_t row_size(left.size()), col_size(right.size());
  std::size_t reval(0);
  std::vector< std::vector<std::size_t> > longest_include_curr( row_size+1, std::vector<std::size_t>(col_size+1, 0) );
  for (std::size_t i=1; i<=row_size; ++i) {
    for (std::size_t j=1; j<=col_size; ++j) {
      if (left[i-1] == right[j-1]) {
        longest_include_curr[i][j] = longest_include_curr[i-1][j-1] + 1;
      } else {
        longest_include_curr[i][j] = 0;
      }
      reval = std::max(reval, longest_include_curr[i][j]);
    }
  }
  return reval;
}

int LongestCommonSubstringLength(const std::string & word1, const std::string & word2) {
  const std::size_t word1_size(word1.size()), word2_size(word2.size());
  // This matrix stores the max common string length including that char
  int reval(0);
  std::vector< std::vector<int> > max_len(word1_size+1,std::vector<int>(word2_size+1,0));
  for (int i=1;i<=word1_size;++i) {
    for (int j=1;j<=word2_size;++j) {
      max_len[i][j] = std::max( std::max( max_len[i][j-1], max_len[i-1][j])
                                , word1[i-1]!=word2[j-1]? 0 : 1+ max_len[i-1][j-1]) ;
      reval = std::max(reval,max_len[i][j]);
    }
  }
  return reval;
}

std::vector<std::string> FilterWords(const std::vector<std::string> & words, const std::vector<std::string> & blacklist) {
  std::vector<std::string> reval;
  for (const std::string & word : words) {
    bool remove(false);
    for (const std::string & black_word : blacklist) {
      if ( std::abs((int)black_word.size() - LongestCommonSubstringLength(word,black_word) )<=1) {
        remove = true;
        break;
      }
    }
    if (!remove) reval.push_back(word);
  }
  return reval;
}

void UnitTest_LongestConsecutiveCommonSubstringLength() {
  assert(LongestCommonSubstringLength("facebook","facebok")==6); // "facebo"
  assert(LongestCommonSubstringLength("facebook","facebxok")==5); // "faceb"
}

void UnitTest_LongestCommonSubstringLength() {
  assert(LongestCommonSubstringLength("facebook","facebok")==7);
  assert(LongestCommonSubstringLength("facebook","facebo0ok")==8);
}

void UnitTest_FilterWords() {
  std::string words_arr[] = {"facebook", "facebok", "facebo0k", "faceboook", "imgood", "fffffacebokwithtail"};
  std::string blacklist_arr[] = {"facebook", "admin"};
  std::vector<std::string> words(std::begin(words_arr),std::end(words_arr));
  std::vector<std::string> blacklist(std::begin(blacklist_arr),std::end(blacklist_arr));
  std::vector<std::string> res = FilterWords(words,blacklist);
  std::ostringstream oss;
  for (const std::string & w : res) {
    oss << w <<' ';
  }
  assert(oss.str()=="imgood");
}

int main() {
  UnitTest_LongestConsecutiveCommonSubstringLength();
  UnitTest_LongestCommonSubstringLength();
  UnitTest_FilterWords();
  return 0;
}
```
