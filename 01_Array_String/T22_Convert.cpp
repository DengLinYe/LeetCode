#include <algorithm>
#include <iostream>
#include <queue>
#include <string>
#include <unordered_map>
#include <vector>

using namespace std;

class Solution {
 public:
  string convert(string s, int numRows) {
    if (numRows == 1) return s;

    int n = s.size(), base = numRows * 2 - 2, f = 0, k = 0;
    string result;

    while (f < numRows && k < n) {
      bool flag = true;

      for (int i = f; i < n;) {
        result += s[i];
        k++;
        if (k >= n) break;

        int weight = base - f * 2;
        if (flag) {
          if (weight == 0) weight = base;
          i += weight;
        } else {
          if (weight == base) weight = 0;
          i += base - weight;
        }

        flag = !flag;
      }

      f++;
    }

    return result;
  }
};

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  string s;
  getline(cin, s);

  int n;
  cin >> n;

  Solution obj;
  cout << obj.convert(s, n);

  return 0;
}