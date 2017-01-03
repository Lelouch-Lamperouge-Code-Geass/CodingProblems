//Find all distinct palindromic sub-strings of a given string.

#include <string>
#include <vector>
#include <unordered_set>
#include <cassert>
#include <iostream>
#include <sstream>

using namespace std;

vector<string> FindAllPalindrome(const string & s) {
  vector<string> res;
  const std::size_t s_size(s.size());
  unordered_set<string> visited;
  vector< vector<bool> > is_palindrome(s_size,vector<bool>(s_size,false));
  for (std::size_t end=0;end<s_size;++end) {
    for (std::size_t start=end;start<s_size;--start) {
      if (start==end||s[start]==s[end]&&(end-start<=1||is_palindrome[start+1][end-1])) {
        is_palindrome[start][end] = true;
        const std::string cur_str(s.substr(start,end-start+1));
        if (visited.count(cur_str)==0) res.push_back(cur_str);
        visited.insert(cur_str);
      }
    }
  }
  return res;
}

void UnitTest(){
  vector<string> res = FindAllPalindrome("aabac");
  assert(res.size()==5);

  res = FindAllPalindrome("geek");
  assert(res.size()==4);

  res = FindAllPalindrome("abaaa");
  assert(res.size()==5);

  res = FindAllPalindrome("aaaaaaaaaaaaaaaaaaaaa");
  assert(res.size()==21);
}

int main(int argc, char* argv[]) {
  UnitTest();
  vector<string> res = FindAllPalindrome("aaaaaaaaaaaaaaaaaaaaa");
  for (const string & item : res) {
    std::cout << item << std::endl;
  }
  return 0;
}
