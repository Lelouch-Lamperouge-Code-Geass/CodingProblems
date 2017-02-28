#include <iostream>
#include <cassert>

class PalindromeChecker {
public:

  PalindromeChecker() : m_prime(103), m_base(256),  m_left_hash(1), m_right_hash(1), m_half_base(1), m_str("") {

  }

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

  std::string Check(char new_char) {
    m_str.push_back(new_char);
    const std::size_t cur_size = m_str.size();
    if (cur_size == 1) {
      m_left_hash = m_right_hash = m_str[0] % m_prime;
    } else if (cur_size == 2) {
      m_right_hash = m_str[1] % m_prime;
    } else {
      char mid_char = m_str[(cur_size-1)/2];
      if (cur_size % 2 != 0) {
        // remove head char from right hash
        m_right_hash = (m_right_hash + m_prime - (mid_char * m_half_base) % m_prime) % m_prime;
        // add new char to right hash
        m_right_hash = (m_right_hash * m_base + new_char) % m_prime;
      } else {
        m_half_base = (m_half_base * m_base) % m_prime; // increase half base
        // add mid char to left hash
        m_left_hash = (mid_char * m_half_base + m_left_hash) % m_prime;

        // add new char to right hash
        m_right_hash = (m_right_hash * m_base + new_char) % m_prime;
      }
    }

    if (m_left_hash != m_right_hash) {
      m_status.push_back('N');
    } else {
      m_status.push_back( (IsPalindrome(m_str, 0, m_str.size()-1) ? 'Y' : 'N') );
    }

    return m_status;
  }

  std::string GetStatus() const {
    return m_status;
  }
private:
  int m_prime;
  int m_base;
  int m_left_hash;
  int m_right_hash;
  int m_half_base;
  std::string m_str;
  std::string m_status;
};


void UnitTest() {
  PalindromeChecker checker;
  const std::string str("AABAA");
  for (char c : str) {
    checker.Check(c);
  }

  assert(checker.GetStatus() == "YYNNY");


  PalindromeChecker checker2;
  const std::string str2("aabaacaabaa");
  for (char c : str2) {
    checker2.Check(c);
      }

  assert(checker2.GetStatus() == "YYNNYNNNNNY");
}


int main() {
  UnitTest();
  return 0;
}





