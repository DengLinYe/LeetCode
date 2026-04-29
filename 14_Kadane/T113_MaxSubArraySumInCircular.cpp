#include <algorithm>
#include <iostream>
#include <queue>
#include <string>
#include <unordered_map>
#include <vector>

using namespace std;

class Solution {
   public:
    int maxSubarraySumCircular(vector<int>& nums) {
        int n = nums.size();
        int sumMax = nums[0], sum = nums[0], leftSum = nums[0], rightSum = 0;

        vector<int> leftMax(n);
        leftMax[0] = nums[0];

        for (int i = 1; i < n; i++) {
            sum = max(nums[i], sum + nums[i]);
            sumMax = max(sum, sumMax);
            leftSum += nums[i];
            leftMax[i] = max(leftMax[i - 1], leftSum);
        }

        for (int i = n - 1; i >= 1; i--) {
            rightSum += nums[i];
            sumMax = max(sumMax, leftMax[i - 1] + rightSum);
        }

        return sumMax;
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
    cout << obj.maxSubarraySumCircular(nums);

    return 0;
}