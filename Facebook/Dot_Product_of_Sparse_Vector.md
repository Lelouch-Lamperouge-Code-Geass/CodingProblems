Suppose we have very large sparse vectors, which contains a lot of zeros and double .

* find a data structure to store them  
* get the dot product of them  

# Knowledge

In mathematics, the __dot product__ or __scalar product__ is an algebraic operation that takes two equal-length sequences of numbers (usually coordinate vectors) and returns a single number. In Euclidean geometry, the dot product of the Cartesian coordinates of two vectors is widely used and often called inner product (or rarely projection product).

Algebraically, the dot product is the sum of the products of the corresponding entries of the two sequences of numbers. Geometrically, it is the product of the Euclidean magnitudes of the two vectors and the cosine of the angle between them. These definitions are equivalent when using Cartesian coordinates. In modern geometry, Euclidean spaces are often defined by using vector spaces. In this case, the dot product is used for defining lengths (the length of a vector is the square root of the dot product of the vector by itself) and angles (the cosine of the angle of two vectors is the quotient of their dot product by the product of their lengths).

> __Algebraic definition__  
  The dot product of two vectors a = [a1, a2, ..., an] and b = [b1, b2, ..., bn] is defined as:
  ![alt](https://wikimedia.org/api/rest_v1/media/math/render/svg/69f8ac1d2b7ffb9ef70bb6b151a4b931f20087a5)
  
# Solution
You can do it if your vectors are stored as a linked list of tuples whith each tuple containing the index and the value of a non zero element and sorted by the index.

You iterate through both vectors, by selecting the next element from the vector where you are at the lower index. If the indexes are the same you multiply the elements and store the result.

Repeat until one list reaches the end.

Since you have one step per non zero element in each list, the complexity is O(m+n) as required.

Footnote: The datastructure doesn't have to be linked list, but must provide a O(1) way to access the next non 0 element and it's index.
