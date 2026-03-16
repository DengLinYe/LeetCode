#include <algorithm>
#include <iostream>
#include <queue>
#include <string>
#include <unordered_map>
#include <vector>

using namespace std;

class Solution {
 public:
  int maxArea(vector<int>& height) {
    int i = 0, j = height.size() - 1, maxVol = 0;
    while (i < j) {
      int vol = (j - i) * min(height[i], height[j]);
      maxVol = max(vol, maxVol);

      if (height[i] < height[j]) {
        i++;
      } else {
        j--;
      }
    }

    return maxVol;
  }
};

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  int n;
  cin >> n;

  vector<int> heights(n);
  for (int i = 0; i < n; i++) {
    cin >> heights[i];
  }

  Solution obj;
  cout << obj.maxArea(heights);

  return 0;
}