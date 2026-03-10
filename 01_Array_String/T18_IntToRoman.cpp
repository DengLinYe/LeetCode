#include <algorithm>
#include <iostream>
#include <queue>
#include <string>
#include <unordered_map>
#include <vector>

using namespace std;

class Solution {
 public:
  string intToRoman(int num) {
    int base = 1000;
    string roman;
    while (base > 0) {
      int k = num / base;
      num = num % base;

      if (k == 0) {
        base /= 10;
        continue;
      }

      if (k == 9 || k == 4) {
        roman = roman + Tran(base) + Tran((k + 1) * base);
      } else if (k >= 5) {
        roman += Tran(5 * base);
        for (int i = 5; i < k; i++) {
          roman += Tran(base);
        }
      } else {
        for (int i = 0; i < k; i++) {
          roman += Tran(base);
        }
      }

      base /= 10;
    }

    return roman;
  }

 private:
  string Tran(int a) {
    switch (a) {
      case 1:
        return "I";
      case 5:
        return "V";
      case 10:
        return "X";
      case 50:
        return "L";
      case 100:
        return "C";
      case 500:
        return "D";
      case 1000:
        return "M";
      default:
        return "0";
    }
  }
};

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  int num;
  cin >> num;

  Solution obj;
  string result = obj.intToRoman(num);

  for (int i = 0; i < result.size(); i++) {
    cout << result[i];
  }

  return 0;
}