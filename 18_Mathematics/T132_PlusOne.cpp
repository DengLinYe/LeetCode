#include <algorithm>
#include <iostream>
#include <queue>
#include <string>
#include <unordered_map>
#include <vector>

using namespace std;

class Solution {
   public:
    vector<int> plusOne(vector<int>& digits) {
        int n = digits.size();
        bool c = 1;
        while (c && n >= 1) {
            digits[n - 1] += c;
            c = (digits[n - 1] == 10);
            digits[n - 1] -= c * 10;
            n--;
        }
        if (c) digits.insert(digits.begin(), 1);
        return digits;
    }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;
    vector<int> digits(n);
    for (int i = 0; i < n; i++) {
        cin >> digits[i];
    }

    Solution obj;
    auto res = obj.plusOne(digits);
    for (int r : res) {
        cout << r;
    }

    return 0;
}