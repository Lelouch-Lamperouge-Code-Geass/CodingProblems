Amazon wants to label its products with tags, which are strings of alphanumeric characters. Each product is associated with a sequence of tags. Edward, an employee in the company, has been assigned the task of labelling the products. He has been given a sequence of all tags that could be associated with any product, as well as a sequence of all desired tags for the product that he is labeling. His task is to find the 0-based start and end indices of the shortest continuous subsequence containing all the desired tags for the product, __in any order__. 

__If more than one minimum continuous subsequence contains all the desired tags, then output the one with the smaller start index__.

Implement an algorithm to find the 0-based start index and end indices of the minimum continuous subsequence containing all the desired tags in any order.

#### Input

The input to the function/method consists of two arguments:

* ```targetList```, a list of strings representing the desired tags;
* ```availableTagList```, a list of strings representing the sequence of all available tags.

#### Output

Return a list where the first element is the start index, and the second element is the ending index. If more than one minimum continuous subsequence contains the desired tags then return the one with the smaller start index. If there isn't a match, output a list of length of 1 with content 0.

#### Note

* ```targetList``` does not contain duplicate tags.
* The returned subsequence may include additional tags beyond thoses in targetList.
* The ```availableTagList``` may include tags other than those in the targetList, and some tags may be duplicated. targetList and availableTagList consist of only alphanumeric character strings,
* If any of the tags in ```targetList``` are missing from ```availableTagList```, then output[0].

#### Example

```
Input:

targetList = ["made", "in", "Spain"]
availableTagList = ["made", "weather", "forecase", "says", "that", "made", "rain", "in", "spain", "stays"]

Output: [5,8]
```

Explanation:

Two of the possible subsequences are:

* The first subsequence occurs with size 9, where the first occurrence of any tag is at the 0th index with "made", and it hits in at index 7, and the last on "Spain" at the 8th index.
* The second subsequence occurs with size 4, where the first occurrence of any tag is at the 5th index with "made", and it hits in at index 7, and the last one "Spain" at the 8th index.

So the output is [5,8], because we are looking for the minimum continuous subsequence.


# Solution

The description should metion that the __tags are case-insensitive__.


```cpp
string getLowercaseString(string data) {
	std::transform(data.begin(), data.end(), data.begin(), ::tolower);
	return data;
}

vector<int> minWindow(const vector<string> &targetList, 
					  const vector<string> &availableTagList) {
	// How many tags are missing in current window
	int tags_to_find(targetList.size());

	// The number of each tage missing in current window
	unordered_map<string, int> number_of_tag_missing_in_window;

	// Originally, our window miss all the tags in targetList
	for (const string & tmp_tag : targetList) {
		++number_of_tag_missing_in_window[getLowercaseString(tmp_tag)];
	}

	int window_start(0), min_window_start(0), min_window_len(INT_MAX);
	for (int i = 0, n = availableTagList.size(); i < n; ++i) {
		// Put current tag into window
		--number_of_tag_missing_in_window[getLowercaseString(availableTagList[i])];

		// Our window just add a tag that should be found
		if (number_of_tag_missing_in_window[getLowercaseString(availableTagList[i])] >= 0) {
			--tags_to_find;
		}

		while (tags_to_find == 0) { // Current window has all tags in targetList
			// Check the length of current window with minimal-window-length we have so far.
			int cur_len = i + 1 - window_start;
			if (cur_len < min_window_len) {
				min_window_start = window_start;
				min_window_len = cur_len;
			}

			// Pop rightmost tag out of window
			++ number_of_tag_missing_in_window[getLowercaseString(availableTagList[window_start])];

			// If the popped tag is one of the tag in targetList
			if (number_of_tag_missing_in_window[getLowercaseString(availableTagList[window_start])] > 0) ++tags_to_find;

			++ window_start;
		}
	}

	if (min_window_len == INT_MAX) {
		return {0};
	} else {
		return { min_window_start, min_window_start + min_window_len - 1};
	}
}

void UnitTest() {
	vector<string> targetList = { "made", "in", "Spain" };
	vector<string> availableTagList = { "made", "weather", "forecase", "says", 
		"that", "made", "rain", "in", "spain", "stays" };
	vector<int> result = minWindow(targetList, availableTagList);
	assert(result[0] == 5);
	assert(result[1] == 8);

	targetList = { "made", "in", "Spain" };
	availableTagList = {"dummy"};
	result = minWindow(targetList, availableTagList);
	assert(result.size() == 1);
	assert(result[0] == 0);
}

int main()
{
	UnitTest();
	return 0;
}
```
