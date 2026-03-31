#include <iostream>
#include <unordered_map>
#include <vector>

using namespace std;

class Node {
   public:
    int val;
    Node* next;
    Node* random;

    Node(int _val) {
        val = _val;
        next = nullptr;
        random = nullptr;
    }
};

class Solution {
   public:
    Node* copyRandomList(Node* head) {
        if (head == nullptr) return head;

        unordered_map<Node*, Node*> o2n;
        Node dummy(0);
        Node *curr = &dummy, *oldCurr = head;

        while (oldCurr != nullptr) {
            curr->next = new Node(oldCurr->val);
            o2n[oldCurr] = curr->next;
            curr = curr->next;
            oldCurr = oldCurr->next;
        }

        curr = dummy.next;
        oldCurr = head;
        while (oldCurr != nullptr) {
            curr->random = o2n[oldCurr->random];
            curr = curr->next;
            oldCurr = oldCurr->next;
        }

        return dummy.next;
    }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    if (cin >> n) {
        if (n == 0) {
            cout << "[]\n";
            return 0;
        }

        vector<Node*> originalNodes(n);
        vector<int> randomIndices(n);

        for (int i = 0; i < n; i++) {
            int val, randomIndex;
            cin >> val >> randomIndex;
            originalNodes[i] = new Node(val);
            randomIndices[i] = randomIndex;
        }

        for (int i = 0; i < n - 1; i++) {
            originalNodes[i]->next = originalNodes[i + 1];
        }

        for (int i = 0; i < n; i++) {
            if (randomIndices[i] != -1) {
                originalNodes[i]->random = originalNodes[randomIndices[i]];
            }
        }

        Solution obj;
        Node* copiedHead = obj.copyRandomList(originalNodes[0]);

        Node* temp = copiedHead;
        unordered_map<Node*, int> nodeToIndex;
        int idx = 0;
        while (temp != nullptr) {
            nodeToIndex[temp] = idx++;
            temp = temp->next;
        }

        temp = copiedHead;
        cout << "[";
        while (temp != nullptr) {
            cout << "[" << temp->val << ",";
            if (temp->random == nullptr) {
                cout << "null]";
            } else {
                cout << nodeToIndex[temp->random] << "]";
            }
            if (temp->next != nullptr) cout << ",";
            temp = temp->next;
        }
        cout << "]\n";
    }

    return 0;
}