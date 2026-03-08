#include <algorithm>
#include <iostream>
#include <queue>
#include <string>
#include <unordered_map>
#include <vector>

using namespace std;

class Solution {
 public:
  int canCompleteCircuit(vector<int>& gas, vector<int>& cost) {
    int n = gas.size(), sum = 0, b = 0, bSt = 0, st = 0;

    for (int i = 0; i < 2 * n; i++) {
      int index = i % n;
      if (i - bSt >= n) break;

      int k = gas[index] - cost[index];
      if (b > 0) {
        b += k;
      } else {
        b = k;
        bSt = index;
      }

      if (b > sum) {
        sum = b;
        st = bSt;
      }
    }

    sum = 0;
    for (int i = st; i < st + n; i++) {
      int index = i % n;
      sum += gas[index] - cost[index];
      if (sum < 0) {
        return -1;
      }
    }

    return st;
  }
};

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  int n;
  while (cin >> n) {
    vector<int> gas(n), cost(n);
    for (int i = 0; i < n; i++) {
      cin >> gas[i];
    }
    for (int i = 0; i < n; i++) {
      cin >> cost[i];
    }

    Solution obj;
    int st = obj.canCompleteCircuit(gas, cost);
    cout << st;
  }

  return 0;
}