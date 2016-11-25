/**
longest chain
类似word ladder，对于一个单词删掉任何一个字母，如果新单词出现在给的词典里 
那么就形成一个 chain： old word -> new word -> newer word, 求最长长度(return int) 
比如给vector<string> w = {a,ba,bca,bda,bdca} 最长是4： bdca->bda->ba->a;
**/
int LongestChainLength(const string & word,unordered_map<string,int> & longest_chain_len,unordered_set<string> & dict){
	if (longest_chain_len.find(word) !=longest_chain_len.end()) return longest_chain_len[word];
	const int word_len = word.size();
	int res(1);// default the chain only contains itself
	for (int i=0;i<word_len;++i) {
		string temp = word.substr(0,i)+word.substr(i+1); // delete one char
		if (dict.find(temp)!=dict.end()) { // sub-word exists
			res = std::max(res, LongestChainLength(temp,longest_chain_len,dict) + 1);
		}
	}
	longest_chain_len[word] = res;
	return res;
}

int FindLongestChain(vector<string> & words) {
	unordered_map<string,int> longest_chain_len; // word and its relative longest chain, avoid duplicate calculation
	unordered_set<string> dict;
	for (const string & word : words) {
		dict.insert(word);
	}

	int reval(0);

	for (string & word : words) {
		int len = LongestChainLength(word,longest_chain_len,dict);
		reval = std::max(reval,len);
	}
	return reval;
}

int main(){
	string arr[] = {"a","abcd","bcd","abd","cd","c"};
	vector<string> vec(std::begin(arr),std::end(arr));
	int val = FindLongestChain(vec);
	return 0;
}
