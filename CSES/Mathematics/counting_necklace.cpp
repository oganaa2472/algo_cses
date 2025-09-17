#include <bits/stdc++.h>
using namespace std;
const long long MOD = 1e9+7;

long long modpow(long long a, long long b) {
    long long res = 1;
    while(b) {
        if(b & 1) res = res * a % MOD;
        a = a * a % MOD;
        b >>= 1;
    }
    return res;
}

// Compute Euler's totient function for integer x
long long phi(long long x) {
    long long res = x;
    for(long long i = 2; i*i <= x; i++) {
        if(x % i == 0) {
            while(x % i == 0) x /= i;
            res -= res / i;
        }
    }
    if(x > 1) res -= res / x;
    return res;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    long long n, m;
    cin >> n >> m;

    long long ans = 0;
    for(long long d = 1; d*d <= n; d++) {
        if(n % d == 0) {
            long long d1 = d;
            long long d2 = n/d;

            ans = (ans + phi(n/d1) * modpow(m,d1) % MOD) % MOD;
            if(d1 != d2) 
                ans = (ans + phi(n/d2) * modpow(m,d2) % MOD) % MOD;
        }
    }

    // Divide by n modulo MOD
    long long n_inv = modpow(n, MOD-2);
    ans = ans * n_inv % MOD;

    cout << ans << "\n";
}
