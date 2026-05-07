#include <algorithm>
#include <iostream>
#include <queue>
#include <string>
#include <unordered_map>
#include <vector>

using namespace std;

class Solution {
   public:
    int reverseBits(int n) {
        int ans = 0;
        long long base = 1;
        vector<bool> bits(32);
        int i = 0;
        while (n >= 1) {
            bits[i++] = n % 2;
            n /= 2;
        }

        reverse(bits.begin(), bits.end());
        for (auto bit : bits) {
            // cout << bit;
            ans += bit * base;
            base *= 2;
        }
        // cout << endl;
        return ans;
    }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;

    Solution obj;
    cout << obj.reverseBits(n);

    return 0;
}