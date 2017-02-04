#include <thread>
#include <iostream>
#include <queue>
#include <chrono>
#include <vector>
#include <mutex>

std::queue<int> timestamp_one, timestamp_two;

void TimeStampStreamOne() {
  std::deque<int> vals;
  for (int i=0;i<10;++i) {
    vals.push_back(rand()%100);
  }
  std::sort(vals.begin(),vals.end());
  
  while ( !vals.empty() ) {
    std::this_thread::sleep_for (std::chrono::seconds(rand()%3));
    std::cout <<"Queue One : " << vals.front() << std::endl;
    timestamp_one.push( vals.front());
    vals.pop_front();
  }
}

void TimeStampStreamTwo() {
  std::deque<int> vals;
  for (int i=0;i<10;++i) {
    vals.push_back(rand()%100);
  }
  std::sort(vals.begin(),vals.end());
  
  while ( !vals.empty() ) {
    std::this_thread::sleep_for (std::chrono::seconds(rand()%3));
    std::cout <<"Queue Two : " << vals.front() << std::endl;
    timestamp_two.push( vals.front());
    vals.pop_front();
  }
}

std::mutex my_mutex;
std::deque<int> queue_one, queue_two;

void calculate(std::deque<int> & q1, std::deque<int> & q2, int val, bool is_reverse) {
  q1.push_back(val);
  while (!q2.empty() && val-q2.front()>10) {
    q2.pop_front();
  }
  for (int q2_val : q2) {
    if (std::abs(val-q2_val) <=10) {
      if (!is_reverse) std::cout <<val<<" : "<<q2_val << std::endl;
      else std::cout <<q2_val<<" : "<<val << std::endl;
    } 
      
  }
}


void Task1() {
  while (true) {
    if (!timestamp_one.empty()) {
      int val = timestamp_one.front();
      timestamp_one.pop();
      std::unique_lock<std::mutex> local_lock(my_mutex);
      calculate(queue_one,queue_two,val,false);
    }
  }
}

void Task2() {
  while (true) {
    if (!timestamp_two.empty()) {
      int val = timestamp_two.front();
      timestamp_two.pop();
      std::unique_lock<std::mutex> local_lock(my_mutex);
      calculate(queue_two,queue_one,val,true);
    }
  }
}

int main() {
  // These two threads keep adding values to the two queues
  std::thread t1(TimeStampStreamOne), t2(TimeStampStreamTwo);
  t1.join();
  t2.join();
  std::thread task1(Task1), task2(Task2);
  task1.join();
  task2.join();
  
  return 0;
}
