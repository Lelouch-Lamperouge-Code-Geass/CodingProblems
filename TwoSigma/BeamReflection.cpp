/***
https://instant.1point3acres.com/thread/141628
两层玻璃叠在一起,一束光斜着照进来.问有几条beam是经过了i次反射.
就是两块玻璃叠在一起，这样有三个平面可以反射，然后问你经历了i次反射的光有多少？
比如： 经历了0次反射的光只有一束，那就是最初射入的那束光线，
在每一个平面都穿过去(当然了，实际情况有衰减)，最后从第三个平面穿过永远地离开了玻璃们；
经历了1次反射的光有三束，因为最初射入的那束光线可以分别在第一，二，三个平面选择反射后沿着既定方向离开玻璃；
经历了i次反射的光的数目其实就是fibonacci数列。记：从第一个平面(由对称性，第三个平面也是一样的)向内部发射的光经历了i次反射后离开玻璃们的数目为g(i)，
那么g(i)(i>=2时)应该由两部分组成: 1. 在第二个平面反射一下，然后回到第一个平面，再反射一下后的那部分光，也就是g(i-2);
2. 穿过第二个平面，在第三个平面反射一下，也就是g(i-1)； 所以。。就是fibonacii数列咯。
只不过g(0) = 1, g(1) = 2; 所以按照我的这个理解，结果是: f(0) = 1, f(1) = 3, i >= 2时, 是: f(i) = g(i); g(i) = g(i-2) + g(i-1); g(0) = 1; g(1) = 2;

 ***/

#include <iostream>
#include <cassert>

std::size_t ReflectionCount(std::size_t num_of_reflection) {
  if (num_of_reflection == 0) return 1;
  if (num_of_reflection == 1) return 3;
  std::size_t pre2 = 1, pre1 = 3;
  for (std::size_t i = 2; i <= num_of_reflection; ++ i) {
    std::size_t curr = pre2 + pre1;
    pre2 = pre1;
    pre1 = curr;
  }
  return pre1;
}


void UnitTest() {
  assert(ReflectionCount(0) == 1);
  assert(ReflectionCount(1) == 3);
  assert(ReflectionCount(2) == 4);
  assert(ReflectionCount(3) == 7);
  assert(ReflectionCount(4) == 11);
  assert(ReflectionCount(5) == 18);
  assert(ReflectionCount(6) == 29);
  assert(ReflectionCount(7) == 47);
}


int main() {
  UnitTest();
  return 0;
}
