// Given an Iterator class of a random number collection, write a new Iterator class
// which only iterates numbers who mods five ==0. For example,5,25,15,90.

class Iterator {
public:
	Iterator(const vector<int>& nums):
	m_nums(nums),
	m_nums_size(nums.size()),
	m_pos(0){

	}
    Iterator(const Iterator& iter);
	virtual ~Iterator(){}
    	// Returns the next element in the iteration.
	int next(){
		return m_nums[m_pos++];
	}
    	// Returns true if the iteration has more elements.
	bool hasNext(){
		return m_pos < m_nums_size;
	}
	void remove(){}
private:
	vector<int> m_nums;
	int m_nums_size;
	int m_pos;
};

class ModFiveIterator : public Iterator {
    int m_res;
    bool m_peeked; // peeked next number or not, specificlly whether m_next_five has been updated or not
public:
	ModFiveIterator(const vector<int>& nums):
	Iterator(nums),
	m_res(-1),
	m_peeked(false){

	}
    int next() {
        hasNext();
        m_peeked = false;
        return m_res;
    }
    
    bool hasNext()  {
	if(m_peeked) {
		// already peeked the next valid number
		return true;
	} else {
		// Let's peek the next number which%5==0
    		while(Iterator::hasNext()) {
			m_res = Iterator::next();
			if (m_res % 5 ==0) {
				m_peeked = true;
				return true;
			}
		}
		return false; // not found
	}
    }
    
};



int _tmain(int argc, _TCHAR* argv[])
{

	vector<int> nums;
	for (int i=1;i<=20;++i) {
		nums.push_back(std::rand());
	}
	Iterator iter = Iterator(nums);
	while(iter.hasNext()){
		std::cout<< iter.next()<<',';
	}
	std::cout << std::endl;
	ModFiveIterator five_iter = ModFiveIterator(nums);
	while(five_iter.hasNext()){
		std::cout<< five_iter.next()<<',';
	}
	std::cout << std::endl;
	return 0;
}

