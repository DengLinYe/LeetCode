#include <algorithm>
#include <iostream>
#include <queue>
#include <string>
#include <unordered_map>
#include <vector>

using namespace std;

class Solution {
   public:
    vector<vector<int>> kSmallestPairs(vector<int>& nums1, vector<int>& nums2, int k) {
        auto cmp = [&nums1, &nums2](const pair<int, int>& a, const pair<int, int>& b) {
            return nums1[a.first] + nums2[a.second] > nums1[b.first] + nums2[b.second];
        };
        priority_queue<pair<int, int>, vector<pair<int, int>>, decltype(cmp)> pq(cmp);

        int n = nums1.size(), m = nums2.size();
        for (int i = 0; i < min(k, n); i++) {
            pq.push({i, 0});
        }

        vector<vector<int>> res(0, vector<int>(2));
        while (k-- > 0 && !pq.empty()) {
            auto [i, j] = pq.top();
            pq.pop();

            res.push_back({nums1[i], nums2[j]});

            if (j + 1 < m) pq.push({i, j + 1});
        }

        return res;
    }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m, k;
    cin >> n >> m >> k;

    vector<int> nums1(n), nums2(m);
    for (int i = 0; i < n; i++) {
        cin >> nums1[i];
    }
    for (int i = 0; i < m; i++) {
        cin >> nums2[i];
    }

    Solution obj;
    vector<vector<int>> res = obj.kSmallestPairs(nums1, nums2, k);

    for (auto& c : res) {
        cout << "[" << c[0] << ", " << c[1] << (c == res.back() ? "]" : "], ");
    }

    return 0;
}