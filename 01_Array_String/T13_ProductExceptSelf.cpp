#include <algorithm>
#include <iostream>
#include <queue>
#include <string>
#include <unordered_map>
#include <vector>

using namespace std;

class Solution {
 public:
  vector<int> productExceptSelf(vector<int>& nums) {
    int n = nums.size(), mul = 1;
    vector<int> out(n, 1);

    for (int i = 0; i < n - 1; i++) {
      mul *= nums[i];
      out[i + 1] *= mul;
    }

    mul = 1;
    for (int i = n - 1; i > 0; i--) {
      mul *= nums[i];
      out[i - 1] *= mul;
    }

    return out;
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
    vector<int> out = obj.productExceptSelf(nums);

    cout << "[";
    for (int i = 0; i < n; i++) {
      cout << out[i] << (i == n - 1 ? " " : ", ");
    }
    cout << "]\n";
  }

  return 0;
}