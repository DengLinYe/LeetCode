#include <algorithm>
#include <iostream>
#include <queue>
#include <string>
#include <unordered_map>
#include <vector>

using namespace std;

class Solution {
 public:
  void rotate(vector<int>& nums, int k) {
    int n = nums.size();
    k = k % int(n);
    if (k == 0) return;

    rotate3(nums, k, n);
  }

  void rotate1(vector<int>& nums, int k, int n) {
    for (int i = 0; i < k; i++) {
      for (int j = n - 1; j > 0; j--) {
        swap(nums[j], nums[j - 1]);
      }
    }
  }

  void rotate2(vector<int>& nums, int k, int n) {
    vector<int> rotateNum(n);

    for (int i = 0; i < n; i++) {
      rotateNum[(i + k) % n] = nums[i];
    }

    nums = rotateNum;
  }

  void rotate3(vector<int>& nums, int k, int n) {
    for (int i = 0; i < n / k; i++) {
      for (int j = 0; j < k; j++) {
        swap(nums[i * k + j], nums[n - k + j]);
      }
    }
  }
};

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  int n, k;
  while (cin >> n) {
    cin >> k;

    vector<int> nums(n);
    for (int i = 0; i < n; ++i) {
      cin >> nums[i];
    }

    Solution obj;
    obj.rotate(nums, k);

    cout << "nums = [";
    for (int i = 0; i < nums.size(); ++i) {
      cout << nums[i] << (i == nums.size() - 1 ? "" : ",");
    }
    cout << "]\n";
  }

  return 0;
}