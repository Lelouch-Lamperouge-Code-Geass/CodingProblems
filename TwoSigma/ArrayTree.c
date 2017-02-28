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

  GetStatus(array_tree,& capacity, n);
  DeleteSubTree(array_tree, & capacity, n, 5);
  GetStatus(array_tree, & capacity, n);
  DeleteSubTree(array_tree, & capacity, n, 2);
  GetStatus(array_tree, & capacity, 2);
  DeleteSubTree(array_tree, & capacity, n, 3);
  GetStatus(array_tree, & capacity, n);
  DeleteSubTree(array_tree, & capacity, n, 3);
  GetStatus(array_tree, & capacity, n);
  DeleteSubTree(array_tree, & capacity, n, 0);
  GetStatus(array_tree, & capacity, n);

}



int main() {
  UnitTest();
  return 0;
}
