
#include <iostream>

void FizzBuzzWithMod(std::size_t n, std::size_t fizz, std::size_t buzz) {
  static const std::string FIZZBUZZ("FizzBuzz"),
    FIZZ("Fizz"), BUZZ("Buzz");
  for (std::size_t i = 1; i < n; ++i) {
    if (i % fizz == 0 && i % buzz == 0) {
      std::cout << FIZZBUZZ << " : " << i << std::endl;
    } else if (i % fizz == 0) {
      std::cout << FIZZ << " : " << i << std::endl;
    } else if (i % buzz == 0) {
      std::cout << BUZZ << " : " << i << std::endl;
    } else {
      // ignore
    }
  }
}

void FizzBuzzWithoutMod(std::size_t n, std::size_t fizz, std::size_t buzz) {
  static const std::string FIZZBUZZ("FizzBuzz"),
    FIZZ("Fizz"), BUZZ("Buzz");

  for (std::size_t i = 1, fizz_val(1), buzz_val(1); i < n; ++i) {
    if (i % fizz == 0 && i % buzz == 0) {
      std::cout << FIZZBUZZ << " : " << i << std::endl;
      fizz_val = 0;
      buzz_val = 0;
    } else if (i % fizz == 0) {
      fizz_val = 0;
      std::cout << FIZZ << " : " << i << std::endl;
    } else if (i % buzz == 0) {
      buzz_val = 0;
      std::cout << BUZZ << " : " << i << std::endl;
    } else {
      // ignore
    }

    ++ fizz_val;
    ++ buzz_val;
  }
}

int main() {
  std::cout << "###### Test FizzBuzzWithMod ######" << std::endl;
  FizzBuzzWithMod(31,3,5);

  std::cout << "###### Test FizzBuzzWithoutMod ######" << std::endl;
  FizzBuzzWithoutMod(31,3,5);
  return 0;
}
