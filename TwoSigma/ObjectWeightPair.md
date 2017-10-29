
Design a data structure to hold objects with a corresponding integer weight. 

(1) GetRandom : It should support: Obtain an object randomly with probability equal to (weight of the element) / (sum of the weights).   
(2) Update : Set an object-weight pair.   
(3) Insert : If the object is already in the structure, its weight will be updated. Otherwise, the object will be inserted and set to its weight.   
(4) Remove : If the weight is zero, the object can be removed.   

put("A",3) 3/33 
put("B",30) 30/33 


# Solution

```cpp
#include <memory>
#include <vector>
#include <string>
#include <list>
#include <cstdlib>
#include <iostream>
#include <unordered_map>
#include <algorithm>

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


void UnitTest_SegmentTreeSolution() {
  std::vector<WeightObjectPtr> objects = {std::make_shared<WeightObject>("apple",4),
                                          std::make_shared<WeightObject>("orange",2),
                                          std::make_shared<WeightObject>("lemon",1)};
  
  SegmentTreeSolution::WeightObjectContainer segment_tree_container(objects);
  for (int i=0;i<10;++i) {
    WeightObjectPtr node = segment_tree_container.GetRandom();
    std::cout <<node->m_label<<std::endl;
  }
}

namespace PrefixSumSolution {
  class PrefixSum {
  public:
    PrefixSum(const std::vector<WeightObjectPtr> & objects)  {
      for (const WeightObjectPtr & obj : objects) {
        Insert(obj);
      }
    }
    
    bool NotZero(int v) {return (v>0);}
    WeightObjectPtr GetRandom() {
      int val = rand() % (m_pre_sum.back()+1);
      auto first_non_zero_iter = std::find_if(m_pre_sum.begin(),m_pre_sum.end(),NotZero);
      auto iter =  std::lower_bound(first_non_zero_iter,m_pre_sum.end(),val);
      std::size_t index = iter - m_pre_sum.begin();
      return m_index_to_object[index];
    }
    void Update(const WeightObjectPtr & obj_ptr,int new_weight) {
      if (m_object_to_index.count(obj_ptr) == 0) return;
      std::size_t index = m_object_to_index[obj_ptr];
      int diff = new_weight - m_index_to_object[index]->m_weight;
      for (std::size_t i=index;i<m_pre_sum.size();++i) {
        m_pre_sum[i] += diff;
      }
      obj_ptr->m_weight = new_weight;
    }
    // Add a new weight-object pair, update if already added.
    void Insert(const WeightObjectPtr & obj_ptr) {
      if (m_object_to_index.count(obj_ptr)!=0) {
        Update(obj_ptr,obj_ptr->m_weight);
      } else {
        if (m_pre_sum.empty() ) {
          m_pre_sum.push_back(obj_ptr->m_weight-1); // first element minus one, since 4 should only map[0,3]
        } else {
          m_pre_sum.push_back(m_pre_sum.back() + obj_ptr->m_weight);
        }
        m_index_to_object[m_pre_sum.size()-1] = obj_ptr; // store index -> object
        m_object_to_index[obj_ptr] = m_pre_sum.size()-1; // store object -> index
      }
    }
    void Remove(const WeightObjectPtr & obj_ptr) {
      if (m_object_to_index.count(obj_ptr)==0) return;
    
      std::size_t index = m_object_to_index[obj_ptr];
      int diff = 0 - m_index_to_object[index]->m_weight;

      //Notice that range 4 means [0-3] for first item
      for (std::size_t i=index;i<m_pre_sum.size();++i) {
        m_pre_sum[i] += diff;
      }
      if (index==0) m_pre_sum[0] = 0;
          
      m_index_to_object.erase(index); // remove index -> object
      m_object_to_index.erase(obj_ptr); // remove object -> index
    }
  private:
    std::vector<int> m_pre_sum;
    std::unordered_map<std::size_t,WeightObjectPtr> m_index_to_object;
    std::unordered_map<WeightObjectPtr,std::size_t> m_object_to_index;
  };

  void UnitTest_PrefixSumSolution() {
    std::vector<WeightObjectPtr> objects = {std::make_shared<WeightObject>("apple",4),
                                            std::make_shared<WeightObject>("orange",2),
                                            std::make_shared<WeightObject>("lemon",1)};
  
    PrefixSum prefix_sum(objects);
    for (int i=0;i<10;++i) {
      WeightObjectPtr node = prefix_sum.GetRandom();
      std::cout <<node->m_label<<std::endl;
    }

    std::cout << "#### Update ####" << std::endl;
    prefix_sum.Update(objects[1],4);
    for (int i=0;i<10;++i) {
      WeightObjectPtr node = prefix_sum.GetRandom();
      std::cout <<node->m_label<<std::endl;
    }

    std::cout << "#### Remove ####" << std::endl;
    prefix_sum.Remove(objects[1]);
    for (int i=0;i<10;++i) {
      WeightObjectPtr node = prefix_sum.GetRandom();
      std::cout <<node->m_label<<std::endl;
    }
  }
}

int main() {
  PrefixSumSolution::UnitTest_PrefixSumSolution();
  return 0;
}
```
