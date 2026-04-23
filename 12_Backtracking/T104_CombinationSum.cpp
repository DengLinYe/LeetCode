#include <algorithm>
#include <iostream>
#include <queue>
#include <string>
#include <unordered_map>
#include <vector>

using namespace std;

class Solution {
   private:
    vector<vector<int>> res;
    vector<int> path;

    void DFS(vector<int>& nums, int index, int sum, int target) {
        if (sum == target) {
            res.push_back(path);
            return;
        }

        for (int i = index; i < nums.size(); i++) {
            if (sum + nums[i] > target) {
                return;
            }

            path.push_back(nums[i]);
            sum += nums[i];
            DFS(nums, i, sum, target);
            path.pop_back();
            sum -= nums[i];
        }
    }

   public:
    vector<vector<int>> combinationSum(vector<int>& candidates, int target) {
        res.clear();
        path.clear();

        int sum = 0;
        sort(candidates.begin(), candidates.end());
        DFS(candidates, 0, sum, target);

        return res;
    }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, target;
    cin >> n >> target;
    vector<int> nums(n);
    for (int i = 0; i < n; i++) {
        cin >> nums[i];
    }

    Solution obj;
    vector<vector<int>> res = obj.combinationSum(nums, target);

    for (auto& r : res) {
        for (int c : r) {
            cout << c << " ";
        }

        cout << endl;
    }

    return 0;
}