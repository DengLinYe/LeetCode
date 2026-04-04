#include <algorithm>
#include <iostream>
#include <queue>
#include <string>
#include <unordered_map>
#include <vector>

using namespace std;

struct Pages {
    int key;
    int val;
    Pages* pre;
    Pages* next;

    Pages() : key(-1), val(-1), pre(nullptr), next(nullptr) {}
    Pages(int key, int val) : key(key), val(val), pre(nullptr), next(nullptr) {}
};

class LRUCache {
   private:
    int cap, size;
    unordered_map<int, Pages*> cache;
    Pages* CahceHead;
    Pages* CacheTail;

   public:
    LRUCache(int capacity) {
        size = 0;
        cap = capacity;
        CahceHead = new Pages();
        CacheTail = new Pages();
        CacheTail->pre = CahceHead;
        CahceHead->next = CacheTail;
    }

    int get(int key) {
        if (!cache.count(key)) {
            return -1;
        } else {
            moveToHead(cache[key]);

            return cache[key]->val;
        }
    }

    void put(int key, int value) {
        if (!cache.count(key)) {
            size++;
            Pages* temp = CahceHead->next;
            CahceHead->next = new Pages(key, value);
            CahceHead->next->next = temp;
            temp->pre = CahceHead->next;
            CahceHead->next->pre = CahceHead;
            cache[key] = CahceHead->next;

            if (size > cap) {
                removeTail();
                size--;
            }
        } else {
            cache[key]->val = value;
            moveToHead(cache[key]);
        }
    }

   private:
    void moveToHead(Pages* curr) {
        curr->pre->next = curr->next;
        curr->next->pre = curr->pre;

        Pages* temp = CahceHead->next;
        CahceHead->next = curr;
        curr->pre = CahceHead;
        curr->next = temp;
        temp->pre = curr;
    }

    void removeTail() {
        cache.erase(CacheTail->pre->key);
        Pages* temp = CacheTail->pre;
        temp->pre->next = CacheTail;
        CacheTail->pre = temp->pre;
        delete temp;
    }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    if (!(cin >> n)) return 0;

    LRUCache* lRUCache = nullptr;

    for (int i = 0; i < n; ++i) {
        string op;
        cin >> op;
        if (op == "LRUCache") {
            int capacity;
            cin >> capacity;
            lRUCache = new LRUCache(capacity);
            cout << "null ";
        } else if (op == "put") {
            int key, value;
            cin >> key >> value;
            lRUCache->put(key, value);
            cout << "null ";
        } else if (op == "get") {
            int key;
            cin >> key;
            cout << lRUCache->get(key) << " ";
        }
    }
    cout << endl;

    return 0;
}