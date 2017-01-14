// http://stackoverflow.com/questions/32748069/the-reason-of-using-stdgreater-for-creating-min-heap-via-priority-queue
// http://www.johndcook.com/blog/standard_deviation/
// https://leetcode.com/problems/find-median-from-data-stream/

// the implementation of pop_heap uses something called sift_down (and push_heap uses sift_up
#include <cassert>
#include <queue>
#include <cmath>
#include <iostream>
#include <algorithm>

class MaxHeap {
public:
  MaxHeap() {}
  void push(double number) {
    // Add the number to the vector
    m_values.push_back(number);
    // Placing the last value at the front element and restore the heap
    // I have to say, std::less is very confusing here for a max-heap
    std::push_heap(m_values.begin(),m_values.end(),std::less<double>());
  }
  
  void pop() {
    // put the front element at the back of the sequence and reduce
    // the size of the heap by one
    std::pop_heap(m_values.begin(),m_values.end(),std::less<double>());
    // Actually remove the top element
    m_values.pop_back();
  }
  // Notice that the top element is always at front
  double top() const { return m_values.front(); }
  
  double KthElement(std::size_t k) const {
    if(k<1||k>m_values.size()) {
      return top();
    } else {
      return m_values[m_values.size()-k];
    }
  }
  std::size_t size() const { return m_values.size();}
private:
  std::vector<double> m_values;
};

class MinHeap {
public:
  MinHeap() {}
  void push(double number) {
    m_values.push_back(number);
    std::push_heap(m_values.begin(),m_values.end(),std::greater<double>());
  }
  void pop() {
    // put the minimum element at the back of the sequence
    // and reduce the size of the heap by one
    std::pop_heap(m_values.begin(),m_values.end(),std::greater<double>());
    m_values.pop_back();
  }
  double top() const { return m_values.front(); }
  double KthElement(std::size_t k) const{
    
  }
  std::size_t size() const { return m_values.size();}
private:
  std::vector<double> m_values;
};

class RunningStat {
public:
  RunningStat() :m_count(0),m_mean(0),m_sum_of_square(0){
  }
  void AddNumber(double num) {
    // Update statistics
    UpdateStat(num);

    // Add the number
    if (m_max_heap.size() > m_min_heap.size()) {
      // pop one number from max heap and add it to min heap
      m_max_heap.push(num);
      m_min_heap.push(m_max_heap.top());
      m_max_heap.pop();
    } else {
      // pop one number from min heap and add it to max heap
      m_min_heap.push(num);
      m_max_heap.push(m_min_heap.top());
      m_min_heap.pop();
    }    
  }

  // priority_queue doesn't support random access.
  // In order to get constant time complexity, have to implement heap.
  double KthElement(int k) const {
    
  }
  
  double GetMedian() const {
    return m_max_heap.size() > m_min_heap.size() ? m_max_heap.top() :( m_max_heap.top() + m_min_heap.top() ) / 2.0;
  }
  double GetMean () const {
    return m_count>0? m_mean : 0;
  }
  double GetVariance() const {
    return m_count > 1 ? m_sum_of_square/(m_count-1) : 0;
  }
  double GetStandardDeviation() const {
    return std::sqrt(GetVariance());
  }
private:
  void UpdateStat(double number) {
    ++ m_count;
    double pre_mean = m_mean;
    m_mean += (number - pre_mean) / m_count;
    m_sum_of_square +=  (number-pre_mean) * (number-m_mean);
  }
  
  MaxHeap m_max_heap;
  MinHeap m_min_heap;
  
  std::size_t m_count;
  double m_mean;
  double m_sum_of_square;
};

void UnitTest() {
  RunningStat running_stat;
  running_stat.AddNumber(1);
  assert(running_stat.GetMedian() == 1);
  running_stat.AddNumber(2);
  assert(running_stat.GetMedian() == 1.5);
  running_stat.AddNumber(3);
  assert(running_stat.GetMedian() == 2);
  running_stat.AddNumber(7);
  running_stat.AddNumber(9);
  assert(running_stat.GetMean() == 4.4);
  assert(running_stat.GetMedian() == 3);
}

void UnitTest_2() {
  RunningStat running_stat;
  running_stat.AddNumber(1);
  assert(running_stat.GetStandardDeviation()==0);
  running_stat.AddNumber(1);
  running_stat.AddNumber(10);
  assert(running_stat.GetMean()==4);
  assert(running_stat.GetStandardDeviation() == 5.196152422706632);
  running_stat.AddNumber(20);
  running_stat.AddNumber(50);
  running_stat.AddNumber(50);
  assert(running_stat.GetStandardDeviation() == 22.794736234490628);
  
}

int main() {
  UnitTest();
  UnitTest_2();
  return 0;
}
