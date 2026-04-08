#include <algorithm>
#include <iostream>
#include <queue>
#include <string>
#include <unordered_map>
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
    void flatten(TreeNode* root) { subFlatten(root); }

   private:
    TreeNode* subFlatten(TreeNode* root) {
        if (root == nullptr) return root;

        TreeNode *right = subFlatten(root->right), *subRight = subFlatten(root->left);
        if (subRight != nullptr) {
            TreeNode* oldRight = root->right;
            root->right = root->left;
            subRight->right = oldRight;
            root->left = nullptr;

            if (right == nullptr) {
                right = subRight;
            }
        } else if (right == nullptr) {
            right = root;
        }

        return right;
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

        if (i < n && nums[i] != "null") {
            curr->left = new TreeNode(stoi(nums[i]));
            q.push(curr->left);
        }
        i++;

        if (i < n && nums[i] != "null") {
            curr->right = new TreeNode(stoi(nums[i]));
            q.push(curr->right);
        }
        i++;
    }

    Solution obj;
    obj.flatten(root);

    queue<TreeNode*> outQ;
    if (root != nullptr) {
        outQ.push(root);
        cout << root->val << " ";
    }

    while (!outQ.empty()) {
        TreeNode* curr = outQ.front();
        outQ.pop();

        if (curr->left != nullptr) {
            outQ.push(curr->left);
            cout << curr->left->val << " ";
        } else {
            cout << "null ";
        }
        if (curr->right != nullptr) {
            outQ.push(curr->right);
            cout << curr->right->val << " ";
        } else {
            cout << "null ";
        }
    }
    cout << "\n";

    return 0;
}