#include <algorithm>
#include <iostream>
#include <queue>
#include <string>
#include <unordered_map>
#include <vector>

using namespace std;

class Solution {
   private:
    double calculator(double x, long long n) {
        if (n == 1) return x;
        double res = calculator(x, n / 2);
        return res * res * (n % 2 ? x : 1);
    }

   public:
    double myPow(double x, long long n) {
        if (x == 0) return 0;
        if (n == 0) return 1;
        if (n < 0) {
            x = 1 / x;
            n *= -1;
        }

        return calculator(x, n);
    }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    double x;
    int n;
    cin >> x >> n;

    Solution obj;
    cout << obj.myPow(x, n);

    return 0;
}