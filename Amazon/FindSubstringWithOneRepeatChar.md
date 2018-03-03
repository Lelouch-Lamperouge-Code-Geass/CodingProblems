给一个字符串，找个出所有长度是K，有1个重复的子字符串。
例子：

```
s: asdfaghjkjqoiiii;N=5. 返回
asdfa
ghjkj
hjkjq
jkjqo
jqoii.
```

# Solution

```cpp
vector<string> substringWithOneRepeatChar(const string &str, int k) {
	if (k <0 || k > str.size()) return vector<string>();

	unordered_map<char, int> num_of_char_in_window;
	unordered_set<string> unique_results;
	int number_of_repeat_chars_in_window(0);

	for (int i = 0, n = str.size(); i < n; ++i) {
		// Add str[i] into window
		++num_of_char_in_window[str[i]];
		if (num_of_char_in_window[str[i]] >= 2) {
			++ number_of_repeat_chars_in_window;
		}

		if (i >= k) { // Evict str[i - k] out of window
			--num_of_char_in_window[str[i - k]];
			if (num_of_char_in_window[str[i - k]] >= 1) {
				-- number_of_repeat_chars_in_window;
			}
		}
		
		if (i + 1 >= k && number_of_repeat_chars_in_window == 1) {
			unique_results.insert(str.substr(i - k + 1, k));
		}
	}

	return vector<string>(unique_results.begin(), unique_results.end());
}

void UnitTest() {
	vector<string> result = substringWithOneRepeatChar("asdfaghjkjqoiiii", 5);
	assert(result.size() == 5);
}

int main()
{
	UnitTest();
	return 0;
}
```
