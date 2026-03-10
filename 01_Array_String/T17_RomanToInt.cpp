#include <algorithm>
#include <iostream>
#include <queue>
#include <string>
#include <unordered_map>
#include <vector>

using namespace std;

class Solution {
 public:
  int romanToInt(string s) {
    int n = s.size(), sum = 0;
    unordered_map<string, int> value;
    value["I"] = 1;
    value["IV"] = 4;
    value["V"] = 5;
    value["IX"] = 9;
    value["X"] = 10;
    value["XL"] = 40;
    value["L"] = 50;
    value["XC"] = 90;
    value["C"] = 100;
    value["CD"] = 400;
    value["D"] = 500;
    value["CM"] = 900;
    value["M"] = 1000;

    for (int i = 0; i < n; i++) {
      switch (s[i]) {
        case 'I':
          if (i != n - 1 && (s[i + 1] == 'V' || s[i + 1] == 'X')) {
            sum += value[s.substr(i, 2)];
            i++;
          } else {
            sum += value[s.substr(i, 1)];
          }
          break;
        case 'X':
          if (i != n - 1 && (s[i + 1] == 'L' || s[i + 1] == 'C')) {
            sum += value[s.substr(i, 2)];
            i++;
          } else {
            sum += value[s.substr(i, 1)];
          }
          break;
        case 'C':
          if (i != n - 1 && (s[i + 1] == 'D' || s[i + 1] == 'M')) {
            sum += value[s.substr(i, 2)];
            i++;
          } else {
            sum += value[s.substr(i, 1)];
          }
          break;
        default:
          sum += value[s.substr(i, 1)];
          break;
      }
    }

    return sum;
  }
};

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  string s;
  cin >> s;

  Solution obj;
  cout << obj.romanToInt(s) << "\n";

  return 0;
}