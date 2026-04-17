#include <algorithm>
#include <iostream>
#include <queue>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>

using namespace std;

struct Node {
    string val;
    vector<pair<Node*, double>> neighbors;

    Node(string _val) : val(_val) { neighbors = vector<pair<Node*, double>>(); }
};

class Solution {
   private:
    unordered_map<string, Node*> build;
    unordered_set<Node*> visit;

   public:
    vector<double> calcEquation(vector<vector<string>>& equations, vector<double>& values,
                                vector<vector<string>>& queries) {
        build.clear();
        int n = equations.size();

        for (int i = 0; i < n; i++) {
            auto& eq = equations[i];

            if (!build.count(eq[0])) {
                build[eq[0]] = new Node(eq[0]);
            }
            if (!build.count(eq[1])) {
                build[eq[1]] = new Node(eq[1]);
            }

            build[eq[0]]->neighbors.push_back({build[eq[1]], values[i]});
            build[eq[1]]->neighbors.push_back({build[eq[0]], values[i] == 0 ? -1 : 1 / values[i]});
        }

        vector<double> res;
        for (auto& q : queries) {
            if (!build.count(q[0]) || !build.count(q[1])) {
                res.push_back(-1);
                continue;
            }
            if (q[0] == q[1]) {
                res.push_back(1);
                continue;
            }

            visit.clear();
            res.push_back(calculate(build[q[0]], q[1]));
        }

        return res;
    }

   private:
    double calculate(Node* st, string& ed) {
        visit.insert(st);

        for (auto neighbor : st->neighbors) {
            if (neighbor.first->val == ed) {
                return neighbor.second;
            }

            if (!visit.count(neighbor.first)) {
                double res = calculate(neighbor.first, ed);
                if (res != -1) return neighbor.second * res;
            }
        }

        return -1;
    }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;
    vector<vector<string>> equations(n, vector<string>(2));
    vector<double> values(n);

    for (int i = 0; i < n; i++) {
        string e1, e2;
        double val;
        cin >> e1 >> e2 >> val;

        equations[i] = {e1, e2};
        values[i] = val;
    }

    int m;
    cin >> m;
    vector<vector<string>> queries(m, vector<string>(2));

    for (int i = 0; i < m; i++) {
        string q1, q2;
        cin >> q1 >> q2;

        queries[i] = {q1, q2};
    }

    Solution obj;
    vector<double> res = obj.calcEquation(equations, values, queries);

    for (auto val : res) {
        cout << val << " ";
    }

    return 0;
}