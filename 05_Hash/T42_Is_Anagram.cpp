#include <algorithm>
#include <iostream>
#include <queue>
#include <string>
#include <unordered_map>
#include <vector>

using namespace std;

class Solution {
 public:
  bool isAnagram(string s, string t) {
    int count = t.size();
    if (count != s.size()) return false;

    vector<int> freq(128);
    for (char x : t) freq[x]++;

    for (char x : s) {
      if (--freq[x] < 0) {
        return false;
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
  cout << obj.isAnagram(s, t);

  return 0;
}