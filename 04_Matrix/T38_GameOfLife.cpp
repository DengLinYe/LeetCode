#include <algorithm>
#include <iostream>
#include <queue>
#include <string>
#include <unordered_map>
#include <vector>

using namespace std;

class Solution {
 public:
  void gameOfLife(vector<vector<int>>& board) {
    int m = board[0].size(), n = board.size();
    vector<vector<int>> nextState(n, vector<int>(m));

    for (int i = 0; i < n; i++) {
      for (int j = 0; j < m; j++) {
        if (board[i][j] == 1) {
          nextState[i][j] += board[i][j];
          if (i > 0) {
            nextState[i - 1][j]++;
          }
          if (j > 0) {
            nextState[i][j - 1]++;
          }
          if (i < n - 1) {
            nextState[i + 1][j]++;
          }
          if (j < m - 1) {
            nextState[i][j + 1]++;
          }
          if (i > 0 && j > 0) {
            nextState[i - 1][j - 1]++;
          }
          if (i > 0 && j < m - 1) {
            nextState[i - 1][j + 1]++;
          }
          if (i < n - 1 && j > 0) {
            nextState[i + 1][j - 1]++;
          }
          if (i < n - 1 && j < m - 1) {
            nextState[i + 1][j + 1]++;
          }
        }
      }
    }

    for (int i = 0; i < n; i++) {
      for (int j = 0; j < m; j++) {
        if (board[i][j] == 0) {
          if (nextState[i][j] == 3) board[i][j] = 1;
        } else {
          if (nextState[i][j] > 4 || nextState[i][j] < 3) board[i][j] = 0;
        }
      }
    }
  }
};

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  int m, n;
  cin >> m >> n;

  vector<vector<int>> matrix(n, vector<int>(m));
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < m; j++) {
      cin >> matrix[i][j];
    }
  }

  Solution obj;
  obj.gameOfLife(matrix);

  for (vector<int> r : matrix) {
    for (int c : r) {
      cout << c << " ";
    }
    cout << endl;
  }

  return 0;
}