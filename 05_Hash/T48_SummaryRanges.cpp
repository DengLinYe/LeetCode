#include <algorithm>
#include <iostream>
#include <queue>
#include <string>
#include <unordered_map>
#include <vector>

using namespace std;

class Solution {
 public:
  vector<string> summaryRanges(vector<int>& nums) {
    int n = nums.size(), st = 0;
    if (n == 0) return {};

    vector<string> res;

    nums.push_back(nums.back());
    for (int i = 0; i < n; i++) {
      if (nums[i] != nums[i + 1] - 1) {
        if (i != st) {
          res.push_back(to_string(nums[st]) + "->" + to_string(nums[i]));
        } else {
          res.push_back(to_string(nums[st]));
        }

        st = i + 1;
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

  vector<int> nums(n);
  for (int i = 0; i < n; i++) {
    cin >> nums[i];
  }

  Solution obj;
  vector<string> res = obj.summaryRanges(nums);

  for (const string& s : res) {
    cout << s << endl;
  }

  return 0;
}