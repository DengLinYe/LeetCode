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
   private:
    ListNode* mergeVector(vector<ListNode*>& lists, int i, int j) {
        if (i == j) {
            return lists[i];
        }
        if (i + 1 == j) {
            return merge2Lists(lists[i], lists[j]);
        }

        ListNode* left = mergeVector(lists, i, (i + j) / 2);
        ListNode* right = mergeVector(lists, (i + j) / 2 + 1, j);

        return merge2Lists(left, right);
    }

    ListNode* merge2Lists(ListNode* l1, ListNode* l2) {
        ListNode dummy(0);
        dummy.next = l1;
        l1 = &dummy;
        while (l1->next != nullptr && l2 != nullptr) {
            if (l1->next->val > l2->val) {
                ListNode* temp = l1->next;
                l1->next = l2;
                l2 = l2->next;
                l1->next->next = temp;
            }
            l1 = l1->next;
        }
        if (l2 != nullptr) l1->next = l2;

        return dummy.next;
    }

   public:
    ListNode* mergeKLists(vector<ListNode*>& lists) {
        if (lists.empty()) return nullptr;
        return mergeVector(lists, 0, lists.size() - 1);
    }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int k;
    if (!(cin >> k)) return 0;

    vector<ListNode*> lists;
    for (int i = 0; i < k; i++) {
        int n;
        cin >> n;
        ListNode dummy(0);
        ListNode* curr = &dummy;
        for (int j = 0; j < n; j++) {
            int val;
            cin >> val;
            curr->next = new ListNode(val);
            curr = curr->next;
        }
        lists.push_back(dummy.next);
    }

    Solution obj;
    ListNode* res = obj.mergeKLists(lists);

    while (res != nullptr) {
        cout << res->val << " ";
        res = res->next;
    }
    cout << "\n";

    return 0;
}