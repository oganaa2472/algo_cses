#include <bits/stdc++.h>
using namespace std;
const long long MOD = 1e9+7;

long long modpow(long long a, long long b) {
    long long res = 1;
    while(b > 0) {
        if(b & 1) res = res * a % MOD;
        a = a * a % MOD;
        b >>= 1;
    }
    return res;
}

int main() {
    int n;
    cin >> n;

    if(n % 2 != 0) {
        cout << 0 << "\n"; // impossible
        return 0;
    }

    int m = n / 2;
    vector<long long> fact(2*m+2), invFact(2*m+2);
    fact[0] = 1;
    for(int i = 1; i <= 2*m; i++) fact[i] = fact[i-1] * i % MOD;
    invFact[2*m] = modpow(fact[2*m], MOD-2);
    for(int i = 2*m-1; i >= 0; i--) invFact[i] = invFact[i+1] * (i+1) % MOD;

    long long catalan = fact[2*m] * invFact[m] % MOD * invFact[m+1] % MOD;
    cout << catalan << "\n";
    return 0;
}
