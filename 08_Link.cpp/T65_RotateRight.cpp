#include <iostream>

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
    ListNode* rotateRight(ListNode* head, int k) {
        if (head == nullptr) return head;

        ListNode dummy(0);
        dummy.next = head;
        ListNode *slow = &dummy, *fast = &dummy;
        int n = 0;

        while (fast->next != nullptr) {
            n++;
            fast = fast->next;
        }

        k = k % n;
        if (k == 0) return head;

        fast = &dummy;
        for (int i = 0; i < k; i++) {
            fast = fast->next;
        }

        while (fast->next != nullptr) {
            fast = fast->next;
            slow = slow->next;
        }

        fast->next = dummy.next;
        dummy.next = slow->next;
        slow->next = nullptr;

        return dummy.next;
    }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    if (cin >> n) {
        if (n == 0) {
            cout << "\n";
            return 0;
        }
        ListNode dummy(0);
        ListNode* curr = &dummy;
        for (int i = 0; i < n; i++) {
            int val;
            cin >> val;
            curr->next = new ListNode(val);
            curr = curr->next;
        }
        int k;
        cin >> k;

        Solution obj;
        ListNode* res = obj.rotateRight(dummy.next, k);

        while (res != nullptr) {
            cout << res->val << " ";
            res = res->next;
        }
        cout << "\n";
    }

    return 0;
}