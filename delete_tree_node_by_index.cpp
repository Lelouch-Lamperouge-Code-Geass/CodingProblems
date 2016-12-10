/*
Define a TreeNode which contains ［parent index，value，valid］at least.
Given an array of TreeNode, how can you delete a sub-stree by a given index?
Here, valid=false means the node has been deleted.
*/
struct TreeNode {
  TreeNode():m_parent_index(-1),m_valid(true),m_val(0){}
  int m_parent_index;
  bool m_valid;
  int m_val;
};


class ArrayTree {
public:
  ArrayTree(const vector<int> & input) : m_nodes(input.size(),TreeNode()) {
    const int n_size(input.size());
    for (int i=0;i<n_size;++i) {
      m_nodes[i].m_parent_index = input[i];
    }
  }
  void Delete(const int index) {
    const int n_size(m_nodes.size());
    if (index<0 || index>=n_size || m_nodes[index].m_valid==false) return;
    vector<bool> visited(n_size,false);
    visited[index] = true;
    m_nodes[index].m_valid = false;
    
    for (int i=0;i<n_size;++i) {
      if (!visited[i]) {
        // go through all nodes, and traverse up until meet visited node
        // or reach root node
        ReverseDfs(i,visited);
      }
    }
  }
  std::string GetStatus() {
    const int nodes_size(m_nodes.size());
    ostringstream oss;
    for (int i=0;i<nodes_size;++i) {
      oss << (m_nodes[i].m_valid? "T":"F");
      if (i!=nodes_size-1) oss<<',';
    }
    return oss.str();
  }
private:
  // reverse depth-first-search to its parent node until meet visited node
  // or reach root node. If it is visited, unwinding back.
  // This will make sure we only visit each node twice.
  // Running time is O(N);
  void ReverseDfs(int index,vector<bool> & visited) {
    if (index<0 || index>=m_nodes.size() || visited[index]) return;
    visited[index] = true;
    TreeNode &cur_node = m_nodes[index], &parent_node = m_nodes[cur_node.m_parent_index];
    ReverseDfs(cur_node.m_parent_index,visited);
    if(!parent_node.m_valid) cur_node.m_valid = parent_node.m_valid; // If parent is not valid, so is current node 
  }
  vector<TreeNode> m_nodes;
};



int _tmain(int argc, _TCHAR* argv[])
{
	int arr[] = {-1,0,1,1,3,3,3,5};
	ArrayTree tree(vector<int>(std::begin(arr),std::end(arr)));
	string temp = tree.GetStatus();
	assert(temp=="T,T,T,T,T,T,T,T");
	tree.DeleteSubTree(5);
	temp = tree.GetStatus();
	assert(temp=="T,T,T,T,T,F,T,F");
	tree.DeleteSubTree(2);
	temp = tree.GetStatus();
	assert(temp=="T,T,F,T,T,F,T,F");
	tree.DeleteSubTree(3);
	temp = tree.GetStatus();
	assert(temp=="T,T,F,F,F,F,F,F");
	return 0;
}
