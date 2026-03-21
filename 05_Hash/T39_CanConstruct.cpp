#include <algorithm>
#include <iostream>
#include <queue>
#include <string>
#include <unordered_map>
#include <vector>

using namespace std;

class Solution {
 public:
  bool canConstruct(string ransomNote, string magazine) {
    vector<int> freq(128);
    int n = ransomNote.size();

    for (char x : magazine) freq[x]++;

    for (int i = 0; i < n; i++) {
      if (--freq[ransomNote[i]] < 0) {
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
  cout << obj.canConstruct(s, t);

  return 0;
}