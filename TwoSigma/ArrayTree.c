#include <stdio.h>
#include <stdbool.h>

struct Node {
  int m_parent_index;
  int m_val;
  bool m_is_valid;
};


void ReverseDfs(struct Node* nodes,bool* visited,int index,int n,int * capacity) {
  if (index <0 || index >= n || visited[index]) return;
  int parent_index = nodes[index].m_parent_index;
  if (parent_index != -1) { // Important check
    ReverseDfs(nodes,visited,parent_index,n,capacity);
    if ( !nodes[parent_index].m_is_valid  && nodes[index].m_is_valid ) {
      nodes[index].m_is_valid = false;
      -- (*capacity);
    }
    visited[index] = true;
  }
}

void DeleteSubTree(struct Node * nodes,int index,int n,int * capacity) {
  if (index<0 || index >=n) return; // invalid range
  
  if ( !nodes[index].m_is_valid ) {
    return ;  // already deleted
  } else {
    nodes[index].m_is_valid =  false;
    -- (*capacity);
  }
  
  bool visited[n];
  for (int i=0; i<n; ++i) {
    visited[i] = false;
  }

  visited[index] = true;

  for (int i=0; i<n; ++i) {
    if (!visited[i]) {
      ReverseDfs(nodes,visited,i,n,capacity);
    }
  }
}

void GetStatus(struct Node * nodes, int n,int * capacity) {
  printf("Tree Size : %d ",*capacity);
  for (int i=0;i<n;++i) {
    printf ( (nodes[i].m_is_valid ? "T":"F") );
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
    array_tree[i].m_is_valid = true;
  }

  GetStatus(array_tree,n,& capacity);
  DeleteSubTree(array_tree,5,n,& capacity);
  GetStatus(array_tree,n,& capacity);
  DeleteSubTree(array_tree,2,n,& capacity);
  GetStatus(array_tree,n,& capacity);
  DeleteSubTree(array_tree,3,n,& capacity);
  GetStatus(array_tree,n,& capacity);
}

int main() {
  UnitTest();
  return 0;
}
