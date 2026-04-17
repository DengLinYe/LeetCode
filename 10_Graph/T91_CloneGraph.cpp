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
    vector<Node*> neighbors;

    Node() {
        val = 0;
        neighbors = vector<Node*>();
    }
    Node(int _val) {
        val = _val;
        neighbors = vector<Node*>();
    }
    Node(int _val, vector<Node*> _neighbors) {
        val = _val;
        neighbors = _neighbors;
    }
};

class Solution {
   public:
    Node* cloneGraph(Node* node) {
        if (node == nullptr) return node;

        queue<Node*> neighbors;
        neighbors.push(node);
        node->val *= -1;

        unordered_map<Node*, Node*> old2new;
        while (!neighbors.empty()) {
            Node* curr = neighbors.front();
            neighbors.pop();

            Node* newCurr = new Node(-1 * curr->val);
            old2new[curr] = newCurr;

            for (auto neighbor : curr->neighbors) {
                if (neighbor->val > 0) {
                    neighbors.push(neighbor);
                    neighbor->val *= -1;
                }
            }
        }

        neighbors.push(node);
        node->val *= -1;
        while (!neighbors.empty()) {
            Node* curr = neighbors.front();
            neighbors.pop();

            for (auto neighbor : curr->neighbors) {
                old2new[curr]->neighbors.push_back(old2new[neighbor]);

                if (neighbor->val < 0) {
                    neighbors.push(neighbor);
                    neighbor->val *= -1;
                }
            }
        }

        return old2new[node];
    }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;
    if (n == 0) return 0;

    vector<Node*> nodes(n);
    for (int i = 0; i < n; i++) {
        nodes[i] = new Node(i + 1);
    }

    for (int i = 0; i < n; i++) {
        int m;
        cin >> m;

        for (int j = 0; j < m; j++) {
            int index;
            cin >> index;

            nodes[i]->neighbors.push_back(nodes[index - 1]);
        }
    }

    Solution obj;
    Node* first = obj.cloneGraph(nodes[0]);

    queue<Node*> neighbors;
    neighbors.push(first);
    first->val *= -1;

    while (!neighbors.empty()) {
        Node* curr = neighbors.front();
        neighbors.pop();

        cout << -1 * curr->val << " ";

        for (auto node : curr->neighbors) {
            if (node->val > 0) {
                neighbors.push(node);
                node->val *= -1;
            }
        }
    }

    return 0;
}