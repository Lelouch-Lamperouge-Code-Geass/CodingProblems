template <typename T>
class ThreadSafeQueue {
typedef typename std::deque<T>::iterator Iterator;
public:
	ThreadSafeQueue(){}
	void Pop(){
		std::unique_lock<std::mutex> local_lock(m_mutex);
		m_queue.pop_front();
	}
	void Push(const T & t) {
		std::unique_lock<std::mutex> local_lock(m_mutex);
		m_queue.push_back(t);
	}
	bool Empty() {
		std::unique_lock<std::mutex> local_lock(m_mutex);
		return m_queue.empty();
	}
	T Front() {
		std::unique_lock<std::mutex> local_lock(m_mutex);
		return m_queue.front();
	}

	// I define begin and end here to use for loop
	Iterator begin() {return m_queue.begin();}
	Iterator end() {return m_queue.end();}
private:

	std::mutex m_mutex;
	std::deque<T> m_queue;
};
