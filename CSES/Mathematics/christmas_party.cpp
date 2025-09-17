#include <bits/stdc++.h>
using namespace std;
const int MOD = 1e9+7;

int main() {
    int n;
    cin >> n;

    if (n == 0) {
        cout << 1 << "\n"; // by convention
        return 0;
    }
    if (n == 1) {
        cout << 0 << "\n";
        return 0;
    }

    vector<long long> der(n+1);
    der[0] = 1;
    der[1] = 0;
    for (int i = 2; i <= n; i++) {
        der[i] = ( (i-1) * (der[i-1] + der[i-2]) ) % MOD;
    }

    cout << der[n] << "\n";
    return 0;
}
