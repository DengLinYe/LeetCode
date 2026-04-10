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

class BSTIterator {
   private:
    vector<TreeNode*> pre;
    TreeNode* r;
    TreeNode* interator;

   public:
    BSTIterator(TreeNode* root) {
        r = root;

        while (root != nullptr) {
            pre.push_back(root);
            root = root->left;
        }

        interator = new TreeNode(pre.back()->val - 1);
    }

    int next() {
        if (interator->right != nullptr) {
            interator = interator->right;
            while (interator->left != nullptr) {
                pre.push_back(interator);
                interator = interator->left;
            }
        } else if (!pre.empty()) {
            interator = pre.back();
            pre.pop_back();
        }

        return interator->val;
    }

    bool hasNext() {
        if (pre.empty() && interator->right == nullptr) {
            return false;
        }

        return true;
    }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int m;
    if (!(cin >> m)) return 0;

    vector<string> ops(m);
    for (int i = 0; i < m; ++i) {
        cin >> ops[i];
    }

    int n;
    if (!(cin >> n)) return 0;

    TreeNode* root = nullptr;
    if (n > 0) {
        vector<string> nodes(n);
        for (int i = 0; i < n; ++i) {
            cin >> nodes[i];
        }

        if (nodes[0] != "null") {
            root = new TreeNode(stoi(nodes[0]));
            queue<TreeNode*> q;
            q.push(root);
            int i = 1;
            while (!q.empty() && i < n) {
                TreeNode* curr = q.front();
                q.pop();
                if (i < n && nodes[i] != "null") {
                    curr->left = new TreeNode(stoi(nodes[i]));
                    q.push(curr->left);
                }
                i++;
                if (i < n && nodes[i] != "null") {
                    curr->right = new TreeNode(stoi(nodes[i]));
                    q.push(curr->right);
                }
                i++;
            }
        }
    }

    BSTIterator* obj = nullptr;

    for (int i = 0; i < m; ++i) {
        if (ops[i] == "BSTIterator") {
            obj = new BSTIterator(root);
            cout << "null ";
        } else if (ops[i] == "next") {
            cout << obj->next() << " ";
        } else if (ops[i] == "hasNext") {
            cout << (obj->hasNext() ? "true" : "false") << " ";
        }
    }
    cout << "\n";

    return 0;
}