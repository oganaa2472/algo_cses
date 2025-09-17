#include <bits/stdc++.h>
using namespace std;

vector<int> computePrefix(const string &pattern) {
    int m = pattern.size();
    vector<int> pi(m, 0);
    for(int i = 1; i < m; i++) {
        int j = pi[i-1];
        while(j > 0 && pattern[i] != pattern[j])
            j = pi[j-1];
        if(pattern[i] == pattern[j]) j++;
        pi[i] = j;
    }
    return pi;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    string s, pattern;
    cin >> s >> pattern;
    int n = s.size(), m = pattern.size();

    vector<int> pi = computePrefix(pattern);

    int j = 0; // current match length
    int count = 0;

    for(int i = 0; i < n; i++) {
        while(j > 0 && s[i] != pattern[j])
            j = pi[j-1];
        if(s[i] == pattern[j]) j++;
        if(j == m) {
            count++;       // match found at position i - m + 1
            j = pi[j-1];   // continue searching
        }
    }

    cout << count << "\n";
}
