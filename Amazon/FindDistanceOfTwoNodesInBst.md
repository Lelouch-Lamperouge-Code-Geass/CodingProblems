Give an array, build a BST, and write a function to return the distance between any two nodes.

```cpp
struct BstTreeNode {
	int m_val;
	BstTreeNode  *m_leftchild;
	BstTreeNode  *m_rightchild;
	BstTreeNode(int val)
		: m_val(val), m_leftchild(nullptr), m_rightchild(nullptr) {}

	~BstTreeNode() {
		delete m_leftchild;
		delete m_rightchild;
		m_leftchild = nullptr;
		m_rightchild = nullptr;
	}
};

// Add a new node in the BST.
void insertNode(BstTreeNode *&root, int num) {
	if (!root) {
		root = new BstTreeNode(num);
	}
	else {
		if (root->m_val > num) {
			insertNode(root->m_leftchild, num);
		}
		else {
			insertNode(root->m_rightchild, num);
		}
	}
}

// Return the root node of the BST generated with numbers.
BstTreeNode* buildBST(const vector<int> &numbers) {
	BstTreeNode *root(nullptr);
	for (int num : numbers) {
		insertNode(root, num);
	}
	return root;
}

// Return the distance from one node to its child node
// which has the value node_val.
int distanceToChild(BstTreeNode *root, int node_val) {
	int distance(0);
	while (root) {
		if (root->m_val == node_val) {
			return distance;
		}
		else {
			++distance;
			if (root->m_val > node_val) {
				root = root->m_leftchild;
			}
			else {
				root = root->m_rightchild;
			}
		}
	}
	return distance;
}

// Return the lowest common ancestor of two nodes.
// You can assume that these two nodes are in this BST.
BstTreeNode* lowestCommonAncestor(BstTreeNode *root, int value_of_node_one, int value_of_node_two) {
	while (root) {
		if (root->m_val > value_of_node_one && root->m_val > value_of_node_two) {
			root = root->m_leftchild;
		}
		else if (root->m_val < value_of_node_one && root->m_val < value_of_node_two) {
			root = root->m_rightchild;
		}
		else { // root->val is within the value of p,q inclusively
			return root;
		}
	}
	return root;
}

// Return the distance between two nodes in the BST.
int distanceOfTwoNodes(BstTreeNode *root, int node_one, int node_two) {
	BstTreeNode * lowest_common_ancestor = lowestCommonAncestor(root, node_one, node_two);
	int distance_to_node_one = distanceToChild(lowest_common_ancestor, node_one);
	int distance_to_node_two = distanceToChild(lowest_common_ancestor, node_two);
	return distance_to_node_one + distance_to_node_two;
}

void UnitTest() {
	vector<int> numbers = { 5,6,3,1,2,4 };
	BstTreeNode *root = buildBST(numbers);
	assert(distanceOfTwoNodes(root, 1, 6) == 3);
	assert(distanceOfTwoNodes(root, 1, 4) == 2);
	assert(distanceOfTwoNodes(root, 4, 6) == 3);
	assert(distanceOfTwoNodes(root, 2, 6) == 4);
	delete root;
	root = nullptr;

	numbers = { 5,2,12,1,3,9,21,19,25 };
	root = buildBST(numbers);
	assert(distanceOfTwoNodes(root, 9, 25) == 3);
	assert(distanceOfTwoNodes(root, 2, 19) == 4);
	assert(distanceOfTwoNodes(root, 3, 3) == 0);
	assert(distanceOfTwoNodes(root, 1, 25) == 5);
}

int main()
{
	UnitTest();
	return 0;
}
```
