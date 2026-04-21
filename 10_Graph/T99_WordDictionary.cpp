#include <iostream>
#include <string>
#include <vector>

using namespace std;

class WordDictionary {
   private:
    struct Node {
        bool isEnd;
        Node* next[26];

        Node(bool _isEnd) : isEnd(_isEnd) {
            for (int i = 0; i < 26; i++) {
                next[i] = nullptr;
            }
        }
    };
    Node* root;

    bool findWord(string& word, int i, Node* curr) {
        if (i >= word.size()) return curr->isEnd;

        if (word[i] == '.') {
            for (int k = 0; k < 26; k++) {
                if (curr->next[k] != nullptr && findWord(word, i + 1, curr->next[k])) return true;
            }
        } else {
            if (curr->next[word[i] - 'a'] != nullptr && findWord(word, i + 1, curr->next[word[i] - 'a'])) return true;
        }

        return false;
    }

   public:
    WordDictionary() { root = new Node(false); }

    void addWord(string word) {
        Node* curr = root;
        for (char c : word) {
            if (curr->next[c - 'a'] == nullptr) {
                curr->next[c - 'a'] = new Node(false);
            }
            curr = curr->next[c - 'a'];
        }
        curr->isEnd = true;
    }

    bool search(string word) { return findWord(word, 0, root); }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    WordDictionary* obj = new WordDictionary();
    int n;
    if (!(cin >> n)) return 0;

    for (int i = 0; i < n; i++) {
        string op, word;
        cin >> op >> word;
        if (op == "addWord") {
            obj->addWord(word);
            cout << "null\n";
        } else if (op == "search") {
            cout << (obj->search(word) ? "true" : "false") << "\n";
        }
    }

    return 0;
}