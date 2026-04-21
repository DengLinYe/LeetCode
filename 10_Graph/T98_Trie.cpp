#include <algorithm>
#include <iostream>
#include <queue>
#include <string>
#include <unordered_map>
#include <vector>

using namespace std;

struct Node {
    string val;
    vector<Node*> children;

    Node(string _val) : val(_val) { children = vector<Node*>(); }
};

class Trie {
   private:
    Node* root;

    int isContain(string& pre, string& word) {
        int n = pre.size(), m = word.size();

        for (int i = 0; i < n; i++) {
            if (i == m) return -m;

            if (pre[i] != word[i]) {
                return i;
            }
        }

        return n;
    }

   public:
    Trie() { root = new Node(""); }

    void insert(string word) {
        Node* curr = root;
        while (true) {
            if (curr->children.empty()) {
                curr->children.push_back(new Node(word));
                if (curr->val != "") curr->children.push_back(new Node(curr->val));
                return;
            }

            int basePre = isContain(curr->val, word);
            bool isContinue = false;
            for (int i = 0; i < curr->children.size(); i++) {
                auto& node = curr->children[i];
                int res = isContain(node->val, word);
                /* 这里res的取值必须确定一下：
                首先要知道的是，进入到这一层之后，node->val.size()是一定大于或等于curr->val.size()的，也即大于或等于basePre。
                1. 如果word比curr要短，那么它不可能进入到这一层；
                2. 如果word和curr等长，那么它在进来之前，就已经pushback了；
                3. 那么word一定比curr长，这时：（res > basePre 防止往叶子节点上加，并且不匹配前缀同curr者）
                    1. word是node的前缀但不相等（res < 0）：把word插入到curr与node之间，并额外并入word作为叶子；
                    2. node是word的前缀（res == node->val.size()）：
                        1. 如果node和word相等（res ==
                word.size()）：找node的孩子，如果之前有过word，那么其孩子一定还有一个与word相等的，否则添加；
                        2. 如果node和word不相等，那就是纯前缀，进入到下一层。
                    3. node和word有共同前缀：就拆分。
                 */
                if (res < 0) {
                    Node* tempNode = node;
                    swap(node, curr->children.back());
                    curr->children.pop_back();
                    curr->children.push_back(new Node(word));
                    curr->children.back()->children.push_back(tempNode);
                    curr->children.back()->children.push_back(new Node(word));
                    return;
                } else if (res > basePre) {
                    if (res < node->val.size()) {
                        string prefix = word.substr(0, res);
                        Node* tempNode = node;
                        swap(node, curr->children.back());
                        curr->children.pop_back();
                        curr->children.push_back(new Node(prefix));
                        curr->children.back()->children.push_back(tempNode);
                        curr->children.back()->children.push_back(new Node(word));
                        return;
                    } else {
                        if (res < word.size()) {
                            curr = node;
                            isContinue = true;
                            break;
                        } else {
                            for (auto subNode : node->children) {
                                if (subNode->val == word) {
                                    return;
                                }
                            }
                            node->children.push_back(new Node(word));
                        }
                    }
                }
            }
            if (isContinue) continue;

            curr->children.push_back(new Node(word));
            return;
        }
    }

    bool search(string word) {
        Node* curr = root;
        while (true) {
            int basePre = isContain(curr->val, word);
            bool isContinue = false;
            for (auto node : curr->children) {
                int res = isContain(node->val, word);
                if (res > basePre) {
                    if (res == node->val.size()) {
                        if (res < word.size()) {
                            curr = node;
                            isContinue = true;
                            break;
                        } else {
                            if (node->children.empty()) return true;

                            for (auto subNode : node->children) {
                                if (subNode->val == word) {
                                    return true;
                                }
                            }

                            return false;
                        }
                    }
                }
            }
            if (isContinue) continue;

            return false;
        }
        return false;
    }

    bool startsWith(string prefix) {
        Node* curr = root;
        while (true) {
            bool isContinue = false;
            for (auto node : curr->children) {
                int res = isContain(node->val, prefix);
                if (res < 0) {
                    return true;
                } else if (res == node->val.size()) {
                    if (res == prefix.size() && node->children.empty()) {
                        return true;
                    } else {
                        curr = node;
                        isContinue = true;
                        break;
                    }
                }
            }
            if (isContinue) continue;

            return false;
        }

        return false;
    }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    Trie trie;
    trie.insert("ab");
    trie.insert("abc");
    trie.insert("ab");  // 重复插入一次 "ab"

    cout << trie.search("ab");  // 致命错误：这里会返回 false！

    return 0;
}