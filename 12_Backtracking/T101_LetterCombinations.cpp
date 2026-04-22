#include <algorithm>
#include <iostream>
#include <queue>
#include <string>
#include <unordered_map>
#include <vector>

using namespace std;

class Solution {
   private:
    vector<vector<string>> dial = {
        {},
        {},
        {"a", "b", "c"},
        {"d", "e", "f"},
        {"g", "h", "i"},
        {"j", "k", "l"},
        {"m", "n", "o"},
        {"p", "q", "r", "s"},
        {"t", "u", "v"},
        {"w", "x", "y", "z"},
    };

   public:
    vector<string> letterCombinations(string digits) {
        if (digits.size() == 0) return {};

        queue<string> q;
        for (string& c : dial[stoi(digits.substr(0, 1))]) {
            q.push(c);
        }

        for (int i = 1; i < digits.size(); i++) {
            int qSize = q.size();
            for (int j = 0; j < qSize; j++) {
                string curr = q.front();
                q.pop();

                for (string& c : dial[stoi(digits.substr(i, 1))]) {
                    q.push(curr + c);
                }
            }
        }

        vector<string> res;
        while (!q.empty()) {
            res.push_back(q.front());
            q.pop();
        }

        return res;
    }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    string digits;
    cin >> digits;

    Solution obj;
    vector<string> res = obj.letterCombinations(digits);
    for (string& s : res) {
        cout << s << " ";
    }

    return 0;
}