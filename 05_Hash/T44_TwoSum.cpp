#include <algorithm>
#include <iostream>
#include <queue>
#include <string>
#include <unordered_map>
#include <vector>

using namespace std;

class Solution {
 public:
  vector<int> twoSum(vector<int>& nums, int target) {
    unordered_map<int, int> index;
    int n = nums.size();
    for (int i = 0; i < n; i++) {
      int sub = target - nums[i];
      if (index.count(sub) != 0) {
        return {index[sub], i};
      } else {
        index[nums[i]] = i;
      }
    }

    return {};
  }
};

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  int n, target;
  cin >> n >> target;

  vector<int> nums(n);
  for (int i = 0; i < n; i++) {
    cin >> nums[i];
  }

  Solution obj;
  vector<int> res = obj.twoSum(nums, target);
  cout << res[0] << " " << res[1];

  return 0;
}