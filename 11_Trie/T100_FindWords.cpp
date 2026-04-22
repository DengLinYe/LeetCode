#include <algorithm>
#include <iostream>
#include <queue>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>

using namespace std;

struct Node {
    bool isEnd;
    int wordLen;
    Node* next[26];

    Node(bool _isEnd) : isEnd(_isEnd) {
        wordLen = 0;
        for (int i = 0; i < 26; i++) {
            next[i] = nullptr;
        }
    }
};

class Trie {
   public:
    Node* root;

    Trie() { root = new Node(false); }

    void addWord(string word) {
        Node* curr = root;
        for (char c : word) {
            curr->wordLen++;
            if (curr->next[c - 'a'] == nullptr) {
                curr->next[c - 'a'] = new Node(false);
            }
            curr = curr->next[c - 'a'];
        }
        curr->isEnd = true;
    }

    void findWord(string& word, int i, Node* curr) {
        if (i >= word.size()) return;

        curr->wordLen--;

        findWord(word, i + 1, curr->next[word[i] - 'a']);
    }
};

class Solution {
   private:
    Trie* wordTree;
    int n;
    int m;
    vector<string> res;
    unordered_set<string> isRes;

    void DFS(vector<vector<char>>& board, int i, int j, Node* curr, string prefix, unordered_set<int> visited) {
        if (curr->isEnd && !isRes.count(prefix)) {
            wordTree->findWord(prefix, 0, wordTree->root);
            isRes.insert(prefix);
            res.push_back(prefix);
        }

        if (curr->wordLen <= 0) return;

        if (i - 1 >= 0 && !visited.count((i - 1) * m + j) && curr->next[board[i - 1][j] - 'a'] != nullptr) {
            string temp = prefix + board[i - 1][j];
            unordered_set tempVis = visited;
            tempVis.insert((i - 1) * m + j);
            DFS(board, i - 1, j, curr->next[board[i - 1][j] - 'a'], temp, tempVis);
        }
        if (i + 1 < n && !visited.count((i + 1) * m + j) && curr->next[board[i + 1][j] - 'a'] != nullptr) {
            string temp = prefix + board[i + 1][j];
            unordered_set tempVis = visited;
            tempVis.insert((i + 1) * m + j);
            DFS(board, i + 1, j, curr->next[board[i + 1][j] - 'a'], temp, tempVis);
        }
        if (j - 1 >= 0 && !visited.count(i * m + j - 1) && curr->next[board[i][j - 1] - 'a'] != nullptr) {
            string temp = prefix + board[i][j - 1];
            unordered_set tempVis = visited;
            tempVis.insert(i * m + j - 1);
            DFS(board, i, j - 1, curr->next[board[i][j - 1] - 'a'], temp, tempVis);
        }
        if (j + 1 < m && !visited.count(i * m + j + 1) && curr->next[board[i][j + 1] - 'a'] != nullptr) {
            string temp = prefix + board[i][j + 1];
            unordered_set tempVis = visited;
            tempVis.insert(i * m + j + 1);
            DFS(board, i, j + 1, curr->next[board[i][j + 1] - 'a'], temp, tempVis);
        }
    }

   public:
    vector<string> findWords(vector<vector<char>>& board, vector<string>& words) {
        wordTree = new Trie();
        res.clear();
        isRes.clear();
        n = board.size();
        m = board[0].size();

        unordered_set<char> boardNum;
        for (auto& r : board) {
            for (char c : r) {
                boardNum.insert(c);
            }
        }
        for (string& w : words) {
            unordered_set<char> wordNum;
            for (char c : w) wordNum.insert(c);

            if (wordNum.size() <= boardNum.size()) {
                wordTree->addWord(w);
            }
        }

        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {
                if (wordTree->root->wordLen <= 0) return res;

                if (wordTree->root->next[board[i][j] - 'a'] != nullptr) {
                    unordered_set<int> visited;
                    visited.insert(i * m + j);
                    DFS(board, i, j, wordTree->root->next[board[i][j] - 'a'], string(1, board[i][j]), visited);
                }
            }
        }

        delete wordTree;
        return res;
    }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m;
    cin >> n >> m;
    vector<vector<char>> board(n, vector<char>(m));
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            cin >> board[i][j];
        }
    }

    cin >> n;
    vector<string> words(n);
    for (int i = 0; i < n; i++) {
        cin >> words[i];
    }

    Solution obj;
    vector<string> res = obj.findWords(board, words);
    for (string& r : res) {
        cout << r << " ";
    }

    return 0;
}