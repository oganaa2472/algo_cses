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

struct Comb {
    vector<long long> fact, invFact;
    Comb(int maxN) {
        fact.resize(maxN+1);
        invFact.resize(maxN+1);
        fact[0] = 1;
        for (int i = 1; i <= maxN; i++) fact[i] = fact[i-1] * i % MOD;
        invFact[maxN] = modpow(fact[maxN], MOD-2);
        for (int i = maxN-1; i >= 0; i--) invFact[i] = invFact[i+1] * (i+1) % MOD;
    }
    long long nCr(int n, int r) {
        if (r < 0 || r > n) return 0;
        return fact[n] * invFact[r] % MOD * invFact[n-r] % MOD;
    }
};

int main() {
    int n, m;
    cin >> n >> m;
    Comb C(n+m); // need up to n+m
    cout << C.nCr(n+m-1, m) << "\n";
    return 0;
}
