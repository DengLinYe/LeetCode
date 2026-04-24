#include <algorithm>
#include <iostream>
#include <queue>
#include <string>
#include <unordered_map>
#include <vector>

using namespace std;

class Solution {
   private:
    vector<string> res;
    string path;

    void findSeq(int n, int index) {
        if (index == 0) {
            if (n == 0) res.push_back(path);
            return;
        }

        path.push_back('(');
        n++;
        for (int i = 0; i <= n; i++) {
            int temp = n;
            for (int j = 0; j < i; j++) {
                path.push_back(')');
                temp--;
            }

            findSeq(temp, index - 1);

            while (path.back() == ')') path.pop_back();
        }
        path.pop_back();
        n--;
    }

   public:
    vector<string> generateParenthesis(int n) {
        res.clear();
        path = "";
        findSeq(0, n);

        return res;
    }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;

    Solution obj;
    vector<string> res = obj.generateParenthesis(n);

    for (string& r : res) {
        cout << r << " ";
    }

    return 0;
}