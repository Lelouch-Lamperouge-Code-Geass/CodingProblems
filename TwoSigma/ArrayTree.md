Remove subtree from tree 给的程序是用C写的，很长，大部分不用看，只需要写一个子函数，要现场编译现场跑给定一个数组，数组的每个元素就是一个节点(struct node)，大概的长得像下面这样 

```
struct node{ int parent; int val; bool valid; }; 
```

#### 思路一

parent代表当前node的parent 在数组里的index，root node的parent是-1. 所以node 是child指向parent的。给定一个数组和数组的某个index，删除这个index以及它的子树(只需要将node里的valid置为false即可)，只能用O(n)的空间复杂度 解法：在strcut node里面添加一个新的元素visited（一定要记得在程序里初始化node的地方，把visited设为false），代表该node是否被访问过。然后从头到尾访问输入数组。对于当前访问的元素，如果已经被visited了，则忽略。否则，沿着parent指针走，直到到达根节点（则从当前node到根节点的所有node都不需要delete），或者到达一个被标记为删除的节点（则当前node到根节点所有的node都需要被删除） 

```
struct node { int parent; int val; bool valid; bool visited; }; 
```

#### 思路二

思路一整体上是正确的，但是往node里面加visited作为成员变量是我并不欣赏的做法，它使得这个成员变量的意义仅仅是为了满足算法的需要。程序员在设计Class的时候要追求极简主义(Minimalism). 其实这里只需要一个 ```vector<bool> visited```就可以了。

# Code

### C programming language

```c
#include <stdio.h>
#include <stdbool.h>

struct Node {
  int m_parent_index;
  int m_val;
  bool m_valid;
};

void ReverseDfs(struct Node *nodes, int *capacity, const int nodes_size, const int index, bool* visited) {
  if (index < 0 || index >= nodes_size) return; // invalid index
  if (visited[index]) return; // already visited
  if (!nodes[index].m_valid) return; // current node was deleted by previous operation

  // Check current node's parent first
  int parent_index = nodes[index].m_parent_index;
  ReverseDfs(nodes, capacity, nodes_size, parent_index, visited);


  // If parent node is deleted, so should current node
  if (parent_index>=0 && parent_index < nodes_size && !nodes[parent_index].m_valid) {
    nodes[index].m_valid = false;
    -- (*capacity);
  }

  visited[index] = true; // mark current node as visited
}

void DeleteSubTree(struct Node *nodes, int *capacity, const int nodes_size, const int index) {
  if (index < 0 || index >= nodes_size) return; // invalid index
  if (!nodes[index].m_valid) return; // can't delete node twice


  bool visited[nodes_size];
  for (int i=0; i<nodes_size; ++i) {
    visited[i] = false;
  }


  nodes[index].m_valid = false;
  -- (*capacity);
  visited[index] = true;

  for (int i = 0; i < nodes_size; ++i) {
    ReverseDfs(nodes, capacity, nodes_size, i, visited);
  }
}

void GetStatus(struct Node * nodes, int * capacity, int n) {
  printf("Tree Size : %d ",*capacity);
  for (int i=0;i<n;++i) {
    printf ( (nodes[i].m_valid ? "T":"F") );
  }
  printf("\n");
}

void UnitTest() {
  const int n = 8;

  int capacity = 8;
  int parent_indices[] = {-1,0,1,1,3,3,3,5};
  struct Node array_tree[n];
  for (int i=0;i<n;++i) {
    array_tree[i].m_parent_index = parent_indices[i];
    array_tree[i].m_valid = true;
  }

  GetStatus(array_tree,& capacity, n); // 8 TTTTTTTT
  
  DeleteSubTree(array_tree, & capacity, n, 5);
  GetStatus(array_tree, & capacity, n); // 6 TTTTTFTF
  
  DeleteSubTree(array_tree, & capacity, n, 2);
  GetStatus(array_tree, & capacity, n); // 5 TTFTTFTF
  
  DeleteSubTree(array_tree, & capacity, n, 3);
  GetStatus(array_tree, & capacity, n); // 2 TTFFFFFF
  
  DeleteSubTree(array_tree, & capacity, n, 3);
  GetStatus(array_tree, & capacity, n); // 2 TTFFFFFF
  
  DeleteSubTree(array_tree, & capacity, n, 0);
  GetStatus(array_tree, & capacity, n); // 0 FFFFFFFF

}

int main() {
  UnitTest();
  return 0;
}
```

### C++
