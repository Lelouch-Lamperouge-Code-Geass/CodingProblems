Define a TreeNode which contains ［parent index，value，valid］at least.

Given an array of TreeNode, how can you delete a sub-stree by a given index?

Here, valid=false means the node has been deleted.


Some about C programming language:

* C has no reference, if you want to use reference, use pointer
* Important to set the value of array one by one, otherwise the dumb compiler may give random true/false values.
* A C variable declaration just tells the compiler to set aside and name an area of memory for you. For automatic variables, also known as stack variables, the values in that memory are not changed from what they were before.

```c
#include <stdio.h>
#include <stdbool.h>

struct Node {
  int m_parent_index;
  bool m_is_valid;
  int m_val;
};

// Clean up the tree after make one node to be deleted.
void CleanTreeWithReverseDFS(struct Node array_tree[],
                             const int tree_capacity,
                             int * const tree_size,
                             int index,
                             bool visited[]) {
  if (index < 0 || index >= tree_capacity) return; // invalid index

  if (visited[index]) return; // already visited

  // Current node was deleted by previous operation.
  if (!array_tree[index].m_is_valid) return;

  visited[index] = true; // Mark it as visited

  int parent_index = array_tree[index].m_parent_index;
  if (parent_index >=0 && parent_index < tree_capacity) {
    // If parent exists, go check parent first
    CleanTreeWithReverseDFS(array_tree, tree_capacity, tree_size, parent_index, visited);

    // If parent node is deleted, so should current node.
    // Must check whether current node is already deleted or not.
    // Otherwise, you may decrease tree_size twice!
    if (!array_tree[parent_index].m_is_valid) {
      if (array_tree[index].m_is_valid) {
        // Parent is invalid but current node is valid, delete current node
        array_tree[index].m_is_valid = false;
        -- *tree_size;
      }
    }
  }
}

void DeleteSubTree(struct Node array_tree[],
                   const int tree_capacity,
                   int * const tree_size,
                   int sub_index) {
  if (sub_index < 0 || sub_index >= tree_capacity) return; // invalid index

  // Important check, we can't delete onde node twice.
  if (!array_tree[sub_index].m_is_valid) return;

  // Important to set the value to be false one by one.
  // Otherwise the dumb compiler may give random true/false values
  bool visited[tree_capacity]; 
  for (int i = 0; i < tree_capacity; ++i) visited[i] = false;


  // Mark this node to be deleted.
  array_tree[sub_index].m_is_valid = false;
  -- *tree_size;
  visited[sub_index] = true;

  // Scan the every nodes and perform clean-up
  for (int i = 0; i < tree_capacity; ++i) {
    CleanTreeWithReverseDFS(array_tree, tree_capacity, tree_size, i, visited);
  }

}

// Print the tree status.
void GetStatus(struct Node * nodes, const int capacity, const int * const tree_size) {
  printf("Tree capacity : %d. Tree size : %d.  ", capacity, *tree_size);
  for (int i = 0; i < capacity; ++i) {
    printf ( (nodes[i].m_is_valid ? "T":"F") );
  }
  printf("\n");
}

void UnitTest() {
  const int capacity = 8;
  int tree_size = 8;
  int parent_indices[] = {-1,0,1,1,3,3,3,5};
  struct Node array_tree[capacity];
  for (int i=0;i < capacity;++i) {
    array_tree[i].m_parent_index = parent_indices[i];
    array_tree[i].m_is_valid = true;
  }

  GetStatus(array_tree, capacity, &tree_size);
  DeleteSubTree(array_tree,  capacity, &tree_size, 5);
  GetStatus(array_tree,  capacity, &tree_size);
  DeleteSubTree(array_tree,  capacity, &tree_size, 2);
  GetStatus(array_tree,  capacity, &tree_size);
  DeleteSubTree(array_tree,  capacity, &tree_size, 3);
  GetStatus(array_tree,  capacity, &tree_size);
  DeleteSubTree(array_tree,  capacity, &tree_size, 3);
  GetStatus(array_tree,  capacity, &tree_size);
  DeleteSubTree(array_tree,  capacity, &tree_size, 0);
  GetStatus(array_tree,  capacity, &tree_size);
}

int main() {
  UnitTest();
  return 0;
}
```

The output should be :

```
Tree capacity : 8. Tree size : 8.  TTTTTTTT
Tree capacity : 8. Tree size : 6.  TTTTTFTF
Tree capacity : 8. Tree size : 5.  TTFTTFTF
Tree capacity : 8. Tree size : 2.  TTFFFFFF
Tree capacity : 8. Tree size : 2.  TTFFFFFF
Tree capacity : 8. Tree size : 0.  FFFFFFFF
```
