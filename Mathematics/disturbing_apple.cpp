#include <iostream>
#include <vector>
using namespace std;

const long long MOD = 1e9 + 7;
const int MAX = 2000005;  // n + m - 1

vector<long long> fact(MAX), invFact(MAX);

// Fast exponentiation (a^b % MOD)
long long power(long long a, long long b) {
    long long result = 1;
    a %= MOD;
    while (b > 0) {
        if (b & 1) result = (result * a) % MOD;
        a = (a * a) % MOD;
        b >>= 1;
    }
    return result;
}

// Precompute factorials and their modular inverses
void precomputeFactorials() {
    fact[0] = invFact[0] = 1;
    for (int i = 1; i < MAX; ++i) {
        fact[i] = (fact[i - 1] * i) % MOD;
        invFact[i] = power(fact[i], MOD - 2);  // Fermat's little theorem for modular inverse
    }
}

// C(a, b) % MOD
long long nCr(long long a, long long b) {
    if (b < 0 || b > a) return 0;
    return fact[a] * invFact[b] % MOD * invFact[a - b] % MOD;
}

int main() {
    long long n, m;
    cin >> n >> m;

    // Precompute factorials and inverse factorials up to n + m - 1
    precomputeFactorials();

    // Compute the result as C(n + m - 1, m)
    long long result = nCr(n + m - 1, m);

    cout << result << endl;

    return 0;
}
