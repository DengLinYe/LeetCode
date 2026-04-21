#include <iostream>
#include <queue>
#include <string>
#include <unordered_map>
#include <vector>

using namespace std;

class Solution {
   public:
    int ladderLength(string beginWord, string endWord, vector<string>& wordList) {
        unordered_map<string, int> wordMap;
        for (string& word : wordList) {
            wordMap[word] = 0;
        }

        queue<pair<string, int>> q;
        int n = beginWord.size();

        q.push({beginWord, 0});
        while (!q.empty()) {
            auto [curr, step] = q.front();
            q.pop();
            // cout << curr << ": ";

            if (curr == endWord) return step + 1;

            for (int i = 0; i < n; i++) {
                char ori = curr[i];
                for (int j = 0; j < 26; j++) {
                    if (ori == 'a' + j) continue;
                    curr[i] = 'a' + j;

                    if (wordMap.count(curr) && wordMap[curr] == 0) {
                        // cout << curr << " ";
                        wordMap[curr]++;
                        q.push({curr, step + 1});
                    }
                }
                curr[i] = ori;
            }
            // cout << endl;
        }

        // cout << endl;
        return 0;
    }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    string beginWord, endWord;
    if (!(cin >> beginWord >> endWord)) return 0;

    int n;
    if (!(cin >> n)) return 0;

    vector<string> wordList(n);
    for (int i = 0; i < n; i++) {
        cin >> wordList[i];
    }

    Solution obj;
    cout << obj.ladderLength(beginWord, endWord, wordList) << "\n";

    return 0;
}