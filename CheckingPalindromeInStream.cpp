// http://www.geeksforgeeks.org/online-algorithm-for-checking-palindrome-in-a-stream/
#include <vector>
#include <iostream>
#include <cassert>

bool IsPalindrome(const std::string & str,
                  std::size_t left,
                  std::size_t right) {
  while(left<right) {
    if (str[left]!=str[right]) {
      return false;
    } else {
      ++ left;
      -- right;
    }
  }
  return true;
}
std::string CheckPalindrome(const std::string & str) {
  // characters in the input alphabet
  static int base(256);
  // q is a prime number used for evaluating Rabin Karp's Rolling hash
  static int quotient(103);
 
  if (str.empty()) return "";
  const std::size_t str_size(str.size());

  std::string reval("");
  reval.push_back('Y');
  if (str_size==1) return reval;

  int left_hash(str[0]%quotient), right_hash(str[1]%quotient);
  for (std::size_t i=1, h=1;i<str_size;++i) {
    if (left_hash != right_hash) {
      reval.push_back('N');
    } else {
      if (IsPalindrome(str,0,i)) {
        reval.push_back('Y');
      } else {
        reval.push_back('N');
      }  
    }

    if (i%2==1) {
      // current string length(i+1) is even ==> next i is even
      // Need to chop the head of the right substring
      // and append (i+1)th char the right substring
      right_hash = (right_hash+quotient-str[(i+1)/2]*h);
      right_hash = ( (right_hash*base) % quotient + str[i+1]) % quotient;
    } else {
      // current string length is odd ==> next i is odd
      // need to append the middle char to the left substring
      // need to append the (i+1)-th char to the right substring
      h = (h*base) % quotient;
      left_hash = (str[i/2]*h + left_hash) % quotient;
      right_hash = ( (right_hash * base) % quotient + str[i+1] ) % quotient;
    }
  }
  return reval;
}

void UnitTest() {
  assert(CheckPalindrome("AABAA")=="YYNNY");
  assert(CheckPalindrome("")=="");
  assert(CheckPalindrome("x")=="Y");
  assert(CheckPalindrome("aabaacaabaa")=="YYNNYNNNNNY");
}

int main() {
  UnitTest();
  std::string reval = CheckPalindrome("AABAA");
  std::cout << reval << std::endl;
  return 0;
}
