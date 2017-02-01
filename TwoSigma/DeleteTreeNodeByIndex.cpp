
/*
Define a TreeNode which contains ［parent index，value，valid］at least.
Given an array of TreeNode, how can you delete a sub-stree by a given index?
Here, valid=false means the node has been deleted.
*/

#include <vector>
#include <sstream>
#include <cassert>
#include <iostream>

class TreeNode {
public:
  TreeNode():m_parent_index(-1),m_value(-1),m_is_valid(true){}
private:
  friend class ArrayTree;
  int m_parent_index;
  int m_value;
  bool m_is_valid;
};

class ArrayTree {
public:
  ArrayTree(const std::vector<int> & vec) : m_capacity(vec.size()),m_size(vec.size()),m_nodes(m_capacity,TreeNode()){
    for (int i=0;i<m_capacity;++i) {
      m_nodes[i].m_parent_index = vec[i];
      m_nodes[i].m_value = i;
    }
  }
  void Delete(int index) {
    if (index<0 || index >=m_capacity || !m_nodes[index].m_is_valid) return;
    std::vector<bool> visited(m_capacity,false);
    m_nodes[index].m_is_valid = false;
    -- m_size; // invalidated one node
    visited[index] = true;
    for (int i=0;i<m_capacity;++i) {
      if(!visited[i])
        DeleteWithReverseDfs(i,visited);
    }
  }
  int GetSize() {return m_size;}
  
  std::string GetStatus() {
    std::ostringstream oss;
    for (int i=0;i<m_capacity;++i) {
      oss << (m_nodes[i].m_is_valid? "T":"F");
      if (i!=m_capacity-1) oss<<',';
    }
    return oss.str();
  }
  
private:
   // reverse depth-first-search to its parent node until meet visited node
  // or reach root node. If it is visited, unwinding back.
  // This will make sure we only visit each node twice.
  // Running time is O(N);
  void DeleteWithReverseDfs(int index,std::vector<bool> & visited){
    if (index<0 || visited[index]) return;
    int pix = m_nodes[index].m_parent_index;
    DeleteWithReverseDfs(pix,visited);
    if (!m_nodes[pix].m_is_valid && m_nodes[index].m_is_valid){
      m_nodes[index].m_is_valid = false;
      -- m_size;
    }
    visited[index] = true;
  }
  int m_capacity;
  int m_size;
  std::vector<TreeNode> m_nodes;
  
};

void UnitTest_ArrayTree() {
  int arr[] = {-1,0,1,1,3,3,3,5};
  ArrayTree tree(std::vector<int>(std::begin(arr),std::end(arr)));
  std::string temp = tree.GetStatus();
  assert(temp=="T,T,T,T,T,T,T,T");
  tree.Delete(5);
  temp = tree.GetStatus();
  assert(temp=="T,T,T,T,T,F,T,F");
  assert(tree.GetSize()==6);
  
  tree.Delete(2);
  temp = tree.GetStatus();
  assert(temp=="T,T,F,T,T,F,T,F");
  assert(tree.GetSize()==5);
  
  tree.Delete(3);
  temp = tree.GetStatus();
  assert(temp=="T,T,F,F,F,F,F,F");
  assert(tree.GetSize()==2);
}

int main() {
  UnitTest_ArrayTree();
  return 0;
 
}
