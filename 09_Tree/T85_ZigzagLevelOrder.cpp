#include <algorithm>
#include <iostream>
#include <queue>
#include <string>
#include <utility>
#include <vector>

using namespace std;

struct TreeNode {
    int val;
    TreeNode* left;
    TreeNode* right;
    TreeNode() : val(0), left(nullptr), right(nullptr) {}
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
    TreeNode(int x, TreeNode* left, TreeNode* right) : val(x), left(left), right(right) {}
};

class Solution {
   public:
    vector<vector<int>> zigzagLevelOrder(TreeNode* root) {
        if (root == nullptr) return {};

        bool ward = true;
        vector<vector<int>> res;
        queue<TreeNode*> q;
        q.push(root);

        while (!q.empty()) {
            int layerSize = q.size();
            vector<int> layer(layerSize);

            for (int i = 0; i < layerSize; i++) {
                TreeNode* curr = q.front();
                q.pop();

                int index = ward ? i : layerSize - 1 - i;
                layer[index] = curr->val;

                if (curr->left != nullptr) q.push(curr->left);
                if (curr->right != nullptr) q.push(curr->right);
            }

            res.push_back(std::move(layer));
            ward = !ward;
        }

        return res;
    }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    if (!(cin >> n)) return 0;

    if (n == 0) {
        cout << "[]\n";
        return 0;
    }

    vector<string> vals(n);
    for (int i = 0; i < n; i++) {
        cin >> vals[i];
    }

    TreeNode* root = new TreeNode(stoi(vals[0]));
    queue<TreeNode*> q;
    q.push(root);
    int i = 1;

    while (!q.empty() && i < n) {
        TreeNode* curr = q.front();
        q.pop();

        if (i < n && vals[i] != "null") {
            curr->left = new TreeNode(stoi(vals[i]));
            q.push(curr->left);
        }
        i++;

        if (i < n && vals[i] != "null") {
            curr->right = new TreeNode(stoi(vals[i]));
            q.push(curr->right);
        }
        i++;
    }

    Solution obj;
    vector<vector<int>> res = obj.zigzagLevelOrder(root);

    cout << "[";
    for (size_t r = 0; r < res.size(); ++r) {
        cout << "[";
        for (size_t c = 0; c < res[r].size(); ++c) {
            cout << res[r][c];
            if (c < res[r].size() - 1) cout << ",";
        }
        cout << "]";
        if (r < res.size() - 1) cout << ",";
    }
    cout << "]\n";

    return 0;
}