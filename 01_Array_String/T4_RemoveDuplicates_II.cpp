#include <algorithm>
#include <iostream>
#include <queue>
#include <string>
#include <unordered_map>
#include <vector>

using namespace std;

class Solution {
 public:
  int removeDuplicates(vector<int>& nums) {
    int base = 0, check = 1, n = nums.size();
    bool flag = true;

    if (n <= 1) {
      return n;
    }

    while (check < n) {
      if (nums[base] == nums[check]) {
        if (flag) {
          base++;
          flag = false;
        }
        nums[base] = nums[check];
        check++;
      } else {
        base++;
        nums[base] = nums[check];
        flag = true;
        check++;
      }
    }

    return base + 1;
  }
};

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  int n;
  while (cin >> n) {
    vector<int> nums(n);
    for (int i = 0; i < n; ++i) {
      cin >> nums[i];
    }

    Solution obj;
    int k = obj.removeDuplicates(nums);

    cout << k << ", nums = [";
    for (int i = 0; i < k; ++i) {
      cout << nums[i] << (i == k - 1 ? "" : ",");
    }
    cout << "]\n";
  }

  return 0;
}