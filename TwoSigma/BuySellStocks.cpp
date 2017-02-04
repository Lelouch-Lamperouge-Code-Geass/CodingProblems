
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
