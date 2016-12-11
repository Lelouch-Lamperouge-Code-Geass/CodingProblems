/**
longest chain
类似word ladder，对于一个单词删掉任何一个字母，如果新单词出现在给的词典里 
那么就形成一个 chain： old word -> new word -> newer word, 求最长长度(return int) 
比如给vector<string> w = {a,ba,bca,bda,bdca} 最长是4： bdca->bda->ba->a;
**/
// Calculate the longest chain length for a specific word and return it.
int LongestChainLen(const std::string & word,
		std::unordered_map<std::string, int> & chain_len,
		const std::unordered_set<std::string> & word_set) {
	if (chain_len.find(word)!=chain_len.end()) return chain_len[word];
	const int word_size(word.size());
	int max_len(1);// For each word, its chain len is at least 1
	for (int i=0;i<word_size;++i) {
		const std::string & mut_word = word.substr(0,i)+word.substr(i+1);// try cut off every char
		if ( word_set.find(mut_word)!=word_set.end() ) {
			max_len = std::max(max_len,1+LongestChainLen(mut_word,chain_len,word_set));
		}
	}
	chain_len[word] = max_len;
	return max_len;
}

int FindLongestChain(vector<string> & words) {
	std::unordered_map<std::string, int> chain_len;
	std::unordered_set<std::string> words_set(words.begin(),words.end());
	int reval(0); // words could be empty
	for (const std::string & word : words_set) {
		reval = std::max(reval,LongestChainLen(word,chain_len,words_set));
	}
	return reval;
}


int _tmain(int argc, _TCHAR* argv[])
{
	string arr[] = {"a","abcd","bcd","abd","cd","c"};
	vector<string> vec(std::begin(arr),std::end(arr));
	int val = FindLongestChain(vec);
	assert(val==4);
	

	string arr2[]  = {"abcde","abc","ab","efabc","fabc","abc","ac","abcd","c"};
	vector<string> vec2(std::begin(arr2),std::end(arr2));
	int val2 = FindLongestChain(vec2);
	assert(val2==5);
	return 0;
}


