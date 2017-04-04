/*
给字符串，写压缩算法，解压算法已有，例如aaabbbbcccc->aaa4xb4xc，
需要考虑3aaaaa->35xa会出问题，
首先分析一下这个题，只有在连续字母超过3个的时候压缩才有意义，
另外如果最前面如果是一个数字的话，比如说3aaaaa应该要压缩成3a4xa这样，而不能压缩成35xa。
之后就主要是implementation的问题了
*/
#include <string>
#include <vector>
#include <iostream>
#include <cassert>
#include <sstream>

std::string EncodeString(const std::string & str) {
  const std::size_t str_size(str.size());
  std::ostringstream oss;
  std::size_t index(0);
  while (index < str_size) {
    char cur_char = str[index];
    int count(0);
    const bool pre_char_is_number = (index > 0 && std::isdigit(str[index-1]));
    while (index < str_size && str[index] == cur_char) {
      ++ index;
      ++ count;
    }
    
     if (count <= 3) {
      while (count > 0) {
        oss << cur_char;
        -- count;
      }
    } else {
      if (pre_char_is_number) oss << ' ';
      oss << count << 'x' << cur_char;
    }
  }

  return oss.str();
}


std::string DecodeString(const std::string & str) {
  const std::size_t str_size(str.size());
  std::ostringstream oss;
  std::size_t index(0);
  while (index < str_size) {
    if (std::isdigit(str[index])) {
      std::size_t not_digit_pos = str.find_first_not_of("0123456789", index);
      const std::string numeric_str = str.substr(index, not_digit_pos - index);
      if (str[not_digit_pos] == 'x' && not_digit_pos + 1 < str_size) {
        int count = std::stoi(numeric_str);
        const char dup_char = str[not_digit_pos + 1];
        while (count > 0) {
          oss << dup_char;
          -- count;
        }

        index = not_digit_pos + 2;
      } else {
        oss << numeric_str;
        if (not_digit_pos == str_size) break;
        if (str[not_digit_pos] == 'x') { oss << str[not_digit_pos]; index = not_digit_pos + 1;}
        else if (str[not_digit_pos] == ' ') { index = not_digit_pos + 1;}
        else index = not_digit_pos;
      }
    } else {
      oss << str[index++];
    }
  }

  return oss.str();
}

void UnitTest_EncodeString() {
  assert(EncodeString("aaabbbbcccc") == "aaa4xb4xc");
  assert(EncodeString("3aaaa") == "3 4xa");
  assert(EncodeString("3aaa") == "3aaa");
  assert(EncodeString("322222") == "3 5x2");
  assert(EncodeString("3     111") == "3 5x 111");
  //assert(EncodeString("5xt") == "5\xt");
  //assert(EncodeString("5xx") == "5xx");
  //assert(EncodeString("5xxxxxx") == "5 6x\x");
}

void UnitTest_DecodeString() {
  assert(DecodeString("aaa4xb4xc") == "aaabbbbcccc");
  assert(DecodeString("3 4xa") == "3aaaa");
  assert(DecodeString("3aaa") == "3aaa");
  assert(DecodeString("3 5x2") == "322222");
  assert(DecodeString("3 5x 111") == "3     111");
  assert(DecodeString("5x") == "5x");
  //assert(EncodeString("5xt") == "5\xt");
  //assert(EncodeString("5xx") == "5xx");
  //assert(EncodeString("5xxxxxx") == "5 6x\x");
}

int main() {
  UnitTest_EncodeString();
  UnitTest_DecodeString();
  return 0;
}
