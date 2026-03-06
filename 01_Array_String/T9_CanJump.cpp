#include <algorithm>
#include <iostream>
#include <queue>
#include <string>
#include <unordered_map>
#include <vector>

using namespace std;

class Solution {
 public:
  bool canJump(vector<int>& nums) {
    int n = nums.size(), canReach = 0;
    for (int i = 0; i < n; i++) {
      if (canReach < i) {
        return false;
      } else {
        canReach = max(canReach, i + nums[i]);
      }
    }

    return true;
  }
};

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  int n;
  while (cin >> n) {
    vector<int> nums(n);
    for (int i = 0; i < n; i++) {
      cin >> nums[i];
    }

    Solution obj;
    bool canJump = obj.canJump(nums);
    cout << canJump;
  }

  return 0;
}