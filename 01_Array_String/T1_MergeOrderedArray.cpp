#include <algorithm>
#include <iostream>
#include <queue>
#include <string>
#include <unordered_map>
#include <vector>

using namespace std;

class Solution {
 public:
  void merge(vector<int>& nums1, int m, vector<int>& nums2, int n) {
    int k = m + n - 1;
    m--;
    n--;

    while (m >= 0 && n >= 0) {
      if (nums1[m] < nums2[n]) {
        nums1[k] = nums2[n];
        n--;
      } else {
        nums1[k] = nums1[m];
        m--;
      }
      k--;
    }

    while (n >= 0) {
      nums1[k] = nums2[n];
      k--;
      n--;
    }
  }
};

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  int m, n;
  while (cin >> m >> n) {
    vector<int> nums1(m + n);
    for (int i = 0; i < m + n; ++i) {
      cin >> nums1[i];
    }

    vector<int> nums2(n);
    for (int i = 0; i < n; ++i) {
      cin >> nums2[i];
    }

    Solution().merge(nums1, m, nums2, n);

    cout << "[";
    for (int i = 0; i < m + n; ++i) {
      cout << nums1[i] << (i == m + n - 1 ? "" : ",");
    }
    cout << "]\n";
  }

  return 0;
}