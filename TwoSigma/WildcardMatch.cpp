#include <string>
#include <vector>
#include <cassert>

namespace RecursiveSolution {
  
 bool WildcardRecursive(const std::string & str,
                       const std::string & pattern,
                       std::size_t str_index,
                       std::size_t pattern_index) {
  if (str_index < str.size() && pattern_index < pattern.size()) {
    if (pattern[pattern_index] != '*') {
      return  (str[str_index] == pattern[pattern_index] || pattern[pattern_index] == '?') 
        &&  WildcardRecursive(str, pattern, str_index + 1, pattern_index + 1);
    } else {
      return pattern[pattern_index] == '*'
        && ( WildcardRecursive(str, pattern, str_index, pattern_index + 1)
             || WildcardRecursive(str, pattern, str_index + 1, pattern_index) );
    }
  } else {
    while (pattern_index < pattern.size() && pattern[pattern_index] == '*') ++pattern_index;
    return str_index == str.size() && pattern_index == pattern.size();
  }
}

bool WildcardMatch(const std::string & str, const std::string & pattern) {
  return WildcardRecursive(str, pattern, 0, 0);
}

  
}


namespace DynamicProgramming{
  bool WildcardMatch(const std::string & str, const std::string & pattern) {
    const std::size_t str_size(str.size()), pattern_size(pattern.size());
    std::vector< std::vector<bool> > is_match(str_size+1,std::vector<bool>(pattern_size+1,false));
    is_match[0][0] = true;
    for (std::size_t i=1;i<=pattern_size && pattern[i-1]=='*';++i) {
      is_match[0][i] = true;
    }

    for (std::size_t i=1;i<=str_size;++i) {
      for (std::size_t j=1;j<=pattern_size;++j) {
        if (pattern[j-1]=='*') {
          is_match[i][j] = is_match[i][j-1] // do nothing
            || is_match[i-1][j]; // match current char
        } else {
          is_match[i][j] = is_match[i-1][j-1]
            && (str[i-1]==pattern[j-1] || pattern[j-1]=='?');
        }
      }
    }
    
    return is_match[str_size][pattern_size];
  }
}

namespace TwoPointerSolution {
  bool WildcardMatch(const std::string & str, const std::string & pattern) {
    const std::size_t str_size(str.size()), pattern_size(pattern.size());
    std::size_t str_index(0),pattern_index(0);
    std::size_t str_marker(-1),pattern_marker(-1);

    // Notice that there is a concealed scenario here, when pattern_index == pattern.size()
    // we accessed pattern[pattern_index] as well. Of course, it will be a mismatch.
    while (str_index < str_size) {
      if (pattern[pattern_index]=='*') {
        // mark where * appears
        pattern_marker = pattern_index;
        str_marker = str_index;

        // at first let * match nothing
        ++ pattern_index; 
      } else {
        if ( str[str_index] == pattern[pattern_index]
             || pattern[pattern_index] == '?') {
          ++ pattern_index;
          ++ str_index;
        } else {
          if (pattern_marker == -1) {
            // no *
            return false;
          } else {
            str_index = ++ str_marker; // need increase str_marker here!
            pattern_index = pattern_marker + 1; 
          }
        }
      }
    }
    // Right now str_index == str_size,
    // we need make sure pattern_index can reach pattern_size
    while (pattern_index < pattern_size && pattern[pattern_index]=='*') ++ pattern_index;

    return pattern_index == pattern_size;
  }
}


void UnitTest() {
  using namespace RecursiveSolution;
  assert(WildcardMatch("aaa","a*")==true);
  assert(WildcardMatch("","*")==true);
  assert(WildcardMatch("abcadca","a*ca")==true);
  assert(WildcardMatch("dbbca","db*cae")==false);
  assert(WildcardMatch("dbbca","db?ca")==true);
  assert(WildcardMatch("","")==true);
  assert(WildcardMatch("ab","?*")==true);
  assert(WildcardMatch("aab","c*a*b")==false);
  assert(WildcardMatch("aa","aa")==true);
  assert(WildcardMatch("aaaaaaa","a*a")==true);
  assert(WildcardMatch("aaa","aa")==false);
  assert(WildcardMatch("aa","?")==false);
}


void UnitTest_Match() {
  assert( WildcardMatch("abc","a*") == true );
  assert( WildcardMatch("","") == true );
  assert( WildcardMatch("","*") == true );
  assert( WildcardMatch("abcd","*") == true );
  assert( WildcardMatch("abc","a*b*c") == true );
  assert( WildcardMatch("abc","abc") == true );
  assert( WildcardMatch("1*3*5","1*5") == true );
  assert( WildcardMatch("1234","1?3?") == true );
  assert( WildcardMatch("1*3?","1?3*") == true );
  assert( WildcardMatch("***","*") == true );
  assert( WildcardMatch("aaaaaaaaaaaa","a*aa") == true );
}

void UnitTest_NotMatch() {
  assert( WildcardMatch("abc","a*d") == false );
  assert( WildcardMatch(""," ") == false );
  assert( WildcardMatch("*","1") == false );
  assert( WildcardMatch("aab","c*a*b") == false );
  assert( WildcardMatch("abc","a*c*b") == false );
  assert( WildcardMatch("aa","?") == false );
  assert( WildcardMatch("aaa","aa") == false );
  assert( WildcardMatch("abcd","a*??c") == false );
}



int main() {
  UnitTest();
  return 0;
}
