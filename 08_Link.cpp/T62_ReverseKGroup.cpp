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
    ListNode* reverseKGroup(ListNode* head, int k) {
        ListNode dummy(0);
        dummy.next = head;

        ListNode *curr = dummy.next, *base = dummy.next, *pre = &dummy;
        int kGroup = k;

        while (curr != nullptr) {
            ListNode* nextIndex = curr->next;
            k--;

            if (k == 0) {
                k = kGroup;
                ListNode* currTemp = pre->next;

                while (base->next != nextIndex) {
                    ListNode* nextTemp = base->next;
                    base->next = nextTemp->next;
                    nextTemp->next = pre->next;
                    pre->next = nextTemp;
                }

                pre = currTemp;
                base = nextIndex;
            }

            curr = nextIndex;
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

        int k;
        cin >> k;

        Solution obj;
        ListNode* rev = obj.reverseKGroup(dummy.next, k);

        curr = rev;
        while (curr != nullptr) {
            cout << curr->val << " ";
            curr = curr->next;
        }
    }

    return 0;
}