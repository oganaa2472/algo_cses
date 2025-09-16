#include <bits/stdc++.h>
using namespace std;

const int MOD = 1e9 + 7;

long long mod_pow(long long a, long long b) {
    if (a == 0 && b == 0) return 1; // 0^0 = 1
    long long result = 1;
    a %= MOD;
    while (b > 0) {
        if (b & 1) result = (result * a) % MOD;
        a = (a * a) % MOD;
        b >>= 1;
    }
    return result;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;
    while (n--) {
        long long a, b;
        cin >> a >> b;
        cout << mod_pow(a, b) << "\n";
    }
}
