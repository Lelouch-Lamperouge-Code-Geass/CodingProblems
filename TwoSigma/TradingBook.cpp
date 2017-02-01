/*
  A trading book is the portolio of financial instruments held by a brokerage or
  bank.
  Design its data structure to support below functionalities:
  (1) Being able to return min sell and max buy price for a security.
  (2) Beging able to tell how much did it cost to buy a security.
  This trading book could have two functions, which are
  (1) Add(symbol_id,company,prices,quyantity,sell/buy)
  (2) Delete(symbol_id)
*/
#include <iostream>
#include <unordered_map>
#include <string>
#include <memory>
#include <stack>
#include <cassert>
#include <iostream>

class BstTreeNode;
typedef std::shared_ptr<BstTreeNode> BstTreeNodePtr;

class BstTreeNode {
 public:
  BstTreeNode(float price, long quantity)
      : m_price(price), m_quantity(quantity) {}

 private:
  friend class BstTree;
  // double have much better precision than float, but in general stock price
  // will only have
  // less than 3 decimal digits.
  float m_price;
  // I would say long is good enough, its maximum value are just more than 2
  // billion.
  // You can switch to unsigned long if you want.
  long m_quantity;

  BstTreeNodePtr m_left, m_right;
};

class BstTree {
 public:
  BstTree() : m_root(new BstTreeNode(0, 0)) {}
  void AddNode(float price, long quantity) {
    BstTreeNodePtr curr(m_root), parent;
    while (curr) {
      parent = curr;
      if (curr->m_price == price) {
        curr->m_quantity += quantity;
        return;
      } else if (curr->m_price > price) {
        curr = curr->m_left;
      } else {
        curr = curr->m_right;
      }
    }

    if (parent->m_price > price)
      parent->m_left = std::make_shared<BstTreeNode>(price, quantity);
    else
      parent->m_right = std::make_shared<BstTreeNode>(price, quantity);
  }
  float GetMinSellPrice() {
    return m_root->m_right ? m_root->m_right->m_price : 0;
  }

  float GetMaxBuyPrice() {
    BstTreeNodePtr curr(m_root);
    while (curr->m_left) {
      curr = curr->m_left;
    }
    return curr->m_price;
  }

  // Need use double here, total cost coulbe be more than 2 billion.
  // Very rare, but can't rule out that possibility.
  double GetTotalCost() {
    BstTreeNodePtr curr(m_root->m_left);
    if (!curr) return 0;
    double reval(0);
    std::stack<BstTreeNodePtr> my_stack;
    my_stack.push(curr);
    while (!my_stack.empty()) {
      curr = my_stack.top();
      reval += (curr->m_price * curr->m_quantity);
      my_stack.pop();
      if(curr->m_left)my_stack.push(curr->m_left);
      if(curr->m_right)my_stack.push(curr->m_right);
    }
    return reval;
  }
 private:
  BstTreeNodePtr m_root;
};

typedef std::shared_ptr<BstTree> BstTreePtr;

enum TradeType {
  BUY,
  SELL
};
class TradeBook {
 public:
  TradeBook() {}
  void AddTrade(const std::string& symbol, const std::string& company,
                float price, const long quantity, const TradeType& trade_type) {
    if (m_company_price_mapper.count(company) == 0) {
      m_company_price_mapper[company] = std::make_shared<BstTree>();
      m_symbol_company_mapper[symbol] = company;
    }
    if (trade_type == BUY) price = -price;
    m_company_price_mapper[company]->AddNode(price, quantity);
  }

  void Delete(const std::string& symbol) {
    if (m_symbol_company_mapper.count(symbol) == 0) return;
    const std::string company(m_symbol_company_mapper[symbol]);
    m_company_price_mapper.erase(company);
    m_symbol_company_mapper.erase(symbol);
  }

  float GetMinSellPrice(const std::string& company) {
    if (m_company_price_mapper.count(company) == 0) return 0;
    return m_company_price_mapper[company]->GetMinSellPrice();
  }

  float GetMaxBuyPrice(const std::string& company) {
    if (m_company_price_mapper.count(company) == 0) return 0;
    return  - m_company_price_mapper[company]->GetMaxBuyPrice();
  }

  double GetTotalCost(const std::string & company) {
    if (m_company_price_mapper.count(company) == 0) return 0;
    return  - m_company_price_mapper[company]->GetTotalCost();
  }
 private:
  std::unordered_map<std::string, std::string> m_symbol_company_mapper;
  std::unordered_map<std::string, BstTreePtr> m_company_price_mapper;
};

void UnitTest_TradeBook() {
  TradeBook trade_book;
  trade_book.AddTrade("GOOGL", "GOOGLE", 507.80, 20, BUY);
  trade_book.AddTrade("GOOGL", "GOOGLE", 601.20, 50, BUY);
  trade_book.AddTrade("GOOGL", "GOOGLE", 307.80, 100, BUY);
  trade_book.AddTrade("GOOGL", "GOOGLE", 717.35, 30, SELL);
  trade_book.AddTrade("GOOGL", "GOOGLE", 866.80, 40, SELL);

  std::cout << trade_book.GetMinSellPrice("GOOGLE") << std::endl;
  std::cout << trade_book.GetMaxBuyPrice("GOOGLE") << std::endl;
  std::cout << trade_book.GetTotalCost("GOOGLE") << std::endl;

  trade_book.AddTrade("FB", "FACEBOOK", 36.3, 2000, BUY);
  trade_book.AddTrade("FB", "FACEBOOK", 44.7, 4000, BUY);
  trade_book.AddTrade("FB", "FACEBOOK", 83.92, 1000, SELL);
  std::cout << trade_book.GetMaxBuyPrice("FACEBOOK") << std::endl;
  trade_book.Delete("FB");
  std::cout << trade_book.GetMaxBuyPrice("FACEBOOK") << std::endl;
}
int main() {
  UnitTest_TradeBook();
  return 0;
}
