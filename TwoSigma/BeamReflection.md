https://instant.1point3acres.com/thread/141628  

两层玻璃叠在一起,一束光斜着照进来.问有几条beam是经过了i次反射.
就是两块玻璃叠在一起，这样有三个平面可以反射，然后问你经历了i次反射的光有多少？
比如： 经历了0次反射的光只有一束，那就是最初射入的那束光线，

```
在每一个平面都穿过去(当然了，实际情况有衰减)，最后从第三个平面穿过永远地离开了玻璃们；
经历了1次反射的光有三束，因为最初射入的那束光线可以分别在第一，二，三个平面选择反射后沿着既定方向离开玻璃；
经历了i次反射的光的数目其实就是fibonacci数列。记：从第一个平面(由对称性，第三个平面也是一样的)
 向内部发射的光经历了i次反射后离开玻璃们的数目为g(i)，
那么g(i)(i>=2时)应该由两部分组成: 1. 在第二个平面反射一下，然后回到第一个平面，再反射一下后的那部分光，也就是g(i-2);
2. 穿过第二个平面，在第三个平面反射一下，也就是g(i-1)； 所以。。就是fibonacii数列咯。
只不过g(0) = 1, g(1) = 2; 所以按照我的这个理解，结果是: 
f(0) = 1, f(1) = 3, i >= 2时, 是: f(i) = g(i); g(i) = g(i-2) + g(i-1); g(0) = 1; g(1) = 2;

```


```
更新 : 上面的思路有问题。玻璃有三块反射面，让我们定义“最后反射点”为一束光永远离开玻璃们的最后的反射点， 
那么如果“最后反射点”在两个外层玻璃的反射光可以衍生出 两个  +1 反射的反射光。
而“最后反射点”在中间的反射光只能衍生出一条 +1 反射的反射光。
另外一个特性在于如果这次最终反射点在中间的玻璃，那么下一个反射点必然在外层玻璃， 
而这次最终反射点在外层玻璃，那么必然下次反射有两个反射点，
一个在内层玻璃而一个在外层玻璃。
设定 Ki 为经历过i次反射且最终反射点在外层玻璃的个数， 设定 Pi 为经历过 i 次反射且最终反射光在内层玻璃的个数。
那么 i = 1 时， K1 = 1, P1 = 1, 加上没射入玻璃的那束光一共三束光，  n = K1 + P1 + 1 = 3;
i = 2 时， K2 = K1 + P1 = 2, P2 = K1 = 1,  n = K2 + P2 = 3;
i = 3 时， K3 = K2 + P2 = 3, P3 = K2 = 2, n = K3 + P3 = 5;
i = 4 时， K4 = K3 + P3 = 5, P4 = K3 = 3, n = K4 + P4 = 8;

抛开 i = 0 为特殊情况， 
 i= 0 时， 经历了0次反射的光有1束
 i= 1 时， 经历了1次反射的光有3束（其中一束的最终反射点在外层玻璃，没有进入玻璃的那束光不算）
 i= 2 时， 经历了2次反射的光有3束 （其中两束光是由i=1的那束最终反射点在外层玻璃的光衍生而来，另外一束则是由最终反射点在内层玻璃的那束光衍生而来）
 i= 3 时， 经历了3次反射的光有5束
 i= 4 时， 经历了4次反射的光有8束
```

```cpp
#include <cassert>
#include <iostream>

/***
    --------------
    |            |
    --------------
    |            |
    --------------
 ***/
std::size_t ReflectionCount(std::size_t num_of_reflection) {
  if (num_of_reflection == 0) return 1;
  if (num_of_reflection == 1) return 3;
  // The amount of reflection==1 is 3, one is the beam hit outlayer outside of the glass,
  // which will leave forever. One is the beam hit outlayer wihin glass, one is the beam
  // hit inner-layer within glass.
  std::size_t pre_outer_layer_reflect(1), pre_inner_layer_reflect(1), cur_reflection(3);

  for (std::size_t i = 2; i <= num_of_reflection; ++i) {

    std::size_t cur_outer_layer_reflect = pre_outer_layer_reflect + pre_inner_layer_reflect;
    std::size_t cur_inner_layer_reflect = pre_outer_layer_reflect;

    // update
    pre_outer_layer_reflect = cur_outer_layer_reflect;
    pre_inner_layer_reflect = cur_inner_layer_reflect;

    cur_reflection = cur_outer_layer_reflect + cur_inner_layer_reflect;
  }

  return cur_reflection;
}


void UnitTest() {
  assert(ReflectionCount(0) == 1);
  assert(ReflectionCount(1) == 3);
  assert(ReflectionCount(2) == 3);
  assert(ReflectionCount(3) == 5);
  assert(ReflectionCount(4) == 8);
  assert(ReflectionCount(5) == 13);
  assert(ReflectionCount(6) == 21);
}

int main() {
  UnitTest();
  return 0;
}
```
