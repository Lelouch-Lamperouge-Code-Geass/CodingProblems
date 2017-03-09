#include <iostream>
#include <cassert>
#include <cmath>
#include <climits>


class Solution {
public:
    bool isPowerOfFour(int num) {
          if (num <= 0) return false;
      
          // Check whether it only has one setting bit
          if ((num & (num - 1)) != 0) return false;
      
            // The setting bit must show up on specific position.
          return (num & 0x55555555) != 0;

    }
};

void UnitTest_PowerOfFour() {
  assert(PowerOfFour(1) == true);
  assert(PowerOfFour(4) == true);
  assert(PowerOfFour(16) == true);
  assert(PowerOfFour(64) == true);
  assert(PowerOfFour(256) == true);
  assert(PowerOfFour(2) == false);
  assert(PowerOfFour(3) == false);
  assert(PowerOfFour(5) == false);
  assert(PowerOfFour(6) == false);
  assert(PowerOfFour(7) == false);
  assert(PowerOfFour(35) == false);
}

// Bit manipulation doesn't work here anymore.
// Instead, we find the maximum number that is
// power of three, and check whether it is a multiple
// of the input. This method works on other prime number as well.
bool PowerOfThree(int num) {
  if (num<=0) return false;
  static int max_power_of_three = std::pow(3, (int)(std::log(INT_MAX) / std::log(3)) );
  return max_power_of_three % num == 0;
}

void UnitTest_PowerOfThree() {
  assert(PowerOfThree(1) == true);
  assert(PowerOfThree(3) == true);
  assert(PowerOfThree(27) == true);
  assert(PowerOfThree(1162261467) == true);
  assert(PowerOfThree(81) == true);
  
  assert(PowerOfThree(2) == false);
  assert(PowerOfThree(4) == false);
  assert(PowerOfThree(256) == false);
  assert(PowerOfThree(6) == false);
  assert(PowerOfThree(7) == false);
  assert(PowerOfThree(35) == false);
}

int main() {
  UnitTest_PowerOfFour();
  UnitTest_PowerOfThree();
  return 0;
}
