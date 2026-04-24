#include <algorithm>
#include <iostream>
#include <queue>
#include <string>
#include <unordered_map>
#include <vector>

using namespace std;

class Solution {
   private:
    vector<bool> c;
    vector<bool> y;
    vector<bool> x;
    int n;
    int nums;

    void placeQueens(int index) {
        if (index == n) {
            nums++;
            return;
        }

        for (int i = 0; i < n; i++) {
            if (c[i]) continue;
            if (x[n - index + i - 1]) continue;
            if (y[2 * n - index - i - 2]) continue;

            c[i] = true;
            x[n - index + i - 1] = true;
            y[2 * n - index - i - 2] = true;
            placeQueens(index + 1);
            c[i] = false;
            x[n - index + i - 1] = false;
            y[2 * n - index - i - 2] = false;
        }
    }

   public:
    int totalNQueens(int n) {
        this->n = n;
        c.resize(n, false);
        x.resize(2 * n - 1, false);
        y.resize(2 * n - 1, false);
        nums = 0;
        placeQueens(0);

        return nums;
    }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;

    Solution obj;
    cout << obj.totalNQueens(n);

    return 0;
}