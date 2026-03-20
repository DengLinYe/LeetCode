#include <iostream>
#include <vector>

using namespace std;

class Solution {
 public:
  void setZeroes(vector<vector<int>>& matrix) {
    int n = matrix.size();
    int m = matrix[0].size();
    vector<int> rowZero(n, 1);
    vector<int> colZero(m, 1);

    for (int i = 0; i < n; i++) {
      for (int j = 0; j < m; j++) {
        if (matrix[i][j] == 0) {
          rowZero[i] = 0;
          colZero[j] = 0;
        }
      }
    }

    for (int i = 0; i < n; i++) {
      for (int j = 0; j < m; j++) {
        if (rowZero[i] == 0 || colZero[j] == 0) {
          matrix[i][j] = 0;
        }
      }
    }
  }
};

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  int n, m;
  if (cin >> n >> m) {
    vector<vector<int>> matrix(n, vector<int>(m));
    for (int i = 0; i < n; i++) {
      for (int j = 0; j < m; j++) {
        cin >> matrix[i][j];
      }
    }

    Solution obj;
    obj.setZeroes(matrix);

    for (int i = 0; i < n; i++) {
      for (int j = 0; j < m; j++) {
        cout << matrix[i][j] << (j == m - 1 ? "" : " ");
      }
      cout << "\n";
    }
  }

  return 0;
}