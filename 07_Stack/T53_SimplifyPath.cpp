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
    string simplifyPath(string path) {
        int n = path.size();
        stack<string> paths;

        for (int i = 0; i < n;) {
            if (path[i] == '/') {
                while (i < n && path[++i] == '/');
                if (i == n) break;
                int nameIndex = i;

                while (i < n && path[++i] != '/');
                string dir = path.substr(nameIndex, i - nameIndex);

                if (dir == "..") {
                    if (!paths.empty()) paths.pop();
                    continue;
                }
                if (dir != ".") {
                    paths.push(dir);
                }
            }
        }

        string res = "";
        while (!paths.empty()) {
            res = "/" + paths.top() + res;
            paths.pop();
        }

        return (res == "" ? "/" : res);
    }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    string path;
    getline(cin, path);

    Solution obj;
    cout << obj.simplifyPath(path);

    return 0;
}