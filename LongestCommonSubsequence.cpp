/***
The longest common subsequence (LCS) problem is the problem of finding the longest subsequence common to all sequences 
in a set of sequences (often just two sequences). It differs from problems of finding common substrings: 
unlike substrings, subsequences are not required to occupy consecutive positions within the original sequences.
***/

#include <vector>
#include <cassert>
#include <iostream>

std::size_t LongestCommonSubsequence(const std::string & left, const std::string & right) {
  const std::size_t row_size(left.size()), col_size(right.size());
  std::size_t reval(0);
  std::vector< std::vector<std::size_t> > longest_so_far( row_size+1, std::vector<std::size_t>(col_size+1, 0) );
  for (std::size_t i=1; i<=row_size; ++i) {
    for (std::size_t j=1; j<=col_size; ++j) {
      if (left[i-1] == right[j-1]) {
        longest_so_far[i][j] = longest_so_far[i-1][j-1] + 1;
      } else {
        longest_so_far[i][j] = 0;
      }
      longest_so_far[i][j] = std::max(longest_so_far[i-1][j], longest_so_far[i][j-1]);
      if (left[i-1] == right[j-1]) longest_so_far[i][j] = std::max(longest_so_far[i][j], longest_so_far[i-1][j-1] + 1);
      reval = std::max(reval, longest_so_far[i][j]);
    }
  }
  return reval;
}

void UnitTest() {
  assert(LongestCommonSubsequence("facebook","facebok") == 7);
  assert(LongestCommonSubsequence("GeeksforGeeks","GeeksQuiz") == 5);
  assert(LongestCommonSubsequence("abcdxyz","xyzabcd") == 4);
  assert(LongestCommonSubsequence("zxabcdezy","yzabcdezx") == 7); // zabcdez
}

int main() {
  UnitTest();
  return 0;
}
