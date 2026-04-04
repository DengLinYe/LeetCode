#include <algorithm>
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
   public:
    int maxDepth(TreeNode* root) { return DeepCount(root, 0); }

   private:
    int DeepCount(TreeNode* node, int depth) {
        if (node == nullptr) {
            return depth;
        } else {
            return max(DeepCount(node->left, depth + 1), DeepCount(node->right, depth + 1));
        }
    }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    if (cin >> n) {
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

            if (i < n && vals[i] != "-1") {
                curr->left = new TreeNode(stoi(vals[i]));
                q.push(curr->left);
            }
            i++;

            if (i < n && vals[i] != "-1") {
                curr->right = new TreeNode(stoi(vals[i]));
                q.push(curr->right);
            }
            i++;
        }

        Solution obj;
        cout << obj.maxDepth(root) << "\n";
    }

    return 0;
}