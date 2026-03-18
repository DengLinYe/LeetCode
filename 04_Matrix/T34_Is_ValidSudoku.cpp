#include <iostream>
#include <vector>

using namespace std;

class Solution {
 public:
  bool isValidSudoku(vector<vector<char>>& board) {
    vector<vector<bool>> row(9, vector<bool>(9, false));
    vector<vector<bool>> col(9, vector<bool>(9, false));
    vector<vector<bool>> sqa(9, vector<bool>(9, false));

    for (int i = 0; i < 9; i++) {
      for (int j = 0; j < 9; j++) {
        if (board[i][j] != '.') {
          int num = board[i][j] - '1';
          int boxIndex = (i / 3) * 3 + j / 3;

          if (row[i][num] || col[j][num] || sqa[boxIndex][num]) {
            return false;
          }

          row[i][num] = true;
          col[j][num] = true;
          sqa[boxIndex][num] = true;
        }
      }
    }

    return true;
  }
};

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  vector<vector<char>> board(9, vector<char>(9));
  for (int i = 0; i < 9; i++) {
    for (int j = 0; j < 9; j++) {
      cin >> board[i][j];
    }
  }

  Solution obj;
  cout << (obj.isValidSudoku(board) ? "true" : "false") << "\n";

  return 0;
}