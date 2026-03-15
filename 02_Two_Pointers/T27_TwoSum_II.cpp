#include <algorithm>
#include <iostream>
#include <queue>
#include <string>
#include <unordered_map>
#include <vector>

using namespace std;

class Solution {
 public:
  vector<int> twoSum(vector<int>& numbers, int target) {
    vector<int> a(2);
    int n = numbers.size(), i = 0;
    int j = n - 1;
    while (i < j) {
      if (numbers[i] + numbers[j] == target) {
        a[0] = i + 1;
        a[1] = j + 1;
        return a;
      } else if (numbers[i] + numbers[j] > target) {
        j--;
      } else {
        i++;
      }
    }

    return a;
  }
};

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  int n, t;
  cin >> n >> t;

  vector<int> nums(n);
  for (int i = 0; i < n; i++) {
    cin >> nums[i];
  }

  Solution obj;
  vector<int> sum = obj.twoSum(nums, t);

  cout << sum[0] << " " << sum[1];
  return 0;
}