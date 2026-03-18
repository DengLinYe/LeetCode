#include <algorithm>
#include <iostream>
#include <queue>
#include <string>
#include <unordered_map>
#include <vector>

using namespace std;

class Solution {
 public:
  string minWindow(string s, string t) {
    int m = s.size(), n = t.size();
    if (n > m) {
      return "";
    }

    vector<int> freq(128, -1), nowFreq(128, 0);
    for (const char& x : t) freq[x] += (freq[x] == -1 ? 2 : 1);

    int count = 0, left = 0, minLen = INT_MAX, minLeft = 0;
    for (int right = 0; right < m; right++) {
      if (freq[s[right]] != 0) {
        nowFreq[s[right]]++;
        if (nowFreq[s[right]] <= freq[s[right]]) count++;
      }
      if (count >= n) {
        while (nowFreq[s[left]] > freq[s[left]]) {
          if (freq[s[left]] != 0) {
            nowFreq[s[left]]--;
          }
          left++;
        }

        if (right - left + 1 < minLen) {
          minLen = right - left + 1;
          minLeft = left;
        }
      }
    }

    return (minLen == INT_MAX ? "" : s.substr(minLeft, minLen));
  }
};

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  string s, t;
  cin >> s >> t;

  Solution obj;
  cout << obj.minWindow(s, t) << endl;

  return 0;
}