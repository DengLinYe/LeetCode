#include <algorithm>
#include <climits>
#include <iostream>
#include <vector>

using namespace std;

class Solution {
   private:
    int minTimes;
    int n;

   public:
    int snakesAndLadders(vector<vector<int>>& board) {
        minTimes = INT_MAX;
        n = board.size();
        vector<int> visited(n * n + 1, INT_MAX);

        move(board, 0, 1, visited);

        return (minTimes == INT_MAX ? -1 : minTimes);
    }

   private:
    void move(vector<vector<int>>& board, int times, int pos, vector<int>& visited) {
        if (times >= minTimes) return;

        if (times >= visited[pos]) return;
        visited[pos] = times;

        if (pos == n * n) {
            minTimes = times;
            return;
        }

        for (int i = 1; i <= 6; i++) {
            int nextPos = pos + i;
            if (nextPos > n * n) break;

            int r = n - 1 - (nextPos - 1) / n;
            int c = ((nextPos - 1) / n) % 2 == 0 ? (nextPos - 1) % n : n - 1 - (nextPos - 1) % n;

            int dest = (board[r][c] == -1 ? nextPos : board[r][c]);

            move(board, times + 1, dest, visited);
        }
    }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    if (!(cin >> n)) return 0;
    if (n == 0) return 0;

    vector<vector<int>> board(n, vector<int>(n));
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            cin >> board[i][j];
        }
    }

    Solution obj;
    cout << obj.snakesAndLadders(board) << "\n";

    return 0;
}