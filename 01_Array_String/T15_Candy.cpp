#include <algorithm>
#include <iostream>
#include <queue>
#include <string>
#include <unordered_map>
#include <vector>

using namespace std;

class Solution {
 public:
  int candy(vector<int>& ratings) {
    int n = ratings.size(), sum = 0, flag = 0, base = 1, tempSum = 0;
    if (n == 1) return 1;
    ratings.push_back(ratings.back());
    for (int i = 1; i < n + 1; i++) {
      int sub = ratings[i] - ratings[i - 1];
      int cat = sub * flag;
      if (cat > 0) {
        tempSum++;
      } else if (cat < 0) {
        if (flag < 0) {
          sum += max(0, base - tempSum - 2);
          base = 1;
        }
        sum += (2 * base + tempSum + (flag - 1) * (-1)) * (tempSum + 1) / 2;
        if (flag > 0) base += tempSum + 1;
        flag *= -1;
        tempSum = 0;
      } else {
        if (sub == 0) {
          if (flag != 0) {
            if (flag < 0) {
              sum += max(0, base - tempSum - 2);
              base = 1;
            }
            if (flag < 0) base = 1;
            sum += (2 * base + tempSum + 1) * (tempSum + 2) / 2;
            tempSum = 0;
            flag *= 0;
          } else {
            sum++;
            base = 1;
          }
        } else {
          if (sub > 0) {
            flag = 1;
          } else {
            flag = -1;
          }
        }
      }
    }
    return sum;
  }
};

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  int n;
  while (cin >> n) {
    vector<int> ratings(n);
    for (int i = 0; i < n; i++) {
      cin >> ratings[i];
    }

    Solution obj;
    int sum = obj.candy(ratings);
    cout << sum;
  }

  return 0;
}