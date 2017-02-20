#include <iostream>
#include <cassert>

bool IsPalindrome(const std::string & str,
                  std::size_t left,
                  std::size_t right) {
  bool reval(true);
  while(left<right) {
    if (str[left]!=str[right]) {
      reval = false;
      break;
    } else {
      ++ left;
      -- right;
    }
  }
  return reval;
}

std::string CheckPalindrome(const std::string & str) {
  static int prime(103), base(256);
  
  std::string reval("");
  if (str.empty()) return reval;
  
  reval.push_back('Y');
  if (str.size() == 1) return reval;

  // left_hash represents the hash value of reversed left string
  int left_hash(str[0] % prime), right_hash(str[1] % prime);

  // since left_hash is the hash value of reversed left string,
  // every time we need to add a char at the begin of the reversed-left-string.
  int left_highest_base(1);
  
  const std::size_t str_size(str.size());
  for (std::size_t i = 1; i < str_size; ++i) {
    if (left_hash != right_hash) {
      reval.push_back('N');
    } else {
      reval.push_back( (IsPalindrome(str,0,i) ? 'Y' : 'N') );
    }

    if (i % 2 == 1) {
      // remove head of right hash
      right_hash = (right_hash + prime - str[(i+1)/2] * left_highest_base);
      // add next char to right hash,
      // the therotical form is `(righ t* base + str[i+1]) % prime`,
      // but we want to prevent overflow here
      right_hash = ( (right_hash * base) % prime + str[i+1]) % prime;
    } else {
      // increase the highest base of left_hash
      left_highest_base = (left_highest_base * base) % prime;

      // append mid char to left hash
      left_hash = ( str[i/2] * left_highest_base + left_hash) % prime;

      // add the next char to right hash
      right_hash = ( (right_hash * base) % prime + str[i+1]) % prime;
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
  return 0;
}





