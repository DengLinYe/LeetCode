#include <algorithm>
#include <iostream>
#include <queue>
#include <string>
#include <unordered_map>
#include <vector>

using namespace std;

class Solution {
   public:
    vector<vector<int>> merge(vector<vector<int>>& intervals) {
        sort(intervals.begin(), intervals.end(),
             [](const vector<int>& a, const vector<int>& b) { return a[0] < b[0]; });

        int n = intervals.size();
        vector<vector<int>> res;

        res.push_back(intervals.front());
        for (int i = 1; i < n; i++) {
            vector<int>& lastRanges = res.back();
            if (lastRanges[0] <= intervals[i][0] && intervals[i][0] <= lastRanges[1]) {
                lastRanges[1] = max(lastRanges[1], intervals[i][1]);
            } else {
                res.push_back(intervals[i]);
            }
        }

        return res;
    }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;

    vector<vector<int>> intervals(n, vector<int>(2));
    for (int i = 0; i < n; i++) {
        cin >> intervals[i][0] >> intervals[i][1];
    }

    Solution obj;
    vector<vector<int>> res = obj.merge(intervals);

    for (vector<int> x : res) {
        cout << "[" << x[0] << ":" << x[1] << "]" << endl;
    }

    return 0;
}