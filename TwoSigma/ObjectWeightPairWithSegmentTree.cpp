#include <memory>
#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
#include <unordered_map>

struct Object {
  Object(const std::string & label, int weight) : m_label(label), m_weight(weight) {}
  std::string m_label;
  int m_weight;
};


typedef std::shared_ptr<Object> ObjectPtr;


struct TreeNode;
typedef std::shared_ptr<TreeNode> TreeNodePtr;

struct TreeNode {

  TreeNode(const std::string & label, int weight)
    : m_label(label), m_weight(weight), m_left(nullptr), m_right(nullptr), m_parent(nullptr){
  }

  std::string m_label;
  int m_weight;
  TreeNodePtr m_left;
  TreeNodePtr m_right;
  TreeNodePtr m_parent;
};


class SegmentTree {
public:
  SegmentTree(const std::vector<Object> & objects) {
    m_root = BuildSegmentTree(objects,0,objects.size()-1);
    m_total_weight = std::accumulate(objects.begin(), objects.end(), 0, [](int w,const Object & obj){return w + obj.m_weight;});
  }

  std::string GetRandom() {
    int random_weight = 1 + rand() % (m_total_weight); // 1-based
    std::cout << random_weight << std::endl;
    return Find(random_weight, m_root)->m_label;
  }

  void Update(std::string label, int new_weight) {
    if (m_mapper.count(label) == 0) {
      return;
    } else {
      TreeNodePtr node = m_mapper[label];
      int diff = new_weight - node->m_weight;
      m_total_weight += diff; // adjust total weight
      while (node) {
        node->m_weight += diff;
        node = node->m_parent;
      }
    }
  }
 void Remove(std::string label) {
    if (m_mapper.count(label) == 0) {
      return;
    } else {
      TreeNodePtr node = m_mapper[label];
      int diff = node->m_weight;
      m_total_weight -= diff;
      m_mapper.erase(label);


      TreeNodePtr parent = node->m_parent;
      if (!parent) {
        m_root = nullptr;
        return; // no nodes left
      }

      TreeNodePtr other_child = (parent->m_left == node ? parent->m_right : parent->m_left);

      if (!parent->m_parent) {
        // deleted node connect to root node directly
        m_root = other_child;
        return;
      }

      TreeNodePtr pp = parent->m_parent;
      if (pp->m_left = parent) {
        pp->m_left = other_child;
      } else {
        pp->m_right = other_child;
      }
      other_child->m_parent = pp;

      while (pp) {
        pp->m_weight -= diff;
        pp = pp->m_parent;
      }
    }
  }

private:
  TreeNodePtr BuildSegmentTree(const std::vector<Object> & objects, std::size_t begin, std::size_t end) {
    if (begin == end) {
      TreeNodePtr reval =  std::make_shared<TreeNode>(objects[begin].m_label, objects[begin].m_weight);
      m_mapper[objects[begin].m_label] = reval;
      return reval;
    } else {
      TreeNodePtr cur_root = std::make_shared<TreeNode>("", 0);
      std::size_t mid = begin + (end - begin) / 2;
      TreeNodePtr left = BuildSegmentTree(objects, begin, mid);
      TreeNodePtr right = BuildSegmentTree(objects, mid+1, end);

      cur_root->m_weight = left->m_weight + right->m_weight;
      cur_root->m_left = left;
      cur_root->m_right = right;

      left->m_parent = cur_root;
      right->m_parent = cur_root;
      return cur_root;
    }
  }


  TreeNodePtr Find(int val, const TreeNodePtr &  node) const {
    if (!node || (!node->m_left && !node->m_right)) { // reach leaf
      return node;
    } else {
      if (val > node->m_left->m_weight) {
        return Find(val - node->m_left->m_weight, node->m_right);
      } else {
        return Find(val, node->m_left);
      }
    }
  }


  TreeNodePtr m_root;
  int m_total_weight;

  std::unordered_map<std::string, TreeNodePtr> m_mapper;
};

void UnitTest() {
  std::vector<Object> objects;
  objects.push_back(Object("apple", 4));
  objects.push_back(Object("orange", 2));
  objects.push_back(Object("lemon", 1));

  SegmentTree tree(objects);
  for (std::size_t i=0; i<10; ++i) {
    std::cout << tree.GetRandom() << std::endl;
  }

  std::cout << "#### UPDATE lemon to be 6" << std::endl;
  tree.Update("lemon",6);
  for (std::size_t i=0; i<10; ++i) {
    std::cout << tree.GetRandom() << std::endl;
  }


  std::cout << "#### REMOVE lemon" << std::endl;
  tree.Remove("lemon");
  for (std::size_t i=0; i<10; ++i) {
    std::cout << tree.GetRandom() << std::endl;
  }
}


int main() {
  UnitTest();
  return 0;
}
