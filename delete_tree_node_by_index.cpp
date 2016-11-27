/*
Define a TreeNode which contains ［parent index，value，valid］at least.
Given an array of TreeNode, how can you delete a sub-stree by a given index?
Here, valid=false means the node has been deleted.
*/
struct ArrayTreeNode{
	ArrayTreeNode(int pix):m_parent_index(pix),m_value(0),m_valid(true),m_visited(false){}
    int m_parent_index;
	int m_value;
    bool m_valid;
	bool m_visited;
};

class ArrayTree {
public:
	ArrayTree(const vector<int> & nums) {// parent id vector
		for (const int num: nums) {
			m_nodes.push_back(ArrayTreeNode(num));
		}
		m_tree_size = m_nodes.size();
	}
	void DeleteSubTree(int index) {
		const int nodes_size(m_nodes.size());
		if (index>=0 && index<nodes_size) {// index must be valid
			// first of all, invalidate the target node
			m_nodes[index].m_valid = false;
			m_nodes[index].m_visited = true;
			-- m_tree_size;
			// go through all nodes, and traverse up until meet visited node
			// or reach root node
			for (int i=0;i<nodes_size;++i) {
				reverse_dfs(i);
			}
		}
		// Eventually, for those valid nodes, we need set m_visited to be false
		// for future process.
		for (int i=0;i<nodes_size;++i) {
			if (m_nodes[i].m_valid) {
				m_nodes[i].m_visited = false;
			}
		}
	}
	string GetStatus() {
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
	void reverse_dfs(int index){
		if (index==-1 || m_nodes[index].m_visited) return;
		m_nodes[index].m_visited = true;
		int parent_index = m_nodes[index].m_parent_index;
		reverse_dfs(parent_index); // keep traversing up
		// traverse down and update m_valid
		if(parent_index!=-1 && !m_nodes[parent_index].m_valid){
			m_nodes[index].m_valid =  m_nodes[parent_index].m_valid;
			-- m_tree_size;
		}
	}
	vector<ArrayTreeNode> m_nodes;
	int m_tree_size;
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
