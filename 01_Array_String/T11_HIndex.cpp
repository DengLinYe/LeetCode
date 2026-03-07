#include <algorithm>
#include <iostream>
#include <queue>
#include <string>
#include <unordered_map>
#include <vector>

using namespace std;

class Solution {
 public:
  int hIndex(vector<int>& citations) {
    int n = citations.size(), h = 0;
    unordered_map<int, int> passby;

    for (int x : citations) {
      if (x > h) {
        passby[x]++;
        if (h >= h + 1 - passby[h]) {
          passby[h]--;
        } else {
          h = h + 1 - passby[h];
        }
      }
    }

    return h;
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
    int h = obj.hIndex(nums);
    cout << h;
  }

  return 0;
}