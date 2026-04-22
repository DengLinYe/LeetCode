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

    void findCombination(int n, int k, int index, vector<int>& path) {
        if (path.size() == k) {
            res.push_back(path);
            return;
        }

        for (int i = index; i <= n + 1 - k + path.size(); i++) {
            path.push_back(i);
            findCombination(n, k, i + 1, path);
            path.pop_back();
        }
    }

   public:
    vector<vector<int>> combine(int n, int k) {
        res.clear();

        vector<int> path;
        findCombination(n, k, 1, path);

        return res;
    }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, k;
    cin >> n >> k;

    Solution obj;
    vector<vector<int>> res = obj.combine(n, k);

    for (auto& r : res) {
        for (int c : r) {
            cout << c << " ";
        }
        cout << endl;
    }

    return 0;
}