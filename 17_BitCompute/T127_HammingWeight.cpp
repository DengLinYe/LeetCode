#include <algorithm>
#include <cstdint>
#include <iostream>
#include <queue>
#include <string>
#include <unordered_map>
#include <vector>

using namespace std;

class Solution {
   public:
    int hammingWeight(int n) {
        uint32_t m = n;
        int ans = 0;
        for (int i = 0; i < 32; i++) {
            if (m & 1) ans++;
            m >>= 1;
        }

        return ans;
    }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;

    Solution obj;
    cout << obj.hammingWeight(n);

    return 0;
}