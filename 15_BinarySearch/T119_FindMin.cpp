#include <algorithm>
#include <iostream>
#include <queue>
#include <string>
#include <unordered_map>
#include <vector>

using namespace std;

class Solution {
   public:
    int findMin(vector<int>& nums) {
        int n = nums.size();
        if (nums[n - 1] >= nums[0]) return nums[0];

        int i = 0, j = n - 1;
        while (i < j) {
            int mid = i + (j - i) / 2;
            if (nums[mid] >= nums[0]) {
                i = mid + 1;
            } else {
                j = mid;
            }
        }

        return nums[i];
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
    cout << obj.findMin(nums) << endl;

    return 0;
}