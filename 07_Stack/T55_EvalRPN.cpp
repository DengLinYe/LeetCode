#include <algorithm>
#include <iostream>
#include <queue>
#include <string>
#include <unordered_map>
#include <vector>

using namespace std;
class Solution {
   public:
    int evalRPN(vector<string>& tokens) {
        int n = tokens.size();
        vector<int> stack;

        for (int i = 0; i < n; i++) {
            if (tokens[i] == "+" || tokens[i] == "-" || tokens[i] == "*" || tokens[i] == "/") {
                int b = stack.back();
                stack.pop_back();
                int a = stack.back();
                stack[stack.size() - 1] = calculate(a, b, tokens[i]);
            } else {
                stack.push_back(stoi(tokens[i]));
            }
        }

        return stack.back();
    }

    int calculate(int a, int b, string cal) {
        if (cal == "*") {
            return a * b;
        }
        if (cal == "/") {
            return a / b;
        }
        if (cal == "+") {
            return a + b;
        }
        if (cal == "-") {
            return a - b;
        }

        return 1;
    }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;

    vector<string> s(n);
    for (int i = 0; i < n; i++) {
        cin >> s[i];
    }

    Solution obj;
    cout << obj.evalRPN(s);

    return 0;
}