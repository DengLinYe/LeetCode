#include <algorithm>
#include <iostream>
#include <queue>
#include <string>
#include <unordered_map>
#include <vector>

using namespace std;

class Node {
   public:
    int val;
    Node* left;
    Node* right;
    Node* next;

    Node() : val(0), left(NULL), right(NULL), next(NULL) {}

    Node(int _val) : val(_val), left(NULL), right(NULL), next(NULL) {}

    Node(int _val, Node* _left, Node* _right, Node* _next) : val(_val), left(_left), right(_right), next(_next) {}
};

class Solution {
   public:
    Node* connect(Node* root) {
        if (root == nullptr) return root;

        Node *base = root, *curr = nullptr, *start = nullptr;
        while (base != nullptr || start != nullptr) {
            if (base == nullptr) {
                base = start;
                start = nullptr;
                curr = nullptr;
            }
            if (start == nullptr) {
                start = base->left != nullptr ? base->left : (base->right != nullptr ? base->right : nullptr);
                curr = start;
                if (curr != nullptr && curr == base->left) {
                    curr->next = base->right;
                    if (curr->next != nullptr) curr = curr->next;
                }
            } else {
                curr->next = base->left;
                if (curr->next != nullptr) curr = curr->next;
                curr->next = base->right;
                if (curr->next != nullptr) curr = curr->next;
            }

            base = base->next;
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

    Node* root = new Node(stoi(nums[0]));
    queue<Node*> q;
    q.push(root);
    int i = 1;

    while (!q.empty() && i < n) {
        Node* curr = q.front();
        q.pop();

        if (i < n && nums[i] != "null") {
            curr->left = new Node(stoi(nums[i]));
            q.push(curr->left);
        }
        i++;

        if (i < n && nums[i] != "null") {
            curr->right = new Node(stoi(nums[i]));
            q.push(curr->right);
        }
        i++;
    }

    Solution obj;
    root = obj.connect(root);

    Node *start = nullptr, *curr = root;
    while (start != nullptr || curr != nullptr) {
        if (curr == nullptr) {
            cout << "# ";
            curr = start;
            start = nullptr;
        }
        if (start == nullptr) {
            start = curr->left;
        }
        if (start == nullptr) {
            start = curr->right;
        }
        cout << curr->val << " ";
        curr = curr->next;
    }
    cout << "#";

    return 0;
}