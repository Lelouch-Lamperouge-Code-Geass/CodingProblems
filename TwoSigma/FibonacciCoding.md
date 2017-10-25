#### Zeckendorf’s Theorem
  
Zeckendorf’s theorem states that every positive Every positive integer can be written uniquely as a sum of distinct non-neighbouring Fibonacci numbers. Two Fibonacci numbers are neighbours if they one come after other in Fibonacci Sequence (0, 1, 1, 2, 3, 5, ..). For example, 3 and 5 are neighbours, but 2 and 5 are not.

Given a number, find a representation of number as sum of non-consecutive Fibonacci numbers.

Examples:

```
Input:  n = 10
Output: 8 2
8 and 2 are two non-consecutive Fibonacci Numbers
and sum of them is 10.

Input:  n = 30
Output: 21 8 1
21, 8 and 1 are non-consecutive Fibonacci Numbers
and sum of them is 30.
```

The idea is to use Greedy Algorithm.

```
1) Let n be input number

2) While n >= 0
     a) Find the greatest Fibonacci Number smaller than n.
        Let this number be 'f'.  Print 'f'
     b) n = n - f 
```     

### Fibonacci Coding

http://www.geeksforgeeks.org/fibonacci-coding/  

In mathematics and computing, Fibonacci coding is a universal code which encodes positive integers into binary code words. 
It is one example of representations of integers based on Fibonacci numbers. 
Each code word ends with "11" and contains no other instances of "11" before the end.
The Fibonacci code is closely related to the Zeckendorf representation, a positional numeral system that uses Zeckendorf's theorem and has the property that no number has a representation with consecutive 1s. 
The Fibonacci code word for a particular integer is exactly the integer's Zeckendorf representation with the order of its digits reversed and an additional "1" appended to the end.
  
  

```cpp
#include <string>
#include <vector>
#include <cassert>
#include <iostream>
#include <sstream>
std::string FibonacciEncoding(int number) {
  if (number<1) return "";

  std::vector<int> digits = {1,2};// Fibonacci Encoding sequence
  while (digits.back()<number) {
    digits.push_back(digits[digits.size()-2]+digits.back());
  }

  int index = std::lower_bound(digits.begin(),digits.end(),number) - digits.begin();
  if (digits[index]>number) --index;
  std::string res("");
  while (index>=0) {
    if (digits[index] <= number) {
      res.push_back('1');
      number -= digits[index];
    } else {
      res.push_back('0');
    }
    -- index;
  }
  std::reverse(res.begin(),res.end());
  res.push_back('1');// extra 1
  return res;
}


void UnitTestFibonacciEncoding() {
  assert(FibonacciEncoding(1)=="11");
  assert(FibonacciEncoding(2)=="011");
  assert(FibonacciEncoding(3)=="0011");
  assert(FibonacciEncoding(4)=="1011");
  assert(FibonacciEncoding(5)=="00011");
  assert(FibonacciEncoding(6)=="10011");
  assert(FibonacciEncoding(8)=="000011");
  assert(FibonacciEncoding(16)=="0010011");
  assert(FibonacciEncoding(11)=="001011");
  assert(FibonacciEncoding(143)=="01010101011");
}
int main(int argc, char* argv[]) {
  UnitTestFibonacciEncoding();
  return 0;
}
```
