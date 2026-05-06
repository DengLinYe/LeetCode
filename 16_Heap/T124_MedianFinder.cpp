#include <algorithm>
#include <iostream>
#include <queue>
#include <string>
#include <unordered_map>
#include <vector>

using namespace std;

class MedianFinder {
   private:
    priority_queue<int, vector<int>, greater<int>> bigger;
    priority_queue<int> smaller;

   public:
    MedianFinder() {}

    void addNum(int num) {
        if (smaller.empty() || num <= smaller.top()) {
            smaller.push(num);
        } else {
            bigger.push(num);
        }

        if (smaller.size() > bigger.size() + 1) {
            bigger.push(smaller.top());
            smaller.pop();
        } else if (bigger.size() > smaller.size()) {
            smaller.push(bigger.top());
            bigger.pop();
        }
    }
    double findMedian() {
        if (bigger.size() == smaller.size()) {
            return (bigger.top() + smaller.top()) / 2.0;
        } else {
            return smaller.top();
        }
    }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    MedianFinder* obj = new MedianFinder();
    obj->addNum(1);
    obj->addNum(2);
    cout << obj->findMedian() << endl;
    obj->addNum(3);
    cout << obj->findMedian() << endl;

    return 0;
}