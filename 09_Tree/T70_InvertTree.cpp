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
    TreeNode* invertTree(TreeNode* root) {
        if (root == nullptr) {
            return root;
        } else {
            TreeNode* temp = root->left;
            root->left = root->right;
            root->right = temp;
            invertTree(root->right);
            invertTree(root->left);
        }

        return root;
    }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    if (!(cin >> n)) return 0;
    if (n == 0) return 0;

    vector<string> nums(n);
    for (int i = 0; i < n; i++) {
        cin >> nums[i];
    }

    TreeNode* root = new TreeNode(stoi(nums[0]));
    queue<TreeNode*> q;
    q.push(root);
    int i = 1;

    while (!q.empty() && i < n) {
        TreeNode* curr = q.front();
        q.pop();

        if (i < n && nums[i] != "-1") {
            curr->left = new TreeNode(stoi(nums[i]));
            q.push(curr->left);
        }
        i++;

        if (i < n && nums[i] != "-1") {
            curr->right = new TreeNode(stoi(nums[i]));
            q.push(curr->right);
        }
        i++;
    }

    Solution obj;
    root = obj.invertTree(root);

    queue<TreeNode*> outQ;
    if (root != nullptr) {
        outQ.push(root);
    }

    while (!outQ.empty()) {
        TreeNode* curr = outQ.front();
        outQ.pop();

        cout << curr->val << " ";

        if (curr->left != nullptr) {
            outQ.push(curr->left);
        }
        if (curr->right != nullptr) {
            outQ.push(curr->right);
        }
    }
    cout << "\n";

    return 0;
}