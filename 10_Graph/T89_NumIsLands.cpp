#include <iostream>
#include <vector>

using namespace std;

class Solution {
   public:
    int numIslands(vector<vector<char>>& grid) {
        int n = grid.size(), m = grid[0].size(), sum = 0;

        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {
                if (grid[i][j] == '1') {
                    // cout<<i <<" "<< j <<endl;
                    sum++;
                    DFS(grid, i, j);
                    // cout<<endl;
                }
            }
        }
        // cout<<endl;

        return sum;
    }

   private:
    void DFS(vector<vector<char>>& grid, int i, int j) {
        // cout<<i <<" "<< j <<endl;

        grid[i][j] = '0';

        if (i - 1 >= 0 && grid[i - 1][j] == '1') DFS(grid, i - 1, j);
        if (j - 1 >= 0 && grid[i][j - 1] == '1') DFS(grid, i, j - 1);
        if (i + 1 < grid.size() && grid[i + 1][j] == '1') DFS(grid, i + 1, j);
        if (j + 1 < grid[0].size() && grid[i][j + 1] == '1') DFS(grid, i, j + 1);
    }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m;
    if (!(cin >> n >> m)) return 0;
    if (n == 0 || m == 0) {
        cout << 0 << "\n";
        return 0;
    }

    vector<vector<char>> grid(n, vector<char>(m));
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            cin >> grid[i][j];
        }
    }

    Solution obj;
    cout << obj.numIslands(grid) << "\n";

    return 0;
}