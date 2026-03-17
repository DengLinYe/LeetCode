#include <algorithm>
#include <iostream>
#include <queue>
#include <string>
#include <unordered_map>
#include <vector>

using namespace std;

class Solution {
 public:
  int lengthOfLongestSubstring(string s) {
    int left = 1, n = s.size(), maxLen = 0;
    unordered_map<char, int> lastIndex;
    for (int right = 0; right < n; right++) {
      if (lastIndex[s[right]] >= left) {
        left = lastIndex[s[right]] + 1;
      }
      lastIndex[s[right]] = right + 1;
      maxLen = max(right - left + 2, maxLen);
    }

    return maxLen;
  }
};

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  string s;
  getline(cin, s);

  Solution obj;
  cout << obj.lengthOfLongestSubstring(s);

  return 0;
}