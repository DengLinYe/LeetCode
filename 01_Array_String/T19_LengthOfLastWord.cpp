#include <algorithm>
#include <iostream>
#include <queue>
#include <string>
#include <unordered_map>
#include <vector>

using namespace std;

class Solution {
 public:
  int lengthOfLastWord(string s) {
    int n = s.size(), lastLen = 0, state = 0;

    for (int i = 0; i < n; i++) {
      if (state == 0 && s[i] != ' ') {
        state++;
        lastLen = 1;
      } else if (state == 1) {
        if (s[i] != ' ') {
          lastLen++;
        } else {
          state--;
        }
      }
    }

    return lastLen;
  }
};

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  string s;
  getline(cin, s);

  Solution obj;
  cout << obj.lengthOfLastWord(s);

  return 0;
}