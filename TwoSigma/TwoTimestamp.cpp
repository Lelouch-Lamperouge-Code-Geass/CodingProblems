/*
A blocking queue is a queue that blocks when you try to dequeue from it and the queue is empty, 
or if you try to enqueue items to it and the queue is already full. 
A thread trying to dequeue from an empty queue is blocked until some other thread inserts an item into the queue.
Given two blocking queues，每个queue都存着timestamp，只能有getNext()来取queue里面的timestamp，
每个timestamp只能被取一次，比较这两个queue里的timestamp，如果差值<1，print这两个timestamp。
例如： //Q1 0.2, 1.4, 3.0 //Q2 1.0 1.1, 3.5 //output: (0.2, 1.0), (1.4, 1.0),
(0.2, 1.1), (1.4, 1.1), (3.0, 3.5)
最后用了两个thread,两个thread-safe queue来实现. 每次call getNext(),
和另一个queue里存的每个item相比, 相差大于一就删除, 否则输出
https://www.ibm.com/developerworks/cn/aix/library/au-multithreaded_structures1/
https://bxie.gitbooks.io/powerbook/content/two_timestamp.html

// Follow up, what if there are ten blocking queues(let's say ten streams)?
Comparing to two streams, the biggest difference how to pop out items from each queue.
For two streams, if a new item comes in from on stream, we lock these queues, and compare this item from the front item in 
the other queue, if the difference > 1 , we pop the front item from the other queue.

If there are multiple streams, we can't simply pop like this.
For example, a new item comes in to Q1, and we compare the item with the front item in Q2, and if the difference > 1, can we
pop the front item from Q2? 
NO! Because there maybe a new item coming  to Q3 whose difference with the front item in Q2 is smaller than 1!

Therefore, we need maintain a MinHeap for all the tail items of these queues.
Let's see we have 10 streams, then we need 10 queues, and also a MinHeap which stores only the tail items of the 10 queues.
If a new item comes in to Q1, here is what we are going to do:
(1) we add it to Q1 as well as the size-10 MinHeap.
(2) We get the Min-Item of the MinHeap, and go to check the front items of each queue, as long as the the difference between 
front item and the Min-Item is larger than 1, we pop the item out from the queue.
(3) Just like what we did for two-streams, we compare the new item with all the other items of other 9 Queues.
*/

#include <deque>
#include <mutex>
#include <vector>
#include <random>
#include <thread>
#include <iostream>

class TimestampStream {
public:
  TimestampStream(const std::vector<double> & input) : m_pos(0){
    m_values = input;
  }
  bool HasNext() { return m_pos<m_values.size();}
  double GetNext() { return m_values[m_pos++]; }
private:
  int m_pos;
  std::vector<double> m_values;
};

std::mutex m_mutex;
std::deque<double> q1, q2;
std::vector<std::pair<double, double> > m_res;

void Calculate(std::deque<double>& q1, std::deque<double>& q2, double val,bool reverse_pair) {
  q1.push_back(val);
  while (!q2.empty() && val - q2.front() >= 1) {
    q2.pop_front();
  }
  for (double num : q2) {
    if (std::abs(val - num) < 1) {
      if (!reverse_pair) m_res.push_back(std::make_pair(val, num));
      else m_res.push_back(std::make_pair(num, val));
    }
  }
  
}

// function that will be executed by thread 1
void Task1(TimestampStream & ss) {
  while (true) {
    if(!ss.HasNext()) break;
    double val = ss.GetNext();
    std::unique_lock<std::mutex> local_lock(m_mutex);  // RAII
    Calculate(q1, q2, val,false);
  }
}

// function that will be executed by thread 2
void Task2(TimestampStream & ss) {
  while (true) {
    if(!ss.HasNext()) break;
    double val = ss.GetNext();
    std::unique_lock<std::mutex> local_lock(m_mutex);
    Calculate(q2, q1, val,true);
  }
}

int main() {
  std::vector<double> input1 = {0.2, 1.4, 3.0}, input2 = {1.0, 1.1, 3.5};
  TimestampStream stream1(input1), stream2(input2);

  std::thread t1(Task1, std::ref(stream1)), t2(Task2, std::ref(stream2) );

  t1.join();
  t2.join();

  for(auto & item :  m_res) {
    std::cout <<item.first<<':'<<item.second<<std::endl;
  }
  return 0;
}
