Write a program that outputs the string representation of numbers from 1 to n.

But for multiples of three it should output “Fizz” instead of the number and for the multiples of five output “Buzz”. For numbers which are multiples of both three and five output “FizzBuzz”.

Example:

```
n = 15,

Return:
[
    "1",
    "2",
    "Fizz",
    "4",
    "Buzz",
    "Fizz",
    "7",
    "8",
    "Fizz",
    "Buzz",
    "11",
    "Fizz",
    "13",
    "14",
    "FizzBuzz"
]
```

# Solution

### Solution 1

```cpp
class Solution {
public:
    vector<string> fizzBuzz(int n) {
        vector<string> reval(n,"");
        for (int i = 1; i <= n; ++i) {
            if (i >= 5 && i % 3 == 0 && i % 5 == 0) {
                reval[i-1] = "FizzBuzz";
            } else if (i >= 3 && i % 3 == 0) {
                reval[i-1] = "Fizz";
            } else if (i >= 5 && i % 5 == 0) {
                reval[i-1] = "Buzz";
            } else {
                reval[i-1] = std::to_string(i);
            }
        }
        return reval;
    }
};
```


### Solution 2, a solution without using '%'

```cpp
class Solution {
public:
    vector<string> fizzBuzz(int n) {
        vector<string> reval(n,"");
        int fizz(0), buzz(0);
        for (int i = 1; i <= n; ++i) {
            ++ fizz, ++ buzz;
            if (fizz == 3 && buzz == 5) {
                reval[i-1] = "FizzBuzz";
                fizz = buzz = 0;
            } else if (fizz == 3) {
                reval[i-1] = "Fizz";
                fizz = 0;
            } else if (buzz == 5) {
                reval[i-1] = "Buzz";
                buzz = 0;
            } else {
                reval[i-1] = std::to_string(i);
            }
        }
        return reval;
    }
};
```
