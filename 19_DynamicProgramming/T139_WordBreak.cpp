#include <algorithm>
#include <iostream>
#include <queue>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>

using namespace std;

class Solution {
   public:
    bool wordBreak(string s, vector<string>& wordDict) {
        unordered_set<string> words;
        int maxLen = 0, minLen = INT_MAX, n = s.size();
        for (string& w : wordDict) {
            words.insert(w);
            maxLen = max(maxLen, int(w.size()));
            minLen = min(minLen, int(w.size()));
        }

        vector<int> dp(n + 1, 0);
        dp[0] = 1;
        int j = 0;
        for (int i = minLen; i <= n; i++) {
            if (i - j > maxLen) return false;
            for (int k = minLen; k <= maxLen; k++) {
                int st = i - k;
                if (st < 0) break;
                if (dp[st] == 0) continue;
                if (words.count(s.substr(st, k))) {
                    dp[i] = 1;
                    j = i;
                }
            }
        }

        return dp[n];
    }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;
    vector<string> words(n);
    for (int i = 0; i < n; i++) {
        cin >> words[i];
    }

    string s;
    cin >> s;

    Solution obj;
    cout << (obj.wordBreak(s, words) ? "true" : "false");

    return 0;
}