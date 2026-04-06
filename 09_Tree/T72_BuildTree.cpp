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
    TreeNode* buildTree(vector<int>& preorder, vector<int>& inorder) {
        TreeNode* root = new TreeNode();
        buildSubTree(root, preorder, inorder);

        return root;
    }

   private:
    void buildSubTree(TreeNode* root, vector<int>& preorder, vector<int>& inorder) {
        root->val = preorder[0];
        auto mid = find(inorder.begin(), inorder.end(), preorder[0]);
        int midIndex = distance(inorder.begin(), mid);

        if (mid != inorder.begin()) {
            root->left = new TreeNode();
            vector<int> preLeftSub(preorder.begin() + 1, preorder.begin() + 1 + midIndex);
            vector<int> inLeftSub(inorder.begin(), mid);
            buildSubTree(root->left, preLeftSub, inLeftSub);
        }
        if (mid != inorder.end() - 1) {
            root->right = new TreeNode();
            vector<int> preRightSub(preorder.begin() + 1 + midIndex, preorder.end());
            vector<int> inRightSub(mid + 1, inorder.end());
            buildSubTree(root->right, preRightSub, inRightSub);
        }
    }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;

    vector<int> preorder(n), inorder(n);
    for (int i = 0; i < n; i++) {
        cin >> preorder[i];
    }
    for (int i = 0; i < n; i++) {
        cin >> inorder[i];
    }

    Solution obj;
    TreeNode* root = obj.buildTree(preorder, inorder);
    queue<TreeNode*> q;
    q.push(root);
    cout << root->val << " ";

    while (!q.empty()) {
        TreeNode* curr = q.front();
        q.pop();

        if (curr->left != nullptr) {
            cout << curr->left->val << " ";
            q.push(curr->left);
        } else {
            cout << "null ";
        }

        if (curr->right != nullptr) {
            cout << curr->right->val << " ";
            q.push(curr->right);
        } else {
            cout << "null ";
        }
    }

    return 0;
}