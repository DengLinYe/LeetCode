#include <algorithm>
#include <iostream>
#include <queue>
#include <string>
#include <unordered_map>
#include <vector>

using namespace std;

class Solution {
   public:
    vector<int> findOrder(int numCourses, vector<vector<int>>& prerequisites) {
        vector<vector<int>> baseCourse(numCourses);
        vector<int> inDegree(numCourses, 0);
        vector<int> res;

        for (auto& pre : prerequisites) {
            baseCourse[pre[1]].push_back(pre[0]);
            inDegree[pre[0]]++;
        }

        queue<int> course;
        for (int i = 0; i < numCourses; i++) {
            if (inDegree[i] == 0) {
                course.push(i);
            }
        }

        int count = 0;
        while (!course.empty()) {
            int curr = course.front();
            course.pop();
            res.push_back(curr);
            count++;

            for (int x : baseCourse[curr]) {
                inDegree[x]--;
                if (inDegree[x] == 0) {
                    course.push(x);
                }
            }
        }

        return count == numCourses ? res : vector<int>();
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
    vector<int> res = obj.findOrder(n, prerequisites);

    for (auto x : res) cout << x << " ";

    return 0;
}