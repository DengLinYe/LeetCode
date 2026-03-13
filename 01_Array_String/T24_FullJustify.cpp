#include <algorithm>
#include <iostream>
#include <queue>
#include <string>
#include <unordered_map>
#include <vector>

using namespace std;

class Solution {
 public:
  vector<string> fullJustify(vector<string>& words, int maxWidth) {
    vector<string> lines;
    int lineLen = 0, lineSt = 0, n = words.size();

    for (int i = 0; i < n; i++) {
      if (words[i].size() + lineLen > maxWidth - max(0, i - lineSt)) {
        string newLine;

        for (int j = lineSt; j < i; j++) {
          newLine += words[j];
          int spaceNum = (maxWidth - lineLen) / max(1, (i - lineSt - 1));

          if (j < i - 1 || i - lineSt - 1 == 0) {
            for (int k = 0; k < spaceNum; k++) {
              newLine += " ";
            }
            if (j < lineSt + (maxWidth - lineLen) % max(1, (i - lineSt - 1))) {
              newLine += " ";
            }
          }
        }

        lines.push_back(newLine);
        lineSt = i--;
        lineLen = 0;
      } else {
        lineLen += words[i].size();

        if (i == n - 1) {
          string newLine;

          for (int j = lineSt; j < i + 1; j++) {
            newLine += words[j] + (j == i ? "" : " ");
            if (j == i) {
              int len = maxWidth - lineLen - i + lineSt;
              while (len-- > 0) newLine += " ";
            }
          }

          lines.push_back(newLine);
        }
      }
    }

    return lines;
  }
};

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  int n, maxWidth;
  cin >> n >> maxWidth;
  cin.ignore();

  vector<string> words(n);
  for (int i = 0; i < n; i++) {
    cin >> words[i];
  }

  Solution obj;
  vector<string> lines = obj.fullJustify(words, maxWidth);

  for (string x : lines) {
    cout << x << endl;
  }
  return 0;
}