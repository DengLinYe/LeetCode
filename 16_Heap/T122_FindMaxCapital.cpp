#include <algorithm>
#include <iostream>
#include <queue>
#include <string>
#include <unordered_map>
#include <vector>

using namespace std;

class Solution {
   private:
    void buildHeap(vector<pair<int, int>>& pairs, priority_queue<pair<int, int>>& pq, int w) {
        while (!pairs.empty()) {
            if (pairs.back().second > w) return;
            pq.push(pairs.back());
            pairs.pop_back();
        }
    }

   public:
    int findMaximizedCapital(int k, int w, vector<int>& profits, vector<int>& capital) {
        vector<pair<int, int>> pairs(profits.size());
        for (int i = 0; i < profits.size(); i++) {
            pairs[i].first = profits[i];
            pairs[i].second = capital[i];
        }
        sort(pairs.begin(), pairs.end(),
             [](const pair<int, int>& a, const pair<int, int>& b) { return a.second > b.second; });

        priority_queue<pair<int, int>> pq;
        while (k > 0) {
            buildHeap(pairs, pq, w);
            if (pq.empty()) return w;

            w += pq.top().first;
            k--;
            pq.pop();
        }

        return w;
    }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, k, w;
    cin >> n >> k >> w;
    vector<int> capital(n), profits(n);
    for (int i = 0; i < n; i++) {
        cin >> profits[i];
    }
    for (int i = 0; i < n; i++) {
        cin >> capital[i];
    }

    Solution obj;
    cout << obj.findMaximizedCapital(k, w, profits, capital);

    return 0;
}