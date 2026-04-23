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
    int n;

    void DFS(vector<int>& nums, int index) {
        if (index == n) {
            res.push_back(path);
        }

        for (int i = index; i < n; i++) {
            swap(nums[index], nums[i]);
            path.push_back(nums[index]);
            DFS(nums, index + 1);
            path.pop_back();
            swap(nums[index], nums[i]);
        }
    }

   public:
    vector<vector<int>> permute(vector<int>& nums) {
        res.clear();
        path.clear();
        n = nums.size();

        DFS(nums, 0);
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
    vector<vector<int>> res = obj.permute(nums);

    for (auto& r : res) {
        for (int c : r) {
            cout << c << " ";
        }
        cout << endl;
    }

    return 0;
}