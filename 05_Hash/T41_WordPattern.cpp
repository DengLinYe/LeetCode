#include <algorithm>
#include <iostream>
#include <queue>
#include <sstream>
#include <string>
#include <unordered_map>
#include <vector>

using namespace std;

class Solution {
 public:
  bool wordPattern(string pattern, string s) {
    istringstream iss(s);
    string word;
    unordered_map<string, int> s2p;
    vector<string> p2s(128, "");

    for (char x : pattern) {
      iss >> word;
      if (word == "") return false;
      if (p2s[x] == "" && s2p.count(word) == 0) {
        p2s[x] = word;
        s2p[word] = x;
      } else {
        if (p2s[x] != word || s2p[word] != x) return false;
      }
    }
    if (iss >> word) return false;

    return true;
  }
};

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  string pattern, s;
  cin >> pattern;
  cin.ignore();
  getline(cin, s);

  Solution obj;
  cout << obj.wordPattern(pattern, s);

  return 0;
}