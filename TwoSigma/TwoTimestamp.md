A blocking queue is a queue that blocks when you try to dequeue from it and the queue is empty,  or if you try to enqueue items to it and the queue is already full.  A thread trying to dequeue from an empty queue is blocked until some other thread inserts an item into the queue.
  
Given two blocking queues，每个queue都存着timestamp，只能有getNext()来取queue里面的timestamp，
每个timestamp只能被取一次，比较这两个queue里的timestamp，如果差值<1，print这两个timestamp。

```
例如： //Q1 0.2, 1.4, 3.0 //Q2 1.0 1.1, 3.5 //output: (0.2, 1.0), (1.4, 1.0),
(0.2, 1.1), (1.4, 1.1), (3.0, 3.5)
```

最后用了两个thread,两个thread-safe queue来实现. 每次call getNext(), 和另一个queue里存的每个item相比, 相差大于一就删除, 否则输出

https://www.ibm.com/developerworks/cn/aix/library/au-multithreaded_structures1/
https://bxie.gitbooks.io/powerbook/content/two_timestamp.html

__The key point here is that we can and should only discard a item when it is useless to us. Being useless here means that there are no future items in the other queue can be paired with this item.__

What's the time compleixty here?

Let's consider the worst case first. Let's say all the items in stream one can be paired with all the items in steam two. Then if stream one have m items in total and stream two have n items in total, then the time complexity is O(m * n).

However, in practical since these two streams are very big(you can think that m and n are inifite number), and in general for any item, it can be only paired with a trivial part of items in the other stream. Therefore, the time complexity is O(m + n).

##### Follow up, what if there are ten blocking queues(let's say ten streams)?

You may give a naive solution like this : when a new item comes in for any queue, we go through other 9 queues one by one and popping out the "useless" items. This won't work! Remember the key point to discard item is "make sure that item is useless for future items come in to other queues". Therefore, we can only discard a front item if its value is 1 less than the minimal value of all tail nodes of other queue. 
                                                 
Comparing to two streams, the biggest difference how to pop out items from each queue.
  
For two streams, if a new item comes in from on stream, we lock these queues, and compare this item from the front item in 
the other queue, if the difference > 1 , we pop the front item from the other queue.

If there are multiple streams, we can't simply pop like this.  
For example, a new item comes in to Q1, and we compare the item with the front item in Q2, and if the difference > 1, can we pop the front item from Q2?  NO! Because there maybe a new item coming  to Q3 whose difference with the front item in Q2 is smaller than 1!  

Therefore, we need maintain a MinHeap for all the tail items of these queues.  

Let's see we have 10 streams, then we need 10 queues, and also a MinHeap which stores only the tail items of the 10 queues.  
If a new item comes in to Q1, here is what we are going to do:  

(1) we add it to Q1 as well as the size-10 MinHeap.    
(2) We get the Min-Item of the MinHeap, and go to check the front items of each queue, as long as the the difference between front item and the Min-Item is larger than 1, we pop the item out from the queue.    
(3) Just like what we did for two-streams, we compare the new item with all the other items of other 9 Queues.   

The key points are :

1. any item in any queue will be discarded only when it is useless  
2. any item in one queue has been compared to all the items come before it, while the reason it is still in this queue is because it is waiting for future items in the other queue   


```cpp
#include <deque>
#include <iostream>
#include <algorithm>
#include <mutex>
#include <thread>
#include <chrono>

double fRand(double fMin, double fMax)
{
  double f = (double)rand() / RAND_MAX;
  return fMin + f * (fMax - fMin);
}

struct Item {
  Item(std::string label, int val, double timestamp) : m_label(label), m_val(val), m_timestamp(timestamp){}
  std::string m_label;
  int m_val;
  double m_timestamp;
  std::string toString() {
    return m_label + "," + std::to_string(m_val) + "," + std::to_string(m_timestamp);
  }
};

class BlockingStream {
public:
  BlockingStream(int capacity, std::string label) {
    for (int i = 0; i < capacity; ++i) {
      m_items.emplace_back(Item(label, rand() % 100, fRand(1, 100)));
    }

    std::sort(m_items.begin(), m_items.end(),
              [](const Item &left, const Item &right){
                return left.m_timestamp < right.m_timestamp;
              });
  }

  bool hasItem() {
    std::unique_lock<std::mutex> lock(m_mutex_of_queue);
    return !m_items.empty();
  }
Item Pop() {
    std::this_thread::sleep_for (std::chrono::milliseconds(100));
    std::unique_lock<std::mutex> lock(m_mutex_of_queue);
    Item reval = m_items.front();
    m_items.pop_front();
    return reval;
  }
private:
  std::mutex m_mutex_of_queue;
  std::deque<Item> m_items;
};


std::deque<Item> queue_one, queue_two;
std::vector< std::pair<Item, Item> > final_result;
std::mutex my_mutex;


void calculate(std::deque<Item> &queue_one, std::deque<Item> &queue_two, const Item &item, bool is_reversed) {
  while (!queue_two.empty() && item.m_timestamp - 1 > queue_two.front().m_timestamp) {
    queue_two.pop_front();
  }

  for (const Item &temp : queue_two) {
    if (std::abs(item.m_timestamp - temp.m_timestamp) < 1) {
      if (!is_reversed) {
        final_result.emplace_back(item, temp);
      } else {
        final_result.emplace_back(temp, item);
      }
    }
  }
}
void addToQueueOne() {
  BlockingStream stream(50, "Queue one");
  while (stream.hasItem()) {
    Item item = stream.Pop();
    std::unique_lock<std::mutex> lock(my_mutex);
    queue_one.push_back(item);
    calculate(queue_one, queue_two, item, false);
  }
}

void addToQueueTwo() {
  BlockingStream stream(50, "Queue two");
  while (stream.hasItem()) {
    Item item = stream.Pop();
    std::unique_lock<std::mutex> lock(my_mutex);
    queue_two.push_back(item);
    calculate(queue_two, queue_one, item, true);
  }
}


int main() {
  std::thread t1(addToQueueOne), t2(addToQueueTwo);
  t1.join();
  t2.join();

  for (auto pair : final_result) {
    std::cout << pair.first.toString() << " , " << pair.second.toString() << std::endl;
  }
  return 0;
}
```
