#include <iostream>
#include <vector>

using namespace std;

class Solution {
   public:
    void solve(vector<vector<char>>& board) {
        if (board.empty()) return;
        int n = board.size(), m = board[0].size();

        for (int i = 0; i < n; i++) {
            if (board[i][0] == 'O') {
                DFS(board, i, 0, 'B');
            }
            if (board[i][m - 1] == 'O') {
                DFS(board, i, m - 1, 'B');
            }
        }

        for (int i = 0; i < m; i++) {
            if (board[0][i] == 'O') {
                DFS(board, 0, i, 'B');
            }
            if (board[n - 1][i] == 'O') {
                DFS(board, n - 1, i, 'B');
            }
        }

        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {
                if (board[i][j] == 'O') {
                    DFS(board, i, j, 'X');
                }
            }
        }

        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {
                if (board[i][j] == 'B') {
                    board[i][j] = 'O';
                }
            }
        }
    }

   private:
    void DFS(vector<vector<char>>& grid, int i, int j, char modify) {
        grid[i][j] = modify;

        if (i - 1 >= 0 && grid[i - 1][j] == 'O') DFS(grid, i - 1, j, modify);
        if (j - 1 >= 0 && grid[i][j - 1] == 'O') DFS(grid, i, j - 1, modify);
        if (i + 1 < grid.size() && grid[i + 1][j] == 'O') DFS(grid, i + 1, j, modify);
        if (j + 1 < grid[0].size() && grid[i][j + 1] == 'O') DFS(grid, i, j + 1, modify);
    }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m;
    if (!(cin >> n >> m)) return 0;
    if (n == 0 || m == 0) return 0;

    vector<vector<char>> board(n, vector<char>(m));
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            cin >> board[i][j];
        }
    }

    Solution obj;
    obj.solve(board);

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            cout << board[i][j] << " ";
        }
        cout << "\n";
    }

    return 0;
}