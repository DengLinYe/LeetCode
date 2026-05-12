#include <algorithm>
#include <iostream>
#include <queue>
#include <string>
#include <unordered_map>
#include <vector>

using namespace std;

class Solution {
   public:
    int mySqrt(int x) {
        if (x < 2) return x;

        long long i = x;
        while (i * i > x) i /= 2;

        int left = i, right = i * 2;
        while (left <= right) {
            long long mid = left + (right - left) / 2;
            // cout << mid << endl;
            if (mid * mid <= x)
                left = mid + 1;
            else
                right = mid - 1;
        }

        return --left;
    }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;

    Solution obj;
    cout << obj.mySqrt(n);

    return 0;
}