#include <algorithm>
#include <iostream>
#include <queue>
#include <string>
#include <unordered_map>
#include <vector>

using namespace std;

class Solution {
 public:
  int minSubArrayLen(int target, vector<int>& nums) {
    int i = 0, j = 1, n = nums.size(), sum = nums[0], minLen = 100001;
    if (n < 2) {
      return (sum >= target ? 1 : 0);
    }

    while (i < j) {
      if (sum >= target) {
        minLen = min(minLen, j - i);
        sum -= nums[i++];
      } else {
        if (j == n) break;
        sum += nums[j++];
      }
    }

    return (minLen == 100001 ? 0 : minLen);
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
  cout << obj.minSubArrayLen(target, nums);

  return 0;
}