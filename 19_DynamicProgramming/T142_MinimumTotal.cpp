#include <algorithm>
#include <iostream>
#include <queue>
#include <string>
#include <unordered_map>
#include <vector>

using namespace std;

class Solution {
   public:
    int minimumTotal(vector<vector<int>>& triangle) {
        int n = triangle.size(), minPath = INT_MAX;

        queue<int> q;
        q.push(triangle[0][0]);
        while (!q.empty()) {
            int layer = q.size();
            if (layer > n) break;

            for (int i = 0; i < layer; i++) {
                int len = q.front();
                q.pop();

                if (layer == n) {
                    minPath = min(minPath, len);
                } else {
                    if (i == 0) {
                        q.push(len + triangle[layer][i]);
                    } else {
                        if (len + triangle[layer][i] < q.back()) {
                            q.back() = len + triangle[layer][i];
                        }
                    }
                    q.push(len + triangle[layer][i + 1]);
                }
            }
        }

        return minPath;
    }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;
    vector<vector<int>> triangle(n, vector<int>(n));
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < i + 1; j++) {
            cin >> triangle[i][j];
        }
    }

    Solution obj;
    cout << obj.minimumTotal(triangle);

    return 0;
}