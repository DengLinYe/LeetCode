#include <iostream>
#include <queue>
#include <string>
#include <vector>

using namespace std;

struct TreeNode {
    int val;
    TreeNode* left;
    TreeNode* right;
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
};

class Solution {
   public:
    TreeNode* lowestCommonAncestor(TreeNode* root, TreeNode* p, TreeNode* q) {
        if (root == nullptr) return root;
        if (p == q) return p;

        vector<pair<TreeNode*, bool>> findStack;
        TreeNode* find = nullptr;
        bool findOne = false;
        while (root != nullptr || !findStack.empty()) {
            while (root != nullptr) {
                findStack.push_back({root, !findOne});
                find = findOne ? find : root;

                if (root == p || root == q) {
                    if (findOne) {
                        return find;
                    } else {
                        findOne = true;
                    }
                }
                root = root->left;
            }
            root = findStack.back().first;
            find = findStack.back().second ? root : find;
            findStack.pop_back();
            root = root->right;
        }

        return find;
    }
};

TreeNode* findNode(TreeNode* root, int val) {
    if (root == nullptr) return nullptr;
    if (root->val == val) return root;
    TreeNode* leftRes = findNode(root->left, val);
    if (leftRes != nullptr) return leftRes;
    return findNode(root->right, val);
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, p_val, q_val;
    if (!(cin >> n >> p_val >> q_val)) return 0;

    if (n == 0) return 0;

    vector<string> vals(n);
    for (int i = 0; i < n; i++) {
        cin >> vals[i];
    }

    TreeNode* root = new TreeNode(stoi(vals[0]));
    queue<TreeNode*> q_tree;
    q_tree.push(root);
    int i = 1;

    while (!q_tree.empty() && i < n) {
        TreeNode* curr = q_tree.front();
        q_tree.pop();

        if (i < n && vals[i] != "null") {
            curr->left = new TreeNode(stoi(vals[i]));
            q_tree.push(curr->left);
        }
        i++;

        if (i < n && vals[i] != "null") {
            curr->right = new TreeNode(stoi(vals[i]));
            q_tree.push(curr->right);
        }
        i++;
    }

    TreeNode* p = findNode(root, p_val);
    TreeNode* q = findNode(root, q_val);

    Solution obj;
    TreeNode* lca = obj.lowestCommonAncestor(root, p, q);

    if (lca != nullptr) {
        cout << lca->val << "\n";
    } else {
        cout << "null\n";
    }

    return 0;
}