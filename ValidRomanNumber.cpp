http://www.diveintopython.net/regular_expressions/roman_numerals.html

/* Solution 1 : using regular expression, which I really hate*/
bool IsValidRomainNumber(const std::string & str) {
  std::regex reg_ex("^M{0,4}(CM|CD|D?C{0,3})(XC|XL|L?X{0,3})(IX|IV|V?I{0,3})$");
  return std::regex_match (str,reg_ex);
}

/* Solution 2*/
