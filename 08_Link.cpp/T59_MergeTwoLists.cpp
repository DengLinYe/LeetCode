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
    ListNode* mergeTwoLists(ListNode* list1, ListNode* list2) {
        if (list1 == nullptr) return list2;
        if (list2 == nullptr) return list1;

        ListNode *base, *cur, *pre;
        bool flag = false;
        if (list2->val > list1->val) {
            base = list1;
            cur = list2;
            flag = true;
        } else {
            base = list2;
            cur = list1;
        }
        pre = base;
        while (cur != nullptr) {
            while (cur->val >= base->val) {
                if (base->next == nullptr) {
                    base->next = cur;
                    return flag ? list1 : list2;
                }
                pre = base;
                base = base->next;
            }
            ListNode* temp = base;
            pre->next = cur;
            cur = cur->next;
            pre->next->next = temp;
            pre = pre->next;
        }

        return flag ? list1 : list2;
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
        ListNode* res = obj.mergeTwoLists(dummy1.next, dummy2.next);

        while (res != nullptr) {
            cout << res->val << " ";
            res = res->next;
        }
        cout << "\n";
    }

    return 0;
}