#include <algorithm>
#include <iostream>
#include <queue>
#include <string>
#include <unordered_map>
#include <vector>

using namespace std;

class Solution {
 public:
  int strStr(string haystack, string needle) {
    int j = 0, i = 1, n = needle.size();

    vector<int> next(n);
    next[0] = 0;

    while (i < n) {
      if (needle[i] == needle[j]) {
        next[i++] = ++j;
      } else if (j == 0) {
        next[i++] = j;
      } else {
        j = next[j - 1];
      }
    }

    j = 0;
    i = 0;
    while (i < haystack.size()) {
      if (haystack[i] == needle[j]) {
        i++;
        j++;
      } else if (j == 0) {
        i++;
      } else {
        j = next[j - 1];
      }

      if (j == n) return i - n;
    }

    return -1;
  }
};

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  string a, b;
  cin >> a >> b;

  Solution obj;
  cout << obj.strStr(a, b);

  return 0;
}