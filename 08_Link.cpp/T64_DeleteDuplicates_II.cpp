#include <algorithm>
#include <iostream>
#include <queue>
#include <string>
#include <unordered_map>
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
    ListNode* deleteDuplicates(ListNode* head) {
        if (head == nullptr) return head;

        ListNode dummy(0);
        dummy.next = head;
        ListNode *pre = &dummy, *curr = head->next;

        while (curr != nullptr) {
            int nowVal = pre->next->val;
            if (curr->val == nowVal) {
                while (curr != nullptr && curr->val == nowVal) {
                    pre->next = curr->next;
                    curr = curr->next;
                }
                if (curr == nullptr || curr->next == nullptr) {
                    break;
                }
                curr = curr->next;
            } else {
                pre = pre->next;
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
    while (cin >> n) {
        ListNode dummy(0);
        ListNode* curr = &dummy;

        for (int i = 0; i < n; i++) {
            int val;
            cin >> val;

            curr->next = new ListNode(val);
            curr = curr->next;
        }

        Solution obj;
        ListNode* head = obj.deleteDuplicates(dummy.next);

        curr = head;
        while (curr != nullptr) {
            cout << curr->val << " ";

            curr = curr->next;
        }
    }

    return 0;
}