#include <algorithm>
#include <iostream>
#include <queue>
#include <string>
#include <unordered_map>
#include <vector>

using namespace std;

class Solution {
 public:
  vector<int> findSubstring(string s, vector<string>& words) {
    unordered_map<string, int> wordsFeq;
    for (string x : words) wordsFeq[x]++;

    int wordLen = words[0].size(), n = words.size(), m = s.size();
    int subLen = wordLen * n;
    vector<int> res;

    for (int i = 0; i < wordLen; i++) {
      unordered_map<string, int> nowWordFeq;
      int left = i, nowMat = 0;
      for (int right = i; right <= m - wordLen; right += wordLen) {
        string sub = s.substr(right, wordLen);
        if (wordsFeq[sub] == 0) {
          left = right + wordLen;
          nowWordFeq.clear();
          nowMat = 0;
        } else {
          nowWordFeq[sub]++;
          nowMat++;
          while (wordsFeq[sub] < nowWordFeq[sub]) {
            string backSub = s.substr(left, wordLen);
            nowWordFeq[backSub]--;
            nowMat--;
            left += wordLen;
          }
          if (nowMat == n) {
            res.push_back(left);
            nowMat--;
            nowWordFeq[s.substr(left, wordLen)]--;
            left += wordLen;
          }
        }
      }
    }

    return res;
  }
};

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  int n;
  cin >> n;

  vector<string> words(n);
  for (int i = 0; i < n; i++) {
    cin >> words[i];
  }

  string s;
  cin >> s;

  Solution obj;
  vector<int> res = obj.findSubstring(s, words);
  for (int x : res) {
    cout << x << " ";
  }

  return 0;
}