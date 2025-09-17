#include <bits/stdc++.h>
using namespace std;

int main() {
    int n, a, b;
    cin >> n >> a >> b;

    vector<vector<long long>> dp(n + 1, vector<long long>(6 * n + 1, 0));
    dp[0][0] = 1;

    for (int i = 1; i <= n; i++) {
        for (int s = i; s <= 6 * i; s++) {
            for (int k = 1; k <= 6; k++) {
                if (s - k >= 0)
                    dp[i][s] += dp[i-1][s-k];
            }
        }
    }

    long long favorable = 0;
    for (int s = a; s <= b; s++) {
        if (s <= 6 * n)
            favorable += dp[n][s];
    }

    long long total = pow(6, n);
    double probability = (double)favorable / total;

    cout << fixed << setprecision(6) << probability << "\n";
    return 0;
}
