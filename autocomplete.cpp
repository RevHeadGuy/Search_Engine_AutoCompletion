#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>
#include <queue>
#include <sstream>
#include <utility>
#include <algorithm>
using namespace std;

struct TrieNode {
    unordered_map<char, TrieNode*> children;
    bool isEnd = false;
    int freq = 0;          // frequency for completed word
    TrieNode() = default;
};

class Trie {
private:
    TrieNode* root;

    // DFS to collect words with their frequencies in subtree rooted at node
    void dfs_collect(TrieNode* node, string &path, vector<pair<int,string>> &collector) {
        if (!node) return;
        if (node->isEnd) {
            collector.emplace_back(node->freq, path);
        }
        for (auto &p : node->children) {
            path.push_back(p.first);
            dfs_collect(p.second, path, collector);
            path.pop_back();
        }
    }

public:
    Trie() { root = new TrieNode(); }

    // Insert a word; increments frequency if word already exists
    void insert(const string &word) {
        TrieNode* cur = root;
        for (char c : word) {
            if (!cur->children.count(c)) cur->children[c] = new TrieNode();
            cur = cur->children[c];
        }
        cur->isEnd = true;
        cur->freq += 1; // increment frequency
    }

    // Force-set frequency (useful to seed dataset with known counts)
    void setFrequency(const string &word, int frequency) {
        TrieNode* cur = root;
        for (char c : word) {
            if (!cur->children.count(c)) cur->children[c] = new TrieNode();
            cur = cur->children[c];
        }
        cur->isEnd = true;
        cur->freq = frequency;
    }

    // Return top-k suggestions for prefix
    vector<pair<int,string>> getTopK(const string &prefix, int k) {
        TrieNode* cur = root;
        for (char c : prefix) {
            if (!cur->children.count(c)) return {}; // no suggestions
            cur = cur->children[c];
        }

        // collect all words in subtree
        vector<pair<int,string>> collector; // pairs (freq, word)
        string path = prefix;
        dfs_collect(cur, path, collector);

        // Max-heap: higher freq first; if tie, lexicographically smaller first
        auto cmp = [](const pair<int,string> &a, const pair<int,string> &b) {
            if (a.first != b.first) return a.first < b.first; // larger freq higher priority
            return a.second > b.second; // lexicographically smaller higher priority
        };
        priority_queue<pair<int,string>, vector<pair<int,string>>, decltype(cmp)> pq(cmp);

        for (auto &p : collector) pq.push(p);

        vector<pair<int,string>> res;
        for (int i = 0; i < k && !pq.empty(); ++i) {
            res.push_back(pq.top()); pq.pop();
        }
        return res;
    }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    Trie trie;

    // --- Seed some sample search queries with frequencies --- Two ways: repeated insert or set specific frequency.
    trie.setFrequency("how to make pizza", 50);
    trie.setFrequency("how to make pasta", 30);
    trie.setFrequency("how to make pancakes", 20);
    trie.setFrequency("how to tie a tie", 45);
    trie.setFrequency("how to train your dragon", 5);
    trie.setFrequency("home remedies for cold", 40);
    trie.setFrequency("holiday packages", 25);
    trie.setFrequency("how to make pizza dough", 35);
    trie.setFrequency("how to make pizza at home", 28);
    trie.setFrequency("how to make protein shake", 18);
    trie.setFrequency("how to make money online", 55);
    trie.setFrequency("how to make coffee", 22);

    // Interactive demo: query multiple prefixes
    cout << "Autocomplete demo. Type prefix and k (e.g. \"how 5\") or type 'exit' to quit.\n";
    while (true) {
        cout << "\nPrefix> ";
        string prefix;
        if (!getline(cin, prefix)) break;
        if (prefix == "exit") break;
        if (prefix.empty()) { cout << "Please enter a prefix.\n"; continue; }

        // expecting input like: "how 5" or just "how" then ask for k
        // We try to parse trailing integer k if present
        stringstream ss(prefix);
        string prefToken;
        int k = 5; // default
        if (!(ss >> prefToken)) continue;
        if (ss >> k) {
            // parsed both
        } else {
            // user entered only prefix; ask for k
            cout << "k (default 5)? ";
            string kline;
            if (!getline(cin, kline) || kline.empty()) k = 5;
            else k = stoi(kline);
        }

        vector<pair<int,string>> suggestions = trie.getTopK(prefToken, k);
        if (suggestions.empty()) {
            cout << "No suggestions found for prefix \"" << prefToken << "\"\n";
        } else {
            cout << "Top " << suggestions.size() << " suggestions for prefix \"" << prefToken << "\":\n";
            for (auto &p : suggestions) {
                cout << "  [" << p.first << "] " << p.second << "\n";
            }
        }
    }

    cout << "Goodbye.\n";
    return 0;
}
