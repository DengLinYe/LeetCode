#include <algorithm>
#include <cmath>
#include <iostream>
#include <queue>
#include <string>
#include <unordered_map>
#include <vector>

using namespace std;

class Solution {
 public:
  bool isHappy(int n) {
    unordered_map<int, int> circ;
    while (circ.count(n) == 0) {
      circ[n] = 1;
      int m = n, sum = 0;
      while (m != 0) {
        sum += int(pow(m % 10, 2));
        m /= 10;
      }
      if (sum == 1) return true;
      n = sum;
    }
    return false;
  }
};

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  int n;
  cin >> n;

  Solution obj;
  cout << obj.isHappy(n);

  return 0;
}