#include <iostream>
#include <vector>

using namespace std;

struct ListNode {
    int val;
    ListNode* next;
    ListNode() : val(0), next(nullptr) {}
    ListNode(int x) : val(x), next(nullptr) {}
    ListNode(int x, ListNode* next) : val(x), next(next) {}
};

class Solution {
   public:
    ListNode* partition(ListNode* head, int x) {
        if (head == nullptr) return head;

        ListNode dummy(0);
        dummy.next = head;
        ListNode *curr = &dummy, *pre = &dummy;

        while (curr->next != nullptr && curr == pre && curr->next->val < x) {
            pre = pre->next;
            curr = curr->next;
        }

        while (curr != nullptr && curr->next != nullptr) {
            if (curr->next->val < x) {
                ListNode* temp = curr->next;
                curr->next = temp->next;
                temp->next = pre->next;
                pre->next = temp;
                pre = pre->next;
            } else {
                curr = curr->next;
            }
        }

        return dummy.next;
    }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    if (cin >> n) {
        ListNode dummy(0);
        ListNode* curr = &dummy;

        for (int i = 0; i < n; i++) {
            int val;
            cin >> val;
            curr->next = new ListNode(val);
            curr = curr->next;
        }

        int x;
        cin >> x;

        Solution obj;
        ListNode* res = obj.partition(dummy.next, x);

        while (res != nullptr) {
            cout << res->val << " ";
            res = res->next;
        }
        cout << "\n";
    }

    return 0;
}