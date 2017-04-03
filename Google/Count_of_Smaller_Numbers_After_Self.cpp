// https://leetcode.com/problems/count-of-smaller-numbers-after-self
class Solution {
private:
    struct TreeNode;
    typedef std::shared_ptr<TreeNode> TreeNodePtr;
    
    struct TreeNode {
        TreeNode(int value) : m_value(value), m_left_children(0),
                                           m_count(1), m_left(nullptr), m_right(nullptr) {}
        int m_value;
        int m_left_children; // recording the amount of left children
        int m_count; // recording the amount of duplicate numbers
        TreeNodePtr m_left, m_right;
    };
    
    // return the amount of previous smaller nodesm
    int Insert(TreeNodePtr & root, const int number) {
        if (!root) { 
            root = std::make_shared<TreeNode>(number);
            return 0;
        } else {
            if (number > root->m_value) {
                return root->m_left_children + root->m_count + Insert(root->m_right, number);
            }  else if (number < root->m_value){
                ++ root->m_left_children;
                return Insert(root->m_left, number);
            }  else { // equal
                ++ root->m_count;
                return root->m_left_children;
            }
        }
    }
    
public:
    vector<int> countSmaller(vector<int>& nums) {
            const std::size_t nums_size(nums.size());
            if (nums_size == 0) return vector<int>();
            vector<int> reval(nums_size, 0);
            TreeNodePtr root(nullptr);
            for (int i = nums_size - 1; i < nums_size; --i) {
                reval[i] = Insert(root, nums[i]);
            }
            return reval;
    }
};
