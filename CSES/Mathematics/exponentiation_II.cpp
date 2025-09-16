#include <bits/stdc++.h>
using namespace std;

const int MOD = 1e9 + 7;

long long mod_pow(long long a, long long b, long long mod) {
    if (a == 0 && b == 0) return 1; // 0^0 = 1
    long long result = 1;
    a %= mod;
    while (b > 0) {
        if (b & 1) result = (result * a) % mod;
        a = (a * a) % mod;
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
        long long a, b,c;
        cin >> a >> b>>c;
        long long exp = mod_pow(b,c,MOD-1);
        cout << mod_pow(a, exp, MOD) << "\n";
    }
}
