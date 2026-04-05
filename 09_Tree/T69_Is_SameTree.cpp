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
    bool isSameTree(TreeNode* p, TreeNode* q) {
        if (p == nullptr && q == nullptr) {
            return true;
        } else if (p == nullptr || q == nullptr) {
            return false;
        } else if (p->val != q->val) {
            return false;
        } else {
            return isSameTree(p->left, q->left) && isSameTree(p->right, q->right);
        }
    }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m;
    if (!(cin >> n >> m)) return 0;

    if (n == 0 && m == 0) {
        cout << "true\n";
        return 0;
    }

    vector<string> pNum(n), qNum(m);
    for (int i = 0; i < n; i++) cin >> pNum[i];
    for (int i = 0; i < m; i++) cin >> qNum[i];

    TreeNode* pRoot = n > 0 ? new TreeNode(stoi(pNum[0])) : nullptr;
    TreeNode* qRoot = m > 0 ? new TreeNode(stoi(qNum[0])) : nullptr;

    if (pRoot != nullptr) {
        queue<TreeNode*> p;
        p.push(pRoot);
        int i = 1;
        while (!p.empty() && i < n) {
            TreeNode* curr = p.front();
            p.pop();
            if (i < n && pNum[i] != "-1") {
                curr->left = new TreeNode(stoi(pNum[i]));
                p.push(curr->left);
            }
            i++;
            if (i < n && pNum[i] != "-1") {
                curr->right = new TreeNode(stoi(pNum[i]));
                p.push(curr->right);
            }
            i++;
        }
    }

    if (qRoot != nullptr) {
        queue<TreeNode*> q;
        q.push(qRoot);
        int i = 1;
        while (!q.empty() && i < m) {
            TreeNode* curr = q.front();
            q.pop();
            if (i < m && qNum[i] != "-1") {
                curr->left = new TreeNode(stoi(qNum[i]));
                q.push(curr->left);
            }
            i++;
            if (i < m && qNum[i] != "-1") {
                curr->right = new TreeNode(stoi(qNum[i]));
                q.push(curr->right);
            }
            i++;
        }
    }

    Solution obj;
    cout << (obj.isSameTree(pRoot, qRoot) ? "true" : "false") << "\n";

    return 0;
}