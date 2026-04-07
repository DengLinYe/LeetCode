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
    unordered_map<int, int> index;

    TreeNode* buildSubTree(const vector<int>& postorder, int inLeft, int inRight, int postLeft, int postRight) {
        if (postLeft > postRight) return nullptr;

        int rootVal = postorder[postRight];
        TreeNode* root = new TreeNode(rootVal);

        int inRootIndex = index[rootVal];
        int leftSize = inRootIndex - inLeft;

        root->left = buildSubTree(postorder, inLeft, inRootIndex - 1, postLeft, postLeft + leftSize - 1);
        root->right = buildSubTree(postorder, inRootIndex + 1, inRight, postLeft + leftSize, postRight - 1);

        return root;
    }

   public:
    TreeNode* buildTree(vector<int>& inorder, vector<int>& postorder) {
        int n = inorder.size();
        for (int i = 0; i < n; i++) {
            index[inorder[i]] = i;
        }
        return buildSubTree(postorder, 0, n - 1, 0, n - 1);
    }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;

    vector<int> inorder(n), postorder(n);
    for (int i = 0; i < n; i++) {
        cin >> inorder[i];
    }
    for (int i = 0; i < n; i++) {
        cin >> postorder[i];
    }

    Solution obj;
    TreeNode* root = obj.buildTree(inorder, postorder);
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