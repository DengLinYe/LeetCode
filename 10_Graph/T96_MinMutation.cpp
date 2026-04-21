#include <algorithm>
#include <iostream>
#include <queue>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>

using namespace std;

class Solution {
   public:
    int minMutation(string startGene, string endGene, vector<string>& bank) {
        unordered_set<string> visited;
        queue<pair<string, int>> q;

        q.push({startGene, 0});
        visited.insert(startGene);

        while (!q.empty()) {
            auto [curr, step] = q.front();
            q.pop();

            if (curr == endGene) return step;

            for (string& gene : bank) {
                if (!visited.count(gene) && isCanConvert(curr, gene)) {
                    visited.insert(gene);
                    q.push({gene, step + 1});
                }
            }
        }

        return -1;
    }

   private:
    bool isCanConvert(string st, string ed) {
        bool times = false;
        for (int i = 0; i < 8; i++) {
            if (st[i] != ed[i]) {
                if (times) return false;
                times = true;
            }
        }

        return times;
    }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    string start, end;
    int n;
    cin >> n >> start >> end;

    vector<string> bank(n);
    for (int i = 0; i < n; i++) {
        cin >> bank[i];
    }

    Solution obj;
    cout << obj.minMutation(start, end, bank);

    return 0;
}