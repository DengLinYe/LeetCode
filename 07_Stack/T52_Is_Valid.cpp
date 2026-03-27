#include <algorithm>
#include <iostream>
#include <queue>
#include <stack>
#include <string>
#include <unordered_map>
#include <vector>

using namespace std;

class Solution {
   public:
    bool isValid(string s) {
        stack<char> b;

        for (char c : s) {
            switch (c) {
                case '(':
                case '[':
                case '{': {
                    b.push(c);
                    break;
                }
                case ')':
                case ']':
                case '}': {
                    if (!b.empty() && c == match(b.top())) {
                        b.pop();
                    } else {
                        return false;
                    }
                    break;
                }
            }
        }

        if (b.empty()) {
            return true;
        } else {
            return false;
        }
    }

    char match(char& a) {
        switch (a) {
            case '(':
                return ')';
            case '[':
                return ']';
            case '{':
                return '}';
        }
        return ' ';
    }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    string s;
    getline(cin, s);

    Solution obj;
    cout << obj.isValid(s);

    return 0;
}