A trading book is the portolio of financial instruments held by a brokerage or bank.

Design its data structure to support below functionalities:

1. Being able to return min sell and max buy price for a security.
2. Beging able to tell how much did it cost to buy a security.
  
This trading book could have two functions, which are
  
1. Add(symbol_id,company,prices,quyantity,sell/buy)
2. Delete(symbol_id)

# Solution

```cpp
#include <iostream>
#include <memory>
#include <unordered_map>
#include <stack>
#include <cassert>

class OrderNode;
typedef std::shared_ptr<OrderNode> OrderNodePtr;

// similar to TRADE Node
class OrderNode {
  friend class OrderTree;
public:
  OrderNode(const std::string & order_id, double price, std::size_t quantity)
    : m_order_id(order_id), m_price(price), m_quantity(quantity),m_left(nullptr),m_right(nullptr){}
private:
  std::string m_order_id;
  double m_price;
  std::size_t m_quantity;
  OrderNodePtr m_left;
  OrderNodePtr m_right;
};

class OrderTree {
public:
  OrderTree(){
    m_root = std::make_shared<OrderNode>("",0,0);
  }
  void AddOrderNode(const OrderNodePtr & node) {
    OrderNodePtr curr(m_root), parent(nullptr);
    while (curr) {
      parent = curr;
      if (node->m_price < curr->m_price) {
        curr = curr->m_left;
      } else {
        curr = curr->m_right;
      }
    }
// add trade node to the tree
    if (node->m_price < parent->m_price) {
      parent->m_left = node;
    } else {
      parent->m_right = node;
    }
  }

  double GetMinSellPrice() const {
    return m_root->m_right ? m_root->m_right->m_price : 0;    
  }

  double GetMaxBuyPrice() const {
    OrderNodePtr curr(m_root);
    while (curr->m_left) {
      curr = curr->m_left;
    }
    return curr->m_price;
  }
double GetTotalCost(std::size_t quantity) const {
    if ( !m_root->m_right ) return 0;
    
    // Begin in-order-traversal for right tree of root node
    double reval(0);
    OrderNodePtr curr(m_root->m_right);
    std::stack<OrderNodePtr> m_stack;
    m_stack.push(curr);
    while ( !m_stack.empty() && quantity != 0 ) {
      if (m_stack.top()->m_left) {
        m_stack.push(m_stack.top()->m_left);
      } else {
        curr = m_stack.top();
        std::size_t need = std::min(quantity, curr->m_quantity);
        reval += curr->m_price * need;
        quantity -= need;
        m_stack.pop();
        if (curr->m_right) m_stack.push(curr->m_right);
      }
    }
    // This depends on discussion.
    // What if asked quantity is more than all the quantity being sold by others, rarely happen though.
    return quantity == 0 ? reval : 0;
  }
  
private:
  OrderNodePtr m_root;
};

typedef std::shared_ptr<OrderTree> OrderTreePtr;

enum OrderType{
  BUY,
  SELL
};

class OrderBook {
public:
  OrderBook() {}
 
  void AddOrder(const std::string & order_id,
           const std::string & company,
           double price,
           std::size_t quantity,
           const OrderType & order_type);
  
  double GetMinSellPrice(const std::string & company);
  
  double GetMaxBuyPrice(const std::string & company);

  double GetTotalCost(const std::string & company,std::size_t quantity);
  
  void Delete(const std::string & order_id);
private:
  std::unordered_map<std::string, OrderTreePtr> m_company_to_order_tree;
  std::unordered_map<std::string, OrderNodePtr> m_order_id_to_trade;
};

void  OrderBook:: AddOrder(const std::string & order_id,
                      const std::string & company,
                      double price,
                      std::size_t quantity,
                      const OrderType & order_type){
  if ( m_company_to_order_tree.count(company) == 0 ) {
    m_company_to_order_tree[company] = std::make_shared<OrderTree>();
  }
  if (order_type == BUY) price = 0 - price; // make it negative for buying order
  OrderNodePtr new_trade = std::make_shared<OrderNode>(order_id, price, quantity);
  m_company_to_order_tree[company]->AddOrderNode(new_trade);
}

double OrderBook::GetMinSellPrice(const std::string & company){
  if (m_company_to_order_tree.count(company) == 0) {
    return 0;
  } else {
    return m_company_to_order_tree[company]->GetMinSellPrice();
  }
}

double OrderBook::GetMaxBuyPrice(const std::string & company){
  if (m_company_to_order_tree.count(company) == 0) {
    return 0;
  } else {
    return m_company_to_order_tree[company]->GetMaxBuyPrice();
  }
}

double OrderBook::GetTotalCost(const std::string & company, std::size_t quantity){
  if (m_company_to_order_tree.count(company) == 0) {
    return 0;
  } else {
    return m_company_to_order_tree[company]->GetTotalCost(quantity);
  }
}


void UnitTest_OrderBook() {
  OrderBook order_book;
  order_book.AddOrder("GOOGL", "GOOGLE", 507.80, 20, BUY);
  order_book.AddOrder("GOOGL", "GOOGLE", 601.20, 50, BUY);
  order_book.AddOrder("GOOGL", "GOOGLE", 307.80, 100, BUY);
  order_book.AddOrder("GOOGL", "GOOGLE", 717.35, 30, SELL);
  order_book.AddOrder("GOOGL", "GOOGLE", 866.80, 40, SELL);

  assert(order_book.GetMinSellPrice("GOOGLE") == 717.35);
  assert(order_book.GetMaxBuyPrice("GOOGLE") == -601.2);
  assert(order_book.GetTotalCost("GOOGLE",40) == 717.35 * 30 + 866.80 * 10);
  
  order_book.AddOrder("FB", "FACEBOOK", 36.3, 2000, BUY);
  order_book.AddOrder("FB", "FACEBOOK", 44.7, 4000, BUY);
  order_book.AddOrder("FB", "FACEBOOK", 83.92, 1000, SELL);
  assert(order_book.GetMaxBuyPrice("FACEBOOK") == -44.7);
  
  // order_book.Delete("FB");
  //std::cout << order_book.GetMaxBuyPrice("FACEBOOK") << std::endl;
}

int main() {
  UnitTest_OrderBook();
  return 0;
}
```
