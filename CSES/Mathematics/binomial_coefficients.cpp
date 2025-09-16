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

    int n;
    cin >> n;
    vector<pair<int,int>> queries(n);
    int maxA = 0;
    for (int i = 0; i < n; i++) {
        cin >> queries[i].first >> queries[i].second;
        maxA = max(maxA, queries[i].first);
    }

    // Precompute factorials and inverse factorials
    vector<long long> fact(maxA+1), invFact(maxA+1);
    fact[0] = 1;
    for (int i = 1; i <= maxA; i++) fact[i] = fact[i-1] * i % MOD;
    invFact[maxA] = modpow(fact[maxA], MOD-2);
    for (int i = maxA-1; i >= 0; i--) invFact[i] = invFact[i+1] * (i+1) % MOD;

    // Answer queries
    for (auto [a, b] : queries) {
        if (b < 0 || b > a) cout << 0 << "\n";
        else {
            long long ans = fact[a] * invFact[b] % MOD * invFact[a-b] % MOD;
            cout << ans << "\n";
        }
    }
    return 0;
}
