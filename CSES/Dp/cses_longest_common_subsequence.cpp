#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
const int maxVal = 1e6 + 10;
const int mod = 1e9 + 7;
int main() {

    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int n, m;
    cin >> n >> m;
    
    vector<long long> a(n), b(m);
    for (int i = 0; i < n; i++) cin >> a[i];
    for (int j = 0; j < m; j++) cin >> b[j];
    
    vector<vector<int>> dp(n + 1, vector<int>(m + 1, 0));
    
    // Fill DP table
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            if (a[i - 1] == b[j - 1])
                dp[i][j] = dp[i - 1][j - 1] + 1;
            else
                dp[i][j] = max(dp[i - 1][j], dp[i][j - 1]);
        }
    }
    
    int i = n, j = m;
    vector<long long> lcs;
    while (i > 0 && j > 0) {
        if (a[i - 1] == b[j - 1]) {
            lcs.push_back(a[i - 1]);
            i--; j--;
        } else if (dp[i - 1][j] > dp[i][j - 1]) {
            i--;
        } else {
            j--;
        }
    }

    reverse(lcs.begin(), lcs.end());

    // Output
    cout << dp[n][m] << "\n";
    for (auto x : lcs) cout << x << " ";
    cout << "\n";

    return 0;

}
