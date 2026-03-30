#include <algorithm>
#include <iostream>
#include <queue>
#include <sstream>
#include <string>
#include <unordered_map>
#include <vector>

using namespace std;

class Solution {
   public:
    int calculate(string s) {
        int n = s.size();
        long long sum = 0;
        bool sign = true;
        vector<bool> bracket;

        for (int i = 0; i < n; i++) {
            if (s[i] == '-' || s[i] == '+') {
                if (!bracket.empty() && !bracket.back()) {
                    sign = s[i] == '-';
                } else {
                    sign = s[i] == '+';
                }
            } else if (s[i] == '(') {
                int index = i;
                while (index > 0 && s[--index] == ' ');
                bracket.push_back(sign);
            } else if (s[i] == ')') {
                bracket.pop_back();
            } else if (s[i] == ' ') {
                continue;
            } else {
                int st = i;
                while (i < n - 1 && isdigit(s[++i]));
                long long num;
                if (i == n - 1) {
                    num = stol(s.substr(st, n - st));
                    sum += (sign ? num : -num);
                    break;
                } else {
                    num = stol(s.substr(st, i - st));
                    sum += (sign ? num : -num);
                    i--;
                }
            }
        }

        return sum;
    }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    string s;
    getline(cin, s);

    Solution obj;
    cout << obj.calculate(s);
    return 0;
}