#include <algorithm>
#include <iostream>
#include <queue>
#include <string>
#include <unordered_map>
#include <vector>

using namespace std;

class Solution {
 public:
  vector<vector<string>> groupAnagrams(vector<string>& strs) {
    int n = strs.size();
    vector<vector<string>> res;
    unordered_map<string, int> index;

    for (int i = 0; i < n; i++) {
      string word = strs[i];
      sort(strs[i].begin(), strs[i].end());

      if (index.count(strs[i]) != 0) {
        res[index[strs[i]]].push_back(word);
      } else {
        res.push_back({word});
        index[strs[i]] = res.size() - 1;
      }
    }

    return res;
  }
};

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  int n;
  cin >> n;
  cin.ignore();

  vector<string> strs(n);
  for (int i = 0; i < n; i++) {
    cin >> strs[i];
  }

  Solution obj;
  vector<vector<string>> res = obj.groupAnagrams(strs);

  for (vector<string> group : res) {
    for (string x : group) {
      cout << x << " ";
    }
    cout << endl;
  }

  return 0;
}