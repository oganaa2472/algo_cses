#include <iostream>
#include <vector>
using namespace std;

const int MOD = 1e9 + 7;
const int MAX = 1000005;

vector<long long> fact(MAX), invFact(MAX);

// (a^b) % MOD-ийг тооцоолох функц
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

// Факториалууд болон урвуу факториалуудыг урьдчилан тооцоолох функц
void precomputeFactorials() {
    fact[0] = invFact[0] = 1;
    for (int i = 1; i < MAX; ++i) {
        fact[i] = (fact[i - 1] * i) % MOD;
        invFact[i] = power(fact[i], MOD - 2);  // Фермагийн бага теорем
    }
}

// Catalan тоог тооцоолох функц
long long catalan(int n) {
    if (n == 0) return 1;
    return fact[2 * n] * invFact[n] % MOD * invFact[n + 1] % MOD;
}

int main() {
    int n;
    cin >> n;

    if (n % 2 != 0) {
        cout << 0 << endl;  // Хэрэв n сондгой бол зөв хаалттай дараалал байхгүй
    } else {
        precomputeFactorials();
        int m = n / 2;
        cout << catalan(m) << endl;
    }

    return 0;
}
