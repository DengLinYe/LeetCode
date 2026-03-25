#include <algorithm>
#include <iostream>
#include <queue>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>

using namespace std;

class Solution {
 public:
  int longestConsecutive(vector<int>& nums) {
    int n = nums.size(), maxLen = 0;
    unordered_set<int> start;
    for (int x : nums) start.insert(x);

    for (int i = 0; i < n; i++) {
      if (!start.count(nums[i] - 1)) {
        int index = nums[i], nowLen = 1;

        while (start.count(++index)) {
          nowLen++;
        }

        maxLen = max(maxLen, nowLen);
      }
    }

    return maxLen;
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
  cout << obj.longestConsecutive(nums);

  return 0;
}