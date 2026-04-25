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
   private:
    void buildTree(TreeNode* root, vector<int>& nums, int i, int j) {
        int mid = (i + j) / 2;
        root->val = nums[mid];

        if (mid > i) {
            root->left = new TreeNode();
            buildTree(root->left, nums, i, mid - 1);
        }
        if (mid < j) {
            root->right = new TreeNode();
            buildTree(root->right, nums, mid + 1, j);
        }
    }

   public:
    TreeNode* sortedArrayToBST(vector<int>& nums) {
        TreeNode* root = new TreeNode();
        buildTree(root, nums, 0, nums.size() - 1);
        return root;
    }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;

    vector<int> nums(n);
    for (int i = 0; i < n; i++) {
        cin >> nums[i];
    }

    Solution obj;
    TreeNode* root = obj.sortedArrayToBST(nums);
    queue<TreeNode*> q;
    q.push(root);

    while (!q.empty()) {
        TreeNode* curr = q.front();
        q.pop();

        cout << curr->val << " ";
        if (curr->left != nullptr) {
            q.push(curr->left);
        }
        if (curr->right != nullptr) {
            q.push(curr->right);
        }
    }

    return 0;
}