#include <iostream>
#include <string>
#include <vector>

using namespace std;

class MinStack {
   private:
    vector<int> stack;
    vector<int> minStack;

   public:
    MinStack() {}

    void push(int val) {
        stack.push_back(val);
        if (minStack.empty() || val <= minStack.back()) {
            minStack.push_back(val);
        }
    }

    void pop() {
        if (stack.back() == minStack.back()) {
            minStack.pop_back();
        }
        stack.pop_back();
    }

    int top() { return stack.back(); }

    int getMin() { return minStack.back(); }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    if (cin >> n) {
        MinStack minStack;
        for (int i = 0; i < n; i++) {
            string cmd;
            cin >> cmd;

            if (cmd == "MinStack") {
                cout << "null ";
            } else if (cmd == "push") {
                int val;
                cin >> val;
                minStack.push(val);
                cout << "null ";
            } else if (cmd == "pop") {
                minStack.pop();
                cout << "null ";
            } else if (cmd == "top") {
                cout << minStack.top() << " ";
            } else if (cmd == "getMin") {
                cout << minStack.getMin() << " ";
            }
        }
        cout << "\n";
    }

    return 0;
}