Implement a stack with methods: 

* pop
* push
* minValue 
* maxValue 
* mean
* median
* mode ( The most common element)


# Solution

pop, push, minValue, maxValue and mean are very easy to support. If we are only asked to support these five, a simple array with minValue, maxValue, sumOfAll, count should be enough. The mean is just (sumOfAll / count).

The tricky part comes in when we need to support median. The median is the middle point of a number set, in which half the numbers are above the median and half are below. To support this, we need to divide the numbers into smaller number set and bigger number set, and also make sure that their size difference <= 1. Therefore, we need a MinHeap and a MaxHeap.





