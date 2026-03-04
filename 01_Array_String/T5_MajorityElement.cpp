#include <algorithm>
#include <iostream>
#include <queue>
#include <string>
#include <unordered_map>
#include <vector>

using namespace std;

class Solution {
 public:
  int majorityElement(vector<int>& nums) {
    unordered_map<int, int> freq;
    int max = 0, maxNum = 0;

    for (auto x : nums) {
      if (++freq[x] > max) {
        max = freq[x];
        maxNum = x;
      }
    }

    return maxNum;
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
    int k = obj.majorityElement(nums);

    cout << k;
  }

  return 0;
}