Write an algorithm ti find the substrings of size K with K distinct characters.
If the given string does not have K distinct characters then output an empty list.
The returned substrings must be distinct, which means you need to perform deduplication.


# Solution

```cpp
vector<string> getUniqueSubstrings(const string &str, int k) {
	if (k <0 || k > str.size()) return vector<string>();

	unordered_map<char, int> num_of_char_in_window;
	unordered_set<string> unique_results;
	vector<string> reval;
	int number_of_repeat_chars_in_window(0);

	for (int i = 0, n = str.size(); i < n; ++i) {
		// Add str[i] into window
		++num_of_char_in_window[str[i]];
		if (num_of_char_in_window[str[i]] >= 2) {
			++number_of_repeat_chars_in_window;
		}

		if (i >= k) { // Evict str[i - k] out of window
			--num_of_char_in_window[str[i - k]];
			if (num_of_char_in_window[str[i - k]] >= 1) {
				--number_of_repeat_chars_in_window;
			}
		}

		if (i + 1 >= k && number_of_repeat_chars_in_window == 0) {
			const string cur_substr(str.substr(i - k + 1, k));
			if (unique_results.find(cur_substr) == unique_results.end()) {
				reval.emplace_back(cur_substr);
				unique_results.insert(cur_substr);
			}
		}
	}

	return reval;
}

void UnitTest() {
	vector<string> result = getUniqueSubstrings("awaglknagawunagwkwagl", 4);
	assert(result[0] == "wagl");
	assert(result[1] == "aglk");
	assert(result[2] == "glkn");
	assert(result[3] == "lkna");
	assert(result[4] == "knag");
	assert(result[5] == "gawu");
	assert(result[6] == "awun");
	assert(result[7] == "wuna");
	assert(result[8] == "unag");
	assert(result[9] == "nagw");
	assert(result[10] == "agwk");
	assert(result[11] == "kwag");
	assert(result.size() == 12);
}
```
