#include <algorithm>
#include <iostream>
#include <queue>
#include <string>
#include <unordered_map>
#include <vector>

using namespace std;

class Solution {
 public:
  bool isSubsequence(string s, string t) {
    int j = 0, n = t.size(), m = s.size();

    if (n == 0 && m == 0) return true;

    for (int i = 0; i < n; i++) {
      if (t[i] == s[j]) {
        j++;
      }

      if (j >= m) {
        return true;
      }
    }

    return false;
  }
};

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  string s, t;
  cin >> s >> t;

  Solution obj;
  cout << obj.isSubsequence(s, t);

  return 0;
}