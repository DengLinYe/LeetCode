#include <algorithm>
#include <iostream>
#include <queue>
#include <string>
#include <unordered_map>
#include <vector>

using namespace std;

class Solution {
   public:
    int findMinArrowShots(vector<vector<int>>& points) {
        int n = points.size(), sum = 0;
        if (n == 1) return 1;

        sort(points.begin(), points.end(), [](const vector<int>& a, const vector<int>& b) { return a[0] < b[0]; });
        int nowRight = points[0][1];

        for (int i = 1; i < n; i++) {
            if (points[i][0] <= nowRight) {
                nowRight = min(nowRight, points[i][1]);
            } else {
                sum++;
                nowRight = points[i][1];
            }

            if (i == n - 1) {
                sum++;
            }
        }

        return sum;
    }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;

    vector<vector<int>> points(n, vector<int>(2));
    for (int i = 0; i < n; i++) {
        cin >> points[i][0] >> points[i][1];
    }

    Solution obj;
    cout << obj.findMinArrowShots(points);

    return 0;
}