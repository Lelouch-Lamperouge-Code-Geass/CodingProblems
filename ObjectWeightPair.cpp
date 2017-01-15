/* * 
   Design a data structure to hold objects with a corresponding integer weight. 
   (1)GetRandom : It should support: Obtain an object randomly with probability 
   equal to (weight of the element) / (sum of the weights). 
   (2)Update : Set an object-weight pair. 
   (3)Insert : If the object is already in the structure, its weight will be updated. 
   Otherwise, the object will be inserted and set to its weight. 
   (4)Remove : If the weight is zero, the object can be removed. 

   put("A",3) 3/33 
   put("B",30) 30/33 
   * */

#include <memory>
#include <vector>
#include <string>
#include <list>
#include <cstdlib>
#include <iostream>

struct WeightObject {
  WeightObject(const std::string & label,int weight) : m_label(label), m_weight(weight) {}
  std::string m_label;
  int m_weight;
};
typedef std::shared_ptr<WeightObject> WeightObjectPtr;


namespace SegmentTreeSolution {
  
  class SegmentTreeNode;
  typedef std::shared_ptr<SegmentTreeNode> SegmentTreeNodePtr;
  
  struct SegmentTreeNode {
  public:
    SegmentTreeNode(const std::string & label,int w) :m_label(label) ,m_weight(w) {
    }
    SegmentTreeNodePtr m_left, m_right;
    std::string m_label;
    int m_weight;
  };


  // Initilize a balanced segment tree
  SegmentTreeNodePtr BuildSegmentTree(const std::vector<WeightObjectPtr> & objects, std::size_t start, std::size_t end){
    if (start==end) {SegmentTreeNodePtr node =  std::make_shared<SegmentTreeNode>(objects[start]->m_label,objects[start]->m_weight);std::cout<<node->m_label<<"|"<<node->m_weight<<std::endl;; return node;}
    std::size_t mid = start + (end - start) / 2;
    SegmentTreeNodePtr mid_node = std::make_shared<SegmentTreeNode>("",0);
    mid_node->m_left = BuildSegmentTree(objects,start,mid);
    mid_node->m_right = BuildSegmentTree(objects,mid+1,end);
    mid_node->m_weight = mid_node->m_left->m_weight + mid_node->m_right->m_weight ;
    return mid_node;
  }

  class WeightObjectContainer {
  public:
    WeightObjectContainer(const std::vector<WeightObjectPtr> & objects) : m_total_weight(0) {
      std::vector<int> weights(objects.size(),0);
      const std::size_t obj_size(objects.size());
      for (std::size_t i=0;i<obj_size;++i) {
        weights[i] = objects[i]->m_weight;
        m_total_weight += objects[i]->m_weight;
        m_objects.push_back(objects[i]);
      }
      m_root = ( obj_size==0? nullptr : BuildSegmentTree(objects,0,obj_size-1) );
    }
  
    // Return the interval leaf node where i should be put
    SegmentTreeNodePtr Find(int i,SegmentTreeNodePtr root) {
      if (!root) return nullptr;
      if (!root->m_left && !root->m_right ) return root; // leaf node
      if (i<=root->m_left->m_weight) return Find(i,root->m_left);
      else return Find(i-root->m_left->m_weight,root->m_right);
    }
  
    WeightObjectPtr GetRandom() {
      int i = rand() % (m_total_weight+1);
      std::cout<< i << std::endl;
      SegmentTreeNodePtr node =  Find(i,m_root);
      if (!node) return nullptr;
      return std::make_shared<WeightObject>(node->m_label,node->m_weight);
    }
  private:
    std::list<WeightObjectPtr> m_objects;  
    int m_total_weight;
    SegmentTreeNodePtr m_root;
  };

}


int main() {
  std::vector<WeightObjectPtr> objects = {std::make_shared<WeightObject>("apple",4),
                                          std::make_shared<WeightObject>("orange",2),
                                          std::make_shared<WeightObject>("lemon",1)};
  
  SegmentTreeSolution::WeightObjectContainer segment_tree_container(objects);
  for (int i=0;i<10;++i) {
    WeightObjectPtr node = segment_tree_container.GetRandom();
    std::cout <<node->m_label<<std::endl;
  }
  return 0;
}
