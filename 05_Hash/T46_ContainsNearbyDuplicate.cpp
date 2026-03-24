#include <algorithm>
#include <iostream>
#include <queue>
#include <string>
#include <unordered_map>
#include <vector>

using namespace std;

class Solution {
 public:
  bool containsNearbyDuplicate(vector<int>& nums, int k) {
    int n = nums.size();
    unordered_map<int, int> index;
    for (int i = 0; i < n; i++) {
      if (index.count(nums[i]) != 0 && i - index[nums[i]] <= k) {
        return true;
      }
      index[nums[i]] = i;
    }
    return false;
  }
};

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  int n, k;
  cin >> n >> k;

  vector<int> nums(n);
  for (int i = 0; i < n; i++) {
    cin >> nums[i];
  }

  Solution obj;
  cout << obj.containsNearbyDuplicate(nums, k);

  return 0;
}