#include <iostream>
#include <vector>

using namespace std;

class Solution {
 public:
  vector<int> spiralOrder(vector<vector<int>>& matrix) {
    if (matrix.empty() || matrix[0].empty()) return {};

    int n = matrix.size();
    int m = matrix[0].size();
    int i = 0, j = 0, k = 0, count = 0;

    vector<vector<int>> move = {
        {0, 1, m - 1}, {1, 0, n - 1}, {0, -1, 0}, {-1, 0, 0}};
    vector<int> res;

    while (count < m * n - 1) {
      if (i * move[k][0] + j * move[k][1] <
          move[k][2] * move[k][0] + move[k][2] * move[k][1]) {
        res.push_back(matrix[i][j]);
        count++;
        i += move[k][0];
        j += move[k][1];
      } else {
        int change = (k + 3) % 4;
        move[change][2] -= move[change][0] + move[change][1];
        k = (k + 1) % 4;
      }
    }
    res.push_back(matrix[i][j]);

    return res;
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
    vector<int> res = obj.spiralOrder(matrix);

    for (size_t x = 0; x < res.size(); x++) {
      cout << res[x] << (x == res.size() - 1 ? "" : " ");
    }
    cout << "\n";
  }

  return 0;
}