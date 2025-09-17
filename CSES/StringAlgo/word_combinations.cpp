#include <bits/stdc++.h>
using namespace std;

const int MOD = 1e9 + 7;

struct TrieNode {
    unordered_map<char, TrieNode*> children;
    bool isWord = false;
};

void insert(TrieNode* root, const string &word) {
    TrieNode* node = root;
    for(char c : word) {
        if(!node->children.count(c))
            node->children[c] = new TrieNode();
        node = node->children[c];
    }
    node->isWord = true;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    string s;
    cin >> s;
    int n = s.size();

    int k;
    cin >> k;

    TrieNode* root = new TrieNode();
    int maxLen = 0;
    for(int i = 0; i < k; i++){
        string word;
        cin >> word;
        insert(root, word);
        maxLen = max(maxLen, (int)word.size());
    }

    vector<int> dp(n+1, 0);
    dp[0] = 1; // empty string

    for(int i = 1; i <= n; i++){
        TrieNode* node = root;
        for(int j = i-1; j >= max(0, i - maxLen); j--){
            char c = s[j];
            if(!node->children.count(c)) break;
            node = node->children[c];
            if(node->isWord){
                dp[i] = (dp[i] + dp[j]) % MOD;
            }
        }
    }

    cout << dp[n] << "\n";
}
