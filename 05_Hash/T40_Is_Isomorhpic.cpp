#include <algorithm>
#include <iostream>
#include <queue>
#include <string>
#include <unordered_map>
#include <vector>

using namespace std;

class Solution {
 public:
  bool isIsomorphic(string s, string t) {
    int n = s.size();
    if (n != t.size()) return false;

    vector<int> map(128, -1), reverseMap(128, 0);

    for (int i = 0; i < n; i++) {
      if (map[s[i]] == -1) {
        if (reverseMap[t[i]] == 0) {
          map[s[i]] = t[i];
          reverseMap[t[i]]++;
        } else {
          return false;
        }
      } else {
        if (map[s[i]] != t[i]) return false;
      }
    }

    return true;
  }
};

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  string s, t;
  cin >> s >> t;

  Solution obj;
  cout << obj.isIsomorphic(s, t);

  return 0;
}