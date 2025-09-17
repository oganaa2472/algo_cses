#include <bits/stdc++.h>
using namespace std;

vector<int> computePrefix(const string &s) {
    int n = s.size();
    vector<int> pi(n, 0);
    for(int i = 1; i < n; i++) {
        int j = pi[i-1];
        while(j > 0 && s[i] != s[j])
            j = pi[j-1];
        if(s[i] == s[j]) j++;
        pi[i] = j;
    }
    return pi;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    string s;
    cin >> s;
    int n = s.size();

    vector<int> pi = computePrefix(s);
    vector<int> borders;

    int len = pi[n-1];
    while(len > 0) {
        borders.push_back(len);
        len = pi[len-1];
    }

    sort(borders.begin(), borders.end()); // increasing order
    for(int b : borders) cout << b << " ";
    cout << "\n";
}
