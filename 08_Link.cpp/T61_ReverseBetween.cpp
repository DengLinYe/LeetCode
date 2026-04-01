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
    ListNode* reverseBetween(ListNode* head, int left, int right) {
        ListNode *pre = head, *base, *tail, *curr = head;
        bool rev = false;
        while (curr != nullptr) {
            ListNode* next = curr->next;
            left--;
            right--;

            if (left == 0) {
                base = curr == head ? nullptr : pre;
                tail = curr;
                rev = true;
            } else if (rev) {
                if (right >= 0) {
                    curr->next = pre;
                }
                if (right == 0) {
                    if (base != nullptr) {
                        base->next = curr;
                    } else {
                        head = curr;
                    }

                    tail->next = next;

                    break;
                }
            }

            pre = curr;
            curr = next;
        }

        return head;
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

        int left, right;
        cin >> left >> right;

        Solution obj;
        ListNode* rev = obj.reverseBetween(dummy.next, left, right);

        curr = rev;
        while (curr != nullptr) {
            cout << curr->val << " ";
            curr = curr->next;
        }
    }

    return 0;
}