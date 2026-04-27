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
    ListNode* sortList(ListNode* head) {
        ListNode dummy(0);

        while (head != nullptr) {
            ListNode* curr = &dummy;
            while (curr->next != nullptr && curr->next->val < head->val) {
                curr = curr->next;
            }
            ListNode* temp = curr->next;
            curr->next = head;
            int right = (temp == nullptr ? INT_MAX : temp->val);
            while (head->next != nullptr && head->next->val > head->val && head->next->val < right) head = head->next;
            ListNode* next = head->next;
            head->next = temp;
            head = next;
        }

        return dummy.next;
    }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;
    ListNode dummy(0);
    ListNode* curr = &dummy;

    while (curr != nullptr && n > 0) {
        int in;
        cin >> in;
        curr->next = new ListNode(in);
        curr = curr->next;
        n--;
    }

    Solution obj;
    curr = obj.sortList(dummy.next);
    while (curr != nullptr) {
        cout << curr->val << " ";
        curr = curr->next;
    }

    return 0;
}