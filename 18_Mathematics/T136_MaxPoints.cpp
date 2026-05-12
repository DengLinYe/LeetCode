#include <algorithm>
#include <iostream>
#include <string>
#include <unordered_map>
#include <vector>

using namespace std;

class Solution {
   private:
    int gcd(int a, int b) { return b == 0 ? a : gcd(b, a % b); }

   public:
    int maxPoints(vector<vector<int>>& points) {
        int n = points.size();
        if (n <= 2) return n;

        int maxN = 0;

        for (int i = 0; i < n; i++) {
            unordered_map<string, int> localMap;
            int localMax = 0;

            for (int j = i + 1; j < n; j++) {
                int dx = points[j][0] - points[i][0];
                int dy = points[j][1] - points[i][1];

                int g = gcd(dx, dy);
                dx /= g;
                dy /= g;

                if (dx < 0 || (dx == 0 && dy < 0)) {
                    dx = -dx;
                    dy = -dy;
                }

                string slopeKey = to_string(dx) + "_" + to_string(dy);
                localMap[slopeKey]++;

                localMax = max(localMax, localMap[slopeKey]);
            }

            maxN = max(maxN, localMax + 1);
        }

        return maxN;
    }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    if (cin >> n) {
        vector<vector<int>> points(n, vector<int>(2));
        for (int i = 0; i < n; i++) {
            cin >> points[i][0] >> points[i][1];
        }

        Solution obj;
        cout << obj.maxPoints(points) << "\n";
    }

    return 0;
}