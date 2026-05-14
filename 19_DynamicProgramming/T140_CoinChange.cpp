#include <algorithm>
#include <iostream>
#include <queue>
#include <string>
#include <unordered_map>
#include <vector>

using namespace std;

class Solution {
   public:
    int coinChange(vector<int>& coins, int amount) {
        int maxNum = 0, minNum = INT_MAX;
        for (int c : coins) {
            maxNum = max(maxNum, c);
            minNum = min(minNum, c);
        }

        vector<int> dp(amount + 1, -1);
        dp[0] = 0;
        int j = 0;
        for (int i = minNum; i <= amount; i++) {
            if (i - j > maxNum) return -1;
            for (int c : coins) {
                if (i - c < 0) continue;
                if (dp[i - c] == -1) continue;
                if (dp[i] == -1)
                    dp[i] = dp[i - c] + 1;
                else
                    dp[i] = min(dp[i], dp[i - c] + 1);
                j = i;
            }
        }

        return dp[amount];
    }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, amount;
    cin >> n >> amount;
    vector<int> coins(n);
    for (int i = 0; i < n; i++) {
        cin >> coins[i];
    }

    Solution obj;
    cout << obj.coinChange(coins, amount);

    return 0;
}