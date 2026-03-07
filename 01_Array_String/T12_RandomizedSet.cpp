#include <algorithm>
#include <iostream>
#include <queue>
#include <random>
#include <string>
#include <unordered_map>
#include <vector>

using namespace std;

static std::random_device rd;
static std::mt19937 gen(rd());

class RandomizedSet {
 public:
  unordered_map<int, int> index;
  vector<int> set;

  RandomizedSet() { set.push_back(-1); }

  bool insert(int val) {
    if (index[val] == 0) {
      set.push_back(val);
      index[val] = set.size() - 1;
      return true;
    } else {
      return false;
    }
  }

  bool remove(int val) {
    if (index[val] == 0) {
      return false;
    } else {
      index[set.back()] = index[val];
      set[index[val]] = set.back();
      set.pop_back();
      index[val] = 0;
      return true;
    }
  }

  int getRandom() {
    uniform_int_distribution<> dis(1, set.size() - 1);

    return set[dis(gen)];
  }
};

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  int n;
  while (cin >> n) {
    RandomizedSet* obj = nullptr;
    cout << "[";
    for (int i = 0; i < n; ++i) {
      string op;
      cin >> op;
      if (op == "RandomizedSet") {
        obj = new RandomizedSet();
        cout << "null";
      } else if (op == "insert") {
        int val;
        cin >> val;
        cout << (obj->insert(val) ? "true" : "false");
      } else if (op == "remove") {
        int val;
        cin >> val;
        cout << (obj->remove(val) ? "true" : "false");
      } else if (op == "getRandom") {
        cout << obj->getRandom();
      }

      if (i < n - 1) cout << ",";
    }
    cout << "]\n";

    delete obj;
  }

  return 0;
}