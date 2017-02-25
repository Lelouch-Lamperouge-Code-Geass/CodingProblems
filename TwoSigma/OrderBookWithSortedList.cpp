#include <list>
#include <memory>
#include <cassert>
#include <unordered_map>

#include <iostream>

class Order;
typedef std::shared_ptr<Order> OrderPtr;

enum OrderType{
  BUY,
  SELL
};

class Order {

public:
  Order(const std::string & order_id, 
        const std::string & company,  
        const OrderType  order_type, 
        double price, 
        std::size_t quantity)
    : m_order_id(order_id), m_company(company), m_order_type(order_type),  m_price(price), m_quantity(quantity) {}

  std::string m_order_id;
  std::string  m_company;
  OrderType  m_order_type;
  double m_price;
  std::size_t m_quantity;
};

class OrderList {
public:
  OrderList() {}
  double GetMinSellPrice() {
    return m_sell_list.empty() ? 0 : m_sell_list.front()->m_price;
  }

  double GetMaxBuyPrice() {
    return  m_buy_list.empty() ? 0 : m_buy_list.front()->m_price;
  }

  void AddOrder(const OrderPtr & order_ptr) {
    if (!order_ptr) return;
    if (order_ptr->m_order_type == BUY) {
      m_buy_mapper[order_ptr] = AddToList(order_ptr,m_buy_list);
    } else {
      m_sell_mapper[order_ptr] = AddToList(order_ptr,m_sell_list);
    }
  }

  double GetTotalCost(std::size_t quantity) const {
    double reval(0);
    std::list<OrderPtr>::const_iterator const_iter = m_sell_list.begin();

    while (const_iter != m_sell_list.end() && quantity != 0) {
      std::size_t need = std::min(quantity, (*const_iter)->m_quantity);
      reval += (*const_iter)->m_price * need;
      quantity -= need;

      ++ const_iter;
    }

    return reval;
  }
   void Delete(const OrderPtr & order_ptr) {
    if (m_buy_mapper.count(order_ptr) != 0 ) {
      m_buy_list.erase(m_buy_mapper[order_ptr]);
      m_buy_mapper.erase(order_ptr);
    }

    if (m_sell_mapper.count(order_ptr) != 0 ) {
      m_sell_list.erase(m_sell_mapper[order_ptr]);
      m_sell_mapper.erase(order_ptr);
    }
  }
private:
  std::list<OrderPtr>::iterator  AddToList(const OrderPtr & order_ptr,  std::list<OrderPtr> & list) {
    if (list.empty()) {
      list.push_front(order_ptr);
      return list.begin();
    } else {
      std::list<OrderPtr>::iterator iter = list.begin();
      std::list<OrderPtr>::iterator pre = list.end();
      while (iter != list.end() && (*iter)->m_price < order_ptr->m_price) {
        pre = iter;
        ++ iter;
      }
      list.insert(iter, order_ptr);
      ++ pre;
      return pre;
    }
  }
  std::list<OrderPtr> m_buy_list; // all negative, from low to high
  std::list<OrderPtr> m_sell_list; // all positive, from low to high
  typedef std::unordered_map<OrderPtr, std::list<OrderPtr>::iterator > OrderToPos;
  OrderToPos m_buy_mapper;
  OrderToPos m_sell_mapper;
};
typedef std::shared_ptr<OrderList> OrderListPtr;

class OrderBook {
public:
  OrderBook(){}
  // add a trading order
  void AddOrder(const std::string & order_id,
           const std::string & company,
           double price,
           std::size_t quantity,
           const OrderType order_type) {

    if ( m_company_to_order_list.count(company) == 0 ) {
      m_company_to_order_list[company] = std::make_shared<OrderList>();
    }

    // Make buy order price negative
    if (order_type == BUY) price = 0 - price;

    OrderPtr order_ptr = std::make_shared<Order>(order_id,company,order_type,price,quantity);

    m_company_to_order_list[company]->AddOrder(order_ptr);
    m_order_id_to_order[order_id] = order_ptr;
  }
  
  // return the min sell price of a share
  double GetMinSellPrice(const std::string & company) {
    return m_company_to_order_list.count(company) == 0 ? 0 : m_company_to_order_list[company]->GetMinSellPrice();
  }

  // return the max buy price of a share
  double GetMaxBuyPrice(const std::string & company) {
    return m_company_to_order_list.count(company) == 0 ? 0 : m_company_to_order_list[company]->GetMaxBuyPrice();
  }

  // return the total cost to buy xxx shares of a company
  double GetTotalCost(const std::string & company, std::size_t quantity) {
    return m_company_to_order_list.count(company) == 0 ? 0 : m_company_to_order_list[company]->GetTotalCost(quantity);
  }

  // cancel a trading order
  void Delete(const std::string & order_id) {
    if (m_order_id_to_order.count(order_id) != 0) {
      OrderPtr order_ptr = m_order_id_to_order[order_id];
      m_company_to_order_list[ order_ptr->m_company ]->Delete(order_ptr);
    }
  }

private:
  std::unordered_map<std::string, OrderListPtr> m_company_to_order_list;
  std::unordered_map<std::string, OrderPtr> m_order_id_to_order;
};


void UnitTest_OrderBook() {
  OrderBook order_book;
  order_book.AddOrder("order_1", "GOOGLE", 507.80, 20, BUY);
  order_book.AddOrder("order_2", "GOOGLE", 601.20, 50, BUY);
  order_book.AddOrder("order_3", "GOOGLE", 307.80, 100, BUY);
  order_book.AddOrder("order_4", "GOOGLE", 717.35, 30, SELL);
  order_book.AddOrder("order_5", "GOOGLE", 866.80, 40, SELL);

  assert(order_book.GetMinSellPrice("GOOGLE") == 717.35);
  assert(order_book.GetMaxBuyPrice("GOOGLE") == -601.2);
  assert(order_book.GetTotalCost("GOOGLE",40) == 717.35 * 30 + 866.80 * 10);

  order_book.AddOrder("order_6", "FACEBOOK", 36.3, 2000, BUY);
  order_book.AddOrder("order_7", "FACEBOOK", 44.7, 4000, BUY);
  order_book.AddOrder("order_8", "FACEBOOK", 16.8, 4000, BUY);
  order_book.AddOrder("order_9", "FACEBOOK", 83.92, 1000, SELL);
  assert(order_book.GetMaxBuyPrice("FACEBOOK") == -44.7);
  order_book.Delete("order_7" );
  assert(order_book.GetMaxBuyPrice("FACEBOOK") == -36.3);
}

int main() {
  UnitTest_OrderBook();
  return 0;
}

