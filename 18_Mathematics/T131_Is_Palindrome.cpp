#include <algorithm>
#include <iostream>
#include <queue>
#include <string>
#include <unordered_map>
#include <vector>

using namespace std;

class Solution {
   public:
    bool isPalindrome(int x) {
        if (x < 0 || x % 10 == 0 && x != 0) return false;
        long long rev = 0;
        int xOri = x;
        while (x != 0) {
            rev *= 10;
            rev += x % 10;
            x /= 10;
        }

        return rev == xOri;
    }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;

    Solution obj;
    cout << (obj.isPalindrome(n) ? "true" : "false");

    return 0;
}