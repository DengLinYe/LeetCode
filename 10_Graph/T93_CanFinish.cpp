#include <algorithm>
#include <iostream>
#include <queue>
#include <string>
#include <unordered_map>
#include <vector>

using namespace std;

class Solution {
   private:
    unordered_map<int, vector<int>> graph;

   public:
    bool canFinish(int numCourses, vector<vector<int>>& prerequisites) {
        graph.clear();
        for (int i = 0; i < numCourses; i++) {
            graph[i] = vector<int>();
        }

        for (auto& pre : prerequisites) {
            graph[pre[0]].push_back(pre[1]);
        }

        vector<int> state(numCourses, 0);
        for (int i = 0; i < numCourses; i++) {
            if (state[i] == 0) {
                if (!checkCirc(state, i)) return false;
            }
        }

        return true;
    }

   private:
    bool checkCirc(vector<int>& state, int node) {
        state[node] = 1;

        for (auto neighbor : graph[node]) {
            if (state[neighbor] == 1) {
                return false;
            }
            if (state[neighbor] == 0) {
                if (!checkCirc(state, neighbor)) return false;
            }
        }

        state[node] = 2;
        return true;
    }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, numCourses;
    cin >> n >> numCourses;

    vector<vector<int>> prerequisites(n, vector<int>(2));
    for (int i = 0; i < n; i++) {
        cin >> prerequisites[i][0] >> prerequisites[i][1];
    }

    Solution obj;
    cout << (obj.canFinish(n, prerequisites) ? "true" : "false");

    return 0;
}