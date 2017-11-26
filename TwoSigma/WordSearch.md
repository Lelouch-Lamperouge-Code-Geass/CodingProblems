Given a dictionary and a String, find all subsets of the substring of the String in the dictionary? ( time complexity, space complexity, how to improve both time and space..)

# Solution

```cpp
struct TrieNode;
typedef shared_ptr<TrieNode> TrieNodePtr;
struct TrieNode {
	TrieNode(char c) : m_char(c), m_children(26, nullptr), m_word_count(0) {}
	char m_char;
	vector<TrieNodePtr> m_children; 
	int m_word_count;
};

// Build a trie based on dictionary.
// The complexity of creating a trie is O(W*L), 
// where W is the number of words, and L is an average length of the word.
TrieNodePtr buildTrie(unordered_set<string> &dictionary) {
	TrieNodePtr root = std::make_shared<TrieNode>(' ');
	for (const string &word : dictionary) {
		TrieNodePtr curr = root;
		for (char c : word) {
			if (!curr->m_children[c - 'a']) {
				curr->m_children[c - 'a'] = std::make_shared<TrieNode>(c);
			}
			curr = curr->m_children[c - 'a'];
		}
		++ curr->m_word_count;
	}
	return root;
}

// FOr a compound word, e.g. "airport", should return "air", "port", "airport".
// Search a word in a trie takes average O(average word length)
vector<string> findWord(const string &str, 
			  std::size_t pos, 
			  TrieNodePtr root){
	vector<string> reval;
	string temp("");
	const std::size_t str_size(str.size());
	while (root && pos < str_size) {
		if (root->m_children[str[pos] - 'a']) {
			temp.push_back(str[pos]);
			root = root->m_children[str[pos] - 'a'];
			if (root->m_word_count > 0) reval.emplace_back(temp);
			++ pos;
		} else {
			break;
		}
	}
	return reval;
}

std::vector<std::string> wordSearch(const string &str, unordered_set<string> &dictionary) {
	std::vector<std::string> reval;
	TrieNodePtr root = buildTrie(dictionary);
	string temp("");
	for (std::size_t i = 0, n = str.size(); i < n; ++i) {
		vector<string> words = findWord(str, i, root);
		reval.insert(reval.end(), words.begin(), words.end());
	}
	return reval;
}

class WordSearchUnitTest{
public :
	WordSearchUnitTest() {
		string arr[] = {"air", "port", "airport"};
		std::vector<string> words(std::begin(arr), std::end(arr));
		for (const string& word : words) {
			m_dictionary.insert(word);
		}
	}
	void TestCompoundWords() {
		string str = "airmbairport";
		std::vector<std::string> items = wordSearch(str, m_dictionary);
		assert(items.size() == 4);
	}
private:
	std::unordered_set<std::string> m_dictionary;
};



int _tmain(int argc, _TCHAR* argv[])
{
	WordSearchUnitTest test;
	test.TestCompoundWords();
	return 0;
}
```
