#include <bits/stdc++.h>
using namespace std;

const int MOD = 1e9 + 7;

struct TrieNode {
    int children[26];
    bool is_end;
    TrieNode() {
        for (int i = 0; i < 26; i++) children[i] = -1;
        is_end = false;
    }
};
vector<TrieNode> trie;
void insert(const string& word){
    int node = 0;
    for(char c:word){
        int idx = c - 'a';
        if(trie[node].children[idx]==-1){
            trie[node].children[idx] = trie.size();
            trie.emplace_back();
        }
        node = trie[node].children[idx];
    }
    trie[node].is_end = true;
}
int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    string s;
    cin>>s;
    int k;
    cin>>k;
    trie.emplace_back();
    for(int i=0;i<k;i++){
        string word;
        cin>>word;
        insert(word);
    }
    int n = s.size();
    vector<int> dp(n+1,0);
    dp[0] = 1;
    for(int i = 0; i<n;i++){
        if(dp[i]==0) continue;
        int node = 0;
        for(int j = i; j<n;j++){
            int idx = s[j]-'a';
            if(trie[node].children[idx]==-1) break;
            node = trie[node].children[idx];
            if(trie[node].is_end){
                dp[j+1] = (dp[j+1]+dp[i])%MOD;
            }
        }
    }
    cout<<dp[n]<<endl;
}

