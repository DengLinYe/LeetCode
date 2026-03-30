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
    ListNode* addTwoNumbers(ListNode* l1, ListNode* l2) {
        ListNode* result = new ListNode();
        ListNode *l1Cur = l1, *l2Cur = l2, *resCur = result;
        bool st = true;
        int c = 0;

        while (l1Cur != nullptr || l2Cur != nullptr) {
            int sum = c;
            if (l1Cur != nullptr && l2Cur != nullptr) {
                sum += l1Cur->val + l2Cur->val;
                l1Cur = l1Cur->next;
                l2Cur = l2Cur->next;
            } else if (l1Cur == nullptr) {
                sum += l2Cur->val;
                l2Cur = l2Cur->next;
            } else {
                sum += l1Cur->val;
                l1Cur = l1Cur->next;
            }

            c = sum / 10;

            if (st) {
                resCur->val = sum % 10;
                st = false;
            } else {
                resCur->next = new ListNode(sum % 10);
                resCur = resCur->next;
            }
        }

        if (c > 0) {
            resCur->next = new ListNode(c);
        }

        return result;
    }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m;
    if (cin >> n >> m) {
        ListNode dummy1(0), dummy2(0);
        ListNode *cur1 = &dummy1, *cur2 = &dummy2;

        for (int i = 0; i < n; i++) {
            int val;
            cin >> val;
            cur1->next = new ListNode(val);
            cur1 = cur1->next;
        }

        for (int i = 0; i < m; i++) {
            int val;
            cin >> val;
            cur2->next = new ListNode(val);
            cur2 = cur2->next;
        }

        Solution obj;
        ListNode* res = obj.addTwoNumbers(dummy1.next, dummy2.next);

        while (res != nullptr) {
            cout << res->val << " ";
            res = res->next;
        }
        cout << "\n";
    }

    return 0;
}