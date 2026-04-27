#include <iostream>
#include <queue>
#include <string>
#include <vector>

using namespace std;

class Node {
   public:
    bool val;
    bool isLeaf;
    Node* topLeft;
    Node* topRight;
    Node* bottomLeft;
    Node* bottomRight;

    Node() {
        val = false;
        isLeaf = false;
        topLeft = nullptr;
        topRight = nullptr;
        bottomLeft = nullptr;
        bottomRight = nullptr;
    }

    Node(bool _val, bool _isLeaf) {
        val = _val;
        isLeaf = _isLeaf;
        topLeft = nullptr;
        topRight = nullptr;
        bottomLeft = nullptr;
        bottomRight = nullptr;
    }

    Node(bool _val, bool _isLeaf, Node* _topLeft, Node* _topRight, Node* _bottomLeft, Node* _bottomRight) {
        val = _val;
        isLeaf = _isLeaf;
        topLeft = _topLeft;
        topRight = _topRight;
        bottomLeft = _bottomLeft;
        bottomRight = _bottomRight;
    }
};

class Solution {
   private:
    Node* buildTree(vector<vector<int>>& grid, int upI, int upJ, int downI, int downJ) {
        if (upI == downI && upJ == downJ) {
            return new Node(grid[upI][upJ] == 1, true);
        }

        int midI = upI + (downI - upI) / 2;
        int midJ = upJ + (downJ - upJ) / 2;

        Node* topLeft = buildTree(grid, upI, upJ, midI, midJ);
        Node* topRight = buildTree(grid, upI, midJ + 1, midI, downJ);
        Node* bottomLeft = buildTree(grid, midI + 1, upJ, downI, midJ);
        Node* bottomRight = buildTree(grid, midI + 1, midJ + 1, downI, downJ);

        if (topLeft->isLeaf && topRight->isLeaf && bottomLeft->isLeaf && bottomRight->isLeaf &&
            topLeft->val == topRight->val && topLeft->val == bottomLeft->val && topLeft->val == bottomRight->val) {
            bool mergedVal = topLeft->val;
            delete topLeft;
            delete topRight;
            delete bottomLeft;
            delete bottomRight;
            return new Node(mergedVal, true);
        }

        return new Node(true, false, topLeft, topRight, bottomLeft, bottomRight);
    }

   public:
    Node* construct(vector<vector<int>>& grid) { return buildTree(grid, 0, 0, grid.size() - 1, grid[0].size() - 1); }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    if (!(cin >> n)) return 0;

    vector<vector<int>> grid(n, vector<int>(n));
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            cin >> grid[i][j];
        }
    }

    Solution obj;
    Node* root = obj.construct(grid);

    if (!root) return 0;

    queue<Node*> q;
    q.push(root);
    cout << "[";

    bool first = true;
    while (!q.empty()) {
        Node* curr = q.front();
        q.pop();

        if (!first) cout << ",";
        first = false;

        if (curr == nullptr) {
            cout << "null";
        } else {
            cout << "[" << (curr->isLeaf ? "1" : "0") << "," << (curr->val ? "1" : "0") << "]";
            if (!curr->isLeaf) {
                q.push(curr->topLeft);
                q.push(curr->topRight);
                q.push(curr->bottomLeft);
                q.push(curr->bottomRight);
            }
        }
    }
    cout << "]" << "\n";

    return 0;
}