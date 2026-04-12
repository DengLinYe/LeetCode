#include <algorithm>
#include <iomanip>
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
    vector<double> averageOfLevels(TreeNode* root) {
        vector<double> avg;
        if (root == nullptr) return avg;

        queue<TreeNode*> layer;
        layer.push(root);

        while (!layer.empty()) {
            int layerSize = layer.size();
            double sum = 0;

            for (int i = 0; i < layerSize; i++) {
                TreeNode* curr = layer.front();
                layer.pop();

                sum += curr->val;

                if (curr->left) layer.push(curr->left);
                if (curr->right) layer.push(curr->right);
            }
            avg.push_back(sum / layerSize);
        }

        return avg;
    }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    if (!(cin >> n)) return 0;

    if (n == 0) {
        cout << "\n";
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
    vector<double> res = obj.averageOfLevels(root);

    cout << fixed << setprecision(5);
    for (double avg : res) {
        cout << avg << " ";
    }
    cout << "\n";

    return 0;
}