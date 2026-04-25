#include <algorithm>
#include <iostream>
#include <queue>
#include <string>
#include <unordered_map>
#include <vector>

using namespace std;

class Solution {
   private:
    int n;
    int m;

    bool wordSearch(vector<vector<char>>& board, string& word, int k, int i, int j) {
        if (board[i][j] == word[k]) {
            if (k == word.size() - 1) return true;
        } else {
            return false;
        }

        char c = board[i][j];
        board[i][j] = '0';
        if (i - 1 >= 0 && board[i - 1][j] != '0' && wordSearch(board, word, k + 1, i - 1, j)) return true;
        if (i + 1 < n && board[i + 1][j] != '0' && wordSearch(board, word, k + 1, i + 1, j)) return true;
        if (j - 1 >= 0 && board[i][j - 1] != '0' && wordSearch(board, word, k + 1, i, j - 1)) return true;
        if (j + 1 < m && board[i][j + 1] != '0' && wordSearch(board, word, k + 1, i, j + 1)) return true;
        board[i][j] = c;

        return false;
    }

   public:
    bool exist(vector<vector<char>>& board, string word) {
        n = board.size();
        m = board[0].size();

        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {
                if (board[i][j] == word[0] && wordSearch(board, word, 0, i, j)) {
                    return true;
                }
            }
        }

        return false;
    }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m;
    cin >> n >> m;

    vector<vector<char>> board(n, vector<char>(m));
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            cin >> board[i][j];
        }
    }

    string word;
    cin >> word;

    Solution obj;
    cout << (obj.exist(board, word) ? "true" : "false");

    return 0;
}