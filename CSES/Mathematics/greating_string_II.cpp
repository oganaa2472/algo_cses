#include <bits/stdc++.h>
using namespace std;
const int MOD = 1e9+7;

long long modpow(long long a, long long b) {
    long long res = 1;
    while (b > 0) {
        if (b & 1) res = res * a % MOD;
        a = a * a % MOD;
        b >>= 1;
    }
    return res;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    string s;
    cin >> s;
    int n = s.size();

    unordered_map<char,int> freq;
    for(char ch:s){
        freq[ch]++;
    }

    // Precompute factorials and inverse factorials
    vector<long long> fact(n+1), invFact(n+1);
    fact[0] = 1;
    for (int i = 1; i <= n; i++) fact[i] = fact[i-1] * i % MOD;
    invFact[n] = modpow(fact[n], MOD-2);
    for (int i = n-1; i >= 0; i--) invFact[i] = invFact[i+1] * (i+1) % MOD;

    long long ans = fact[n];
    for (auto [ch, cnt] : freq) {
        ans = ans * invFact[cnt] % MOD;
    }

    cout << ans << "\n";
    return 0;
}
