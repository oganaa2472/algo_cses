#include <bits/stdc++.h>
using namespace std;
using u128 = unsigned __int128;
using u64 = unsigned long long;

// Fast modular multiplication to avoid overflow
u64 mulmod(u64 a, u64 b, u64 mod) {
    return (u128)a * b % mod;
}

// Fast modular exponentiation
u64 powmod(u64 a, u64 e, u64 mod) {
    u64 res = 1;
    while (e) {
        if (e & 1) res = mulmod(res, a, mod);
        a = mulmod(a, a, mod);
        e >>= 1;
    }
    return res;
}

// Miller-Rabin primality test
bool isPrime(u64 n) {
    if (n < 2) return false;
    for (u64 p : {2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37}) {
        if (n % p == 0) return n == p;
    }

    u64 d = n - 1, s = 0;
    while ((d & 1) == 0) {
        d >>= 1;
        s++;
    }

    auto check = [&](u64 a) {
        if (a % n == 0) return true;
        u64 x = powmod(a, d, n);
        if (x == 1 || x == n - 1) return true;
        for (u64 r = 1; r < s; r++) {
            x = mulmod(x, x, n);
            if (x == n - 1) return true;
        }
        return false;
    };

    // Deterministic bases for 64-bit integers
    for (u64 a : {2ULL, 325ULL, 9375ULL, 28178ULL,
                  450775ULL, 9780504ULL, 1795265022ULL}) {
        if (!check(a)) return false;
    }
    return true;
}

u64 nextPrime(u64 n) {
    u64 x = n + 1;
    while (!isPrime(x)) x++;
    return x;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int t;
    cin >> t;
    while (t--) {
        u64 n;
        cin >> n;
        cout << nextPrime(n) << "\n";
    }
}
