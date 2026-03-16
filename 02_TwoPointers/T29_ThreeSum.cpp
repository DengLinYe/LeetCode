#include <algorithm>
#include <iostream>
#include <queue>
#include <string>
#include <unordered_map>
#include <vector>

using namespace std;

class Solution {
 public:
  vector<vector<int>> threeSum(vector<int>& nums) {
    sort(nums.begin(), nums.end());

    vector<vector<int>> result;

    int x = 0, n = nums.size();
    while (x < n - 2) {
      if (nums[x] + nums[n - 2] + nums[n - 1] < 0) {
        x++;
      } else if (nums[x] + nums[x + 1] + nums[x + 2] > 0) {
        break;
      } else if (1 <= x && nums[x] == nums[x - 1]) {
        x++;
        continue;
      }

      int y = x + 1, z = n - 1, sum = -nums[x];
      while (y < z) {
        if (z < n - 1 && y > x + 1 && nums[y] == nums[y - 1] &&
            nums[z] == nums[z + 1]) {
          z--;
          y++;
        } else if (nums[y] + nums[z] == sum) {
          result.push_back(vector<int>{nums[x], nums[y], nums[z]});
          z--;
          y++;
        } else if (nums[y] + nums[z] > sum) {
          z--;
        } else {
          y++;
        }
      }

      x++;
    }

    return result;
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
  vector<vector<int>> res = obj.threeSum(nums);

  for (auto x : res) {
    cout << "[";
    for (int y : x) {
      cout << y << " ";
    }
    cout << "]\n";
  }

  return 0;
}