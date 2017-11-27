### Problem one : How to check whether a long integer is power of 4.

```cpp
bool isPowerOfFour(long num) {
    if (num <= 0) return false;
      
    // Check whether it only has one setting bit
    if ((num & (num - 1)) != 0) return false;
      
    // The setting bit must show up on specific position.
    return (num & 0x55555555) != 0;
}


void UnitTest_PowerOfFour() {
  assert(isPowerOfFour(1) == true);
  assert(isPowerOfFour(4) == true);
  assert(isPowerOfFour(16) == true);
  assert(isPowerOfFour(64) == true);
  assert(isPowerOfFour(256) == true);
  assert(isPowerOfFour(2) == false);
  assert(isPowerOfFour(3) == false);
  assert(isPowerOfFour(5) == false);
  assert(isPowerOfFour(6) == false);
  assert(isPowerOfFour(7) == false);
  assert(isPowerOfFour(35) == false);
}
```

### Problem two  : How to check whether a long integer is power of 3.

Bit manipulation doesn't work here anymore.

Instead, we find the maximum number that is power of three, and check whether it is a multiple of the input. This method works on other prime number as well.

```cpp
bool isPowerOfThree(int num) {
  if (num<=0) return false;
  static int max_power_of_three = std::pow(3, (int)(std::log(INT_MAX) / std::log(3)) );
  return max_power_of_three % num == 0;
}

void UnitTest_PowerOfThree() {
  assert(isPowerOfThree(1) == true);
  assert(isPowerOfThree(3) == true);
  assert(isPowerOfThree(27) == true);
  assert(isPowerOfThree(1162261467) == true);
  assert(isPowerOfThree(81) == true);
  
  assert(isPowerOfThree(2) == false);
  assert(isPowerOfThree(4) == false);
  assert(isPowerOfThree(256) == false);
  assert(isPowerOfThree(6) == false);
  assert(isPowerOfThree(7) == false);
  assert(isPowerOfThree(35) == false);
}
```
