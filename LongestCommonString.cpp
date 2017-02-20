/***
http://www.geeksforgeeks.org/longest-common-substring/
 ***/
#include <iostream>
#include <vector>
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


void UnitTest() {
  assert(LongestCommonString("facebook","facebok") == 6);
  assert(LongestCommonString("GeeksforGeeks","GeeksQuiz") == 5);
  assert(LongestCommonString("abcdxyz","xyzabcd") == 4);
  assert(LongestCommonString("zxabcdezy","yzabcdezx") == 6);
}

int main() {
  UnitTest();
  return 0;
}
