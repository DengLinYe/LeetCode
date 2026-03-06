#include <algorithm>
#include <iostream>
#include <queue>
#include <string>
#include <unordered_map>
#include <vector>

using namespace std;

class Solution {
 public:
  int minTimes = 10000;

  int jump(vector<int>& nums) {
    if (nums.size() == 1) {
      return 0;
    }

    canReach(nums, nums.size() - 1, -1);

    return minTimes;
  }

  void canReach(vector<int>& nums, int k, int times) {
    // cout << "enter pos:" << k << ", and now:" << times << endl;
    times++;
    if (times > minTimes) return;

    for (int i = k - 1; i >= 0; i--) {
      if (i + nums[i] >= k) {
        // cout << "in " << k << ", reach: " << i << ", and now: " << times
        //      << endl;
        if (i == 0) {
          minTimes = min(minTimes, times + 1);
          return;
        } else {
          canReach(nums, i, times);
        }
      }
    }
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
    int jumpTimes = obj.jump(nums);
    cout << jumpTimes;
  }

  return 0;
}