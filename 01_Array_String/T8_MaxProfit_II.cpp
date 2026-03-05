#include <algorithm>
#include <iostream>
#include <queue>
#include <string>
#include <unordered_map>
#include <vector>

using namespace std;

class Solution {
 public:
  int maxProfit(vector<int>& prices) {
    int n = prices.size(), sum = 0;

    for (int i = 1; i < n; i++) {
      int profit = prices[i] - prices[i - 1];
      if (profit > 0) {
        sum += profit;
      }
    }

    return sum;
  }
};

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  int n;
  while (cin >> n) {
    vector<int> p(n);
    for (int i = 0; i < n; i++) {
      cin >> p[i];
    }

    Solution obj;
    int profit = obj.maxProfit(p);

    cout << profit;
  }
  return 0;
}