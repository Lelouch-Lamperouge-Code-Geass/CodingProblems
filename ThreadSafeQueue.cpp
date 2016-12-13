
// Code refered from <<C++ concurrency>>
template <typename T>
class ThreadSafeQueue {
private:
  mutable std::mutex m_mutex;
  std::queue<T> m_queue;
  std::condition_variable m_cond_var;
public:
  ThreadSafeQueue(){}
  
  ThreadSafeQueue(const ThreadSafeQueue & other) {
    std::lock_guard<std::mutex> lk(other.m_mutex);
    m_queue = other.m_queue;
  }
  
  void Push(const T & t) {
    std::lock_guard<std::mutex> lk(m_mutex);
    m_queue.push_back(t);
    m_cond_var.notify_one();
  }

  void WaitAndPop(T & t) {
    std::unique_lock<std::mutex> lk(m_mutex);
    m_cond_var.wait(lk,[this]{return !m_queue.empty();});
    t = m_queue.front();
    m_queue.pop();
  }

  std::shared_ptr<T> WaitAndPop() {
    std::unique_lock<std::mutex> lk(m_mutex);
    m_cond_var.wait(lk,[this]{return !m_queue.empty();});
    std::shared_ptr<T> res( std::make_shared<T>(m_queue.front()));
    m_queue.pop();
    return res;
  }
  
  bool TryPop(T & t){
    std::lock_guard<std::mutex> lk(m_mutex);
    if (m_queue.empty()) return false;
    t = m_queue.front();
    m_queue.pop();
    return true;
  }

  std::shared_ptr<T> TryPop(){
    std::lock_guard<std::mutex> lk(m_mutex);
    if (m_queue.empty()) return std::shared_ptr<T>();
    std::shared_ptr<T> res( std::make_shared<T>(m_queue.front()));
    m_queue.pop();
    return res;
  }
  
  bool Empty() const {
    std::lock_guard<std::mutex> lk(m_mutex);
    return m_queue.empty();
  }
};
