#include <algorithm>
#include <iostream>
#include <queue>
#include <string>
#include <unordered_map>
#include <vector>

using namespace std;

class Solution {
   public:
    int rangeBitwiseAnd(int left, int right) {
        long long base = 1;
        while (base < right - left) base *= 2;
        base = ~(base - 1);
        return (right & left) & base;
    }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int left, right;
    cin >> left >> right;

    Solution obj;
    cout << obj.rangeBitwiseAnd(left, right);

    return 0;
}