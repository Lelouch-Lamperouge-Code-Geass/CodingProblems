// http://www.geeksforgeeks.org/online-algorithm-for-checking-palindrome-in-a-stream/
#include <iostream>

class PalindromeChecker {
public:
  PalindromeChecker() : m_str(""), m_prime(919), m_base(256), m_half_base(1) , m_left_hash(0), m_right_hash(0){}

  static bool IsPalindrome(const std::string & str,
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
  
  bool AddAndCheck(char new_char) {
    m_str.push_back(new_char);
    if (m_str.size() <=1 ) {
      return true;
    } else {
      if (m_str.size() % 2 == 0) {
        if(m_str.size() >= 4) m_half_base *= m_base;

        char left_head = m_str[(m_str.size()-1) / 2];
        m_left_hash = ( left_head * m_half_base + m_left_hash) % m_prime;
        m_right_hash = (m_right_hash * m_base + new_char) % m_prime;
      } else {
        char right_head = m_str[m_str.size() / 2];
        // remove head from right hash
        m_right_hash = (m_right_hash + m_prime - (right_head * m_half_base) % m_prime) % m_prime;
        // add new char
        m_right_hash = (m_right_hash * m_base + new_char) % m_prime;
      }
    }

    //std::cout << m_left_hash <<" : " << m_right_hash << std::endl;
    return m_left_hash == m_right_hash && IsPalindrome(m_str, 0, m_str.size() - 1);
  }
private:
  int m_prime;
  int m_left_hash;
  int m_right_hash;
  int m_base;
  int m_half_base;
  std::string m_str;
};


void UnitTest() {
  PalindromeChecker checker;
  const std::string str("aabaacaabaa");
  for (char c : str) {
    std::cout << ( checker.AddAndCheck(c)? "Y":"N" ) << std::endl;
  }
}

int main() {
  UnitTest();
  return 0;
}
