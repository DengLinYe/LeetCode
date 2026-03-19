#include <iostream>
#include <vector>

using namespace std;

class Solution {
 public:
  void rotate(vector<vector<int>>& matrix) {
    int n = matrix.size();
    for (int i = n - 1; i >= n / 2; i--) {
      int layer = n - 1 - i;
      for (int j = 0; j < i - layer; j++) {
        int temp = matrix[layer][layer + j];
        matrix[layer][layer + j] = matrix[i - j][layer];
        matrix[i - j][layer] = matrix[i][i - j];
        matrix[i][i - j] = matrix[layer + j][i];
        matrix[layer + j][i] = temp;
      }
    }
  }
};

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  int n;
  if (cin >> n) {
    vector<vector<int>> matrix(n, vector<int>(n));
    for (int i = 0; i < n; i++) {
      for (int j = 0; j < n; j++) {
        cin >> matrix[i][j];
      }
    }

    Solution obj;
    obj.rotate(matrix);

    for (int i = 0; i < n; i++) {
      for (int j = 0; j < n; j++) {
        cout << matrix[i][j] << (j == n - 1 ? "" : " ");
      }
      cout << "\n";
    }
  }

  return 0;
}