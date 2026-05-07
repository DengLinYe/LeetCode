#include <algorithm>
#include <iostream>
#include <queue>
#include <string>
#include <unordered_map>
#include <vector>

using namespace std;

class Solution {
   public:
    string addBinary(string a, string b) {
        if (a.size() < b.size()) swap(a, b);

        int n = a.size(), m = b.size();
        bool c = 0;
        for (int i = 0; i < n; i++) {
            int aI = n - 1 - i, bI = m - 1 - i;
            a[aI] += c + (bI >= 0 ? b[bI] - '0' : 0);
            c = (a[aI] >= '2');
            a[aI] = '0' + (a[aI] - '0') % 2;
        }
        if (c) a = '1' + a;

        return a;
    }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    string a, b;
    cin >> a >> b;

    Solution obj;
    cout << obj.addBinary(a, b);

    return 0;
}