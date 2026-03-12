#include <algorithm>
#include <iostream>
#include <queue>
#include <string>
#include <unordered_map>
#include <vector>

using namespace std;

class Solution {
 public:
  string reverseWords(string s) {
    int n = s.size();
    for (int i = 0; i < n / 2; i++) {
      int temp = s[i];
      s[i] = s[n - i - 1];
      s[n - i - 1] = temp;
    }

    int k = 0, state = 0, lastStart = 0;
    s.push_back(' ');
    for (int i = 0; i <= n; i++) {
      if (state == 0 && s[i] != ' ') {
        lastStart = k;
        s[k++] = s[i];
        state++;
      } else if (state == 1) {
        if (s[i] == ' ') {
          state--;
          int d = lastStart + k;
          for (int j = lastStart; j < d / 2; j++) {
            int temp = s[j];
            s[j] = s[d - j - 1];
            s[d - j - 1] = temp;
          }
        }

        s[k++] = s[i];
      }
    }
    s.resize(k - 1);

    return s;
  }
};

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  string s;
  getline(cin, s);

  Solution obj;
  cout << obj.reverseWords(s);

  return 0;
}