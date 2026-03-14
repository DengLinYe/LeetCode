#include <algorithm>
#include <cctype>
#include <iostream>
#include <queue>
#include <string>
#include <unordered_map>
#include <vector>

using namespace std;

class Solution {
 public:
  bool isPalindrome(string s) {
    int left = 0, right = s.size();

    while (left < right) {
      if (!isalpha(s[left]) && !isdigit(s[left])) {
        left++;
      } else if (!isalpha(s[right]) && !isdigit(s[right])) {
        right--;
      } else {
        if (s[left] == s[right] || (isalpha(s[right]) && isalpha(s[left]) &&
                                    abs(s[left] - s[right]) == 32)) {
          left++;
          right--;
        } else {
          return false;
        }
      }
    }

    return true;
  }
};

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  string s;
  getline(cin, s);

  Solution obj;
  cout << obj.isPalindrome(s);

  return 0;
}