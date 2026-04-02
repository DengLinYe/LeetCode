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
    ListNode* removeNthFromEnd(ListNode* head, int n) {
        ListNode dummy(0);
        dummy.next = head;
        ListNode *curr = &dummy, *preN = &dummy;
        int count = 0;

        while (curr != nullptr) {
            if (count < n) {
                count++;
                curr = curr->next;
            } else {
                if (curr->next == nullptr) {
                    break;
                }
                curr = curr->next;
                preN = preN->next;
            }
        }

        preN->next = preN->next->next;

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

        int k;
        cin >> k;

        Solution obj;
        ListNode* head = obj.removeNthFromEnd(dummy.next, k);

        curr = head;
        while (curr != nullptr) {
            cout << curr->val << " ";

            curr = curr->next;
        }
    }

    return 0;
}