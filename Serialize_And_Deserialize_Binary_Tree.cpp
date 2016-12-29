#include <iostream>
#include <cassert>
#include <vector>
#include <string>
#include <sstream>

using namespace std;

struct TreeNode {
  int val;
  TreeNode* left;
  TreeNode* right;
  TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};

// Encodes a tree to a single string.
void serialize_preorder(TreeNode* root, std::ostringstream & oss) {
  if (root) {
    oss << root->val << ' ';
    serialize_preorder(root->left,oss);
    serialize_preorder(root->right,oss);
  } else {
    oss <<'#'<<' ';
  }
}

string serialize(TreeNode* root) {
  std::ostringstream oss;
  serialize_preorder(root,oss);
  return oss.str();
}


// Decodes your encoded data to tree.
TreeNode* deserialize(istringstream & iss) {
  string cur_val;
  iss >> cur_val;
  if (cur_val == "#") {
    return nullptr;
  } else {
    TreeNode* reval = new TreeNode( std::stoi(cur_val) );
    reval->left = deserialize(iss);
    reval->right = deserialize(iss);
    return reval;
  }
}

TreeNode* deserialize(string data) {
  istringstream in(data);
  return deserialize(in);
}


void UnitTest_TreeSerilization(){
  TreeNode* root = deserialize("1 2 # # 3 4 # # 5 # # ");
  assert("1 2 # # 3 4 # # 5 # # "==serialize(root));
}

int main() {
  UnitTest_TreeSerilization();
}
