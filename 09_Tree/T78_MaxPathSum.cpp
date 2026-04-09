#include <algorithm>
#include <climits>  // 引入 INT_MIN
#include <iostream>
#include <queue>
#include <string>
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
   private:
    int maxSum = INT_MIN;

    int subNodeSelect(TreeNode* root) {
        if (root == nullptr) return 0;

        int left = max(subNodeSelect(root->left), 0);
        int right = max(subNodeSelect(root->right), 0);

        int nowSum = root->val + left + right;
        maxSum = max(maxSum, nowSum);

        return root->val + max(left, right);
    }

   public:
    int maxPathSum(TreeNode* root) {
        maxSum = INT_MIN;
        subNodeSelect(root);
        return maxSum;
    }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    if (!(cin >> n)) return 0;
    if (n == 0) {
        cout << 0 << "\n";
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
    cout << obj.maxPathSum(root) << "\n";

    return 0;
}