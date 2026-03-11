#include <algorithm>
#include <iostream>
#include <queue>
#include <string>
#include <unordered_map>
#include <vector>

using namespace std;

class Solution {
 public:
  string longestCommonPrefix(vector<string>& strs) {
    int n = strs.size();
    if (n == 0) return "";

    int k = strs[0].size();
    for (int i = 1; i < n; i++) {
      k = prefixFetch(strs[0], strs[i], k);
      if (k == 0) break;
    }

    return strs[0].substr(0, k);
  }

 private:
  int prefixFetch(string& a, string& b, int k) {
    int newK = 0;
    for (int i = 0; i < k; i++) {
      if (a[i] - b[i] == 0) {
        newK++;
      } else {
        break;
      }
    }

    return newK;
  }
};

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  int n;
  if (!(cin >> n)) return 0;
  cin.ignore();

  vector<string> strs(n);
  for (int i = 0; i < n; i++) {
    getline(cin, strs[i]);
  }

  Solution obj;
  cout << obj.longestCommonPrefix(strs);

  return 0;
}