#include <iostream>
#include <vector>

using namespace std;

struct ListNode {
    int val;
    ListNode* next;
    ListNode(int x) : val(x), next(NULL) {}
};

class Solution {
   public:
    bool hasCycle(ListNode* head) {
        if (head == NULL || head->next == NULL) return false;
        ListNode *fast = head->next, *slow = head;
        while (fast != NULL && fast->next != NULL) {
            if (fast == slow) {
                return true;
            }
            fast = fast->next->next;
            slow = slow->next;
        }

        return false;
    }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    if (cin >> n) {
        if (n == 0) {
            cout << "false\n";
            return 0;
        }

        vector<ListNode*> nodes;
        for (int i = 0; i < n; i++) {
            int val;
            cin >> val;
            nodes.push_back(new ListNode(val));
        }

        for (int i = 0; i < n - 1; i++) {
            nodes[i]->next = nodes[i + 1];
        }

        int pos;
        cin >> pos;
        if (pos >= 0 && pos < n) {
            nodes[n - 1]->next = nodes[pos];
        }

        Solution obj;
        cout << (obj.hasCycle(nodes[0]) ? "true" : "false") << "\n";
    }

    return 0;
}