#include <algorithm>
#include <iostream>
#include <queue>
#include <string>
#include <unordered_map>
#include <vector>

using namespace std;

class Solution {
 public:
  int trap(vector<int>& height) {
    int st = 0, n = height.size(), peak = 0, peakSum = 0, rain = 0;
    for (int i = 0; i < n; i++) {
      if (height[i] >= peak) {
        rain += peak * (i - st - 1) - peakSum;
        st = i;
        peakSum = 0;
        peak = height[i];
      } else {
        peakSum += height[i];
      }
    }

    peak = 0;
    peakSum = 0;
    int ed = n - 1;
    for (int i = n - 1; i >= st; i--) {
      if (height[i] >= peak) {
        rain += peak * (ed - i - 1) - peakSum;
        ed = i;
        peakSum = 0;
        peak = height[i];
      } else {
        peakSum += height[i];
      }
    }

    return rain;
  }
};

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  int n;
  while (cin >> n) {
    vector<int> height(n);
    for (int i = 0; i < n; i++) {
      cin >> height[i];
    }

    Solution obj;
    int rain = obj.trap(height);
    cout << rain;
  }

  return 0;
}