#include <algorithm>
#include <iostream>
#include <queue>
#include <string>
#include <unordered_map>
#include <vector>

using namespace std;

class Solution {
   public:
    int trailingZeroes(int n) {
        int N = n;
        int a = 0, b = 0;

        while (n > 0) {
            a += n / 5;
            n /= 5;
        }

        n = N;
        while (n > 0) {
            b += n / 2;
            n /= 2;
        }

        return min(a, b);
    }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;

    Solution obj;
    cout << obj.trailingZeroes(n);

    return 0;
}