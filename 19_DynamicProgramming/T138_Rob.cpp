#include <algorithm>
#include <iostream>
#include <queue>
#include <string>
#include <unordered_map>
#include <vector>

using namespace std;

class Solution {
   public:
    int rob(vector<int>& nums) {
        int n = nums.size();
        if (n == 1) return nums[0];

        int pre1 = nums[0], pre2 = max(nums[0], nums[1]);
        for (int i = 2; i < n; i++) {
            int curr = max(pre1 + nums[i], pre2);
            pre1 = pre2;
            pre2 = curr;
        }

        return pre2;
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
    cout << obj.rob(nums);

    return 0;
}