int maxProfit(vector<int>& prices) {
      if (prices.empty()) return 0;
      const std::size_t prices_size(prices.size());
      std::vector<int> max_buy_one(prices_size,0), max_sell_one(prices_size,0);
      std::vector<int> max_buy_two(prices_size,0), max_sell_two(prices_size,0);
      max_buy_one[0] = max_buy_two[0] = -prices[0];

      for (std::size_t i = 1; i < prices_size; ++i) {
          max_buy_one[i] = std::max(max_buy_one[i-1], - prices[i]);
          max_sell_one[i] = std::max(max_sell_one[i-1], max_buy_one[i] + prices[i]);
          max_buy_two[i] = std::max(max_buy_two[i-1], max_sell_one[i] - prices[i]);
          max_sell_two[i] = std::max(max_sell_two[i-1], max_buy_two[i] + prices[i]);
      }

      return max_sell_two[prices_size - 1];
}



int maxProfit(vector<int>& prices) {
  // These four variables records the maximum profit on that status.
  // e.g. buy_first represents the maximum profit when buy first stock at this price.
  // sell_first represents the maimum profist when sell first stock at this price.
  int buy_first(INT_MIN),sell_first(0),buy_second(INT_MIN),sell_second(0);
  for (int price : prices) {
    buy_first = std::max(buy_first,0-price);
    sell_first = std::max(sell_first,buy_first+price);
    buy_second = std::max(buy_second,sell_first-price);
    sell_second = std::max(sell_second,buy_second+price);
  }
  return sell_second;
}




int main() {
  return 0;
}
