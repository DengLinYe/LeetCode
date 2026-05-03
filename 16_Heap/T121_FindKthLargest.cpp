#include <algorithm>
#include <iostream>
#include <queue>
#include <string>
#include <unordered_map>
#include <vector>

using namespace std;

struct MaxHeap {
    int size;
    vector<int> heap;

    MaxHeap(int _size, vector<int>& _heap) {
        size = _size;
        heap = _heap;

        for (int i = size / 2 - 1; i >= 0; i--) {
            siftDown(i);
        }
    }

    void siftDown(int index) {
        if (index >= size) return;

        int l = index * 2 + 1, r = index * 2 + 2, largest = index;
        if (l < size && heap[l] > heap[largest]) largest = l;
        if (r < size && heap[r] > heap[largest]) largest = r;
        if (largest != index) {
            swap(heap[index], heap[largest]);
            siftDown(largest);
        }
    }

    bool getMax(int& maxNum) {
        if (size == 0) return false;

        maxNum = heap[0];
        swap(heap[0], heap[size - 1]);
        size--;
        siftDown(0);

        return true;
    }
};

class Solution {
   public:
    int findKthLargest(vector<int>& nums, int k) {
        MaxHeap heap(nums.size(), nums);
        int maxNum;
        for (int i = 0; i < k; i++) {
            heap.getMax(maxNum);
        }

        return maxNum;
    }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, k;
    cin >> n >> k;
    vector<int> nums(n);
    for (int i = 0; i < n; i++) {
        cin >> nums[i];
    }

    Solution obj;
    cout << obj.findKthLargest(nums, k);

    return 0;
}