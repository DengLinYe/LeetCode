#include <algorithm>
#include <iostream>
#include <queue>
#include <string>
#include <unordered_map>
#include <vector>

using namespace std;

class Solution {
   public:
    int lengthOfLIS(vector<int>& nums) {
        int n = nums.size(), th = nums[0], totalMax = 1;
        vector<int> dp(n, 1);
        for (int i = 1; i < n; i++) {
            if (nums[i] <= th) {
                th = nums[i];
                continue;
            }

            int maxLen = 0;
            for (int j = 0; j < i; j++) {
                if (nums[j] < nums[i]) maxLen = max(maxLen, dp[j]);
            }

            dp[i] = maxLen + 1;
            totalMax = max(totalMax, dp[i]);
        }

        return totalMax;
    }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;
    vector<int> nums(n);
    for (int i = 0; i < n; i++) {
        cin >> nums[i];
    }

    Solution obj;
    cout << obj.lengthOfLIS(nums);

    return 0;
}