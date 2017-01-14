// http://www.johndcook.com/blog/standard_deviation/
// https://leetcode.com/problems/find-median-from-data-stream/

#include <cassert>
#include <queue>
#include <cmath>
#include <iostream>

typedef std::priority_queue<double,std::vector<double>,std::less<double> > MaxHeap;
typedef std::priority_queue<double,std::vector<double>,std::greater<double> > MinHeap;

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
