#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
const int maxVal = 1e6 + 10;
const int mod = 1e9 + 7;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    vector<vector<ll>> dp(maxVal, vector<ll>(8, 0));

    // base case
    for (int i = 0; i < 8; i++) {
        dp[0][i] = 1;
    }

    // DP transitions
    for (int i = 1; i < maxVal; i++) {
        for (int j = 0; j < 8; j++) {
            if (j == 0 || j == 2 || j == 3 || j == 4 || j == 5) {
                dp[i][j] = (dp[i - 1][0] + dp[i - 1][1] + dp[i - 1][3] +
                            dp[i - 1][4] + dp[i - 1][5]) % mod;
            } else {
                dp[i][j] = (dp[i - 1][2] + dp[i - 1][6] + dp[i - 1][7]) % mod;
            }
        }
    }

    int t;
    cin >> t;
    while (t--) {
        int n;
        cin >> n;
        ll ans = (dp[n - 1][3] + dp[n - 1][7]) % mod;
        cout << ans << "\n";
    }

    return 0;
}
