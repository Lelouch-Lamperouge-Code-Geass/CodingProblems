Implement a stack with methods: 

* pop
* push
* minValue 
* maxValue 
* mean
* median
* [ mode ( The most common element) ] (https://en.wikipedia.org/wiki/Mode_(statistics))


# Solution

pop, push, minValue, maxValue and mean are very easy to support. If we are only asked to support these five, a simple array with minValue, maxValue, sumOfAll, count should be enough. The mean is just (sumOfAll / count).

The tricky part comes in when we need to support median. The median is the middle point of a number set, in which half the numbers are above the median and half are below. To support this, we need to divide the numbers into smaller number set and bigger number set, and also make sure that their size difference <= 1. Therefore, we need a MinHeap and a MaxHeap.

The stack should have one MinHeap to store smaller numbers, and one MaxHeap to store bigger numbers. We can use built-in priority queue , or better,  we can also implement our own O(1) MinStack and MaxStack, like here : https://github.com/YangLiuNYU/LeetCode/blob/master/cplusplus/155_Min_Stack.md.

However, how can we support Pop() function int this case? Pop needs to pop out the recent added number and it is possible that the client keep calling Pop() function. Therefore, we definitely need a way to maintain the insertion order.





The double linked list maintains the input order. 

##### GetMax()  

Maintains a m_max_value variable. Whenever Push or Pop number, we need update this one. __Time complexity is O(1)__.

##### GetMin() 

Maintains a m_min_value variable. Whenever Push or Pop number, we need update this one. __Time complexity is O(1)__.


##### GetMean() 

Maintains a m_sum variable and m_count variable. Mean is ```m_sum / m_count```. Whenever we Push or Pop number, need update these two variables. __Time complexity is O(1)__.


##### GetMedian() 

We need a way to find the largest number in the half smaller set, and the smallest number in the half bigger set. We can use MaxHeap and MinHeap here. Or MinStack and MaxStack like this https://github.com/YangLiuNYU/LeetCode/blob/master/cplusplus/155_Min_Stack.md. This can be O(logN) or O(1) depends on the data strcture. 

This is acturally where makes pop tricky. We know that the new number get pushed can be in the middle of our "MinHeap/MinStack" or "MaxHeap/MaxStack". So these two can't give us any information about the "Push order" or our numbers, and we need to know the "Push order" (insertion order). That's why we use a double-linked-list here. 

However, how to update these two heaps/stacks when we popping item from the back of double-linked-list?

If we are using MaxHeap and MinHeap here, we probably need to implement them by ourselves so that they can support function ```Delete(int val)```. This delete operation will probably cost O(logN). 

An alternative here is to use HashMap to record the numbers that are deleted but not yet reflected in our heaps(Other information can be updated immediately within Pop function). The HashMap will look like <number-to-delete, delete-count-of-this-number> So that in our function GetMedian(), we need to compare the top() of these two heaps/stacks against the HashMap, and keep removing the top numbers and also updating the HashMap. Remember, we must maintain the size difference <= 1 of these two heaps.

If we are using MaxStack and MinStack which we need to implement from scratch, then the number to be deleted is either on top of the MaxStack or MinStack, because they maintain the insertion order. Reference : https://github.com/YangLiuNYU/LeetCode/blob/master/cplusplus/155_Min_Stack.md.


##### Push(int val) 

We push number into the double linked list. Increase m_sum and m_count.

##### Pop()  

We pop number out of the double linked list. Decrease m_sum and m_count.

And we also need to update the two heaps/stacks mentioned as above.

##### GetMode() 

