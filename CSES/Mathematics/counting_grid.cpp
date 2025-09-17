#include <bits/stdc++.h>
using namespace std;
const long long MOD = 1e9+7;

long long modpow(long long a, long long b, long long MOD) {
    long long res = 1;
    a %= MOD;
    while(b) {
        if(b & 1) res = res * a % MOD;
        a = a * a % MOD;
        b >>= 1;
    }
    return res;
}

int main() {
    long long n;
    cin >> n;

    long long F0 = modpow(2, n*n % (MOD-1), MOD); // 2^(n^2) % MOD
    long long F180 = modpow(2, (n*n + (n%2)) /2 % (MOD-1), MOD); // ceil(n^2/2)
    long long F90;

    if(n%2 == 0) F90 = modpow(2, n*n/4 % (MOD-1), MOD);
    else F90 = modpow(2, (n*n + 3)/4 % (MOD-1), MOD);

    long long sum = (F0 + F180 + 2*F90) % MOD;
    long long inv4 = modpow(4, MOD-2, MOD);
    long long ans = sum * inv4 % MOD;
    cout << ans << "\n";
}
