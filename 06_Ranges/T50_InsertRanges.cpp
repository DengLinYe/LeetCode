#include <algorithm>
#include <iostream>
#include <queue>
#include <string>
#include <unordered_map>
#include <vector>

using namespace std;

class Solution {
   public:
    vector<vector<int>> insert(vector<vector<int>>& intervals, vector<int>& newInterval) {
        int n = intervals.size();
        if (n == 0) return {newInterval};

        int left = 0, right = n - 1;
        while (right != left) {
            int middle = (left + right) / 2;
            if (newInterval[0] == intervals[middle][0]) {
                right = middle;
                left = middle;
            } else if (newInterval[0] > intervals[middle][0]) {
                if (newInterval[0] <= intervals[middle][1]) {
                    left = middle;
                    right = middle;
                } else {
                    left = middle + 1;
                }
            } else {
                right = middle;
            }
        }

        vector<vector<int>> res;
        bool flag;
        int l;
        for (int i = 0; i < n; i++) {
            if (i < left) {
                res.push_back(intervals[i]);
            } else {
                if (flag) {
                    res.push_back(intervals[i]);
                } else {
                    if (i == left) {
                        if (intervals[i][1] >= newInterval[0]) {
                            l = min(intervals[i][0], newInterval[0]);
                        } else {
                            res.push_back(intervals[i]);
                            l = newInterval[0];
                        }
                    }
                    if (intervals[i][0] > newInterval[1]) {
                        res.push_back({l, newInterval[1]});
                        res.push_back(intervals[i]);
                        flag = true;
                    } else if (intervals[i][1] >= newInterval[1]) {
                        res.push_back({l, intervals[i][1]});
                        flag = true;
                    } else if (i == n - 1) {
                        res.push_back({l, newInterval[1]});
                        flag = true;
                    }
                }
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

    vector<int> newInterval(2);
    cin >> newInterval[0] >> newInterval[1];

    Solution obj;
    vector<vector<int>> res = obj.insert(intervals, newInterval);

    for (const auto& x : res) {
        cout << "[" << x[0] << ":" << x[1] << "]" << endl;
    }

    return 0;
}