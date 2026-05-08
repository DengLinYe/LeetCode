#include <algorithm>
#include <cstdint>
#include <iostream>
#include <queue>
#include <string>
#include <unordered_map>
#include <vector>

using namespace std;

class Solution {
   public:
    int singleNumber(vector<int>& nums) {
        uint32_t res = nums[0];
        for (int i = 1; i < nums.size(); i++) {
            res ^= nums[i];
        }

        return res;
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
    cout << obj.singleNumber(nums);

    return 0;
}